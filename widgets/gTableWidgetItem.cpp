/*!
 * =============================================================================
 *
 *   @file: gTableWidgetItem.cpp
 *
 *   @date: December, 2023
 *
 * @author: Gino Francesco Bogo
 *
 * =============================================================================
 */

#include "gTableWidgetItem.hpp"

#include "gTableWidgetBase.hpp"
#include "gTableWidgetRow.hpp"

gTableWidgetItem::gTableWidgetItem(gTableWidgetRow* parent) : gTableWidgetBase(ITEM, this) {
    m_parent = parent;

    setText("...");
}
