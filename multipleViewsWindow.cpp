#include "multipleViewsWindow.h"

MultipleViewsWindow::MultipleViewsWindow(QWidget* parent)
    : QMainWindow(parent)
{
    // Création du widget central
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Layout principal horizontal
    mainLayout = new QHBoxLayout(centralWidget);

    // Création du menu latéral
    createSideMenu();

    // Création du widget empilé pour les différentes pages
    stackedWidget = new QStackedWidget;
    createPages();

    // Ajout des widgets au layout principal
    mainLayout->addWidget(sideMenu);
    mainLayout->addWidget(stackedWidget);

    // Définir une taille minimale pour la fenêtre
    setMinimumSize(800, 600);
}

void MultipleViewsWindow::createSideMenu()
{
    sideMenu = new QWidget;
    menuLayout = new QVBoxLayout(sideMenu);

    // Création des boutons du menu
    QPushButton* page1Button = new QPushButton("Page 1");
    QPushButton* page2Button = new QPushButton("Page 2");
    QPushButton* page3Button = new QPushButton("Page 3");

    // Style pour le menu latéral
    sideMenu->setMaximumWidth(200);
    sideMenu->setStyleSheet("background-color: #f0f0f0;");

    // Ajout des boutons au layout du menu
    menuLayout->addWidget(page1Button);
    menuLayout->addWidget(page2Button);
    menuLayout->addWidget(page3Button);
    menuLayout->addStretch(); // Ajoute un espace extensible en bas

    // Connexion des boutons
    connect(page1Button, &QPushButton::clicked, [this]() { changePage(0); });
    connect(page2Button, &QPushButton::clicked, [this]() { changePage(1); });
    connect(page3Button, &QPushButton::clicked, [this]() { changePage(2); });
}

void MultipleViewsWindow::createPages()
{
    // Création des pages exemple
    QWidget* page1 = new QWidget;
    QWidget* page2 = new QWidget;
    QWidget* page3 = new QWidget;

    // Exemple de contenu pour les pages
    QVBoxLayout* layout1 = new QVBoxLayout(page1);
    layout1->addWidget(new QLabel("Contenu de la page 1"));

    QVBoxLayout* layout2 = new QVBoxLayout(page2);
    layout2->addWidget(new QLabel("Contenu de la page 2"));

    QVBoxLayout* layout3 = new QVBoxLayout(page3);
    layout3->addWidget(new QLabel("Contenu de la page 3"));

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