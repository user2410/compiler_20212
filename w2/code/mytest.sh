#! /bin/bash
echo -e "\n================test1===================\n"
./scanner ../tests/example1.kpl | diff ../tests/result1.txt -
echo -e "\n================test2===================\n"
./scanner ../tests/example2.kpl | diff ../tests/result2.txt -
echo -e "\n================test3===================\n"
./scanner ../tests/example3.kpl | diff ../tests/result3.txt -
echo -e "\n================test4===================\n"
./scanner ../tests/example4.kpl | diff ../tests/result4.txt -
echo -e "\n================test5===================\n"
./scanner ../tests/example5.kpl | diff ../tests/result5.txt -
echo -e "\n================test6===================\n"
./scanner ../tests/example6.kpl | diff ../tests/result6.txt -
