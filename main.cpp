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

#define ENABLE_SPLASH_SCREEN

int main(int argc, char* argv[]) {
    QApplication::setStyle("fusion");

    QApplication app(argc, argv);

    gMainWidget wnd;

    wnd.show();

#ifdef ENABLE_SPLASH_SCREEN
    QPixmap pixmap(":/res/images/splash.png");

    QSplashScreen splash(pixmap, Qt::WindowStaysOnTopHint);

    const auto rect_1 = wnd.normalGeometry();
    const auto rect_2 = splash.normalGeometry();
    const auto pos_x  = rect_1.x() + (rect_1.width() - rect_2.width()) / 2;
    const auto pos_y  = rect_1.y() + (rect_1.height() - rect_2.height()) / 2;

    splash.move(pos_x, pos_y);
    splash.show();

    QTimer::singleShot(2500, &splash, &QWidget::close);
#endif

    return QApplication::exec();
}

/* =============================================================================
   End of file
 */
