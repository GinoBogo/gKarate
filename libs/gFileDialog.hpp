/*!
 * =============================================================================
 *
 *   @file: gFileDialog.hpp
 *
 *   @date: December, 2023
 *
 * @author: Gino Francesco Bogo
 *
 * =============================================================================
 */

#ifndef GFILEDIALOG_HPP
#define GFILEDIALOG_HPP

#include <QFileDialog>
#include <QString>
#include <QStringList>

class gFileDialog : public QFileDialog {
  public:
    gFileDialog(QWidget* parent, AcceptMode mode);

    bool show(QString& directory, const QString& filename = "");

    [[nodiscard]] bool isExtensionEmpty() const;

  public:
    QStringList filters;
    QString     selected;
};

#endif // GFILEDIALOG_HPP
