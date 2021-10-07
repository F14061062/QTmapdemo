#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QQuickItem>
#include<QtSql/QtSql>
#include<QtSql/QSqlDatabase>
#include<QMessageBox>
#include<QtSql/QSqlQuery>
#include<QDebug>
#include <QSqlQueryModel>
#include <iostream>
#include <QVector>
#include <QVector2D>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->quickWidget->setSource(QUrl(QString("qrc:/map.qml")));
    ui->quickWidget->show();
    ui->widget_2->setVisible(false);
    QSqlDatabase db =QSqlDatabase::addDatabase("QODBC");
    QString connectString = "Driver={SQL Server};"; // Driver is now Driver={SQL Server Native Client 11.0};
    connectString.append("Server=140.116.85.227,57964;"); // IP,Port
    connectString.append("Database=NCKUfish;");  // Schema
    connectString.append("Uid=root;");           // User
    connectString.append("Pwd=123456;");           // Pass
    db.setDatabaseName(connectString);
    if (db.open()){
    }else{
    QMessageBox::information(this,"unconnect","unconnect");

    }
    //db.setHostName("140.116.85.227");
    //db.setPort(57964);
    //db.setUserName("root");
    //db.setPassword("123456");
    //db.setDatabaseName("Student1");
    //db.open();



    auto obj = ui->quickWidget->rootObject();
    connect(this,SIGNAL(setCenter(QVariant,QVariant)),obj,SLOT(setCenter(QVariant,QVariant)));
    connect(this,SIGNAL(remove()),obj,SLOT(remove()));
    connect(this,SIGNAL(testd(QVariant )),obj,SLOT(testd(QVariant)));
    //emit setCenter(25.000,50.000);



}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_actionreset_triggered()
{
    emit setCenter(25.000,50.000);
}


void MainWindow::on_actionclear_triggered()
{
    emit remove();
}


void MainWindow::on_pushButton_clicked()
{
    QSqlDatabase db =QSqlDatabase::addDatabase("QODBC");
    QString connectString = "Driver={SQL Server};"; // Driver is now Driver={SQL Server Native Client 11.0};
    connectString.append("Server=140.116.85.227,57964;"); // IP,Port
    connectString.append("Database=NCKUfish;");  // Schema
    connectString.append("Uid=root;");           // User
    connectString.append("Pwd=123456;");           // Pass
    db.setDatabaseName(connectString);
    if (db.open()){
    QMessageBox::information(this,"connect","connect");

    }else{
    QMessageBox::information(this,"unconnect","unconnect");

    }
    QStringList list = db.tables(QSql::Tables);
    for(int i=0;i<list.size(); ++i)
    {
       qDebug() << "Table names " << list.at(i) << endl;
    }

    //QSqlQueryModel model;
    //model.setQuery("USE Student1;");
    //model.setQuery("Select * From StudentsInfo;");
    //QString salary = model.data(model.index(1, 1)).toString();
    //qDebug() << "Table names " << (salary=="") << endl;
    //for(int i=0;i<7; ++i)
    //{
    //    salary = model.data(model.index(0, i)).toString();
    //   qDebug() << "variable " << salary << endl;
    //}
    QSqlTableModel model1;
    model1.setTable("StudentsInfo");
    model1.select();
    int salary = model1.data(model1.index(0,0)).toInt();
    qDebug() << "variable " << salary << endl;
    qDebug() << "bool" << ui->widget_2->isVisible() <<endl;

}


void MainWindow::on_pushButton_4_clicked()
{
    if (ui->widget_3->isVisible()){
        ui->widget_2->setVisible(true);
        ui->widget_3->setVisible(false);

    }else
    {
        ui->widget_2->setVisible(false);
        ui->widget_3->setVisible(true);
    }

}


void MainWindow::mssql_get_datafun1()
{
    QSqlTableModel model1;
    QStringList fonts={"","","","","",""};
    model1.setTable("fishdata");
    model1.select();
    //QString salary = model1.data(model1.index(0,0)).toString();
    for (int ii=0;ii<model1.rowCount();ii++){
    for (int i=0;i<model1.columnCount();i++)
    {
       fonts[i] = model1.data(model1.index(ii,i)).toString();;
    }
    emit testd(fonts);
    qDebug() << fonts << endl;
    }



}

void MainWindow::on_pushButton_3_clicked()
{
    std::string tat[]={"ssff","dd","aa","ss","ss"};
    std::cout << sizeof(tat)/sizeof(tat[0]) << std::endl;
    QStringList fonts = { "Arial", "Helvetica", "Times" };
    QVector<QStringList> dvector(200);
    dvector[0]=fonts;
    fonts[2]="ddsds";
    dvector[1]=fonts;
    qDebug() << "Table names " << dvector[0] << endl;
    qDebug() << "Table names " << dvector[1] << endl;
    MainWindow::mssql_get_datafun1();

    //emit testd(dvector[1]);

}

