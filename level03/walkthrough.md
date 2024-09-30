# level03 walkthrough

## the binary
``` shell
level03@OverRide:~$ ./level03 
***********************************
*		level03		**
***********************************
Password:admin

Invalid Password
```

## methodology
- brute-force attack

After a closer examination, we can outline the basic flow of the binary's lifecycle:
``` vbnet
F_MAIN:
  stdin: input 
    --> call: test(input, 322424845)

F_TEST:
  calculate: key = 322424845 - input
    |--> key > 21?
          --> call: decrypt(rand())
    |--> key <= 21?
          --> call: decrypt(key)

F_DECRYPT:
  for every 'character' in "Q}|u`sfg~sf{}|a3" do:
    character XOR key 
      --> is the result "Congratulations!"? 
            |--> yes: spawn shell
            |--> no: invalid password
```

We identified the decryption buffer using the following steps:
``` shell
(gdb) b *decrypt+51
Breakpoint 1 at 0x8048693
(gdb) r
Starting program: /home/users/level03/level03 
***********************************
*		level03		**
***********************************
Password:42

Breakpoint 1, 0x08048693 in decrypt ()
(gdb) i reg ebp
ebp            0xffffd5b8	0xffffd5b8
(gdb) set $array = $ebp - 0x1d
(gdb) x/s $array
0xffffd59b:	 "Q}|u`sfg~sf{}|a3"
```

The exploitation is straightforward: we simply test inputs that meet the following conditions:
``` vbnet
--> 0 <= 322424845 - input && 322424845 - input <= 21 --> 322424824 <= input <= 322424845
    |--> No negative numbers!
    |--> input ∈ <322424824, 322424845>
```

We use an automated shell script to brute-force the correct input by testing the mentioned array of numbers.

## flag
``` shell
level03@OverRide:~$ bash /tmp/exploit3
Testing 322424824 as input:
***********************************
*		level03		**
***********************************
Password:
Invalid Password

Testing 322424825 as input:
***********************************
*		level03		**
***********************************
Password:
Invalid Password

Testing 322424826 as input:
***********************************
*		level03		**
***********************************
Password:
Invalid Password

Testing 322424827 as input:
***********************************
*		level03		**
***********************************
whoami
level04
cat /home/users/level04/.pass
kgv3tkEb9h2mLkRsPkXRfc2mHbjMxQzvb2FrgKkf
```
