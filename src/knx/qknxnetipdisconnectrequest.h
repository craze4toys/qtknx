/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
****************************************************************************/

#ifndef QKNXNETIPDISCONNECTREQUEST_H
#define QKNXNETIPDISCONNECTREQUEST_H

#include <QtKnx/qknxnetipframe.h>
#include <QtKnx/qknxnetiphpai.h>
#include <QtKnx/qknxglobal.h>

QT_BEGIN_NAMESPACE

class Q_KNX_EXPORT QKnxNetIpDisconnectRequest final : public QKnxNetIpFrame
{
public:
    QKnxNetIpDisconnectRequest() = default;
    ~QKnxNetIpDisconnectRequest() override = default;

    QKnxNetIpDisconnectRequest(quint8 channelId, const QKnxNetIpHPAI &controlEndpoint);

    template <typename T>
        static QKnxNetIpDisconnectRequest fromBytes(const T &bytes, quint16 index)
    {
        return QKnxNetIpFrameHelper::fromBytes(bytes, index,
            QKnxNetIp::ServiceType::DisconnectRequest);
    }

    quint8 channelId() const;
    QKnxNetIpHPAI controlEndpoint() const;

    bool isValid() const override;

private:
    QKnxNetIpDisconnectRequest(const QKnxNetIpFrame &other);
};

QT_END_NAMESPACE

#endif
