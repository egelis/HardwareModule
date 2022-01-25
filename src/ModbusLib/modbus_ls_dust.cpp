#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "modbus_reg.h"
#include "modbus_ls_dust.hpp"

#define cmdStart                0x1
#define cmdStop                 0x0





void   modbus_ls_dust_motor::start(float time,float target)
{
WriteRegisterFloat(regMotorPositionTarget,target);
WriteRegisterFloat(regMotorTimeOut,time);
};


void   modbus_ls_dust_motor::stop(void)
{
WriteRegisterFloat(regMotorTimeOut,0.0);
};


float   modbus_ls_dust_motor::getPosition(void)
{
return(ReadRegisterFloat(regMotorPosition));
};

float   modbus_ls_dust_motor::getVelocity(void)
{
return(ReadRegisterFloat(regMotorVelocity));
};


int modbus_ls_dust_motor::getPositionEndStatus(void)
{
return(ReadRegisterInt(regMotoEndPositionStatus));
};


float   modbus_ls_dust_motor::getAmplitudeVoltage(void)
{
return(ReadRegisterFloat(regMotorAmplitudeVoltage));
};


float   modbus_ls_dust_motor::getAmplitudeCurrent(void)
{
return(ReadRegisterFloat(regMotorAmplitudeCurrent));
};


float   modbus_ls_dust_motor::getTimeout(void)
{
return(ReadRegisterFloat(regMotorTimeOut));
};


float modbus_ls_dust::getTemperature(void)
{
return(ReadRegisterFloat(regDustTemperatury));
};

float modbus_ls_dust::getPressure(void)
{
return(ReadRegisterFloat(regDustPressure));
};




void modbus_ls_dust_control::VibroBank(float time, float amplitude,int bankmask,int freq)
{
WriteRegisterInt(regControlVibroBanksMask,bankmask);
WriteRegisterFloat(regControlVibroAmplitude,amplitude);
WriteRegisterInt(regControlVibroFreqMode,freq);
WriteRegisterFloat(regControlVibroEnableTime,time);
};


void modbus_ls_dust_control::OpenBank(float time, float current,int banknum)
{
WriteRegister(regControlOpenBanksNum,banknum);
WriteRegisterFloat(regControlOpenOverburningCurrentSet,current);
WriteRegisterFloat(regControlOpenBanksEnableTime,time);
};

float modbus_ls_dust_control::getOpenOverburningCurrent(void)
{
return(ReadRegisterFloat(regControlOpenOverburningCurrent));
};

float modbus_ls_dust_control::getKnifeCurrentOne(void)
{
return(ReadRegisterFloat(regControlKnifeCurrentOne));
};

float modbus_ls_dust_control::getKnifeCurrentTwo(void)
{
return(ReadRegisterFloat(regControlKnifeCurrentTwo));
};



void modbus_ls_dust_experimental::Disclousure(float time)
{
WriteRegisterFloat(regExperimentalDisclousureEnableTime,time);
};

int modbus_ls_dust_experimental::getDisclousureStatus(void)
{
return(ReadRegisterInt(regExperimentalDisclousureStatus));
};


void modbus_ls_dust_experimental::SyncroCameras(float time,float freq, float duty_cameras,float duty_knife)
{
WriteRegisterFloat(regExperimentalSyncroFreq,freq);
WriteRegisterFloat(regExperimentalSyncroCamerasDutyCycle,duty_cameras);
WriteRegisterFloat(regExperimentalSyncroKnifeDutyCycle,duty_knife);
WriteRegisterFloat(regExperimentalSyncroEnableTime,time);
};

void modbus_ls_dust_experimental::LightOne(float time)
{
WriteRegisterFloat(regExperimentalLightEnableTimeOne,time);
};


void modbus_ls_dust_experimental::LightTwo(float time)
{
WriteRegisterFloat(regExperimentalLightEnableTimeTwo,time);
};


float modbus_ls_dust_experimental::getLightCurrentOne(void)
{
return(ReadRegisterFloat(regExperimentalLightCurrentOne));
};

float modbus_ls_dust_experimental::getLightCurrentTwo(void)
{
return(ReadRegisterFloat(regExperimentalLightCurrentTwo));
};
