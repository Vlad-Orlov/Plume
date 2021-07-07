#! /bin/bash

. setup.sh
make

for i in results_vershift/*/
do
	echo "$i"
	rm newDataMerged.root
	cd $i 
	root -b -q mergeMT.cc
	ln -s "$i/newDataMerged.root" ./
	./bin/stabana
	mkdir -p "histos/$i"
	mv histos.root "histos/$i/hist.root"
done

