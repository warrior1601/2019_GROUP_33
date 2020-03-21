# Important notes about compiling with CMake
This CMakeList.txt first finds the required Qt and VTK libraries, as well as creating the required Model library. Then it creates the executable, called model_viewer, from the source and include folders of the model_viewer folder. The model_viewer file is then linked to the required libraries of Qt, VTK and Model. Image files that are needed by the model_viewer are copied from the images folder to the build directory. Finally the installer is created depending upon if the compilation is occurring on windows or not windows.

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
   * enter command> `xcodebuild -scheme ALL_BUILD build`
   * enter command> `cd debug`
   * The executable file, `model_viewer`, can be called from the current directory
