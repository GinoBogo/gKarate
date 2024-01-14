/*!
 * =============================================================================
 *
 *   @file: gDateDialog.cpp
 *
 *   @date: December, 2023
 *
 * @author: Gino Francesco Bogo
 *
 * =============================================================================
 */

#include "gDateDialog.hpp"

#include "ui_gDateDialog.h"

#include <qchar.h>
#include <qcontainerfwd.h>
#include <qdatetime.h>
#include <qdialog.h>
#include <qnamespace.h>
#include <qregularexpression.h>
#include <qwidget.h>

gDateDialog::gDateDialog(QWidget* parent) : QDialog(parent), ui(new Ui::gDateDialog) {
    ui->setupUi(this);
}

gDateDialog::~gDateDialog() {
    delete ui;
}

void gDateDialog::setDate(const QDate& date) {
    ui->calendarWidget->setSelectedDate(date);
}

const QDate gDateDialog::getDate() {
    return ui->calendarWidget->selectedDate();
}

const QString gDateDialog::date2str(const QDate& date) {
    return QString("%1/%2/%3") //
        .arg(date.day(), 2, 10, QChar('0'))
        .arg(date.month(), 2, 10, QChar('0'))
        .arg(date.year());
}

const QDate gDateDialog::str2date(const QString& str) {
    QDate date;

    static QRegularExpression const re("[/ -.]");

    QStringList const list = str.split(re, Qt::SkipEmptyParts);

    if (list.count() == 3) {
        int const D = list.at(0).toInt();
        int const M = list.at(1).toInt();
        int const Y = list.at(2).toInt();

        date.setDate(Y, M, D);
    }

    return date;
}

void gDateDialog::slotButton_Cancel() {
    setResult(QDialog::Rejected);
    hide();
}

void gDateDialog::slotButton_Select() {
    setResult(QDialog::Accepted);
    hide();
}
