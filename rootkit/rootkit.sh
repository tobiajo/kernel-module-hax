make > /dev/null 2>&1
sudo insmod rootkit.ko

echo '> whoami'
whoami
echo '> kill 5'
kill 5
echo '> whoami'
whoami

sudo rmmod rootkit
make clean > /dev/null 2>&1
