#!/bin/bash

rm log.txt

date | tee time.txt

for i in {1..20}
do
	cd ../build
	cmake ../ > /dev/null
	make > /dev/null
	./LHCbLumi vis_file.mac > /dev/null #| grep Random:seed
	cp data.root ../analysis
	cd ../analysis
	# rm dataNew.root
	root -b -q -l group.cc  > /dev/null
	root -b -q -l ana2.cc | grep Mean | awk '{print $3}' | tee -a log.txt
done

date | tee -a time.txt

mv time.txt timelog.txt



python2 draw.py
