# MaterialTestCode_cmake/CMkaeList.txt

cmake_minimum_required( VERSION 2.8)

project( MaterialTestCode )

#project( VectorsTestCode )

#This project contains a library

add_library( Material SHARED "src/Material.cpp" )
add_library( Vectors SHARED "src/Vectors.cpp" )
add_library( Matrix SHARED "src/Matrix.cpp;src/Vectors.cpp" )
add_library( Cell SHARED "src/Cell.cpp;src/Matrix.cpp;src/Vectors.cpp;src/Material.cpp" )
add_library( Model SHARED "src/Model.cpp;src/Cell.cpp;src/Matrix.cpp;src/Vectors.cpp;src/Material.cpp" )

include_directories( include )

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

#
# cmake -G "MinGW Makefiles" -DBUILD_SHARED_LIBS=ON ..
# mingw32-make
