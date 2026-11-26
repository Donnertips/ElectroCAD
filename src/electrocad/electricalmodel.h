/* SPDX-License-Identifier: GPL-2.0-or-later */
#pragma once

#include <set>
#include <string>
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

class ElectricalModel final {
public:
    bool registerTerminal(const TerminalRef &terminal);
    ConnectionError connect(const TerminalRef &from, const TerminalRef &to);
    bool hasTerminal(const TerminalRef &terminal) const;
    const std::vector<Connection> &connections() const noexcept;

private:
    std::set<TerminalRef> terminals_;
    std::set<std::pair<TerminalRef, TerminalRef>> connection_keys_;
    std::vector<Connection> connections_;
};

} // namespace electrocad
