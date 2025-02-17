#include "loginwindow.h"
#include "adminwindow.h"
#include "traderwindow.h"
#include "dataanalystwindow.h"
#include "APIManager.h"

#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

LoginWindow::LoginWindow(APIManager* apiManager, QWidget *parent)
    : QWidget(parent), apiManager(apiManager) {

    setWindowTitle("Login");
    setFixedSize(400, 300);

    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *titleLabel = new QLabel("Login", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    usernameField = new QLineEdit(this);
    usernameField->setPlaceholderText("Username");
    layout->addWidget(usernameField);

    passwordField = new QLineEdit(this);
    passwordField->setPlaceholderText("Password");
    passwordField->setEchoMode(QLineEdit::Password);
    layout->addWidget(passwordField);

    QPushButton *loginButton = new QPushButton("Connexion", this);
    layout->addWidget(loginButton);

    errorLabel = new QLabel(this);
    errorLabel->setStyleSheet("color: red;");
    errorLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(errorLabel);

    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::attemptLogin);
}

void LoginWindow::attemptLogin() {
    QString username = usernameField->text();
    QString password = passwordField->text();

    if (!apiManager) {
        errorLabel->setText("Erreur: APIManager est NULL.");
        return;
    }

    if (apiManager->login(username.toStdString(), password.toStdString())) {
        // Store the token inside APIManager
        std::string role = apiManager->getUserRole();

        if (role == "Admin") {
            hide();
            AdminWindow* adminWindow = new AdminWindow(apiManager);  // Pass APIManager
            adminWindow->show();
        } else if (role == "Trader") {
            hide();
            TraderWindow* traderWindow = new TraderWindow();  // We shall later add Pass APIManager
            traderWindow->show();
        } else if (role == "DataAnalyst") {
            hide();
            DataAnalystWindow* analystWindow = new DataAnalystWindow();  // same here for Pass APIManager
            analystWindow->show();
        } else {
            errorLabel->setText("Erreur: Rôle utilisateur inconnu.");
        }
    } else {
        errorLabel->setText("Identifiants incorrects !");
    }
}

