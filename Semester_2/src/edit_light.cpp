
#include <QMessageBox>
#include <QTextStream>
#include <QFile>
#include <QFileDialog>
#include <vtkSTLReader.h>
#include <QString>
#include <QColorDialog>
#include <QColor>
#include <QDebug>
#include <QDialog>


#include <vtkLight.h>
#include <vtkRenderWindow.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

#include "edit_light.h"
#include "ui_edit_light.h"
#include "vtklight_withname.h"




Edit_Light::Edit_Light(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Edit_Light)
{
    ui->setupUi(this);
    // need to link the ok button to the Dialog's "accept" slot
       connect( ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept );

    // need to link the cancel button to the Dialog's "reject" slot
       connect( ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject );

}

Edit_Light::~Edit_Light()
{
    delete ui;
}

void Edit_Light::open(vtkLight_WithName &Passed, vtkSmartPointer<vtkGenericOpenGLRenderWindow> &PassedWindow)
{
        l = Passed;
        renderWindow = PassedWindow;
        ui->LightName->setText(l.GetName());
        ui->Light_Cone_Angle->setValue(int (l.light->GetConeAngle()));
        ui->Light_Intensity->setValue(int ((l.light->GetIntensity()) * 100) );

        double * Origin = l.light->GetPosition();
        ui->Light_X_Coordinate_Origin->setValue(int (Origin[0]) );
        ui->Light_Y_Coordinate_Origin->setValue(int (Origin[1]) );
        ui->Light_Z_Coordinate_Origin->setValue(int (Origin[2]) );

        double * Focal_Point = l.light->GetFocalPoint();
        ui->Light_X_Coordinate_Focal_Point->setValue(int (Focal_Point[0]) );
        ui->Light_Y_Coordinate_Focal_Point->setValue(int (Focal_Point[1]) );
        ui->Light_Z_Coordinate_Focal_Point->setValue(int (Focal_Point[2]) );
}

void Edit_Light::on_Light_Cone_Angle_valueChanged(int LightConeAngle)
{
    //qDebug() << "GET :" << (l.light->GetConeAngle());
    //qDebug() << "SET :" << (double (LightConeAngle));
    l.light->SetConeAngle(double (LightConeAngle));
    renderWindow->Render();
}

void Edit_Light::on_Light_Intensity_valueChanged(int value)
{
    double LightIntensity = double (value) / 100.00;
    l.light->SetIntensity( LightIntensity );
    //qDebug() << "GET :" << (l.light->GetIntensity());
    //qDebug() << "SET :" << LightIntensity;
    renderWindow->Render();

}

void Edit_Light::on_Change_Light_Color_released()
{
    QColor Color = QColorDialog::getColor(Qt::white,this,"Choose Light Filter");
        if(Color.isValid())
        {
            double red = Color.redF();
            double green = Color.greenF();
            double blue = Color.blueF();
            l.light->SetDiffuseColor( red, green, blue );
        }
        //rerenders the window after the color change
        renderWindow->Render();

}

void Edit_Light::on_Light_X_Coordinate_Origin_valueChanged(int arg1)
{
    double* LightOrigin = l.light->GetPosition();
    l.light->SetPosition(double (arg1),LightOrigin[1],LightOrigin[2]);
    renderWindow->Render();
}

void Edit_Light::on_Light_Y_Coordinate_Origin_valueChanged(int arg1)
{
    double* LightOrigin = l.light->GetPosition();
    l.light->SetPosition(LightOrigin[0],double (arg1),LightOrigin[2]);
    renderWindow->Render();
}

void Edit_Light::on_Light_Z_Coordinate_Origin_valueChanged(int arg1)
{
    double* LightOrigin = l.light->GetPosition();
    l.light->SetPosition(LightOrigin[0],LightOrigin[1],double (arg1));
    renderWindow->Render();
}

void Edit_Light::on_Light_X_Coordinate_Focal_Point_valueChanged(int arg1)
{
    double* LightFocus = l.light->GetFocalPoint();
    l.light->SetFocalPoint(double (arg1),LightFocus[1],LightFocus[2]);
    renderWindow->Render();
}

void Edit_Light::on_Light_Y_Coordinate_Focal_Point_valueChanged(int arg1)
{
    double* LightFocus = l.light->GetFocalPoint();
    l.light->SetFocalPoint(LightFocus[0],double (arg1),LightFocus[2]);
    renderWindow->Render();
}

void Edit_Light::on_Light_Z_Coordinate_Focal_Point_valueChanged(int arg1)
{
    double* LightFocus = l.light->GetFocalPoint();
    l.light->SetFocalPoint(LightFocus[0],LightFocus[1],double (arg1));
    renderWindow->Render();
}

void Edit_Light::on_LightName_textEdited(const QString &arg1)
{
   l.SetName(arg1);
   ui->Test->setText(l.GetName());
   renderWindow->Render();
}

void Edit_Light::on_Light_Switch_toggled(bool checked)
{
    if (checked == true)
    {
        l.light->SwitchOn();
    }
    else
    {
        l.light->SwitchOff();
    }
    renderWindow->Render();
}
