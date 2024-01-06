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

int main(int argc, char* argv[]) {

    QApplication::setStyle("fusion");

    QApplication app(argc, argv);

    gMainWidget wnd;

    wnd.show();

    QPixmap pixmap(":/res/images/splash.png");

    QSplashScreen splash(pixmap, Qt::WindowStaysOnTopHint);

    splash.show();

    QTimer::singleShot(2500, &splash, &QWidget::close);

    return app.exec();
}
