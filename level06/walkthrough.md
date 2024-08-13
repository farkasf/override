# level06 walkthrough

## the binary
``` shell
level06@OverRide:~$ ./level06
***********************************
*		level06		  *
***********************************
-> Enter Login: filipos
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 4242
```

## methodology
- syscall tampering

Upon inspecting the binary, we realize that its main purpose is to take a given login and serial as input, perform a <code>ptrace</code> check to see if any tampering happened, generate a hash of the login and check if it matches the serial. The task seems pretty straightforward:

- find a way around the <code>ptrace</code> check to be able to debug with gdb
- uncover the hash for a given login, so we can use it for authentification

The first subtask is pretty straighforward, as we break directly on the <code>ptrace</code> call. As for the serial, we can access it from the part of the <code>auth</code> function where the comparison happens:

``` shell
   0x08048866 <+286>:	cmp    -0x10(%ebp),%eax
```

We run gdb with the 2 breaks:
``` shell
level06@OverRide:~$ gdb ./level06 
Reading symbols from /home/users/level06/level06...(no debugging symbols found)...done.
(gdb) b ptrace
Breakpoint 1 at 0x80485f0
(gdb) b *auth+286
Breakpoint 2 at 0x8048866
(gdb) r
Starting program: /home/users/level06/level06 
***********************************
*		level06		  *
***********************************
-> Enter Login: filipos
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 4242
```

On the first break, we change the return value of the <code>eax</code> register:
``` shell
Breakpoint 1, 0xf7f14990 in ptrace () from /lib32/libc.so.6
(gdb) step
Single stepping until exit from function ptrace,
which has no line number information.
0x080487ba in auth ()
(gdb) p $eax
$1 = -1
(gdb) s $eax = 0
(gdb) step
Single stepping until exit from function auth,
which has no line number information.
```

On the second break, we can see that the <code>eax</code> register contains the entered serial and <code>ebp-0x10</code> holds the value of the generated value that is compared to it:
``` shell
Breakpoint 2, 0x08048866 in auth ()
(gdb) p $eax
$2 = 4242
(gdb) p $ebp-0x10
$3 = (void *) 0xffffd5a8
(gdb) x/d 0xffffd5a8
0xffffd5a8:	6233782
```

This gives us the correct login/serial combination enabling us to log in.

## flag
``` shell
level06@OverRide:~$ ./level06 
***********************************
*		level06		  *
***********************************
-> Enter Login: filipos
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 6233782
Authenticated!
$ whoami
level07
$ cat /home/users/level07/.pass
GbcPDRgsFK77LNnnuh7QyFYA2942Gp8yKj9KrWD8
```
