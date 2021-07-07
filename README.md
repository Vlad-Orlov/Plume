# Plume

# Geant4 version : 4.10.06

## HOW TO
to build the project do:
```
git clone https://github.com/Vlad-Orlov/Plume.git
mkdir build-Plume && cd build-Plume
cmake ../Plume
make -jN /// N is the number of threads available on the machine
```
Then an executable file should appear. Run it with
```
./Plume
```
A window will pop-up with a simple geometry. When pressing `run` button you should a particle hitting quartz and generated cherenkov photons.
