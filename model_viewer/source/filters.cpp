//-----filters.cpp--------------//

// filters.cpp
// Worksheet 6 Computing Project
// Edited By Jedidiah Paterson on 02/22/2020
// Copyright @ 2020 Jedidiah Paterson. All rights reserved.
// This file contains the defined functions that are found in filters.h
// They link the filters.ui buttons to actions by the user.

#include <QDebug>  // FOR TROUBLE SHOOTING ONLY //

#include "filters.h"
#include "ui_filters.h"

Filters::Filters(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Filters)
{
    ui->setupUi(this);
}

Filters::~Filters()
{
    delete ui;
}

void Filters::Open_Dialog(vtkSmartPointer<vtkSTLReader> &aReader,
                          vtkSmartPointer<vtkDataSetMapper> &aMapper,
                          vtkSmartPointer<vtkGenericOpenGLRenderWindow> &aWindow,
                          bool &PassedFilterWindowOpenStatus)
{
    // Sets the Local smart pointer used to render the image on th MainWindow
    // now the *->Render() can be called.
    FilterWindowOpenStatus = &PassedFilterWindowOpenStatus;
    renderWindow_Local = aWindow;
    reader_Local = aReader;
    mapper_Local = aMapper;
}

void Filters::on_Close_clicked()
{
    checked_Box_Status_Updater(0);
    *FilterWindowOpenStatus = false;
    renderWindow_Local->Render();
    this->close();
}
// This appies the shrink Filter to the image on the MainWindow
void Filters::on_Shrink_Filter_toggled(bool Shrink_Filter_Status)
{
    if(Shrink_Filter_Status == true )
    {
        // When this function is called it ensures that all other fillters are
        // No longer being applied
        checked_Box_Status_Updater(1);

        Shrink_Filter->SetInputConnection( reader_Local->GetOutputPort() );
        Shrink_Filter->SetShrinkFactor(double(ui->Scale->value())/100.00);
        Shrink_Filter->Update();
        mapper_Local->SetInputConnection( Shrink_Filter->GetOutputPort() );
    }
    else
    {
        mapper_Local->SetInputConnection( reader_Local->GetOutputPort() );
    }
    renderWindow_Local->Render();
}
// This applies the Clipping Filter to the image on the MainWindow
void Filters::on_Clipper_Filter_toggled(bool Clipper_Filter_Status)
{
    if(Clipper_Filter_Status == true )
    {
        checked_Box_Status_Updater(2);

        planeLeft->SetOrigin(double(ui->X_Origin->value()/10.0), double(ui->Y_Origin->value()/10.0), double(ui->Z_Origin->value()/10.0));
        planeLeft->SetNormal(double(ui->X_Normal->value()/10.0), double(ui->Y_Normal->value()/10.0), double(ui->Z_Normal->value()/10.0));

        Clipper_Filter->SetInputConnection( reader_Local->GetOutputPort() ) ;
        Clipper_Filter->SetClipFunction( planeLeft.Get() );
        mapper_Local->SetInputConnection( Clipper_Filter->GetOutputPort() );
    }
    else
    {
        mapper_Local->SetInputConnection( reader_Local->GetOutputPort() );
    }
    renderWindow_Local->Render();
}

void Filters::on_Scale_valueChanged(int value)
{
    Shrink_Filter->SetShrinkFactor((double (value))/100.00);
    renderWindow_Local->Render();
}

void Filters::on_X_Origin_valueChanged(int value)
{
    // This sets the Clipping Filter's X-Domain loaction
    double* Filter_Scroll = planeLeft->GetOrigin();
    planeLeft->SetOrigin(double (value)/10.00, Filter_Scroll[1], Filter_Scroll[2]);
    renderWindow_Local->Render();
}

void Filters::on_Y_Origin_valueChanged(int value)
{
    // This sets the Clipping Filter's Y-Domain loaction
    double* Filter_Scroll = planeLeft->GetOrigin();
    planeLeft->SetOrigin(Filter_Scroll[0], double (value)/10.00 ,Filter_Scroll[2]);
    renderWindow_Local->Render();
}

void Filters::on_Z_Origin_valueChanged(int value)
{
    // This sets the Clipping Filter's Z-Domain loaction
    double* Filter_Scroll = planeLeft->GetOrigin();
    planeLeft->SetOrigin(Filter_Scroll[0], Filter_Scroll[1], double (value)/10.00);
    renderWindow_Local->Render();
}

void Filters::on_X_Normal_valueChanged(int value)
{
    // This sets the Clipping Filter's X-Domain loaction

    double* Filter_Scroll = planeLeft->GetNormal();
    planeLeft->SetNormal(double (value)/10.00, Filter_Scroll[1], Filter_Scroll[2]);
    renderWindow_Local->Render();
}

void Filters::on_Y_Normal_valueChanged(int value)
{
    // This sets the Clipping Filter's Y-Domain loaction
    double* Filter_Scroll = planeLeft->GetNormal();
    planeLeft->SetNormal(Filter_Scroll[0], double (value)/10.00 ,Filter_Scroll[2]);
    renderWindow_Local->Render();
}

void Filters::on_Z_Normal_valueChanged(int value)
{
    // This sets the Clipping Filter's Z-Domain loaction
    double* Filter_Scroll = planeLeft->GetNormal();
    planeLeft->SetNormal(Filter_Scroll[0], Filter_Scroll[1], double (value)/10.00);
    renderWindow_Local->Render();
}
// When this function is called it ensures all other Filters are decatiated
void Filters::checked_Box_Status_Updater(int CheckBox_Number)
{
    // The Switch statement checks the number being passed and applied the desired change
    switch (CheckBox_Number)
    {
    // When Addin more filters add them to each case for their turn off
    case 0 : ui->Clipper_Filter->setCheckState(Qt::Unchecked);
             ui->Shrink_Filter->setCheckState(Qt::Unchecked);
        break;
    case 1 : ui->Clipper_Filter->setCheckState(Qt::Unchecked);
        break;
    case 2 : ui->Shrink_Filter->setCheckState(Qt::Unchecked);
        break;
    }
}
