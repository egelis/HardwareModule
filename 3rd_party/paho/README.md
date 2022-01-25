# Eclipse Paho C/C++ Client Library for the MQTT Protocol

This code builds **static** libraries that enable applications to
connect to an MQTT broker to publish messages and to subscribe to topics
and receive published messages.

## Installation

To install libraries use script **install_paho.sh**


```bash
./install_paho.sh
```

## Test

After installation, you can check the correct libs with the demo project
in **test_paho** dir.



## Changes

For a correct include directory, the line 46 in the file **paho.mqtt.cpp-master/src/mqtt/CMakeLists.txt** was changed:


```c
include/mqtt    ->    ${CMAKE_INSTALL_INCLUDEDIR}/mqtt

```

## Documentation

Reference documentation is
[online](https://www.eclipse.org/paho/files/cppdoc/index.html).
