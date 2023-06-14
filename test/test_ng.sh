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
# ファイル名を指定
#=======================================================


test_rt() {
	printf "$1 \"$2\""
    printf "\n"
	./miniRT $2
}

echo "${ESC}${BG_PINK}"
printf "./miniRT test/ng/"
echo "${ESC}[m"
test_rt generally1 test/ng/generally/test1.rt
test_rt generally2 test/ng/generally/test2.rt
test_rt generally3 test/ng/generally/test3.rt
test_rt generally4 test/ng/generally/test4.rt
test_rt generally5 test/ng/generally/test5.rt
test_rt generally6 test/ng/generally/test6.rt
test_rt generally7 test/ng/generally/test7.rt
echo "${ESC}${BG_PINK}"
printf "./miniRT test/id_dup/"
echo "${ESC}[m"
test_rt id_dup1 test/ng/id_dup/test1.rt
test_rt id_dup2 test/ng/id_dup/test2.rt
test_rt id_dup3 test/ng/id_dup/test3.rt
echo "${ESC}${BG_PINK}"
printf "./miniRT test/missing/"
echo "${ESC}[m"
test_rt missing1 test/ng/missing/test1.rt
test_rt missing2 test/ng/missing/test2.rt
test_rt missing3 test/ng/missing/test3.rt
test_rt missing4 test/ng/missing/test4.rt
test_rt missing5 test/ng/missing/test5.rt
echo "${ESC}${BG_PINK}"
printf "./miniRT test/out_of_range/"
echo "${ESC}[m"
test_rt out_of_range1 test/ng/out_of_range/test1.rt
test_rt out_of_range2 test/ng/out_of_range/test2.rt
test_rt out_of_range3 test/ng/out_of_range/test3.rt
test_rt out_of_range4 test/ng/out_of_range/test4.rt
test_rt out_of_range5 test/ng/out_of_range/test5.rt
test_rt out_of_range6 test/ng/out_of_range/test6.rt
test_rt out_of_range7 test/ng/out_of_range/test7.rt
test_rt out_of_range8 test/ng/out_of_range/test8.rt
test_rt out_of_range9 test/ng/out_of_range/test9.rt
test_rt out_of_range10 test/ng/out_of_range/test10.rt
echo "${ESC}${BG_PINK}"
printf "./miniRT test/ :case of NG filename"
echo "${ESC}[m"
test_rt filename1 test/ng/.rt/rt_file.rts
test_rt filename2 test/ng/.rt/rt_file.rd
test_rt filename3 test/.rd
test_rt filename4 test/filenamert
test_rt filename5 test/filename.rt
test_rt filename6 </dev/null
test_rt filename7 test/ng/.rt
test_rt filename8 test/permission.rt

