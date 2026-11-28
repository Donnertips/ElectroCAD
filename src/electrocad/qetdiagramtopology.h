/* SPDX-License-Identifier: GPL-2.0-or-later */
#pragma once

#include "electricalmodel.h"

#include <QObject>

#include <cstdint>
#include <functional>

class Diagram;

namespace electrocad {

// Keeps an in-memory ElectroCAD topology snapshot synchronized with the
// native QElectroTech scene. Scene notifications are coalesced so a single
// editing operation does not rebuild the graph for every painted item, and
// the changed callback only fires when the electrical topology actually
// differs from the previous snapshot.
class QetDiagramTopology final : public QObject {
public:
    explicit QetDiagramTopology(Diagram &diagram, QObject *parent = nullptr);

    const ElectricalModel &model() const noexcept { return m_model; }

    // Incremented every time a refresh produced a different topology.
    std::uint64_t revision() const noexcept { return m_revision; }

    // Terminals and connections added/removed by the latest change.
    const ModelChange &lastChange() const noexcept { return m_last_change; }

    void refreshNow();
    void setChangedCallback(std::function<void()> callback);

private:
    void scheduleRefresh();

    Diagram *m_diagram;
    ElectricalModel m_model;
    ModelChange m_last_change;
    std::uint64_t m_revision = 0;
    std::function<void()> m_changed_callback;
    bool m_refresh_pending = false;
};

} // namespace electrocad
