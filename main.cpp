#include "multipleViewsWindow.h"

#include <QApplication>

int main(int argc, char* argv[]) {
	// Création de l'application Qt
    QApplication app(argc, argv);
    MultipleViewsWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
