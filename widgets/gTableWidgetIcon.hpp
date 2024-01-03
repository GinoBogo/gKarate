/*!
 * =============================================================================
 *
 *   @file: gTableWidgetIcon.hpp
 *
 *   @date: January, 2024
 *
 * @author: Gino Francesco Bogo
 *
 * =============================================================================
 */

#ifndef GTABLEWIDGETICON_HPP
#define GTABLEWIDGETICON_HPP

#include "gTableWidgetBase.hpp"

#include <QLabel>
#include <QPixmap>

class gTableWidgetRow;

class gTableWidgetIcon : public gTableWidgetBase, public QLabel {

  public:
    gTableWidgetIcon(gTableWidgetRow* parent);

    QList<QPixmap>& images() { return m_images; }
    QString         index() const { return QString::number(m_index); }
    void            setIndex(const QString& data);

  private:
    gTableWidgetRow* m_parent;
    QList<QPixmap>   m_images;
    int              m_index;
};

#endif // GTABLEWIDGETICON_HPP
