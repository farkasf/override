# level00 analysis

## functions
``` asm
All defined functions:

Non-debugging symbols:
0x08048338  _init
0x08048380  printf
0x08048380  printf@plt
0x08048390  puts
0x08048390  puts@plt
0x080483a0  system
0x080483a0  system@plt
0x080483b0  __gmon_start__
0x080483b0  __gmon_start__@plt
0x080483c0  __libc_start_main
0x080483c0  __libc_start_main@plt
0x080483d0  __isoc99_scanf
0x080483d0  __isoc99_scanf@plt
0x080483e0  _start
0x08048410  __do_global_dtors_aux
0x08048470  frame_dummy
0x08048494  main
0x08048520  __libc_csu_init
0x08048590  __libc_csu_fini
0x08048592  __i686.get_pc_thunk.bx
0x080485a0  __do_global_ctors_aux
0x080485cc  _fini
```

## variables
``` asm
All defined variables:

Non-debugging symbols:
0x080485e8  _fp_hw
0x080485ec  _IO_stdin_used
0x08048758  __FRAME_END__
0x08049f14  __CTOR_LIST__
0x08049f14  __init_array_end
0x08049f14  __init_array_start
0x08049f18  __CTOR_END__
0x08049f1c  __DTOR_LIST__
0x08049f20  __DTOR_END__
0x08049f24  __JCR_END__
0x08049f24  __JCR_LIST__
0x08049f28  _DYNAMIC
0x08049ff4  _GLOBAL_OFFSET_TABLE_
0x0804a018  __data_start
0x0804a018  data_start
0x0804a01c  __dso_handle
0x0804a020  completed.6159
0x0804a024  dtor_idx.6161
```

## main() function
``` asm
Dump of assembler code for function main:
   0x08048494 <+0>:	push   %ebp
   0x08048495 <+1>:	mov    %esp,%ebp
   0x08048497 <+3>:	and    $0xfffffff0,%esp
   0x0804849a <+6>:	sub    $0x20,%esp
   0x0804849d <+9>:	movl   $0x80485f0,(%esp)
   0x080484a4 <+16>:	call   0x8048390 <puts@plt>
   0x080484a9 <+21>:	movl   $0x8048614,(%esp)
   0x080484b0 <+28>:	call   0x8048390 <puts@plt>
   0x080484b5 <+33>:	movl   $0x80485f0,(%esp)
   0x080484bc <+40>:	call   0x8048390 <puts@plt>
   0x080484c1 <+45>:	mov    $0x804862c,%eax
   0x080484c6 <+50>:	mov    %eax,(%esp)
   0x080484c9 <+53>:	call   0x8048380 <printf@plt>
   0x080484ce <+58>:	mov    $0x8048636,%eax
   0x080484d3 <+63>:	lea    0x1c(%esp),%edx
   0x080484d7 <+67>:	mov    %edx,0x4(%esp)
   0x080484db <+71>:	mov    %eax,(%esp)
   0x080484de <+74>:	call   0x80483d0 <__isoc99_scanf@plt>
   0x080484e3 <+79>:	mov    0x1c(%esp),%eax
   0x080484e7 <+83>:	cmp    $0x149c,%eax
   0x080484ec <+88>:	jne    0x804850d <main+121>
   0x080484ee <+90>:	movl   $0x8048639,(%esp)
   0x080484f5 <+97>:	call   0x8048390 <puts@plt>
   0x080484fa <+102>:	movl   $0x8048649,(%esp)
   0x08048501 <+109>:	call   0x80483a0 <system@plt>
   0x08048506 <+114>:	mov    $0x0,%eax
   0x0804850b <+119>:	jmp    0x804851e <main+138>
   0x0804850d <+121>:	movl   $0x8048651,(%esp)
   0x08048514 <+128>:	call   0x8048390 <puts@plt>
   0x08048519 <+133>:	mov    $0x1,%eax
   0x0804851e <+138>:	leave  
   0x0804851f <+139>:	ret    
End of assembler dump.
```
