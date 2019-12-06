# CMakeList.txt
cmake_minimum_required( VERSION 2.8)
project( Computing_Project )

# This CMakeList file will load all the individual class executable files in one series of commands
####################################################################################################
# THE REQUIRE COMMANDS ARE AT THE LOCATED AT THE BOTTOM OF THE FILE WITH
# THE *.bat FILE NEEDS TO BE CHECKED FOR YOUR VERSION OF MICORSOFT VISUAL STUDIO
####################################################################################################

# This project contains many header files the "include_directories" sets the path for the header files
# To be located

include_directories( include )

# Addition of the Libraries needs to have the required headers for each class that is included to ensure
# That the library is built correctly

add_library( Material src/Material.cpp; include/Material.h )
add_library( Vectors src/Vectors.cpp; include/Vectors.h )
add_library( Matrix src/Matrix.cpp; src/Vectors.cpp; include/Matrix.hpp; include/Vectors.h )
add_library( Cell src/Cell.cpp; src/Matrix.cpp; src/Vectors.cpp; src/Material.cpp; include/Cell.hpp; include/Matrix.hpp; include/Vectors.h; include/Material.h )
add_library( Model src/Model.cpp; src/Cell.cpp; src/Matrix.cpp; src/Vectors.cpp; src/Material.cpp; include/Model.hpp; include/Cell.hpp; include/Matrix.hpp; include/Vectors.h; include/Material.h )

if( NOT BUILD_SHARED_LIBS )
add_definitions( -Dmaths_STATIC )
endif()

# This creates the .exe file for each test code

add_executable( MaterialTestCode Test/MaterialTestCode.cpp  )
add_executable( VectorsTestCode Test/VectorsTestCode.cpp  )
add_executable( MatrixTestCode Test/MatrixTestCode.cpp  )
add_executable( CellTestCode Test/CellTestCode.cpp  )
add_executable( ModelTestCode Test/ModelTestCode.cpp  )

# This links the libraries to the .exe file

target_link_libraries( MaterialTestCode Material )
target_link_libraries( VectorsTestCode Vectors )
target_link_libraries( MatrixTestCode Matrix )
target_link_libraries( CellTestCode Cell )
target_link_libraries( ModelTestCode Model )

####################################################################################################

#IMPORTANT****************************TO COMPILE WITH MinGW*******************************IMPORTANT
					
# After Down loading the GitHub repo you will need to make a build folder
# (assuming that this file will be Named 2019_GROUP_33)
# In command prompt
# Navigate to dir ..\2019_GROUP_33
# enter command> mkdir build
# enter command> cd build
# enter command> cmake -G "MinGW Makefiles" -DBUILD_SHARED_LIBS=ON ..
# This will build Libraries for the source files that are dynamically linked to the *.exe files
# enter command> mingw32-make
# Now the executables will be created and can be tested through the command window
# enter command> MaterialTestCode.exe (or any other classes test code)

####################################################################################################

# IMPORTANT*************************TO COMPILE WITH Visual Studio**************************IMPORTANT
# After Downloading the GitHub repo you will need to make a build folder
# (assuming that this file will be Named 2019_GROUP_33)
# In command prompt
# Navigate to dir ..\2019_GROUP_33)
# enter command> mkdir build
# enter command> cd build
# Commands need to be tailored to match you version of Visual Studio
# enter command> cmake -G "Visual Studio 15 2017 Win64" ..

#    !!NOTE!!	.bat file for visual studio is similar to below might not be the same
# enter command> "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" amd64
# enter command> msbuild Computing_Project.sln
# enter command> cd debug
# The executable files for the TEST code will be located here and can be entered via command prompt as follows
# enter command> MaterialTestCode.exe (or any other classes test code)
