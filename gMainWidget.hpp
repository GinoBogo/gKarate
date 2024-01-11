/*!
 * =============================================================================
 *
 *   @file: gMainWidget.hpp
 *
 *   @date: December, 2023
 *
 * @author: Gino Francesco Bogo
 *
 * =============================================================================
 */

#ifndef GMAINWIDGET_HPP
#define GMAINWIDGET_HPP

#include "gDateDialog.hpp"
#include "gFileDialog.hpp"
#include "gTableWidget.hpp"
#include "xlsxdocument.h"

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
    class gMainWidget;
}
QT_END_NAMESPACE

class gMainWidget : public QWidget {
    Q_OBJECT

  public:
    gMainWidget(QWidget* parent = nullptr);
    ~gMainWidget();

  private slots:
    void slotButton_MatchDate();
    void slotButton_FileNew();
    void slotButton_FileOpen();
    void slotButton_FileSave();
    void slotButton_MakeKata();
    void slotButton_MakeKumite();

    void slotComboBox_ReferenceKata(const QString& text);
    void slotComboBox_ReferenceKumite(const QString& text);

    void slotButton_ReorderKata();
    void slotButton_ReorderKumite();
    void slotButton_ExportKata();
    void slotButton_ExportKumite();

  private:
    void    updateWindowTitle();
    void    updateRowTargetDate();
    QString getDocName() const;
    QString getAppPath() const;
    QString addAppPath(const QString& filename) const;
    void    openConfig(const QString& filename);
    void    saveConfig(const QString& filename);

    void clearTab1_Match();
    void clearTab2_Kata();
    void clearTab3_Kumite();

    void comboBox_ReferencePopulate(QComboBox* comboBox_people_dst, QWidget* tab_number_dst, const QString& filter);

    void comboBox_ReferenceChanged(gTableWidget* tableWidget_people_dst, const QString& reference, const QString& filter);

    void tableWidget_ReorderPeople(gTableWidget* tableWidget_people_dst);

    void tableWidget_ExportRegister(gTableWidget*    tableWidget_people_src,
                                    QXlsx::Document& document,
                                    const QString&   title,
                                    const QString&   practice);

    void tableWidget_ExportEvaluate(gTableWidget*    tableWidget_people_src,
                                    QXlsx::Document& document,
                                    const QString&   title,
                                    const QString&   practice);

  private:
    Ui::gMainWidget* ui;

    gFileDialog* m_openDialog;
    gFileDialog* m_saveDialog;
    gFileDialog* m_saveExport;
    gDateDialog* m_dateDialog;

    QString m_document;
    QString m_directory;
};

#endif // GMAINWIDGET_HPP
