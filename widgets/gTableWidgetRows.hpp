/*!
 * =============================================================================
 *
 *   @file: gTableWidgetRows.hpp
 *
 *   @date: December, 2023
 *
 * @author: Gino Francesco Bogo
 *
 * =============================================================================
 */

#ifndef GTABLEWIDGETROWS_HPP
#define GTABLEWIDGETROWS_HPP

#include <QList>

#include "gTableWidgetRow.hpp"

class gTableWidget;

class gTableWidgetRows : public QList<gTableWidgetRow*> {

  public:
    gTableWidgetRows(gTableWidget* parent);
    ~gTableWidgetRows();

    void setupRow(gTableWidgetRow::func_setupRow setupRow) { f_setupRow = setupRow; }

    void clearAll();

    bool isClipboardEmpty() { return m_clipboard.count() == 0; }

    void insertRow(int row, gTableWidgetRow* item);
    void insertRow(int row);
    void removeRow(int row);
    void cutRow(int row);
    void copyRow(int row);
    void pasteRow(int row);
    void moveUpRow(int row);
    void moveDownRow(int row);

    QList<QStringList> cellsData();
    void               setCellsData(const QList<QStringList>& list);

    QList<gTableWidgetRow*> filterRows(int col, const QString& data) const;

  private:
    void connectRowToTable(int row);

  private:
    gTableWidget* m_parent;
    QStringList   m_clipboard;

    gTableWidgetRow::func_setupRow f_setupRow;
};

#endif // GTABLEWIDGETROWS_HPP
