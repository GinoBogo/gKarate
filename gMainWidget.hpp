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

#include "libs/gFileDialog.hpp"

#include "gDateDialog.hpp"

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

  private:
    void    updateWindowTitle();
    QString getAppPath() const;
    QString addAppPath(const QString& filename) const;
    void    openConfig(const QString& filename);
    void    saveConfig(const QString& filename);

  private:
    Ui::gMainWidget* ui;

    gFileDialog* m_openDialog;
    gFileDialog* m_saveDialog;
    gDateDialog* m_dateDialog;

    QString m_document;
    QString m_directory;
};

#endif // GMAINWIDGET_HPP
