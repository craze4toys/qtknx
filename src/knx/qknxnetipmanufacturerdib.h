/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
****************************************************************************/

#ifndef QKNXNETIPMANUFACTURERDIB_H
#define QKNXNETIPMANUFACTURERDIB_H

#include <QtCore/qbytearray.h>
#include <QtCore/qdatastream.h>
#include <QtCore/qdebug.h>
#include <QtCore/qstring.h>
#include <QtCore/qvector.h>
#include <QtKnx/qknxglobal.h>
#include <QtKnx/qknxnetipstruct.h>
#include <QtKnx/qknxtraits.h>

QT_BEGIN_NAMESPACE

class Q_KNX_EXPORT QKnxNetIpManufacturerDIB final : public QKnxNetIpStruct
{
public:
    QKnxNetIpManufacturerDIB() = default;
    ~QKnxNetIpManufacturerDIB() override = default;

    explicit QKnxNetIpManufacturerDIB(quint16 manufacturerId);
    QKnxNetIpManufacturerDIB(quint16 manufacturerId, const QByteArray &manufacturerData);
    QKnxNetIpManufacturerDIB(quint16 manufacturerId, const QVector<quint8> &manufacturerData);

    template <typename T> static QKnxNetIpManufacturerDIB fromBytes(const T &bytes, quint16 index)
    {
        return QKnxNetIpStruct::fromBytes(bytes, index);
    }

    QKnxNetIp::DescriptionType descriptionType() const;
    quint16 manufacturerId() const;
    template <typename T> auto manufacturerData() const -> decltype(T())
    {
        static_assert(is_type<T, QByteArray, QVector<quint8>, std::deque<quint8>,
            std::vector<quint8>>::value, "Type not supported.");
        const auto &ref = payloadRef();
        return ref.bytes<T>(2, ref.size() - 2);
    }

    bool isValid() const override;

private:
    QKnxNetIpManufacturerDIB(const QKnxNetIpStruct &other);
};
Q_DECLARE_TYPEINFO(QKnxNetIpManufacturerDIB, Q_MOVABLE_TYPE);

QT_END_NAMESPACE

#endif
