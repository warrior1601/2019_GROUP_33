cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

foreach(p
    CMP0071 # 3.10: Let AUTOMOC and AUTOUIC process GENERATED files
    )
  if(POLICY ${p})
    cmake_policy(SET ${p} NEW)
  endif()
endforeach()

PROJECT( model_viewer )

# The CMake build process might generate some new files in the current
# directory. This makes sure they can be found.
set( CMAKE_INCLUDE_CURRENT_DIR ON )

# This allows CMake to run one of Qt's build tools called moc
# if it is needed. moc.exe can be found in Qt's bin directory.
# We'll look at what moc does later.
set( CMAKE_AUTOMOC ON )
set( CMAKE_AUTOUIC ON )
set( CMAKE_AUTORCC ON )

# Find the Qt widgets package. This locates the relevant include and
# lib directories, and the necessary static libraries for linking.
find_package( Qt5Widgets )

include_directories( include )
include_directories( ../model/include )

add_library( Model 	../model/source/Model.cpp; ../model/source/Cell.cpp; ../model/source/Matrix.cpp; 			../model/source/Vectors.cpp; ../model/source/Material.cpp; ../model/include/Model.hpp; 			../model/include/Cell.hpp; ../model/include/Matrix.hpp; ../model/include/Vectors.h; 			../model/include/Material.h )

set( UIS mainwindow.ui )
qt5_wrap_ui( UI_Srcs ${UIS} )

# set( ICONS Icons/icons.qrc )
# qt5_add_resources( QRC_Srcs ${ICONS} )


# Also link to VTK
find_package( VTK REQUIRED )
include( ${VTK_USE_FILE} )

# Define the executable output and its sources
add_executable( model_viewer MACOSX_BUNDLE
				source/main.cpp
				source/mainwindow.cpp	include/mainwindow.h	source/mainwindow.ui
				source/edit_light.cpp 	include/edit_light.h 	source/edit_light.ui
				source/filters.cpp 	include/filters.h 		source/filters.ui
				source/vtklight_withname.cpp include/vtklight_withname.h
				images/Images.qrc
				)

# Tell CMake that the executable depends on Library built in SEMESTER 1
target_link_libraries( model_viewer Model )

# Tell CMake that the executable depends on the Qt::Widget libraries.
target_link_libraries( model_viewer Qt5::Widgets )

# Tell CMake that the executable depends on the VTK libraries
target_link_libraries( model_viewer ${VTK_LIBRARIES} )

ADD_CUSTOM_COMMAND(TARGET model_viewer POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_CURRENT_SOURCE_DIR}/images
                       ${CMAKE_CURRENT_SOURCE_DIR}/../build/images
                  )


if(WIN32)
  set(CPACK_GENERATOR NSIS)
else()
  set(CPACK_GENERATOR ZIP)
endif()

install(
        TARGETS Model
        ARCHIVE
        DESTINATION lib
        COMPONENT libraries
)

install(
        TARGETS
        ARCHIVE
        DESTINATION lib
        COMPONENT libraries
)

install(
        TARGETS ${VTK_LIBRARIES}/vtkChartsCore-8.2
        ARCHIVE
        DESTINATION lib
        COMPONENT libraries
)

install(
        TARGETS model_viewer
        RUNTIME
        DESTINATION bin
        COMPONENT applications
)

install(
        FILES  ../model/include/Model.hpp; ../model/include/Cell.hpp; ../model/include/Matrix.hpp; ../model/include/Vectors.h; ../model/include/Material.h; include/mainwindow.h; include/edit_light.h; include/filters.h; include/vtklight_withname.h
        DESTINATION include
        COMPONENT headers
)

# CPACK macros below here

set (CPACK_PACKAGE_NAME "Model Viewer")
set (CPACK_PACKAGE_VENDOR "Group 33")
set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "Model Viewer Installation")
set (CPACK_PACKAGE_VERSION "1.0.0")
set (CPACK_PACKAGE_VERSION_MAJOR "1")
set (CPACK_PACKAGE_VERSION_MINOR "0")
set (CPACK_PACKAGE_VERSION_PATCH "0")
set (CPACK_PACKAGE_INSTALL_DIRECTORY "Model Viewer")

# Define components and their display names
set (CPACK_COMPONENTS_ALL applications libraries headers)
set (CPACK_COMPONENT_APPLICATIONS_DISPLAY_NAME "Applications")
set (CPACK_COMPONENT_LIBRARIES_DISPLAY_NAME "Libraries")
set (CPACK_COMPONENT_HEADERS_DISPLAY_NAME "Headers")

# Human readable component descriptions
set (CPACK_COMPONENT_APPLICATIONS_DESCRIPTION "An extremely useful application that makes use of Model Viewer libraries")
set (CPACK_COMPONENT_LIBRARIES_DESCRIPTION "Static libraries used to build programs with Model Viewer")
set (CPACK_COMPONENT_HEADERS_DESCRIPTION "C/C++ header files for use with Model Viewer")

# Define dependencies between components
set (CPACK_COMPONENT_HEADERS_DEPENDS libraries)

# Define groups
set(CPACK_COMPONENT_APPLICATIONS_GROUP "Runtime")
set(CPACK_COMPONENT_LIBRARIES_GROUP "Runtime")
set(CPACK_COMPONENT_HEADERS_GROUP "Development")

#set(CPACK_COMPONENT_GROUP_DEVELOPMENT_DESCRIPTION "All of the tools you'll ever need to develop software")

# Define NSIS installation types
set(CPACK_ALL_INSTALL_TYPES Full Developer)
set(CPACK_COMPONENT_APPLICATIONS_INSTALL_TYPES Full)
set(CPACK_COMPONENT_LIBRARIES_INSTALL_TYPES Developer Full)
set(CPACK_COMPONENT_HEADERS_INSTALL_TYPES Developer Full)

# Must be after the last CPACK macros
include(CPack)
