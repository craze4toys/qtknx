/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
****************************************************************************/

#ifndef QKNXNETIPSTRUCTHEADER_H
#define QKNXNETIPSTRUCTHEADER_H

#include <QtCore/qbytearray.h>
#include <QtCore/qdatastream.h>
#include <QtCore/qdebug.h>
#include <QtCore/qstring.h>
#include <QtCore/qvector.h>
#include <QtKnx/qknxbytestore.h>
#include <QtKnx/qknxglobal.h>
#include <QtKnx/qknxnetip.h>
#include <QtKnx/qknxtraits.h>
#include <QtKnx/qknxutils.h>

QT_BEGIN_NAMESPACE

template <typename CodeType> class Q_KNX_EXPORT QKnxNetIpStructHeader final : private QKnxByteStore
{
    friend struct QKnxNetIpStructHelper;
    friend struct QKnxNetIpConnectionHeaderFrameHelper;

public:
    QKnxNetIpStructHeader() = default;
    ~QKnxNetIpStructHeader() override = default;

    explicit QKnxNetIpStructHeader(CodeType code)
        : QKnxNetIpStructHeader(code, 0)
    {}

    QKnxNetIpStructHeader(CodeType code, quint16 payloadSize)
    {
        setCode(code);
        setPayloadSize(payloadSize);
    }

    bool isValid() const
    {
        if (size() != 2 && size() != 4)
            return false;
        return QKnxNetIp::isStructType(code());
    }

    quint16 totalSize() const
    {
        if (size() == 2)
            return byte(0);

        if (size() == 4)
            return QKnxUtils::QUint16::fromBytes(bytes(1, 2));
        return 0;
    }

    quint16 payloadSize() const
    {
        return totalSize() - size();
    }

    void setPayloadSize(quint16 payloadSize)
    {
        // 2.1.3 Structures:

        // If the amount of data exceeds 252 octets, the length octet shall be FFh
        // and the next two octets shall contain the length as a 16 bit value. Then
        // the structure data shall start at the fifth octet.

        resize(payloadSize > 0xfc ? 4 : 2, quint8(code()));
        if (payloadSize > 0xfc) {
            setByte(0, 0xff);
            setByte(1, quint8((payloadSize + 4) >> 8));
            setByte(2, quint8(payloadSize + 4));
        } else {
            setByte(0, quint8(payloadSize + 2));
        }
    }

    CodeType code() const
    {
        if (size() == 0)
            return CodeType::Unknown;
        return CodeType(byte(size() - 1));
    }

    void setCode(CodeType code)
    {
        if (size() == 0)
            resize(2, 2);
        setByte(size() - 1, quint8(code));
    }

    QString toString() const override
    {
        return QStringLiteral("Total size { 0x%1 }, Code { 0x%2 }")
            .arg(totalSize(), 2, 16, QLatin1Char('0')).arg(quint8(code()), 2, 16, QLatin1Char('0'));
    }

    using QKnxByteStore::size;
    using QKnxByteStore::byte;
    using QKnxByteStore::bytes;

    template <typename T, std::size_t S = 0>
        static QKnxNetIpStructHeader fromBytes(const T &bytes, quint16 index)
    {
        static_assert(is_type<T, QByteArray, QKnxByteStoreRef, QVector<quint8>, std::deque<quint8>,
            std::vector<quint8>, std::array<quint8, S>>::value, "Type not supported.");

        const qint32 availableSize = bytes.size() - index;
        if (availableSize < 1)
            return {}; // total size missing

        quint16 totalSize = QKnxUtils::QUint8::fromBytes(bytes, index);
        const quint8 headerSize = totalSize == 0xff ? 4 : 2;
        if (availableSize < headerSize)
            return {}; // total size and code missing

        if (headerSize == 4)
            totalSize = QKnxUtils::QUint16::fromBytes(bytes, index + 1);

        auto code = CodeType(QKnxUtils::QUint8::fromBytes(bytes, index + headerSize - 1));
        if (!QKnxNetIp::isStructType(code))
            return {};
        return QKnxNetIpStructHeader(code, totalSize - headerSize);
    }
};

QT_END_NAMESPACE

#endif
