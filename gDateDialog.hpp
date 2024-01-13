/*!
 * =============================================================================
 *
 *   @file: gDateDialog.hpp
 *
 *   @date: December, 2023
 *
 * @author: Gino Francesco Bogo
 *
 * =============================================================================
 */

#ifndef GDATEDIALOG_HPP
#define GDATEDIALOG_HPP

#include <QDate>
#include <QDialog>
#include <QString>

namespace Ui {
    class gDateDialog;
} // namespace Ui

class gDateDialog : public QDialog {
    Q_OBJECT

  public:
    explicit gDateDialog(QWidget* parent = nullptr);
    ~gDateDialog();

    void        setDate(const QDate& date);
    const QDate getDate();

    static const QString date2str(const QDate& date);
    static const QDate   str2date(const QString& str);

  private slots:
    void slotButton_Cancel();
    void slotButton_Select();

  private:
    Ui::gDateDialog* ui;

    QDate m_date;
};

#endif // GDATEDIALOG_HPP
