#include "MainWindow.h"

#include <QApplication>

/**
 * @brief The entry point of the application
 * @param argc The number of command-line arguments
 * @param argv The array of command-line arguments
 * @return The exit code of the application
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
