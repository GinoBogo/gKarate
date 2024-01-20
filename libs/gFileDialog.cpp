/*!
 * =============================================================================
 *
 *   @file: gFileDialog.cpp
 *
 *   @date: December, 2023
 *
 * @author: Gino Francesco Bogo
 *
 * =============================================================================
 */

#include "gFileDialog.hpp"

#include <qdialog.h>
#include <qfiledialog.h>
#include <qfileinfo.h>
#include <qstring.h>
#include <qwidget.h>

gFileDialog::gFileDialog(QWidget* parent, AcceptMode mode) :
QFileDialog(parent) {

    filters.append("Any files (*)");

    setOption(QFileDialog::DontUseNativeDialog, true);
    setViewMode(QFileDialog::List);
    setAcceptMode(mode);

    switch (mode) {
        case AcceptOpen: {
            setWindowTitle("Open File");
            setFileMode(ExistingFile);
        } break;

        case AcceptSave: {
            setWindowTitle("Save File");
            setFileMode(AnyFile);
        } break;

        default: {
        } break;
    }
}

bool gFileDialog::show(QString& directory, const QString& filename) {
    setDirectory(directory);
    setNameFilters(filters);

    if (!filename.isEmpty()) {
        selectFile(filename);
    }

    auto* parent = parentWidget();
    if (parent != nullptr) {
        auto rect_1 = parent->normalGeometry();
        auto rect_2 = normalGeometry();

        auto pos_x = rect_1.x() + (rect_1.width() - rect_2.width()) / 2;
        auto pos_y = rect_1.y() + (rect_1.height() - rect_2.height()) / 2;

        move(pos_x, pos_y);
    }

    if (exec() == QDialog::Accepted) {
        const auto& list = selectedFiles();

        if (list.count() > 0) {
            QFileInfo const info(list.at(0));
            selected  = info.absoluteFilePath();
            directory = info.absolutePath();
            return true;
        }
    }

    return false;
}

bool gFileDialog::isExtensionEmpty() const {
    const auto& info = QFileInfo(selected);
    return info.suffix().isEmpty();
}

/* =============================================================================
   End of file
 */
