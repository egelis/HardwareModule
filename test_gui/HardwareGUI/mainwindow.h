#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>

#include <QMainWindow>
#include <QDateTime>
#include <QTimer>
#include <QScrollBar>
#include <QtMqtt/QMqttClient>
#include <QStringListModel>

#include "topics.h"
#include "logmodel.h"
#include "topicfilterproxymodel.h"

#include "../../Common/ModbusLib/serial.hpp"
#include "../../Common/ModbusLib/modbus_ls_dust.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    LogModel *log_model;
    QMqttClient *client;
    TopicFilterProxyModel proxy_model;
    int QoS;

    QTimer *timer_1s,
           *timer_10s;

    QDateTime reconnect_timer = QDateTime::currentDateTime();

    // Devices
    serial                      serial0;
    modbus_ls_dust_motor        motor;
    modbus_ls_dust_control      control;
    modbus_ls_dust_experimental experimental;

    // Devices states
    bool isMotorStarted  = false,
         isLight1Started = false,
         isLight2Started = false,
         isKnifesStarted = false,
         isDiscStarted   = false;

    // Gui states
    bool isLogging = true;

    void changeTopicsInFilterLoogingAtState(int state, const QVector<QString> &topics);
    void addLogToLogger(const QString &content, const QString &topic = "");
    void parseTopics(const QString &topic, const QString &message);
    void initServerAndDevices();
    void defineConnections();

private slots:
    void reconnectPort();

    void updateDiscInf();
    void updateMotorInf();
    void updateTempAndPres();
    void updateLightInf();
    void updateKnifeInf();

    // Mqtt
    void subscribeToTopics();
    void recieveMesseges(const QByteArray &message, const QMqttTopicName &topic);

    void on_loggingState_clicked();
    void on_open_start_clicked();
    void on_vibro_start_clicked();

    // Logger view panel
    void on_MotorView_stateChanged(int state);
    void on_LightsView_stateChanged(int state);
    void on_KnifesView_stateChanged(int state);
    void on_TempPres_stateChanged(int state);
    void on_VibrationView_stateChanged(int state);
    void on_OpeningView_stateChanged(int state);
    void on_SyncroView_stateChanged(int state);
    void on_DisclView_stateChanged(int state);
};
#endif // MAINWINDOW_H
