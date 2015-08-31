#!/usr/bin/env bash

echo '==================================Begin'

echo '==================================HeapTrack.cpp'

echo '########################Build..'

g++ -std=c++11 -o test.out HeapTrack.cpp

echo '########################Test..'

./test.out

echo '==================================TemplateUtil.cpp'

echo '########################Build..'

g++ -std=c++11 -o test.out TemplateUtil.cpp

echo '########################Test..'

./test.out

echo '==================================Clean'

rm -f ./test.out

echo '==================================Finish'