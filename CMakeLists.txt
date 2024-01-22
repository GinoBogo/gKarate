cmake_minimum_required(VERSION 3.5)

project(gKarate VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

include_directories("./libs")
include_directories("./qxlsx")
include_directories("./widgets")

set(PROJECT_SOURCES
        main.cpp
        gMainWidget.cpp
        gMainWidget.hpp
        gMainWidget.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(gKarate
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        libs/gFileDialog.cpp
        libs/gFileDialog.hpp
        libs/gXmlFile.cpp
        libs/gXmlFile.hpp
        libs/gXmlNode.cpp
        libs/gXmlNode.hpp
        libs/gXmlPair.cpp
        libs/gXmlPair.hpp
        qxlsx/xlsxabstractooxmlfile.cpp
        qxlsx/xlsxabstractooxmlfile.h
        qxlsx/xlsxabstractooxmlfile_p.h
        qxlsx/xlsxabstractsheet.cpp
        qxlsx/xlsxabstractsheet.h
        qxlsx/xlsxabstractsheet_p.h
        qxlsx/xlsxcell.cpp qxlsx/xlsxcell.h
        qxlsx/xlsxcell_p.h
        qxlsx/xlsxcellformula.cpp
        qxlsx/xlsxcellformula.h
        qxlsx/xlsxcellformula_p.h
        qxlsx/xlsxcelllocation.cpp
        qxlsx/xlsxcelllocation.h
        qxlsx/xlsxcellrange.cpp
        qxlsx/xlsxcellrange.h
        qxlsx/xlsxcellreference.cpp
        qxlsx/xlsxcellreference.h
        qxlsx/xlsxchart.cpp
        qxlsx/xlsxchart.h
        qxlsx/xlsxchart_p.h
        qxlsx/xlsxchartsheet.cpp
        qxlsx/xlsxchartsheet.h
        qxlsx/xlsxchartsheet_p.h
        qxlsx/xlsxcolor.cpp
        qxlsx/xlsxcolor_p.h
        qxlsx/xlsxconditionalformatting.cpp
        qxlsx/xlsxconditionalformatting.h
        qxlsx/xlsxconditionalformatting_p.h
        qxlsx/xlsxcontenttypes.cpp
        qxlsx/xlsxcontenttypes_p.h
        qxlsx/xlsxdatavalidation.cpp
        qxlsx/xlsxdatavalidation.h
        qxlsx/xlsxdatavalidation_p.h
        qxlsx/xlsxdatetype.cpp
        qxlsx/xlsxdatetype.h
        qxlsx/xlsxdocpropsapp.cpp
        qxlsx/xlsxdocpropsapp_p.h
        qxlsx/xlsxdocpropscore.cpp
        qxlsx/xlsxdocpropscore_p.h
        qxlsx/xlsxdocument.cpp
        qxlsx/xlsxdocument.h
        qxlsx/xlsxdocument_p.h
        qxlsx/xlsxdrawing.cpp
        qxlsx/xlsxdrawing_p.h
        qxlsx/xlsxdrawinganchor.cpp
        qxlsx/xlsxdrawinganchor_p.h
        qxlsx/xlsxformat.cpp
        qxlsx/xlsxformat.h
        qxlsx/xlsxformat_p.h
        qxlsx/xlsxglobal.h
        qxlsx/xlsxmediafile.cpp
        qxlsx/xlsxmediafile_p.h
        qxlsx/xlsxnumformatparser.cpp
        qxlsx/xlsxnumformatparser_p.h
        qxlsx/xlsxrelationships.cpp
        qxlsx/xlsxrelationships_p.h
        qxlsx/xlsxrichstring.cpp
        qxlsx/xlsxrichstring.h
        qxlsx/xlsxrichstring_p.h
        qxlsx/xlsxsharedstrings.cpp
        qxlsx/xlsxsharedstrings_p.h
        qxlsx/xlsxsimpleooxmlfile.cpp
        qxlsx/xlsxsimpleooxmlfile_p.h
        qxlsx/xlsxstyles.cpp
        qxlsx/xlsxstyles_p.h
        qxlsx/xlsxtheme.cpp
        qxlsx/xlsxtheme_p.h
        qxlsx/xlsxutility.cpp
        qxlsx/xlsxutility_p.h
        qxlsx/xlsxworkbook.cpp
        qxlsx/xlsxworkbook.h
        qxlsx/xlsxworkbook_p.h
        qxlsx/xlsxworksheet.cpp
        qxlsx/xlsxworksheet.h
        qxlsx/xlsxworksheet_p.h
        qxlsx/xlsxzipreader.cpp
        qxlsx/xlsxzipreader_p.h
        qxlsx/xlsxzipwriter.cpp
        qxlsx/xlsxzipwriter_p.h
        widgets/gTableWidget.cpp
        widgets/gTableWidget.hpp
        widgets/gTableWidgetBase.cpp
        widgets/gTableWidgetBase.hpp
        widgets/gTableWidgetCBox.cpp
        widgets/gTableWidgetCBox.hpp
        widgets/gTableWidgetCell.cpp
        widgets/gTableWidgetCell.hpp
        widgets/gTableWidgetDate.cpp
        widgets/gTableWidgetDate.hpp
        widgets/gTableWidgetIcon.cpp
        widgets/gTableWidgetIcon.hpp
        widgets/gTableWidgetItem.cpp
        widgets/gTableWidgetItem.hpp
        widgets/gTableWidgetRow.cpp
        widgets/gTableWidgetRow.hpp
        widgets/gTableWidgetRows.cpp
        widgets/gTableWidgetRows.hpp
        gDateDialog.cpp
        gDateDialog.hpp
        gDateDialog.ui
        main.qrc
        main.rc
        tableWidgetExport.cpp
        tableWidgetExport.hpp
        tableWidgetSetup.cpp
        tableWidgetSetup.hpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET gKarate APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(gKarate SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(gKarate
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(gKarate PRIVATE Qt${QT_VERSION_MAJOR}::WidgetsPrivate)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.gKarate)
endif()
set_target_properties(gKarate PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS gKarate
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(gKarate)
endif()
