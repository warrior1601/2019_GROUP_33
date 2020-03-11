#include <map>
#include <vector>

#include <QFileDialog>
#include <QDialog>
#include <QDebug>
#include <QColor>
#include <QColorDialog>
#include <QButtonGroup>
#include <QMessageBox>

#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkSTLReader.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkNew.h>
#include <vtkLight.h>
#include <vtkCamera.h>
#include <vtkProperty.h>
#include <vtkNamedColors.h>
#include <vtkPlane.h>
#include <vtkClipDataSet.h>
#include <vtkShrinkFilter.h>
#include <vtkPyramid.h>
#include <vtkTetra.h>
#include <vtkHexahedron.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkUnstructuredGrid.h>
#include <vtkPolyData.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"

using std::map;
using std::vector;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    // standard call to setup Qt UI (same as previously)
    ui->setupUi( this );
	
	// create a STL reader to read a STL file
    STLReader = vtkSmartPointer<vtkSTLReader>::New();
    // create a renderer
    renderer = vtkSmartPointer<vtkRenderer>::New();
    // create an actor used for set the properties of the model
    actor = vtkSmartPointer<vtkActor>::New();
	// create an actor for primitive shape
    // shapeActor = vtkSmartPointer<vtkActor>::New();
    // create a light to provides light setting
    light = vtkSmartPointer<vtkLight>::New();
    // create color to set related information
	color = vtkSmartPointer<vtkNamedColors>::New();
    // create a mapper to hold a the information of the model
    mapper = vtkSmartPointer<vtkDataSetMapper>::New();
    // create a camera
    camera = vtkSmartPointer<vtkCamera>::New();

 	// set the background color of the render window
    renderer->SetBackground(0.5, 0.5, 0.5);
    // set the light
    light->SetLightTypeToSceneLight();

	for (size_t i = 0; i < 3; i++)
	{
		value.push_back(1);
	}


	ui->openGLWidget->SetRenderWindow(renderWindow);
	ui->openGLWidget->GetRenderWindow()->AddRenderer(renderer);


	connect(ui->Open, SIGNAL(triggered()), this, SLOT(open()));
	connect(ui->reset, SIGNAL(clicked()), this, SLOT(resetcamera()));
    connect(ui->RTB, SIGNAL(clicked()), this, SLOT(RTB()));
	connect(ui->ChangeColor, SIGNAL(clicked()), this, SLOT(selectecolor()));
	connect(ui->lightColor, SIGNAL(clicked()), this, SLOT(setLightColor()));
    connect(ui->intensity, SIGNAL(valueChanged(double)), this, SLOT(setLightIntensity()));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::open()
{
	// renderer->RemoveActor(shapeActor);
    // ui->noShape->setChecked(true);

    // obtain the file name
    QString filename = QFileDialog::getOpenFileName(this, QString("Open STL file"), "E:\\STL Model Files-20200207", "STL file (*.stl)");

    // if file name is invalid then terminate the function
    if(filename.isEmpty())
    {
        QMessageBox::critical(this, "Error", "Invalid file name", QMessageBox::Ok);
        return;
    }

    // read the file
    STLReader->SetFileName(filename.toLatin1().data());
    STLReader->Update();

    mapper->SetInputConnection(STLReader->GetOutputPort());

    // set properties and date of the actor
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(color->GetColor3d("Blue").GetData());

    // render the actor
    renderer->AddActor(actor);

    ui->openGLWidget->GetRenderWindow()->AddRenderer(renderer);
    ui->openGLWidget->GetRenderWindow()->Render();


	camera->SetPosition(10, 0, 0);
    camera->SetFocalPoint(0, 0, 0);
    camera->SetClippingRange(-10, 10);
    camera->SetViewUp(0, 0, 0);

    // set active camera for randerer
    renderer->SetActiveCamera(camera);
    ui->openGLWidget->GetRenderWindow()->Render();
}

void MainWindow::resetcamera()
{
    // set camera parameters
    camera->SetPosition(10, 0, 0);
    camera->SetFocalPoint(0, 0, 0);
    camera->SetClippingRange(-10, 10);
    camera->SetViewUp(0, 0, 0);

    // set active camera for randerer
    renderer->SetActiveCamera(camera);
    ui->openGLWidget->GetRenderWindow()->Render();

}


void MainWindow::RTB()
{
    // allocate momory for store current object color
    double temp[3];
    // obtain the current object color
    for(size_t i = 0; i < 3; i++)
    {
        temp[i] = actor->GetProperty()->GetColor()[i];
    }

    // if current color is red
    if(temp[0] == 1 && temp[1] == 0 && temp[2] == 0)
    {
        // change color to blue
        actor->GetProperty()->SetColor(color->GetColor3d("Blue").GetData());
    }
    // if current color is not red
    else
    {
        // change color to blue
        actor->GetProperty()->SetColor(color->GetColor3d("Red").GetData());
    }

    // render the object
    renderer->AddActor(actor);
    ui->openGLWidget->GetRenderWindow()->Render();
}

void MainWindow::selectecolor()
{
    double red, green, blue;
    // obtain the color selected by user
    QColor selectedColor = QColorDialog::getColor(Qt::white, this,
                                           "Select the color", QColorDialog::ShowAlphaChannel);
    // check the validity of the selected color
    if(!selectedColor.isValid())
    {
        return ;
    }

    // calculate the RGB conponents
    red = selectedColor.red() / 255.0;
    green = selectedColor.green() / 255.0;
    blue = selectedColor.blue() / 255.0;

    // render the actor using the new color
    actor->GetProperty()->SetColor(red, green, blue);
    ui->openGLWidget->GetRenderWindow()->Render();
}

void MainWindow::setLightColor()
{
    // obtain the color selected by user
    QColor selectedColor = QColorDialog::getColor(Qt::white, this,
                                           "Select the color", QColorDialog::ShowAlphaChannel);
    // check the validity of the selected color
    if(!selectedColor.isValid())
    {
        return ;
    }

    // calculate the RGB conponents
    value[0] = selectedColor.red() / 255.0; 
    value[1] = selectedColor.green() / 255.0;
    value[2] = selectedColor.blue() / 255.0;

	light->SetColor(value[0],value[1],value[2]);
	renderer->AddLight(light);
    ui->openGLWidget->GetRenderWindow()->Render();

}

void MainWindow::setLightIntensity()
{
    // obtain the value fron the spin box
    intensity = ui->intensity->text().toDouble();

    // set light intensity
    light->SetIntensity(intensity);
    // maintain the color as before
	light->SetColor(value[0], value[1], value[2]);
    // add new light source to renderer
    renderer->AddLight(light);
    ui->openGLWidget->GetRenderWindow()->Render();

    // enable reset light operation
    // ui->removeLight->setEnabled(true);
}
