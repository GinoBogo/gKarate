/*!
 * =============================================================================
 *
 *   @file: gTableWidgetIcon.cpp
 *
 *   @date: January, 2024
 *
 * @author: Gino Francesco Bogo
 *
 * =============================================================================
 */

#include "gTableWidgetIcon.hpp"

#include "gTableWidgetRow.hpp"

gTableWidgetIcon::gTableWidgetIcon(gTableWidgetRow* parent) : gTableWidgetBase(ICON, this) {
    m_parent = parent;

    setAlignment(Qt::AlignCenter);
}

void gTableWidgetIcon::setIndex(const QString& data) {
    auto index = data.toInt();

    if ((0 <= index) && (index < m_images.count())) {
        setPixmap(m_images.at(index));
        m_index = index;
    }
}
