#include "SurveillanceWindow.h"
#include "LoginWindow.h"
#include "MultipleViewsWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

SurveillanceWindow::SurveillanceWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Data Analyst Dashboard");
    setFixedSize(500, 400);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Barre supérieure avec le bouton Logout
    QHBoxLayout *topLayout = new QHBoxLayout();
    QPushButton *logoutButton = new QPushButton("Logout", this);
    topLayout->addWidget(logoutButton);
    topLayout->addStretch(1);
    mainLayout->addLayout(topLayout);

    // Section centrale avec un seul bouton "MultipleView"
    QVBoxLayout *centerLayout = new QVBoxLayout();
    centerLayout->setAlignment(Qt::AlignCenter);

    QPushButton *multipleViewsButton = new QPushButton("MultipleView", this);
    centerLayout->addWidget(multipleViewsButton);

    mainLayout->addLayout(centerLayout);

    // Connexions des boutons aux slots
    connect(logoutButton, &QPushButton::clicked, this, &SurveillanceWindow::goToLogin);
    connect(multipleViewsButton, &QPushButton::clicked, this, &SurveillanceWindow::goToMultipleViews);
}

void SurveillanceWindow::goToLogin() {
    hide();
    LoginWindow *loginWindow = new LoginWindow(nullptr);
    loginWindow->show();
}

void SurveillanceWindow::goToMultipleViews() {
    hide();
    MultipleViewsWindow *multipleViewsWindow = new MultipleViewsWindow(nullptr);
    multipleViewsWindow->show();
}
