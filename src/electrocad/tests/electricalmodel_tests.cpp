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
}

int main()
{
    ElectricalModel model;
    const TerminalRef a{"Q1", "1"};
    const TerminalRef b{"Q1", "2"};
    const TerminalRef c{"X1", "1"};
    const TerminalRef d{"X2", "1"};

    require(model.registerTerminal(a), "register first terminal");
    require(model.registerTerminal(b), "register second terminal");
    require(model.registerTerminal(c), "register third terminal");
    require(model.registerTerminal(d), "register fourth terminal");
    require(!model.registerTerminal(a), "reject duplicate terminal");
    require(!model.registerTerminal({"", "1"}), "reject empty component id");

    require(model.connect(a, c) == ConnectionError::None, "connect registered terminals");
    require(model.connections().size() == 1, "store one connection");
    require(model.connect(c, a) == ConnectionError::DuplicateConnection,
            "reject duplicate connection regardless of direction");
    require(model.connect(a, a) == ConnectionError::SelfConnection,
            "reject self connection");
    require(model.connect(a, {"X9", "99"}) == ConnectionError::UnknownTerminal,
            "reject unknown terminal");
    require(model.connect(a, {"", "2"}) == ConnectionError::EmptyIdentifier,
            "reject empty endpoint identifier");
    require(model.connections().size() == 1, "invalid connections do not alter model");

    require(!model.createNet(""), "reject empty net identifier");
    require(model.createNet("N-001"), "create electrical net");
    require(model.createNet("N-002"), "create independent electrical net");
    require(!model.createNet("N-001"), "reject duplicate net identifier");
    require(model.assignTerminalToNet(a, "N-404") == NetError::UnknownNet,
            "reject assignment to unknown net");
    require(model.assignTerminalToNet({"Q9", "1"}, "N-001") == NetError::UnknownTerminal,
            "reject unknown terminal assignment");
    require(model.assignTerminalToNet(a, "N-001") == NetError::None,
            "assign first terminal to net");
    require(model.assignTerminalToNet(b, "N-001") == NetError::None,
            "assign second terminal to net");
    require(model.assignTerminalToNet(c, "N-001") == NetError::None,
            "assign branch terminal to net");
    require(model.assignTerminalToNet(a, "N-001") == NetError::TerminalAlreadyAssigned,
            "reject duplicate assignment");
    require(model.assignTerminalToNet(a, "N-002") == NetError::TerminalAlreadyAssigned,
            "terminal cannot belong to two networks");
    require(model.assignTerminalToNet(d, "N-002") == NetError::None,
            "assign terminal to an independent network");
    require(model.netForTerminal(d) == model.net("N-002"),
            "independent network membership is preserved");

    const auto *net = model.net("N-001");
    require(net != nullptr, "find net by identifier");
    require(net->terminals.size() == 3, "net contains three branch terminals");
    require(model.netForTerminal(b) == net, "resolve net from terminal");
    require(model.net("N-404") == nullptr, "unknown net returns null");
    require(model.netForTerminal(d) == nullptr, "unassigned terminal has no net");

    require(model.removeTerminalFromNet(b) == NetError::None,
            "remove terminal from net");
    require(model.removeTerminalFromNet(b) == NetError::TerminalNotAssigned,
            "reject repeated removal");
    require(model.netForTerminal(b) == nullptr, "removed terminal has no net");
    require(model.net("N-001")->terminals.size() == 2,
            "removal updates net membership");
    require(model.removeTerminalFromNet(d) == NetError::None,
            "remove terminal from independent network");
    require(model.net("N-002")->terminals.empty(),
            "independent network remains after its terminal is removed");

    return EXIT_SUCCESS;
}
