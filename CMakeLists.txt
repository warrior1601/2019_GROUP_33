# This CMakeList file can, depending upon which booleans are set, create the Model
# and Model_Viewer libararies; create the Model library test code and CTests; create the
# Observer executable; and create the installer
cmake_minimum_required( VERSION 3.9.2 )

# The name of the project and its curent version
project( Observer VERSION 1.2.1)

# Boolean to adjust want you want to build
set( BUILD_MODEL_TEST_CODE 	FALSE )
set( BUILD_OBSERVER 		FALSE )
set( BUILD_INSTALLERS		TRUE )

# All booleans require the model library
if ( ${BUILD_MODEL_TEST_CODE} )
	add_subdirectory ( model )

endif()

# Observer and installer require the model_viewer library and Observer executable
if ( ${BUILD_OBSERVER} OR ${BUILD_INSTALLERS} )
	add_subdirectory ( model_viewer )
endif()

# Installer code
if( ${BUILD_INSTALLERS} )
		if( WIN32 )
			set( CPACK_GENERATOR NSIS )
		else()
		 	set(CPACK_GENERATOR ZIP)
		endif()

		include (InstallRequiredSystemLibraries)

		install( TARGETS Observer
			 RUNTIME
			 DESTINATION bin
			 COMPONENT applications
			 )

		install(TARGETS Observer_Model_Library
				ARCHIVE
				DESTINATION lib/static
				COMPONENT libraries
				)

		install(FILES  C:/Users/Jedidiah/2019_GROUP_33/model_viewer/images/Observer.stl
				DESTINATION bin
				COMPONENT libraries
				)

		install(FILES  C:/Users/Jedidiah/2019_GROUP_33/example_models/Model_One.txt
			       C:/Users/Jedidiah/2019_GROUP_33/example_models/Model_One.txt
			       C:/Users/Jedidiah/2019_GROUP_33/example_models/a-10-thunderbolt-mk2.stl
                               C:/Users/Jedidiah/2019_GROUP_33/example_models/airbus_a400m.stl
                               C:/Users/Jedidiah/2019_GROUP_33/example_models/bawar_plane.stl
                               C:/Users/Jedidiah/2019_GROUP_33/example_models/cube.stl
                               C:/Users/Jedidiah/2019_GROUP_33/example_models/sphere.stl
			       DESTINATION example_models
			       )

		install(FILES	C:/Qt/5.12.5/msvc2017_64/bin/Qt5Cored.dll
				C:/Qt/5.12.5/msvc2017_64/bin/Qt5Guid.dll
				C:/Qt/5.12.5/msvc2017_64/bin/Qt5Widgetsd.dll
				C:/VTK-8.2.0/build/bin/Debug/vtkRenderingGL2PSOpenGL2-8.2.dll
				C:/VTK-8.2.0/build/bin/Debug/QVTKWidgetPlugin.dll
				C:/VTK-8.2.0/build/bin/Debug/vtkCommonColor-8.2.dll
				C:/VTK-8.2.0/build/bin/Debug/vtkCommonComputationalGeometry-8.2.dll
				C:/VTK-8.2.0/build/bin/Debug/vtkCommonCore-8.2.dll
				C:/VTK-8.2.0/build/bin/Debug/vtkCommonDataModel-8.2.dll
				C:/VTK-8.2.0/build/bin/Debug/vtkCommonExecutionModel-8.2.dll
				C:/VTK-8.2.0/build/bin/Debug/vtkCommonMath-8.2.dll
				C:/VTK-8.2.0/build/bin/Debug/vtkCommonMisc-8.2.dll
				C:/VTK-8.2.0/build/bin/Debug/vtkCommonSystem-8.2.dll
				C:/VTK-8.2.0/build/bin/Debug/vtkCommonTransforms-8.2.dll
				C:/VTK-8.2.0/build/bin/Debug/vtkDICOMParser-8.2.dll
				C:/VTK-8.2.0/build/bin/Debug/vtkdoubleconversion-8.2.dll
				C:/VTK-8.2.0/build/bin/Debug/vtkFiltersCore-8.2.dll
				C:/VTK-8.2.0/build/bin/Debug/vtkFiltersExtraction-8.2.dll
				C:/VTK-8.2.0/build/bin/Debug/vtkFiltersGeneral-8.2.dll
				C:/VTK-8.2.0/build/bin/Debug/vtkFiltersGeometry-8.2.dll
				C:/VTK-8.2.0/build/bin/Debug/vtkFiltersHybrid-8.2.dll
				C:/VTK-8.2.0/build/bin/Debug/vtkFiltersModeling-8.2.dll
				C:/VTK-8.2.0/build/bin/Debug/vtkFiltersSources-8.2.dll
				C:/VTK-8.2.0/build/bin/Debug/vtkFiltersStatistics-8.2.dll
				C:/VTK-8.2.0/build/bin/Debug/vtkfreetype-8.2.dll
				C:/VTK-8.2.0/build/bin/Debug/vtkgl2ps-8.2.dll
				C:/VTK-8.2.0/build/bin/Debug/vtkglew-8.2.dll
				C:/VTK-8.2.0/build/bin/Debug/vtkGUISupportQt-8.2.dll
				C:/VTK-8.2.0/build/bin/Debug/vtkImagingColor-8.2.dll
				C:/VTK-8.2.0/build/bin/Debug/vtkImagingCore-8.2.dll
				C:/VTK-8.2.0/build/bin/Debug/vtkImagingFourier-8.2.dll
				C:/VTK-8.2.0/build/bin/Debug/vtkImagingGeneral-8.2.dll
				C:/VTK-8.2.0/build/bin/Debug/vtkImagingHybrid-8.2.dll
				C:/VTK-8.2.0/build/bin/Debug/vtkImagingSources-8.2.dll
				C:/VTK-8.2.0/build/bin/Debug/vtkInteractionStyle-8.2.dll
				C:/VTK-8.2.0/build/bin/Debug/vtkInteractionWidgets-8.2.dll
				C:/VTK-8.2.0/build/bin/Debug/vtkIOCore-8.2.dll
				C:/VTK-8.2.0/build/bin/Debug/vtkIOGeometry-8.2.dll
				C:/VTK-8.2.0/build/bin/Debug/vtkIOImage-8.2.dll
				C:/VTK-8.2.0/build/bin/Debug/vtkjpeg-8.2.dll
				C:/VTK-8.2.0/build/bin/Debug/vtklz4-8.2.dll
				C:/VTK-8.2.0/build/bin/Debug/vtklzma-8.2.dll
				C:/VTK-8.2.0/build/bin/Debug/vtkmetaio-8.2.dll
				C:/VTK-8.2.0/build/bin/Debug/vtkpng-8.2.dll
				C:/VTK-8.2.0/build/bin/Debug/vtkRenderingAnnotation-8.2.dll
				C:/VTK-8.2.0/build/bin/Debug/vtkRenderingCore-8.2.dll
				C:/VTK-8.2.0/build/bin/Debug/vtkRenderingFreeType-8.2.dll
				C:/VTK-8.2.0/build/bin/Debug/vtkRenderingGL2PSOpenGL2-8.2.dll
				C:/VTK-8.2.0/build/bin/Debug/vtkRenderingOpenGL2-8.2.dll
				C:/VTK-8.2.0/build/bin/Debug/vtksys-8.2.dll
				C:/VTK-8.2.0/build/bin/Debug/vtktiff-8.2.dll
				C:/VTK-8.2.0/build/bin/Debug/vtkzlib-8.2.dll
				DESTINATION bin
				COMPONENT libraries
				)
    
		install(FILES   model/include/Model.hpp;
				model/include/Cell.hpp;
				model/include/Matrix.hpp;
				model/include/Vectors.h;
				model/include/Material.h;
				model_viewer/include/mainwindow.h;
				model_viewer/include/edit_light.h;
				model_viewer/include/filters.h;
				model_viewer/include/vtklight_withname.h
		 		DESTINATION include
		 		COMPONENT headers
				)

		# CPACK macros below here
		set (CPACK_PACKAGE_NAME "Observer")
		set (CPACK_NSIS_MUI_ICON ${CMAKE_CURRENT_SOURCE_DIR}/model_viewer/images/ObserverLogo.ico)
		set (CPACK_NSIS_MUI_UNIICON ${CMAKE_CURRENT_SOURCE_DIR}/model_viewer/images/ObserverLogo.ico)
		set (CPACK_NSIS_INSTALLED_ICON_NAME ${CMAKE_CURRENT_SOURCE_DIR}/model_viewer/images/ObserverLogo.ico)
		set (CPACK_PACKAGE_VENDOR "The Space Explorers")
		set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "Observer Installation")
		set (CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
		set (CPACK_PACKAGE_INSTALL_DIRECTORY "Observer")
		set (CPACK_CREATE_DESKTOP_LINKS ON)
		set (CPACK_PACKAGE_EXECUTABLES "Observer" "Observer")
		set (CPACK_CREATE_DESKTOP_LINKS "Observer" "Observer")
		set (CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt)

		# Define components and their display names
		set (CPACK_COMPONENTS_ALL applications libraries headers)
		set (CPACK_COMPONENT_APPLICATIONS_DISPLAY_NAME "Applications")
		set (CPACK_COMPONENT_LIBRARIES_DISPLAY_NAME "Libraries")
		set (CPACK_COMPONENT_HEADERS_DISPLAY_NAME "Headers")

		# Define dependencies between components
		set (CPACK_COMPONENT_HEADERS_DEPENDS libraries)

		# Define groups
		set(CPACK_COMPONENT_APPLICATIONS_GROUP "Runtime")
		set(CPACK_COMPONENT_LIBRARIES_GROUP "Runtime")
		set(CPACK_COMPONENT_HEADERS_GROUP "Development")

		# Define NSIS installation types
		set(CPACK_ALL_INSTALL_TYPES Full Developer)
		set(CPACK_COMPONENT_APPLICATIONS_INSTALL_TYPES Full)
		set(CPACK_COMPONENT_LIBRARIES_INSTALL_TYPES Developer Full)
		set(CPACK_COMPONENT_HEADERS_INSTALL_TYPES Developer Full)

	# Must be after the last CPACK macros
	include(CPack)

endif()