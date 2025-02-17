#include "instrumentmanagerwindow.h"
#include "loginwindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>

InstrumentManagerWindow::InstrumentManagerWindow(APIManager* apiManager, QWidget *parent)
    : QWidget(parent), apiManager(apiManager) {

    if (!apiManager) {
        std::cerr << "❌ ERROR: APIManager is nullptr in InstrumentManagerWindow!" << std::endl;
        return;
    }

    setWindowTitle("Instrument Manager");
    setFixedSize(800, 700);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Top Bar with Logout Button
    QHBoxLayout *topLayout = new QHBoxLayout();
    logoutButton = new QPushButton("Logout", this);
    topLayout->addWidget(logoutButton);
    topLayout->addStretch(1);
    mainLayout->addLayout(topLayout);

    // Table for Instruments
    instrumentTable = new QTableWidget(this);
    instrumentTable->setColumnCount(4);
    instrumentTable->setHorizontalHeaderLabels({"ISIN", "MIC", "Currency", "Status"});
    instrumentTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    instrumentTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    instrumentTable->setFixedHeight(300);
    mainLayout->addWidget(instrumentTable);

    connect(instrumentTable, &QTableWidget::cellClicked, this, &InstrumentManagerWindow::populateFieldsFromTable);

    // Form Layout
    QVBoxLayout *formLayout = new QVBoxLayout();

    // ISIN Field
    QHBoxLayout *isinLayout = new QHBoxLayout();
    isinLayout->addWidget(new QLabel("ISIN:"));
    isinEntry = new QLineEdit(this);
    isinLayout->addWidget(isinEntry);
    formLayout->addLayout(isinLayout);

    // MIC Field
    QHBoxLayout *micLayout = new QHBoxLayout();
    micLayout->addWidget(new QLabel("MIC:"));
    micEntry = new QLineEdit(this);
    micLayout->addWidget(micEntry);
    formLayout->addLayout(micLayout);

    // Currency Field
    QHBoxLayout *currencyLayout = new QHBoxLayout();
    currencyLayout->addWidget(new QLabel("Currency:"));
    currencyEntry = new QLineEdit(this);
    currencyLayout->addWidget(currencyEntry);
    formLayout->addLayout(currencyLayout);

    // Status Field
    QHBoxLayout *statusLayout = new QHBoxLayout();
    statusLayout->addWidget(new QLabel("Status:"));
    statusEntry = new QLineEdit(this);
    statusLayout->addWidget(statusEntry);
    formLayout->addLayout(statusLayout);

    mainLayout->addLayout(formLayout);

    // Buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    refreshButton = new QPushButton("Refresh", this);
    addButton = new QPushButton("Add", this);
    modifyButton = new QPushButton("Modify", this);
    deleteButton = new QPushButton("Delete", this);

    buttonLayout->addWidget(refreshButton);
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(modifyButton);
    buttonLayout->addWidget(deleteButton);

    mainLayout->addLayout(buttonLayout);

    // Connect Button Events
    connect(logoutButton, &QPushButton::clicked, this, &InstrumentManagerWindow::goToLogin);
    connect(refreshButton, &QPushButton::clicked, this, &InstrumentManagerWindow::refreshTable);
    connect(addButton, &QPushButton::clicked, this, &InstrumentManagerWindow::addInstrument);
    connect(modifyButton, &QPushButton::clicked, this, &InstrumentManagerWindow::modifyInstrument);
    connect(deleteButton, &QPushButton::clicked, this, &InstrumentManagerWindow::deleteInstrument);

    // Populate Initial Data
    populateInstrumentTable();
}

void InstrumentManagerWindow::refreshTable() {
    populateInstrumentTable();
}

void InstrumentManagerWindow::addInstrument() {
    if (isinEntry->text().isEmpty() || micEntry->text().isEmpty() ||
        currencyEntry->text().isEmpty() || statusEntry->text().isEmpty()) {
        QMessageBox::warning(this, "Error", "All fields are required.");
        return;
    }

    if (apiManager->addInstrument(isinEntry->text().toStdString(), micEntry->text().toStdString(),
                                  currencyEntry->text().toStdString(), statusEntry->text().toStdString())) {
        QMessageBox::information(this, "Success", "Instrument added successfully.");
        refreshTable();
    } else {
        QMessageBox::critical(this, "Error", "Failed to add instrument.");
    }
}

void InstrumentManagerWindow::deleteInstrument() {
    if (isinEntry->text().isEmpty()) {
        QMessageBox::warning(this, "Error", "ISIN is required to delete an instrument.");
        return;
    }

    if (apiManager->dellInstrument(isinEntry->text().toStdString())) {
        QMessageBox::information(this, "Success", "Instrument deleted successfully.");
        refreshTable();
    } else {
        QMessageBox::critical(this, "Error", "Failed to delete instrument.");
    }
}

void InstrumentManagerWindow::modifyInstrument() {
    if (isinEntry->text().isEmpty()) {
        QMessageBox::warning(this, "Error", "ISIN is required to modify an instrument.");
        return;
    }

    if (apiManager->modifyInstrument(isinEntry->text().toStdString(), micEntry->text().toStdString(),
                                     currencyEntry->text().toStdString(), statusEntry->text().toStdString())) {
        QMessageBox::information(this, "Success", "Instrument modified successfully.");
        refreshTable();
    } else {
        QMessageBox::critical(this, "Error", "Failed to modify instrument.");
    }
}

void InstrumentManagerWindow::populateInstrumentTable() {
    instrumentTable->setRowCount(0);
    std::vector<std::unordered_map<std::string, std::string>> instruments = apiManager->getInstruments();

    for (const auto& instrument : instruments) {
        int row = instrumentTable->rowCount();
        instrumentTable->insertRow(row);

        instrumentTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(instrument.at("isin"))));
        instrumentTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(instrument.at("mic"))));
        instrumentTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(instrument.at("currency"))));
        instrumentTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(instrument.at("status"))));
    }
}

void InstrumentManagerWindow::goToLogin() {
    hide();
    LoginWindow *loginWindow = new LoginWindow(apiManager, nullptr);
    loginWindow->show();
}
void InstrumentManagerWindow::populateFieldsFromTable(int row, int column) {
    if (row < 0 || row >= instrumentTable->rowCount()) {
        return; // Prevent accessing invalid rows
    }

    isinEntry->setText(instrumentTable->item(row, 0)->text());
    micEntry->setText(instrumentTable->item(row, 1)->text());
    currencyEntry->setText(instrumentTable->item(row, 2)->text());
    statusEntry->setText(instrumentTable->item(row, 3)->text());
}

