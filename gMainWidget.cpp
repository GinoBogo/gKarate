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
#include "ui_gMainWidget.h"

#include "libs/gXmlFile.hpp"
#include "tableWidgetExport.hpp"
#include "tableWidgetSetup.hpp"

#include <QByteArray>
#include <QDir>

#include <algorithm>
#include <random>

gMainWidget::gMainWidget(QWidget* parent) : QWidget(parent), ui(new Ui::gMainWidget) {

    ui->setupUi(this);

    ui->tabWidget->setStyleSheet("QTabBar::tab { width: 160px; }");
    ui->tabWidget->setCurrentIndex(0);

    ui->tableWidget_people->setupUi();
    ui->tableWidget_people->renameMenuNames(setup_menu_names);
    ui->tableWidget_people->rows()->setupRow(setupRow_Full);

    ui->tableWidget_peopleKata->setupUi();
    ui->tableWidget_peopleKata->renameMenuNames(setup_menu_names);
    ui->tableWidget_peopleKata->rows()->setupRow(setupRow_Mini);
    ui->tableWidget_peopleKata->setContextMenuPolicy(Qt::NoContextMenu);

    ui->tableWidget_peopleKumite->setupUi();
    ui->tableWidget_peopleKumite->renameMenuNames(setup_menu_names);
    ui->tableWidget_peopleKumite->rows()->setupRow(setupRow_Mini);
    ui->tableWidget_peopleKumite->setContextMenuPolicy(Qt::NoContextMenu);

    m_document  = "senza nome";
    m_directory = getAppPath();
    openConfig(addAppPath("gKarate.cfg"));

    m_openDialog = new gFileDialog(this, QFileDialog::AcceptOpen);
    m_saveDialog = new gFileDialog(this, QFileDialog::AcceptSave);
    m_saveExport = new gFileDialog(this, QFileDialog::AcceptSave);
    m_openDialog->setFont(this->font());
    m_saveDialog->setFont(this->font());
    m_saveExport->setFont(this->font());

    m_openDialog->filters.insert(0, "Dojo files (*.dojo)");
    m_saveDialog->filters.insert(0, "Dojo files (*.dojo)");
    m_saveExport->filters.insert(0, "Excel files (*.xlsx)");

    m_dateDialog = new gDateDialog(this);
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

QString gMainWidget::getAppPath() const {
    return qApp->applicationDirPath() + QDir::separator();
}

QString gMainWidget::addAppPath(const QString& filename) const {
    return getAppPath() + filename;
}

void gMainWidget::openConfig(const QString& filename) {
    gXmlFile xmlFile;

    if (xmlFile.open(filename)) {

        gXmlNode* node_0 = nullptr;
        gXmlNode* node_1 = xmlFile.findNode(node_0, "main_widget");
        gXmlNode* node_2 = xmlFile.findNode(node_1, "tab_widget");

        { // SECTION: "geometry"
            gXmlNode* node_A = xmlFile.findNode(node_1, "geometry");

            if (node_A != nullptr) {
                auto data = xmlFile.getAttribute(node_A, "data");
                restoreGeometry(gXmlPair::str2byte(data));
            }
        }

        { // SECTION: "directory"
            gXmlNode* node_A = xmlFile.findNode(node_1, "directory");

            if (node_A != nullptr) {
                auto data   = xmlFile.getAttribute(node_A, "data");
                m_directory = gXmlPair::hex2str(data);
            }
        }

        { // SECTION: "tab_widget_people"
            gXmlNode* node = xmlFile.findNode(node_2, "tab_widget_people");

            if (node != nullptr) {
                foreach (gXmlNode* child, node->children) {
                    auto name = xmlFile.getAttribute(child, "name");
                    auto size = xmlFile.getAttribute(child, "size").toInt();

                    (void)ui->tableWidget_people->setHeaderSize(name, size);
                }
            }
        }

        { // SECTION: "tab_widget_people_kata"
            gXmlNode* node = xmlFile.findNode(node_2, "tab_widget_people_kata");

            if (node != nullptr) {
                foreach (gXmlNode* child, node->children) {
                    auto name = xmlFile.getAttribute(child, "name");
                    auto size = xmlFile.getAttribute(child, "size").toInt();

                    (void)ui->tableWidget_peopleKata->setHeaderSize(name, size);
                }
            }
        }

        { // SECTION: "tab_widget_people_kumite"
            gXmlNode* node = xmlFile.findNode(node_2, "tab_widget_people_kumite");

            if (node != nullptr) {
                foreach (gXmlNode* child, node->children) {
                    auto name = xmlFile.getAttribute(child, "name");
                    auto size = xmlFile.getAttribute(child, "size").toInt();

                    (void)ui->tableWidget_peopleKumite->setHeaderSize(name, size);
                }
            }
        }
    }
}

void gMainWidget::saveConfig(const QString& filename) {
    gXmlFile xmlFile;

    xmlFile.setRootName("gKarate");

    gXmlNode* node_0 = nullptr;
    gXmlNode* node_1 = xmlFile.insertNode(node_0, "main_widget");
    gXmlNode* node_2 = xmlFile.insertNode(node_1, "tab_widget");

    { // SECTION: "geometry"
        gXmlNode* node_A = xmlFile.insertNode(node_1, "geometry");

        gXmlPair pair("data", gXmlPair::byte2str(saveGeometry()));
        node_A->attributes.append(pair);
    }

    { // SECTION: "directory"
        gXmlNode* node_A = xmlFile.insertNode(node_1, "directory");

        gXmlPair pair("data", gXmlPair::str2hex(m_directory));
        node_A->attributes.append(pair);
    }

    { // SECTION: "tab_widget_people"
        gXmlNode* node = xmlFile.insertNode(node_2, "tab_widget_people");

        const auto& headerNames = ui->tableWidget_people->headerNames();
        const auto& headerSizes = ui->tableWidget_people->headerSizes();

        auto N = headerNames.count();
        for (decltype(N) i{0}; i < N; ++i) {
            const auto& name = QString("header_%1").arg(i, 2, 10, QChar('0'));

            auto* node_i = xmlFile.insertNode(node, name);
            node_i->attributes.append(gXmlPair("name", headerNames.at(i)));
            node_i->attributes.append(gXmlPair("size", headerSizes.at(i)));
        }
    }

    { // SECTION: "tab_widget_people_kata"
        gXmlNode* node = xmlFile.insertNode(node_2, "tab_widget_people_kata");

        const auto& headerNames = ui->tableWidget_peopleKata->headerNames();
        const auto& headerSizes = ui->tableWidget_peopleKata->headerSizes();

        auto N = headerNames.count();
        for (decltype(N) i{0}; i < N; ++i) {
            const auto& name = QString("header_%1").arg(i, 2, 10, QChar('0'));

            auto* node_i = xmlFile.insertNode(node, name);
            node_i->attributes.append(gXmlPair("name", headerNames.at(i)));
            node_i->attributes.append(gXmlPair("size", headerSizes.at(i)));
        }
    }

    { // SECTION: "tab_widget_people_kumite"
        gXmlNode* node = xmlFile.insertNode(node_2, "tab_widget_people_kumite");

        const auto& headerNames = ui->tableWidget_peopleKumite->headerNames();
        const auto& headerSizes = ui->tableWidget_peopleKumite->headerSizes();

        auto N = headerNames.count();
        for (decltype(N) i{0}; i < N; ++i) {
            const auto& name = QString("header_%1").arg(i, 2, 10, QChar('0'));

            auto* node_i = xmlFile.insertNode(node, name);
            node_i->attributes.append(gXmlPair("name", headerNames.at(i)));
            node_i->attributes.append(gXmlPair("size", headerSizes.at(i)));
        }
    }

    (void)xmlFile.save(filename);
}

void gMainWidget::clearTab1_Match() {
    ui->lineEdit_match_name->setText("");
    ui->lineEdit_match_site->setText("");
    ui->lineEdit_match_date->setText("");

    ui->tableWidget_people->rows()->clearAll();
}

void gMainWidget::clearTab2_Kata() {
    ui->comboBox_ReferenceKata->clear();

    ui->tableWidget_peopleKata->rows()->clearAll();
}

void gMainWidget::clearTab3_Kumite() {}

void gMainWidget::slotButton_MatchDate() {
    auto date = QDate::currentDate();
    auto text = ui->lineEdit_match_date->text();

    if (!text.isEmpty()) {
        date = gDateDialog::str2date(text);
    }

    m_dateDialog->setDate(date);

    if (m_dateDialog->exec() == QDialog::Accepted) {
        date = m_dateDialog->getDate();
        text = gDateDialog::date2str(date);
        ui->lineEdit_match_date->setText(text);
    }
}

void gMainWidget::slotButton_FileNew() {
    m_document = "senza nome";
    updateWindowTitle();

    clearTab1_Match();
    clearTab2_Kata();
    clearTab3_Kumite();
}

void gMainWidget::slotButton_FileOpen() {
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

            { // SECTION: "group_match"
                gXmlNode* node_1 = xmlFile.findNode(node_0, "group_match");
                gXmlNode* node_2 = xmlFile.findNode(node_1, "match_name");
                gXmlNode* node_3 = xmlFile.findNode(node_1, "match_site");
                gXmlNode* node_4 = xmlFile.findNode(node_1, "match_date");

                if (node_2 != nullptr) {
                    ui->lineEdit_match_name->setText(node_2->text);
                }
                if (node_3 != nullptr) {
                    ui->lineEdit_match_site->setText(node_3->text);
                }
                if (node_4 != nullptr) {
                    ui->lineEdit_match_date->setText(node_4->text);
                }
            }

            { // SECTION: "group_people"
                gXmlNode* node_1 = xmlFile.findNode(node_0, "group_people");

                auto* rows = ui->tableWidget_people->rows();

                auto nodes = xmlFile.findNodes(node_1, "athlete");

                auto N = nodes.count();
                for (decltype(N) i{0}; i < N; ++i) {
                    auto* item = new gTableWidgetRow(rows, setupRow_Full);

                    // clang-format off
                    item->at(0)->toItem()->setText (xmlFile.getAttribute(nodes.at(i), "surname"  ));
                    item->at(1)->toItem()->setText (xmlFile.getAttribute(nodes.at(i), "name"     ));
                    item->at(2)->toDate()->setDate (xmlFile.getAttribute(nodes.at(i), "birthday" ));
                    item->at(3)->toCBox()->setIndex(xmlFile.getAttribute(nodes.at(i), "category" ));
                    item->at(4)->toCBox()->setIndex(xmlFile.getAttribute(nodes.at(i), "rank"     ));
                    item->at(5)->toCBox()->setIndex(xmlFile.getAttribute(nodes.at(i), "practice" ));
                    item->at(6)->toCBox()->setIndex(xmlFile.getAttribute(nodes.at(i), "style"    ));
                    item->at(7)->toItem()->setText (xmlFile.getAttribute(nodes.at(i), "society"  ));
                    item->at(8)->toItem()->setText (xmlFile.getAttribute(nodes.at(i), "reference"));
                    // clang-format on

                    rows->insertRow(i, item);
                }
            }
        }
    }
}

void gMainWidget::slotButton_FileSave() {
    if (m_saveDialog->show(m_directory)) {
        gXmlFile xmlFile;

        xmlFile.setRootName("gKarate");

        gXmlNode* node_0 = nullptr;

        { // SECTION: "group_match"
            gXmlNode* node_1 = xmlFile.insertNode(node_0, "group_match");
            gXmlNode* node_2 = xmlFile.insertNode(node_1, "match_name");
            gXmlNode* node_3 = xmlFile.insertNode(node_1, "match_site");
            gXmlNode* node_4 = xmlFile.insertNode(node_1, "match_date");

            node_2->text = ui->lineEdit_match_name->text().trimmed();
            node_3->text = ui->lineEdit_match_site->text().trimmed();
            node_4->text = ui->lineEdit_match_date->text().trimmed();
        }

        { // SECTION: "group_people"
            gXmlNode* node_1 = xmlFile.insertNode(node_0, "group_people");

            const auto* rows = ui->tableWidget_people->rows();

            auto N = rows->count();
            for (decltype(N) i{0}; i < N; ++i) {
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

void gMainWidget::slotButton_MakeKata() {
    comboBox_ReferencePopulate(ui->comboBox_ReferenceKata, ui->tab_2_kata, "02");
}

void gMainWidget::slotButton_MakeKumite() {
    comboBox_ReferencePopulate(ui->comboBox_ReferenceKumite, ui->tab_3_kumite, "12");
}

void gMainWidget::slotComboBox_ReferenceKata(const QString& text) {
    comboBox_ReferenceChanged(ui->tableWidget_peopleKata, text, "02");
}

void gMainWidget::slotComboBox_ReferenceKumite(const QString& text) {
    comboBox_ReferenceChanged(ui->tableWidget_peopleKumite, text, "12");
}

void gMainWidget::slotButton_ReorderKata() {
    tableWidget_ReorderPeople(ui->tableWidget_peopleKata);
}

void gMainWidget::slotButton_ReorderKumite() {
    tableWidget_ReorderPeople(ui->tableWidget_peopleKumite);
}

void gMainWidget::slotButton_ExportKata() {
    const auto& title = ui->lineEdit_match_name->text();
    tableWidget_ExportPeople(ui->tableWidget_peopleKata, title, "KATA");
}

void gMainWidget::slotButton_ExportKumite() {
    const auto& title = ui->lineEdit_match_name->text();
    tableWidget_ExportPeople(ui->tableWidget_peopleKumite, title, "KUMITE");
}

void gMainWidget::comboBox_ReferencePopulate(QComboBox*     comboBox_people_dst,
                                             QWidget*       tab_number_dst,
                                             const QString& filter) {

    QStringList references;

    const auto* rows_src = ui->tableWidget_people->rows();

    auto N = rows_src->count();
    for (decltype(N) i{0}; i < N; ++i) {
        auto* row = rows_src->at(i);
        auto  tag = row->at(FULL_PRACTICE)->toCBox()->index();
        auto  ref = row->at(FULL_REFERENCE)->toItem()->text();

        if (filter.contains(tag) && !references.contains(ref)) {
            references.append(ref);
        }
    }

    if (references.count() > 0) {
        references.sort();
        comboBox_people_dst->clear();
        comboBox_people_dst->addItems(references);

        ui->tabWidget->setCurrentWidget(tab_number_dst);
    }
}

void gMainWidget::comboBox_ReferenceChanged(gTableWidget*  tableWidget_people_dst,
                                            const QString& reference,
                                            const QString& filter) {

    const auto* rows_src = ui->tableWidget_people->rows();
    auto*       rows_dst = tableWidget_people_dst->rows();

    rows_dst->clearAll();

    auto group = rows_src->filterRows(FULL_REFERENCE, reference);

    auto N = group.count();
    for (decltype(N) i{0}; i < N; ++i) {
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
            rows_dst->insertRow(i, item);
        }
    }
}

void gMainWidget::tableWidget_ReorderPeople(gTableWidget* tableWidget_people_dst) {
    auto* rows = tableWidget_people_dst->rows();

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

void gMainWidget::tableWidget_ExportPeople(gTableWidget*  tableWidget_people_src,
                                           const QString& title,
                                           const QString& practice) {

    auto* rows = tableWidget_people_src->rows();

    if (rows->count() > 0) {
        if (m_saveExport->show(m_directory)) {
            if (m_saveExport->isExtensionEmpty()) {
                m_saveExport->selected += ".xlsx";
            }

            QXlsx::Document document;

            gXlsx::PeopleRecord record;

            record.title    = title;
            record.practice = practice;

            gXlsx::decodeTableWidget(tableWidget_people_src, record);

            gXlsx::createSheet(document, record);

            document.saveAs(m_saveExport->selected);
        }
    }
}
