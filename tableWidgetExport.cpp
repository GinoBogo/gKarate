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
#include "xlsxrichstring.h"

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
                auto rank = row->at(MINI_RANK)->toIcon()->index().toInt();
                auto rem  = rank % 2;
                rank += rem;

                dst_record.category = row->at(MINI_CATEGORY)->toItem()->text();
                dst_record.rank     = RANK_MAP[rank];
            }

            const auto athlete = //
                QString("%1 %2;%3;%4")
                    .arg(row->at(MINI_SURNAME)->toItem()->text(), //
                         row->at(MINI_NAME __)->toItem()->text(), //
                         row->at(MINI_SOCIETY)->toItem()->text(), //
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

    rw = std::max(0, rw - 1);
    ch = std::max(0, ch - 1);

    auto _r2 = r1 + rw;
    auto _c2 = c1 + ch;

    CellRange range(r1, c1, _r2, _c2);
    document.mergeCells(range, format);

    if (r2 != nullptr) {
        *r2 = _r2 + 1;
    }

    if (c2 != nullptr) {
        *c2 = _c2 + 1;
    }
}

void gXlsx::createSheetRegister(QXlsx::Document& document, PeopleRecord& record, int sheet) {
    document.workbook()->setHtmlToRichStringEnabled(true);

    auto shift_col = 3.0;
    auto scale_col = 4.5;
    auto shift_row = 14.0;
    auto scale_row = 16.0;

    // clang-format off
    document.setRowHeight(1, shift_row);

    document.setColumnWidth(1,  1, shift_col);
    document.setColumnWidth(2, 21, scale_col);

    CellRange range_1_( 2,  2,  4, 21);
    CellRange range_2_( 5,  2,  8, 21);
    CellRange range_3_( 9,  2, 10, 21);
    CellRange range_4A(11,  2, 13, 11);
    CellRange range_4B(11, 12, 13, 21);
    CellRange range_5A(14,  2, 15,  3);
    CellRange range_5B(14,  4, 15, 10);
    CellRange range_5C(14, 11, 15, 17);
    CellRange range_5D(14, 18, 15, 21);
    // clang-format on

    QColor frame_color;
    if (record.practice == "KATA") {
        frame_color = color_kata;
    }
    else {
        frame_color = color_kumite;
    }

    Format frame_center;
    frame_center.setBorderStyle(Format::BorderMedium);
    frame_center.setVerticalAlignment(Format::AlignVCenter);
    frame_center.setHorizontalAlignment(Format::AlignHCenter);
    frame_center.setPatternBackgroundColor(frame_color);

    document.mergeCells(range_1_, frame_center);
    document.mergeCells(range_2_, frame_center);
    document.mergeCells(range_3_, frame_center);
    document.mergeCells(range_4A, frame_center);
    document.mergeCells(range_4B, frame_center);
    document.mergeCells(range_5A, frame_center);
    document.mergeCells(range_5B, frame_center);
    document.mergeCells(range_5C, frame_center);
    document.mergeCells(range_5D, frame_center);

    Format header_1(frame_center);
    header_1.setFontBold(true);
    header_1.setFontSize(18);

    Format header_2(frame_center);
    header_2.setFontBold(true);
    header_2.setFontSize(14);

    Format header_3(frame_center);
    header_3.setFontBold(true);
    header_3.setFontSize(13);

    const auto& category = QString("CATEGORIA:  %1").arg(record.category);
    const auto& rank     = QString("GRADO:  %1").arg(record.rank);
    // clang-format off
    document.write( 2,  2, record.title           , header_1);
    document.write( 5,  2, "VERBALE DI ISCRIZIONE", header_1);
    document.write( 9,  2, record.practice        , header_1);
    document.write(11,  2, category               , header_2);
    document.write(11, 12, rank                   , header_2);
    document.write(14,  2, "NUM."                 , header_3);
    document.write(14,  4, "COGNOME E NOME"       , header_3);
    document.write(14, 11, "SOCIETA'"             , header_3);
    document.write(14, 18, "STILE"                , header_3);
    // clang-format on

    Format lines_center;
    lines_center.setBorderStyle(Format::BorderThin);
    lines_center.setVerticalAlignment(Format::AlignVCenter);
    lines_center.setHorizontalAlignment(Format::AlignHCenter);
    lines_center.setFontSize(11);

    Format lines_left;
    lines_left.setBorderStyle(Format::BorderThin);
    lines_left.setVerticalAlignment(Format::AlignVCenter);
    lines_left.setHorizontalAlignment(Format::AlignLeft);
    lines_left.setFontSize(11);

    for (int i = 1; i <= max_register_lines; ++i) {
        document.setRowHeight(15 + i, scale_row);
        // clang-format off
        CellRange range_A(15 + i,  2, 15 + i,  3);
        CellRange range_B(15 + i,  4, 15 + i, 10);
        CellRange range_C(15 + i, 11, 15 + i, 17);
        CellRange range_D(15 + i, 18, 15 + i, 21);

        document.mergeCells(range_A, lines_center); // Numero
        document.mergeCells(range_B, lines_left  ); // Cognome e Nome
        document.mergeCells(range_C, lines_left  ); // Società
        document.mergeCells(range_D, lines_center); // Stile
        // clang-format on

        auto number = QString::number(i + (sheet - 1) * max_register_lines);
        document.write(15 + i, 2, number);
    }

    auto N = record.athletes.count();
    for (decltype(N) i{0}; i < N; ++i) {
        auto athlete = record.athletes.at(i).split(";", Qt::SkipEmptyParts);
        if (athlete.count() > 2) {
            document.write(16 + i, 04, athlete.at(0));
            document.write(16 + i, 11, athlete.at(1));
            document.write(16 + i, 18, athlete.at(2));
        }
    }
}

void __createTitle_evaluateKata(QXlsx::Document& document, int row) {
    Format frame;
    frame.setBorderStyle(Format::BorderThin);
    frame.setVerticalAlignment(Format::AlignVCenter);
    frame.setHorizontalAlignment(Format::AlignHCenter);
    frame.setPatternBackgroundColor(color_kata);
    frame.setFontBold(true);
    frame.setFontSize(9);

    int c2;
    __merge_cells(document, frame, row, 2, 1, 9, 0, &c2);
    document.write(row, c2 - 9, "COGNOME E NOME");

    __merge_cells(document, frame, row, c2, 1, 9, 0, &c2);
    document.write(row, c2 - 9, "SOCIETA' E STILE");

    __merge_cells(document, frame, row, c2, 1, 10, 0, &c2);
    document.write(row, c2 - 10, "1° KATA");

    __merge_cells(document, frame, row, c2, 1, 3, 0, &c2);
    document.write(row, c2 - 3, "NOTE");

    __merge_cells(document, frame, row, c2, 1, 10, 0, &c2);
    document.write(row, c2 - 10, "2° KATA");

    __merge_cells(document, frame, row, c2, 1, 3, 0, &c2);
    document.write(row, c2 - 3, "NOTE");

    __merge_cells(document, frame, row, c2, 1, 10, 0, &c2);
    document.write(row, c2 - 10, "3° KATA");

    __merge_cells(document, frame, row, c2, 1, 3, 0, &c2);
    document.write(row, c2 - 3, "NOTE");

    __merge_cells(document, frame, row, c2, 1, 9, 0, &c2);
    document.write(row, c2 - 9, "CLASSIFICA FINALE");
}

void __createPodium_evaluateKata(QXlsx::Document& document, int row, int col) {
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

    int ri = row;

    __merge_cells(document, frame, ri, col, 2, 9, &ri);
    document.write(ri - 2, col, "PODIO . . . . . . . . . . . . .");

    for (int i = 1; i <= 4; ++i) {
        __merge_cells(document, lines, ri, col, 2, 9, &ri);
        document.write(ri - 2, col, QString("%1.").arg(i));
    }

    __merge_cells(document, frame, ri, col, 2, 9, &ri, 0);
    document.write(ri - 2, col, "PODIO . . . . . . . . . . . . .");

    for (int i = 1; i <= 4; ++i) {
        __merge_cells(document, lines, ri, col, 2, 9, &ri);
        document.write(ri - 2, col, QString("%1.").arg(i));
    }

    __merge_cells(document, frame, ri, col, 2, 9, &ri);
    document.write(ri - 2, col, "SPAREGGI");

    for (int i = 1; i <= 5; ++i) {
        __merge_cells(document, lines, ri, col, 2, 9, &ri);
        document.write(ri - 2, col, QString("%1.").arg(i));
    }
}

void __createRow_evaluateKata(QXlsx::Document& document, int row) {
    Format frame;
    frame.setBorderStyle(Format::BorderThin);
    frame.setVerticalAlignment(Format::AlignVCenter);
    frame.setHorizontalAlignment(Format::AlignLeft);
    frame.setFontSize(9);

    const auto row_1 = (row * 2) + 3;
    const auto row_2 = row_1 + 1;

    auto make_col_t1 = [&](int r1, int c1, int r2, int cw, int* cn) {
        --cw;
        auto _c2 = c1 + cw;

        CellRange cr(r1, c1, r2, _c2);
        document.mergeCells(cr, frame);

        if (cn != 0) {
            *cn = _c2 + 1;
        }
    };

    auto make_col_t2 = [&](int r1, int c1, int r2, int cw, int* cn) {
        --cw;
        auto _c1 = c1;
        auto _c2 = c1 + cw;

        for (int i = 0; i < 5; ++i) {
            CellRange cr(r1, _c1, r2, _c2);
            document.mergeCells(cr, frame);
            _c1 = _c2 + 1;
            _c2 = _c1 + cw;
        }

        if (cn != 0) {
            *cn = _c2 + 1;
        }
    };

    // clang-format off
    int cn;
    make_col_t1(row_1,  2, row_2, 9, &cn);
    make_col_t1(row_1, cn, row_1, 9,   0);
    make_col_t1(row_2, cn, row_2, 9, &cn);

    make_col_t2(row_1, cn, row_1, 2,   0);
    make_col_t1(row_2, cn, row_2, 7, &cn);
    make_col_t1(row_2, cn, row_2, 3, &cn);
    make_col_t1(row_1, cn, row_2, 3, &cn);

    make_col_t2(row_1, cn, row_1, 2,   0);
    make_col_t1(row_2, cn, row_2, 7, &cn);
    make_col_t1(row_2, cn, row_2, 3, &cn);
    make_col_t1(row_1, cn, row_2, 3, &cn);

    make_col_t2(row_1, cn, row_1, 2,   0);
    make_col_t1(row_2, cn, row_2, 7, &cn);
    make_col_t1(row_2, cn, row_2, 3, &cn);
    make_col_t1(row_1, cn, row_2, 3, &cn);
    // clang-format on
}

void __createSheet_evaluateKata(QXlsx::Document& document, gXlsx::PeopleRecord& record, int sheet) {
    // clang-format off
    auto shift_col =  3.0;
    auto scale_col =  2.0;
    auto shift_row = 14.0;
    auto scale_row = 14.5;

    document.setRowHeight(1,  1, shift_row);
    document.setRowHeight(2, 64, scale_row);

    document.setColumnWidth(1,   1, shift_col);
    document.setColumnWidth(2, 120, scale_col);
    // clang-format on

    __createTitle_evaluateKata(document, 2);
    __createPodium_evaluateKata(document, 3, 59);

    for (int i = 0; i < gXlsx::max_evaluate_lines; ++i) {
        __createRow_evaluateKata(document, i);
    }

    auto N = record.athletes.count();
    for (decltype(N) i{0}; i < N; ++i) {
        auto athlete = record.athletes.at(i).split(";", Qt::SkipEmptyParts);
        if (athlete.count() > 2) {
            document.write(3 + (i * 2), __ 2, athlete.at(0));
            document.write(3 + (i * 2), _ 11, athlete.at(1));
            document.write(4 + (i * 2), _ 11, athlete.at(2));
        }
    }
}

void __createSheet_evaluateKumite(QXlsx::Document& document, gXlsx::PeopleRecord& record, int sheet) {}

void gXlsx::createSheetEvaluate(QXlsx::Document& document, PeopleRecord& record, int sheet) {
    document.workbook()->setHtmlToRichStringEnabled(true);

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
