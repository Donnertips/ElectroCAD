/* SPDX-License-Identifier: GPL-2.0-or-later */
#include "qetdiagramadapter.h"

#include "diagram.h"
#include "qetgraphicsitem/conductor.h"
#include "qetgraphicsitem/element.h"
#include "qetgraphicsitem/terminal.h"

#include <algorithm>
#include <map>
#include <numeric>
#include <QString>
#include <QUuid>
#include <utility>
#include <vector>

namespace electrocad {
namespace {

QString uuidString(const QUuid &uuid)
{
    return uuid.toString(QUuid::WithoutBraces);
}

} // namespace

ElectricalModel QetDiagramAdapter::buildModel(const Diagram &diagram)
{
    ElectricalModel model;
    std::vector<TerminalRef> references;
    std::map<const Terminal *, std::size_t> terminal_indices;

    // Register every placed symbol terminal, including terminals that are
    // currently unconnected. Element UUID + stable terminal UUID gives a
    // persistent identity across diagram moves and reloads.
    for (Element *element : diagram.elements()) {
        if (!element) {
            continue;
        }

        const QString componentId = uuidString(element->uuid());
        if (componentId.isEmpty()) {
            continue;
        }

        for (Terminal *terminal : element->terminals()) {
            if (!terminal) {
                continue;
            }

            const QString terminalId = uuidString(terminal->stableUuid());
            if (terminalId.isEmpty()) {
                continue;
            }

            TerminalRef reference{
                componentId.toStdString(),
                terminalId.toStdString()
            };
            if (!model.registerTerminal(reference)) {
                continue;
            }

            terminal_indices.emplace(terminal, references.size());
            references.push_back(std::move(reference));
        }
    }

    std::vector<std::size_t> parent(references.size());
    std::vector<bool> connected(references.size(), false);
    std::iota(parent.begin(), parent.end(), std::size_t{0});

    const auto findRoot = [&parent](std::size_t index) {
        while (parent[index] != index) {
            parent[index] = parent[parent[index]];
            index = parent[index];
        }
        return index;
    };

    // QElectroTech conductors are the authoritative explicit wire edges.
    // Junctions/branches naturally become connected components of this
    // graph. No continuity is inferred through a component's other pins.
    for (Conductor *conductor : diagram.conductors()) {
        if (!conductor || !conductor->isValid()
            || !conductor->terminal1 || !conductor->terminal2) {
            continue;
        }

        const auto first = terminal_indices.find(conductor->terminal1);
        const auto second = terminal_indices.find(conductor->terminal2);
        if (first == terminal_indices.end() || second == terminal_indices.end()) {
            continue;
        }

        const auto connectionResult = model.connect(
            references[first->second], references[second->second]);
        if (connectionResult != ConnectionError::None
            && connectionResult != ConnectionError::DuplicateConnection) {
            continue;
        }

        connected[first->second] = true;
        connected[second->second] = true;

        const std::size_t firstRoot = findRoot(first->second);
        const std::size_t secondRoot = findRoot(second->second);
        if (firstRoot != secondRoot) {
            parent[secondRoot] = firstRoot;
        }
    }

    std::map<std::size_t, std::vector<TerminalRef>> connectedGroups;
    for (std::size_t index = 0; index < references.size(); ++index) {
        // A terminal belongs to a generated net only if at least one
        // explicit conductor touches its connected component.
        if (connected[index]) {
            connectedGroups[findRoot(index)].push_back(references[index]);
        }
    }

    for (auto &entry : connectedGroups) {
        auto &members = entry.second;
        std::sort(members.begin(), members.end());
        if (members.size() < 2) {
            continue;
        }

        const std::string netId = "NET-" + members.front().component_id
            + "-" + members.front().terminal_id;
        if (!model.createNet(netId)) {
            continue;
        }
        for (const TerminalRef &member : members) {
            model.assignTerminalToNet(member, netId);
        }
    }

    return model;
}

} // namespace electrocad
