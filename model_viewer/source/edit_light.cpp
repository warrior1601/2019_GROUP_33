//--------------------edit_light.cpp--------------------//
// edit_light.cpp
// Computing Project
// Edited By Jedidiah Paterson on 02/22/2020.
// Copyright @ 2020 Jedidiah Paterson. All right reserved.
// This File contains the implemetations of defined functions
// In the edit_light.h file


#include <QColorDialog>
#include <QDebug>           // TROUBLESHOOTING ONLY //

#include "edit_light.h"
#include "ui_edit_light.h"
#include "vtklight_withname.h"

//-------------Constructor------------//

Edit_Light::Edit_Light(QWidget *parent) : QDialog(parent), ui(new Ui::Edit_Light)
{
    ui->setupUi(this);
}
//--------------Destructor-------------//

Edit_Light::~Edit_Light()
{
    delete ui;
}
//-------Special Member Functions------//
// This function is overloaded with the filters open function
// Called in MianWindow.cpp

void Edit_Light::Open_Dialog(vtkLight_WithName &Passed, vtkSmartPointer<vtkGenericOpenGLRenderWindow> &PassedWindow)
{
    light_Local = &Passed;
    renderWindow = PassedWindow;

    ui->Light_Cone_Angle->setValue(int (light_Local->light->GetConeAngle()));
    ui->Light_Intensity->setValue(int ((light_Local->light->GetIntensity()) * 100) );
    ui->Light_Switch->setCheckState((light_Local->Check_State()));

    double * Origin = light_Local->light->GetPosition();
    ui->Light_X_Coordinate_Origin->setValue(int (Origin[0]) );
    ui->Light_Y_Coordinate_Origin->setValue(int (Origin[1]) );
    ui->Light_Z_Coordinate_Origin->setValue(int (Origin[2]) );

    double * Focal_Point = light_Local->light->GetFocalPoint();
    ui->Light_X_Coordinate_Focal_Point->setValue(int (Focal_Point[0]) );
    ui->Light_Y_Coordinate_Focal_Point->setValue(int (Focal_Point[1]) );
    ui->Light_Z_Coordinate_Focal_Point->setValue(int (Focal_Point[2]) );
}

void Edit_Light::on_Light_Cone_Angle_valueChanged(int LightConeAngle)
{
    light_Local->light->SetConeAngle(double (LightConeAngle));
    renderWindow->Render();
}

void Edit_Light::on_Light_Intensity_valueChanged(int value)
{
    double LightIntensity = double (value) / 100.00;
    light_Local->light->SetIntensity( LightIntensity );
    renderWindow->Render();
}

void Edit_Light::on_Specular_Colour_released()
{
    QColor Color = QColorDialog::getColor(Qt::white,this,"Choose Light Filter");
    if(Color.isValid())
    {
        double red = Color.redF();
        double green = Color.greenF();
        double blue = Color.blueF();
        light_Local->light->SetSpecularColor( red, green, blue );
    }
    //rerenders the window after the color change
    renderWindow->Render();
}

void Edit_Light::on_Ambient_Colour_released()
{
    QColor Color = QColorDialog::getColor(Qt::white,this,"Choose Specular Light Filter");
    if(Color.isValid())
    {
        double red = Color.redF();
        double green = Color.greenF();
        double blue = Color.blueF();
        light_Local->light->SetAmbientColor( red, green, blue );
    }
    renderWindow->Render();
}

void Edit_Light::on_Diffuse_Colour_released()
{
    QColor Color = QColorDialog::getColor(Qt::white,this,"Choose Diffuse Light Filter");
    if(Color.isValid())
    {
        double red = Color.redF();
        double green = Color.greenF();
        double blue = Color.blueF();
        light_Local->light->SetDiffuseColor( red, green, blue );
    }
    renderWindow->Render();
}

void Edit_Light::on_Light_X_Coordinate_Origin_valueChanged(int arg1)
{
    double* LightOrigin = light_Local->light->GetPosition();
    light_Local->light->SetPosition(double (arg1),LightOrigin[1],LightOrigin[2]);
    renderWindow->Render();
}

void Edit_Light::on_Light_Y_Coordinate_Origin_valueChanged(int arg1)
{
    double* LightOrigin = light_Local->light->GetPosition();
    light_Local->light->SetPosition(LightOrigin[0],double (arg1),LightOrigin[2]);
    renderWindow->Render();
}

void Edit_Light::on_Light_Z_Coordinate_Origin_valueChanged(int arg1)
{
    double* LightOrigin = light_Local->light->GetPosition();
    light_Local->light->SetPosition(LightOrigin[0],LightOrigin[1],double (arg1));
    renderWindow->Render();
}

void Edit_Light::on_Light_X_Coordinate_Focal_Point_valueChanged(int arg1)
{
    double* LightFocus = light_Local->light->GetFocalPoint();
    light_Local->light->SetFocalPoint(double (arg1),LightFocus[1],LightFocus[2]);
    renderWindow->Render();
}

void Edit_Light::on_Light_Y_Coordinate_Focal_Point_valueChanged(int arg1)
{
    double* LightFocus = light_Local->light->GetFocalPoint();
    light_Local->light->SetFocalPoint(LightFocus[0],double (arg1),LightFocus[2]);
    renderWindow->Render();
}

void Edit_Light::on_Light_Z_Coordinate_Focal_Point_valueChanged(int arg1)
{
    double* LightFocus = light_Local->light->GetFocalPoint();
    light_Local->light->SetFocalPoint(LightFocus[0],LightFocus[1],double (arg1));
    renderWindow->Render();
}

void Edit_Light::on_Light_Switch_toggled(bool checked)
{
    if (checked == true)
    {
        light_Local->light->SwitchOn();
    }
    else
    {
        light_Local->light->SwitchOff();
    }
    renderWindow->Render();
}
