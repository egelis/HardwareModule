#ifndef MODBUS_H
#define MODBUS_H

#include "serial.hpp"
#include <string>
using namespace std;

class modbus
{
public:
        modbus();
        void init(class serial *iserial, int iadress,string iname);
        void reset(void);

        void  WriteRegister      (unsigned short reg,short data);
        void  WriteRegisterInt   (unsigned short reg,int   data);
        void  WriteRegisterFloat (unsigned short reg,float data);

        short ReadRegister      (unsigned short reg);
        int   ReadRegisterInt   (unsigned short reg);
        float ReadRegisterFloat (unsigned short reg);

        void  WriteRegisters (unsigned short reg, void *data, unsigned short num);
        void  ReadRegisters  (unsigned short reg, void *data, unsigned short num);

        bool error;
        bool ok;
        string name;
        int adress;

private:
//        void rtu2ascii(void);
  //      void ascii2rtu(void);


        serial *port;

};


#endif // MODBUS_H




