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
#include <QCompleter>
#include <QtCharts>


class filter_main_fun{
    public:
    virtual QVector<QStringList> filter_tuna(QVector<QStringList> olddata,QString Filter_target)=0;
    virtual QStringList filter_id(QVector<QStringList> data);
    virtual QVector<QStringList> filter_certain_id(QVector<QStringList> data,QString Id);
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
        }else{
            connect_statue = false;
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
    QVector<QStringList> filter_tuna(QVector<QStringList> olddata,QString Filter_target)
    {
        QVector<QStringList> array;
        for (int i=0 ; i<olddata.size();i++){
            if (olddata[i][2]==Filter_target)
            {
                array.append(olddata[i]);
            }
        }
        return array;
    }

    QStringList filter_id(QVector<QStringList> data)
    {
        QStringList array;
        for (int i=0 ; i<data.size();i++){
            bool statue = _Search(array , data[i][1]);
            if(statue){
                array.append(data[i][1]);
            }
        }
        if(array.length()>1){
            array.append("Not_Limit");
        }
        return array;
    }

    QVector<QStringList> filter_certain_id(QVector<QStringList> data,QString Id)
    {
        QVector<QStringList> f_data;
        for (int i=0 ; i<data.size();i++){
            if (data[i][1]==Id){
                f_data.append(data[i]);
            }
        }

        return f_data;
    }

    private:

    bool _Search(QStringList Name_list,QString Target){
        bool statue =true;
        for(int i=0 ; i<Name_list.length();i++){
            if(Name_list[i]==Target){
                statue =false;
                break;
            }
        }
        return statue;
    }
};


////////////////////////////////////start here/////////////////////////////////////////////////////////////////////////////////////////

database_getdata *ddb = new database_getdata();
QCompleter *completer = new QCompleter();

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
    //ui->comboBox->addItem("123");
    //ui->comboBox->addItem("124");

    QStringList wordList;
    wordList << "alpha" << "omega" << "omicron" << "zeta";
    QStringList wwordList;
    wwordList << "aalpha" << "oomega" << "oomicron" << "zzeta";


    //QCompleter *completer = new QCompleter(wordList, this);
    completer->setModel(new QStringListModel( wordList, completer ) );
    completer->setCaseSensitivity(Qt::CaseInsensitive);

    //QLineEdit *lineedit =new QLineEdit(this);
    ui->comboBox->setCurrentIndex(0);
    ui->comboBox->setCompleter(completer);
    ui->comboBox->setItemDelegate(new QItemDelegate);
    ui->comboBox->addItems(wordList);
    ui->comboBox->clear();
    completer->setModel(new QStringListModel( wwordList, completer ) );
    ui->comboBox->addItems(wwordList);


    //ui->comboBox->addItem("1230");
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
    QMessageBox::information(this,"statue",ui->comboBox->currentText());
    ui->quickWidget->setVisible(0);

}


void MainWindow::on_pushButton_2_clicked()
{
    ui->quickWidget->setVisible(1);
    QVector<QStringList> data =ddb->get_data();

    filter_data ss;

    QVector<QStringList> ddata = ss.filter_tuna(data,"tuna");
    qDebug() <<"press 2" << endl;
    qDebug() <<ddata << endl;

}


void MainWindow::plot_map(){
    emit remove();
    filter_data *ss=new filter_data;
    QVector<QStringList> *ffilter_data= new QVector<QStringList>;
    QVector<QStringList> data =ddb->get_data();
    QStringList Data_statue={QString::number(int(Qt::Checked ==ui->Tuna_filter_checkbox->checkState())),
                             QString::number(int(Qt::Checked ==ui->Shark_filter_checkbox->checkState())),
                             QString::number(int(Qt::Checked ==ui->Marlin_filter_checkbox->checkState()))};
    QStringList Data_target={"tuna","shark","marlin"};
    for (int i=0;i<Data_statue.length();i++){
        if(Data_statue[i]=="1"){
            QVector<QStringList> ddata = ss->filter_tuna(data,Data_target[i]);
            ffilter_data->append(ddata);
        }
    }
    qDebug() <<*ffilter_data<<endl;
    QStringList Id_array=ss->filter_id(*ffilter_data);
    qDebug() <<Id_array<<endl;


    completer->setModel(new QStringListModel( Id_array, completer ) );
    ui->comboBox->clear();
    ui->comboBox->addItems(Id_array);
    if(Id_array.length()>1){
        ui->comboBox->setCurrentIndex(Id_array.length()-1);
    }
    for (int i=0;i<ffilter_data->length();i++){
        emit testd((*ffilter_data)[i]);
    }
    delete ffilter_data;
    delete ss;
}


void MainWindow::plot_map(int i){
    emit remove();
    filter_data *ss=new filter_data;
    QVector<QStringList> *ffilter_data= new QVector<QStringList>;
    QVector<QStringList> data =ddb->get_data();
    QStringList Data_statue={QString::number(int(Qt::Checked ==ui->Tuna_filter_checkbox->checkState())),
                             QString::number(int(Qt::Checked ==ui->Shark_filter_checkbox->checkState())),
                             QString::number(int(Qt::Checked ==ui->Marlin_filter_checkbox->checkState()))};
    QStringList Data_target={"tuna","shark","marlin"};
    for (int i=0;i<Data_statue.length();i++){
        if(Data_statue[i]=="1"){
            QVector<QStringList> ddata = ss->filter_tuna(data,Data_target[i]);
            ffilter_data->append(ddata);
        }
    }
    QVector<QStringList> *f_data=new QVector<QStringList>;
    if (ui->comboBox->currentText() != "Not_Limit"){
        f_data->append(ss->filter_certain_id(*ffilter_data,ui->comboBox->currentText()));
    //qDebug() <<"hello"<<f_data << endl;
    }else{
        f_data->append(*ffilter_data);

    }
    qDebug() <<"www"<<f_data->length()<< endl;

    for(int i=0;i<f_data->length();i++){
         //qDebug() <<"www"<<i<< endl;
        emit testd((*f_data)[i]);
    }
    delete ss;
    delete f_data;
    delete ffilter_data;
}


void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    qDebug() <<ui->comboBox->currentText() << endl;
    qDebug() <<QString::number(int(Qt::Checked ==ui->Tuna_filter_checkbox->checkState())) <<endl;
    plot_map(0);
}


void MainWindow::Change_buttom_statue(int i){
    ui->Allfish_filter_checkbox->setChecked(i);
    ui->radioButton->setChecked(i);
    ui->Marlin_filter_checkbox->setChecked(i);
    ui->Shark_filter_checkbox->setChecked(i);
    ui->Tuna_filter_checkbox->setChecked(i);
}


void MainWindow::on_Tuna_filter_checkbox_clicked()
{
    plot_map();
    if (Qt::Checked == ui->Tuna_filter_checkbox->checkState()){
        //Change_buttom_statue();
        ui->Tuna_filter_checkbox->setChecked(1);
    }else{
        //Change_buttom_statue();
        //ui->Allfish_filter_checkbox->setChecked(1);
    }

}


void MainWindow::on_Shark_filter_checkbox_clicked()
{
    plot_map();
    if (Qt::Checked == ui->Shark_filter_checkbox->checkState()){
        //Change_buttom_statue();
        ui->Shark_filter_checkbox->setChecked(1);
    }else{
        //Change_buttom_statue();
        //ui->Allfish_filter_checkbox->setChecked(1);
    }

}


void MainWindow::on_Marlin_filter_checkbox_clicked()
{
    plot_map();
    if (Qt::Checked == ui->Marlin_filter_checkbox->checkState()){
        //Change_buttom_statue();
        ui->Marlin_filter_checkbox->setChecked(1);
    }else{
        //Change_buttom_statue();
        //ui->Allfish_filter_checkbox->setChecked(1);
    }

}





void MainWindow::on_Allfish_filter_checkbox_clicked()
{
    if (Qt::Checked == ui->Allfish_filter_checkbox->checkState()){
        Change_buttom_statue(1);
    }else{
        Change_buttom_statue(0);
        //Change_buttom_statue();
        //ui->Allfish_filter_checkbox->setChecked(1);
    }
    plot_map();
}

