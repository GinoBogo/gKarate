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

#include "gTableWidget.hpp"
#include "xlsxdocument.h"

namespace gXlsx {
    typedef struct {
        QString     title;
        QString     practice;
        QStringList athletes;

    } PeopleRecord;

    void decodeTableWidget(gTableWidget* src_table, PeopleRecord& dst_record);

    void createSheet(QXlsx::Document& document, PeopleRecord& record);
}; // namespace gXlsx

#endif // TABLEWIDGETEXPORT_HPP
