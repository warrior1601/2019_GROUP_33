# This CMakeList file will create all the test code for model
cmake_minimum_required( VERSION 2.8)

# The name of the project
project( model )

# This project contains many header files the "include_directories" sets the path for the header files to be located
include_directories( Include )

# Addition of the Libraries needs to have the required headers for each class that is included to ensure that the library is built correctly
add_library( Model 	source/Material.cpp;  include/Material.h;
                    source/Vectors.cpp;   include/Vectors.h;
                    source/Matrix.cpp;    include/Matrix.hpp;
                    source/Cell.cpp;      include/Cell.hpp;
                    source/Model.cpp;     include/Model.hpp;
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

#Create the CTests
add_test( MaterialTestCode  MaterialTestCode_CTest )
add_test( VectorsTestCode   VectorsTestCode_CTest  )
add_test( MatrixTestCode 	  MatrixTestCode_CTest  )
add_test( CellTestCode      CellTestCode_CTest  )
add_test( ModelTestCode 	  ModelTestCode_CTest )

# Copy the model files for ModelTestCode.exe in to build directory
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


# Copy the model files for ModelTestCode.exe in to debug directory
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
