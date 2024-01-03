/*!
 * =============================================================================
 *
 *   @file: gTableWidgetCBox.hpp
 *
 *   @date: December, 2023
 *
 * @author: Gino Francesco Bogo
 *
 * =============================================================================
 */

#ifndef GTABLEWIDGETCBOX_HPP
#define GTABLEWIDGETCBOX_HPP

#include "gTableWidgetBase.hpp"

#include <QComboBox>
#include <QLineEdit>

class gTableWidgetRow;

class gTableWidgetCBox : public gTableWidgetBase, public QComboBox {

  public:
    gTableWidgetCBox(gTableWidgetRow* parent);

    void resize(int items);
    void setupUi();

    QList<QPixmap>&  images() { return m_images; }
    const QLineEdit& lineEdit() { return m_line_edit; }
    const QString    index() { return QString::number(currentIndex()); }
    void             setIndex(const QString& value) { setCurrentIndex(value.toInt()); }

  private:
    gTableWidgetRow* m_parent;
    QList<QPixmap>   m_images;
    QLineEdit        m_line_edit;
};

#endif // GTABLEWIDGETCBOX_HPP
