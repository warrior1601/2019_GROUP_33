# This CMakeList file will load all the individual class executable files in one series of commands

cmake_minimum_required( VERSION 2.8)

project( model )



# This project contains many header files the "include_directories" sets the path for the header files to be located
include_directories( Include )



# Addition of the Libraries needs to have the required headers for each class that is included to ensure that the library is built correctly
add_library( Material 	source/Material.cpp; include/Material.h )
add_library( Vectors 	source/Vectors.cpp; include/Vectors.h )
add_library( Matrix 	source/Matrix.cpp; source/Vectors.cpp; include/Matrix.hpp; include/Vectors.h )
add_library( Cell 	source/Cell.cpp; source/Matrix.cpp; source/Vectors.cpp; source/Material.cpp; include/Cell.hpp; include/Matrix.hpp; include/Vectors.h; include/Material.h )
add_library( Model 	source/Model.cpp; source/Cell.cpp; source/Matrix.cpp; source/Vectors.cpp; source/Material.cpp; include/Model.hpp; include/Cell.hpp; include/Matrix.hpp; include/Vectors.h; include/Material.h )



if( NOT BUILD_SHARED_LIBS )
add_definitions( -Dmaths_STATIC )
endif()



# This creates the .exe file for each test code
add_executable( MaterialTestCode  test_code/MaterialTestCode.cpp  )
add_executable( VectorsTestCode   test_code/VectorsTestCode.cpp  )
add_executable( MatrixTestCode 	  test_code/MatrixTestCode.cpp  )
add_executable( CellTestCode      test_code/CellTestCode.cpp  )
add_executable( ModelTestCode 	  test_code/ModelTestCode.cpp  )



# This links the libraries to the .exe file
target_link_libraries( MaterialTestCode	Material )
target_link_libraries( VectorsTestCode 	Vectors )
target_link_libraries( MatrixTestCode 	Matrix )
target_link_libraries( CellTestCode 	Cell )
target_link_libraries( ModelTestCode 	Model )



ADD_CUSTOM_COMMAND(TARGET ModelTestCode POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                       ${CMAKE_CURRENT_SOURCE_DIR}/../example_models/ExampleModel1.mod
                       ${CMAKE_CURRENT_SOURCE_DIR}/../build/ExampleModel1.mod )

ADD_CUSTOM_COMMAND(TARGET ModelTestCode POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                       ${CMAKE_CURRENT_SOURCE_DIR}/../example_models/ExampleModel2.mod
                       ${CMAKE_CURRENT_SOURCE_DIR}/../build/ExampleModel2.mod )

ADD_CUSTOM_COMMAND(TARGET ModelTestCode POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                       ${CMAKE_CURRENT_SOURCE_DIR}/../example_models/ExampleModel3.mod
                       ${CMAKE_CURRENT_SOURCE_DIR}/../build/ExampleModel3.mod )

ADD_CUSTOM_COMMAND(TARGET ModelTestCode POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                       ${CMAKE_CURRENT_SOURCE_DIR}/../example_models/Model_One.txt
                       ${CMAKE_CURRENT_SOURCE_DIR}/../build/Model_One.txt )

ADD_CUSTOM_COMMAND(TARGET ModelTestCode POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                       ${CMAKE_CURRENT_SOURCE_DIR}/../example_models/Model_Two.txt
                       ${CMAKE_CURRENT_SOURCE_DIR}/../build/Model_Two.txt )



ADD_CUSTOM_COMMAND(TARGET ModelTestCode POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                       ${CMAKE_CURRENT_SOURCE_DIR}/../example_models/ExampleModel1.mod
                       ${CMAKE_CURRENT_SOURCE_DIR}/../build/Debug/ExampleModel1.mod )

ADD_CUSTOM_COMMAND(TARGET ModelTestCode POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                       ${CMAKE_CURRENT_SOURCE_DIR}/../example_models/ExampleModel2.mod
                       ${CMAKE_CURRENT_SOURCE_DIR}/../build/Debug/ExampleModel2.mod )

ADD_CUSTOM_COMMAND(TARGET ModelTestCode POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                       ${CMAKE_CURRENT_SOURCE_DIR}/../example_models/ExampleModel3.mod
                       ${CMAKE_CURRENT_SOURCE_DIR}/../build/Debug/ExampleModel3.mod )

ADD_CUSTOM_COMMAND(TARGET ModelTestCode POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                       ${CMAKE_CURRENT_SOURCE_DIR}/../example_models/Model_One.txt
                       ${CMAKE_CURRENT_SOURCE_DIR}/../build/Debug/Model_One.txt )

ADD_CUSTOM_COMMAND(TARGET ModelTestCode POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                       ${CMAKE_CURRENT_SOURCE_DIR}/../example_models/Model_Two.txt
                       ${CMAKE_CURRENT_SOURCE_DIR}/../build/Debug/Model_Two.txt )






################################################### TO COMPILE WITH MINGW ###################################################
					
# After downloading the GitHub repo you will need to make a build folder
# assuming that this file will be Named 2019_GROUP_33)
# Open command prompt and navigate to dir ..\2019_GROUP_33
# enter command> mkdir build
# enter command> cd build
# enter command> cmake -G "MinGW Makefiles" -DBUILD_SHARED_LIBS=ON ..\model
# This will build libraries for the source files that are dynamically linked to the *.exe files
# enter command> mingw32-make
# The executable files will be located here and can be entered via command prompt as follows
# enter command> MaterialTestCode.exe (or any other classes test code)



################################################ TO COMPILE WITH VISUAL STUDIO ################################################

# After downloading the GitHub repo you will need to make a build folder
# (assuming that this file will be Named 2019_GROUP_33)
# Open command prompt and navigate to dir ..\2019_GROUP_33
# enter command> mkdir build
# enter command> cd build
# Commands need to be tailored to match you version of Visual Studio
# enter command> cmake -G "Visual Studio 15 2017 Win64" ..\model        or      cmake -G "Visual Studio 16 2019" ..\model

################ Note that the path for the .bat file below may need changing for your visual studio version ################

# enter command> "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" amd64        or        "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x86_amd64
# This sets the PATH for the Visual Studio compiler
# enter command> msbuild Computing_Project.sln
# enter command> cd Debug
# The executable files will be located here and can be entered via command prompt as follows
# enter command> MaterialTestCode.exe (or any other classes test code)



################################################### TO COMPILE WITH XCODE ###################################################

# After Downloading the GitHub repo you will need to make a build folder
# (assuming that this file will be Named 2019_GROUP_33)
# Open command prompt and navigate to dir ..\2019_GROUP_33
# enter command> mkdir build
# enter command> cd build
# enter command> cmake -G "Xcode" -DBUILD_SHARED_LIBS=ON ..\model
# enter command> xcodebuild -scheme ALL_BUILD build
# Open the Xcode project file in build
# At the top left, next to the run and stop buttons, click on the ALL_BUILD button
# Then click on the desired executable - which will contain TestCode in file name
# Then click run and open the debug area to see output
# Repeat for all executables  