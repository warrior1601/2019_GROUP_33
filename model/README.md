# Important notes about compiling with CMake
This CMakeList.txt creates a library called model that is made up from all the file in source and include folders, then creates the test code executable for all classes (Material, Vectors, Matrix3x3, Cell and its sub-classes, and Model). The executables are then linked to the model library and CTest files are created from them. Finally the model files required by `ModelTestCode.exe` are copied to the build and Debug directories.

##    MinGW Compiler  
   * Navigate to the root directory of repository
   * enter command> `mkdir build`
   * enter command> `cd build`
   * enter command> `cmake -G "MinGW Makefiles" -DBUILD_SHARED_LIBS=ON ..\model`
   * enter command> `mingw32-make`
   * The executable files can be called from the current directory with the names `MaterialTestCode.exe`, `VectorsTestCode.exe`, `MatrixTestCode.exe`, `CellTestCode.exe`, and `ModelTestCode.exe` - they will return 0 if test is passed

##    Microsoft Visual Studio
  * Navigate to the root directory of repository
  * enter command> `mkdir build`
  * enter command> `cd build`

  :warning: Command below needs to be tailored to match your version of Visual Studio :warning:

  * enter command> `cmake -G "Visual Studio 16 2019" ..\model`

  :warning: The path for the .bat file below may need changing for your visual studio version  :warning:

  * enter command> `"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x86_amd64`
  * enter command> `msbuild Computing_Project.sln`
  * enter command> `cd debug`
  * The executable files can be called from the current directory with the names `MaterialTestCode.exe`, `VectorsTestCode.exe`, `MatrixTestCode.exe`, `CellTestCode.exe`, and `ModelTestCode.exe` - they will return 0 if test is passed

## Xcode Compiler on MacOS
  * Navigate to the root directory of repository
  * enter command> `mkdir build`
  * enter command> `cd build`
  * enter command> `cmake -G "Xcode" -DBUILD_SHARED_LIBS=ON ..\model`
  * ener commadnd> `xcodebuild -scheme ALL_BUILD build`
  * enter command> `cd debug`
  * The executable files can be called from the current directory with the names `MaterialTestCode.exec`, `VectorsTestCode.exec`, `MatrixTestCode.exec`, `CellTestCode.exec`, and `ModelTestCode.exec` - they will return 0 if test is passed
