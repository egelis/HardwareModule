echo 'Start install Paho mqtt library'


compiler_c='/usr/bin/cc'
compiler_cpp='/usr/bin/c++'
make_path='/usr/bin/make'


mosquitto_build_dir=build_mosquitto
mosquitto_unzip_dir=mosquitto-2.0.0




echo '1. Unzip source code'

mkdir -p $mosquitto_build_dir && cd $_

if [ -d "$mosquitto_unzip_dir" ]; then
	echo "Mosquitto is already unzipped. Skip."
else
    tar xf ../$mosquitto_unzip_dir.tar.gz
    echo "Success unzip Mosquitto"
fi



echo '2. Build'
build_mosquitto_dir=build
need_to_build=true

if [ -d "$build_mosquitto_dir" ]; then
	echo "Mosquitto build dir is already exist. Do you want clean & rebuild? [y]es/[n]o: "; read rebuild
    
    if [ $rebuild = "y" ]; then
        need_to_build=true
        rm -r $build_mosquitto_dir
        
    else
        need_to_build=false
    fi
fi

echo need_to_build = $need_to_build

if $need_to_build; then
    
    mkdir -p $build_mosquitto_dir
    cd $build_mosquitto_dir

    cmake -G"Unix Makefiles" \
          -DCMAKE_INSTALL_PREFIX=build \
          -DCMAKE_INSTALL_SBINDIR=../../../../../mosquitto \
          -DWITH_TLS=OFF \
          -DWITH_CLIENTS=OFF \
          -DWITH_APPS=OFF \
          -DWITH_PLUGINS=OFF \
          -DDOCUMENTATION=OFF \
          -DCMAKE_C_COMPILER=$compiler_c \
          -DCMAKE_CXX_COMPILER=$compiler_cpp \
          -DCMAKE_MAKE_PROGRAM=$make_path \
          ../$mosquitto_unzip_dir
    

    make
    make install
    cp -v ../../mosquitto.conf ../../../../mosquitto/mosquitto.conf
    #cp -v ../../accounts.txt ../../../../mosquitto/accounts.txt
    echo "Finish build Mosquitto"
    cd ../../
fi

