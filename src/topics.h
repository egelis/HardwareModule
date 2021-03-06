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


    //???????????? ?????????????? ?????????????? ????????????. ?????????? ?????????? ???????????????????? ?? ?????????? ????????????: /<?????? ????????????>/<??????????>
    const static std::map<std::string, std::string> module_base_topics{{"alive",   "/alive"}, // ???????????? ???????????? ???????????????????? ?? ???????? ?????????? ?????????????? ??????????. ?????????????? ?????? ?????????????????? ????????????????, ?????????? ???????????? ?????? ??????
                                                                       {"started", "/started"}}; // ?????????? ????????: ?????????????? ???? ????????????. ????????????????, ?????? ???????????? ?????????? ?????????????????????? ???? MQTT ?? ?????????????????? ???????? ?????????????????????? (?? ?????????????? ????????)

    //???????????? ?????????????? ?????????????? ???????????? ????????. ?????????? ?????????? ???????????????????? ?? /MainModule/<??????????????????(0, 1 ?????? 2)>/<??????????>
    //?????? ????????????-???????????? ?????????????????????? ????????????, ???? ???????????????????? ?????? ?? /MainModule/master/<??????????>
    //????????????-???????????? ???????????????? ??????????????????  ???? /MainModule/master/ ?? ???????????????????? ???? ?? ???????? ???????????? ?? ???????????? ???????? ???????????? ?????????????? (/MainModule/<??????????????????(0, 1 ?????? 2)>/)
    const static std::map<std::string, std::string> master_module_topics{{"Index",                          "/Master/Master_index"}, //???????????? "??????????????". ????????????, ?????????????????? ???????? ????????????, ?????????????????? ????????????????. ?????? ?????????????????? ???????????? ?????????? ?? True, ?????????? ???????? ???????????? ?????????????? ?????????????????? False
                                                                         {"Status_power",                   "/Master/Status_power"}, //????????, ???????????????????? ???????????????? ?????????????? 24 ?? 12?? (Enable_1). ?????? ??????. ???????? ???????????? ?????? ???????????? ?????? ????????, ?????????? ??????????????
                                                                         {"Status_AFU_power",               "/Master/Status_AFU_power"}, //???????? ?????????????? ??????. ???????????? ?????? ????????????, ?????????? ????????????-????????????.
                                                                         {"Status_AFU_switch",              "/Master/Status_AFU_switch"}, //???????? ?????????????????? ?????????????????? ??????. ???????????? ?????? ????????????, ?????????? ????????????-????????????.
                                                                         {"Status_AFU_opened",              "/Master/Status_AFU_opened"}, //???????? ?????????????????? ?????????????????????? ??????. ?????????????????????????????? ???? ?????????????????? ???????? ????????????: ?????????????????? ?? ???????? ?????????????????????? ????????. ???????????? ?????? ????????????, ?????????? ????????????-????????????.
                                                                         {"Status_AFU_ready",               "/Master/Status_AFU_ready"}, //???????? ?????????????????? ?????? (????????????????/???? ????????????????). ????????????????, ?????? ?????? ???????????????? "???? ??????????????????". ???????????? ?????? ????????????, ?????????? ????????????-????????????.
                                                                         {"Status_Camera1",                 "/Master/Status_Camera1"}, //???????? ?????????????????? ???????????? 1 (????????????????/???? ????????????????). ???????????? ?????? ????????????, ?????????? ????????????-????????????.
                                                                         {"Status_??amera1_stream",          "/Master/Status_??amera1_stream"}, //???????? ?????????????????? ?????????????????????? ???????????? 1 (????????/???? ????????). ???????????? ?????? ????????????, ?????????? ????????????-????????????.
                                                                         {"Status_??amera2",                 "/Master/Status_??amera2"}, //???????? ?????????????????? ???????????? 2 (????????????????/???? ????????????????). ???????????? ?????? ????????????, ?????????? ????????????-????????????.
                                                                         {"Status_??amera2_stream",          "/Master/Status_??amera2_stream"}, //???????? ?????????????????? ?????????????????????? ???????????? 2 (????????/???? ????????). ???????????? ?????? ????????????, ?????????? ????????????-????????????.
                                                                         {"Status_??amera3",                 "/Master/Status_??amera3"}, //???????? ?????????????????? ???????????? 3 (????????????????/???? ????????????????). ???????????? ?????? ????????????, ?????????? ????????????-????????????.
                                                                         {"Status_??amera3_stream",          "/Master/Status_??amera3_stream"}, //???????? ?????????????????? ?????????????????????? ???????????? 3 (????????/???? ????????). ???????????? ?????? ????????????, ?????????? ????????????-????????????.
                                                                         {"Status_Truss_switch",            "/Master/Status_Truss_switch"}, // ???????????????? ???????????????????? ?????????? ?? ??????. ???????????? ?????? ????????????, ?????????? ????????????-????????????.
                                                                         {"Status_Truss_motor",             "/Master/Status_Truss_motor"}, // ?????????????? ???????????????? ?????????????????? ???????????????????? ?????????? ?? ??????. ???????????? ?????? ????????????, ?????????? ????????????-????????????.
                                                                         {"Status_Technological_vibration", "/Master/Status_Technological_vibration"}, // ???????? ?????????????????????????????? ????????????????. ???????????? ?????? ????????????, ?????????? ????????????-????????????.
                                                                         {"Status_session_started",         "/Master/Status_session_started"}, // ???????????? ???????????????????? ????????????. ???????????? ?????? ????????????, ?????????? ????????????-????????????.
                                                                         {"Status_light_1",         "/Master/Status_light_1"}, // ???????????? ???????????????????? ????????????. ???????????? ?????? ????????????, ?????????? ????????????-????????????.
                                                                         {"Status_light_2",         "/Master/Status_light_2"}, // ???????????? ???????????????????? ????????????. ???????????? ?????? ????????????, ?????????? ????????????-????????????.

                                                                         {"Status_bank_0",                  "/Master/Status_bank_0"}, // ???????????? ?????????? ???0. ???????????? ?????? ????????????, ?????????? ????????????-????????????.
                                                                         {"Status_bank_1",                  "/Master/Status_bank_1"}, // ???????????? ?????????? ???1. ???????????? ?????? ????????????, ?????????? ????????????-????????????.
                                                                         {"Status_bank_2",                  "/Master/Status_bank_2"}, // ???????????? ?????????? ???2. ???????????? ?????? ????????????, ?????????? ????????????-????????????.
                                                                         {"Status_bank_3",                  "/Master/Status_bank_3"}, // ???????????? ?????????? ???3. ???????????? ?????? ????????????, ?????????? ????????????-????????????.
                                                                         {"Status_bank_4",                  "/Master/Status_bank_4"}, // ???????????? ?????????? ???4. ???????????? ?????? ????????????, ?????????? ????????????-????????????.
                                                                         {"Status_bank_5",                  "/Master/Status_bank_5"}, // ???????????? ?????????? ???5. ???????????? ?????? ????????????, ?????????? ????????????-????????????.
                                                                         {"Status_bank_6",                  "/Master/Status_bank_6"}, // ???????????? ?????????? ???6. ???????????? ?????? ????????????, ?????????? ????????????-????????????.
                                                                         {"Status_bank_7",                  "/Master/Status_bank_7"}, // ???????????? ?????????? ???7. ???????????? ?????? ????????????, ?????????? ????????????-????????????.
                                                                         {"Status_bank_8",                  "/Master/Status_bank_8"}, // ???????????? ?????????? ???8. ???????????? ?????? ????????????, ?????????? ????????????-????????????.
                                                                         {"Status_bank_9",                  "/Master/Status_bank_9"}, // ???????????? ?????????? ???9. ???????????? ?????? ????????????, ?????????? ????????????-????????????.


                                                                         {"??ommand_push_truss",             "/Master/Command_push_truss"}, // ?????????????? ???????????????????? ?????????? ?? ??????. ???????????????????????? ???????????? ????????????. ?? ?????????????????? ???????????? ???????????????????????? ?????????????????????????????? ????????
                                                                         {"Command_vibrate_bank",           "/Master/Command_vibrate_bank"}, // ?????????????? ???????????????????? ?????????? ?? ??????. ???????????????????????? ???????????? ????????????. ?? ?????????????????? ???????????? ???????????????????????? ?????????????????????????????? ????????
                                                                         {"Command_open_bank",              "/Master/Command_open_bank"}, // ?????????????? ???????????????????? ?????????? ?? ??????. ???????????????????????? ???????????? ????????????. ?? ?????????????????? ???????????? ???????????????????????? ?????????????????????????????? ????????
                                                                         {"Command_open_AFU",               "/Master/Command_open_AFU"}, // ?????????????? ???????????????????? ?????????? ?? ??????. ???????????????????????? ???????????? ????????????. ?? ?????????????????? ???????????? ???????????????????????? ?????????????????????????????? ????????
                                                                         {"Command_start_session",          "/Master/Command_start_session"}, // ?????????????? ???????????????????? ?????????? ?? ??????. ???????????????????????? ???????????? ????????????. ?? ?????????????????? ???????????? ???????????????????????? ?????????????????????????????? ????????
                                                                         {"Command_enable_light_1",          "/Master/Command_enable_light_1"}, // ?????????????? ???????????????????? ?????????? ?? ??????. ???????????????????????? ???????????? ????????????. ?? ?????????????????? ???????????? ???????????????????????? ?????????????????????????????? ????????
                                                                         {"Command_enable_light_2",          "/Master/Command_enable_light_2"}, // ?????????????? ???????????????????? ?????????? ?? ??????. ???????????????????????? ???????????? ????????????. ?? ?????????????????? ???????????? ???????????????????????? ?????????????????????????????? ????????
    };


}

#endif // TOPICS_H
