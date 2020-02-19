#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSerialPortInfo>
#include <QSpinBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
     void showError(const QString &s);
     void makeConnection();

private:
    int m_transactionCount = 0;
    QLabel *serialPortLabel = nullptr;
    QComboBox *serialPortComboBox = nullptr;
    QLabel *baudRate = nullptr;
    QComboBox *baudRateComboBox = nullptr;
    QLabel *waitResponseLabel = nullptr;
    QSpinBox *waitResponseSpinBox = nullptr;
    QLabel *requestLabel = nullptr;
    QLineEdit *requestLineEdit = nullptr;
    QPushButton *runButton = nullptr;
};

#endif // MAINWINDOW_H
