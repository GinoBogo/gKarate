/*!
 * =============================================================================
 *
 *   @file: tableWidgetSetup.cpp
 *
 *   @date: January, 2024
 *
 * @author: Gino Francesco Bogo
 *
 * =============================================================================
 */

#include "tableWidgetSetup.hpp"

void setupRow_People(gTableWidgetRow* row_ptr) {
    if (row_ptr != nullptr) {
        // NOTE: automatic downcasting
        QList<gTableWidgetBase*> items =     //
            {new gTableWidgetItem(row_ptr),  // 0 Cognome
             new gTableWidgetItem(row_ptr),  // 1 Nome
             new gTableWidgetDate(row_ptr),  // 2 Data di Nascita
             new gTableWidgetCBox(row_ptr),  // 3 Categoria
             new gTableWidgetCBox(row_ptr),  // 4 Grado
             new gTableWidgetCBox(row_ptr),  // 5 Pratica
             new gTableWidgetCBox(row_ptr),  // 6 Stile
             new gTableWidgetItem(row_ptr),  // 7 Società
             new gTableWidgetItem(row_ptr)}; // 8 Riferimento

        items.at(2)->toDate()->setDate("31/12/2016");

        items.at(3)->toCBox()->addItems( //
            {"6 ÷ 8 anni",
             "9 ÷ 10 anni",
             "11 ÷ 12 anni",
             "13 ÷ 14 anni",
             "15 ÷ 17 anni",
             "18 ÷ 21 anni",
             "22 ÷ 35 anni",
             "36 ÷ 45 anni",
             "+45 anni"});

        items.at(4)->toCBox()->images() = //
            {QPixmap(":/res/images/beld_white.png"),
             QPixmap(":/res/images/beld_white_yellow.png"),
             QPixmap(":/res/images/beld_yellow.png"),
             QPixmap(":/res/images/beld_yellow_orange.png"),
             QPixmap(":/res/images/beld_orange.png"),
             QPixmap(":/res/images/beld_orange_green.png"),
             QPixmap(":/res/images/beld_green.png"),
             QPixmap(":/res/images/beld_green_blue.png"),
             QPixmap(":/res/images/beld_blue.png"),
             QPixmap(":/res/images/beld_blue_brown.png"),
             QPixmap(":/res/images/beld_brown.png"),
             QPixmap(":/res/images/beld_brown_black.png"),
             QPixmap(":/res/images/beld_black.png")};

        auto N = items.at(4)->toCBox()->images().count();
        items.at(4)->toCBox()->setIconSize(QSize(64, 24));
        items.at(4)->toCBox()->resize(N);
        items.at(4)->toCBox()->setupUi();

        items.at(5)->toCBox()->addItems({"Kata", "Kumite", "Kata / Kumite"});
        items.at(6)->toCBox()->addItems({"Interstile", "Shotokan", "Gojo-ryu", "Shito-ryu", "Wado-ryu"});

        items.at(8)->toItem()->setText("1");
        items.at(8)->toItem()->setTextAlignment(Qt::AlignCenter);

        foreach (auto* item, items) {
            row_ptr->append(item);
        }
    }
}

void setupRow_PeopleKata(gTableWidgetRow* row_ptr) {
    if (row_ptr != nullptr) {
        // NOTE: automatic downcasting
        QList<gTableWidgetBase*> items = //
            {
                new gTableWidgetItem(row_ptr), // 0 Cognome
                new gTableWidgetItem(row_ptr), // 1 Nome
                new gTableWidgetItem(row_ptr), // 2 Categoria
                new gTableWidgetIcon(row_ptr), // 3 Grado
                new gTableWidgetItem(row_ptr), // 4 Società
                new gTableWidgetItem(row_ptr), // 5 Stile
            };

        // items.at(0)->toItem()->setFlags(Qt::ItemIsEnabled);
        items.at(2)->toItem()->setTextAlignment(Qt::AlignCenter);

        items.at(3)->toIcon()->images() = //
            {QPixmap(":/res/images/beld_white.png"),
             QPixmap(":/res/images/beld_white_yellow.png"),
             QPixmap(":/res/images/beld_yellow.png"),
             QPixmap(":/res/images/beld_yellow_orange.png"),
             QPixmap(":/res/images/beld_orange.png"),
             QPixmap(":/res/images/beld_orange_green.png"),
             QPixmap(":/res/images/beld_green.png"),
             QPixmap(":/res/images/beld_green_blue.png"),
             QPixmap(":/res/images/beld_blue.png"),
             QPixmap(":/res/images/beld_blue_brown.png"),
             QPixmap(":/res/images/beld_brown.png"),
             QPixmap(":/res/images/beld_brown_black.png"),
             QPixmap(":/res/images/beld_black.png")};

        items.at(5)->toItem()->setTextAlignment(Qt::AlignCenter);

        foreach (auto* item, items) {
            row_ptr->append(item);
        }
    }
}
