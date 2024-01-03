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

#include <QDate>
#include <QDateEdit>

class gTableWidgetRow;

class gTableWidgetDate : public gTableWidgetBase, public QDateEdit {

  public:
    gTableWidgetDate(gTableWidgetRow* parent);

    QString date() const;
    void    setDate(const QString& value);

    static const QString date2str(const QDate& date);
    static const QDate   str2date(const QString& str);

  private slots:
    void slotDateChanged(QDate date);

  private:
    gTableWidgetRow* m_parent;
};

#endif // GTABLEWIDGETDATE_HPP
