/*!
 * =============================================================================
 *
 *   @file: gTableWidgetCell.cpp
 *
 *   @date: December, 2023
 *
 * @author: Gino Francesco Bogo
 *
 * =============================================================================
 */

#include "gTableWidgetCell.hpp"

#include "gTableWidgetRow.hpp"

gTableWidgetCell::gTableWidgetCell(gTableWidgetRow* parent) : gTableWidgetBase(CELL, this) {
    m_parent = parent;
}
