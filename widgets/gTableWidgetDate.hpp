/*!
 * =============================================================================
 *
 *   @file: gTableWidgetDate.hpp
 *
 *   @date: January, 2024
 *
 * @author: Gino Francesco Bogo
 *
 * =============================================================================
 */

#ifndef GTABLEWIDGETDATE_HPP
#define GTABLEWIDGETDATE_HPP

#include "gTableWidgetBase.hpp"
#include "qtmetamacros.h"

#include <QDate>
#include <QDateEdit>

class gTableWidgetRow;

class gTableWidgetDate : public gTableWidgetBase, public QDateEdit {

  public:
    gTableWidgetDate(gTableWidgetRow* parent);

    [[nodiscard]] QString date() const;
    void                  setDate(const QString& value);
    void                  setTargetDate(const QString& value);

    static QString date2str(const QDate& date);
    static QDate   str2date(const QString& str);

    void wheelEvent(QWheelEvent* e) override {
        if (hasFocus()) {
            QDateEdit::wheelEvent(e);
        }
    }

  private slots:
    void slotDateChanged(QDate date);

  private:
    gTableWidgetRow* m_parent;
    QDate            m_target;
};

#endif // GTABLEWIDGETDATE_HPP
