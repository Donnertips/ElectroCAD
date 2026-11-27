/* SPDX-License-Identifier: GPL-2.0-or-later */
#pragma once

#include "electricalmodel.h"

class Diagram;

namespace electrocad {

// Builds a read-only electrical topology snapshot from QElectroTech's native
// diagram objects. Only explicit conductor endpoints are treated as
// electrically connected; device-internal continuity is deliberately not
// inferred here.
class QetDiagramAdapter final {
public:
    static ElectricalModel buildModel(const Diagram &diagram);
};

} // namespace electrocad
