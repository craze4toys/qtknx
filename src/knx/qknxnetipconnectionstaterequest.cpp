/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
****************************************************************************/

#include "qknxnetipconnectionstaterequest.h"

QT_BEGIN_NAMESPACE

QKnxNetIpConnectionStateRequest::QKnxNetIpConnectionStateRequest(quint8 channelId,
        const QKnxNetIpHPAI &controlEndpoint)
    : QKnxNetIpFrame(quint16(QKnxNetIp::ServiceType::ConnectionStateRequest))
{
    QKnxNetIpPayload payload(channelId);
    payload.setByte(1, 0x00); // reserved
    payload.appendBytes(controlEndpoint.bytes());
    setPayload(payload);
}

quint8 QKnxNetIpConnectionStateRequest::channelId() const
{
    return payloadRef().byte(0);
}

QKnxNetIpHPAI QKnxNetIpConnectionStateRequest::controlEndpoint() const
{
    return QKnxNetIpHPAI::fromBytes(payloadRef(), 1);
}

bool QKnxNetIpConnectionStateRequest::isValid() const
{
    return QKnxNetIpFrame::isValid() && size() == 16;
}

QT_END_NAMESPACE