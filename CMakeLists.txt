# MaterialTestCode_cmake/CMkaeList.txt
cmake_minimum_required( VERSION 2.8)
project( MaterialTestCode )

#This project contains many librarys 

include_directories( include )

add_library( Material src/Material.cpp; include/Material.h )
add_library( Vectors src/Vectors.cpp; include/Vectors.h )
add_library( Matrix src/Matrix.cpp; src/Vectors.cpp; include/Matrix.hpp; include/Vectors.h )
add_library( Cell src/Cell.cpp; src/Matrix.cpp; src/Vectors.cpp; src/Material.cpp; include/Cell.hpp; include/Matrix.hpp; include/Vectors.h; include/Material.h )
add_library( Model src/Model.cpp; src/Cell.cpp; src/Matrix.cpp; src/Vectors.cpp; src/Material.cpp; include/Model.hpp; include/Cell.hpp; include/Matrix.hpp; include/Vectors.h; include/Material.h )

if( NOT BUILD_SHARED_LIBS )
add_definitions( -Dmaths_STATIC )
endif()

add_executable( MaterialTestCode Test/MaterialTestCode.cpp  )
add_executable( VectorsTestCode Test/VectorsTestCode.cpp  )
add_executable( MatrixTestCode Test/MatrixTestCode.cpp  )
add_executable( CellTestCode Test/CellTestCode.cpp  )
add_executable( ModelTestCode Test/ModelTestCode.cpp  )
#
target_link_libraries( MaterialTestCode Material )
target_link_libraries( VectorsTestCode Vectors )
target_link_libraries( MatrixTestCode Matrix )
target_link_libraries( CellTestCode Cell )
target_link_libraries( ModelTestCode Model )

# cmake -G "MinGW Makefiles" -DBUILD_SHARED_LIBS=ON ..
# mingw32-make

# cmake -G "Visual Studio 15 2017 Win64" ..
# bat file for visual stuido
# "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" amd64
# msbuild *.sln
# debug\*.exe