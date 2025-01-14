#include "multipleViewsWindow.h"

MultipleViewsWindow::MultipleViewsWindow(QWidget* parent)
    : QMainWindow(parent)
{
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QHBoxLayout(centralWidget);

    createSideMenu();

    stackedWidget = new QStackedWidget;
    createPages();

    mainLayout->addWidget(sideMenu);
    mainLayout->addWidget(stackedWidget);

    setMinimumSize(1280, 720);
}

void MultipleViewsWindow::createSideMenu()
{
    sideMenu = new QWidget;
    menuLayout = new QVBoxLayout(sideMenu);

    QPushButton* page1Button = new QPushButton("Executed scan");
    QPushButton* page2Button = new QPushButton("Order book scan");
    QPushButton* page3Button = new QPushButton("Raw Data");

    sideMenu->setMaximumWidth(200);
    sideMenu->setStyleSheet("background-color: #f0f0f0;");

    menuLayout->addWidget(page1Button);
    menuLayout->addWidget(page2Button);
    menuLayout->addWidget(page3Button);
    menuLayout->addStretch(); 

    connect(page1Button, &QPushButton::clicked, [this]() { changePage(0); });
    connect(page2Button, &QPushButton::clicked, [this]() { changePage(1); });
    connect(page3Button, &QPushButton::clicked, [this]() { changePage(2); });
}

void MultipleViewsWindow::createPages()
{
    QWidget* page1 = new QWidget;
    QWidget* page2 = new QWidget;
    QWidget* page3 = new QWidget;

    // Exemple de contenu pour les pages
    QVBoxLayout* layout1 = new QVBoxLayout(page1);
    layout1->addWidget(new QLabel("Chart on executed data"));

    QVBoxLayout* layout2 = new QVBoxLayout(page2);
    layout2->addWidget(new QLabel("Chart on pretrade data"));

    QVBoxLayout* layout3 = new QVBoxLayout(page3);
    layout3->addWidget(new QLabel("Raw data search"));

    // Ajout des pages au widget empilé
    stackedWidget->addWidget(page1);
    stackedWidget->addWidget(page2);
    stackedWidget->addWidget(page3);
}

void MultipleViewsWindow::changePage(int index)
{
    stackedWidget->setCurrentIndex(index);
}

MultipleViewsWindow::~MultipleViewsWindow()
{
}