/*!
 * =============================================================================
 *
 *   @file: gXmlPair.hpp
 *
 *   @date: December, 2023
 *
 * @author: Gino Francesco Bogo
 *
 * =============================================================================
 */

#ifndef GXMLPAIR_HPP
#define GXMLPAIR_HPP

#include <QByteArray>
#include <QList>
#include <QPair>
#include <QString>

class gXmlPair;

typedef QList<gXmlPair> gXmlPairs;

class gXmlPair : public QPair<QString, QString> {
  public:
    gXmlPair(const QString& name, const QString& value);

    inline QString& name() { return this->first; }
    inline QString& value() { return this->second; }

    inline void name(const QString& data) { this->first = data; }
    inline void value(const QString& data) { this->second = data; }

    static QString    byte2str(const QByteArray& data) { return QString::fromUtf8(data.toHex()); }
    static QByteArray str2byte(const QString& data) { return QByteArray::fromHex(data.toUtf8()); }

    static QString str2hex(const QString& data) { return QString(data.toUtf8().toHex()); }
    static QString hex2str(const QString& data) { return QString(QByteArray::fromHex(data.toUtf8())); }
};

#endif // GXMLPAIR_HPP
