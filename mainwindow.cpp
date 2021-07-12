#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
/*Load DB*/
void MainWindow::on_pushButton_clicked()
{
    ui->tableWidget->setRowCount(0);
    QFile List("/home/aleksandra/Документы/Cpp/ProductList/List.txt");
    int i=0;
    if (List.open(QIODevice::ReadOnly))
    {
       QTextStream in(&List);
       while (!in.atEnd())
       {
          QString line = in.readLine();
          QStringList words = line.split("->");
          ui->tableWidget->insertRow(ui->tableWidget->rowCount());
          ui->tableWidget->setItem(i,0,new QTableWidgetItem(words[0]));
          ui->tableWidget->setItem(i,1,new QTableWidgetItem(words[1]));
          ui->tableWidget->setItem(i,2,new QTableWidgetItem(words[2]));
          ui->tableWidget->setItem(i,3,new QTableWidgetItem(words[3]));
          i++;
       }
       List.close();
    }
}
/*Add Element*/
void MainWindow::on_pushButton_2_clicked()
{
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
}
/*Save DB*/
void MainWindow::on_pushButton_3_clicked()
{
    QFile List("/home/aleksandra/Документы/Cpp/ProductList/List.txt");
    List.resize(0);
    int i;
    if(List.open(QIODevice::Append|QIODevice::Text))
    {
        QTextStream in(&List);
        for(i=0; i< ui->tableWidget->rowCount();i++)
        {
            in<<ui->tableWidget->item(i,0)->text()<<"->"<<ui->tableWidget->item(i,1)->text()<<"->";
            in<<ui->tableWidget->item(i,2)->text()<<"->"<<ui->tableWidget->item(i,3)->text()<<endl;
        }
    }
}
/*Delete Table*/
void MainWindow::on_pushButton_4_clicked()
{
    ui->tableWidget->setRowCount(0);
}


void MainWindow::on_spinBox_valueChanged(int arg1)
{

}
/*Delete Row*/
void MainWindow::on_pushButton_5_clicked()
{
    ui->tableWidget->removeRow(ui->spinBox->value() - 1);
}
/*Continue to Step 2*/
void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    index = 1;
    int i;
    for(i=0; i< ui->tableWidget->rowCount();i++)
    {
        ID.append(ui->tableWidget->item(i,0)->text());
        Name.append(ui->tableWidget->item(i,1)->text());
        Shop.append(ui->tableWidget->item(i,2)->text());
        Price.append(ui->tableWidget->item(i,3)->text());
    }
    for(i=0; i< ui->tableWidget_2->rowCount();i++)
    {
        List.append(ui->tableWidget_2->item(i,0)->text());
    }
}
/*Add to Buying List*/
void MainWindow::on_pushButton_6_clicked()
{
    QString Product;
    Product=ui->textEdit->toPlainText();
    qDebug()<<ui->tableWidget_2->rowCount();
    ui->tableWidget_2->insertRow(ui->tableWidget_2->rowCount());
    ui->tableWidget_2->setItem(ui->tableWidget_2->rowCount() - 1,0,new QTableWidgetItem(Product));
}
/*remowe product from list*/
void MainWindow::on_pushButton_7_clicked()
{
    ui->tableWidget_2->removeRow(ui->spinBox_2->value() - 1);
}
/*load Product List*/
void MainWindow::on_pushButton_8_clicked()
{
    ui->tableWidget_2->setRowCount(0);
    QFile List("/home/aleksandra/Документы/Cpp/ProductList/ProductList.txt");
    if (List.open(QIODevice::ReadOnly))
    {
       QTextStream in(&List);
       while (!in.atEnd())
       {
          QString line = in.readLine();
          ui->tableWidget_2->insertRow(ui->tableWidget_2->rowCount());
          ui->tableWidget_2->setItem(ui->tableWidget_2->rowCount()-1,0,new QTableWidgetItem(line));
       }
       List.close();
    }
}
/*Something*/
void MainWindow::on_pushButton_9_clicked()
{
    class MainWindow *m;
    int lineNumber=ui->tableWidget->rowCount()-1;
    QStringList ListShops = b->findUniqueShop(m, lineNumber);
    QStringList ShopWithAllProduct = b->calculateTotalPrice(m, ListShops, List, lineNumber);
    for(int i =0; i < ShopWithAllProduct.size();i++)
    {
        QStringList BestShop = ShopWithAllProduct[i].split("->");
        ui->listWidget->addItem(BestShop[0]+" "+BestShop[1]);
    }
    BestPlace pl;
    pl = b->FindBestShop(ShopWithAllProduct);
    ui->listWidget_2->addItem(QString::number(pl.BestPrice));
    ui->listWidget_3->addItem(pl.BestShop);
    qDebug()<< pl.BestPrice;
}
