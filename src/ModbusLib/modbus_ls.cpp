#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "modbus_reg.h"
#include "modbus_ls.hpp"




int modbus_ls::getVersionHard(void)
{
return(ReadRegisterInt(regVersionHard));
};

int modbus_ls::getVersionSoft(void)
{
return(ReadRegisterInt(regVersionSoft));
};



int modbus_ls::getStatus(void)
{
return(ReadRegisterInt(regStatus));
};



float modbus_ls::getVoltageCPU(void)
{
return(ReadRegisterFloat(regVoltageCPU));
};


float modbus_ls::getTemperatureCPU(void)
{
return(ReadRegisterFloat(regTemperatureCPU));
};


int modbus_ls::getTimeWork(void)
{
return(ReadRegisterInt(regTimeWork));
};



void modbus_ls::programm(unsigned char *data,int len)
{
};



void modbus_ls::printVersion(void)
{
    int versionHard=getVersionHard();
    int versionSoft=getVersionSoft();
    cout<<name<<" ["<<adress<<"] version=";
    if(ok)  cout<<std::hex<<"HW:"<<versionHard<<" SW:"<<versionSoft<<std::dec<<endl;
              else cout<<"not answer"<<endl;

};


void modbus_ls::printStatus(void)
{
    int temp=getStatus();
    cout<<name<<" ["<<adress<<"] status=";
    if(ok)  cout<<std::hex<<temp<<std::dec<<endl;
              else cout<<"not answer"<<endl;

};


void modbus_ls::printTimeWork(void)
{
    int temp=getTimeWork();
    cout<<name<<" ["<<adress<<"] timework=";
    if(ok)  cout<<temp<<endl;
       else cout<<"not answer"<<endl;

};

void modbus_ls::printTemperatureCPU(void)
{
    float temp=getTemperatureCPU();
    cout<<name<<" ["<<adress<<"] temperature=";
    if(ok)  cout<<temp<<endl;
              else cout<<"not answer"<<endl;

};

void modbus_ls::printVoltageCPU(void)
{
    float temp=getVoltageCPU();
    cout<<name<<" ["<<adress<<"] voltage=";
    if(ok)  cout<<temp<<endl;
       else cout<<"not answer"<<endl;

};




