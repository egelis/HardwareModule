# Eclipse Mosquitto MQTT broker

Mosquitto is an open source implementation of a server for version 5.0, 3.1.1, and 3.1 of the MQTT protocol. 

## Installation

To install libraries use script **install_mosquitto.sh**


```bash
./install_mosquitto.sh
```

## Changes

For a build without TLS, the line 40 in the file **src/CMakeLists.txt** was removed:


```c
set (MOSQ_SRCS 
...
# password_mosq.c password_mosq.h
... )

...

add_executable(mosquitto ${MOSQ_SRCS})

```

## Documentation

Reference documentation is
[here](https://mosquitto.org/documentation/).
