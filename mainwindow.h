#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QPushButton;
class QVBoxLayout;
class QWidget;
class LoginWindow;

enum class WindowType {
    LISTING,
    SURVEILLANCE
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    static void showMainWindow();  // Ouvre la fenêtre principale après le login
    void openNewWindow(WindowType type); // Garde la gestion des autres fenêtres

private slots:
    void closeAndTransferOwnership(QMainWindow* newWindow);
    void onNewWindowDestroyed();

private:
    void setupUI();
    QMainWindow* createListingWindow();
    QMainWindow* createSurveillanceWindow();
};

#endif // MAINWINDOW_H
