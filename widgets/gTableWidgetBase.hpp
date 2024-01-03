/*!
 * =============================================================================
 *
 *   @file: gTableWidgetBase.hpp
 *
 *   @date: December, 2023
 *
 * @author: Gino Francesco Bogo
 *
 * =============================================================================
 */

#ifndef GTABLEWIDGETBASE_HPP
#define GTABLEWIDGETBASE_HPP

#include <QFlags>
#include <QList>

class gTableWidgetItem;
class gTableWidgetCell;
class gTableWidgetCBox;
class gTableWidgetDate;
class gTableWidgetIcon;

class gTableWidgetBase {

  public:
    enum base_type {
        ITEM = 0b00000001,
        CELL = 0b10000000,
        CBOX = 0b00000001 | CELL,
        DATE = 0b00000010 | CELL,
        ICON = 0b00000100 | CELL,
    };
    Q_DECLARE_FLAGS(BaseType, base_type);

    typedef QList<BaseType> BaseTypes;

    gTableWidgetBase(BaseType type, void* widget);

    gTableWidgetItem* toItem() { return (gTableWidgetItem*)m_widget; }
    gTableWidgetCell* toCell() { return (gTableWidgetCell*)m_widget; }
    gTableWidgetCBox* toCBox() { return (gTableWidgetCBox*)m_widget; }
    gTableWidgetDate* toDate() { return (gTableWidgetDate*)m_widget; }
    gTableWidgetIcon* toIcon() { return (gTableWidgetIcon*)m_widget; }

    BaseType type() { return m_type; }

  private:
    const BaseType m_type;
    void*          m_widget;
};

#endif // GTABLEWIDGETBASE_HPP
