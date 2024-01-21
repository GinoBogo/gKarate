/*!
 * =============================================================================
 *
 *   @file: tableWidgetSetup.hpp
 *
 *   @date: January, 2024
 *
 * @author: Gino Francesco Bogo
 *
 * =============================================================================
 */

#ifndef TABLEWIDGETSETUP_HPP
#define TABLEWIDGETSETUP_HPP

#include "widgets/gTableWidgetRow.hpp"

#include <qstringlist.h>

extern QStringList RANK_MAP;

enum ROW_FULL_INDEX {
    FULL_SURNAME,   //
    FULL_NAME,      //
    FULL_BIRTHDAY,  //
    FULL_CATEGORY,  //
    FULL_RANK,      //
    FULL_PRACTICE,  //
    FULL_STYLE,     //
    FULL_SOCIETY,   //
    FULL_REFERENCE, //
};

enum ROW_MINI_INDEX {
    MINI_SURNAME,  //
    MINI_NAME,     //
    MINI_CATEGORY, //
    MINI_RANK,     //
    MINI_SOCIETY,  //
    MINI_STYLE,    //
};

void setupRankMap();
void setupRow_Full(gTableWidgetRow* row_ptr);
void setupRow_Mini(gTableWidgetRow* row_ptr);

#endif // TABLEWIDGETSETUP_HPP
