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
- syscall tampering attack

Upon inspecting the binary, we find that its main functionality involves taking a login and serial as input, performing a `ptrace` check to detect tampering, generating a hash of the login, and comparing it to the provided serial. The task is straightforward:

- bypass the `ptrace` check to enable debugging with gdb
- uncover the hash for a given login so we can use it for authentication

The first subtask is straightforward: we set a breakpoint on the `ptrace` call. For the serial, we can obtain it from the part of the `auth` function where the comparison is made:
``` shell
   0x08048866 <+286>:	cmp    -0x10(%ebp),%eax
```

We run the binary with `gdb` and set two breakpoints:
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

When the first breakpoint is hit, we modify the return value of the `eax` register:
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

When the second breakpoint is hit, we check that the `eax` register contains the entered serial and `ebp-0x10` holds the generated hash value that is compared to it:
``` shell
Breakpoint 2, 0x08048866 in auth ()
(gdb) p $eax
$2 = 4242
(gdb) p $ebp-0x10
$3 = (void *) 0xffffd5a8
(gdb) x/d 0xffffd5a8
0xffffd5a8:	6233782
```

This reveals the correct login/serial combination needed for authentication.

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
