## Plume

# Geant4 version : 4.10.06

## HOW TO
to build the project do:
```
$ git clone https://github.com/Vlad-Orlov/Plume.git
$ mkdir build-Plume && cd build-Plume
$ cmake ../Plume
$ make -jN /// N is the number of threads available on the machine
```
An executable file should appear. Run it with
```
$ ./Plume
```
A window will pop-up with a simple geometry. When pressing `run` button you should see a particle hitting quartz and emmited cherenkov photons.

# To run:
To run and save the results in a `.root` file do:
```
$ ./Plume run.mac filename.root
```
A file `filename.root` will appear in the `build-Plume` directory. Open it with ROOT `TBrowser` and you should see a tuple named `nPhot`, which shows how many photons were registered in each event.
