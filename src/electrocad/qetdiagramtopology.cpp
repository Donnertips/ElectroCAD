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

    // The view may be created after the diagram has already been loaded.
    refreshNow();
}

void QetDiagramTopology::refreshNow()
{
    if (!m_diagram) {
        m_model = ElectricalModel{};
        return;
    }

    m_model = QetDiagramAdapter::buildModel(*m_diagram);
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
