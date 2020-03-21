# Important notes about compiling with CMake
This cmake list does ......................................

##    MinGW Compiler  
   * Navigate to the root directory of repository
   * enter command> `mkdir build`
   * enter command> `cd build`
   * enter command> `cmake -G "MinGW Makefiles" -DBUILD_SHARED_LIBS=ON ..\model_viewer`
   * This will build libraries for the source files that are dynamically linked to the .exe files
   * enter command> `mingw32-make`
   * The executable file, `model_viewer.exe`, can be called from the current directory

##    Microsoft Visual Studio
   * Navigate to the root directory of repository
   * enter command> `mkdir build`
   * enter command> `cd build`

   :warning: Command below needs to be tailored to match your version of Visual Studio :warning:

   * enter command> `cmake -G "Visual Studio 16 2019" ..\model_viewer`

   :warning: The path for the .bat file below may need changing for your visual studio version  :warning:

   * enter command> `"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x86_amd64`    
   * enter command> `msbuild Computing_Project.sln`
   * enter command> `cd debug`
   * The executable file, `model_viewer.exe`, can be called from the current directory

## Xcode Compiler on MacOS
   * Navigate to the root directory of repository
   * enter command> `mkdir build`
   * enter command> `cd build`
   * enter command> `cmake -G "Xcode" -DBUILD_SHARED_LIBS=ON ..\model_viewer`
   * ener commadnd> `xcodebuild -scheme ALL_BUILD build`
   * enter command> `cd debug`
   * The executable file, `model_viewer.exe`, can be called from the current directory
