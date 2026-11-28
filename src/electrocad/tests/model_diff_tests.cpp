/* SPDX-License-Identifier: GPL-2.0-or-later */
#include "electricalmodel.h"

#include <cstdlib>
#include <iostream>

using electrocad::ConnectionError;
using electrocad::ElectricalModel;
using electrocad::NetError;
using electrocad::TerminalRef;

namespace {
void require(bool condition, const char *message)
{
    if (!condition) {
        std::cerr << "FAIL: " << message << '\n';
        std::exit(EXIT_FAILURE);
    }
}

ElectricalModel baseModel()
{
    ElectricalModel model;
    model.registerTerminal({"Q1", "1"});
    model.registerTerminal({"Q1", "2"});
    model.registerTerminal({"X1", "1"});
    model.connect({"Q1", "1"}, {"X1", "1"});
    return model;
}
}

int main()
{
    const TerminalRef q1_1{"Q1", "1"};
    const TerminalRef q1_2{"Q1", "2"};
    const TerminalRef x1_1{"X1", "1"};
    const TerminalRef x2_1{"X2", "1"};

    // Identical content compares equal and produces an empty change set.
    const ElectricalModel first = baseModel();
    const ElectricalModel second = baseModel();
    require(first == second, "identically built models are equal");
    require(!(first != second), "identical models are not different");
    require(first.diff(second).empty(), "identical models have an empty diff");

    // Connection direction and insertion order do not affect equality.
    ElectricalModel reversed;
    reversed.registerTerminal(x1_1);
    reversed.registerTerminal(q1_2);
    reversed.registerTerminal(q1_1);
    require(reversed.connect(x1_1, q1_1) == ConnectionError::None,
            "connect in reverse direction");
    require(first == reversed, "direction and registration order do not matter");

    // Adding a terminal and a connection is reported as an addition.
    ElectricalModel grown = baseModel();
    require(grown.registerTerminal(x2_1), "register extra terminal");
    require(grown.connect(q1_2, x2_1) == ConnectionError::None,
            "connect extra terminal");
    require(grown != first, "added terminal and connection make models differ");

    const auto added = grown.diff(first);
    require(!added.empty(), "growth produces a non-empty diff");
    require(added.added_terminals.size() == 1, "one terminal added");
    require(added.added_terminals.front() == x2_1, "added terminal is X2:1");
    require(added.removed_terminals.empty(), "no terminal removed on growth");
    require(added.added_connections.size() == 1, "one connection added");
    require(added.removed_connections.empty(), "no connection removed on growth");

    // The reverse direction reports the same items as removals.
    const auto removed = first.diff(grown);
    require(removed.removed_terminals.size() == 1, "one terminal removed");
    require(removed.removed_terminals.front() == x2_1, "removed terminal is X2:1");
    require(removed.added_terminals.empty(), "no terminal added on shrink");
    require(removed.removed_connections.size() == 1, "one connection removed");
    require(removed.added_connections.empty(), "no connection added on shrink");

    // Removing only a connection leaves the terminals untouched.
    ElectricalModel without_connection;
    without_connection.registerTerminal(q1_1);
    without_connection.registerTerminal(q1_2);
    without_connection.registerTerminal(x1_1);
    const auto dropped = without_connection.diff(first);
    require(dropped.added_terminals.empty() && dropped.removed_terminals.empty(),
            "terminals unchanged when only a connection is removed");
    require(dropped.removed_connections.size() == 1, "connection removal detected");

    // Net membership alone changes equality even if terminals and
    // connections are the same.
    ElectricalModel with_net = baseModel();
    require(with_net.createNet("N-001"), "create net");
    require(with_net.assignTerminalToNet(q1_1, "N-001") == NetError::None,
            "assign first terminal");
    require(with_net != first, "net membership makes models differ");
    require(with_net.diff(first).empty(),
            "net-only change has no terminal or connection delta");

    ElectricalModel same_net = baseModel();
    same_net.createNet("N-001");
    same_net.assignTerminalToNet(q1_1, "N-001");
    require(with_net == same_net, "models with identical nets are equal");

    return EXIT_SUCCESS;
}
