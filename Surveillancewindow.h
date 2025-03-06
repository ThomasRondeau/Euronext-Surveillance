#ifndef SURVEILLANCEWINDOW_H
#define SURVEILLANCEWINDOW_H

#include <QWidget>

class QPushButton;

class SurveillanceWindow : public QWidget {
    Q_OBJECT

public:
    explicit SurveillanceWindow(QWidget *parent = nullptr);

private slots:
    void goToLogin();
    void goToMultipleViews();
};

#endif // SURVEILLANCEWINDOW_H
