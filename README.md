# 2019_GROUP_33
 
 
 
###### Design Team :
  * Junaid Afzal
  * Jedidiah Paterson
  * Chanyanis Kulanumphol
  * Chang XING

### Read Carefully
   * Instructions for downloading and compiling this file are detailed below.
   * When downloading as a zip file or cloning the repository DO NOT rename the files or directories.
   * Renaming files or directories will cause build errors when trying to compile.
   * This project utilizes CMake via the command prompt compile the project.
   * The end-state of the project is to read a .txt document then generate a 3-Dimensional object
   * Currently the projects generation is only virtual. All of the Vertices are represented by numerical values for the *X-Y-Z* coordinates
   * Later revision of this project will include using a 3-D imaging tool to display the .txt file to the user.
   
#### Model Explained
   * A Model is a 3-dimenional shape that can be comprised of many smaller shapes referred to as cells. 
   * Class Cell further differentiates into smaller sub-classes of tetrahedron, pyramid, hexahedron. 
   * Each Cell is defined by it's number of vertices and material. Tetrahedras have 4,  pyramids have 5, and hexahedrals have 6. 
   * Each vertex is described as a Vector in this project that has a X-Y-Z coordinate. 
   * A material includes it's colour, density and name.
   * This allows the model to be made of many different cells, with each cell having its own dimensions and material type. 

#### Functions
   * Create and edit materials
   * Create and edit vectors
   * Vector functions include - add vectors, subtract vectors, multiply vectors, obtain magnitude of vector, and get distance to another vector
   * Create and edit cells 
   * Cell function include - calculating the weight, calculating the volume, calculating the center of gravity of a cell, rotating a cell around an X, Y, or Z axis centered on a vector point
   * Create and edit model
   * Model functions include - calculating the volume of the model, calculating the weight of the model, calculating the center of gravity of the model, calculating the overall dimensions of the model, rotating the entire model around an X, Y, or Z axis centered on a vector point



# Important notes about compiling with CMake
### All Test files are generated with one CMakeList.txt
##    MinGW Compiler  
    * After downloading the GitHub repo you will need to make a build folder
    * (assuming that this file will be Named 2019_GROUP_33)
    * Open command prompt and navigate to dir ..\2019_GROUP_33
    * enter command> mkdir build
    * enter command> cd build
    * enter command> cmake -G "MinGW Makefiles" -DBUILD_SHARED_LIBS=ON ..
    * This will build libraries for the source files that are dynamically linked to the *.exe files
    * enter command> _mingw32-make_
    * The executable files will be located here and can be entered via command prompt as follows
    * enter command> MaterialTestCode.exe (or any other classes test code)

##    Microsoft Visual Studio
    * After downloading the GitHub repo you will need to make a build folder
    * (assuming that this file will be Named 2019_GROUP_33)
    * Open command prompt and navigate to dir ..\2019_GROUP_33
    * enter command> mkdir build
    * enter command> cd build
    * Commands need to be tailored to match you version of Visual Studio
    * enter command> cmake -G "Visual Studio 15 2017 Win64" ..
    #################### Note that the path for the .bat file below may need changing for your visual studio version ####################
    * enter command> "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" amd64
    * This sets the PATH for the Visual Studio compiler
    * enter command> msbuild Computing_Project.sln
    * enter command> cd debug
    * The executable files will be located here and can be entered via command prompt as follows
    * enter command> MaterialTestCode.exe (or any other classes test code)

## Xcode Compiler on MacOS
    * After Downloading the GitHub repo you will need to make a build folder
    * (assuming that this file will be Named 2019_GROUP_33)
    * Open command prompt and navigate to dir ..\2019_GROUP_33
    * enter command> mkdir build
    * enter command> cd build
    * enter command> cmake -G "Xcode" -DBUILD_SHARED_LIBS=ON ..
    * ener commadnd> xcodebuild -scheme ALL_BUILD build
    * enter command> cd debug
    * The executable files will be located in the debug dir
