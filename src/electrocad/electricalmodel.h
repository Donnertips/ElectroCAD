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

private:
    std::set<TerminalRef> terminals_;
    std::set<std::pair<TerminalRef, TerminalRef>> connection_keys_;
    std::vector<Connection> connections_;
    std::map<std::string, ElectricalNet> nets_;
    std::map<TerminalRef, std::string> terminal_to_net_;
};

} // namespace electrocad
