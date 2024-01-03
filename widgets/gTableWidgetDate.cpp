/*!
 * =============================================================================
 *
 *   @file: gTableWidgetDate.cpp
 *
 *   @date: January, 2024
 *
 * @author: Gino Francesco Bogo
 *
 * =============================================================================
 */

#include "gTableWidgetDate.hpp"

#include "gTableWidgetBase.hpp"

gTableWidgetDate::gTableWidgetDate(gTableWidgetRow* parent) : gTableWidgetBase(DATE, this) {
    m_parent = parent;

    setAlignment(Qt::AlignCenter);
    setButtonSymbols(QAbstractSpinBox::NoButtons);
    setContextMenuPolicy(Qt::NoContextMenu);

    connect(this, &QDateEdit::dateChanged, this, &gTableWidgetDate::slotDateChanged);
}

QString gTableWidgetDate::date() const {
    auto date = date2str(QDateEdit::date());
    return date;
}

void gTableWidgetDate::setDate(const QString& value) {
    auto date = str2date(value);
    QDateEdit::setDate(date);
}

void gTableWidgetDate::slotDateChanged(QDate date) {
    auto age = QDate::currentDate().year() - date.year();
    setToolTip(QString::number(age));
}

const QString gTableWidgetDate::date2str(const QDate& date) {
    return QString("%1/%2/%3")
        .arg(date.day(), 2, 10, QChar('0'))
        .arg(date.month(), 2, 10, QChar('0'))
        .arg(date.year());
}

const QDate gTableWidgetDate::str2date(const QString& str) {
    QDate date;

    static QRegularExpression re("[/ -.]");

    QStringList list = str.split(re, Qt::SkipEmptyParts);

    if (list.count() == 3) {
        int D = list.at(0).toInt();
        int M = list.at(1).toInt();
        int Y = list.at(2).toInt();

        date.setDate(Y, M, D);
    }

    return date;
}
