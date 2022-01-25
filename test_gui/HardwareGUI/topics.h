#ifndef TOPICS_H
#define TOPICS_H

#include <QString>
#include <QMap>

namespace Topics {
    const QMap <QString, QString> global_topics{{"motor",      "/motor/#"},
                                                {"control",    "/control/#"},
                                                {"experiment", "/experiment/#"}};

    const QMap <QString, QString> motor_topics{{"start",      "/motor/start"},
                                               {"stop",       "/motor/stop"},
                                               {"position",   "/motor/position"},
                                               {"velocity",   "/motor/velocity"},
                                               {"timeout",    "/motor/timeout"},
                                               {"end_status", "/motor/end_status"}};

    const QMap <QString, QString> control_topics{{"vibrobank",           "/control/vibrobank"},
                                                 {"openbank",            "/control/openbank"},
                                                 {"overburning_current", "/control/overburning_current"},
                                                 {"knife_current1",      "/control/knife_current1"},
                                                 {"knife_current2",      "/control/knife_current2"},
                                                 {"temperature",         "/control/temperature"},
                                                 {"pressure",            "/control/pressure"}};

    const QMap <QString, QString> experimental_topics{{"disclosure",              "/experiment/disclosure"},
                                                      {"disclosure_status",       "/experiment/disclosure_status"},
                                                      {"knifes_syncrocam_enable", "/experiment/knifes_syncrocam_enable"},
                                                      {"light_enable1",           "/experiment/light_enable1"},
                                                      {"light_enable2",           "/experiment/light_enable2"},
                                                      {"light_current1",          "/experiment/light_current1"},
                                                      {"light_current2",          "/experiment/light_current2"},
                                                      {"temperature",             "/experiment/temperature"},
                                                      {"pressure",                "/experiment/pressure"}};
}

#endif // TOPICS_H
