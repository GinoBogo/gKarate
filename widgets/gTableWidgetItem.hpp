/*!
 * =============================================================================
 *
 *   @file: gTableWidgetItem.hpp
 *
 *   @date: December, 2023
 *
 * @author: Gino Francesco Bogo
 *
 * =============================================================================
 */

#ifndef GTABLEWIDGETITEM_HPP
#define GTABLEWIDGETITEM_HPP

#include "gTableWidgetBase.hpp"

#include <QTableWidgetItem>

class gTableWidgetRow;

class gTableWidgetItem : public gTableWidgetBase, public QTableWidgetItem {

  public:
    gTableWidgetItem(gTableWidgetRow* parent);

  private:
    gTableWidgetRow* m_parent;
};

#endif // GTABLEWIDGETITEM_HPP
