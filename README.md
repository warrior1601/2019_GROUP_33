# 2019_GROUP_33
 
###### Design Team :
 
  * Junaid Afzal
  * Jedidiah Paterson
  * Chanyanis Kulanumphol
  * Chang XING

### Read carefully
 
   * Intructions for downloading and complining this file are detailed below.
   * When downloading as a zip file or cloning the repository DO NOT rename the files or directories.
   * Renaming files or directories will cause build errors when trying to compile.
   * This project utilizes CMake via the command pomt compile the project.
   * The endstate of the project is to read a .txt document then generate a 3-Dimensional obeject
   * Currently the projects generation is only virtual. All of the Vertices are represened by numerical values for the *X-Y-Z* coordinates
   * Later revision of this project will include using a 3-D imaging tool to display th .txt file to the user.
   
#### Model Explained
   * A Model is a 3-dimenional shape that can be comprised of many smaller shapes refered to as cells. 
   * Class Cells furter differentiates into smaller subclasses of hexahedral, pyramid, and tetrahedral. 
   * Each Cell is defined by the number of vertices they have and of the material they are comprised. Tetrahedras have 4,  pyramids have 5, and hexahedrals have 6. 
   * Each vertice is described as a Vector in this project that has a X-Y-Z coordinate. 
   * A material has describing features that includes Color, Density, and Name.
   * This allows the model to be made of many different cells, each cell having its own dimensions and material type. 

#### Functions
   * The user has the ability to create new and change material types of color, density and name
   * Create new vectors and change vectors
   * Add, subtract, multiply, obtain magnitude of, and get distance to a vector
   * Create new cells 
   * Calculate the weight of each cell
   * Calculate the volume of the cell
   * Calculate the center of the gavity of the cell 
   * Rotate a cell around its X, Y, or Z axis
   * Create new model of the model
   * Calculate the volume of the model
   * Calculate the weight of the model
   * Calculate the center of gravity of the model
   * Calculate the overal dimensions of the model
   * Rotate the entire model around its X, Y, or Z axis


# Important notes about compiling with CMake
### All Test files are genorated with one CMakeList.txt
##    MinGW Compiler  
    * After Down loading the github repo you will need to make a build folder
    * (assuming that this file will be Named 2019_GROUP_33)
    * Open cmmand promt and Navigate to dir ..\2019_GROUP_33
    * enter command> mkdir build
    * enter command> cd build
    * enter command> cmake -G "MinGW Makefiles" -DBUILD_SHARED_LIBS=ON ..
    * This will build Libraries for the source files that are dynamiclly linked to the *.exe files
    * enter command> mingw32-make
    * Now the executables will be created and can be testd through the command window
    * enter command> MaterialTestCode.exe (or anyother classes test code)

##    Microsoft Visual Studio
    * After Down loading the github repo you will need to make a build folder
    * (assuming that this file will be Named 2019_GROUP_33)
    * In command prompt
    * Navigate to dir ..\2019_GROUP_33
    * enter command> mkdir build
    * enter command> cd build
    * Commands need to be tailored to match you version of Visual Studio
    * enter command> cmake -G "Visual Studio 15 2017 Win64" ..

<h4>!!NOTE!!</h4> 
    * .bat file for visual stuido is similar to below might not be the same
    * enter command> "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" amd64
    * This sets the PATH for the compiler if you already have this set up in on your system enviroment you may note need to do this
    * enter command> msbuild Computing_Project.sln
    * enter command> cd debug
    * The execuable files for the TEST code will be located here and can be entered via command prompt as follows
    * enter command> MaterialTestCode.exe (or anyother classes test code)



















