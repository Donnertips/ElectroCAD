/* SPDX-License-Identifier: GPL-2.0-or-later */
#include "electricalmodel.h"

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

} // namespace electrocad
