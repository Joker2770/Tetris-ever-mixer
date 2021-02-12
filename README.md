# Tetris-ever
An simple tetris game writen with C, and be render by SDL2.

## Dependencies
Required:
* [cmake](http://www.cmake.org) - buildsystem
* g++ (>= 7.4.0 recommended)
* gcc (>= 7.4.0 recommended)
* libsdl2-dev,libsdl2-ttf-dev (Linux), sdl2.nuget,sdl2_ttf.nuget (Windows)

## Build on Ubuntu(Linux)
~~~
sudo apt install libsdl2-dev libsdl2-ttf-dev
git clone https://github.com/Joker2770/Tetris-ever.git
cd Tetris-ever
mkdir build
cd build
cmake ..
make
cp ../res/bb3273.ttf ./
./Tetris-ever
sudo make install
Tetris-ever
~~~

## Build on Windows
~~~
git clone https://github.com/Joker2770/Tetris-ever.git
cd Tetris-ever/msvc/
~~~
Then double click 'Tetris-ever.sln', build with Visual Studio, do not forget copy 'bb3273.ttf' to program directory.
