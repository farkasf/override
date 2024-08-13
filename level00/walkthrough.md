# level00 walkthrough

## the binary
``` shell
level00@OverRide:~$ ./level00 
***********************************
* 	     -Level00 -		  *
***********************************
Password:
```

## methodology
- no common exploit

Similarly to the previous project, the entered password is directly compared to a number, and a shell is spawned if the two match.
``` shell
0x080484e7 <+83>:	cmp    $0x149c,%eax

(gdb) p 0x149c
$1 = 5276
```

## flag
``` shell
level00@OverRide:~$ ./level00 
***********************************
* 	     -Level00 -		  *
***********************************
Password:5276

Authenticated!
$ whoami
level01
$ cat /home/users/level01/.pass
uSq2ehEGT6c9S24zbshexZQBXUGrncxn5sD5QfGL
```
