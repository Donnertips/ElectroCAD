/* SPDX-License-Identifier: GPL-2.0-or-later */
#include "qetdiagramtopology.h"

#include "diagram.h"
#include "qetdiagramadapter.h"

#include <QGraphicsScene>
#include <QTimer>

#include <utility>

namespace electrocad {

QetDiagramTopology::QetDiagramTopology(Diagram &diagram, QObject *parent) :
    QObject(parent),
    m_diagram(&diagram)
{
    connect(&diagram, &QGraphicsScene::changed, this,
            [this](const QList<QRectF> &) { scheduleRefresh(); });
    connect(&diagram, &QObject::destroyed, this, [this]() {
        m_diagram = nullptr;
    });

    // The view may be created after the diagram has already been loaded.
    refreshNow();
}

void QetDiagramTopology::refreshNow()
{
    ElectricalModel next = m_diagram
        ? QetDiagramAdapter::buildModel(*m_diagram)
        : ElectricalModel{};

    // Scene updates that do not alter the electrical topology (moving a
    // symbol, repainting, text edits) must not notify listeners.
    if (next == m_model) {
        return;
    }

    m_last_change = next.diff(m_model);
    m_model = std::move(next);
    ++m_revision;

    if (m_changed_callback) {
        m_changed_callback();
    }
}

void QetDiagramTopology::setChangedCallback(std::function<void()> callback)
{
    m_changed_callback = std::move(callback);
}

void QetDiagramTopology::scheduleRefresh()
{
    if (m_refresh_pending) {
        return;
    }

    m_refresh_pending = true;
    QTimer::singleShot(0, this, [this]() {
        m_refresh_pending = false;
        refreshNow();
    });
}

} // namespace electrocad
