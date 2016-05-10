make > /dev/null 2>&1
sudo insmod hello.ko
sudo rmmod hello
dmesg | tail
make clean > /dev/null 2>&1
