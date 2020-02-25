//--------------------edit_light.h--------------------//


// edit_light.h
// WorkSheet 6 Computing Project
// Edited By Jedidiah Paterson on 02/22/2020.
// This file contains a list of functions and variable that are connected
// To the buttons on the edit_light.ui window. These function all the object
// That is presentedon MainWindow.ui to be manipluated. This file is
// Desgined to allow for future updates and addtions to filtering functions

#ifndef EDIT_LIGHT_H
#define EDIT_LIGHT_H

#include <QDialog>

#include <vtkGenericOpenGLRenderWindow.h>

#include "vtklight_withname.h"

namespace Ui {
class Edit_Light;
}

class Edit_Light : public QDialog
{
Q_OBJECT
public:
// Constructor

    explicit Edit_Light(QWidget *parent = nullptr);
// Destructor

    ~Edit_Light();
// Overloaded function found in other files. Without this function editlight buttons
// Would not be able to Render() the MainWindow Display_Window when they are activated
// This fuction is called in MainWindow.cpp

    void open(vtkLight_WithName &l, vtkSmartPointer<vtkGenericOpenGLRenderWindow> &PassedWindow);

private slots:

    void on_Light_Cone_Angle_valueChanged(int value);
    void on_Light_Intensity_valueChanged(int value);
    void on_Change_Light_Color_released();
    void on_Light_X_Coordinate_Origin_valueChanged(int arg1);
    void on_Light_Y_Coordinate_Origin_valueChanged(int arg1);
    void on_Light_Z_Coordinate_Origin_valueChanged(int arg1);
    void on_Light_X_Coordinate_Focal_Point_valueChanged(int arg1);
    void on_Light_Y_Coordinate_Focal_Point_valueChanged(int arg1);
    void on_Light_Z_Coordinate_Focal_Point_valueChanged(int arg1);
    void on_LightName_textEdited(const QString &arg1);
    void on_Light_Switch_toggled(bool checked);


private:
    Ui::Edit_Light *ui;
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow =vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    vtkLight_WithName light_Local;

};

#endif // EDIT_LIGHT_H
