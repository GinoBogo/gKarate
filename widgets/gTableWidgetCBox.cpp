/*!
 * =============================================================================
 *
 *   @file: gTableWidgetCBox.cpp
 *
 *   @date: December, 2023
 *
 * @author: Gino Francesco Bogo
 *
 * =============================================================================
 */

#include "gTableWidgetCBox.hpp"

#include "gTableWidgetBase.hpp"
#include "gTableWidgetRow.hpp"

#include <qnamespace.h>

gTableWidgetCBox::gTableWidgetCBox(gTableWidgetRow* parent) : gTableWidgetBase(CBOX, this) {
    m_parent = parent;

    m_line_edit.setReadOnly(true);
    m_line_edit.setAlignment(Qt::AlignCenter);

    setLineEdit(&m_line_edit);
    setFocusPolicy(Qt::StrongFocus);
    setContextMenuPolicy(Qt::NoContextMenu);
}

void gTableWidgetCBox::resize(int items) {
    if (items < 0) {
        clear();
        return;
    }

    auto N = count();

    if (N < items) {
        while (N < items) {
            insertItem(N++, "");
        }
    }

    if (N > items) {
        while (N > items) {
            removeItem(--N);
        }
    }
}

void gTableWidgetCBox::setupUi() {
    auto N = count();

    for (decltype(N) i{0}; i < N; ++i) {
        setItemData(i, m_images.at(i), Qt::DecorationRole);
        setItemData(i, Qt::AlignCenter, Qt::TextAlignmentRole);
    }
}
