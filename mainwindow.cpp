#include "mainwindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include "multipleViewsWindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle("Fenêtre Principale");
    resize(1280, 720);

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);

    QPushButton* button = new QPushButton("Ouvrir une nouvelle fenêtre", this);
    layout->addWidget(button);

    connect(button, &QPushButton::clicked, this, [this]() { openNewWindow(WindowType::SURVEILLANCE); });
}

MainWindow::~MainWindow() {
}

void MainWindow::openNewWindow(WindowType type) {
    QMainWindow* newWindow = nullptr;

    switch (type) {
    case WindowType::LISTING:
        newWindow = createListingWindow();
        break;
    case WindowType::SURVEILLANCE:
        newWindow = createSurveillanceWindow();
        break;
    default:
        return;
    }

    if (newWindow) {
        closeAndTransferOwnership(newWindow);
    }
}

void MainWindow::closeAndTransferOwnership(QMainWindow* newWindow) {
    if (!newWindow) return;

    // Configure la nouvelle fenêtre
    newWindow->setAttribute(Qt::WA_DeleteOnClose);

    // transferData(newWindow);

    connect(newWindow, &QMainWindow::destroyed, this, &MainWindow::onNewWindowDestroyed);

    newWindow->show();
    this->close();
}

void MainWindow::onNewWindowDestroyed() {
    // Logique à exécuter quand la nouvelle fenêtre est fermée
    this->show();
    // Autres actions de nettoyage si nécessaire
}

QMainWindow* MainWindow::createSurveillanceWindow() {
    return new MultipleViewsWindow(this);
}

QMainWindow* MainWindow::createListingWindow() {
    // Implémentez la création de la fenêtre de listing
    return nullptr;
}