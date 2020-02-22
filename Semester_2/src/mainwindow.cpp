//--------------------mainwindow.cpp--------------------//


// MainWindow.cpp
// WorkSheet 6 Computing Project
// Edited By Jedidiah Paterson on 02/22/2020.
// Copyright @ 2020 Jedidiah Paterson. All right reserved.
// This file loads an Image onto a GUI (Grapgical User Interface)
// Impleminting the function defined in MainWindow.h and connected
// To the buttons on MainWindow.ui

#include <vtkCamera.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>

#include <QColorDialog>
#include <QDebug>           // TROUBLESHOOTING ONLY //
#include <QFileDialog>
#include <QInputDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "edit_light.h"
#include "vtklight_withname.h"

//-------------Constructor------------//

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
// This Sets the RinderWindow to the *.ui files Widget named Display_Window

    ui->Display_Window->SetRenderWindow( renderWindow );
    connect( this, &MainWindow::statusUpdateMessage, ui->statusBar, &QStatusBar::showMessage );
// First this the file does is loads a valid file
// Currently only *.STL files but an update will
// Allow for *.MOD files to be loaded

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open STL File"), "../../stl", tr("STL Files(*.stl)"));
    std::string str= fileName.toUtf8().constData();
    reader->SetFileName(str.data());
    reader->Update();
// Initial Setup of the the Display_Window and the viewing plane

    mapper->SetInputConnection( reader->GetOutputPort() );
    actor->SetMapper(mapper);
    actor->GetProperty()->EdgeVisibilityOn();
    actor->GetProperty()->SetColor( colors->GetColor3d("Green").GetData() );

    ui->Display_Window->GetRenderWindow()->AddRenderer( renderer );
// Adding an actor and a camera allows

    renderer->AddActor(actor);
    renderer->SetBackground( colors->GetColor3d("Silver").GetData() );
    renderer->ResetCamera();
    renderer->GetActiveCamera()->Azimuth(30);
    renderer->GetActiveCamera()->Elevation(30);
    renderer->ResetCameraClippingRange();
}
//--------------Destructor-------------//

MainWindow::~MainWindow()
{
    delete ui;
}
//-------Special Member Functions------//

void MainWindow::on_Change_Object_Color_released()
{
    ui->statusBar->showMessage("Change Object Color Button was clicked",3000);
    //Opens Dialog Box to allow the use to chose a color
        QColor Color = QColorDialog::getColor(Qt::white,this,"Choose Color");
        //checks to ensure that the selector color is valid
        if(Color.isValid())
        {
            //converts the QColor to RGB values ranging from 0.0 - 1.0 to be used by SetColor function
            double red = Color.redF();
            double green = Color.greenF();
            double blue = Color.blueF();
            //Outputs values to the termial block for debuging
            //qDebug() << Color;
            //qDebug() << Color.redF();
            //qDebug() << Color.greenF();
            //qDebug() << Color.blueF();
            actor->GetProperty()->SetColor( red,green,blue );
        }
        //rerenders the window after the color change
        renderWindow->Render();
}

void MainWindow::on_Add_Light_released()
{
    ui->statusBar->showMessage("Add Light Button was clicked",3000);
    vtkLight_WithName light;
    light.SetName(InputQString());
    ListOfLights.push_back(light);
// This checks to ensure a name has been given to the light
// If this check is not done clicking cancle will result in a crash

    if(light.GetName().isEmpty() == false)
    {
// This establishes default settingd for an added light

        ui->Select_Light->addItem(light.GetName());
        light.light->SetLightTypeToSceneLight();
        light.light->SetPosition( 5, 5, 15 );
        light.light->SetPositional( true );
        light.light->SetConeAngle( 10 );
        light.light->SetFocalPoint( 0, 0, 0 );
        light.light->SetDiffuseColor( 1, 1, 1 );
        light.light->SetAmbientColor( 1, 1, 1 );
        light.light->SetSpecularColor( 1, 1, 1 );
        light.light->SetIntensity( 0.5 );
        renderer->AddLight( light.light );
        ui->Display_Window->GetRenderWindow()->Render();
        //renderWindow->Render();
    }
}

QString MainWindow::InputQString()
{
   bool ok;
        QString text = QInputDialog::getText(this, tr("Light Name"),
                                             tr("Light Name:"), QLineEdit::Normal,
                                             tr("Light Name"), &ok);
        if (ok && !text.isEmpty())
            return (text);
       // This keeps the window from crashing when nothing is returned from the input
        else
            return(0);
}

void MainWindow::on_Change_Back_Ground_Color_released()
{
    ui->statusBar->showMessage("Change Color Back Ground Button was clicked",3000);
    QColor Color = QColorDialog::getColor(Qt::white,this,"Choose Back Ground Color");
        if(Color.isValid())
        {
            double red = Color.redF();
            double green = Color.greenF();
            double blue = Color.blueF();
            renderer->SetBackground( red,green,blue );
        }
        //rerenders the window after the color change
        renderWindow->Render();
}

void MainWindow::on_Reset_Camera_released()
{
    ui->statusBar->showMessage("Reset Button was clicked",3000);
    renderer->ResetCamera();
      double* CameraLocation = renderer->GetActiveCamera()->GetPosition();
      renderWindow->Render();
}

void MainWindow::on_Apply_Filters_released()
{
    ui->statusBar->showMessage(" Apply Filter Button was clicked",3000);
// This open a Modaless window which allows
// User interaction with the mainwindow while open

    filters =new Filters(this);
    filters->setWindowTitle("Apply Filters");
    filters->show();
    filters->open(reader, mapper, renderWindow);
}

void MainWindow::on_X_Camera_Pos_valueChanged(int value)
{
    ui->statusBar->showMessage("X Camera Position Value was Changed",3000);
    static int Last_Value_Pitch = 0;
    int Temp = value;
    value = value-Last_Value_Pitch;
    renderer->GetActiveCamera()->Azimuth(double (value));
    Last_Value_Pitch = Temp;
    renderWindow->Render();
}

void MainWindow::on_Y_Camera_Pos_valueChanged(int value)
{
    ui->statusBar->showMessage("Y Camera Position Value was Changed",3000);
    static double Last_Value_Roll = 0.0;
    int Temp = value;
    value = value-Last_Value_Roll;
    renderer->GetActiveCamera()->Roll(double (value));
    Last_Value_Roll = Temp;
    renderWindow->Render();
}

void MainWindow::on_Z_Camera_Pos_valueChanged(int value)
{
    ui->statusBar->showMessage("Z Camera Position Value was Changed",3000);
    static double Last_Value_Yaw= 0.0;
    int Temp = value;
    value = value-Last_Value_Yaw;
    renderer->GetActiveCamera()->Elevation(double (value));
    Last_Value_Yaw = Temp;
    renderWindow->Render();
}

void MainWindow::on_Vertical_Shift_valueChanged(int arg1)
{
    ui->statusBar->showMessage("Vertical Shift Value was Changed",3000);
    static double Last_Value_Elevation= 0.0;
    int Temp = arg1;
    arg1 = arg1-Last_Value_Elevation;
    renderer->GetActiveCamera()->Pitch(double (-arg1));
    Last_Value_Elevation = Temp;
    renderWindow->Render();
}

void MainWindow::on_Horizontal_Shift_valueChanged(int arg1)
{
    ui->statusBar->showMessage("Horizontal Shift Value was Changed",3000);
    static double Last_Value_Azimuth= 0.0;
    int Temp = arg1;
    arg1 = arg1-Last_Value_Azimuth;
    renderer->GetActiveCamera()->Yaw(double (arg1));
    Last_Value_Azimuth = Temp;
    renderWindow->Render();
}

void MainWindow::on_actionOpen_triggered()
{
    ui->statusBar->showMessage("Open Action Triggered",3000);
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open STL File"), "../../stl", tr("STL Files(*.stl)"));
    std::string str= fileName.toUtf8().constData();
    reader->SetFileName(str.data());
    reader->Update();
    renderer->ResetCamera();
    renderWindow->Render();
}

void MainWindow::on_actionSave_triggered()
{
    ui->statusBar->showMessage("Save Action Triggered",3000);
    // Function not Yet Made //
}

void MainWindow::on_Edit_Light_clicked()
{
    ui->statusBar->showMessage("Edit Light Button was clicked",3000);
// This ensures a light has been created before t can be selected to be edited

    if(ui->Select_Light->currentIndex() > -1)
        {
        Edit_LightDialog =new Edit_Light(this);
        Edit_LightDialog->setWindowTitle(ListOfLights.at(ui->Select_Light->currentIndex()).GetName());
        Edit_LightDialog->show();
        Edit_LightDialog->open(ListOfLights.at(ui->Select_Light->currentIndex()),renderWindow );
        }
    else
    ui->statusBar->showMessage("Nothing selected to Edit ",3000);
}

void MainWindow::on_Delete_Light_released()
{
// There will be a recall of Deleted light function to recover
// Accidentally deleted lights during the users current session
// Also, A save&load list of loghts function will be added

    int LightToDelete = ui->Select_Light->currentIndex();
    if(ui->Select_Light->currentIndex() > -1)
        {
        ui->Select_Light->removeItem(ui->Select_Light->currentIndex());
        renderer->RemoveLight(ListOfLights.at(LightToDelete).light);
        //ListOfLights.at(LightToDelete).light->SwitchOff();
        // add a light recall function and save the list of lights to be loaded later
        ListOfLights.erase(ListOfLights.begin()+LightToDelete);
        }
    else
        {
        ui->statusBar->showMessage("Nothing to Delete ",3000);
        }
    renderWindow->Render();
}
