/*!
 * =============================================================================
 *
 *   @file: gTableWidgetRow.hpp
 *
 *   @date: December, 2023
 *
 * @author: Gino Francesco Bogo
 *
 * =============================================================================
 */

#ifndef GTABLEWIDGETROW_HPP
#define GTABLEWIDGETROW_HPP

#include "gTableWidgetBase.hpp"
#include "gTableWidgetCBox.hpp"
#include "gTableWidgetCell.hpp"
#include "gTableWidgetDate.hpp"
#include "gTableWidgetIcon.hpp"
#include "gTableWidgetItem.hpp"

#include <QStringList>

class gTableWidgetRows;

class gTableWidgetRow : public QList<gTableWidgetBase*> {

  public:
    typedef void (*func_setupRow)(gTableWidgetRow*);

    gTableWidgetRow(gTableWidgetRows* parent, func_setupRow setupRow);
    ~gTableWidgetRow();

    void clearAll();

    QStringList cellData();
    void        setCellData(const QStringList& cellData);

  private:
    gTableWidgetRows* m_parent;
};

#endif // GTABLEWIDGETROW_HPP
