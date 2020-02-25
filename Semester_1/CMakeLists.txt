# This CMakeList file will load all the individual class executable files in one series of commands

cmake_minimum_required( VERSION 2.8)

project( Computing_Project )



# This project contains many header files the "include_directories" sets the path for the header files to be located
include_directories( inc )



# Addition of the Libraries needs to have the required headers for each class that is included to ensure that the library is built correctly
add_library( Material src/Material.cpp; inc/Material.h )
add_library( Vectors src/Vectors.cpp; inc/Vectors.h )
add_library( Matrix src/Matrix.cpp; src/Vectors.cpp; inc/Matrix.hpp; inc/Vectors.h )
add_library( Cell src/Cell.cpp; src/Matrix.cpp; src/Vectors.cpp; src/Material.cpp; inc/Cell.hpp; inc/Matrix.hpp; inc/Vectors.h; inc/Material.h )
add_library( Model src/Model.cpp; src/Cell.cpp; src/Matrix.cpp; src/Vectors.cpp; src/Material.cpp; inc/Model.hpp; inc/Cell.hpp; inc/Matrix.hpp; inc/Vectors.h; inc/Material.h )



if( NOT BUILD_SHARED_LIBS )
add_definitions( -Dmaths_STATIC )
endif()



# This creates the .exe file for each test code
add_executable( MaterialTestCode all_test_code/MaterialTestCode.cpp  )
add_executable( VectorsTestCode all_test_code/VectorsTestCode.cpp  )
add_executable( MatrixTestCode all_test_code/MatrixTestCode.cpp  )
add_executable( CellTestCode all_test_code/CellTestCode.cpp  )
add_executable( ModelTestCode all_test_code/ModelTestCode.cpp  )



# This links the libraries to the .exe file
target_link_libraries( MaterialTestCode Material )
target_link_libraries( VectorsTestCode Vectors )
target_link_libraries( MatrixTestCode Matrix )
target_link_libraries( CellTestCode Cell )
target_link_libraries( ModelTestCode Model )



ADD_CUSTOM_COMMAND(TARGET ModelTestCode POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                       ${CMAKE_CURRENT_SOURCE_DIR}/all_model_files/ExampleModel1.mod
                       ${CMAKE_CURRENT_SOURCE_DIR}/_build/ExampleModel1.mod )

ADD_CUSTOM_COMMAND(TARGET ModelTestCode POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                       ${CMAKE_CURRENT_SOURCE_DIR}/all_model_files/ExampleModel2.mod
                       ${CMAKE_CURRENT_SOURCE_DIR}/_build/ExampleModel2.mod )

ADD_CUSTOM_COMMAND(TARGET ModelTestCode POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                       ${CMAKE_CURRENT_SOURCE_DIR}/all_model_files/ExampleModel3.mod
                       ${CMAKE_CURRENT_SOURCE_DIR}/_build/ExampleModel3.mod )

ADD_CUSTOM_COMMAND(TARGET ModelTestCode POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                       ${CMAKE_CURRENT_SOURCE_DIR}/all_model_files/Model_One.txt
                       ${CMAKE_CURRENT_SOURCE_DIR}/_build/Model_One.txt )

ADD_CUSTOM_COMMAND(TARGET ModelTestCode POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                       ${CMAKE_CURRENT_SOURCE_DIR}/all_model_files/Model_Two.txt
                       ${CMAKE_CURRENT_SOURCE_DIR}/_build/Model_Two.txt )

ADD_CUSTOM_COMMAND(TARGET ModelTestCode POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                       ${CMAKE_CURRENT_SOURCE_DIR}/all_model_files/ExampleModel1.mod
                       ${CMAKE_CURRENT_SOURCE_DIR}/_build/Debug/ExampleModel1.mod )

ADD_CUSTOM_COMMAND(TARGET ModelTestCode POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                       ${CMAKE_CURRENT_SOURCE_DIR}/all_model_files/ExampleModel2.mod
                       ${CMAKE_CURRENT_SOURCE_DIR}/_build/Debug/ExampleModel2.mod )

ADD_CUSTOM_COMMAND(TARGET ModelTestCode POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                       ${CMAKE_CURRENT_SOURCE_DIR}/all_model_files/ExampleModel3.mod
                       ${CMAKE_CURRENT_SOURCE_DIR}/_build/Debug/ExampleModel3.mod )

ADD_CUSTOM_COMMAND(TARGET ModelTestCode POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                       ${CMAKE_CURRENT_SOURCE_DIR}/all_model_files/Model_One.txt
                       ${CMAKE_CURRENT_SOURCE_DIR}/_build/Debug/Model_One.txt )

ADD_CUSTOM_COMMAND(TARGET ModelTestCode POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                       ${CMAKE_CURRENT_SOURCE_DIR}/all_model_files/Model_Two.txt
                       ${CMAKE_CURRENT_SOURCE_DIR}/_build//Debug/Model_Two.txt )






################################################### TO COMPILE WITH MINGW ###################################################
					
# After downloading the GitHub repo you will need to make a build folder
# assuming that this file will be Named 2019_GROUP_33)
# Open command prompt and navigate to dir ..\2019_GROUP_33
# enter command> mkdir _build
# enter command> cd _build
# enter command> cmake -G "MinGW Makefiles" -DBUILD_SHARED_LIBS=ON ..
# This will build libraries for the source files that are dynamically linked to the *.exe files
# enter command> mingw32-make
# The executable files will be located here and can be entered via command prompt as follows
# enter command> MaterialTestCode.exe (or any other classes test code)



################################################ TO COMPILE WITH VISUAL STUDIO ################################################

# After downloading the GitHub repo you will need to make a build folder
# (assuming that this file will be Named 2019_GROUP_33)
# Open command prompt and navigate to dir ..\2019_GROUP_33
# enter command> mkdir _build
# enter command> cd _build
# Commands need to be tailored to match you version of Visual Studio
# enter command> cmake -G "Visual Studio 15 2017 Win64" ..        or      cmake -G "Visual Studio 16 2019" .. 

################ Note that the path for the .bat file below may need changing for your visual studio version ################

# enter command> "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" amd64        or        "C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\VC\Auxiliary\Build\vcvarsall.bat" x86_amd64
# This sets the PATH for the Visual Studio compiler
# enter command> msbuild Computing_Project.sln
# enter command> cd debug
# The executable files will be located here and can be entered via command prompt as follows
# enter command> MaterialTestCode.exe (or any other classes test code)



################################################### TO COMPILE WITH XCODE ###################################################

# After Downloading the GitHub repo you will need to make a build folder
# (assuming that this file will be Named 2019_GROUP_33)
# Open command prompt and navigate to dir ..\2019_GROUP_33
# enter command> mkdir _build
# enter command> cd _build
# enter command> cmake -G "Xcode" -DBUILD_SHARED_LIBS=ON ..
# enter command> xcodebuild -scheme ALL_BUILD build
# Open the Xcode project file in build
# At the top left, next to the run and stop buttons, click on the ALL_BUILD button
# Then click on the desired executable - which will contain TestCode in file name
# Then click run and open the debug area to see output
# Repeat for all executables  