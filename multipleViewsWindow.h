#ifndef MULTIPLEVIEWSWINDOW_H
#define MULTIPLEVIEWSWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>

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

    void createSideMenu();
    void createPages();
};

#endif
