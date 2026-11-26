/* SPDX-License-Identifier: GPL-2.0-or-later */
#include "electricalmodel.h"

#include <cstdlib>
#include <iostream>

using electrocad::ConnectionError;
using electrocad::ElectricalModel;
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

    require(model.registerTerminal(a), "register first terminal");
    require(model.registerTerminal(b), "register second terminal");
    require(model.registerTerminal(c), "register third terminal");
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

    return EXIT_SUCCESS;
}
