# Important notes about compiling with CMake
This cmake list does ......................................
##    MinGW Compiler  
   * After downloading the GitHub repo you will need to make a build folder
   * (assuming that this file will be Named 2019_GROUP_33)
   * Open command prompt and navigate to dir ..\2019_GROUP_33
   * enter command> `mkdir build`
   * enter command> `cd build`
   * enter command> `cmake -G "MinGW Makefiles" -DBUILD_SHARED_LIBS=ON ..\model`
   * This will build libraries for the source files that are dynamically linked to the .exe files
   * enter command> `mingw32-make`
   * The executable files will be located here and can be entered via command prompt as follows
   * enter command> `MaterialTestCode.exe` (or any other classes test code) .... more details

##    Microsoft Visual Studio
   * After downloading the GitHub repo you will need to make a build folder
   * (assuming that this file will be Named 2019_GROUP_33)
   * Open command prompt and navigate to dir ..\2019_GROUP_33
   * enter command> `mkdir build`
   * enter command> `cd build`
   
   :warning: Command below needs to be tailored to match your version of Visual Studio :warning:
   
   * enter command> `cmake -G "Visual Studio 16 2019" ..\model` 
   
   :warning: The path for the .bat file below may need changing for your visual studio version  :warning:
   
   * enter command> `"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x86_amd64`
   * enter command> `msbuild Computing_Project.sln`
   * enter command> `cd debug`
   * The executable files will be located here and can be entered via command prompt as follows
   * enter command> `MaterialTestCode.exe` (or any other classes test code) ... give all names

## Xcode Compiler on MacOS
   * After Downloading the GitHub repo you will need to make a build folder
   * (assuming that this file will be Named 2019_GROUP_33)
   * Open command prompt and navigate to dir ..\2019_GROUP_33
   * enter command> `mkdir build`
   * enter command> `cd build`
   * enter command> `cmake -G "Xcode" -DBUILD_SHARED_LIBS=ON ..\model`
   * ener commadnd> `xcodebuild -scheme ALL_BUILD build`
   * enter command> `cd debug`
   * The executable files will be located in the debug dir .... more details
