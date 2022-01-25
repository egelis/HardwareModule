#ifndef MODBUS_REG_H
#define MODBUS_REG_H

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

#define regMotorCommand                         0x100
#define regMotorStatus                          0x300
#define regMotorPosition                        0x302
#define regMotorVelocity                        0x304
#define regMotorPositionTarget                  0x306
#define regMotorTimeOut                         0x308
#define regMotoEndPositionStatus                0x30A
#define regMotorAmplitudeVoltage                0x30C
#define regMotorAmplitudeCurrent                0x30E

#define regDustTemperatury                      0x310
#define regDustPressure                         0x312

#define regControlVibroEnableTime               0x320
#define regControlVibroBanksMask                0x322
#define regControlVibroAmplitude                0x324
#define regControlVibroFreqMode                 0x326

#define regControlOpenOverburningCurrentSet     0x330
#define regControlOpenOverburningCurrent        0x332
#define regControlOpenBanksNum                  0x334
#define regControlOpenBanksEnableTime           0x336

#define regControlKnifeCurrentOne               0x340
#define regControlKnifeCurrentTwo               0x342


#define regExperimentalDisclousureEnableTime         0x350
#define regExperimentalDisclousureStatus             0x352

#define regExperimentalSyncroEnableTime              0x360
#define regExperimentalSyncroFreq                    0x362
#define regExperimentalSyncroCamerasDutyCycle        0x364
#define regExperimentalSyncroKnifeDutyCycle          0x366

#define regExperimentalLightEnableTimeOne            0x370
#define regExperimentalLightEnableTimeTwo            0x372
#define regExperimentalLightCurrentOne               0x374
#define regExperimentalLightCurrentTwo               0x376

#define regMotorTimeOutTest                          0x390
#define regMotorHallStep                             0x392
#define regMotorOutStep                              0x394


#endif // MODBUS_REG_H

