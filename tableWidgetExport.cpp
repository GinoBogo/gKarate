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

#include "qnamespace.h"
#include "tableWidgetSetup.hpp"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxformat.h"
#include "xlsxworkbook.h"

using namespace QXlsx;

void gXlsx::decodeTableWidget(gTableWidget* src_table, PeopleRecord& dst_record) {
    if (src_table != nullptr) {
        dst_record.athletes.clear();

        const auto* rows = src_table->rows();

        auto N = rows->count();
        for (decltype(N) i{0}; i < N; ++i) {
            const auto* row = rows->at(i);

            const auto athlete = //
                QString("%1 %2; %3; %4")
                    .arg(row->at(MINI_SURNAME /**/)->toItem()->text(), //
                         row->at(MINI_NAME /*****/)->toItem()->text(), //
                         row->at(MINI_SOCIETY /**/)->toItem()->text(), //
                         row->at(MINI_STYLE /****/)->toItem()->text());

            dst_record.athletes.append(athlete);
        }
    }
}

void gXlsx::createSheet(QXlsx::Document& document, PeopleRecord& record) {
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

    Format frame_center;
    frame_center.setBorderStyle(Format::BorderMedium);
    frame_center.setVerticalAlignment(Format::AlignVCenter);
    frame_center.setHorizontalAlignment(Format::AlignHCenter);
    frame_center.setPatternBackgroundColor(QColor(245, 245, 245));

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

    // clang-format off
    document.write( 2,  2, record.title           , header_1);
    document.write( 5,  2, "VERBALE DI ISCRIZIONE", header_1);
    document.write( 9,  2, record.practice        , header_1);
    document.write(11,  2, "CATEGORIA"            , header_2);
    document.write(11, 12, "GRADO"                , header_2);
    document.write(14,  2, "NUM."                 , header_3);
    document.write(14,  4, "COGNOME E NOME"       , header_3);
    document.write(14, 11, "SOCIETA'"             , header_3);
    document.write(14, 18, "STILE"                , header_3);
    // clang-format on

    Format lines_center;
    lines_center.setBorderStyle(Format::BorderThin);
    lines_center.setVerticalAlignment(Format::AlignVCenter);
    lines_center.setHorizontalAlignment(Format::AlignHCenter);

    Format lines_left;
    lines_left.setBorderStyle(Format::BorderThin);
    lines_left.setVerticalAlignment(Format::AlignVCenter);
    lines_left.setHorizontalAlignment(Format::AlignLeft);

    for (int i = 1; i <= 32; ++i) {
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

        document.write(15 + i, 2, QString::number(i));
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
