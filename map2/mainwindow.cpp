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
#include <QString>

class filter_main_fun{

};


class data_main_fun{
    public:
    virtual void first_setting()=0;
    virtual QVector<QStringList> get_data()=0;
    virtual bool statue()=0;
    virtual void data_split(QVector<QStringList> input)=0;
};

class database_getdata:public data_main_fun
{
private:
    std::string connect_sql;

    bool connect_statue=false;
    QStringList dataarray={};
    const int datarow = 6 ;

    void set_connect_sql()
    {
        connect_sql = "Driver={SQL Server};";
        connect_sql.append("Server=140.116.85.227,57964;");
        connect_sql.append("Database=NCKUfish;");
        connect_sql.append("Uid=root;");
        connect_sql.append("Pwd=123456;");
    }

public:
    QSqlDatabase db;
    void first_setting()
    {
        set_connect_sql();
        db =QSqlDatabase::addDatabase("QODBC");

        db.setDatabaseName(QString::fromStdString(connect_sql));
        if (db.open()){
            connect_statue = true;
            qDebug() << "connect"<< endl;

        }else{
            connect_statue = false;
            qDebug() << "unconnect"<< endl;
        }
    }

    QVector<QStringList> get_data()
    {
        QVector<QStringList> array1;
        QSqlTableModel model1;
        QStringList fonts={"","","","","",""};
        model1.setTable("fishdata");
        model1.select();
        for (int ii=0;ii<model1.rowCount();ii++){
        for (int i=0;i<model1.columnCount();i++)
        {
           fonts[i] = model1.data(model1.index(ii,i)).toString();
        }
           array1.append(fonts);
        }
        return array1;
    }

    bool statue(){
    return connect_statue;
    }

    void data_split(QVector<QStringList> input){

        for (int i=0;i<input.size();i++){
        qDebug() << input[i]<< endl;
        }
    }

};


class filter_data{
    public:
    QVector<QStringList> filter_fish(QVector<QStringList> olddata)
    {
        QVector<QStringList> array;
        for (int i=0 ; i<olddata.size();i++){
            if (olddata[i][2]=="tuna")
            {
                array.append(olddata[i]);
            }
        }
        return array;
    }


};


database_getdata *ddb = new database_getdata();


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ddb->first_setting();
    QVector<QStringList> ttemp =ddb->get_data();
    qDebug() << ttemp<< endl;
    if (ddb->statue()){
        QMessageBox::information(this,"connect","connect");
        ui->setupUi(this);
        ui->quickWidget->setSource(QUrl(QString("qrc:/map.qml")));
        ui->quickWidget->show();
        ui->widget_2->setVisible(false);
    }else{
        QMessageBox::information(this,"unconnect","unconnect");

    }
    ui->comboBox->addItem("123");
    ui->comboBox->addItem("124");
    auto obj = ui->quickWidget->rootObject();
    connect(this,SIGNAL(setCenter(QVariant,QVariant)),obj,SLOT(setCenter(QVariant,QVariant)));
    connect(this,SIGNAL(remove()),obj,SLOT(remove()));
    connect(this,SIGNAL(testd(QVariant )),obj,SLOT(testd(QVariant)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionreset_triggered()
{
    emit setCenter(22.9989,120.2169);
}


void MainWindow::on_actionclear_triggered()//clear()
{
    emit remove();
}


void MainWindow::on_pushButton_clicked()
{
    QVector<QStringList> data =ddb->get_data();
    qDebug() <<data.size() << endl;
    emit remove();

    for (int i=0;i<data.size();i++)
    {
       emit testd(data[i]);
    }

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


void MainWindow::on_pushButton_3_clicked()
{
    qDebug() <<"press 3" << endl;

}


void MainWindow::on_pushButton_2_clicked()
{
    QVector<QStringList> data =ddb->get_data();

    filter_data ss;

    QVector<QStringList> ddata = ss.filter_fish(data);
    qDebug() <<"press 2" << endl;
    qDebug() <<ddata << endl;

}

