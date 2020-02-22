#include "filters.h"
#include "ui_filters.h"
//#include "vtkSmartPointers.h"

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

void Filters::open(vtkSmartPointer<vtkSTLReader> &Passedreader,
                   vtkSmartPointer<vtkDataSetMapper> &Passmapper,
                   vtkSmartPointer<vtkGenericOpenGLRenderWindow> &PassedWindow)
{
    renderWindow_Local = PassedWindow;
    reader_Local = Passedreader;
    mapper_Local = Passmapper;
}

void Filters::on_Shrink_Filter_toggled(bool checked)
{
    if(checked ==true )
        {
        Shrink_Filter->SetInputConnection( reader_Local->GetOutputPort() );
        Shrink_Filter->SetShrinkFactor(.5);
        Shrink_Filter->Update();
        mapper_Local->SetInputConnection( Shrink_Filter->GetOutputPort() );
        }
        else
        {
         mapper_Local->SetInputConnection( reader_Local->GetOutputPort() );
        }
        renderWindow_Local->Render();
}

void Filters::on_Clipper_Filter_toggled(bool checked)
{
    if(checked ==true )
        {
        // this will apply a clipping plane whose normal is the x-axis that crosses the x-axis at x=0
        planeLeft->SetOrigin(0.0, 0.0, 0.0);
        planeLeft->SetNormal(-1.0, 0.0, 0.0);

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

void Filters::on_X_valueChanged(int value)
{
    double* Filter_Scroll = planeLeft->GetNormal();
    planeLeft->SetOrigin(double (value), Filter_Scroll[1], Filter_Scroll[2]);
    Clipper_Filter->SetInputConnection( reader_Local->GetOutputPort() ) ;
    Clipper_Filter->SetClipFunction( planeLeft.Get() );
    mapper_Local->SetInputConnection( Clipper_Filter->GetOutputPort() );
    renderWindow_Local->Render();
}

void Filters::on_Y_valueChanged(int value)
{
    double* Filter_Scroll = planeLeft->GetNormal();
    planeLeft->SetOrigin(Filter_Scroll[0], double (value) ,Filter_Scroll[2]);
    Clipper_Filter->SetInputConnection( reader_Local->GetOutputPort() ) ;
    Clipper_Filter->SetClipFunction( planeLeft.Get() );
    mapper_Local->SetInputConnection( Clipper_Filter->GetOutputPort() );
    renderWindow_Local->Render();


}

void Filters::on_Z_valueChanged(int value)
{
    double* Filter_Scroll = planeLeft->GetNormal();
    planeLeft->SetOrigin(Filter_Scroll[0], Filter_Scroll[1], double (value));
    Clipper_Filter->SetInputConnection( reader_Local->GetOutputPort() ) ;
    Clipper_Filter->SetClipFunction( planeLeft.Get() );
    mapper_Local->SetInputConnection( Clipper_Filter->GetOutputPort() );
    renderWindow_Local->Render();
}
