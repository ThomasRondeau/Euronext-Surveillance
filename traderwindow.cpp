#include "traderwindow.h"
#include "loginwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

TraderWindow::TraderWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Trader Dashboard");
    setFixedSize(500, 400);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QHBoxLayout *topLayout = new QHBoxLayout();
    QPushButton *logoutButton = new QPushButton("Logout", this);
    topLayout->addWidget(logoutButton);
    topLayout->addStretch(1);
    mainLayout->addLayout(topLayout);

    QVBoxLayout *centerLayout = new QVBoxLayout();
    centerLayout->setAlignment(Qt::AlignCenter);

    QPushButton *button1 = new QPushButton("Button 1", this);
    QPushButton *button2 = new QPushButton("Button 2", this);

    centerLayout->addWidget(button1);
    centerLayout->addWidget(button2);

    mainLayout->addLayout(centerLayout);

    connect(logoutButton, &QPushButton::clicked, this, &TraderWindow::goToLogin);
}

void TraderWindow::goToLogin() {
    hide();
    LoginWindow *loginWindow = new LoginWindow(nullptr);
    loginWindow->show();
}
