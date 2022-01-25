#ifndef MODBUS_LS_DUST_H
#define MODBUS_LS_DUST_H

#include  "modbus_ls.hpp"


class    modbus_ls_dust_motor: public modbus_ls
{
public:
    void    start(float time,float target);
    void    stop(void);
    float   getPosition(void);
    float   getVelocity(void);
    float   getTimeout(void);
    int     getPositionEndStatus(void);
    float   getAmplitudeVoltage(void);
    float   getAmplitudeCurrent(void);
};

class    modbus_ls_dust: public modbus_ls
{
public:
    float   getTemperature(void);
    float   getPressure(void);
};

class    modbus_ls_dust_control: public modbus_ls_dust
{
public:
    void    VibroBank(float time, float amplitude,int bankmask,int freq);
    void    OpenBank(float time, float current,int banknum);
    float   getOpenOverburningCurrent(void);

    float   getKnifeCurrentOne(void);
    float   getKnifeCurrentTwo(void);
};


class    modbus_ls_dust_experimental: public modbus_ls_dust
{
public:
    void    Disclousure(float time);
    int     getDisclousureStatus(void);

    void    SyncroCameras(float time,float freq, float duty_cameras,float duty_knife);

    void    LightOne(float time);
    void    LightTwo(float time);
    float   getLightCurrentOne(void);
    float   getLightCurrentTwo(void);
};


#endif // MODBUS_LS_DUST_H











