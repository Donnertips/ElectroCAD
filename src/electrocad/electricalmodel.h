/* SPDX-License-Identifier: GPL-2.0-or-later */
#pragma once

#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>

namespace electrocad {

struct TerminalRef {
    std::string component_id;
    std::string terminal_id;

    bool operator<(const TerminalRef &other) const noexcept;
    bool operator==(const TerminalRef &other) const noexcept;
};

struct Connection {
    TerminalRef from;
    TerminalRef to;
};

enum class ConnectionError {
    None,
    EmptyIdentifier,
    UnknownTerminal,
    SelfConnection,
    DuplicateConnection
};

// A net is an electrical node/network. Three or more assigned terminals
// represent a branch without implying any device's internal continuity.
struct ElectricalNet {
    std::string id;
    std::vector<TerminalRef> terminals;

    bool operator==(const ElectricalNet &other) const
    {
        return id == other.id && terminals == other.terminals;
    }
};

enum class NetError {
    None,
    EmptyIdentifier,
    DuplicateNet,
    UnknownNet,
    UnknownTerminal,
    TerminalAlreadyAssigned,
    TerminalNotAssigned
};

// Structural difference between two topology snapshots. Connections are
// reported with their endpoints in canonical (sorted) order.
struct ModelChange {
    std::vector<TerminalRef> added_terminals;
    std::vector<TerminalRef> removed_terminals;
    std::vector<Connection> added_connections;
    std::vector<Connection> removed_connections;

    bool empty() const noexcept
    {
        return added_terminals.empty() && removed_terminals.empty()
            && added_connections.empty() && removed_connections.empty();
    }
};

class ElectricalModel final {
public:
    bool registerTerminal(const TerminalRef &terminal);
    ConnectionError connect(const TerminalRef &from, const TerminalRef &to);
    bool hasTerminal(const TerminalRef &terminal) const;
    const std::vector<Connection> &connections() const noexcept;

    bool createNet(const std::string &net_id);
    NetError assignTerminalToNet(const TerminalRef &terminal, const std::string &net_id);
    NetError removeTerminalFromNet(const TerminalRef &terminal);
    const ElectricalNet *net(const std::string &net_id) const noexcept;
    const ElectricalNet *netForTerminal(const TerminalRef &terminal) const noexcept;
    const std::map<std::string, ElectricalNet> &nets() const noexcept;

    // Two models are equal when they hold the same terminals, the same
    // connections (regardless of direction or insertion order) and the same
    // nets with the same members.
    bool operator==(const ElectricalModel &other) const;
    bool operator!=(const ElectricalModel &other) const { return !(*this == other); }

    // Terminals and connections present in this model but not in
    // `previous` (added) and the other way round (removed).
    ModelChange diff(const ElectricalModel &previous) const;

private:
    std::set<TerminalRef> terminals_;
    std::set<std::pair<TerminalRef, TerminalRef>> connection_keys_;
    std::vector<Connection> connections_;
    std::map<std::string, ElectricalNet> nets_;
    std::map<TerminalRef, std::string> terminal_to_net_;
};

} // namespace electrocad
