//-----MainWindow.h--------------//
// Computing Project
// Created by Jedidiah Paterson on 02/22/2020.
// Copyright @ 2020 Jedidiah Paterson. All rights reserved.

/** @file file contains the function that allow a model to be loaded and manipulated.
 * Currently suppoorting .MOD/.TXT/.STL files only.
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

signals:
    // All other SIGNALS and SLOTS are created with the "QT helping tools" from the ui page
    /** @brief This displays a message on the tool bar when the user interacts with the ui,
     * letting them know that there interaction has been initiated
     */
    void statusUpdateMessage( const QString & message, int timeout );

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
     *  @return The return status is used at start up. If no file is selected to open the program will terminate
     */
    int on_actionOpen_triggered();
    /** @brief This function is not yet implemented
     */
    void on_actionSave_triggered();
    /** @brief Using the QT QFileDialog this function saves the list of lights that are in the combo box and all of their settings in a text file
     */
    void on_actionSave_Lights_triggered();
    /** @brief Using the QT QFileDialog this function loads a text file and applies the lights to the scene
     */
    void on_actionLoad_Lights_triggered();
    /**
     * @brief This function opens a dialog box that allows the user to edit the lights properties. The light that will be edited will be the light
     * that is currently in the combo box. The name of the light can be edited directly from the combo box
     */
    void on_Edit_Light_clicked();
    /** @brief This function deletes the light that is currently selected in the combo box. Future upgrade will move the deleted light into a staging area where it
     * will be able to be recalled
     */
    void on_Delete_Light_released();
    /** @brief This function aplies the orintation widget to the cube
     */
    void on_actioncube_triggered();
    /** @brief This function aplies the orintation widget to the he11
     */
    void on_actionhelicopter_triggered();
    /** @brief This function aplies the orintation widget to the bawa plane
     */
    void on_actionplane_triggered();
    /** @brief This function aplies the orintation widget to the sphere
     */
    void on_actionsphere_triggered();
    /** @brief This function aplies the orintation widget to the a-10 thunderbolt
     */
    void on_actionThunderbolt_triggered();
    /** @brief This function aplies the orintation widget to the airbus
     */
    void on_actionairbus_triggered();
    /** @brief This function adds the measuring ruler tool to the window
     */
    void on_actionRuler_triggered();
    /** @brief This function removes the measuring ruler tool from the window. Needs to be fix becuase it does not return the window to mouse interaction properly
     */
    void on_actionRemove_Ruler_triggered();

private:
//-------Private Functions--------//
    /** @brief This function allows for the user to input text
     */
    QString InputQString();
    /** @brief The function is used by on_actionLoad_Lights_triggered() to set the light data
     */
    void SetLightData(double *Data, std::string currentLine);
//-------Private Members---------//
    Ui::MainWindow *ui; ///< This is the User Interface
    bool LoadedFileType = true; ///< This is used to track what type of file is loaded either .STL or .MOD/.TXT
    bool FilterWindowOpenStatus = false; ///< This tracks if the filter window is open or closed. If true a window is open and the user can not open another window
    Edit_Light *Edit_LightDialog; ///< This is a pointer to the Edit light dialog box
    Filters *filters; ///< This is a pointer to the filters dialog box

    std::vector<vtkLight_WithName> ListOfLights; ///< This is a list of the vtkLights_withname
    std::vector<std::array<double, 3>> pointCoordinates; ///<This list stores the points used in a loaded model

    std::vector<vtkSmartPointer<vtkActor>> ListOfActors; ///< This is a list of all the actors present
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkNamedColors> colors = vtkSmartPointer<vtkNamedColors>::New();

    std::vector<vtkSmartPointer<vtkDataSetMapper>> ListOfMappers; ///< This is a list of all the mappers in the rendering window
    vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();

    vtkSmartPointer<vtkSTLReader> reader = vtkSmartPointer<vtkSTLReader>::New();
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    std::vector<vtkSmartPointer<vtkRenderer>> ListOfRenderers; ///< This is a list of the Renderers
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();

    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

    std::vector<vtkSmartPointer<vtkUnstructuredGrid>> ListOfUgs; ///< This is a list of all the UnstructoredGrids
    vtkSmartPointer<vtkUnstructuredGrid> ug = vtkSmartPointer<vtkUnstructuredGrid>::New();

    std::vector<vtkSmartPointer<vtkTetra>> ListOfTetras; ///< This is a list of all the Tetras loaded in a model
    std::vector<vtkSmartPointer<vtkPyramid>> ListOfPyramids; ///< This is a list of all the Pyramids loaded in a model
    std::vector<vtkSmartPointer<vtkHexahedron>> ListOfHexs; ///< This is a list of all the Hexahedrons loaded in a model

    vtkSmartPointer<vtkCellArray> cellArray = vtkSmartPointer<vtkCellArray>::New();
    std::vector<vtkSmartPointer<vtkTriangle>> ListOfTriangles; ///< This is a list of all the vtkTriangles. This is important to have for the conversion process from .MOD/.TXT to .STL file type
    vtkSmartPointer<vtkCellArray> TriangleArray = vtkSmartPointer<vtkCellArray>::New();

    vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
    vtkSmartPointer<vtkSTLWriter> stlWriter = vtkSmartPointer<vtkSTLWriter>::New();
///----Check this put when you have time with below ----////
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    vtkSmartPointer<vtkDistanceWidget> distanceWidget = vtkSmartPointer<vtkDistanceWidget>::New();

    vtkSmartPointer<vtkAxesActor> axes = vtkSmartPointer<vtkAxesActor>::New();
    vtkSmartPointer<vtkOrientationMarkerWidget> orientationWidget = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
    vtkSmartPointer< vtkTransform> transform = vtkSmartPointer< vtkTransform>::New();
////-----Why are there two of me-----/////
    vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
};

#endif // MAINWINDOW_H
