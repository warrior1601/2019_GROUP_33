#ifndef EDIT_LIGHT_H
#define EDIT_LIGHT_H

#include <QDialog>

#include <vtkLight.h>
#include <vtkSmartPointer.h>
#include "vtklight_withname.h"
#include <vtkGenericOpenGLRenderWindow.h>


namespace Ui {
class Edit_Light;
}

class Edit_Light : public QDialog
{
Q_OBJECT
public:
    explicit Edit_Light(QWidget *parent = nullptr);
    ~Edit_Light();
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
    vtkSmartPointer<vtkLight> light = vtkSmartPointer<vtkLight>::New();
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow =vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    vtkLight_WithName l;
};

#endif // EDIT_LIGHT_H
