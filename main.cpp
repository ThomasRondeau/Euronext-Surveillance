#include <QApplication>
#include "loginwindow.h"
#include "APIManager.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Initialise APIManager avec l'URL de l'API (modifie si nécessaire)
    APIManager apiManager("http://localhost:18080");

    // Passe APIManager au LoginWindow
    LoginWindow loginWindow(&apiManager);
    loginWindow.show();  // Affiche la page de connexion en premier

    return app.exec();
}
