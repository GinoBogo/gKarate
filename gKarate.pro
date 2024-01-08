######################################################################
# Automatically generated by qmake (3.1) Fri Dec 29 14:31:27 2023
######################################################################

QT += core gui widgets-private xml

TEMPLATE = app
TARGET = gKarate

INCLUDEPATH += .
INCLUDEPATH += ./libs
INCLUDEPATH += ./qxlsx
INCLUDEPATH += ./widgets

QMAKE_CXXFLAGS += -std=c++17
QMAKE_CXXFLAGS += -Wno-unused-parameter -Wno-unused-variable

# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_UP_TO=0x060000 # disables all APIs deprecated in Qt 6.0.0 and earlier

# Input
HEADERS += gMainWidget.hpp \
           gDateDialog.hpp \
           libs/gFileDialog.hpp \
           libs/gXmlFile.hpp \
           libs/gXmlNode.hpp \
           libs/gXmlPair.hpp \
           qxlsx/xlsxabstractooxmlfile.h \
           qxlsx/xlsxabstractooxmlfile_p.h \
           qxlsx/xlsxabstractsheet.h \
           qxlsx/xlsxabstractsheet_p.h \
           qxlsx/xlsxcell.h \
           qxlsx/xlsxcell_p.h \
           qxlsx/xlsxcellformula.h \
           qxlsx/xlsxcellformula_p.h \
           qxlsx/xlsxcelllocation.h \
           qxlsx/xlsxcellrange.h \
           qxlsx/xlsxcellreference.h \
           qxlsx/xlsxchart.h \
           qxlsx/xlsxchart_p.h \
           qxlsx/xlsxchartsheet.h \
           qxlsx/xlsxchartsheet_p.h \
           qxlsx/xlsxcolor_p.h \
           qxlsx/xlsxconditionalformatting.h \
           qxlsx/xlsxconditionalformatting_p.h \
           qxlsx/xlsxcontenttypes_p.h \
           qxlsx/xlsxdatavalidation.h \
           qxlsx/xlsxdatavalidation_p.h \
           qxlsx/xlsxdatetype.h \
           qxlsx/xlsxdocpropsapp_p.h \
           qxlsx/xlsxdocpropscore_p.h \
           qxlsx/xlsxdocument.h \
           qxlsx/xlsxdocument_p.h \
           qxlsx/xlsxdrawing_p.h \
           qxlsx/xlsxdrawinganchor_p.h \
           qxlsx/xlsxformat.h \
           qxlsx/xlsxformat_p.h \
           qxlsx/xlsxglobal.h \
           qxlsx/xlsxmediafile_p.h \
           qxlsx/xlsxnumformatparser_p.h \
           qxlsx/xlsxrelationships_p.h \
           qxlsx/xlsxrichstring.h \
           qxlsx/xlsxrichstring_p.h \
           qxlsx/xlsxsharedstrings_p.h \
           qxlsx/xlsxsimpleooxmlfile_p.h \
           qxlsx/xlsxstyles_p.h \
           qxlsx/xlsxtheme_p.h \
           qxlsx/xlsxutility_p.h \
           qxlsx/xlsxworkbook.h \
           qxlsx/xlsxworkbook_p.h \
           qxlsx/xlsxworksheet.h \
           qxlsx/xlsxworksheet_p.h \
           qxlsx/xlsxzipreader_p.h \
           qxlsx/xlsxzipwriter_p.h \
           tableWidgetExport.hpp \
           tableWidgetSetup.hpp \
           widgets/gTableWidget.hpp \
           widgets/gTableWidgetBase.hpp \
           widgets/gTableWidgetCBox.hpp \
           widgets/gTableWidgetCell.hpp \
           widgets/gTableWidgetDate.hpp \
           widgets/gTableWidgetIcon.hpp \
           widgets/gTableWidgetItem.hpp \
           widgets/gTableWidgetRow.hpp \
           widgets/gTableWidgetRows.hpp

FORMS += gMainWidget.ui \
         gDateDialog.ui

SOURCES += main.cpp \
           gMainWidget.cpp \
           gDateDialog.cpp \
           libs/gFileDialog.cpp \
           libs/gXmlFile.cpp \
           libs/gXmlNode.cpp \
           libs/gXmlPair.cpp \
           qxlsx/xlsxabstractooxmlfile.cpp \
           qxlsx/xlsxabstractsheet.cpp \
           qxlsx/xlsxcell.cpp \
           qxlsx/xlsxcellformula.cpp \
           qxlsx/xlsxcelllocation.cpp \
           qxlsx/xlsxcellrange.cpp \
           qxlsx/xlsxcellreference.cpp \
           qxlsx/xlsxchart.cpp \
           qxlsx/xlsxchartsheet.cpp \
           qxlsx/xlsxcolor.cpp \
           qxlsx/xlsxconditionalformatting.cpp \
           qxlsx/xlsxcontenttypes.cpp \
           qxlsx/xlsxdatavalidation.cpp \
           qxlsx/xlsxdatetype.cpp \
           qxlsx/xlsxdocpropsapp.cpp \
           qxlsx/xlsxdocpropscore.cpp \
           qxlsx/xlsxdocument.cpp \
           qxlsx/xlsxdrawing.cpp \
           qxlsx/xlsxdrawinganchor.cpp \
           qxlsx/xlsxformat.cpp \
           qxlsx/xlsxmediafile.cpp \
           qxlsx/xlsxnumformatparser.cpp \
           qxlsx/xlsxrelationships.cpp \
           qxlsx/xlsxrichstring.cpp \
           qxlsx/xlsxsharedstrings.cpp \
           qxlsx/xlsxsimpleooxmlfile.cpp \
           qxlsx/xlsxstyles.cpp \
           qxlsx/xlsxtheme.cpp \
           qxlsx/xlsxutility.cpp \
           qxlsx/xlsxworkbook.cpp \
           qxlsx/xlsxworksheet.cpp \
           qxlsx/xlsxzipreader.cpp \
           qxlsx/xlsxzipwriter.cpp \
           tableWidgetExport.cpp \
           tableWidgetSetup.cpp \
           widgets/gTableWidget.cpp \
           widgets/gTableWidgetBase.cpp \
           widgets/gTableWidgetCBox.cpp \
           widgets/gTableWidgetCell.cpp \
           widgets/gTableWidgetDate.cpp \
           widgets/gTableWidgetIcon.cpp \
           widgets/gTableWidgetItem.cpp \
           widgets/gTableWidgetRow.cpp \
           widgets/gTableWidgetRows.cpp

RESOURCES += main.qrc
