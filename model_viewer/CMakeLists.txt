# # This CMakeList file will create the Observer executable
cmake_minimum_required( VERSION 3.9.2 )

foreach(p
    CMP0071 # 3.10: Let AUTOMOC and AUTOUIC process GENERATED files
    )
  if(POLICY ${p})
    cmake_policy(SET ${p} NEW)
  endif()
endforeach()

# The name of the project and its curent version
PROJECT( Observer VERSION 1.2.2 )

# The CMake build process might generate some new files in the current directory. This makes sure they can be found.
set( CMAKE_INCLUDE_CURRENT_DIR ON )

# This allows CMake to run one of Qt's build tools called moc if it is needed. moc.exe can be found in Qt's bin directory. We'll look at what moc does later.
set( CMAKE_AUTOMOC ON )
set( CMAKE_AUTOUIC ON )
set( CMAKE_AUTORCC ON )

# Find the Qt widgets package. This locates the relevant include and lib directories, and the necessary static libraries for linking.
find_package( Qt5Widgets )

# Doing the same for VTK
find_package( VTK REQUIRED )
include( ${VTK_USE_FILE} )

# This project contains many header files the "include_directories" sets the path for the header files to be located
include_directories( include )
include_directories( ../model/include )

add_library(Observer_Model_Library
            ../model/include/Material.h;                  ../model/source/Material.cpp;
            ../model/include/Vectors.h;                   ../model/source/Vectors.cpp;
            ../model/include/Matrix.hpp;                  ../model/source/Matrix.cpp;
            ../model/include/Cell.hpp;                    ../model/source/Cell.cpp;
            ../model/include/Model.hpp;                   ../model/source/Model.cpp;
					  ../model/include/double_equality_function.h;  ../model/source/double_equality_function.cpp;
	          ../model/include/Testing_File_Functions.h;
)

set( UIS mainwindow.ui )
qt5_wrap_ui( UI_Srcs ${UIS} )

if (WIN32)
  # Define the executable output and its sources
  add_executable(Observer #WIN32
                source/main.cpp
                include/mainwindow.h          source/mainwindow.cpp           source/mainwindow.ui
                include/filters.h             source/filters.cpp              source/filters.ui
                include/edit_light.h          source/edit_light.cpp           source/edit_light.ui
                include/vtklight_withname.h   source/vtklight_withname.cpp
  )

else()
  # Define the executable output and its sources
  add_executable(Observer MACOSX_BUNDLE
                source/main.cpp
                include/mainwindow.h          source/mainwindow.cpp           source/mainwindow.ui
                include/filters.h             source/filters.cpp              source/filters.ui
                include/edit_light.h          source/edit_light.cpp           source/edit_light.ui
                include/vtklight_withname.h   source/vtklight_withname.cpp
                images/Images.qrc
)
endif()

# Tell CMake that the executable depends on library built in SEMESTER 1
target_link_libraries( Observer Observer_Model_Library )

# Tell CMake that the executable depends on the Qt::Widget libraries.
target_link_libraries( Observer Qt5::Widgets )

# Tell CMake that the executable depends on the VTK libraries
target_link_libraries( Observer ${VTK_LIBRARIES} )
