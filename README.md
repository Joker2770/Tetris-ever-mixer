# Tetris-ever-mixer
An simple tetris game writen with C, and be render by SDL2.

## Dependencies
Required:
* [cmake](http://www.cmake.org) - buildsystem
* g++ (>= 7.4.0 recommended)
* gcc (>= 7.4.0 recommended)
* libsdl2-dev,libsdl2-ttf-dev,libsdl2-mixer-dev (Linux), sdl2.nuget,sdl2_ttf.nuget,sdl2_mixer.nuget (Windows)

## Build on Ubuntu(Linux)
~~~
sudo apt install libsdl2-dev libsdl2-ttf-dev libsdl2-mixer-dev
git clone https://github.com/Joker2770/Tetris-ever-mixer.git
cd Tetris-ever-mixer
mkdir build
cd build
cmake ..
make
cp ../res/*.* ./
./Tetris-ever-mixer
sudo make install
Tetris-ever-mixer
~~~

## Build on Windows
~~~
git clone https://github.com/Joker2770/Tetris-ever-mixer.git
cd Tetris-ever-mixer/msvc/
~~~
Then double click 'Tetris-ever-mixer.sln', build with Visual Studio, do not forget copy 'bb3273.ttf' and 'Aaron-19-Tetris-YANGS-remix.mp3' to program directory.
