/*!
 * =============================================================================
 *
 *   @file: gTableWidget.cpp
 *
 *   @date: December, 2023
 *
 * @author: Gino Francesco Bogo
 *
 * =============================================================================
 */

#include "gTableWidget.hpp"

#include "gTableWidgetRows.hpp"

#include <qcontainerfwd.h>
#include <qfont.h>
#include <qforeach.h>
#include <qmenu.h>
#include <qnamespace.h>
#include <qpoint.h>
#include <qstring.h>
#include <qtablewidget.h>
#include <qwidget.h>

#define CONNECT_MENU(index, slot) \
    connect(m_actions.at(index), &QAction::triggered, this, &gTableWidget::slot);

gTableWidget::gTableWidget(QWidget* parent) : QTableWidget(parent) {
    setContextMenuPolicy(Qt::CustomContextMenu);

    m_rows = new gTableWidgetRows(this);

    m_menu = new QMenu(this);

    QFont font = m_menu->font();
    font.setPointSize(12);
    m_menu->setFont(font);

    foreach (const auto& name, m_menu_names) {
        if (name != "---") {
            auto* action = new QAction(name);
            m_actions.append(action);
            m_menu->addAction(action);
        }
        else {
            m_menu->addSeparator();
        }
    }

    int i = 0;
    foreach (const auto& icon, m_menu_icons) {
        m_actions.at(i++)->setIcon(QIcon(icon));
    }

    // clang-format off
    CONNECT_MENU(INSERT   , slotMenu_Insert  );
    CONNECT_MENU(REMOVE   , slotMenu_Remove  );
    CONNECT_MENU(CLEAR    , slotMenu_Clear   );
    CONNECT_MENU(COPY     , slotMenu_Copy    );
    CONNECT_MENU(CUT      , slotMenu_Cut     );
    CONNECT_MENU(PASTE    , slotMenu_Paste   );
    CONNECT_MENU(MOVE_UP  , slotMenu_MoveUp  );
    CONNECT_MENU(MOVE_DOWN, slotMenu_MoveDown);
    // clang-format on
}

gTableWidget::~gTableWidget() {
    delete m_rows;

    foreach (auto* action, m_actions) {
        delete action;
    }

    delete m_menu;
}

void gTableWidget::setupUi() {
    auto N = columnCount();

    m_header_names.clear();
    for (decltype(N) i{0}; i < N; ++i) {
        m_header_names.append(horizontalHeaderItem(i)->text());
    }
}

const QStringList& gTableWidget::headerSizes() {
    auto N = columnCount();

    m_header_sizes.clear();
    for (decltype(N) i{0}; i < N; ++i) {
        m_header_sizes.append(QString::number(columnWidth(i)));
    }

    return m_header_sizes;
}

bool gTableWidget::setHeaderSize(const QString& name, int size) {
    if (size > 0) {
        auto N = m_header_names.count();

        for (decltype(N) i{0}; i < N; ++i) {
            if (name == m_header_names.at(i)) {
                setColumnWidth(i, size);
                return true;
            }
        }
    }

    return false;
}

void gTableWidget::renameMenuNames(const QStringList& names) {
    auto N = names.count();

    if (N == m_actions.count()) {
        for (decltype(N) i{0}; i < N; ++i) {
            m_actions[i]->setText(names.at(i));
        }
    }
}

void gTableWidget::slotCustomContextMenu(const QPoint& pos) {
    showActions(false);

    auto row_count = rowCount();
    auto row_index = currentRow();

    const bool check_1 = row_index != -1;
    const bool check_2 = m_rows->isClipboardEmpty() == false;
    const bool check_3 = row_index > 0;
    const bool check_4 = row_index < (row_count - 1);

    switch (row_count) {
        case 0: {
            m_actions.at(INSERT)->setVisible(true);
        } break;

        case 1: {
            // clang-format off
            m_actions.at(INSERT)->setVisible(true);
            m_actions.at(REMOVE)->setVisible(check_1);
            m_actions.at(COPY  )->setVisible(check_1);
            m_actions.at(CUT   )->setVisible(check_1);
            m_actions.at(PASTE )->setVisible(check_1 && check_2);
            // clang-format on
        } break;

        default: {
            // clang-format off
            m_actions.at(INSERT   )->setVisible(true);
            m_actions.at(REMOVE   )->setVisible(true);
            m_actions.at(CLEAR    )->setVisible(true);
            m_actions.at(COPY     )->setVisible(check_1);
            m_actions.at(CUT      )->setVisible(check_1);
            m_actions.at(PASTE    )->setVisible(check_1 && check_2);
            m_actions.at(MOVE_UP  )->setVisible(check_1 && check_3);
            m_actions.at(MOVE_DOWN)->setVisible(check_1 && check_4);
            // clang-format on
        } break;
    }

    m_menu->popup(viewport()->mapToGlobal(pos));
}

void gTableWidget::slotMenu_Insert() {
    auto row_index = currentRow();
    m_rows->insertRow(row_index + 1);
}

void gTableWidget::slotMenu_Remove() {
    auto row_index = currentRow();
    m_rows->removeRow(row_index);
}

void gTableWidget::slotMenu_Clear() {
    m_rows->clearAll();
}

void gTableWidget::slotMenu_Copy() {
    auto row_index = currentRow();
    m_rows->copyRow(row_index);
}

void gTableWidget::slotMenu_Cut() {
    auto row_index = currentRow();
    m_rows->cutRow(row_index);
}

void gTableWidget::slotMenu_Paste() {
    auto row_index = currentRow();
    m_rows->pasteRow(row_index + 1);
}

void gTableWidget::slotMenu_MoveUp() {
    auto row_index = currentRow();
    m_rows->moveUpRow(row_index);
}

void gTableWidget::slotMenu_MoveDown() {
    auto row_index = currentRow();
    m_rows->moveDownRow(row_index);
}
