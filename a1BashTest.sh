#!/bin/bash
echo TEST 1:
cat in01.txt | ./kwic1 >  output.txt
MYVAR=$(diff out01.txt output.txt)
chrlen=${#MYVAR}
echo $chrlen

echo TEST 2:
cat in02.txt | ./kwic1 >  output.txt
#diff out02.txt output.txt
MYVAR=$(diff out02.txt output.txt)
chrlen=${#MYVAR}
echo $chrlen

echo TEST 3:
cat in03.txt | ./kwic1 >  output.txt
#diff out03.txt output.txt
MYVAR=$(diff out03.txt output.txt)
chrlen=${#MYVAR}
echo $chrlen

echo TEST 4:
cat in04.txt | ./kwic1 >  output.txt
#diff out04.txt output.txt
MYVAR=$(diff out04.txt output.txt)
chrlen=${#MYVAR}
echo $chrlen


echo TEST 5:
cat in05.txt | ./kwic1 >  output.txt
#diff out05.txt output.txt
MYVAR=$(diff out05.txt output.txt)
chrlen=${#MYVAR}
echo $chrlen



echo TEST 6:
cat in06.txt | ./kwic1 >  output.txt
#diff out06.txt output.txt
MYVAR=$(diff out06.txt output.txt)
chrlen=${#MYVAR}
echo $chrlen



echo TEST 7:
cat in07.txt | ./kwic1 >  output.txt
#diff out07.txt output.txt
MYVAR=$(diff out07.txt output.txt)
chrlen=${#MYVAR}
echo $chrlen



echo TEST 8:
cat in08.txt | ./kwic1 >  output.txt
#diff out08.txt output.txt
MYVAR=$(diff out08.txt output.txt)
chrlen=${#MYVAR}
echo $chrlen



echo TEST 9:
cat in09.txt | ./kwic1 >  output.txt
#diff out09.txt output.txt
MYVAR=$(diff out09.txt output.txt)
chrlen=${#MYVAR}
echo $chrlen



echo TEST 10:
cat in10.txt | ./kwic1 >  output.txt
#diff out10.txt output.txt
MYVAR=$(diff out10.txt output.txt)
chrlen=${#MYVAR}
echo $chrlen

