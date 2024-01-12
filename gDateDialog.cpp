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

#include <QRegularExpression>
#include <QStringList>

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

void gDateDialog::slotButton_Cancel() {
    setResult(QDialog::Rejected);
    hide();
}

void gDateDialog::slotButton_Select() {
    setResult(QDialog::Accepted);
    hide();
}
