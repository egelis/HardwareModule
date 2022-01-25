#ifndef MODBUS_LS_H
#define MODBUS_LS_H

#include  "modbus.hpp"

#define	regCommand              0x100
#define	regStatus               0x300
#define	regVoltageCPU           0x700
#define	regTemperatureCPU       0x720
#define	regTimeWork            0x780
#define	regVersionHard          0x800
#define	regVersionSoft         0x802


#define	regMemorySetAdr         0xA00
#define	regMemorySetCRC         0xA02
#define	regMemorySetLen         0xA04
#define	regMemoryBuffer         0xA10
#define	regMemoryProgramm       0xA40


class    modbus_ls: public modbus
{
public:

    int     status;
    int     versionHard;
    int     versionSoft;
    float   voltage;
    float   temperature;
    int     timeWork;


    int getVersionHard(void);
    int getVersionSoft(void);
    int getStatus(void);
    float getVoltageCPU(void);
    float getTemperatureCPU(void);
    int  getTimeWork(void);
    void programm(unsigned char *data,int len);

    void printVersion(void);
    void printStatus(void);
    void printTimeWork(void);
    void printTemperatureCPU(void);
    void printVoltageCPU(void);


private:
};


#endif  //MODBUS_LS_H




