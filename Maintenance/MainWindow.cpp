#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    newCat = new Catalogue();
    QString currLabel;
    if(newCat->size() > 0)
    {
        currLabel = newCat->getCurrent()->getName().c_str();
        updateForm();
    }
    else
    {
        currLabel = "No items found";
    }
    ui->lineEdit->setText(currLabel);
}

MainWindow::~MainWindow()
{
    newCat->save();
    delete ui;
    delete newCat;
}

void MainWindow::updateForm()
{
    std::vector<std::string> details;
    if(newCat->getCurrent()->getName() != "Null")
    {
        details = newCat->getCurrent()->getDetails();
        QString name = details.at(0).c_str();
        ui->lineEdit->setText(name);
        QString colour = (details.at(1)).c_str();
        ui->lineEdit_2->setText(colour);
        QString material = (details.at(2)).c_str();
        ui->lineEdit_3->setText(material);
        QString laceStyle = (details.at(3)).c_str();
        ui->lineEdit_4->setText(laceStyle);
        QString sStyle = (details.at(4)).c_str();
        ui->comboBox->setCurrentText(sStyle);
        QString size = (details.at(5)).c_str();
        ui->lineEdit_5->setText(size);
        QString price = (details.at(6)).c_str();
        ui->lineEdit_6->setText(price);
        QString stock = (details.at(7)).c_str();
        ui->stockCount->setText(stock);
        QString style;
        if(details.size() == 9)
        {
            setShoe();
            style = (details.at(8)).c_str();
            ui->comboBox_2->setCurrentText(style);
        }
        else if (details.size() == 10)
        {
            setBoot();
            style = (details.at(9)).c_str();
            ui->comboBox_2->setCurrentText(style);
            QString target = (details.at(8)).c_str();
            ui->lineEdit_7->setText(target);
        }
    }
}

void MainWindow::setShoe()
{
    QString flipflop = "Flipflop";
    QString court = "Court";
    QString sandal = "Sandal";
    QString trainer = "Trainer";
    QString slipper = "Slipper";
    ui->shared->setText((QString)"Shoe type:");
    ui->comboBox_2->clear();
    ui->comboBox_2->addItem(flipflop);
    ui->comboBox_2->addItem(court);
    ui->comboBox_2->addItem(sandal);
    ui->comboBox_2->addItem(trainer);
    ui->comboBox_2->addItem(slipper);
    ui->radioButton->setChecked(true);
    ui->radioButton_2->setChecked(false);
    ui->target->setVisible(false);
    ui->lineEdit_7->setVisible(false);
}

void MainWindow::setBoot()
{
    QString chelsea = "Chelsea";
    QString knee = "Knee";
    QString ankle = "Ankle";
    QString thigh = "Thigh";
    QString jodhpur = "Jodhpur";
    QString rigger = "Rigger";
    ui->shared->setText((QString)"Boot type:");
    ui->comboBox_2->clear();
    ui->comboBox_2->addItem(chelsea);
    ui->comboBox_2->addItem(knee);
    ui->comboBox_2->addItem(ankle);
    ui->comboBox_2->addItem(thigh);
    ui->comboBox_2->addItem(jodhpur);
    ui->comboBox_2->addItem(rigger);
    ui->radioButton->setChecked(false);
    ui->radioButton_2->setChecked(true);
    ui->target->setVisible(true);
    ui->lineEdit_7->setVisible(true);
}

void MainWindow::on_pushButton_2_clicked()
{
    newCat->next();
    updateForm();
}

void MainWindow::on_pushButton_clicked()
{
    newCat->previous();
    updateForm();
}

void MainWindow::on_pushButton_3_clicked()
{
    newCat->remove(newCat->getCurrent());
    newCat->insert(getDetails());
    newCat->save();
    newCat->end();
}

void MainWindow::on_pushButton_4_clicked()
{
    std::vector<std::string> details = getDetails();
    newCat->insert(details);
}

void MainWindow::on_pushButton_5_clicked()
{
    newCat->remove(newCat->getCurrent());
    MainWindow::on_pushButton_clicked();
}

void MainWindow::on_radioButton_clicked()
{
    setShoe();
}

void MainWindow::on_radioButton_2_clicked()
{
    setBoot();
}

std::vector<std::string> MainWindow::getDetails()
{
    std::vector<std::string> details;
    details.push_back(ui->lineEdit->text().toStdString());
    details.push_back(ui->lineEdit_2->text().toStdString());
    details.push_back(ui->lineEdit_3->text().toStdString());
    details.push_back(ui->lineEdit_4->text().toStdString());
    details.push_back(ui->comboBox->currentText().toStdString());
    details.push_back(ui->lineEdit_5->text().toStdString());
    details.push_back(ui->lineEdit_6->text().toStdString());
    details.push_back(ui->comboBox_2->currentText().toStdString());
    if(ui->radioButton_2->isChecked())
    {
        details.push_back(ui->lineEdit_7->text().toStdString());
    }
    return details;
}

void MainWindow::on_pushButton_6_clicked()
{
    QString amount = ui->lineEdit_8->text();
    newCat->getCurrent()->addStock(atoi(amount.toStdString().c_str()));
    ui->stockCount->setText((QString)std::to_string(newCat->getCurrent()->getStock()).c_str());
    ui->lineEdit_8->setText("");
}

void MainWindow::on_pushButton_7_clicked()
{
    ui->listWidget->clear();
    std::vector<std::pair<std::string, int>> items = newCat->generateReportStockCount();
    for(int i = 0; i < items.size(); i++)
    {
        std::pair<std::string, int> current = items.at(i);
        QString item = (current.first + " Stock: " +std::to_string(current.second)).c_str();
        ui->listWidget->addItem(item);
    }
}
