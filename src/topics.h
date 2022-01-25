#ifndef TOPICS_H
#define TOPICS_H

#include <string>
#include <map>

namespace Topics {
    // HARDWARE module topics
    const std::map<std::string, std::string> hw_status_topics{{"life_status", "/control_hardware/life_status"},
                                                              {"motor_life_status", "/control_hardware/motor_life_status"},
                                                              {"control_life_status", "/control_hardware/control_life_status"},
                                                              {"exper_life_status", "/control_hardware/exper_life_status"},};

    const std::map<std::string, std::string> global_topics{{"motor",      "/motor/#"},
                                                           {"control",    "/control/#"},
                                                           {"experiment", "/experiment/#"}};

    const std::map<std::string, std::string> motor_topics{{"start",        "/motor/start"},
                                                          {"stop",         "/motor/stop"},
                                                          {"position",     "/motor/position"},
                                                          {"velocity",     "/motor/velocity"},
                                                          {"timeout",      "/motor/timeout"},
                                                          {"end_status",   "/motor/end_status"},
                                                          {"ampl_voltage", "/motor/amplitude_voltage"},
                                                          {"ampl_current", "/motor/amplitude_current"}};

    const std::map<std::string, std::string> control_topics{{"vibrobank",           "/control/vibrobank"},
                                                            {"openbank",            "/control/openbank"},
                                                            {"overburning_current", "/control/overburning_current"},
                                                            {"knife_current1",      "/control/knife_current1"},
                                                            {"knife_current2",      "/control/knife_current2"},
                                                            {"temperature",         "/control/temperature"},
                                                            {"pressure",            "/control/pressure"}};

    const std::map<std::string, std::string> experimental_topics{{"disclosure",              "/experiment/disclosure"},
                                                                 {"disclosure_status",       "/experiment/disclosure_status"},
                                                                 {"knives_syncrocam_enable", "/experiment/knives_syncrocam_enable"},
                                                                 {"light_enable1",           "/experiment/light_enable1"},
                                                                 {"light_enable2",           "/experiment/light_enable2"},
                                                                 {"light_current1",          "/experiment/light_current1"},
                                                                 {"light_current2",          "/experiment/light_current2"},
                                                                 {"temperature",             "/experiment/temperature"},
                                                                 {"pressure",                "/experiment/pressure"}};
    // end of HARDWARE module topics


    // CAMERA module topics
    const std::map<std::string, std::string> camera_module_topics{{"recording", "dust-uv/Camera/Recording"},
                                                                  {"stop",      "dust-uv/Camera/Stop"},
                                                                  {"streaming", "dust-uv/Camera/Streaming"}};
    // end of CAMERA module topics


    //список топиков каждого модуля. Любой топик начинается с имени модуля: /<имя модуля>/<топик>
    const static std::map<std::string, std::string> module_base_topics{{"alive",   "/alive"}, // каждый модуль записывает в этот топик текущее время. Считаем его временной отметкой, когда модуль был жив
                                                                       {"started", "/started"}}; // булев флаг: запущен ли модуль. Означает, что модуль имеет подключение по MQTT и выполняет свою циклограмму (у каждого свою)

    //список топиков каждого модуля БУКа. Любой топик начинается с /MainModule/<приоритет(0, 1 или 2)>/<топик>
    //для мастер-модуля дублируются топики, но начинаются они с /MainModule/master/<топик>
    //мастер-модуль получает сообщения  на /MainModule/master/ и записывает их в свои топики и топики двух других модулей (/MainModule/<приоритет(0, 1 или 2)>/)
    const static std::map<std::string, std::string> master_module_topics{{"Index",                          "/Master/Master_index"}, //Индекс "мастера". Модуль, владеющий этим флагом, считается мастером. При установке своего флага в True, нужно двум другим модулям отправить False
                                                                         {"Status_power",                   "/Master/Status_power"}, //флаг, сообщающий включено питание 24 и 12В (Enable_1). или нет. Флаг только для чтения для всех, кроме мастера
                                                                         {"Status_AFU_power",               "/Master/Status_AFU_power"}, //Флаг питания АФУ. Только для чтения, кроме мастер-модуля.
                                                                         {"Status_AFU_switch",              "/Master/Status_AFU_switch"}, //Флаг состояния концевика АФУ. Только для чтения, кроме мастер-модуля.
                                                                         {"Status_AFU_opened",              "/Master/Status_AFU_opened"}, //Флаг состояния откидывания АФУ. Устанавливается по состоянию двух флагов: концевика и тока перезженной нити. Только для чтения, кроме мастер-модуля.
                                                                         {"Status_AFU_ready",               "/Master/Status_AFU_ready"}, //Флаг состояния АФУ (рабоатет/не работает). Означает, что АФУ работает "на излучение". Только для чтения, кроме мастер-модуля.
                                                                         {"Status_Camera1",                 "/Master/Status_Camera1"}, //Флаг состояния камеры 1 (рабоатет/не работает). Только для чтения, кроме мастер-модуля.
                                                                         {"Status_Сamera1_stream",          "/Master/Status_Сamera1_stream"}, //Флаг состояния видеопотока камеры 1 (шлет/не шлет). Только для чтения, кроме мастер-модуля.
                                                                         {"Status_Сamera2",                 "/Master/Status_Сamera2"}, //Флаг состояния камеры 2 (рабоатет/не работает). Только для чтения, кроме мастер-модуля.
                                                                         {"Status_Сamera2_stream",          "/Master/Status_Сamera2_stream"}, //Флаг состояния видеопотока камеры 2 (шлет/не шлет). Только для чтения, кроме мастер-модуля.
                                                                         {"Status_Сamera3",                 "/Master/Status_Сamera3"}, //Флаг состояния камеры 3 (рабоатет/не работает). Только для чтения, кроме мастер-модуля.
                                                                         {"Status_Сamera3_stream",          "/Master/Status_Сamera3_stream"}, //Флаг состояния видеопотока камеры 3 (шлет/не шлет). Только для чтения, кроме мастер-модуля.
                                                                         {"Status_Truss_switch",            "/Master/Status_Truss_switch"}, // Концевик выдвижения фермы с ЭПП. Только для чтения, кроме мастер-модуля.
                                                                         {"Status_Truss_motor",             "/Master/Status_Truss_motor"}, // Счетчик оборотов двигателя выдвижения фермы с ЭПП. Только для чтения, кроме мастер-модуля.
                                                                         {"Status_Technological_vibration", "/Master/Status_Technological_vibration"}, // Флаг технологической вибрации. Только для чтения, кроме мастер-модуля.
                                                                         {"Status_session_started",         "/Master/Status_session_started"}, // Индекс работающей сессии. Только для чтения, кроме мастер-модуля.
                                                                         {"Status_light_1",         "/Master/Status_light_1"}, // Индекс работающей сессии. Только для чтения, кроме мастер-модуля.
                                                                         {"Status_light_2",         "/Master/Status_light_2"}, // Индекс работающей сессии. Только для чтения, кроме мастер-модуля.

                                                                         {"Status_bank_0",                  "/Master/Status_bank_0"}, // Статус банки №0. Только для чтения, кроме мастер-модуля.
                                                                         {"Status_bank_1",                  "/Master/Status_bank_1"}, // Статус банки №1. Только для чтения, кроме мастер-модуля.
                                                                         {"Status_bank_2",                  "/Master/Status_bank_2"}, // Статус банки №2. Только для чтения, кроме мастер-модуля.
                                                                         {"Status_bank_3",                  "/Master/Status_bank_3"}, // Статус банки №3. Только для чтения, кроме мастер-модуля.
                                                                         {"Status_bank_4",                  "/Master/Status_bank_4"}, // Статус банки №4. Только для чтения, кроме мастер-модуля.
                                                                         {"Status_bank_5",                  "/Master/Status_bank_5"}, // Статус банки №5. Только для чтения, кроме мастер-модуля.
                                                                         {"Status_bank_6",                  "/Master/Status_bank_6"}, // Статус банки №6. Только для чтения, кроме мастер-модуля.
                                                                         {"Status_bank_7",                  "/Master/Status_bank_7"}, // Статус банки №7. Только для чтения, кроме мастер-модуля.
                                                                         {"Status_bank_8",                  "/Master/Status_bank_8"}, // Статус банки №8. Только для чтения, кроме мастер-модуля.
                                                                         {"Status_bank_9",                  "/Master/Status_bank_9"}, // Статус банки №9. Только для чтения, кроме мастер-модуля.


                                                                         {"Сommand_push_truss",             "/Master/Command_push_truss"}, // Команда выдвижения фермы с ЭПП. Обрабатывает только мастер. У остальных только выставляется соответствующий флаг
                                                                         {"Command_vibrate_bank",           "/Master/Command_vibrate_bank"}, // Команда выдвижения фермы с ЭПП. Обрабатывает только мастер. У остальных только выставляется соответствующий флаг
                                                                         {"Command_open_bank",              "/Master/Command_open_bank"}, // Команда выдвижения фермы с ЭПП. Обрабатывает только мастер. У остальных только выставляется соответствующий флаг
                                                                         {"Command_open_AFU",               "/Master/Command_open_AFU"}, // Команда выдвижения фермы с ЭПП. Обрабатывает только мастер. У остальных только выставляется соответствующий флаг
                                                                         {"Command_start_session",          "/Master/Command_start_session"}, // Команда выдвижения фермы с ЭПП. Обрабатывает только мастер. У остальных только выставляется соответствующий флаг
                                                                         {"Command_enable_light_1",          "/Master/Command_enable_light_1"}, // Команда выдвижения фермы с ЭПП. Обрабатывает только мастер. У остальных только выставляется соответствующий флаг
                                                                         {"Command_enable_light_2",          "/Master/Command_enable_light_2"}, // Команда выдвижения фермы с ЭПП. Обрабатывает только мастер. У остальных только выставляется соответствующий флаг
    };


}

#endif // TOPICS_H
