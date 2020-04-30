//-----MainWindow.h--------------//
// Computing Project
// Created by Jedidiah Paterson on 02/22/2020.
// Copyright @ 2020 Jedidiah Paterson. All rights reserved.

/** @file file contains the function that allow a model to be loaded and manipulated.
 * Currently suppoorting .MOD/.TXT/.STL files only.
 * @author Jedidiah Paterson
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
// Header files from QT
#include <QColorDialog>
#include <QDebug>           // TROUBLESHOOTING ONLY //
#include <QFileDialog>
#include <QInputDialog>
#include <QMainWindow>
#include <QMessageBox>
// Header files from vtk
#include <vtkAxesActor.h>
#include <vtkCubeAxesActor.h>
#include <vtkCamera.h>
#include <vtkCellArray.h>
#include <vtkCellType.h>
#include <vtkDelaunay2D.h>
#include <vtkDistanceRepresentation.h>
#include <vtkDistanceWidget.h>
#include <vtkHexahedron.h>
#include <vtkInformation.h>
#include <vtkNamedColors.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkProperty.h>
#include <vtkPyramid.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSTLWriter.h>
#include <vtkTetra.h>
#include <vtkTransform.h>
#include <vtkTriangle.h>
#include <vtkUnstructuredGrid.h>
// C++ Header files
#include <array>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
// Projct Header files
#include "Cell.hpp"
#include "edit_light.h"
#include "filters.h"
#include "Material.h"
#include "Matrix.hpp"
#include "Model.hpp"
#include "Vectors.h"
#include "vtklight_withname.h"

namespace Ui {
class MainWindow;
}
/** @class MainWindow MainWindow.h "mainwindow.h"
 *  @brief The main window class contains the display window for the model as well as several buttons that allow the user to
 *  manipulate the model that they are viewing.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /** @brief Blank constructor (empty)
     */
    explicit MainWindow(QWidget *parent = nullptr);

    /** @brief Blank destructor (empty)
     */
    ~MainWindow();

private slots:
    /** @brief Using the QT QColorDialog this function sets the color of the model
     */
    void on_Change_Object_Color_released();
    /** @brief This function creates a light adds it to the sceene as well as adding it to the combo box to enable editing
     */
    void on_Add_Light_released();
    /** @brief This enable the user to edit the name of the light
     */
    void on_Select_Light_editTextChanged(const QString &text);
    /** @brief Using the QT QColorDialog this function sets the color of the background
     */
    void on_Change_Back_Ground_Color_released();
    /** @brief on_Reset_Camera_released
     */
    void on_Reset_Camera_released();
    /** @brief This function opens the Filters dialog box that enable filters to be applied to the model.
     * Only one of these dialog boxes can be open at a time, reverting all filters when the dialog box is closed
     */
    void on_Apply_Filters_released();
    /** @brief This rotates the camera position allong the X-Axis
     */
    void on_X_Camera_Pos_valueChanged(int value);
    /** @brief This rotates the camera position allong the Y-Axis
     */
    void on_Y_Camera_Pos_valueChanged(int value);
    /** @brief This rotates the camera position allong the Z-Axis
     */
    void on_Z_Camera_Pos_valueChanged(int value);
    /** @brief This vertically shifts the camera and its focal point
     */
    void on_Vertical_Shift_valueChanged(int arg1);
    /** @brief This Horizontally shifts the camera and its focal point
     */
    void on_Horizontal_Shift_valueChanged(int arg1);
    /** @brief Using the QT QFileDialog this opens a window to select a file to open. Currently only supporting .MOD/.TXT/.STL files
     *  When opening a file that is NOT an .STL file the program automatically saves it as a .STL file to comply with company policy of file conversion.
     */
    void on_LoadModelButton_released();
    /** @brief This function is not yet implemented
     */
    void on_SaveModelButton_released();
    /** @brief Using the QT QFileDialog this function saves the list of lights that are in the combo box and all of their settings in a text file
     */
    void on_SaveLightsButton_released();
    /** @brief Using the QT QFileDialog this function loads a text file and applies the lights to the scene
     */
    void on_LoadLightsButton_released();
    /** @brief This function opens a dialog box that allows the user to edit the lights properties. The light that will be edited will be the light
     * that is currently in the combo box. The name of the light can be edited directly from the combo box
     */
    void on_Edit_Light_clicked();
    /** @brief This function deletes the light that is currently selected in the combo box. Future upgrade will move the deleted light into a staging area where it
     * will be able to be recalled
     */
    void on_Delete_Light_released();
    /** @brief This function adds the measuring ruler tool to the window
     */
    void on_AddRulerPushButton_released();
    /** @brief This function removes the measuring ruler tool from the window. Needs to be fix becuase it does not return the window to mouse interaction properly
     */
    void on_RemoveRulerPushButton_released();
    /** @brief This functions displays the Weight, Volume, Center of Gavity, Overal Dimensions, and Density of the model.
     * Currently this only applies to .MOD/.TXT files
     */
    void on_Model_Statistics_released();
    /** @brief This function will highlight a selected cell disabling another cell from being selected
     */
    void on_Tetra_Highlight_stateChanged(int state);
    /** @brief This function will highlight a selected cell disabling another cell from being selected
     */
    void on_Pyramid_Highlight_stateChanged(int state);
    /** @brief This function will highlight a selected cell disabling another cell from being selected
     */
    void on_Hexahedron_Highlight_stateChanged(int state);
    /** @brief This function allows the user to selected the colour for a cell to highlight, default setting is Black
     */
    void on_Highlight_released();
    /** @brief This funcion will display the highlights cells Statistics. Volume, weight, density, loacion, and colour
     */
    void on_Cell_Statistics_released();
    /** @brief This funcion will display the length,width and hight of the object
     */
    void on_showAxes_released();
    /** @brief This funcion will remove the length,width and hight of the object
     */
    void on_deleteshowAxes_released();

private:
//-------Private Functions--------//
    /** @brief This function allows for the user to input text
     */
    QString InputQString();
    /** @brief The function is used by on_actionLoad_Lights_triggered() to set the light data
     */
    void SetLightData(double *Data, std::string currentLine);
    /** @brief Initializes the Camera light
     */
    void Init_CameraLight();
//-------Private Members---------//
    Ui::MainWindow *ui; ///< @brief This is the User Interface
    bool LoadedFileType = true; ///< @brief This is used to track what type of file is loaded either .STL = true or .MOD/.TXT = false
    bool FilterWindowOpenStatus = false; ///< @brief This tracks if the filter window is open or closed. If true a window is open and the user can not open another window
    Edit_Light *Edit_LightDialog; ///< @brief This is a pointer to the Edit light dialog box
    Filters *filters; ///< @brief This is a pointer to the filters dialog box

    double Highlight_red = 0; ///< @brief This stores the red value that user has selected for highlighting cells
    double Highlight_green = 0; ///< @brief This stores the green value that user has selected for highlighting cells
    double Highlight_blue = 0; ///< @brief This stores the blue value that user has selected for highlighting cells

    Model ModelOne; ///< @brief This sotres a model when it is loaded

    std::vector<vtkLight_WithName> ListOfLights; ///< @brief This is a list of the vtkLights_withname
    std::vector<std::array<double, 3>> pointCoordinates; ///< @brief This list stores the points used in a loaded model
    //Having a list of actors separately allows for ensuring the correct actor is modified when highlighting a cell type
    std::vector< vtkSmartPointer<vtkActor> > ListOfActors_tetra; ///< @brief This is a list of all the actors present on tetrahedrons
    std::vector< vtkSmartPointer<vtkActor> > ListOfActors_pyramid; ///< @brief This is a list of all the actors present on pyramids
    std::vector< vtkSmartPointer<vtkActor> > ListOfActors_hexahedron; ///< @brief This is a list of all the acotrs present on hexahedrons

    double Temp_Tetra_color_red; ///< @brief This stores the orginal red value for a highlighted cell
    double Temp_Tetra_color_green; ///< @brief This stores the orginal green value for a highlighted cell
    double Temp_Tetra_color_blue; ///< @brief This stores the orginal blue value for a highlighted cell

    double Temp_Pyramid_color_red; ///< @brief This stores the orginal red value for a highlighted cell
    double Temp_Pyramid_color_green; ///< @brief This stores the orginal green value for a highlighted cell
    double Temp_Pyramid_color_blue; ///< @brief This stores the orginal blue value for a highlighted cell

    double Temp_Hexahedron_color_red; ///< @brief This stores the orginal red value for a highlighted cell
    double Temp_Hexahedron_color_green; ///< @brief This stores the orginal green value for a highlighted cell
    double Temp_Hexahedron_color_blue; ///< @brief This stores the orginal blue value for a highlighted cell

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New(); ///< @brief For more information on vtk Classes visit https://vtk.org/doc/nightly/html/annotated.html
    vtkSmartPointer<vtkNamedColors> colors = vtkSmartPointer<vtkNamedColors>::New(); ///< @brief For more information on vtk Classes visit https://vtk.org/doc/nightly/html/annotated.html

    std::vector<vtkSmartPointer<vtkDataSetMapper>> ListOfMappers; ///< @brief This is a list of all the mappers in the rendering window
    vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New(); ///< @brief For more information on vtk Classes visit https://vtk.org/doc/nightly/html/annotated.html

    vtkSmartPointer<vtkSTLReader> reader = vtkSmartPointer<vtkSTLReader>::New(); ///< @brief For more information on vtk Classes visit https://vtk.org/doc/nightly/html/annotated.html
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New(); ///< @brief For more information on vtk Classes visit https://vtk.org/doc/nightly/html/annotated.html
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New(); ///< @brief For more information on vtk Classes visit https://vtk.org/doc/nightly/html/annotated.html

    std::vector<vtkSmartPointer<vtkUnstructuredGrid>> ListOfUgs; ///< @brief This is a list of all the UnstructoredGrids
    vtkSmartPointer<vtkUnstructuredGrid> ug = vtkSmartPointer<vtkUnstructuredGrid>::New(); ///< @brief For more information on vtk Classes visit https://vtk.org/doc/nightly/html/annotated.html

    std::vector<vtkSmartPointer<vtkTetra>> ListOfTetras; ///< @brief This is a list of all the Tetras loaded in a model
    std::vector<vtkSmartPointer<vtkPyramid>> ListOfPyramids; ///< @brief This is a list of all the Pyramids loaded in a model
    std::vector<vtkSmartPointer<vtkHexahedron>> ListOfHexs; ///< @brief This is a list of all the Hexahedrons loaded in a model

    std::vector<vtkSmartPointer<vtkTriangle>> ListOfTriangles; ///< @brief This is a list of all the vtkTriangles. This is important to have for the conversion process from .MOD/.TXT to .STL file type
    vtkSmartPointer<vtkCellArray> TriangleArray = vtkSmartPointer<vtkCellArray>::New(); ///< @brief For more information on vtk Classes visit https://vtk.org/doc/nightly/html/annotated.html

    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New(); ///< @brief For more information on vtk Classes visit https://vtk.org/doc/nightly/html/annotated.html
    vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New(); ///< @brief This smart point stores the data so it can be saved. For more information on vtk Classes visit https://vtk.org/doc/nightly/html/annotated.html

    vtkSmartPointer<vtkSTLWriter> stlWriter = vtkSmartPointer<vtkSTLWriter>::New(); ///< @brief Allows for saving a STL file. For more information on vtk Classes visit https://vtk.org/doc/nightly/html/annotated.html

    vtkSmartPointer<vtkAxesActor> axes = vtkSmartPointer<vtkAxesActor>::New(); ///< @brief For more information on vtk Classes visit https://vtk.org/doc/nightly/html/annotated.html
    vtkSmartPointer<vtkOrientationMarkerWidget> orientationWidget = vtkSmartPointer<vtkOrientationMarkerWidget>::New(); ///< @brief For more information on vtk Classes visit https://vtk.org/doc/nightly/html/annotated.html

    vtkSmartPointer<vtkDistanceWidget> distanceWidget = vtkSmartPointer<vtkDistanceWidget>::New(); ///< @brief For more information on vtk Classes visit https://vtk.org/doc/nightly/html/annotated.html
    vtkSmartPointer< vtkTransform> transform = vtkSmartPointer< vtkTransform>::New(); ///< @brief For more information on vtk Classes visit https://vtk.org/doc/nightly/html/annotated.html

    vtkSmartPointer<vtkCubeAxesActor> AxesActor = vtkSmartPointer<vtkCubeAxesActor>::New(); ////< @brief For more information on vtk Classes visit https://vtk.org/doc/nightly/html/annotated.html
};

#endif // MAINWINDOW_H
