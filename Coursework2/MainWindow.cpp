#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QString>
#include <QList>

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
    ui->name->setText(currLabel);
    updateStats();
}

MainWindow::~MainWindow()
{
    newCat->save();
    delete ui;
    delete newCat;
}

void MainWindow::on_pushButton_clicked()
{
    newCat->previous();
    updateForm();
}

void MainWindow::on_pushButton_2_clicked()
{
    newCat->next();
    updateForm();
}

void MainWindow::on_pushButton_3_clicked()
{
    if(newCat->getCurrent()->getStock() > 0)
    {
        newCat->addToQueue(newCat->getCurrent());
        newCat->getCurrent()->removeStock(1);
        updateStats();
    }
}

void MainWindow::updateStats()
{
    QString boots = ("Total Boots: "+std::to_string(newCat->getBootStock())).c_str();
    QString shoes = ("Total Shoes: "+std::to_string(newCat->getShoeStock())).c_str();
    QString total = ("Total: "+std::to_string(newCat->getTotalStock())).c_str();
    QString items = ("Items in Queue: "+std::to_string(newCat->queueSize())).c_str();
    ui->label_2->setText(boots);
    ui->label_3->setText(shoes);
    ui->label_4->setText(total);
    ui->label_5->setText(items);
}

void MainWindow::updateForm()
{
    std::vector<std::string> details;
    if(newCat->getCurrent()->getName() != "Null")
    {
        details = newCat->getCurrent()->getDetails();
        QString name = details.at(0).c_str();
        ui->name->setText(name);
        QString colour = ("Colour: "+details.at(1)).c_str();
        ui->colour->setText(colour);
        QString material = ("Material: "+details.at(2)).c_str();
        ui->material->setText(material);
        QString laceStyle = ("Lace Style: "+details.at(3)).c_str();
        ui->laceStyle->setText(laceStyle);
        QString soleStyle = ("Sole Style: "+details.at(4)).c_str();
        ui->soleStyle->setText(soleStyle);
        QString size = ("Size: "+details.at(5)).c_str();
        ui->size->setText(size);
        QString price = ("Price: "+details.at(6)).c_str();
        ui->price->setText(price);
        QString style;

        if(details.size() == 9)
        {
            style = ("Shoe style: "+details.at(8)).c_str();
            ui->shared->setText(style);
            ui->target->setVisible(false);
        }
        else if (details.size() == 10)
        {
            ui->target->setVisible(true);
            style = ("Boot style: "+details.at(9)).c_str();
            ui->shared->setText(style);
            QString target = ("Speciality: "+details.at(8)).c_str();
            ui->target->setText(target);
        }
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    std::string colour = ui->textEdit_2->toPlainText().toStdString();
    std::string size = ui->textEdit_3->toPlainText().toStdString();
    searchResults = newCat->search(colour, size);
    ui->listWidget->clear();
    for(int i = 0; i < searchResults->size(); i++)
    {
        QString currName = searchResults->at(i)->getName().c_str();
        ui->listWidget->insertItem (i, currName);
    }
}
