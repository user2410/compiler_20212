#! /bin/bash
echo -e "\n================Test1===================\n"
./kplc ../tests/example1.kpl | diff ../tests/result1.txt -
echo -e "\n================Test2===================\n"
./kplc ../tests/example2.kpl | diff ../tests/result2.txt -
echo -e "\n================Test3===================\n"
./kplc ../tests/example3.kpl | diff ../tests/result3.txt -
echo -e "\n================Test4===================\n"
./kplc ../tests/example4.kpl | diff ../tests/result4.txt -
echo -e "\n================Test5===================\n"
./kplc ../tests/example5.kpl | diff ../tests/result5.txt -
echo -e "\n================Test6===================\n"
./kplc ../tests/example6.kpl | diff ../tests/result6.txt -
#./kplc ../tests/example7.kpl | diff ../tests/result7.txt -