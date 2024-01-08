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
#include "qdatetimeedit.h"

gTableWidgetDate::gTableWidgetDate(gTableWidgetRow* parent) : gTableWidgetBase(DATE, this) {
    m_parent = parent;
    m_target = QDate::currentDate();

    setAlignment(Qt::AlignCenter);
    setButtonSymbols(QAbstractSpinBox::NoButtons);
    setFocusPolicy(Qt::StrongFocus);
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

void gTableWidgetDate::setTargetDate(const QString& value) {
    m_target = str2date(value);
    slotDateChanged(QDateEdit::date());
}

void gTableWidgetDate::slotDateChanged(QDate date) {
    auto stop = m_target;

    if (date.daysTo(stop) < 0) {
        auto temp = stop;
        stop      = date;
        date      = temp;
    }

    auto Y = 0;
    auto M = 0;
    auto D = 0;

    Y = stop.year() - date.year();

    if ((M = stop.month() - date.month()) < 0) {
        Y -= 1;
        M += 12;
    }

    if ((D = stop.day() - date.day()) < 0) {
        if (--M < 0) {
            Y -= 1;
            M += 12;
        }
        D += date.daysInMonth();
    }

    setToolTip(QString("%1Y %2M %3D").arg(Y).arg(M).arg(D));
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
