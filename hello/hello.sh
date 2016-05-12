make > /dev/null 2>&1

echo '> sudo insmod hello.ko'
sudo insmod hello.ko
echo '> dmesg | tail -1'
dmesg | tail -1
echo '> sudo rmmod hello'
sudo rmmod hello
echo '> dmesg | tail -1'
dmesg | tail -1

make clean > /dev/null 2>&1
