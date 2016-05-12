# kernel-module-hax
Play with Linux kernel modules, for educational purposes

## hello
Example output:
```
$ ./hello.sh
> sudo insmod hello.ko
> dmesg | tail -1
[  365.689187] Hello from kernel!
> sudo rmmod hello
> dmesg | tail -1
[  365.700431] Goodbye from kernel.
```

## rootkit
Example output:
```
$ ./rootkit.sh
> sudo insmod rootkit.ko
> dmesg | tail -1
[  372.014160] Rootkit installed
> whoami
tobias
> kill 5
./rootkit.sh: line 11: kill: (5) - Operation not permitted
> dmesg | tail -1
[  372.023794] You are now root!
> whoami
root
> sudo rmmod rootkit
> dmesg | tail -1
[  372.100772] Rootkit removed
```
