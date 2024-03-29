/*!
 * =============================================================================
 *
 *   @file: gMainWidget.cpp
 *
 *   @date: December, 2023
 *
 * @author: Gino Francesco Bogo
 *
 * =============================================================================
 */

#include "gMainWidget.hpp"

#include "gDateDialog.hpp"
#include "libs/gFileDialog.hpp"
#include "libs/gXmlFile.hpp"
#include "libs/gXmlNode.hpp"
#include "libs/gXmlPair.hpp"
#include "qxlsx/xlsxdocument.h"
#include "tableWidgetExport.hpp"
#include "tableWidgetSetup.hpp"
#include "ui_gMainWidget.h"
#include "widgets/gTableWidgetRow.hpp"
#include "widgets/gTableWidgetRows.hpp"

#include <algorithm>
#include <qapplication.h>
#include <qcombobox.h>
#include <qcontainerfwd.h>
#include <qdatetime.h>
#include <qdialog.h>
#include <qdir.h>
#include <qfiledialog.h>
#include <qfileinfo.h>
#include <qforeach.h>
#include <qlogging.h>
#include <qnamespace.h>
#include <qstring.h>
#include <qstringliteral.h>
#include <qwidget.h>
#include <random>

gMainWidget::gMainWidget(QWidget* parent) :
QWidget(parent),
ui(new Ui::gMainWidget),
m_openDialog(new gFileDialog(this, QFileDialog::AcceptOpen)),
m_saveDialog(new gFileDialog(this, QFileDialog::AcceptSave)),
m_saveExport(new gFileDialog(this, QFileDialog::AcceptSave)),
m_dateDialog(new gDateDialog(this)),
m_document(m_untitled) {

    ui->setupUi(this);

    setupRankMap();

    ui->tabWidget->setStyleSheet("QTabBar::tab { width: 160px; }");
    ui->tabWidget->setCurrentIndex(0);

    ui->tableWidget_AthletesList->setupUi();
    ui->tableWidget_AthletesList->rows()->setupRow(setupRow_Full);

    ui->tableWidget_AthletesKata->setupUi();
    ui->tableWidget_AthletesKata->rows()->setupRow(setupRow_Mini);
    ui->tableWidget_AthletesKata->setContextMenuPolicy(Qt::NoContextMenu);

    ui->tableWidget_AthletesKumite->setupUi();
    ui->tableWidget_AthletesKumite->rows()->setupRow(setupRow_Mini);
    ui->tableWidget_AthletesKumite->setContextMenuPolicy(Qt::NoContextMenu);

    m_directory = getAppPath();
    openConfig(addAppPath("gKarate.cfg"));

    m_openDialog->setFont(this->font());
    m_saveDialog->setFont(this->font());
    m_saveExport->setFont(this->font());

    m_openDialog->filters.insert(0, "Dojo files (*.dojo)");
    m_saveDialog->filters.insert(0, "Dojo files (*.dojo)");
    m_saveExport->filters.insert(0, "Excel files (*.xlsx)");

    m_dateDialog->setFont(this->font());

    updateWindowTitle();
}

gMainWidget::~gMainWidget() {
    saveConfig(addAppPath("gKarate.cfg"));

    delete m_openDialog;
    delete m_saveDialog;
    delete m_saveExport;
    delete m_dateDialog;

    delete ui;
}

void gMainWidget::updateWindowTitle() {
    setWindowTitle(m_document + " - " + "gKarate");
}

void gMainWidget::updateRowTargetDate() {
    const auto& date = ui->lineEdit_EventDate->text();
    const auto* rows = ui->tableWidget_AthletesList->rows();

    auto N = rows->count();
    for (decltype(N) i(0); i < N; ++i) {
        const auto* row = rows->at(i);
        row->at(FULL_BIRTHDAY)->toDate()->setTargetDate(date);
    }
}

QString gMainWidget::getDocName() const {
    QString name = m_untitled;

    auto title = windowTitle().split(" - ");
    if (title.count() > 1) {
        name = title.at(0);
        name.replace(".dojo", "", Qt::CaseInsensitive);
    }

    return name;
}

QString gMainWidget::getAppPath() {
    return qApp->applicationDirPath() + QDir::separator();
}

QString gMainWidget::addAppPath(const QString& filename) {
    return getAppPath() + filename;
}

// NOTE cognitive complexity warning (threshold 25).
void gMainWidget::openConfig(const QString& filename) {
    gXmlFile xmlFile;

    if (xmlFile.open(filename)) {
        gXmlNode* node_0 = xmlFile.getRoot();
        gXmlNode* node_1 = xmlFile.findNode(node_0, "gMainWidget");
        gXmlNode* node_2 = xmlFile.findNode(node_1, "tabWidget");

        { // SEGMENT "geometry"
            gXmlNode* node_A = xmlFile.findNode(node_1, "geometry");

            if (node_A != nullptr) {
                auto data = gXmlFile::getAttribute(node_A, "data");
                restoreGeometry(gXmlPair::str2byte(data));
            }
        }

        { // SEGMENT "directory"
            gXmlNode* node_A = xmlFile.findNode(node_1, "directory");

            if (node_A != nullptr) {
                auto data   = gXmlFile::getAttribute(node_A, "data");
                m_directory = gXmlPair::hex2str(data);
            }
        }

        { // SEGMENT "tableWidget_AthletesList"
            gXmlNode* node = xmlFile.findNode(node_2, "tableWidget_AthletesList");

            if (node != nullptr) {
                foreach (gXmlNode* child, node->children) {
                    auto name = gXmlFile::getAttribute(child, "name");
                    auto size = gXmlFile::getAttribute(child, "size").toInt();

                    (void)ui->tableWidget_AthletesList->setHeaderSize(name, size);
                }
            }
        }

        { // SEGMENT "tableWidget_AthletesKata"
            gXmlNode* node = xmlFile.findNode(node_2, "tableWidget_AthletesKata");

            if (node != nullptr) {
                foreach (gXmlNode* child, node->children) {
                    auto name = gXmlFile::getAttribute(child, "name");
                    auto size = gXmlFile::getAttribute(child, "size").toInt();

                    (void)ui->tableWidget_AthletesKata->setHeaderSize(name, size);
                }
            }
        }

        { // SEGMENT "tableWidget_AthletesKumite"
            gXmlNode* node = xmlFile.findNode(node_2, "tableWidget_AthletesKumite");

            if (node != nullptr) {
                foreach (gXmlNode* child, node->children) {
                    auto name = gXmlFile::getAttribute(child, "name");
                    auto size = gXmlFile::getAttribute(child, "size").toInt();

                    (void)ui->tableWidget_AthletesKumite->setHeaderSize(name, size);
                }
            }
        }
    }
}

void gMainWidget::saveConfig(const QString& filename) {
    gXmlFile xmlFile;

    xmlFile.setRootName("gKarate");

    gXmlNode* node_0 = xmlFile.getRoot();
    gXmlNode* node_1 = xmlFile.insertNode(node_0, "gMainWidget");
    gXmlNode* node_2 = xmlFile.insertNode(node_1, "tabWidget");

    { // SEGMENT "geometry"
        gXmlNode* node_A = xmlFile.insertNode(node_1, "geometry");

        gXmlPair const pair("data", gXmlPair::byte2str(saveGeometry()));
        node_A->attributes.append(pair);
    }

    { // SEGMENT "directory"
        gXmlNode* node_A = xmlFile.insertNode(node_1, "directory");

        gXmlPair const pair("data", gXmlPair::str2hex(m_directory));
        node_A->attributes.append(pair);
    }

    { // SEGMENT "tableWidget_AthletesList"
        gXmlNode* node = xmlFile.insertNode(node_2, "tableWidget_AthletesList");

        const auto& headerNames = ui->tableWidget_AthletesList->headerNames();
        const auto& headerSizes = ui->tableWidget_AthletesList->headerSizes();

        auto N = headerNames.count();
        for (decltype(N) i(0); i < N; ++i) {
            const auto& name = QString("header_%1").arg(i, 2, 10, QChar('0'));

            auto* node_i = xmlFile.insertNode(node, name);
            node_i->attributes.append(gXmlPair("name", headerNames.at(i)));
            node_i->attributes.append(gXmlPair("size", headerSizes.at(i)));
        }
    }

    { // SEGMENT "tableWidget_AthletesKata"
        gXmlNode* node = xmlFile.insertNode(node_2, "tableWidget_AthletesKata");

        const auto& headerNames = ui->tableWidget_AthletesKata->headerNames();
        const auto& headerSizes = ui->tableWidget_AthletesKata->headerSizes();

        auto N = headerNames.count();
        for (decltype(N) i(0); i < N; ++i) {
            const auto& name = QString("header_%1").arg(i, 2, 10, QChar('0'));

            auto* node_i = xmlFile.insertNode(node, name);
            node_i->attributes.append(gXmlPair("name", headerNames.at(i)));
            node_i->attributes.append(gXmlPair("size", headerSizes.at(i)));
        }
    }

    { // SEGMENT "tableWidget_AthletesKumite"
        gXmlNode* node = xmlFile.insertNode(node_2, "tableWidget_AthletesKumite");

        const auto& headerNames = ui->tableWidget_AthletesKumite->headerNames();
        const auto& headerSizes = ui->tableWidget_AthletesKumite->headerSizes();

        auto N = headerNames.count();
        for (decltype(N) i(0); i < N; ++i) {
            const auto& name = QString("header_%1").arg(i, 2, 10, QChar('0'));

            auto* node_i = xmlFile.insertNode(node, name);
            node_i->attributes.append(gXmlPair("name", headerNames.at(i)));
            node_i->attributes.append(gXmlPair("size", headerSizes.at(i)));
        }
    }

    (void)xmlFile.save(filename);
}

void gMainWidget::clearTab1_Match() {
    ui->lineEdit_EventName->setText("");
    ui->lineEdit_EventSite->setText("");
    ui->lineEdit_EventDate->setText("");

    ui->tableWidget_AthletesList->rows()->clearAll();
}

void gMainWidget::clearTab2_Kata() {
    ui->comboBox_ReferenceKata->clear();
    ui->tableWidget_AthletesKata->rows()->clearAll();
}

void gMainWidget::clearTab3_Kumite() {
    ui->comboBox_ReferenceKumite->clear();
    ui->tableWidget_AthletesKumite->rows()->clearAll();
}

void gMainWidget::slotButton_MatchDate() {
    auto date = QDate::currentDate();
    auto text = ui->lineEdit_EventDate->text();

    if (!text.isEmpty()) {
        date = gDateDialog::str2date(text);
    }

    m_dateDialog->setDate(date);

    if (m_dateDialog->exec() == QDialog::Accepted) {
        date = m_dateDialog->getDate();
        text = gDateDialog::date2str(date);
        ui->lineEdit_EventDate->setText(text);

        updateRowTargetDate();
    }
}

void gMainWidget::slotButton_FileNew() {
    m_document = m_untitled;
    updateWindowTitle();

    clearTab1_Match();
    clearTab2_Kata();
    clearTab3_Kumite();
}

void gMainWidget::slotButton_FileOpen() {
    ui->tableWidget_AthletesList->setSortingEnabled(false);

    if (m_openDialog->show(m_directory)) {
        gXmlFile xmlFile;

        auto filepath = m_openDialog->selected;
        m_document    = QFileInfo(filepath).fileName();

        if (xmlFile.open(filepath)) {
            updateWindowTitle();

            clearTab1_Match();
            clearTab2_Kata();
            clearTab3_Kumite();

            gXmlNode* node_0 = nullptr;

            { // SEGMENT "group_event"
                gXmlNode* node_1 = xmlFile.findNode(node_0, "group_event");
                gXmlNode* node_2 = xmlFile.findNode(node_1, "event_name");
                gXmlNode* node_3 = xmlFile.findNode(node_1, "event_site");
                gXmlNode* node_4 = xmlFile.findNode(node_1, "event_date");

                if (node_2 != nullptr) {
                    ui->lineEdit_EventName->setText(node_2->text);
                }
                if (node_3 != nullptr) {
                    ui->lineEdit_EventSite->setText(node_3->text);
                }
                if (node_4 != nullptr) {
                    ui->lineEdit_EventDate->setText(node_4->text);
                }
            }

            { // SEGMENT "group_athlete"
                gXmlNode* node_1 = xmlFile.findNode(node_0, "group_athlete");

                auto* rows = ui->tableWidget_AthletesList->rows();

                auto nodes = xmlFile.findNodes(node_1, "athlete");

                auto N = nodes.count();
                for (decltype(N) i(0); i < N; ++i) {
                    auto* item = new gTableWidgetRow(rows, setupRow_Full);
                    // clang-format off
                    item->at(0)->toItem()->setText (gXmlFile::getAttribute(nodes.at(i), "surname"  ));
                    item->at(1)->toItem()->setText (gXmlFile::getAttribute(nodes.at(i), "name"     ));
                    item->at(2)->toDate()->setDate (gXmlFile::getAttribute(nodes.at(i), "birthday" ));
                    item->at(3)->toCBox()->setIndex(gXmlFile::getAttribute(nodes.at(i), "category" ));
                    item->at(4)->toCBox()->setIndex(gXmlFile::getAttribute(nodes.at(i), "rank"     ));
                    item->at(5)->toCBox()->setIndex(gXmlFile::getAttribute(nodes.at(i), "practice" ));
                    item->at(6)->toCBox()->setIndex(gXmlFile::getAttribute(nodes.at(i), "style"    ));
                    item->at(7)->toItem()->setText (gXmlFile::getAttribute(nodes.at(i), "society"  ));
                    item->at(8)->toItem()->setText (gXmlFile::getAttribute(nodes.at(i), "reference"));
                    // clang-format on
                    rows->insertRow((int)i, item);
                }
                updateRowTargetDate();
            }
        }
    }

    ui->tableWidget_AthletesList->setSortingEnabled(true);
}

void gMainWidget::slotButton_FileSave() {
    if (m_saveDialog->show(m_directory)) {
        gXmlFile xmlFile;

        xmlFile.setRootName("gKarate");

        gXmlNode* node_0 = nullptr;

        { // SEGMENT "group_event"
            gXmlNode* node_1 = xmlFile.insertNode(node_0, "group_event");
            gXmlNode* node_2 = xmlFile.insertNode(node_1, "event_name");
            gXmlNode* node_3 = xmlFile.insertNode(node_1, "event_site");
            gXmlNode* node_4 = xmlFile.insertNode(node_1, "event_date");

            node_2->text = ui->lineEdit_EventName->text().trimmed();
            node_3->text = ui->lineEdit_EventSite->text().trimmed();
            node_4->text = ui->lineEdit_EventDate->text().trimmed();
        }

        { // SEGMENT "group_athlete"
            gXmlNode* node_1 = xmlFile.insertNode(node_0, "group_athlete");

            const auto* rows = ui->tableWidget_AthletesList->rows();

            auto N = rows->count();
            for (decltype(N) i(0); i < N; ++i) {
                gXmlNode* node_2 = xmlFile.insertNode(node_1, "athlete");

                const auto* row = rows->at(i);
                // clang-format off
                node_2->attributes.append(gXmlPair("surname"  , row->at(0)->toItem()->text() ));
                node_2->attributes.append(gXmlPair("name"     , row->at(1)->toItem()->text() ));
                node_2->attributes.append(gXmlPair("birthday" , row->at(2)->toDate()->date() ));
                node_2->attributes.append(gXmlPair("category" , row->at(3)->toCBox()->index()));
                node_2->attributes.append(gXmlPair("rank"     , row->at(4)->toCBox()->index()));
                node_2->attributes.append(gXmlPair("practice" , row->at(5)->toCBox()->index()));
                node_2->attributes.append(gXmlPair("style"    , row->at(6)->toCBox()->index()));
                node_2->attributes.append(gXmlPair("society"  , row->at(7)->toItem()->text() ));
                node_2->attributes.append(gXmlPair("reference", row->at(8)->toItem()->text() ));
                // clang-format on
            }
        }

        if (m_saveDialog->isExtensionEmpty()) {
            m_saveDialog->selected += ".dojo";
        }

        auto filepath = m_openDialog->selected;
        m_document    = QFileInfo(filepath).completeBaseName();

        if (xmlFile.save(filepath)) {
            updateWindowTitle();
        }
    }
}

void gMainWidget::slotButton_CreateKata() {
    comboBox_ReferencePopulate(ui->comboBox_ReferenceKata, ui->tab_2_kata, "02");
}

void gMainWidget::slotButton_CreateKumite() {
    comboBox_ReferencePopulate(ui->comboBox_ReferenceKumite, ui->tab_3_kumite, "12");
}

void gMainWidget::slotComboBox_ReferenceKata(const QString& text) {
    comboBox_ReferenceChanged(ui->tableWidget_AthletesKata, text, "02");
}

void gMainWidget::slotComboBox_ReferenceKumite(const QString& text) {
    comboBox_ReferenceChanged(ui->tableWidget_AthletesKumite, text, "12");
}

void gMainWidget::slotButton_ReorderKata() {
    tableWidget_ReorderPeople(ui->tableWidget_AthletesKata);
}

void gMainWidget::slotButton_ReorderKumite() {
    tableWidget_ReorderPeople(ui->tableWidget_AthletesKumite);
}

void export_sanitizer(QString& selected) {
    auto m1 = QStringLiteral("((_register)|(_evaluate))(.xlsx)");
    auto r1 = QRegularExpression(m1, QRegularExpression::CaseInsensitiveOption);
    selected.remove(r1);

    auto m2 = QStringLiteral("((_kata)|(_kumite))(_ref)(\\d+)");
    auto r2 = QRegularExpression(m2, QRegularExpression::CaseInsensitiveOption);
    selected.remove(r2);
}

void gMainWidget::slotButton_ExportKata() {
    const auto reference = "_kata_ref" + ui->comboBox_ReferenceKata->currentText();

    if (m_saveExport->show(m_directory, getDocName() + reference)) {
        auto selected = m_saveExport->selected;
        export_sanitizer(selected);

        auto register_filename = selected + reference + "_register.xlsx";
        auto evaluate_filename = selected + reference + "_evaluate.xlsx";

        QXlsx::Document register_xlsx;
        QXlsx::Document evaluate_xlsx;

        register_xlsx.setDocumentProperty("creator", "Gino Francesco Bogo");
        evaluate_xlsx.setDocumentProperty("creator", "Gino Francesco Bogo");

        const auto& title = ui->lineEdit_EventName->text();
        tableWidget_ExportRegister(ui->tableWidget_AthletesKata, register_xlsx, title, "KATA");
        tableWidget_ExportEvaluate(ui->tableWidget_AthletesKata, evaluate_xlsx, title, "KATA");

        register_xlsx.saveAs(register_filename);
        evaluate_xlsx.saveAs(evaluate_filename);
    }
}

void gMainWidget::slotButton_ExportKumite() {
    const auto reference = "_kumite_ref" + ui->comboBox_ReferenceKumite->currentText();

    if (m_saveExport->show(m_directory, getDocName() + reference)) {
        auto selected = m_saveExport->selected;
        export_sanitizer(selected);

        auto register_filename = selected + reference + "_register.xlsx";
        auto evaluate_filename = selected + reference + "_evaluate.xlsx";

        QXlsx::Document register_xlsx;
        QXlsx::Document evaluate_xlsx;

        register_xlsx.setDocumentProperty("creator", "Gino Francesco Bogo");
        evaluate_xlsx.setDocumentProperty("creator", "Gino Francesco Bogo");

        const auto& title = ui->lineEdit_EventName->text();
        tableWidget_ExportRegister(ui->tableWidget_AthletesKumite, register_xlsx, title, "KUMITE");
        tableWidget_ExportEvaluate(ui->tableWidget_AthletesKumite, evaluate_xlsx, title, "KUMITE");

        register_xlsx.saveAs(register_filename);
        evaluate_xlsx.saveAs(evaluate_filename);
    }
}

void gMainWidget::comboBox_ReferencePopulate(QComboBox* comboBox_AthletesDst, QWidget* tab_number_dst, const QString& filter) {

    QStringList references;

    const auto* rows_src = ui->tableWidget_AthletesList->rows();

    auto N = rows_src->count();
    for (decltype(N) i(0); i < N; ++i) {
        auto* row = rows_src->at(i);
        auto  tag = row->at(FULL_PRACTICE)->toCBox()->index();
        auto  ref = row->at(FULL_REFERENCE)->toItem()->text();

        if (filter.contains(tag) && !references.contains(ref)) {
            references.append(ref);
        }
    }

    if (references.count() > 0) {
        references.sort();
        comboBox_AthletesDst->clear();
        comboBox_AthletesDst->addItems(references);

        ui->tabWidget->setCurrentWidget(tab_number_dst);
    }
}

void gMainWidget::comboBox_ReferenceChanged(gTableWidget* tableWidget_AthletesDst, const QString& reference, const QString& filter) {

    const auto* rows_src = ui->tableWidget_AthletesList->rows();
    auto*       rows_dst = tableWidget_AthletesDst->rows();

    rows_dst->clearAll();

    auto group = rows_src->filterRows(FULL_REFERENCE, reference);

    auto N = group.count();
    for (decltype(N) i(0); i < N; ++i) {
        auto* row_ptr = group.at(i);

        auto index = row_ptr->at(FULL_PRACTICE)->toCBox()->index();

        if (filter.contains(index)) {
            auto* item = new gTableWidgetRow(rows_dst, setupRow_Mini);
            // clang-format off
            item->at(MINI_SURNAME )->toItem()->setText (row_ptr->at(FULL_SURNAME )->toItem()->text() );
            item->at(MINI_NAME    )->toItem()->setText (row_ptr->at(FULL_NAME    )->toItem()->text() );
            item->at(MINI_CATEGORY)->toItem()->setText (row_ptr->at(FULL_CATEGORY)->toCBox()->text() );
            item->at(MINI_RANK    )->toIcon()->setIndex(row_ptr->at(FULL_RANK    )->toCBox()->index());
            item->at(MINI_SOCIETY )->toItem()->setText (row_ptr->at(FULL_SOCIETY )->toItem()->text() );
            item->at(MINI_STYLE   )->toItem()->setText (row_ptr->at(FULL_STYLE   )->toCBox()->text() );
            // clang-format on
            rows_dst->insertRow((int)i, item);
        }
    }
}

void gMainWidget::tableWidget_ReorderPeople(gTableWidget* tableWidget_AthletesDst) {
    auto* rows = tableWidget_AthletesDst->rows();

    if (rows->count() > 0) {
        auto list = rows->cellsData();

        auto iB = list.begin();
        auto iE = list.end();

        // std::sort(iB, iE, [](const auto& a, const auto& b) {
        //     return a.at(MINI_SOCIETY) < b.at(MINI_SOCIETY);
        // });

        std::random_device random;
        std::mt19937       engine(random());

        auto attempts = 0;
        while (attempts++ < 100) {
            std::shuffle(iB, iE, engine);
            bool sparse = true;

            auto iP = iB;
            auto iN = iB + 1;

            while (iN != iE) {
                const auto& name_P = iP->at(MINI_SOCIETY);
                const auto& name_N = iN->at(MINI_SOCIETY);

                if (name_P == name_N) {
                    sparse = false;
                    break;
                }
                ++iP;
                ++iN;
            }

            if (sparse) {
                break;
            }
        }

        rows->setCellsData(list);

        qDebug("reorder attempts: %d", attempts);
    }
}

void gMainWidget::tableWidget_ExportRegister(gTableWidget*    tableWidget_AthletesSrc,
                                             QXlsx::Document& document,
                                             const QString&   title,
                                             const QString&   practice) {

    const auto* rows = tableWidget_AthletesSrc->rows();

    if (rows->count() > 0) {
        gXlsx::PeopleRecord record;
        record.title    = title;
        record.practice = practice;
        gXlsx::decodeTableWidget(tableWidget_AthletesSrc, record);

        auto mod = (int)record.athletes.count() / gXlsx::max_register_lines;
        auto rem = (int)record.athletes.count() % gXlsx::max_register_lines;

        auto group = record;

        decltype(mod) sheet(1);
        for (; sheet <= mod; ++sheet) {
            document.addSheet(QString("%1_%2").arg(record.practice).arg(sheet));

            const auto pos = (sheet - 1) * gXlsx::max_register_lines;
            group.athletes = record.athletes.mid(pos, gXlsx::max_register_lines);
            gXlsx::createSheetRegister(document, group, sheet);
        }

        if (rem > 0) {
            document.addSheet(QString("%1_%2").arg(record.practice).arg(sheet));

            const auto pos = (sheet - 1) * gXlsx::max_register_lines;
            group.athletes = record.athletes.mid(pos, rem);
            gXlsx::createSheetRegister(document, group, sheet);
        }
    }
}

void gMainWidget::tableWidget_ExportEvaluate(gTableWidget*    tableWidget_AthletesSrc,
                                             QXlsx::Document& document,
                                             const QString&   title,
                                             const QString&   practice) {

    const auto* rows = tableWidget_AthletesSrc->rows();

    if (rows->count() > 0) {
        gXlsx::PeopleRecord record;
        record.title    = title;
        record.practice = practice;
        gXlsx::decodeTableWidget(tableWidget_AthletesSrc, record);

        auto mod = (int)record.athletes.count() / gXlsx::max_evaluate_lines;
        auto rem = (int)record.athletes.count() % gXlsx::max_evaluate_lines;

        auto group = record;

        decltype(mod) sheet{1};
        for (; sheet <= mod; ++sheet) {
            document.addSheet(QString("%1_%2").arg(record.practice).arg(sheet));

            const auto pos = (sheet - 1) * gXlsx::max_evaluate_lines;
            group.athletes = record.athletes.mid(pos, gXlsx::max_evaluate_lines);
            gXlsx::createSheetEvaluate(document, group, sheet);
        }

        if (rem > 0) {
            document.addSheet(QString("%1_%2").arg(record.practice).arg(sheet));

            const auto pos = (sheet - 1) * gXlsx::max_evaluate_lines;
            group.athletes = record.athletes.mid(pos, rem);
            gXlsx::createSheetEvaluate(document, group, sheet);
        }
    }
}

/* =============================================================================
   End of file
 */
