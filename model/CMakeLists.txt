# This CMakeList file will create the Model library and its test code and CTests
cmake_minimum_required( VERSION 3.9.2 )

# The name of the project and its curent version
project( Model VERSION 4.2.3 )

# This project contains many header files the "include_directories" sets the path for the header files to be located
include_directories( include )

# Addition of the Libraries needs to have the required headers for each class that is included to ensure that the library is built correctly
add_library( Model  include/Material.h;   source/Material.cpp;
                    include/Vectors.h;    source/Vectors.cpp;
                    include/Matrix.hpp;   source/Matrix.cpp;
                    include/Cell.hpp;     source/Cell.cpp;
                    include/Model.hpp;    source/Model.cpp;
)

# Library check
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
target_link_libraries( MaterialTestCode	Model )
target_link_libraries( VectorsTestCode 	Model )
target_link_libraries( MatrixTestCode 	Model )
target_link_libraries( CellTestCode 	  Model )
target_link_libraries( ModelTestCode    Model )

# Required for automating testing with TravisCI
include ( CTest )

# Create the CTests
add_test( MaterialTestCode  MaterialTestCode )
add_test( VectorsTestCode   VectorsTestCode  )
add_test( MatrixTestCode 	  MatrixTestCode  )
add_test( CellTestCode      CellTestCode  )
add_test( ModelTestCode 	  ModelTestCode )

# Copy the model files for ModelTestCode.exe/MaterialTestCode_CTest.exe in to build directory
ADD_CUSTOM_COMMAND( TARGET ModelTestCode POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
                    ${CMAKE_CURRENT_SOURCE_DIR}/../example_models/ExampleModel1.mod
                    ${CMAKE_CURRENT_SOURCE_DIR}/../build/model/ExampleModel1.mod )

ADD_CUSTOM_COMMAND( TARGET ModelTestCode POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
                    ${CMAKE_CURRENT_SOURCE_DIR}/../example_models/ExampleModel2.mod
                    ${CMAKE_CURRENT_SOURCE_DIR}/../build/model/ExampleModel2.mod )

ADD_CUSTOM_COMMAND( TARGET ModelTestCode POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
                    ${CMAKE_CURRENT_SOURCE_DIR}/../example_models/ExampleModel3.mod
                    ${CMAKE_CURRENT_SOURCE_DIR}/../build/model/ExampleModel3.mod )

ADD_CUSTOM_COMMAND( TARGET ModelTestCode POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
                    ${CMAKE_CURRENT_SOURCE_DIR}/../example_models/Model_One.txt
                    ${CMAKE_CURRENT_SOURCE_DIR}/../build/model/Model_One.txt )

ADD_CUSTOM_COMMAND( TARGET ModelTestCode POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
                    ${CMAKE_CURRENT_SOURCE_DIR}/../example_models/Model_Two.txt
                    ${CMAKE_CURRENT_SOURCE_DIR}/../build/model/Model_Two.txt )


# Copy the model files for ModelTestCode.exe/MaterialTestCode_CTest.exe in to debug directory
ADD_CUSTOM_COMMAND( TARGET ModelTestCode POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
                    ${CMAKE_CURRENT_SOURCE_DIR}/../example_models/ExampleModel1.mod
                    ${CMAKE_CURRENT_SOURCE_DIR}/../build/model/Debug/ExampleModel1.mod )

ADD_CUSTOM_COMMAND( TARGET ModelTestCode POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
                    ${CMAKE_CURRENT_SOURCE_DIR}/../example_models/ExampleModel2.mod
                    ${CMAKE_CURRENT_SOURCE_DIR}/../build/model/Debug/ExampleModel2.mod )

ADD_CUSTOM_COMMAND( TARGET ModelTestCode POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
                    ${CMAKE_CURRENT_SOURCE_DIR}/../example_models/ExampleModel3.mod
                    ${CMAKE_CURRENT_SOURCE_DIR}/../build/model/Debug/ExampleModel3.mod )

ADD_CUSTOM_COMMAND( TARGET ModelTestCode POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
                    ${CMAKE_CURRENT_SOURCE_DIR}/../example_models/Model_One.txt
                    ${CMAKE_CURRENT_SOURCE_DIR}/../build/model/Debug/Model_One.txt )

ADD_CUSTOM_COMMAND( TARGET ModelTestCode POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
                    ${CMAKE_CURRENT_SOURCE_DIR}/../example_models/Model_Two.txt
                    ${CMAKE_CURRENT_SOURCE_DIR}/../build/model/Debug/Model_Two.txt )
