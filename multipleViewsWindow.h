#ifndef MULTIPLEVIEWSWINDOW_H
#define MULTIPLEVIEWSWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QtCore>
#include <QtGui>
#include <QtCharts>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QTableWidget>
#include <QLCDNumber>

class MultipleViewsWindow : public QMainWindow
{
    Q_OBJECT

public:
    MultipleViewsWindow(QWidget* parent = nullptr);
    ~MultipleViewsWindow();

private slots:
    void changePage(int index);

private:
    QWidget* centralWidget;
    QHBoxLayout* mainLayout;
    QWidget* sideMenu;
    QVBoxLayout* menuLayout;
    QStackedWidget* stackedWidget;

    // Graphic components -- TODO
    QChart* m_priceChart;
    QLineSeries* m_priceSeries;
    QChartView* m_chartView;


    void createSideMenu();
    void createPages();

    void createPriceChart();
};

#endif
