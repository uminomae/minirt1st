#!/bin/bash

#=======================================================
#定数 color
#=======================================================
ESC=$(printf '\033') 
# RED=$(printf '[31m')
GREEN=$(printf '[32m')
YELLOW=$(printf '[33m')
BLUE=$(printf '[34m')
PURPLE=$(printf '[35m')
SKYBLUE=$(printf '[36m')
PINK=$(printf '[38;5;199m')
C1=$(printf '[38;5;197m')
WHITE=$(printf '[38;5;015m')
RED=$(printf '[38;5;196m')
BG_PINK=$(printf '[48;5;198m')
BG_WHITE=$(printf '[48;5;15m')

#=======================================================
# head
#=======================================================
echo "${ESC}${BG_PINK}"
echo ""
echo ""
echo ""
echo ""
echo "${ESC}[m"
echo "${ESC}${PINK}"
echo "======================================================="
echo "start miniRT test"
echo "======================================================="
echo "${ESC}[m"


#=======================================================
i=1
max_i=4
timeout=5
#=======================================================

test_expect(){
    expect -c "
        set timeout ${timeout}
        spawn ./miniRT test/ok/pl/test${i}.rt
            expect \"test/\"
            send \"exit\n\"
    "
}
while [ $i -lt $max_i ]
do
    test_expect
    ((i++))
done
