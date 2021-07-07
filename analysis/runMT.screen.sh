#!/bin/bash

rm dataNew_*

rm log.txt
cd ../build
cmake ../ > /dev/null
make > /dev/null
cd ../analysis

rm dataNew*
rm data*


for i in {1..20}
do
	mkdir "temp_$i"
	cp groupMTopt.cc "temp_$i"
	cp ana2MT.cc "temp_$i"
	cp runMT.sh "temp_$i"
	cd "temp_$i"
	screen -S "Lumi_$i" -L -d -m ./runMT.sh $i
	cd ../
done



while [ $(screen -ls | grep Lumi | wc -l) -ne 0 ]
do
	sleep 1
done

cd temp_1
nFile=$(ls | grep data_ | wc -l)
cd -

touch log.txt

for i in {1..20}
do
	cat "temp_$i/log.txt">>log.txt
	cp "temp_$i/"data_* ./
done


root -l -b -q "mergeMT.cc+(20,$nFile)" > /dev/null

rm -rf temp*

rm *.d *.so *.pcm

# python2 draw.py

