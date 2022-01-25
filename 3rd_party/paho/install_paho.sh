echo 'Start install Paho mqtt library'


compiler_c='/usr/bin/cc'
compiler_cpp='/usr/bin/c++'
make_path='/usr/bin/make'


paho_unzip_dir=build_paho
paho_c_dir=paho.mqtt.c-master
paho_cpp_dir=paho.mqtt.cpp-master




echo '1. Unzip source code'

mkdir -p $paho_unzip_dir && cd $_

if [ -d "$paho_c_dir" ]; then
	echo "Paho C lib is already unzipped. Skip."
else
    unzip ../$paho_c_dir.zip
    echo "Success unzip Paho C lib"
fi

if [ -d "$paho_cpp_dir" ]; then
	echo "Paho C++ lib is already unzipped. Skip."
else
    unzip ../$paho_cpp_dir.zip
    echo "Success unzip Paho C++ lib"
fi






echo '2. Build C lib'
build_paho_c_dir=build_paho_c
need_to_build=true

if [ -d "$build_paho_c_dir" ]; then
	echo "Paho C lib build dir is already exist. Do you want clean & rebuild? [y]es/[n]o: "; read rebuild
    
    if [ $rebuild = "y" ]; then
        need_to_build=true
        rm -r $build_paho_c_dir
        
    else
        need_to_build=false
    fi
fi

if $need_to_build; then
    
    mkdir -p $build_paho_c_dir
    cd $build_paho_c_dir

    cmake -G"Unix Makefiles" \
          -DPAHO_WITH_SSL=FALSE \
          -DPAHO_BUILD_SAMPLES=FALSE \
          -DCMAKE_C_COMPILER=$compiler_c \
          -DCMAKE_MAKE_PROGRAM=$make_path \
          -DCMAKE_INSTALL_PREFIX=./ \
          -DCMAKE_INSTALL_LIBDIR=../../lib \
          -DCMAKE_INSTALL_INCLUDEDIR=../../include \
          -DPAHO_BUILD_STATIC=TRUE \
          -DPAHO_BUILD_SHARED=FALSE \
          ../$paho_c_dir
    

    make
    make install
    echo "Finish install Paho C lib"
    cd ../
fi




echo '3. Build C++ lib'
build_paho_cpp_dir=build_paho_cpp
need_to_build=true

if [ -d "$build_paho_cpp_dir" ]; then
	echo "Paho C++ lib build dir is already exist. Do you want clean & rebuild? [y]es/[n]o: "; read rebuild
    
    if [ $rebuild = "y" ]; then
        need_to_build=true
        rm -r $build_paho_cpp_dir
    else
        need_to_build=false
    fi
fi

if $need_to_build; then
    mkdir -p $build_paho_cpp_dir
    cd $build_paho_cpp_dir

    cmake -G"Unix Makefiles" \
          -DPAHO_WITH_SSL=FALSE \
          -DPAHO_BUILD_SAMPLES=FALSE \
          -DPAHO_MQTT_C_LIBRARIES=../../lib \
          -DPAHO_MQTT_C_INCLUDE_DIRS=../../include \
          -DCMAKE_CXX_COMPILER=$compiler_cpp \
          -DCMAKE_MAKE_PROGRAM=$make_path \
          -DCMAKE_INSTALL_PREFIX=../../ \
          -DCMAKE_INSTALL_LIBDIR=lib \
          -DCMAKE_INSTALL_INCLUDEDIR=include \
          -DPAHO_BUILD_STATIC=TRUE \
          -DPAHO_BUILD_SHARED=FALSE \
          ../$paho_cpp_dir
    
    
    make
    make install
    cd ../
    echo "Finish install Paho C++ lib"
fi

