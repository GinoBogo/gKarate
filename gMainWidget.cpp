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
#include "tableWidgetSetup.hpp"

#include <QByteArray>
#include <QDir>

gMainWidget::gMainWidget(QWidget* parent) : QWidget(parent), ui(new Ui::gMainWidget) {

    ui->setupUi(this);

    ui->tabWidget->setStyleSheet("QTabBar::tab { width: 160px; }");
    ui->tabWidget->setCurrentIndex(0);

    QStringList menu_names = {
        "Aggiungi Atleta",   // Insert
        "Rimuovi Atleta",    // Remove
        "Elimina Elenco",    // Clear
        "Copia Riga",        // Copy
        "Taglia Riga",       // Cut
        "Incolla Riga",      // Paste
        "Sposta Riga Sopra", // Move Up
        "Sposta Riga Sotto"  // Move Down
    };

    ui->tableWidget_people->setupUi();
    ui->tableWidget_people->renameMenuNames(menu_names);
    ui->tableWidget_people->rows()->setupRow(setupRow_People);

    ui->tableWidget_peopleKata->setupUi();
    ui->tableWidget_peopleKata->renameMenuNames(menu_names);
    ui->tableWidget_peopleKata->rows()->setupRow(setupRow_PeopleKata);

    m_document  = "senza nome";
    m_directory = getAppPath();
    openConfig(addAppPath("gKarate.cfg"));

    m_openDialog = new gFileDialog(this, QFileDialog::AcceptOpen);
    m_saveDialog = new gFileDialog(this, QFileDialog::AcceptSave);
    m_openDialog->setFont(this->font());
    m_saveDialog->setFont(this->font());

    m_openDialog->filters.insert(0, "Dojo files (*.dojo)");
    m_saveDialog->filters.insert(0, "Dojo files (*.dojo)");

    m_dateDialog = new gDateDialog(this);
    m_dateDialog->setFont(this->font());

    updateWindowTitle();
}

gMainWidget::~gMainWidget() {
    saveConfig(addAppPath("gKarate.cfg"));

    delete m_openDialog;
    delete m_saveDialog;
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
                    auto* item = new gTableWidgetRow(rows, setupRow_People);

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
    const auto* rows = ui->tableWidget_people->rows();

    auto references = rows->zipCellDataByColumn(8);

    if (references.count() > 0) {
        ui->comboBox_ReferenceKata->clear();
        ui->comboBox_ReferenceKata->addItems(references);

        ui->tabWidget->setCurrentIndex(1);
    }
}

void gMainWidget::slotButton_MakeKumite() {}

void gMainWidget::slotComboBox_ReferenceKata(const QString& text) {
    const auto* rows      = ui->tableWidget_people->rows();
    auto*       rows_kata = ui->tableWidget_peopleKata->rows();

    rows_kata->clearAll();

    auto group = rows->filterRows(8, text);

    auto N = group.count();
    for (decltype(N) i{0}; i < N; ++i) {
        auto* row_ptr = group.at(i);

        auto* item = new gTableWidgetRow(rows_kata, setupRow_PeopleKata);
        // clang-format off
        item->at(0)->toItem()->setText (row_ptr->at(0)->toItem()->text() ); // Cognome
        item->at(1)->toItem()->setText (row_ptr->at(1)->toItem()->text() ); // Nome
        item->at(2)->toItem()->setText (row_ptr->at(3)->toCBox()->text() ); // Categoria
        item->at(3)->toIcon()->setIndex(row_ptr->at(4)->toCBox()->index()); // Grado
        item->at(4)->toItem()->setText (row_ptr->at(7)->toItem()->text() ); // Società
        item->at(5)->toItem()->setText (row_ptr->at(6)->toCBox()->text() ); // Stile
        // clang-format on

        rows_kata->insertRow(i, item);
    }
}

void gMainWidget::slotComboBox_ReferenceKumite(const QString& text) {
    (void)text;
}
