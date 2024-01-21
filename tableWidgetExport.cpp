/*!
 * =============================================================================
 *
 *   @file: tableWidgetExport.cpp
 *
 *   @date: January, 2024
 *
 * @author: Gino Francesco Bogo
 *
 * =============================================================================
 */

#include "tableWidgetExport.hpp"

#include "qobject.h"
#include "qxlsx/xlsxcellrange.h"
#include "qxlsx/xlsxdocument.h"
#include "qxlsx/xlsxformat.h"
#include "tableWidgetSetup.hpp"
#include "widgets/gTableWidget.hpp"

#include <algorithm>
#include <qcolor.h>
#include <qlogging.h>
#include <qnamespace.h>
#include <qstring.h>

using namespace QXlsx;

const auto color_kata   = QColor(235, 235, 255);
const auto color_kumite = QColor(235, 255, 235);

void gXlsx::decodeTableWidget(gTableWidget* src_table, PeopleRecord& dst_record) {
    if (src_table != nullptr) {
        dst_record.athletes.clear();

        const auto* rows = src_table->rows();

        auto N = rows->count();
        for (decltype(N) i(0); i < N; ++i) {
            const auto* row = rows->at(i);

            if (i == 0) {
                auto rank  = row->at(MINI_RANK)->toIcon()->index().toInt();
                auto rem   = rank % 2;
                rank      += rem;

                dst_record.category = row->at(MINI_CATEGORY)->toItem()->text();
                dst_record.rank     = RANK_MAP.at(rank);
            }
            // clang-format off
            const auto athlete = QString("%1;%2;%3;%4")
                                     .arg(row->at(MINI_SURNAME)->toItem()->text(),
                                          row->at(MINI_NAME   )->toItem()->text(),
                                          row->at(MINI_SOCIETY)->toItem()->text(),
                                          row->at(MINI_STYLE  )->toItem()->text());
            // clang-format on
            dst_record.athletes.append(athlete);
        }
    }
}

// REVIEW the number of function arguments exceeds the limit of 4.
void merge_cells(QXlsx::Document&     document, //
                 const QXlsx::Format& format,
                 int                  r1,
                 int                  c1,
                 int                  rh,
                 int                  cw,
                 int*                 r2 = nullptr,
                 int*                 c2 = nullptr) {

    const auto _r2 = r1 + std::max(0, rh - 1);
    const auto _c2 = c1 + std::max(0, cw - 1);

    const CellRange range(r1, c1, _r2, _c2);
    document.mergeCells(range, format);

    if (r2 != nullptr) {
        *r2 = _r2 + 1;
    }

    if (c2 != nullptr) {
        *c2 = _c2 + 1;
    }
}

void createTitle_registerCommon(QXlsx::Document& document, gXlsx::PeopleRecord& record, int r1, int c1) {
    const QColor frame_color = (record.practice == "KATA") ? color_kata : color_kumite;

    Format frame_center;
    frame_center.setBorderStyle(Format::BorderMedium);
    frame_center.setVerticalAlignment(Format::AlignVCenter);
    frame_center.setHorizontalAlignment(Format::AlignHCenter);
    frame_center.setPatternBackgroundColor(frame_color);
    frame_center.setFontBold(true);

    Format header_1(frame_center);
    header_1.setFontSize(18);

    Format header_2(frame_center);
    header_2.setFontSize(14);

    Format header_3(frame_center);
    header_3.setFontSize(11);

    const auto& category = QString(QObject::tr("CATEGORY:  %1")).arg(record.category);
    const auto& rank     = QString(QObject::tr("RANK:  %1")).arg(record.rank);

    int r2 = 0;
    int c2 = 0;

    document.write(r1, c1, record.title);
    merge_cells(document, header_1, r1, c1, 3, 20, &r2, nullptr);

    document.write(r2, c1, QObject::tr("REGISTRATION REPORT"));
    merge_cells(document, header_1, r2, c1, 3, 20, &r2, nullptr);

    document.write(r2, c1, record.practice);
    merge_cells(document, header_1, r2, c1, 2, 20, &r2, nullptr);

    document.write(r2, c1, category);
    merge_cells(document, header_2, r2, c1, 2, 10, nullptr, &c2);

    document.write(r2, c2, rank);
    merge_cells(document, header_2, r2, c2, 2, 10, &r2, nullptr);

    document.write(r2, c1, QObject::tr("NUM."));
    merge_cells(document, header_3, r2, c1, 1, 2, nullptr, &c2);

    document.write(r2, c2, QObject::tr("SURNAME, NAME"));
    merge_cells(document, header_3, r2, c2, 1, 7, nullptr, &c2);

    document.write(r2, c2, QObject::tr("SOCIETY"));
    merge_cells(document, header_3, r2, c2, 1, 7, nullptr, &c2);

    document.write(r2, c2, QObject::tr("STYLE"));
    merge_cells(document, header_3, r2, c2, 1, 4, nullptr, nullptr);
}

void createRow_registerCommon(QXlsx::Document& document, int index, int r1, int c1) {
    Format lines_center; // Index, Style
    lines_center.setBorderStyle(Format::BorderThin);
    lines_center.setVerticalAlignment(Format::AlignVCenter);
    lines_center.setHorizontalAlignment(Format::AlignHCenter);
    lines_center.setFontSize(11);

    Format lines_left; // Identity, Society
    lines_left.setBorderStyle(Format::BorderThin);
    lines_left.setVerticalAlignment(Format::AlignVCenter);
    lines_left.setHorizontalAlignment(Format::AlignLeft);
    lines_left.setFontSize(11);

    // clang-format off
    merge_cells(document, lines_center, r1, c1, 1, 2, nullptr,     &c1);
    merge_cells(document, lines_left  , r1, c1, 1, 7, nullptr,     &c1);
    merge_cells(document, lines_left  , r1, c1, 1, 7, nullptr,     &c1);
    merge_cells(document, lines_center, r1, c1, 1, 4, nullptr, nullptr);
    // clang-format on

    document.write(r1, 2, QString("%1.").arg(index));
}

void gXlsx::createSheetRegister(QXlsx::Document& document, PeopleRecord& record, int sheet) {
    auto row_shift = 14.0;
    auto row_scale = 16.5;
    document.setRowHeight(1, 1, row_shift);
    document.setRowHeight(2, 64, row_scale);

    auto col_shift = 3.0;
    auto col_scale = 4.5;
    document.setColumnWidth(1, 1, col_shift);
    document.setColumnWidth(2, 96, col_scale);

    createTitle_registerCommon(document, record, 2, 2);

    for (int i = 0; i < max_register_lines; ++i) {
        auto index = (i + 1) + (sheet - 1) * gXlsx::max_register_lines;
        createRow_registerCommon(document, index, 13 + i, 2);
    }

    auto N = (int)record.athletes.count();
    for (decltype(N) i(0); i < N; ++i) {
        auto athlete = record.athletes.at(i).split(";", Qt::SkipEmptyParts);
        if (athlete.count() > 2) {
            document.write(13 + i, 04, athlete.at(0) + ", " + athlete.at(1));
            document.write(13 + i, 11, athlete.at(2));
            document.write(13 + i, 18, athlete.at(3));
        }
    }
}

void createTitle_evaluateKata(QXlsx::Document& document, int r1, int c1) {
    Format frame;
    frame.setBorderStyle(Format::BorderThin);
    frame.setVerticalAlignment(Format::AlignVCenter);
    frame.setHorizontalAlignment(Format::AlignHCenter);
    frame.setPatternBackgroundColor(color_kata);
    frame.setFontBold(true);
    frame.setFontSize(9);

    int c2 = 0;

    merge_cells(document, frame, r1, c1, 1, 8, nullptr, &c2);
    document.write(r1, c2 - 8, QObject::tr("SURNAME, NAME"));

    merge_cells(document, frame, r1, c2, 1, 10, nullptr, &c2);
    document.write(r1, c2 - 10, QObject::tr("SOCIETY, STYLE"));

    merge_cells(document, frame, r1, c2, 1, 10, nullptr, &c2);
    document.write(r1, c2 - 10, QObject::tr("1° KATA"));

    merge_cells(document, frame, r1, c2, 1, 3, nullptr, &c2);
    document.write(r1, c2 - 3, QObject::tr("NOTE"));

    merge_cells(document, frame, r1, c2, 1, 10, nullptr, &c2);
    document.write(r1, c2 - 10, QObject::tr("2° KATA"));

    merge_cells(document, frame, r1, c2, 1, 3, nullptr, &c2);
    document.write(r1, c2 - 3, QObject::tr("NOTE"));

    merge_cells(document, frame, r1, c2, 1, 10, nullptr, &c2);
    document.write(r1, c2 - 10, QObject::tr("3° KATA"));

    merge_cells(document, frame, r1, c2, 1, 3, nullptr, &c2);
    document.write(r1, c2 - 3, QObject::tr("NOTE"));

    merge_cells(document, frame, r1, c2, 1, 9, nullptr, &c2);
    document.write(r1, c2 - 9, QObject::tr("FINAL RANKING"));
}

void createPodium_evaluateKata(QXlsx::Document& document, int r1, int c1) {
    Format frame;
    frame.setBorderStyle(Format::BorderThin);
    frame.setVerticalAlignment(Format::AlignVCenter);
    frame.setHorizontalAlignment(Format::AlignHCenter);
    frame.setPatternBackgroundColor(color_kata);
    frame.setFontBold(true);
    frame.setFontSize(9);

    Format lines;
    lines.setBorderStyle(Format::BorderThin);
    lines.setVerticalAlignment(Format::AlignVCenter);
    lines.setHorizontalAlignment(Format::AlignLeft);
    lines.setFontSize(9);

    merge_cells(document, frame, r1, c1, 2, 9, &r1);
    document.write(r1 - 2, c1, QObject::tr("PODIUM  . . . . . . . . . . . ."));

    for (int i = 1; i <= 4; ++i) {
        merge_cells(document, lines, r1, c1, 2, 9, &r1);
        document.write(r1 - 2, c1, QString("%1.").arg(i));
    }

    merge_cells(document, frame, r1, c1, 2, 9, &r1);
    document.write(r1 - 2, c1, QObject::tr("PODIUM  . . . . . . . . . . . ."));

    for (int i = 1; i <= 4; ++i) {
        merge_cells(document, lines, r1, c1, 2, 9, &r1);
        document.write(r1 - 2, c1, QString("%1.").arg(i));
    }

    merge_cells(document, frame, r1, c1, 2, 9, &r1);
    document.write(r1 - 2, c1, QObject::tr("PLAY-OFF"));

    for (int i = 1; i <= 5; ++i) {
        merge_cells(document, lines, r1, c1, 2, 9, &r1);
        document.write(r1 - 2, c1, QString("%1.").arg(i));
    }
}

void createRow_evaluateKata(QXlsx::Document& document, int r1, int c1) {
    Format frame;
    frame.setBorderStyle(Format::BorderThin);
    frame.setVerticalAlignment(Format::AlignVCenter);
    frame.setHorizontalAlignment(Format::AlignLeft);
    frame.setFontSize(8);
    frame.setTextWrap(true);

    // clang-format off
    int c2 = 0;

    merge_cells(document, frame, r1, c1, 2,  8, nullptr, &c2);
    merge_cells(document, frame, r1, c2, 2, 10, nullptr, &c2);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 5; ++j) {
            merge_cells(document, frame, r1, c2, 1, 2, nullptr, &c2);
        }
        c2 -= 2 * 5;
        merge_cells(document, frame, r1 + 1, c2, 1, 7, nullptr, &c2);
        merge_cells(document, frame, r1 + 1, c2, 1, 3, nullptr, &c2);
        merge_cells(document, frame, r1    , c2, 2, 3, nullptr, &c2);
    }
    // clang-format on
}

void createSheet_evaluateKata(QXlsx::Document& document, gXlsx::PeopleRecord& record, int sheet) {
    (void)sheet;

    auto row_shift = 14.0;
    auto row_scale = 14.5;
    document.setRowHeight(1, 1, row_shift);
    document.setRowHeight(2, 64, row_scale);

    auto col_shift = 3.0;
    auto col_scale = 2.0;
    document.setColumnWidth(1, 1, col_shift);
    document.setColumnWidth(2, 96, col_scale);

    createTitle_evaluateKata(document, 2, 2);
    createPodium_evaluateKata(document, 3, 59);

    for (int i = 0; i < gXlsx::max_evaluate_lines; ++i) {
        createRow_evaluateKata(document, 3 + (i * 2), 2);
    }

    auto N = (int)record.athletes.count();
    for (decltype(N) i(0); i < N; ++i) {
        auto athlete = record.athletes.at(i).split(";", Qt::SkipEmptyParts);
        if (athlete.count() > 2) {
            // clang-format off
            document.write(3 + (i * 2),  2, athlete.at(0) + "\n" + athlete.at(1));
            document.write(3 + (i * 2), 10, athlete.at(2) + "\n" + athlete.at(3));
            // clang-format on
        }
    }
}

void createTitle_evaluateKumite(QXlsx::Document& document, int r1, int c1) {
    Format frame;
    frame.setBorderStyle(Format::BorderMedium);
    frame.setVerticalAlignment(Format::AlignVCenter);
    frame.setHorizontalAlignment(Format::AlignHCenter);
    frame.setPatternBackgroundColor(color_kumite);
    frame.setFontSize(9);
    frame.setFontBold(true);

    int c2 = 0;

    // clang-format off
    merge_cells(document, frame, r1, c1    , 3, 5, nullptr,     &c2);
    merge_cells(document, frame, r1, c2 + 1, 3, 5, nullptr, nullptr);
    // clang-format on

    r1 += 52;
    document.write(r1, c1, QObject::tr("3° CLASSIFIED"));
    merge_cells(document, frame, r1, c1, 3, 5, &r1);

    frame.setBorderStyle(Format::BorderThin);
    frame.setPatternBackgroundColor("white");
    merge_cells(document, frame, r1, c1, 3, 5, &r1);
    merge_cells(document, frame, r1, c1, 3, 5, &r1);
}

void createPodium_evaluateKumite(QXlsx::Document& document, int r1, int c1) {
    Format frame;
    frame.setVerticalAlignment(Format::AlignVCenter);
    frame.setHorizontalAlignment(Format::AlignHCenter);
    frame.setFontSize(9);
    frame.setFontBold(true);

    int ri = r1;
    for (int i = 0; i < 2; ++i) {
        frame.setBorderStyle(Format::BorderMedium);
        frame.setPatternBackgroundColor(color_kumite);
        document.write(ri, c1, QObject::tr("SEMI-FINAL"));
        merge_cells(document, frame, ri, c1, 3, 5, &ri);

        frame.setBorderStyle(Format::BorderThin);
        frame.setPatternBackgroundColor("white");
        merge_cells(document, frame, ri, c1, 3, 5, &ri);
        merge_cells(document, frame, ri, c1, 3, 5, &ri);
    }

    frame.setBorderStyle(Format::BorderMedium);
    frame.setPatternBackgroundColor(color_kumite);
    document.write(ri, c1, QObject::tr("FINAL"));
    merge_cells(document, frame, ri, c1, 3, 5, &ri);

    frame.setBorderStyle(Format::BorderThin);
    frame.setPatternBackgroundColor("white");
    merge_cells(document, frame, ri, c1, 3, 5, &ri);
    merge_cells(document, frame, ri, c1, 3, 5, &ri);

    frame.setBorderStyle(Format::BorderMedium);
    frame.setPatternBackgroundColor(color_kumite);
    document.write(ri, c1, QObject::tr("CUP STANDINGS"));
    merge_cells(document, frame, ri, c1, 3, 5, &ri);

    frame.setHorizontalAlignment(Format::AlignLeft);
    frame.setBorderStyle(Format::BorderThin);
    frame.setPatternBackgroundColor("white");
    for (int i = 1; i <= 4; ++i) {
        document.write(ri, c1, QString("%1.").arg(i));
        merge_cells(document, frame, ri, c1, 3, 5, &ri);
    }
}

void createRow_evaluateKumite(QXlsx::Document& document, int r1, int c1, int loop, int step) {
    Format frame;
    frame.setRightBorderStyle(Format::BorderThin);
    frame.setBottomBorderStyle(Format::BorderThin);
    frame.setVerticalAlignment(Format::AlignVCenter);
    frame.setHorizontalAlignment(Format::AlignLeft);
    frame.setFontSize(9);
    frame.setTextWrap(true);

    int ri = r1;
    for (int i = 0; i < loop; ++i) {
        merge_cells(document, frame, ri, c1, 2, 5, &ri);
        ri += step;
    }
}

void createSheet_evaluateKumite(QXlsx::Document& document, gXlsx::PeopleRecord& record, int sheet) {
    (void)sheet;

    auto row_shift = 14.0;
    auto row_scale = 8.0;
    document.setRowHeight(1, 1, row_shift);
    document.setRowHeight(2, 64, row_scale);

    auto col_shift = 3.0;
    auto col_scale = 4.5;
    document.setColumnWidth(1, 1, col_shift);
    document.setColumnWidth(2, 96, col_scale);

    createTitle_evaluateKumite(document, 2, 20);
    document.write(2, 20, QObject::tr("CATEGORY: ") + record.category);
    document.write(2, 26, QObject::tr("RANK: ") + record.rank);

    createPodium_evaluateKumite(document, 10, 26);

    // clang-format off
    createRow_evaluateKumite(document,  2,  2, 16,  2);
    createRow_evaluateKumite(document,  4,  8,  8,  6);
    createRow_evaluateKumite(document,  8, 14,  4, 14);  
    createRow_evaluateKumite(document, 16, 20,  2, 30);
    // clang-format on

    auto N = (int)record.athletes.count();
    for (decltype(N) i(0); i < N; ++i) {
        auto athlete = record.athletes.at(i).split(";", Qt::SkipEmptyParts);
        if (athlete.count() > 1) {
            document.write(2 + (i * 4), 2, athlete.at(0) + ", " + athlete.at(1));
        }
    }
}

void gXlsx::createSheetEvaluate(QXlsx::Document& document, PeopleRecord& record, int sheet) {
    if (record.practice == "KATA") {
        createSheet_evaluateKata(document, record, sheet);
        return;
    }

    if (record.practice == "KUMITE") {
        createSheet_evaluateKumite(document, record, sheet);
        return;
    }
}

/* =============================================================================
   End of file
 */
