#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include "APIManager.h"

class QLineEdit;
class QPushButton;
class QLabel;

class LoginWindow : public QWidget {
    Q_OBJECT

public:
    explicit LoginWindow(APIManager* apiManager, QWidget *parent = nullptr);

signals:
    void loginSuccessful();

private slots:
    void attemptLogin();

private:
    APIManager* apiManager;
    QLineEdit *usernameField;
    QLineEdit *passwordField;
    QLabel *errorLabel;
};

#endif // LOGINWINDOW_H
