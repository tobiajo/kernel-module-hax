#!/bin/sh
make > /dev/null 2>&1

echo '> sudo insmod rootkit.ko'
sudo insmod rootkit.ko
echo '> dmesg | tail -1'
dmesg | tail -1

echo '> whoami'
whoami
echo '> kill 5'
kill 5
echo '> dmesg | tail -1'
dmesg | tail -1
echo '> whoami'
whoami

echo '> sudo rmmod rootkit'
sudo rmmod rootkit
echo '> dmesg | tail -1'
dmesg | tail -1

make clean > /dev/null 2>&1
