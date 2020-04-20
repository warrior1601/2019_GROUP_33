//-----MainWindow.h--------------//


// MainWindow.h
// Worksheet 6 Computing Project
// Edited By Jedidiah Paterson on 02/22/2020
// Copyright @ 2020 Jedidiah Paterson. All rights reserved.
// This file contanins the functions that allow an image
// To be loaded and manipluated in MainWindow.ui viewing screen

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <vtkCellArray.h>
#include <vtkCellType.h>
#include <vtkDelaunay2D.h>
#include <vtkHexahedron.h>
#include <vtkNamedColors.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPyramid.h>
#include <vtkSTLWriter.h>
#include <vtkTetra.h>
#include <vtkUnstructuredGrid.h>


#include <vtkAxesActor.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkTransform.h>
#include <vtkRenderWindow.h>
#include <vtkCamera.h>
#include <vtkBoxWidget.h>
#include <vtkCommand.h>
#include <vtkTransform.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkBoxRepresentation.h>
#include <vtkDistanceWidget.h>
#include <vtkDistanceRepresentation.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>

#include <array>
#include <vector>

#include "edit_light.h"
#include "filters.h"
#include "vtklight_withname.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

signals:
// All other SIGNALS and SLOTS are created with the "QT helping tools from the ui page

    void statusUpdateMessage( const QString & message, int timeout );

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_Change_Object_Color_released();
    void on_Add_Light_released();
    void on_Change_Back_Ground_Color_released();
    void on_Reset_Camera_released();
    void on_Apply_Filters_released();
    void on_X_Camera_Pos_valueChanged(int value);
    void on_Y_Camera_Pos_valueChanged(int value);
    void on_Z_Camera_Pos_valueChanged(int value);
    void on_Vertical_Shift_valueChanged(int arg1);
    void on_Horizontal_Shift_valueChanged(int arg1);
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSave_Lights_triggered();
    void on_actionLoad_Lights_triggered();
    void on_Edit_Light_clicked();
    void on_Delete_Light_released();
	void on_FullScreen_clicked(bool checked);
	void on_actioncube_triggered();
	void on_actionhelicopter_triggered();
	void on_actionplane_triggered();
	void on_actionsphere_triggered();
	void on_actionThunderbolt_triggered();
	void on_actionairbus_triggered();
	void on_actionRuler_triggered();
	//void on_BoxW_clicked(bool checked);
	void on_actionRemove_Ruler_triggered();

private:
    Ui::MainWindow *ui;
// This is the file type loaded true for *.stl false for *.mod and *.txt
    bool LoadedFileType = true;
// These pointers are for the Secondary windows that control funtions
// That allows the user to interact with the image

    Edit_Light *Edit_LightDialog;
    Filters *filters;
// QT Function for editing/Inputng a QString

    QString InputQString();
    void SetLightData(double *Data, std::string currentLine);
// This is a light of all active lights

    std::vector<vtkLight_WithName> ListOfLights;
    std::vector<std::array<double, 3>> pointCoordinates;

    std::vector<vtkSmartPointer<vtkActor>> ListOfActors;
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkNamedColors> colors = vtkSmartPointer<vtkNamedColors>::New();

    std::vector<vtkSmartPointer<vtkDataSetMapper>> ListOfMappers;
    vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();

    vtkSmartPointer<vtkSTLReader> reader = vtkSmartPointer<vtkSTLReader>::New();  
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    std::vector<vtkSmartPointer<vtkRenderer>> ListOfRenderers;
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();

    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

    std::vector<vtkSmartPointer<vtkUnstructuredGrid>> ListOfUgs;
    vtkSmartPointer<vtkUnstructuredGrid> ug = vtkSmartPointer<vtkUnstructuredGrid>::New();

    std::vector<vtkSmartPointer<vtkTetra>> ListOfTetras;
    std::vector<vtkSmartPointer<vtkPyramid>> ListOfPyramids;
    std::vector<vtkSmartPointer<vtkHexahedron>> ListOfHexs;

    vtkSmartPointer<vtkCellArray> cellArray = vtkSmartPointer<vtkCellArray>::New();
    std::vector<vtkSmartPointer<vtkTriangle>> ListOfTriangles;
    vtkSmartPointer<vtkCellArray> TriangleArray = vtkSmartPointer<vtkCellArray>::New();

    vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
    vtkSmartPointer<vtkSTLWriter> stlWriter = vtkSmartPointer<vtkSTLWriter>::New();

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    vtkSmartPointer<vtkDistanceWidget> distanceWidget = vtkSmartPointer<vtkDistanceWidget>::New();







	vtkSmartPointer<vtkAxesActor> axes = vtkSmartPointer<vtkAxesActor>::New();
	vtkSmartPointer<vtkOrientationMarkerWidget> orientationWidget = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
	vtkSmartPointer< vtkTransform> transform = vtkSmartPointer< vtkTransform>::New();

	vtkSmartPointer<vtkBoxWidget> boxWidget = vtkSmartPointer<vtkBoxWidget>::New();
	vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
};

#endif // MAINWINDOW_H
