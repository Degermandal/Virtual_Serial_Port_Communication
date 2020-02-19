#include "mainwindow.h"
#include <iostream>
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <timeoutserial.h>
#include <adapter.h>
#include<myserver.h>
#include <fstream>

using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;
std::unique_ptr<MyServer> g_http;
void on_initialize(const string_t& address)
{
   uri_builder uri(address);
   auto addr = uri.to_uri().to_string();
   g_http=std::unique_ptr<MyServer>(new MyServer(addr));
   g_http->open().wait();
   ucout<<utility::string_t(U("listening to requests at:")) << addr <<std::endl;
   return;
}

void on_shutdown()
{
    g_http->close();
    return;
}
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    serialPortLabel(new QLabel(tr("Serial port:"))),
    serialPortComboBox(new QComboBox),
    baudRate(new QLabel(tr("Baud Rate:"))),
    baudRateComboBox(new QComboBox),
    waitResponseLabel(new QLabel(tr("Wait response, msec:"))),
    waitResponseSpinBox(new QSpinBox),
    requestLabel(new QLabel(tr("Request:"))),
    requestLineEdit(new QLineEdit(tr("Init"))),
    runButton(new QPushButton(tr("Start"))){
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos)
        serialPortComboBox->addItem(info.portName());
    baudRateComboBox->addItems({"9600", "14400", "19200", "38400", "57600", "115200"});
    baudRateComboBox->setCurrentText("19200");
    waitResponseSpinBox->setRange(0, 10000);
    waitResponseSpinBox->setValue(1000);


    auto mainLayout = new QGridLayout;
    mainLayout->addWidget(serialPortLabel, 0, 0);
    mainLayout->addWidget(serialPortComboBox, 0, 1);
    mainLayout->addWidget(baudRate, 1, 0);
    mainLayout->addWidget(baudRateComboBox, 1, 1);
    mainLayout->addWidget(waitResponseLabel, 2, 0);
    mainLayout->addWidget(waitResponseSpinBox, 2, 1);
    mainLayout->addWidget(runButton, 0, 2, 2, 1);
    mainLayout->addWidget(requestLabel, 3, 0);
    mainLayout->addWidget(requestLineEdit, 3, 1, 1, 3);

    auto central = new QWidget;
    central->setLayout(mainLayout);
    setCentralWidget(central);
    std::fstream config;
    config.open("config.txt");
    char *url = new char[256];
    char *s = new char[256];
    config.getline(s,256,'\n');
    config.getline(s,256,'\n');
    config.getline(s,256,'=');
    config.getline(url,256,'\n');
    setWindowTitle(tr("Qt Serio"));
    serialPortComboBox->setFocus();
    connect(runButton, &QPushButton::clicked,this, &MainWindow::makeConnection);
    utility::string_t address=(url);
    on_initialize((address));

}

void MainWindow::showError(const QString &s){

}

void MainWindow::makeConnection(){
//    SimpleSerial serial("/dev/"+serialPortComboBox->currentText().toStdString() ,std::stoi(baudRateComboBox->currentText().toStdString() ));
//    serial.writeString(requestLineEdit->text().toStdString()+'\x03');
//    std::cout<<requestLineEdit->text().toStdString()<<std::endl;
}


MainWindow::~MainWindow(){
}
