/******************************************************************************
**
** Copyright (C) 2018 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtKnx module.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
******************************************************************************/

#ifndef QKNXNETIPROUTER_P_H
#define QKNXNETIPROUTER_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt KNX API.  It exists for the convenience
// of the Qt KNX implementation.  This header file may change from version
// to version without notice, or even be removed.
//
// We mean it.
//

#include <QtCore/qtimer.h>
#include <QtCore/private/qobject_p.h>

#include <QtKnx/qknxnetip.h>
#include <QtKnx/qknxnetipframe.h>
#include <QtKnx/qknxnetiprouter.h>

#include <QtNetwork/qnetworkdatagram.h>
#include <QtNetwork/qnetworkinterface.h>
#include <QtNetwork/qudpsocket.h>

QT_BEGIN_NAMESPACE

class QKnxNetIpRouterPrivate : public QObjectPrivate
{
    Q_DECLARE_PUBLIC(QKnxNetIpRouter)
public:
    QKnxNetIpRouterPrivate() = default;
    ~QKnxNetIpRouterPrivate() = default;

    void start();
    void restart();
    void stop();

    void cleanup();

    void processRoutingIndication(const QKnxNetIpFrame &frame);
    void processRoutingBusy(const QKnxNetIpFrame &frame);
    void processRoutingLostMessage(const QKnxNetIpFrame &frame);
    void processRoutingSystemBroadcast(const QKnxNetIpFrame &frame);

    bool sendFrame(const QKnxNetIpFrame &frame);

    void flowControlHandling(quint16 newBusyWaitTime);

    void changeState(QKnxNetIpRouter::State state);
    void errorOccurred(QKnxNetIpRouter::Error error, const QString &errorString);

    QKnxNetIpRouter::FilterAction filterAction(const QKnxLinkLayerFrame &frame);

    QUdpSocket *m_socket { nullptr };

    QKnxAddress m_individualAddress;

    quint16 m_framesReadCount;
    QKnxAddress m_lastIndicationAddress;
    quint16 m_sameKnxDstAddressIndicationCount;

    QNetworkInterface m_iface;
    QHostAddress m_multicastAddress { QLatin1String(QKnxNetIp::Constants::MulticastAddress) };
    quint16 m_multicastPort { QKnxNetIp::Constants::DefaultPort };
    QHostAddress m_ownAddress;

    QKnxNetIpRouter::State m_state { QKnxNetIpRouter::State::NotInit };

    quint16 m_busyWaitTime { QKnxNetIp::RoutingBusyWaitTime };
    QTimer *m_busyTimer { nullptr };

    enum class BusyTimerStage : quint8
    {
        NotInit,
        Wait,
        RandomWait,
        SlowDuration,
        DecrementBusyCounter
    };
    BusyTimerStage m_busyStage { BusyTimerStage::NotInit };
    quint32 m_busyCounter { 0 };

    QKnxNetIpRouter::Error m_error { QKnxNetIpRouter::Error::None };
    QString m_errorMessage;

    QKnxNetIpRouter::KnxAddressWhitelist m_filterTable;
    QKnxNetIpRouter::RoutingMode m_routingMode { QKnxNetIpRouter::RoutingMode::Block };
};

QT_END_NAMESPACE

#endif
