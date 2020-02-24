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

#include <vtkNamedColors.h>

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

private:
    Ui::MainWindow *ui;
// These pointers are for the Secondary windows that control funtions
// That allows the user to interact with the image

    Edit_Light *Edit_LightDialog;
    Filters *filters;
// QT Function for editing/Inputng a QString

    QString InputQString();
// This is a light of all active lights

    std::vector<vtkLight_WithName> ListOfLights;
    vtkSmartPointer<vtkNamedColors> colors = vtkSmartPointer<vtkNamedColors>::New();
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    vtkSmartPointer<vtkSTLReader> reader = vtkSmartPointer<vtkSTLReader>::New();
    vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
};

#endif // MAINWINDOW_H
