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
#include "libs/gFileDialog.hpp"
#include "qxlsx/xlsxdocument.h"
#include "widgets/gTableWidget.hpp"

#include <qwidget.h>

QT_BEGIN_NAMESPACE
namespace Ui {
    class gMainWidget;
} // namespace Ui
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
    void slotButton_CreateKata();
    void slotButton_CreateKumite();

    void slotComboBox_ReferenceKata(const QString& text);
    void slotComboBox_ReferenceKumite(const QString& text);

    void slotButton_ReorderKata();
    void slotButton_ReorderKumite();
    void slotButton_ExportKata();
    void slotButton_ExportKumite();

  private:
    void                         updateWindowTitle();
    void                         updateRowTargetDate();
    [[nodiscard]] QString        getDocName() const;
    [[nodiscard]] static QString getAppPath();
    [[nodiscard]] static QString addAppPath(const QString& filename);
    void                         openConfig(const QString& filename);
    void                         saveConfig(const QString& filename);

    void clearTab1_Match();
    void clearTab2_Kata();
    void clearTab3_Kumite();

    void comboBox_ReferencePopulate(QComboBox*     comboBox_AthletesDst, //
                                    QWidget*       tab_number_dst,
                                    const QString& filter);

    void comboBox_ReferenceChanged(gTableWidget*  tableWidget_AthletesDst, //
                                   const QString& reference,
                                   const QString& filter);

    static void tableWidget_ReorderPeople(gTableWidget* tableWidget_AthletesDst);

    static void tableWidget_ExportRegister(gTableWidget*    tableWidget_AthletesSrc,
                                           QXlsx::Document& document,
                                           const QString&   title,
                                           const QString&   practice);

    static void tableWidget_ExportEvaluate(gTableWidget*    tableWidget_AthletesSrc,
                                           QXlsx::Document& document,
                                           const QString&   title,
                                           const QString&   practice);

  private:
    Ui::gMainWidget* ui;

    gFileDialog* m_openDialog;
    gFileDialog* m_saveDialog;
    gFileDialog* m_saveExport;
    gDateDialog* m_dateDialog;

    const QString m_untitled = tr("untitled");
    QString       m_document;
    QString       m_directory;
};

#endif // GMAINWIDGET_HPP
