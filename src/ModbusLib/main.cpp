#include <iostream>

#include "serial.hpp"
#include "modbus_ls_dust.hpp"
#include <time.h>
#include <unistd.h>
#include <string>
using namespace std;


serial serial0;
serial serial1;
serial serial2;


modbus_ls_dust_motor motor1;
modbus_ls_dust_motor motor2;

modbus_ls_dust_control control1;
modbus_ls_dust_control control2;

modbus_ls_dust_experimental experimental1;
modbus_ls_dust_experimental experimental2;

float fTestNull=0.1;
int  iTestNull=0;


int  test_llk()
{

    serial0.init("/dev/ttyUSB0",57600);

    motor1.init(&serial0,8,"motor");

    serial0.openport();

  motor1.WriteRegisterInt(0x1000,10);

    for(;;)
    {
        motor1.WriteRegisterInt(0x1008,32000);
        if(motor1.ok)  cout<<"write ok"<<endl;
                  else cout<<"write error"<<endl;
        sleep(1);

        motor1.WriteRegisterInt(0x1008,0);
        if(motor1.ok)  cout<<"write ok"<<endl;
                  else cout<<"write error"<<endl;
        sleep(1);

    }


};



void test_motor_print(int time)
{

    for(int i=0;i<time;i++)
        {
          float pos,velo,fVampl;
          int endpos;

          pos=motor1.getPosition();
          velo=motor1.getVelocity();
          fVampl=motor1.getAmplitudeVoltage();
          endpos=motor1.getPositionEndStatus();
          if(motor1.ok) cout<<"motor1 pos="<<pos<<" velo="<<velo<<" ampl="<<fVampl<<" end="<<endpos<<endl;
                   else cout<<"motor1 not answer"<<endl;

          pos=motor2.getPosition();
          velo=motor2.getVelocity();
          fVampl=motor2.getAmplitudeVoltage();
          endpos=motor2.getPositionEndStatus();
          if(motor2.ok) cout<<"motor2 pos="<<pos<<" velo="<<velo<<" ampl="<<fVampl<<" end="<<endpos<<endl;
                   else cout<<"motor2 not answer"<<endl;


        sleep(1);
        }
};


int  test_motor(void)
{

    serial0.init("/dev/ttyUSB0",115200);

     motor1.init(&serial0,1,"motor");
     motor2.init(&serial0,2,"motor");

    serial0.openport();

    cout<<"Write=0x300,0x12345678" <<endl;
  // motor1.WriteRegisterInt(0x300,0x12345678);
 //   motor1.WriteRegisterFloat(0x300,123.456);

   // cout<<"read 0x300="<<motor1.ReadRegisterFloat(0x300)<<endl;

    float timeout=30.0;

    motor1.start(15,2000);
    motor2.start(15,2000);
    test_motor_print(1500);

    test_motor_print(15);

//    motor1.start(15,2000);
 //   motor2.start(15,2000);
  //  test_motor_print(15);



    serial0.closeport();




};



int main()
{

  //test_motor();

  //return(0);

    serial0.init("/dev/ttyUSB0",115200);
   // serial1.init("/dev/ttyUSB1",115200);
  //  serial2.init("/dev/ttyUSB2",115200);

    motor1.init(&serial0,1,"motor");
    motor2.init(&serial0,2,"motor");

    control1.init(&serial0,3,"cntrl");
    control2.init(&serial0,4,"cntrl");

    experimental1.init(&serial0,5,"exper");
    experimental2.init(&serial0,6,"exper");


    serial0.openport();


    motor1.printVersion();
    motor2.printVersion();
    control1.printVersion();
    control2.printVersion();
    experimental1.printVersion();
    experimental2.printVersion();

    if(motor1.error) return(1);
    if(motor2.error) return(1);
    if(control1.error) return(1);
    if(control2.error) return(1);
    if(experimental1.error) return(1);
    if(experimental2.error) return(1);


    motor1.printStatus();
    motor2.printStatus();
    control1.printStatus();
    control2.printStatus();
    experimental1.printStatus();
    experimental2.printStatus();


    motor1.printTimeWork();
    motor2.printTimeWork();
    control1.printTimeWork();
    control2.printTimeWork();
    experimental1.printTimeWork();
    experimental2.printTimeWork();

    motor1.printTemperatureCPU();
    motor2.printTemperatureCPU();
    control1.printTemperatureCPU();
    control2.printTemperatureCPU();
    experimental1.printTemperatureCPU();
    experimental2.printTemperatureCPU();


    motor1.printVoltageCPU();
    motor2.printVoltageCPU();
    control1.printVoltageCPU();
    control2.printVoltageCPU();
    experimental1.printVoltageCPU();
    experimental2.printVoltageCPU();


    cout<<"control1 Temperature="<<control1.getTemperature()<<endl;
    cout<<"control1 Pressure="<<control1.getPressure()<<endl;
    cout<<"experimental1 Temperature="<<experimental1.getTemperature()<<endl;
    cout<<"experimental2 Pressure="<<experimental2.getPressure()<<endl;


    cout<<"Disclousure"<<endl;
    experimental1.Disclousure(4.0);
    experimental2.Disclousure(4.0);

    cout<<"experimental1 Disclousure status="<<experimental1.getDisclousureStatus()<<endl;
    cout<<"experimental2 Disclousure status="<<experimental2.getDisclousureStatus()<<endl;


    cout<<"motor start"<<endl;
    motor1.start(21.0,120.0);
    motor2.start(21.0,120.0);

    cout<<"motor1.getPosition="<<motor1.getPosition()<<endl;
    cout<<"motor2.getPosition="<<motor2.getPosition()<<endl;
    cout<<"motor1.getVelocity="<<motor1.getVelocity()<<endl;
    cout<<"motor2.getVelocity="<<motor2.getVelocity()<<endl;
    cout<<"motor1.getTimeout="<<motor1.getTimeout()<<endl;
    cout<<"motor2.getTimeout="<<motor1.getTimeout()<<endl;
    cout<<"motor1.getPositionEndStatus="<<motor1.getPositionEndStatus()<<endl;
    cout<<"motor2.getPositionEndStatus="<<motor1.getPositionEndStatus()<<endl;


    cout<<"vibro start"<<endl;

    control1.VibroBank(120.0, 5.0,1,1);
    control2.VibroBank(120.0, 5.0,1,1);
    sleep(1);

    cout<<"open bank"<<endl;

    control1.OpenBank(2.0, 0.3,1);
    control2.OpenBank(2.0, 0.3,1);

    cout<<"control1 vibro overburning current="<<control1.getOpenOverburningCurrent()<<endl;
    cout<<"control2 vibro overburning current="<<control2.getOpenOverburningCurrent()<<endl;

    experimental1.LightOne(120.0);
    experimental1.LightTwo(120.0);
    experimental2.LightOne(120.0);
    experimental2.LightTwo(120.0);

    experimental1.SyncroCameras(120.0,30.0,0.5,0.5);
    experimental2.SyncroCameras(120.0,30.0,0.5,0.5);

    cout<<"control1 knife 1 current="<<control1.getKnifeCurrentOne()<<endl;
    cout<<"control1 knife 2 current="<<control1.getKnifeCurrentTwo()<<endl;
    cout<<"control2 knife 1 current="<<control2.getKnifeCurrentOne()<<endl;
    cout<<"control2 knife 2 current="<<control2.getKnifeCurrentTwo()<<endl;

    cout<<"experimental1 light 1 current="<<experimental1.getLightCurrentOne()<<endl;
    cout<<"experimental1 light 2 current="<<experimental1.getLightCurrentTwo()<<endl;
    cout<<"experimental2 light 1 current="<<experimental2.getLightCurrentOne()<<endl;
    cout<<"experimental2 light 2 current="<<experimental2.getLightCurrentTwo()<<endl;

    serial0.closeport();

    return 0;
}

