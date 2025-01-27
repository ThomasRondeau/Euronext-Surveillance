#include "multipleViewsWindow.h"
#include "searchableTableWidget.h"

// creation of the window
MultipleViewsWindow::MultipleViewsWindow(QWidget* parent)
    : QMainWindow(parent), 
    m_priceChart(new QChart()),
    m_priceSeries(new QLineSeries()),
    m_chartView(new QChartView(m_priceChart)),
	m_orderBookTable(new QTableWidget(10, 4, this))
{
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QHBoxLayout(centralWidget);

    //Test, to refactor
	createPriceChart();
    createOrderBookDisplay();
    
    createSideMenu();

    stackedWidget = new QStackedWidget;
    createPages();

    mainLayout->addWidget(sideMenu);
    mainLayout->addWidget(stackedWidget);

    setMinimumSize(1280, 720);
}

//Destructor
MultipleViewsWindow::~MultipleViewsWindow()
{
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

	//Page 1 : executed data
    QVBoxLayout* layout1 = new QVBoxLayout(page1);
    layout1->addWidget(new QLabel("Chart on executed data"));
	layout1->addWidget(m_chartView);

    QVBoxLayout* layout2 = new QVBoxLayout(page2);
    layout2->addWidget(new QLabel("Chart on pretrade data"));
	layout2->addWidget(m_orderBookTable);

    SearchableTableWidget* searchTable = new SearchableTableWidget(this);
    QVBoxLayout* layout3 = new QVBoxLayout(page3);
    layout3->addWidget(new QLabel("Raw data search"));
	layout3->addWidget(searchTable);

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

// Create the price chart
void MultipleViewsWindow::createPriceChart()
{
    m_priceSeries->setName("Price");
    m_priceChart->addSeries(m_priceSeries);
    m_priceChart->legend()->hide();
    m_priceChart->createDefaultAxes();
    m_priceChart->setTitle("Price Evolution");

    m_chartView->setRenderHint(QPainter::Antialiasing);
}

// Create the order book display
void MultipleViewsWindow::createOrderBookDisplay()
{
    m_orderBookTable->setHorizontalHeaderLabels({
        "Bid Size", "Bid Price", "Ask Price", "Ask Size"
    });
}