BUILD

mkdir build
cd build
../configure --target-list="arm-softmmu arm-linux-user"
make

