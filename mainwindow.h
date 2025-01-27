#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QPushButton;
class QVBoxLayout;
class QWidget;

enum class WindowType {
    LISTING,
    SURVEILLANCE
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    void openNewWindow(WindowType type);

private slots:
    void closeAndTransferOwnership(QMainWindow* newWindow);
    void onNewWindowDestroyed();  // Nouveau slot dédié

private:
    QMainWindow* createListingWindow();
    QMainWindow* createSurveillanceWindow();
};

#endif // MAINWINDOW_H