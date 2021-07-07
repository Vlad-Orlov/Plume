make -j8 
./LHCbLumi vis_file.mac file.root 
root -b -q groupMTopt.cc+()

../analysis/bin/stabana
root -b -q ana.C+(1)
mv comparison.png ../../Reports_Lumi/1_25_20/pos$1_mode24.png

../analysis/bin/stabana 1
root -b -q ana.C+(0)
mv comparison.png ../../Reports_Lumi/1_25_20/pos$1_mode1.png
