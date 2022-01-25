#include "serial.hpp"
#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <sys/file.h>
#include <errno.h>

using namespace std;

termios m_port_settings;


serial::serial()
{
port_descriptor=-1;
strcpy(portname,"/dev/ttyUSB0");
portbaud=115200;
};

void serial::init(const char *name, int baud)
{
port_descriptor=-1;
strcpy(portname,name);
portbaud=baud;
};

int serial::openport(void)
{

    int baudr;

     switch(portbaud)
     {
       case      50 : baudr = B50;
                      break;
       case      75 : baudr = B75;
                      break;
       case     110 : baudr = B110;
                      break;
       case     134 : baudr = B134;
                      break;
       case     150 : baudr = B150;
                      break;
       case     200 : baudr = B200;
                      break;
       case     300 : baudr = B300;
                      break;
       case     600 : baudr = B600;
                      break;
       case    1200 : baudr = B1200;
                      break;
       case    1800 : baudr = B1800;
                      break;
       case    2400 : baudr = B2400;
                      break;
       case    4800 : baudr = B4800;
                      break;
       case    9600 : baudr = B9600;
                      break;
       case   19200 : baudr = B19200;
                      break;
       case   38400 : baudr = B38400;
                      break;
       case   57600 : baudr = B57600;
                      break;
       case  115200 : baudr = B115200;
                      break;
       case  230400 : baudr = B230400;
                      break;
       case  460800 : baudr = B460800;
                      break;
       case  500000 : baudr = B500000;
                      break;
       case  576000 : baudr = B576000;
                      break;
       case  921600 : baudr = B921600;
                      break;
       case 1000000 : baudr = B1000000;
                      break;
       default      : printf("invalid baudrate\n");
                      return(0);
                      break;
     }

  //   port_descriptor = open(portname, O_RDWR | O_NOCTTY | O_NDELAY | /*(nonblocking ?*/ O_NONBLOCK /*: 0)*/);

     port_descriptor = open(portname, O_RDWR | O_NOCTTY | O_NDELAY );


     if(port_descriptor>0)
	{
        printf("Serial port %s open %d\n",portname,port_descriptor);
     	}
	else  
	{
        printf("Serial port %s not open %d\n",portname,port_descriptor);
       	return (0);
	};



     memset(&m_port_settings, 0, sizeof(m_port_settings));  /* clear the new struct */

     m_port_settings.c_cflag = baudr | CS8 | CLOCAL | CREAD;
     m_port_settings.c_iflag = IGNPAR;
     m_port_settings.c_oflag = 0;
     m_port_settings.c_lflag = 0;
     m_port_settings.c_cc[VMIN] = 0;      /* block untill n bytes are received */
     m_port_settings.c_cc[VTIME] = 0;     /* block untill a timer expires (n * 100 mSec.) */
     int m_error = tcsetattr(port_descriptor, TCSANOW, &m_port_settings);
     if(m_error==-1)
     {
       close(port_descriptor);
       printf("Serial port not open unable to adjust portsettings \n");
       return (0);
     }

     return(1);

};

int serial::closeport(void)
{
    return close(port_descriptor);

};

inline long long time_to_ns(struct timespec *ts)
{
	return (long long)ts->tv_sec * 1000 * 1000 * 1000 + ts->tv_nsec;
}

long long get_ns(void)
{
	struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	return time_to_ns(&ts);
}


int serial::exchange(unsigned char *data, int lenwrite,int lenread, int timeout)
{

long long timestart;

int i;

usleep(6000);
timestart=get_ns();
timeout=6000+87*(lenwrite+lenread);

if(write(port_descriptor, data,lenwrite)==lenwrite)
	{
   usleep(timeout);
	
	int  len,lread=0,lmax=256; 
	int c0=0,c1=0;

    timeout=10;

    	do  {
	    len=read(port_descriptor,data+lread,lmax);
	    if(len>0)  
		  {
		  lread+=len;
		  lmax-=len;
		  c1++;
		  } else c0++;
        usleep(100);
        }  while ((lread<lenread)&&(timeout-->0));


	timestart=get_ns()-timestart;
  //  printf("time=%3.1f  %d  %d   >>",((float)timestart)/1000000.0,c1,c0);

    if(lread==lenread)
             return(1);
    }

return(0);
};




