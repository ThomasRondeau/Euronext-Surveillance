#include "adminwindow.h"
#include "instrumentmanagerwindow.h"
#include "loginwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

AdminWindow::AdminWindow(APIManager* apiManager,QWidget *parent) : QWidget(parent),apiManager(apiManager) {
    if (!apiManager) {
        std::cerr << "❌ ERROR: APIManager is NULL in AdminWindow!" << std::endl;
        return;
    }

    setWindowTitle("Admin Panel");
    setFixedSize(500, 400);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Top Bar with Logout Button
    QHBoxLayout *topLayout = new QHBoxLayout();
    logoutButton = new QPushButton("Logout", this);
    topLayout->addWidget(logoutButton);
    topLayout->addStretch(1);
    mainLayout->addLayout(topLayout);

    // Center Layout for Main Buttons
    QVBoxLayout *centerLayout = new QVBoxLayout();
    centerLayout->setAlignment(Qt::AlignCenter);

    instrumentManagerButton = new QPushButton("Instrument Manager", this);
    userManagementButton = new QPushButton("User Management", this); // Placeholder

    centerLayout->addWidget(instrumentManagerButton);
    centerLayout->addWidget(userManagementButton);

    mainLayout->addLayout(centerLayout);

    // Connect Button Events
    connect(logoutButton, &QPushButton::clicked, this, &AdminWindow::goToLogin);
    connect(instrumentManagerButton, &QPushButton::clicked, this, &AdminWindow::openInstrumentManager);
    connect(userManagementButton, &QPushButton::clicked, this, &AdminWindow::openUserManagement);
}

// Navigate back to login
void AdminWindow::goToLogin() {
    hide();
    LoginWindow *loginWindow = new LoginWindow(nullptr);
    loginWindow->show();
}

void AdminWindow::openInstrumentManager() {
    if (!apiManager) {
        std::cerr << "❌ ERROR: APIManager is nullptr in openInstrumentManager()" << std::endl;
        return;
    }

    hide();
    InstrumentManagerWindow *instrumentManager = new InstrumentManagerWindow(apiManager, nullptr);
    instrumentManager->show();
}

// Placeholder function for User Management (to be implemented later)
void AdminWindow::openUserManagement() {
    // This will be implemented in the future
}
