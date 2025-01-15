#include "multipleViewsWindow.h"

// creation of the window
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

// creation of the side menu to switch between pages
void MultipleViewsWindow::createSideMenu()
{
    sideMenu = new QWidget;
    menuLayout = new QVBoxLayout(sideMenu);

    // Add of buttons
    QPushButton* page1Button = new QPushButton("Executed scan");
    QPushButton* page2Button = new QPushButton("Order book scan");
    QPushButton* page3Button = new QPushButton("Raw Data");

	// Set side menu properties
    sideMenu->setMaximumWidth(200);
    sideMenu->setStyleSheet("background-color: #f0f0f0;");

	//Add buttons to the menu layout
    menuLayout->addWidget(page1Button);
    menuLayout->addWidget(page2Button);
    menuLayout->addWidget(page3Button);
	menuLayout->addStretch(); // Add a stretch to push the buttons to the top

	//Connect the buttons to the changePage function to put a real action in place
    connect(page1Button, &QPushButton::clicked, [this]() { changePage(0); });
    connect(page2Button, &QPushButton::clicked, [this]() { changePage(1); });
    connect(page3Button, &QPushButton::clicked, [this]() { changePage(2); });
}

// creation of the three pages with QWidget
void MultipleViewsWindow::createPages()
{
    QWidget* page1 = new QWidget;
    QWidget* page2 = new QWidget;
    QWidget* page3 = new QWidget;

	//Add a label to each page to describe what they do
    QVBoxLayout* layout1 = new QVBoxLayout(page1);
    layout1->addWidget(new QLabel("Chart on executed data"));

    QVBoxLayout* layout2 = new QVBoxLayout(page2);
    layout2->addWidget(new QLabel("Chart on pretrade data"));

    QVBoxLayout* layout3 = new QVBoxLayout(page3);
    layout3->addWidget(new QLabel("Raw data search"));

	//Add the pages to the stacked widget
    stackedWidget->addWidget(page1);
    stackedWidget->addWidget(page2);
    stackedWidget->addWidget(page3);
}

// change the stack widget index, which allows to switch pages
void MultipleViewsWindow::changePage(int index)
{
    stackedWidget->setCurrentIndex(index);
}

MultipleViewsWindow::~MultipleViewsWindow()
{
}

// To add the same chart as in the mainwindow view

void MultipleViewsWindow::createPriceChart()
{
    m_priceSeries->setName("Price");
    m_priceChart->addSeries(m_priceSeries);
    m_priceChart->legend()->hide();
    m_priceChart->createDefaultAxes();
    m_priceChart->setTitle("Price Evolution");

    m_chartView->setRenderHint(QPainter::Antialiasing);
}