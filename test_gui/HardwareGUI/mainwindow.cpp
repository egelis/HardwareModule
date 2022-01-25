#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , QoS(1)
{
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint |
                         Qt::WindowCloseButtonHint);
    ui->setupUi(this);

    log_model = new LogModel(this);
    proxy_model.setSourceModel(log_model);
    ui->Logger->setModel(&proxy_model);

    initServerAndDevices();

    defineConnections();
}


void MainWindow::initServerAndDevices()
{
    // Initialization of server
    std::cout << "Initializing for server '" << "127.0.0.1" << std::endl;
    client = new QMqttClient(this);
    client->setHostname("127.0.0.1");
    client->setPort(1883);
    client->setClientId("HardwareGUI");
    client->connectToHost();

    // Initialization of devices
    serial0     .init("/dev/ttyUSB0", 115200);
    motor       .init(&serial0, 1, "motor");
    control     .init(&serial0, 3, "control");
    experimental.init(&serial0, 5, "exper");

    serial0.openport();
}


void MainWindow::defineConnections()
{
    // Connects with timers //
    timer_1s = new QTimer();
    connect(timer_1s, &QTimer::timeout, this, &MainWindow::updateMotorInf);
    connect(timer_1s, &QTimer::timeout, this, &MainWindow::updateDiscInf);
    connect(timer_1s, &QTimer::timeout, this, &MainWindow::updateLightInf);
    connect(timer_1s, &QTimer::timeout, this, &MainWindow::updateKnifeInf);
    timer_1s->start(1'000);

    timer_10s = new QTimer();
    connect(timer_10s, &QTimer::timeout, this, &MainWindow::updateTempAndPres);
    timer_10s->start(10'000);

    // Buttons connects //
    connect(ui->m_start, &QPushButton::clicked, this, [this]{ client->publish(Topics::motor_topics["start"], QString::number(ui->m_timeout->value()).toUtf8() + " "
                                                                                 + QString::number(ui->m_position->value()).toUtf8(),
                                                                                 QoS, false); });
    connect(ui->m_stop, &QPushButton::clicked, this, [this]{ client->publish(Topics::motor_topics["stop"], "",
                                                                                 QoS, false); });
    connect(ui->l1_start, &QPushButton::clicked, this, [this]{ client->publish(Topics::experimental_topics["light_enable1"], QString::number(ui->l1_timeout->value()).toUtf8(),
                                                                                 QoS, false); });
    connect(ui->l2_start, &QPushButton::clicked, this, [this]{ client->publish(Topics::experimental_topics["light_enable2"], QString::number(ui->l2_timeout->value()).toUtf8(),
                                                                                 QoS, false); });
    connect(ui->ks_start, &QPushButton::clicked, this, [this]{ client->publish(Topics::experimental_topics["knifes_syncrocam_enable"], QString::number(ui->ks_timeout->value()).toUtf8() + " "
                                                                                 + QString(ui->ks_frequency->currentText()).toUtf8() + " "
                                                                                 + QString(ui->ks_imp_c->currentText()).toUtf8() + " "
                                                                                 + QString(ui->ks_imp_k->currentText()).toUtf8(),
                                                                                 QoS, false); });
    connect(ui->d_start, &QPushButton::clicked, this, [this] { client->publish(Topics::experimental_topics["disclosure"], QString::number(ui->d_timeout->value()).toUtf8(),
                                                                                 QoS, false); });

    // Mqtt connects //
    connect(client, &QMqttClient::stateChanged, this, &MainWindow::subscribeToTopics);
    connect(client, &QMqttClient::messageReceived, this, &MainWindow::recieveMesseges);
}

MainWindow::~MainWindow()
{
    std::cout << "\nShutting down and disconnecting from the MQTT server..." << std::flush;
    client->unsubscribe(QMqttTopicFilter{Topics::global_topics["motor"]});
    client->unsubscribe(QMqttTopicFilter{Topics::global_topics["control"]});
    client->unsubscribe(QMqttTopicFilter{Topics::global_topics["experiment"]});
    client->disconnectFromHost();
    std::cout << "OK" << std::endl;

    delete timer_1s;
    delete timer_10s;
    delete client;
    delete log_model;
    delete ui;
}


void MainWindow::subscribeToTopics()
{
    addLogToLogger(QString{QDateTime::currentDateTime().toString("hh:mm:ss")
                   + QLatin1String(": State Change ")
                   + QString::number(client->state())});

    if (client->state() == QMqttClient::Connected)
    {
        std::cout << "Connected" << std::endl;
        client->subscribe(QMqttTopicFilter{Topics::global_topics["motor"]}, QoS);
        client->subscribe(QMqttTopicFilter{Topics::global_topics["control"]}, QoS);
        client->subscribe(QMqttTopicFilter{Topics::global_topics["experiment"]}, QoS);

        addLogToLogger(QString{QDateTime::currentDateTime().toString("hh:mm:ss")
                       + QLatin1String(": Subscribed on topics: ")
                       + Topics::global_topics["motor"] + ", "
                       + Topics::global_topics["control"] + ", "
                       + Topics::global_topics["experiment"]});
    }
}


void MainWindow::recieveMesseges(const QByteArray &message, const QMqttTopicName &topic)
{
    const QString content = QDateTime::currentDateTime().toString("hh:mm:ss")
                + QLatin1String(" Received Topic: ")
                + topic.name()
                + QLatin1String(" Message: ")
                + message;

    // Если true, то логгируем в окно MQTT
    if (isLogging) {
        addLogToLogger(content, topic.name());
        ui->Logger->scrollToBottom();
    }

    parseTopics(topic.name(), message);
}


void MainWindow::addLogToLogger(const QString &content, const QString &topic) {
    log_model->addLog(Log{topic, content});
}


void MainWindow::parseTopics(const QString &topic, const QString &message)
{
    auto params = message.split(" ");

    // Motor
    if (topic == Topics::motor_topics["start"]) {
        motor.start(params[0].toFloat(), params[1].toFloat());
        isMotorStarted = true;
    }
    else if (topic == Topics::motor_topics["stop"]) {
        motor.stop();
        isMotorStarted = false;
    }
    // Vibrobank
    else if (topic == Topics::control_topics["vibrobank"]) {
        control.VibroBank(params[0].toFloat(), params[1].toFloat(), params[2].toInt(), params[3].toInt());
    }
    // Openbank
    else if (topic == Topics::control_topics["openbank"]) {
        control.OpenBank(params[0].toFloat(), params[1].toFloat(), params[2].toInt());
    }
    //Lights
    else if (topic == Topics::experimental_topics["light_enable1"]) {
        experimental.LightOne(params[0].toFloat());
        isLight1Started = true;
    }
    else if (topic == Topics::experimental_topics["light_enable2"]) {
        experimental.LightTwo(params[0].toFloat());
        isLight2Started = true;
    }
    // Disclosure
    else if (topic == Topics::experimental_topics["disclosure"]) {
        experimental.Disclousure(params[0].toFloat());
        isDiscStarted = true;
    }
    // Syncro and knives
    else if (topic == Topics::experimental_topics["knifes_syncrocam_enable"]) {
        experimental.SyncroCameras(params[0].toFloat(), params[1].toFloat(), params[2].toFloat(), params[3].toFloat());
        isKnifesStarted = true;
    }
}


void MainWindow::updateLightInf()
{
    if (isLight1Started) {
        const float current = experimental.getLightCurrentOne();

        if (!experimental.error) {
            client->publish(Topics::experimental_topics["light_current1"], QString::number(current).toUtf8(),
                            QoS, false);

            ui->l1_current->clear();
            ui->l1_current->insertPlainText(QString::number(current));

        } else {
            ui->l1_current->clear();
            ui->l1_current->insertPlainText(QString("Ошибка"));
            cout << "UpdateLight1 error" << endl;
            reconnectPort();
        }
    }

    if (isLight2Started) {
        const float current = experimental.getLightCurrentTwo();

        if (!experimental.error) {
            client->publish(Topics::experimental_topics["light_current2"], QString::number(current).toUtf8(),
                            QoS, false);

            ui->l2_current->clear();
            ui->l2_current->insertPlainText(QString::number(current));

        } else {
            ui->l2_current->clear();
            ui->l2_current->insertPlainText(QString("Ошибка"));
            cout << "UpdateLight2 error" << endl;
            reconnectPort();
        }
    }
}


void MainWindow::updateKnifeInf() {
    if (isKnifesStarted) {
        const float current1 = control.getKnifeCurrentOne();
        const float current2 = control.getKnifeCurrentTwo();

        if (!control.error) {
            client->publish(Topics::control_topics["knife_current1"], QString::number(current1).toUtf8(),
                            QoS, false);

            client->publish(Topics::control_topics["knife_current2"], QString::number(current2).toUtf8(),
                            QoS, false);

            ui->k1_current->clear();
            ui->k1_current->insertPlainText(QString::number(current1));

            ui->k2_current->clear();
            ui->k2_current->insertPlainText(QString::number(current2));

        } else {
            ui->k1_current->clear();
            ui->k1_current->insertPlainText(QString("Ошибка"));

            ui->k2_current->clear();
            ui->k2_current->insertPlainText(QString("Ошибка"));
            cout << "UpdateKnife error" << endl;
            reconnectPort();
        }
    }
}

void MainWindow::updateTempAndPres()
{
    const float ctrl_temp = control.getTemperatureCPU();
    const float ctrl_pres = control.getPressure();
    const float exp_temp = experimental.getTemperatureCPU();
    const float exp_pres = experimental.getPressure();

    if (!control.error && !experimental.error) {
        client->publish(Topics::control_topics["temperature"], QString::number(ctrl_temp).toUtf8(),
                        QoS, false);
        client->publish(Topics::control_topics["pressure"], QString::number(ctrl_pres).toUtf8(),
                        QoS, false);
        client->publish(Topics::experimental_topics["temperature"], QString::number(exp_temp).toUtf8(),
                        QoS, false);
        client->publish(Topics::experimental_topics["pressure"], QString::number(exp_pres).toUtf8(),
                        QoS, false);
    } else {
        cout << "UpdateTempAndPres error" << endl;
        reconnectPort();
    }
}

void MainWindow::updateDiscInf()
{
    if (isDiscStarted) {
        const int discStatus = experimental.getDisclousureStatus();

        if (!experimental.error)
        {
            if (discStatus == 1) {
                ui->d_status->setText("Откинуто");
            }
            else {
                ui->d_status->setText("Не откинуто");
            }
        } else {
            ui->d_status->setText("Ошибка");
            cout << "updateDiscInf error" << endl;
            reconnectPort();
        }
    }
}

void MainWindow::updateMotorInf()
{
    if (isMotorStarted) {
        const float vel       = motor.getVelocity();
        const float pos       = motor.getPosition();
        const int   status    = motor.getStatus();
        const int   endStatus = motor.getPositionEndStatus();

        if (!motor.error)
        {
            client->publish(Topics::motor_topics["position"], QString::number(pos).toUtf8(),
                            QoS, false);

            client->publish(Topics::motor_topics["velocity"], QString::number(vel).toUtf8(),
                            QoS, false);

            client->publish(Topics::motor_topics["status"], QString::number(status).toUtf8(),
                            QoS, false);

            ui->m_velocity->clear();
            ui->m_cur_position->clear();
            ui->m_velocity->insertPlainText(QString::number(vel));
            ui->m_cur_position->insertPlainText(QString::number(pos));

            if (endStatus == 1) {
                ui->m_status->setText("Конечная позиция\nдостигнута");
            }
            else {
                ui->m_status->setText("Конечная позиция\nне достигнута");
            }

        } else {
            ui->m_velocity->clear();
            ui->m_cur_position->clear();
            ui->m_velocity->insertPlainText(QString("Ошибка"));
            ui->m_cur_position->insertPlainText(QString("Ошибка"));
            ui->m_status->setText("Ошибка");
            cout << "UpdateMotorInf error" << endl;
            reconnectPort();
        }
    }
}


void MainWindow::reconnectPort()
{
    if (reconnect_timer.secsTo(QDateTime::currentDateTime()) >= 2)
    {
        addLogToLogger(QString{QDateTime::currentDateTime().toString("hh:mm:ss") +
                               ": Попытка переподключения порта..."}, "error");
        ui->Logger->scrollToBottom();

        serial0.closeport();
        serial0.openport();

        motor.reset();
        control.reset();
        experimental.reset();

        reconnect_timer = QDateTime::currentDateTime();
    }
}


void MainWindow::on_loggingState_clicked()
{
    if (isLogging) {
        ui->loggingState->setText("Продолжить вывод логов");
        isLogging = false;
    } else {
        ui->loggingState->setText("Остановить вывод логов");
        isLogging = true;
    }
}


void MainWindow::on_open_start_clicked()
{
    static QVector<QRadioButton*> radioButtons {ui->radioButton_1, ui->radioButton_2, ui->radioButton_3, ui->radioButton_4, ui->radioButton_5,
                                                ui->radioButton_6, ui->radioButton_7, ui->radioButton_8, ui->radioButton_9, ui->radioButton_10};

    size_t bank_num = 1;
    for (auto &checkBox: radioButtons) {
        if (checkBox->isChecked()) {
            client->publish(Topics::control_topics["openbank"], QString::number(ui->o_timeout->value()).toUtf8() + " "
                            + QString::number(ui->o_current->value()).toUtf8() + " "
                            + QString::number(bank_num).toUtf8(),
                            QoS, false);
        }
        ++bank_num;
    }
}


void MainWindow::on_vibro_start_clicked()
{
    static QVector<QCheckBox*> checkBoxes {ui->checkBox_1, ui->checkBox_2, ui->checkBox_3, ui->checkBox_4,
                                           ui->checkBox_5, ui->checkBox_6, ui->checkBox_7, ui->checkBox_8,
                                           ui->checkBox_9, ui->checkBox_10};

    size_t bank_num = 0;
    int mask = 0x00;
    for (auto &radioButton: checkBoxes) {
        if (radioButton->isChecked()) {
            int bank_mask = 0x01;
            bank_mask <<= bank_num;
            mask |= bank_mask;
        }
        ++bank_num;
    }

    client->publish(Topics::control_topics["vibrobank"], QString::number(ui->v_timeout->value()).toUtf8() + " "
                    + QString::number(ui->v_amplitude->value()).toUtf8() + " "
                    + QString::number(mask).toUtf8() + " "
                    + QString(ui->v_frequency->currentText()).toUtf8(),
                    QoS, false);
}

// TODO: Передавать каждый конкретный топик отдельно, чтобы не делить топики по непонятным категориям
void MainWindow::on_MotorView_stateChanged(int state)
{
    static const QVector<QString> motor_topics{Topics::motor_topics["start"],
                                               Topics::motor_topics["stop"],
                                               Topics::motor_topics["position"],
                                               Topics::motor_topics["velocity"],
                                               Topics::motor_topics["timeout"],
                                               Topics::motor_topics["end_status"]};

    changeTopicsInFilterLoogingAtState(state, motor_topics);
}


void MainWindow::on_LightsView_stateChanged(int state)
{
    static const QVector<QString> light_topics {Topics::experimental_topics["light_enable1"],
                                                Topics::experimental_topics["light_enable2"],
                                                Topics::experimental_topics["light_current1"],
                                                Topics::experimental_topics["light_current2"]};

    changeTopicsInFilterLoogingAtState(state, light_topics);
}


void MainWindow::on_KnifesView_stateChanged(int state)
{
    static const QVector<QString> knife_topics {Topics::control_topics["knife_current1"],
                                                Topics::control_topics["knife_current2"]};

    changeTopicsInFilterLoogingAtState(state, knife_topics);
}


void MainWindow::on_TempPres_stateChanged(int state)
{
    static const QVector<QString> temp_pres_topics {Topics::control_topics["temperature"],
                                                    Topics::control_topics["pressure"],
                                                    Topics::experimental_topics["temperature"],
                                                    Topics::experimental_topics["pressure"]};

    changeTopicsInFilterLoogingAtState(state, temp_pres_topics);
}

void MainWindow::on_VibrationView_stateChanged(int state)
{
    changeTopicsInFilterLoogingAtState(state, {Topics::control_topics["vibrobank"]});
}

void MainWindow::on_OpeningView_stateChanged(int state)
{
    changeTopicsInFilterLoogingAtState(state, {Topics::control_topics["openbank"]});
}

void MainWindow::on_SyncroView_stateChanged(int state)
{
    changeTopicsInFilterLoogingAtState(state, {Topics::experimental_topics["knifes_syncrocam_enable"]});
}

void MainWindow::on_DisclView_stateChanged(int state)
{
    changeTopicsInFilterLoogingAtState(state, {Topics::experimental_topics["disclosure"]});
}

void MainWindow::changeTopicsInFilterLoogingAtState(int state, const QVector<QString> &topics) {
    if (state == Qt::Checked) {
        proxy_model.EraseTopicsFromFilter(topics);
    } else {
        proxy_model.InsertTopicsInFilter(topics);
    }
}
