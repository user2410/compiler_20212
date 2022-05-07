#! /bin/bash
echo -e "\n================Test1===================\n"
./parser ../tests/example1.kpl | diff ../tests/result1.txt -
echo -e "\n================Test2===================\n"
./parser ../tests/example2.kpl | diff ../tests/result2.txt -
echo -e "\n================Test3===================\n"
./parser ../tests/example3.kpl | diff ../tests/result3.txt -
echo -e "\n================Test4===================\n"
./parser ../tests/example4.kpl | diff ../tests/result4.txt -
echo -e "\n================Test5===================\n"
./parser ../tests/example5.kpl | diff ../tests/result5.txt -
echo -e "\n================Test6===================\n"
./parser ../tests/example6.kpl | diff ../tests/result6.txt -
echo -e "\n================Test7===================\n"
./parser ../tests/example7.kpl | diff ../tests/result7.txt -
