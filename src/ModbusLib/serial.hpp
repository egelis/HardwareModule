#ifndef SERIAL_HPP
#define SERIAL_HPP


#define maxpacketserial (256+16)

class serial
{
public:
        serial();
        void    init(const char *portname, int portbaud);
        int 	openport(void);
    	int 	exchange(unsigned char *data, int lenwrite,int lenread, int timeout);
        int 	closeport(void);

private:
        int     port_descriptor;
    	char 	portname[128];
        int 	portbaud;
};


inline long long time_to_ns(struct timespec *ts);
long long get_ns(void);

#endif // SSERIAL_HPP
