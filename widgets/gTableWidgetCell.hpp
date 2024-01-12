/*!
 * =============================================================================
 *
 *   @file: gTableWidgetCell.hpp
 *
 *   @date: December, 2023
 *
 * @author: Gino Francesco Bogo
 *
 * =============================================================================
 */

#ifndef GTABLEWIDGETCELL_H
#define GTABLEWIDGETCELL_H

#include "gTableWidgetBase.hpp"

#include <QWidget>

class gTableWidgetRow;

class gTableWidgetCell : public gTableWidgetBase, public QWidget {

  public:
    gTableWidgetCell(gTableWidgetRow* parent);

    QString title() const {
        return windowTitle();
    }
    void setTitle(const QString& title) {
        setWindowTitle(title);
    }

  private:
    gTableWidgetRow* m_parent;
};

#endif // GTABLEWIDGETCELL_H
