/*!
 * =============================================================================
 *
 *   @file: tableWidgetExport.hpp
 *
 *   @date: January, 2024
 *
 * @author: Gino Francesco Bogo
 *
 * =============================================================================
 */

#ifndef TABLEWIDGETEXPORT_HPP
#define TABLEWIDGETEXPORT_HPP

#include "widgets/gTableWidget.hpp"
#include "xlsxdocument.h"
#include "xlsxworkbook.h"

namespace gXlsx {
    const int max_register_lines = 32;
    const int max_evaluate_lines = 16;

    typedef struct {
        QString     title;
        QString     practice;
        QString     category;
        QString     rank;
        QStringList athletes;
    } PeopleRecord;

    void decodeTableWidget(gTableWidget* src_table, PeopleRecord& dst_record);

    void createSheetRegister(QXlsx::Document& document, PeopleRecord& record, int sheet = 1);
    void createSheetEvaluate(QXlsx::Document& document, PeopleRecord& record, int sheet = 1);
}; // namespace gXlsx

#endif // TABLEWIDGETEXPORT_HPP
