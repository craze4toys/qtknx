/****************************************************************************
**
** Copyright (C) 2019 The Qt Company Ltd.
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
****************************************************************************/

#include "qknxsecureconfiguration.h"
#include "private/qknxcryptographicdata_p.h"

QT_BEGIN_NAMESPACE

/*!
    \since 5.13
    \inmodule QtKnx

    \class QKnxSecureConfiguration
    \ingroup qtknx-general-classes

    \brief The QKnxSecureConfiguration class holds configuration
    options used for the secure session authentication process.

    It holds information such as secure key, user ID and password, device
    authentication code, and so on.

    This class is part of the Qt KNX module and currently available as a
    Technology Preview, and therefore the API and functionality provided
    by the class may be subject to change at any time without prior notice.
*/

/*!
    Constructs a new, empty, invalid secure configuration.

    \sa isNull(), isValid()
*/
QKnxSecureConfiguration::QKnxSecureConfiguration()
    : d(new QKnxSecureConfigurationPrivate)
{}

/*!
    Releases any resources held by the secure configuration.
*/
QKnxSecureConfiguration::~QKnxSecureConfiguration() = default;

/*!
    Returns \c true if this is a default constructed secure configuration;
    otherwise returns \c false. A secure configuration is considered \c null
    if it contains no initialized values.
*/
bool QKnxSecureConfiguration::isNull() const
{
    return d->privateKey.isNull() && d->userId == QKnxNetIp::SecureUserId::Reserved
        && d->userPassword.isNull() && d->deviceAuthenticationCode.isNull();
}

/*!
    Returns \c true if the secure configuration contains initialized values and
    is in itself valid, otherwise returns \c false.

    A valid secure configuration consists of at least a valid user ID,
    a valid \l {QKnxSecureKey} {secure key}, and sensible device authentication
    code.
*/
bool QKnxSecureConfiguration::isValid() const
{
    if (isNull())
        return false;

    return d->privateKey.type() == QKnxSecureKey::Type::Private && d->privateKey.isValid()
        && QKnxNetIp::isSecureUserId(d->userId) && (!d->deviceAuthenticationCode.isEmpty());
}

/*!
    Returns the public \l {QKnxSecureKey} {secure key} used to establish the
    secure session. The public key is derived from the given private key.
*/
QKnxSecureKey QKnxSecureConfiguration::publicKey() const
{
    return d->publicKey;
}

/*!
    Returns the private \l {QKnxSecureKey} {secure key} used to establish the
    secure session.
*/
QKnxSecureKey QKnxSecureConfiguration::privateKey() const
{
    return d->privateKey;
}

/*!
    Set the \l {QKnxSecureKey} {secure key} used to establish the secure
    connection to \a key and returns \c true on success; \c false otherwise.
*/
bool QKnxSecureConfiguration::setPrivateKey(const QKnxSecureKey &key)
{
    auto valid = key.isValid() && key.type() == QKnxSecureKey::Type::Private;
    if (valid) {
        d->privateKey = key;
        d->publicKey = QKnxSecureKey::publicKeyFromPrivate(key);
    }
    return valid;
}

/*!
    Returns the user ID used in the KNXnet/IP session authentication frame.
*/
QKnxNetIp::SecureUserId QKnxSecureConfiguration::userId() const
{
    return d->userId;
}

/*!
    Sets the user ID used in the KNXnet/IP session authentication frame
    to \a userId and returns \c true on success; \c false otherwise.

    \note A userId() with the value \c QKnxNetIp::SecureUserId::Reserved or
    equal to or more than \c QKnxNetIp::SecureUserId::Invalid is considered
    invalid according to the KNX application note AN159.
*/
bool QKnxSecureConfiguration::setUserId(QKnxNetIp::SecureUserId userId)
{
    auto valid = QKnxNetIp::isSecureUserId(userId);
    if (valid)
        d->userId = userId;
    return valid;
}

/*!
    Returns the user password used to authenticate the user while establishing
    the secure session as an array of bytes.
*/
QByteArray QKnxSecureConfiguration::userPassword() const
{
    return d->userPassword;
}

/*!
    Sets the user password to authenticate the user while establishing the
    secure session to \a userPassword. Returns \c true on success; \c false
    otherwise.
*/
void QKnxSecureConfiguration::setUserPassword(const QByteArray &userPassword)
{
    d->userPassword = userPassword;
}

/*!
    Returns the requested individual address for the secure session.
*/
QKnxAddress QKnxSecureConfiguration::individualAddress() const
{
    return d->ia;
}

/*!
    Sets the requested individual address of the secure session to \a address.

    \note To request any of the freely available addresses for the secure
    session, or to reset the requested one, pass an invalid \a address to
    the function.
*/
bool QKnxSecureConfiguration::setIndividualAddress(const QKnxAddress &address)
{
    auto isIa = address.type() == QKnxAddress::Type::Individual;
    if (isIa)
        d->ia = address;
    return isIa;
}

/*!
    Returns the device authentication code to establish the secure session
    as an array of bytes.
*/
QByteArray QKnxSecureConfiguration::deviceAuthenticationCode() const
{
    return d->deviceAuthenticationCode;
}

/*!
    Sets the device authentication code used to establish the secure session
    to \a authenticationCode. Returns \c true on success; \c false otherwise.

    \note The device authentication code cannot be empty.
*/
bool QKnxSecureConfiguration::setDeviceAuthenticationCode(const QByteArray &authenticationCode)
{
    auto valid = !authenticationCode.isEmpty();
    if (valid)
        d->deviceAuthenticationCode = authenticationCode;
    return valid;
}

/*!
    Returns \c true if the keep alive flag is set; \c false otherwise. By
    default this is set to \c false.
*/
bool QKnxSecureConfiguration::isSecureSessionKeepAliveSet() const
{
    return d->keepAlive;
}

/*!
    Determines whether the connection should be kept alive. Set \a keepAlive to
    \c true to keep a secure session alive even if there is no traffic for more
    than \l {KnxNetIp::SecureSessionTimeout} {60 seconds}.
*/
void QKnxSecureConfiguration::setKeepSecureSessionAlive(bool keepAlive)
{
    d->keepAlive = keepAlive;
}

/*!
    Constructs a copy of \a other.
*/
QKnxSecureConfiguration::QKnxSecureConfiguration(const QKnxSecureConfiguration &other)
    : d(other.d)
{}

/*!
    Assigns the specified \a other to this secure configuration.
*/
QKnxSecureConfiguration &QKnxSecureConfiguration::operator=(const QKnxSecureConfiguration &other)
{
    d = other.d;
    return *this;
}

/*!
    Move-constructs a secure configuration, making it point to the same secure
    configuration that \a other was pointing to.
*/
QKnxSecureConfiguration::QKnxSecureConfiguration(QKnxSecureConfiguration &&other) Q_DECL_NOTHROW
    : d(other.d)
{
    other.d = nullptr;
}

/*!
    Move-assigns \a other to this secure configuration.
*/
QKnxSecureConfiguration &
    QKnxSecureConfiguration::operator=(QKnxSecureConfiguration &&other) Q_DECL_NOTHROW
{
    swap(other);
    return *this;
}

/*!
    Swaps \a other with this secure configuration. This operation is very fast
    and never fails.
*/
void QKnxSecureConfiguration::swap(QKnxSecureConfiguration &other) Q_DECL_NOTHROW
{
    d.swap(other.d);
}

/*!
    Returns \c true if this secure configuration and the given \a other are
    equal; otherwise returns \c false.
*/
bool QKnxSecureConfiguration::operator==(const QKnxSecureConfiguration &other) const
{
    return d == other.d || (d->privateKey == other.d->privateKey
        && d->userId == other.d->userId
        && d->userPassword == other.d->userPassword
        && d->deviceAuthenticationCode == other.d->deviceAuthenticationCode
        && d->keepAlive == other.d->keepAlive);
}

/*!
    Returns \c true if this secure configuration and the given \a other are not
    equal; otherwise returns \c false.
*/
bool QKnxSecureConfiguration::operator!=(const QKnxSecureConfiguration &other) const
{
    return !operator==(other);
}

QT_END_NAMESPACE