cd build/
# cmake ../
# make -j8

cd ../Pythia/
make main -j8
./main > /dev/null

cp events.root ../build/
cd ../build
./LHCbLumi vis_file.mac

cp data.root ../analysis
cd ../analysis

