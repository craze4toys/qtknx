/******************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtKnx module.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
******************************************************************************/

#include "qknxnetipserverdiscoveryinfo.h"
#include "qknxnetipserverdiscoveryinfo_p.h"

QT_BEGIN_NAMESPACE

QKnxNetIpServerDiscoveryInfo::QKnxNetIpServerDiscoveryInfo()
    : d_ptr(new QKnxNetIpServerDiscoveryInfoPrivate)
{}

QKnxNetIpServerDiscoveryInfo::~QKnxNetIpServerDiscoveryInfo()
{}

QString QKnxNetIpServerDiscoveryInfo::deviceName() const
{
    return QString::fromUtf8(d_ptr->hardware.deviceName());
}

QKnxAddress QKnxNetIpServerDiscoveryInfo::individualAddress() const
{
    return d_ptr->hardware.individualAddress();
}

quint16 QKnxNetIpServerDiscoveryInfo::controlEndpointPort() const
{
    return d_ptr->hpai.port();
}

QHostAddress QKnxNetIpServerDiscoveryInfo::controlEndpointAddress() const
{
    return d_ptr->hpai.address();
}

QKnxNetIpServiceFamiliesDIB::ServiceFamilyIdVersions QKnxNetIpServerDiscoveryInfo::supportedServices() const
{
    return d_ptr->services.serviceFamilyIdVersions();
}

QKnxNetIpHPAI QKnxNetIpServerDiscoveryInfo::endpoint() const
{
    return d_ptr->hpai;
}

QKnxNetIpDeviceDIB QKnxNetIpServerDiscoveryInfo::hardware() const
{
    return d_ptr->hardware;
}

QKnxNetIpServiceFamiliesDIB QKnxNetIpServerDiscoveryInfo::services() const
{
    return d_ptr->services;
}

QKnxNetIpServerDiscoveryInfo::QKnxNetIpServerDiscoveryInfo(const QKnxNetIpServerDiscoveryInfo &o)
    : d_ptr(o.d_ptr)
{}

QKnxNetIpServerDiscoveryInfo &
QKnxNetIpServerDiscoveryInfo::operator=(const QKnxNetIpServerDiscoveryInfo &other)
{
    QKnxNetIpServerDiscoveryInfo(other).swap(*this);
    return *this;

}

QKnxNetIpServerDiscoveryInfo::QKnxNetIpServerDiscoveryInfo(const QKnxNetIpHPAI &hpai,
    const QKnxNetIpDeviceDIB &hardware, QKnxNetIpServiceFamiliesDIB services)
    : QKnxNetIpServerDiscoveryInfo()
{
    d_ptr->hpai = hpai;
    d_ptr->hardware = hardware;
    d_ptr->services = services;
}

QKnxNetIpServerDiscoveryInfo::QKnxNetIpServerDiscoveryInfo(QKnxNetIpServerDiscoveryInfoPrivate &dd)
    : d_ptr(new QKnxNetIpServerDiscoveryInfoPrivate(dd))
{}

void QKnxNetIpServerDiscoveryInfo::swap(QKnxNetIpServerDiscoveryInfo other)
{
    d_ptr.swap(other.d_ptr);
}

QT_END_NAMESPACE