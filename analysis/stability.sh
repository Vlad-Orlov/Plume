#!/bin/bash

date | tee timelog.txt

for k in {1..20}
do
	. runMT.screen.sh
	root -q groupMTopt.cc
	filenameNew="newData_$k.root"
	filename="rawData_$k.root"
	mv -v data.root $filename
	mv -v dataNew.root $filenameNew
done

date | tee -a timelog.txt
