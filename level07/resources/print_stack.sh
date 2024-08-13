#!/bin/bash

for i in $(seq 100 125); do
    value=$(./level07 <<EOF
read
$i
quit
EOF
)
    echo -n "tab[$i]: "
    num=$(echo "$value" | grep "Number at " | awk '{print $8}')
    printf '0x%x\n' "$num"
done
