#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H
#include "APIManager.h"
#include <QWidget>

class QPushButton;
class InstrumentManagerWindow;

class AdminWindow : public QWidget {
    Q_OBJECT

public:
    explicit AdminWindow(APIManager* apiManager, QWidget *parent = nullptr);

private slots:
    void goToLogin();
    void openInstrumentManager();
    void openUserManagement(); // Placeholder for future implementation

private:
    QPushButton *logoutButton;
    QPushButton *instrumentManagerButton;
    QPushButton *userManagementButton;
    APIManager* apiManager;
};

#endif // ADMINWINDOW_H
