//-----filters.cpp--------------//

// filters.cpp
// Computing Project
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
    // now Render()  can be called.
    FilterWindowOpenStatus = &PassedFilterWindowOpenStatus;
    renderWindow_Local = aWindow;
    reader_Local = aReader;
    mapper_Local = aMapper;
    FileTypeSTL = true;
}

void Filters::Open_Dialog(std::vector<vtkSmartPointer<vtkDataSetMapper>> &aListOfMappers,
                          vtkSmartPointer<vtkGenericOpenGLRenderWindow> &aWindow,
                          bool &PassedFilterWindowOpenStatus)
{
    FilterWindowOpenStatus = &PassedFilterWindowOpenStatus;
    renderWindow_Local = aWindow;
    for (unsigned int i = 0; i < aListOfMappers.size(); i++)
    {
        ListOfMappers_Local.push_back(aListOfMappers[i]);
    }
    FileTypeSTL = false;
}

void Filters::on_Close_clicked()
{
    checked_Box_Status_Updater(0);
    *FilterWindowOpenStatus = false;
    renderWindow_Local->Render();
    this->close();
}

void Filters::closeEvent(QCloseEvent *event)
{
    //This ensures that when the "X" button that closes a window is closed
    //The desired close event is concluded
    on_Close_clicked();
}

// This appies the shrink Filter to the image on the MainWindow
void Filters::on_Shrink_Filter_toggled(bool Shrink_Filter_Status)
{
    //Filtering for STL files
    if((Shrink_Filter_Status == true ) && (FileTypeSTL == true))
    {
        // When this function is called it ensures that all other fillters are
        // No longer being applied
        checked_Box_Status_Updater(1);
        // establishing the pipeline for filtering
        Shrink_Filter->SetInputConnection( reader_Local->GetOutputPort() );
        Shrink_Filter->SetShrinkFactor(double(ui->Scale->value())/100.00);
        Shrink_Filter->Update();
        mapper_Local->SetInputConnection( Shrink_Filter->GetOutputPort() );
    }
    else if ((Shrink_Filter_Status == false ) && (FileTypeSTL == true))
    {
        // discontects the filter from the pipeline
        mapper_Local->SetInputConnection( reader_Local->GetOutputPort() );
    }
    //FIltering for MOD/TXT files
    if((Shrink_Filter_Status == true ) && (FileTypeSTL == false))
    {
        checked_Box_Status_Updater(1);
        ListOfShrink_Filters.clear(); // This ensures all the previous filters are deleted
        for (unsigned int i = 0; i < ListOfMappers_Local.size(); i++)
        {   //This creates a filter for each mapper. Each mapper has its own data (One Cell)
            //The reason for this is beacuse each mapper has its own actor determining color
            vtkSmartPointer<vtkShrinkFilter> Shrink_Filters = vtkSmartPointer<vtkShrinkFilter>::New();
            ListOfShrink_Filters.push_back(Shrink_Filters);
            //Estabishing the pipeling from the Data in the mapper back to the mapper for display
            ListOfShrink_Filters[i]->SetInputData( ListOfMappers_Local[i]->GetInput() );
            ListOfShrink_Filters[i]->SetShrinkFactor(double(ui->Scale->value())/100.00);
            ListOfShrink_Filters[i]->Update();
            ListOfMappers_Local[i]->SetInputConnection( ListOfShrink_Filters[i]->GetOutputPort() );
        }
    }
    else if ((Shrink_Filter_Status == false ) && (FileTypeSTL == false))
    {   //Discontecting the pipeline
        for (unsigned int i = 0; i < ListOfMappers_Local.size(); i++)
        {   //The data in the mapper can be perminitly change if you are not careful
            //To restore the pipeline with the data intact. Resetting the Shink Filters to 1.0 does this
            ListOfShrink_Filters[i]->SetShrinkFactor(double(1.0));
            ListOfShrink_Filters[i]->Update();
            ListOfMappers_Local[i]->SetInputData( ListOfMappers_Local[i]->GetInput() );
        }
    }
    renderWindow_Local->Render();
}
// This applies the Clipping Filter to the image on the MainWindow
void Filters::on_Clipper_Filter_toggled(bool Clipper_Filter_Status)
{
    // This is the Plane where clipping will occur. If clipping be sure to know which direction your normal faces, that diection will be clipped
    planeLeft->SetOrigin(double(ui->X_Origin->value()/10.0), double(ui->Y_Origin->value()/10.0), double(ui->Z_Origin->value()/10.0));
    planeLeft->SetNormal(double(ui->X_Normal->value()/10.0), double(ui->Y_Normal->value()/10.0), double(ui->Z_Normal->value()/10.0));
    //Filtering for STL files
    if((Clipper_Filter_Status == true )&& (FileTypeSTL == true))
    {
        checked_Box_Status_Updater(2);
        Clipper_Filter->SetInputConnection( reader_Local->GetOutputPort() ) ;
        Clipper_Filter->SetClipFunction( planeLeft.Get() );
        mapper_Local->SetInputConnection( Clipper_Filter->GetOutputPort() );
    }
    else if ((Clipper_Filter_Status == false )&& (FileTypeSTL == true))
    {
        mapper_Local->SetInputConnection( reader_Local->GetOutputPort() );
    }

    if((Clipper_Filter_Status == true )&& (FileTypeSTL == false))
    {
        checked_Box_Status_Updater(2);
        ListOfClipper_Filters.clear();
        for (unsigned int i = 0; i < ListOfMappers_Local.size(); i++)
        {
            vtkSmartPointer<vtkClipDataSet> Clipper_Filters = vtkSmartPointer<vtkClipDataSet>::New();
            ListOfClipper_Filters.push_back(Clipper_Filters);
            ListOfClipper_Filters[i]->SetInputData( ListOfMappers_Local[i]->GetInput() ) ;
            ListOfClipper_Filters[i]->SetClipFunction( planeLeft.Get() );
            ListOfMappers_Local[i]->SetInputConnection( ListOfClipper_Filters[i]->GetOutputPort() );
        }
    }
    else if ((Clipper_Filter_Status == false )&& (FileTypeSTL == false))
    {
        //This is not the correct way to return the data to is unchanged state
        //But it is unlikely that an image will be this close to the edge of a double's range/capacity
        planeLeft->SetOrigin(double(1e250), double(1e250), double(1e250));
        planeLeft->SetNormal(double(-1e250), double(-1e250), double(-1e250));

        for (unsigned int i = 0; i < ListOfClipper_Filters.size(); i++)
        {
            ListOfClipper_Filters[i]->SetClipFunction( planeLeft.Get()  );
            ListOfClipper_Filters[i]->Update();
            ListOfMappers_Local[i]->SetInputData( ListOfMappers_Local[i]->GetInput() );
        }
    }
    renderWindow_Local->Render();
}

void Filters::on_Scale_valueChanged(int value)
{
    if (FileTypeSTL == true)
    {
        Shrink_Filter->SetShrinkFactor((double (value))/100.00);
    }
    if (FileTypeSTL == false)
    {
        for (unsigned int i = 0; i < ListOfMappers_Local.size(); i++)
        {
            ListOfShrink_Filters[i]->SetShrinkFactor((double (value))/100.00);
        }
    }
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
    // When Adding more filters add them to each case for their turn off value
    case 0 : ui->Clipper_Filter->setCheckState(Qt::Unchecked);
        ui->Shrink_Filter->setCheckState(Qt::Unchecked);
        break;
    case 1 : ui->Clipper_Filter->setCheckState(Qt::Unchecked);
        break;
    case 2 : ui->Shrink_Filter->setCheckState(Qt::Unchecked);
        break;
    }
}
