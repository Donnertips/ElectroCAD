/* SPDX-License-Identifier: GPL-2.0-or-later */
#pragma once

#include "electricalmodel.h"

#include <QObject>

#include <functional>

class Diagram;

namespace electrocad {

// Keeps an in-memory ElectroCAD topology snapshot synchronized with the
// native QElectroTech scene. Scene notifications are coalesced so a single
// editing operation does not rebuild the graph for every painted item.
class QetDiagramTopology final : public QObject {
public:
    explicit QetDiagramTopology(Diagram &diagram, QObject *parent = nullptr);

    const ElectricalModel &model() const noexcept { return m_model; }
    void refreshNow();
    void setChangedCallback(std::function<void()> callback);

private:
    void scheduleRefresh();

    Diagram *m_diagram;
    ElectricalModel m_model;
    std::function<void()> m_changed_callback;
    bool m_refresh_pending = false;
};

} // namespace electrocad
