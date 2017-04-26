/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
****************************************************************************/

#include "qknxnetiphpai.h"
#include "qknxutils.h"

QT_BEGIN_NAMESPACE

/*!
    \class QKnxNetIpHPAI

    \inmodule QtKnx
    \brief The QKnxNetIpHPAI class represents the structure containing the
    information that is necessary to uniquely identify an Internet Protocol
    transport connection endpoint. It includes the Network Layer address and
    the Transport Layer identifier called Port number.
*/

QKnxNetIpHPAI::QKnxNetIpHPAI(const QKnxNetIpStruct &other)
    : QKnxNetIpStruct(other)
{}

QKnxNetIpHPAI::QKnxNetIpHPAI(const QHostAddress &address, quint16 port)
    : QKnxNetIpHPAI(QKnxNetIpHPAI::HostProtocolCode::IpV4_Udp, address, port)
{}

QKnxNetIpHPAI::QKnxNetIpHPAI(QKnxNetIpHPAI::HostProtocolCode hpc, const QHostAddress &address,
        quint16 port)
    : QKnxNetIpStruct(quint8(hpc))
{
    QKnxNetIpPayload payload;
    payload.setBytes(QKnxUtils::HostAddress::bytes(address
        .isNull() ? QHostAddress::LocalHost : address));
    payload.appendBytes(QKnxUtils::QUint16::bytes(port));
    setPayload(payload);
}

QKnxNetIpHPAI::HostProtocolCode QKnxNetIpHPAI::hostProtocolCode() const
{
    return HostProtocolCode(code());
}

void QKnxNetIpHPAI::setHostProtocolCode(QKnxNetIpHPAI::HostProtocolCode code)
{
    setCode(quint8(code));
}

QHostAddress QKnxNetIpHPAI::address() const
{
    return QKnxUtils::HostAddress::fromBytes(payloadRef());
}

quint16 QKnxNetIpHPAI::port() const
{
    return QKnxUtils::QUint16::fromBytes(payloadRef(), 4);
}

bool QKnxNetIpHPAI::isValid() const
{
    bool validHostProtocolCode = hostProtocolCode() == HostProtocolCode::IpV4_Udp
        || hostProtocolCode() == HostProtocolCode::IpV4_Tcp;
    return QKnxNetIpStruct::isValid() && size() == 8 && validHostProtocolCode;
}

QT_END_NAMESPACE
