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

#include "tableWidgetSetup.hpp"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxdocument.h"
#include "xlsxformat.h"

using namespace QXlsx;

const auto color_kata   = QColor(245, 245, 255);
const auto color_kumite = QColor(245, 255, 245);

#define _
#define __
#define ___
#define ____

void gXlsx::decodeTableWidget(gTableWidget* src_table, PeopleRecord& dst_record) {
    if (src_table != nullptr) {
        dst_record.athletes.clear();

        const auto* rows = src_table->rows();

        auto N = rows->count();
        for (decltype(N) i{0}; i < N; ++i) {
            const auto* row = rows->at(i);

            if (i == 0) {
                auto rank  = row->at(MINI_RANK)->toIcon()->index().toInt();
                auto rem   = rank % 2;
                rank      += rem;

                dst_record.category = row->at(MINI_CATEGORY)->toItem()->text();
                dst_record.rank     = RANK_MAP[rank];
            }

            const auto athlete = QString("%1;%2;%3;%4")
                                     .arg(row->at(MINI_SURNAME)->toItem()->text(),
                                          row->at(MINI_NAME __)->toItem()->text(),
                                          row->at(MINI_SOCIETY)->toItem()->text(),
                                          row->at(MINI_STYLE _)->toItem()->text());

            dst_record.athletes.append(athlete);
        }
    }
}

void __merge_cells(QXlsx::Document&     document, //
                   const QXlsx::Format& format,
                   int                  r1,
                   int                  c1,
                   int                  rw,
                   int                  ch,
                   int*                 r2 = nullptr,
                   int*                 c2 = nullptr) {

    const auto _r2 = r1 + std::max(0, rw - 1);
    const auto _c2 = c1 + std::max(0, ch - 1);

    CellRange range(r1, c1, _r2, _c2);
    document.mergeCells(range, format);

    if (r2 != nullptr) {
        *r2 = _r2 + 1;
    }

    if (c2 != nullptr) {
        *c2 = _c2 + 1;
    }
}

void __createTitle_registerCommon(QXlsx::Document& document, gXlsx::PeopleRecord& record, int r1, int c1) {
    QColor frame_color = (record.practice == "KATA") ? color_kata : color_kumite;

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
    header_3.setFontSize(13);

    const auto& category = QString("CATEGORIA:  %1").arg(record.category);
    const auto& rank     = QString("GRADO:  %1").arg(record.rank);

    int r2, c2;

    __merge_cells(document, frame_center, r1, c1, 3, 20, &r2, 0);
    document.write(r1, c1, record.title, header_1);

    __merge_cells(document, frame_center, r2, c1, 4, 20, &r2, 0);
    document.write(r2 - 4, c1, "VERBALE DI ISCRIZIONE", header_1);

    __merge_cells(document, frame_center, r2, c1, 2, 20, &r2, 0);
    document.write(r2 - 2, c1, record.practice, header_1);

    __merge_cells(document, frame_center, r2, c1, 3, 10, 0, &c2);
    document.write(r2, c2 - 10, category, header_2);

    __merge_cells(document, frame_center, r2, c2, 3, 10, &r2, 0);
    document.write(r2 - 3, c2, rank, header_2);

    __merge_cells(document, frame_center, r2, c1, 2, 2, 0, &c2);
    document.write(r2, c2 - 2, "NUM.", header_3);

    __merge_cells(document, frame_center, r2, c2, 2, 7, 0, &c2);
    document.write(r2, c2 - 7, "COGNOME E NOME", header_3);

    __merge_cells(document, frame_center, r2, c2, 2, 7, 0, &c2);
    document.write(r2, c2 - 7, "SOCIETA'", header_3);

    __merge_cells(document, frame_center, r2, c2, 2, 4, 0, 0);
    document.write(r2, c2, "STILE", header_3);
}

void __createRow_registerCommon(QXlsx::Document& document, int index, int r1, int c1) {
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
    __merge_cells(document, lines_center, r1, c1, 1, 2, 0, &c1);
    __merge_cells(document, lines_left  , r1, c1, 1, 7, 0, &c1);
    __merge_cells(document, lines_left  , r1, c1, 1, 7, 0, &c1);
    __merge_cells(document, lines_center, r1, c1, 1, 4, 0, 0);
    // clang-format on

    document.write(r1, 2, QString("%1.").arg(index));
}

void gXlsx::createSheetRegister(QXlsx::Document& document, PeopleRecord& record, int sheet) {
    auto shift_row = 14.0;
    auto scale_row = 16.5;

    auto shift_col = 3.0;
    auto scale_col = 4.5;

    document.setRowHeight(1, 1, shift_row);
    document.setRowHeight(2, 64, scale_row);

    document.setColumnWidth(1, 1, shift_col);
    document.setColumnWidth(2, 96, scale_col);

    __createTitle_registerCommon(document, record, 2, 2);

    for (int i = 0; i < max_register_lines; ++i) {
        auto index = (i + 1) + (sheet - 1) * gXlsx::max_register_lines;
        __createRow_registerCommon(document, index, 16 + i, 2);
    }

    auto N = record.athletes.count();
    for (decltype(N) i{0}; i < N; ++i) {
        auto athlete = record.athletes.at(i).split(";", Qt::SkipEmptyParts);
        if (athlete.count() > 2) {
            document.write(16 + i, 04, athlete.at(0) + ", " + athlete.at(1));
            document.write(16 + i, 11, athlete.at(2));
            document.write(16 + i, 18, athlete.at(3));
        }
    }
}

void __createTitle_evaluateKata(QXlsx::Document& document, int r1, int c1) {
    Format frame;
    frame.setBorderStyle(Format::BorderThin);
    frame.setVerticalAlignment(Format::AlignVCenter);
    frame.setHorizontalAlignment(Format::AlignHCenter);
    frame.setPatternBackgroundColor(color_kata);
    frame.setFontBold(true);
    frame.setFontSize(9);

    int c2;
    __merge_cells(document, frame, r1, c1, 1, 8, 0, &c2);
    document.write(r1, c2 - 8, "COGNOME E NOME");

    __merge_cells(document, frame, r1, c2, 1, 10, 0, &c2);
    document.write(r1, c2 - 10, "SOCIETA' E STILE");

    __merge_cells(document, frame, r1, c2, 1, 10, 0, &c2);
    document.write(r1, c2 - 10, "1° KATA");

    __merge_cells(document, frame, r1, c2, 1, 3, 0, &c2);
    document.write(r1, c2 - 3, "NOTE");

    __merge_cells(document, frame, r1, c2, 1, 10, 0, &c2);
    document.write(r1, c2 - 10, "2° KATA");

    __merge_cells(document, frame, r1, c2, 1, 3, 0, &c2);
    document.write(r1, c2 - 3, "NOTE");

    __merge_cells(document, frame, r1, c2, 1, 10, 0, &c2);
    document.write(r1, c2 - 10, "3° KATA");

    __merge_cells(document, frame, r1, c2, 1, 3, 0, &c2);
    document.write(r1, c2 - 3, "NOTE");

    __merge_cells(document, frame, r1, c2, 1, 9, 0, &c2);
    document.write(r1, c2 - 9, "CLASSIFICA FINALE");
}

void __createPodium_evaluateKata(QXlsx::Document& document, int r1, int c1) {
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

    __merge_cells(document, frame, r1, c1, 2, 9, &r1);
    document.write(r1 - 2, c1, "PODIO  . . . . . . . . . . . . .");

    for (int i = 1; i <= 4; ++i) {
        __merge_cells(document, lines, r1, c1, 2, 9, &r1);
        document.write(r1 - 2, c1, QString("%1.").arg(i));
    }

    __merge_cells(document, frame, r1, c1, 2, 9, &r1, 0);
    document.write(r1 - 2, c1, "PODIO  . . . . . . . . . . . . .");

    for (int i = 1; i <= 4; ++i) {
        __merge_cells(document, lines, r1, c1, 2, 9, &r1);
        document.write(r1 - 2, c1, QString("%1.").arg(i));
    }

    __merge_cells(document, frame, r1, c1, 2, 9, &r1);
    document.write(r1 - 2, c1, "SPAREGGI");

    for (int i = 1; i <= 5; ++i) {
        __merge_cells(document, lines, r1, c1, 2, 9, &r1);
        document.write(r1 - 2, c1, QString("%1.").arg(i));
    }
}

void __createRow_evaluateKata(QXlsx::Document& document, int r1, int c1) {
    Format frame;
    frame.setBorderStyle(Format::BorderThin);
    frame.setVerticalAlignment(Format::AlignVCenter);
    frame.setHorizontalAlignment(Format::AlignLeft);
    frame.setFontSize(8);
    frame.setTextWrap(true);

    // clang-format off
    int c2;
    __merge_cells(document, frame, r1    , c1, 2,  8, 0, &c2);
    __merge_cells(document, frame, r1    , c2, 1, 10, 0,   0);
    __merge_cells(document, frame, r1 + 1, c2, 1, 10, 0, &c2);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 5; ++j) {
            __merge_cells(document, frame, r1, c2, 1, 2, 0, &c2);
        }
        c2 -= 2 * 5;
        __merge_cells(document, frame, r1 + 1, c2, 1, 7, 0, &c2);
        __merge_cells(document, frame, r1 + 1, c2, 1, 3, 0, &c2);
        __merge_cells(document, frame, r1    , c2, 2, 3, 0, &c2);
    }
    // clang-format on
}

void __createSheet_evaluateKata(QXlsx::Document& document, gXlsx::PeopleRecord& record, int sheet) {
    // clang-format off
    auto shift_row = 14.0;
    auto scale_row = 14.5;
    document.setRowHeight(1,  1, shift_row);
    document.setRowHeight(2, 64, scale_row);
    
    auto shift_col =  3.0;
    auto scale_col =  2.0;
    document.setColumnWidth(1,  1, shift_col);
    document.setColumnWidth(2, 96, scale_col);
    // clang-format on

    __createTitle_evaluateKata(document, 2, 2);
    __createPodium_evaluateKata(document, 3, 59);

    for (int i = 0; i < gXlsx::max_evaluate_lines; ++i) {
        __createRow_evaluateKata(document, 3 + (i * 2), 2);
    }

    auto N = record.athletes.count();
    for (decltype(N) i{0}; i < N; ++i) {
        auto athlete = record.athletes.at(i).split(";", Qt::SkipEmptyParts);
        if (athlete.count() > 2) {
            document.write(3 + (i * 2), __ 2, athlete.at(0) + "\n" + athlete.at(1));
            document.write(3 + (i * 2), _ 10, athlete.at(2));
            document.write(4 + (i * 2), _ 10, athlete.at(3));
        }
    }
}

void __createSheet_evaluateKumite(QXlsx::Document& document, gXlsx::PeopleRecord& record, int sheet) {
}

void gXlsx::createSheetEvaluate(QXlsx::Document& document, PeopleRecord& record, int sheet) {
    if (record.practice == "KATA") {
        __createSheet_evaluateKata(document, record, sheet);
        return;
    }

    if (record.practice == "KUMITE") {
        __createSheet_evaluateKumite(document, record, sheet);
        return;
    }

    qDebug("[E200] wrong condition detected");
}
