@echo off
rem This bat file will run all the Test code at once using MinGW compiler.
rem It will also run the CTest code. 
rem The user will be able to see the out put from each Test code as well as from the CTest

mkdir build
cd build
cmake -G "MinGW Makefiles" -DBUILD_SHARED_LIBS=ON ..
mingw32-make

MaterialTestCode.exe
VectorsTestCode.exe
CellTestCode.exe
ModelTestCode.exe
MatrixTestCode.exe

mingw32-make test
cd ..
rmdir /Q /S build
