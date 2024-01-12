/*!
 * =============================================================================
 *
 *   @file: gTableWidget.hpp
 *
 *   @date: December, 2023
 *
 * @author: Gino Francesco Bogo
 *
 * =============================================================================
 */

#ifndef GTABLEWIDGET_HPP
#define GTABLEWIDGET_HPP

#include "gTableWidgetRows.hpp"

#include <QAction>
#include <QList>
#include <QMenu>
#include <QTableWidget>

class gTableWidget : public QTableWidget {
    Q_OBJECT

  public:
    gTableWidget(QWidget* parent);
    ~gTableWidget();

    void setupUi();

    const QStringList& headerNames() {
        return m_header_names;
    }
    const QStringList& headerSizes();

    bool setHeaderSize(const QString& name, int size);

    void renameMenuNames(const QStringList& names);

    gTableWidgetRows* rows() {
        return m_rows;
    }

  private slots:
    void slotCustomContextMenu(const QPoint& pos);

    void slotMenu_Insert();
    void slotMenu_Remove();
    void slotMenu_Clear();
    void slotMenu_Copy();
    void slotMenu_Cut();
    void slotMenu_Paste();
    void slotMenu_MoveUp();
    void slotMenu_MoveDown();

  private:
    void showActions(bool mode) {
        foreach (auto* action, m_actions) {
            action->setVisible(mode);
        }
    }

  private:
    gTableWidgetRows* m_rows;
    QStringList       m_header_names;
    QStringList       m_header_sizes;

    enum MenuIndex {
        INSERT, //
        REMOVE,
        CLEAR,
        COPY,
        CUT,
        PASTE,
        MOVE_UP,
        MOVE_DOWN
    };

    const QStringList m_menu_names = //
        {"Insert",                   //
         "Remove",                   //
         "Clear",                    //
         "---",                      //
         "Copy",                     //
         "Cut",                      //
         "Paste",                    //
         "---",                      //
         "Move Up",                  //
         "Move Down"};               //

    const QStringList m_menu_icons =        //
        {":/res/icons/menu_insert.png",     //
         ":/res/icons/menu_remove.png",     //
         ":/res/icons/menu_clear.png",      //
         ":/res/icons/menu_copy.png",       //
         ":/res/icons/menu_cut.png",        //
         ":/res/icons/menu_paste.png",      //
         ":/res/icons/menu_move_up.png",    //
         ":/res/icons/menu_move_down.png"}; //

    QMenu*          m_menu;
    QList<QAction*> m_actions;
};

#endif // GTABLEWIDGET_HPP
