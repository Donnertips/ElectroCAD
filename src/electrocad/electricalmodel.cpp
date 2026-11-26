/* SPDX-License-Identifier: GPL-2.0-or-later */
#include "electricalmodel.h"

#include <algorithm>
#include <utility>

namespace electrocad {

bool TerminalRef::operator<(const TerminalRef &other) const noexcept
{
    if (component_id != other.component_id) {
        return component_id < other.component_id;
    }
    return terminal_id < other.terminal_id;
}

bool TerminalRef::operator==(const TerminalRef &other) const noexcept
{
    return component_id == other.component_id && terminal_id == other.terminal_id;
}

bool ElectricalModel::registerTerminal(const TerminalRef &terminal)
{
    if (terminal.component_id.empty() || terminal.terminal_id.empty()) {
        return false;
    }
    return terminals_.insert(terminal).second;
}

ConnectionError ElectricalModel::connect(const TerminalRef &from, const TerminalRef &to)
{
    if (from.component_id.empty() || from.terminal_id.empty()
        || to.component_id.empty() || to.terminal_id.empty()) {
        return ConnectionError::EmptyIdentifier;
    }
    if (!hasTerminal(from) || !hasTerminal(to)) {
        return ConnectionError::UnknownTerminal;
    }
    if (from == to) {
        return ConnectionError::SelfConnection;
    }

    const auto ordered = (to < from)
        ? std::make_pair(to, from)
        : std::make_pair(from, to);
    if (!connection_keys_.insert(ordered).second) {
        return ConnectionError::DuplicateConnection;
    }

    connections_.push_back({from, to});
    return ConnectionError::None;
}

bool ElectricalModel::hasTerminal(const TerminalRef &terminal) const
{
    return terminals_.find(terminal) != terminals_.end();
}

const std::vector<Connection> &ElectricalModel::connections() const noexcept
{
    return connections_;
}

bool ElectricalModel::createNet(const std::string &net_id)
{
    if (net_id.empty()) {
        return false;
    }
    return nets_.emplace(net_id, ElectricalNet{net_id, {}}).second;
}

NetError ElectricalModel::assignTerminalToNet(
    const TerminalRef &terminal, const std::string &net_id)
{
    if (terminal.component_id.empty() || terminal.terminal_id.empty() || net_id.empty()) {
        return NetError::EmptyIdentifier;
    }
    const auto net_it = nets_.find(net_id);
    if (net_it == nets_.end()) {
        return NetError::UnknownNet;
    }
    if (!hasTerminal(terminal)) {
        return NetError::UnknownTerminal;
    }
    if (terminal_to_net_.find(terminal) != terminal_to_net_.end()) {
        return NetError::TerminalAlreadyAssigned;
    }

    net_it->second.terminals.push_back(terminal);
    terminal_to_net_.emplace(terminal, net_id);
    return NetError::None;
}

NetError ElectricalModel::removeTerminalFromNet(const TerminalRef &terminal)
{
    if (terminal.component_id.empty() || terminal.terminal_id.empty()) {
        return NetError::EmptyIdentifier;
    }
    if (!hasTerminal(terminal)) {
        return NetError::UnknownTerminal;
    }
    const auto assignment = terminal_to_net_.find(terminal);
    if (assignment == terminal_to_net_.end()) {
        return NetError::TerminalNotAssigned;
    }

    auto net_it = nets_.find(assignment->second);
    if (net_it != nets_.end()) {
        auto &members = net_it->second.terminals;
        members.erase(std::remove(members.begin(), members.end(), terminal), members.end());
    }
    terminal_to_net_.erase(assignment);
    return NetError::None;
}

const ElectricalNet *ElectricalModel::net(const std::string &net_id) const noexcept
{
    const auto it = nets_.find(net_id);
    return it == nets_.end() ? nullptr : &it->second;
}

const ElectricalNet *ElectricalModel::netForTerminal(const TerminalRef &terminal) const noexcept
{
    const auto assignment = terminal_to_net_.find(terminal);
    return assignment == terminal_to_net_.end() ? nullptr : net(assignment->second);
}

const std::map<std::string, ElectricalNet> &ElectricalModel::nets() const noexcept
{
    return nets_;
}

} // namespace electrocad
