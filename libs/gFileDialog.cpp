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
#include "qfileinfo.h"

#include <QFileInfo>
#include <QMessageBox>

gFileDialog::gFileDialog(QWidget* parent, AcceptMode mode) : QFileDialog(parent) {

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

bool gFileDialog::show(QString& directory, QString filename) {
    setDirectory(directory);
    setNameFilters(filters);

    if (!filename.isEmpty()) {
        selectFile(filename);
    }

    if (exec() == QDialog::Accepted) {
        const auto& list = selectedFiles();

        if (list.count() > 0) {
            QFileInfo info(list.at(0));
            selected  = info.absoluteFilePath();
            directory = info.absolutePath();
            return true;
        }
    }

    return false;
}

bool gFileDialog::isExtensionEmpty() {
    auto info = QFileInfo(selected);
    return info.suffix().isEmpty();
}
