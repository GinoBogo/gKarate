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

#include "widgets/gTableWidgetBase.hpp"
#include "widgets/gTableWidgetRow.hpp"

#include <qcontainerfwd.h>
#include <qforeach.h>
#include <qlist.h>
#include <qnamespace.h>
#include <qpixmap.h>
#include <qsize.h>
#include <qstring.h>

QStringList RANK_MAP;

void setupRankMap() {
    RANK_MAP = QStringList{
        QObject::tr("WHITE"),         //  0
        QObject::tr("WHITE-YELLOW"),  //  1
        QObject::tr("YELLOW"),        //  2
        QObject::tr("YELLOW-ORANGE"), //  3
        QObject::tr("ORANGE"),        //  4
        QObject::tr("ORANGE-GREEN"),  //  5
        QObject::tr("GREEN"),         //  6
        QObject::tr("GREEN-BLUE"),    //  7
        QObject::tr("BLUE"),          //  8
        QObject::tr("BLUE-BROWN"),    //  9
        QObject::tr("BROWN"),         // 10
        QObject::tr("BROWN-BLACK"),   // 11
        QObject::tr("BLACK")          // 12
    };
}

void setupRow_Full(gTableWidgetRow* row_ptr) {
    if (row_ptr != nullptr) {
        // NOTE: automatic downcasting
        QList<gTableWidgetBase*> const items = //
            {new gTableWidgetItem(row_ptr),    // 0 Surname
             new gTableWidgetItem(row_ptr),    // 1 Name
             new gTableWidgetDate(row_ptr),    // 2 Birthday
             new gTableWidgetCBox(row_ptr),    // 3 Category
             new gTableWidgetCBox(row_ptr),    // 4 Rank
             new gTableWidgetCBox(row_ptr),    // 5 Practice
             new gTableWidgetCBox(row_ptr),    // 6 Style
             new gTableWidgetItem(row_ptr),    // 7 Society
             new gTableWidgetItem(row_ptr)};   // 8 Reference

        items.at(2)->toDate()->setDate("31/12/2016");

        items.at(3)->toCBox()->addItems( //
            {QObject::tr("6 ÷ 8 age"),   //
             QObject::tr("9 ÷ 10 age"),  //
             QObject::tr("11 ÷ 12 age"), //
             QObject::tr("13 ÷ 14 age"), //
             QObject::tr("15 ÷ 17 age"), //
             QObject::tr("18 ÷ 21 age"), //
             QObject::tr("22 ÷ 35 age"), //
             QObject::tr("36 ÷ 45 age"), //
             QObject::tr("+45 age")});

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

        auto N = (int)items.at(4)->toCBox()->images().count();
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

void setupRow_Mini(gTableWidgetRow* row_ptr) {
    if (row_ptr != nullptr) {
        // NOTE: automatic downcasting
        QList<gTableWidgetBase*> const items = //
            {
                new gTableWidgetItem(row_ptr), // 0 Surname
                new gTableWidgetItem(row_ptr), // 1 Name
                new gTableWidgetItem(row_ptr), // 2 Category
                new gTableWidgetIcon(row_ptr), // 3 Rank
                new gTableWidgetItem(row_ptr), // 4 Society
                new gTableWidgetItem(row_ptr), // 5 Style
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

/* =============================================================================
   End of file
 */
