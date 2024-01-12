/*!
 * =============================================================================
 *
 *   @file: main.cpp
 *
 *   @date: December, 2023
 *
 * @author: Gino Francesco Bogo
 *
 * =============================================================================
 */

#include "gMainWidget.hpp"

#include <QApplication>
#include <QPixmap>
#include <QSplashScreen>
#include <QTimer>

// #define ENABLE_SPLASH_SCREEN

int main(int argc, char* argv[]) {

    QApplication::setStyle("macos");

    QApplication app(argc, argv);

    gMainWidget wnd;

    wnd.show();

#ifdef ENABLE_SPLASH_SCREEN
    QPixmap pixmap(":/res/images/splash.png");

    QSplashScreen splash(pixmap, Qt::WindowStaysOnTopHint);

    splash.show();

    QTimer::singleShot(2500, &splash, &QWidget::close);
#endif

    return app.exec();
}
