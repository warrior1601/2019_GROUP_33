//--------------------mainwindow.cpp--------------------//


// MainWindow.cpp
// WorkSheet 6 Computing Project
// Edited By Jedidiah Paterson on 02/22/2020.
// Copyright @ 2020 Jedidiah Paterson. All right reserved.
// This file loads an Image onto a GUI (Grapgical User Interface)
// Impleminting the function defined in MainWindow.h and connected
// To the buttons on MainWindow.ui

#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

#include <vtkCamera.h>
#include <vtkInformation.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkTriangle.h>

#include <QColorDialog>
#include <QDebug>           // TROUBLESHOOTING ONLY //
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "edit_light.h"
#include "vtklight_withname.h"

#include "Material.h"
#include "Vectors.h"
#include "Matrix.hpp"
#include "Cell.hpp"
#include "Model.hpp"

//-------------Constructor------------//

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // This Sets the RinderWindow to the *.ui files Widget named Display_Window

    ui->Display_Window->SetRenderWindow( renderWindow );
    connect( this, &MainWindow::statusUpdateMessage, ui->statusBar, &QStatusBar::showMessage );
    // First this the file does is loads a valid file

    on_actionOpen_triggered();
    // Adding a camera light

    vtkLight_WithName light;
    light.SetName("Camera Light");
    ListOfLights.push_back(light);
    ui->Select_Light->addItem(light.GetName());
    light.light->SetLightTypeToHeadlight();
    light.light->SetPosition( 5.0, 5.0, 15.0 );
    light.light->SetPositional( true );
    light.light->SetConeAngle( 10 );
    light.light->SetFocalPoint( 0.0, 0.0, 0.0 );
    light.light->SetDiffuseColor( 1, 1, 1 );
    light.light->SetAmbientColor( 1, 1, 1 );
    light.light->SetSpecularColor( 1, 1, 1 );
    light.light->SetIntensity( 0.5 );
    light.light->SwitchOff();
    renderer->AddLight( light.light );
    ui->Display_Window->GetRenderWindow()->Render();
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
        //converts the QColor to RGB values ranging from 0.0 through 1.0 to be used by SetColor function
        double red = Color.redF();
        double green = Color.greenF();
        double blue = Color.blueF();
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
    // With out this check clicking the canle button would cause the program to crash

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

//One comment to look at in this function
void MainWindow::on_Reset_Camera_released()
{
    ui->statusBar->showMessage("Reset Button was clicked",3000);
    renderer->ResetCamera();
    double* CameraLocation = renderer->GetActiveCamera()->GetPosition();
    //create a dispaly to show where the camer is currently at and where the focal point of the camer is.
    renderWindow->Render();
}

void MainWindow::on_Apply_Filters_released()
{
    ui->statusBar->showMessage(" Apply Filter Button was clicked",3000);
    // This open a Modaless window which allows
    // User interaction with the mainwindow while open

    if (LoadedFileType == true)
    {
        filters =new Filters(this);
        filters->setWindowTitle("Apply Filters");
        filters->show();
        filters->Open_Dialog(reader, mapper, renderWindow);
    }
    else
    {
        QMessageBox FilterMessage;
        FilterMessage.setWindowTitle("Error");
        FilterMessage.setText("Filters can only be applied to stl files.");
        FilterMessage.exec();
        ui->statusBar->showMessage("Filters can only be applied to stl files",3000);
    }
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
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "../../../example_models",
                                                    tr("STL Files(*.stl);;Text files (*.txt);;MOD Files(*.mod)"));
    std::string FilePath = fileName.toUtf8().constData();
    std::ifstream myFile(FilePath);

    if (myFile.is_open()) //Check if file has been opened sucessfully, if so returns true
    {
        // deletes the .mod or .txt file information that was loaded
        if (ListOfRenderers.size() > 0 )
        {
            ui->Display_Window->GetRenderWindow()->RemoveRenderer(ListOfRenderers[0]);
        }
        ListOfRenderers.clear();
        ListOfMappers.clear();
        ListOfUgs.clear();
        ListOfActors.clear();
        ListOfTriangles.clear();

        std::size_t found = FilePath.find_last_of(".");
        std::cout << "File type is: " << FilePath.substr(found+1) << std::endl;
        std::string FileType = FilePath.substr(found+1);

        if(FileType.compare("stl") == 0 )
        {
            LoadedFileType = true;
            reader->SetFileName(FilePath.data());
            mapper->SetInputConnection( reader->GetOutputPort() );
            renderer->ResetCameraClippingRange();
            reader->Update();

            actor->SetMapper(mapper);
            actor->GetProperty()->EdgeVisibilityOff();
            actor->GetProperty()->SetColor( colors->GetColor3d("Green").GetData() );
            ui->Display_Window->GetRenderWindow()->AddRenderer( renderer );
            renderer->AddActor(actor);
        }
        else if ((FileType.compare("txt") == 0 ) || (FileType.compare("mod")) == 0)
        {
            LoadedFileType = false;

            std::string currentLine;
            unsigned int tetra_count = 0;
            unsigned int pyramid_count = 0;
            unsigned int hexaherdon_cont = 0;
            unsigned int triangle_count = 0;

            points->Initialize();
            cellArray->Initialize();
            TriangleArray->Initialize();

            Model ModelOne;
            ModelOne.Load_Model(FilePath);
            vtkSmartPointer<vtkRenderer> Renderer = vtkSmartPointer<vtkRenderer>::New();
            ListOfRenderers.push_back(Renderer);
            ui->Display_Window->GetRenderWindow()->AddRenderer( ListOfRenderers[0] );

            std::string col;
            std::stringstream testing;

            for (unsigned int i = 0; i < ModelOne.Get_Vectors().size(); i++)
            {
                //loading of the vectors into points to be used by the stlwriter
                double Data[] = { ModelOne.Get_Vectors()[i].GetXVector(),
                                  ModelOne.Get_Vectors()[i].GetYVector(),
                                  ModelOne.Get_Vectors()[i].GetZVector()};
                points->InsertNextPoint(Data);
            }
            for (unsigned int i = 0; i < ModelOne.Get_Cell_Order().size(); i++)
            {
                vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
                ListOfMappers.push_back(mapper);

                vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
                ListOfActors.push_back(actor);

                vtkSmartPointer<vtkUnstructuredGrid> ug = vtkSmartPointer<vtkUnstructuredGrid>::New();
                ListOfUgs.push_back(ug);

                // This is baics shape reader needs changing for loading more complex shapes
                Cell Test = *ModelOne.Get_Cells()[i];
                if (ModelOne.Get_Cell_Order()[i] == 't')
                {
                    ListOfUgs[i]->SetPoints(points);
                    vtkSmartPointer<vtkTetra> tetra = vtkSmartPointer<vtkTetra>::New();
                    ListOfTetras.push_back(tetra);
                    for (vtkIdType vtkId = 0; vtkId < 4; vtkId++)
                    {
                        ListOfTetras[tetra_count]->GetPointIds()->SetId(vtkId, vtkIdType (Test.Get_Vertices_Order()[vtkId]) );
                    }
                    //Loading Triangles
                    vtkSmartPointer<vtkTriangle> triangle_Tetra_0 = vtkSmartPointer<vtkTriangle>::New();
                    ListOfTriangles.push_back(triangle_Tetra_0);
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 0, vtkIdType (Test.Get_Vertices_Order()[0]) );
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 1, vtkIdType (Test.Get_Vertices_Order()[1]) );
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 2, vtkIdType (Test.Get_Vertices_Order()[2]) );
                    TriangleArray->InsertNextCell(ListOfTriangles[triangle_count]);
                    triangle_count++;

                    vtkSmartPointer<vtkTriangle> triangle_Tetra_1 = vtkSmartPointer<vtkTriangle>::New();
                    ListOfTriangles.push_back(triangle_Tetra_1);
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 0, vtkIdType (Test.Get_Vertices_Order()[0]) );
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 1, vtkIdType (Test.Get_Vertices_Order()[2]) );
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 2, vtkIdType (Test.Get_Vertices_Order()[3]) );
                    TriangleArray->InsertNextCell(ListOfTriangles[triangle_count]);
                    triangle_count++;

                    vtkSmartPointer<vtkTriangle> triangle_Tetra_2 = vtkSmartPointer<vtkTriangle>::New();
                    ListOfTriangles.push_back(triangle_Tetra_2);
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 0, vtkIdType (Test.Get_Vertices_Order()[0]) );
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 1, vtkIdType (Test.Get_Vertices_Order()[1]) );
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 2, vtkIdType (Test.Get_Vertices_Order()[3]) );
                    TriangleArray->InsertNextCell(ListOfTriangles[triangle_count]);
                    triangle_count++;

                    vtkSmartPointer<vtkTriangle> triangle_Tetra_3 = vtkSmartPointer<vtkTriangle>::New();
                    ListOfTriangles.push_back(triangle_Tetra_3);
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 0, vtkIdType (Test.Get_Vertices_Order()[1]) );
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 1, vtkIdType (Test.Get_Vertices_Order()[2]) );
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 2, vtkIdType (Test.Get_Vertices_Order()[3]) );
                    TriangleArray->InsertNextCell(ListOfTriangles[triangle_count]);
                    triangle_count++;

                    cellArray->InsertNextCell(ListOfTetras[tetra_count]);
                    ListOfUgs[i]->InsertNextCell(tetra->GetCellType(), ListOfTetras[tetra_count]->GetPointIds());
                    ListOfMappers[i]->SetInputData(ListOfUgs[i]);
                    ListOfActors[i]->SetMapper(ListOfMappers[i]);


                    // put in function ??//
                    col =  Test.Get_Material().GetColour();
                    std::string RGB_Red = col.substr(0,2);
                    std::string RGB_Green = col.substr(2,2);
                    std::string RGB_Blue = col.substr(4,2);

                    int Red = 0;
                    std::istringstream(RGB_Red) >> std::hex >> Red;
                    double Red_remapped = (0.0 + (1.0 - 0.0) * ((Red - 0.0) / (255 - 0.0)));

                    int Green = 0;
                    std::istringstream(RGB_Green) >> std::hex >> Green;
                    double Green_remapped = (0.0 + (1.0 - 0.0) * ((Green - 0.0) / (255 - 0.0)));

                    int Blue = 0;
                    std::istringstream(RGB_Blue) >> std::hex >> Blue;
                    double Blue_remapped = (0.0 + (1.0 - 0.0) * ((Blue - 0.0) / (255 - 0.0)));

                    ListOfActors[i]->GetProperty()->SetColor(Red_remapped,Green_remapped,Blue_remapped);
                    ListOfRenderers[0]->AddActor(ListOfActors[i]);
                    tetra_count++;
                }

                if (ModelOne.Get_Cell_Order()[i] == 'p')
                {
                    ListOfUgs[i]->SetPoints(points);
                    vtkSmartPointer<vtkPyramid> pyramid = vtkSmartPointer<vtkPyramid>::New();
                    ListOfPyramids.push_back(pyramid);
                    for (vtkIdType vtkId = 0; vtkId < 5; vtkId++)
                    {
                        ListOfPyramids[pyramid_count]->GetPointIds()->SetId(vtkId, vtkIdType (Test.Get_Vertices_Order()[vtkId]) );
                    }
                    //Loading triangles
                    vtkSmartPointer<vtkTriangle> triangle_Pyramid_0 = vtkSmartPointer<vtkTriangle>::New();
                    ListOfTriangles.push_back(triangle_Pyramid_0);
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 0, vtkIdType (Test.Get_Vertices_Order()[0]) );
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 1, vtkIdType (Test.Get_Vertices_Order()[1]) );
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 2, vtkIdType (Test.Get_Vertices_Order()[4]) );
                    TriangleArray->InsertNextCell(ListOfTriangles[triangle_count]);
                    triangle_count++;

                    vtkSmartPointer<vtkTriangle> triangle_Pyramid_1 = vtkSmartPointer<vtkTriangle>::New();
                    ListOfTriangles.push_back(triangle_Pyramid_1);
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 0, vtkIdType (Test.Get_Vertices_Order()[1]) );
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 1, vtkIdType (Test.Get_Vertices_Order()[2]) );
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 2, vtkIdType (Test.Get_Vertices_Order()[4]) );
                    TriangleArray->InsertNextCell(ListOfTriangles[triangle_count]);
                    triangle_count++;

                    vtkSmartPointer<vtkTriangle> triangle_Pyramid_2 = vtkSmartPointer<vtkTriangle>::New();
                    ListOfTriangles.push_back(triangle_Pyramid_2);
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 0, vtkIdType (Test.Get_Vertices_Order()[2]) );
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 1, vtkIdType (Test.Get_Vertices_Order()[3]) );
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 2, vtkIdType (Test.Get_Vertices_Order()[4]) );
                    TriangleArray->InsertNextCell(ListOfTriangles[triangle_count]);
                    triangle_count++;

                    vtkSmartPointer<vtkTriangle> triangle_Pyramid_3 = vtkSmartPointer<vtkTriangle>::New();
                    ListOfTriangles.push_back(triangle_Pyramid_3);
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 0, vtkIdType (Test.Get_Vertices_Order()[3]) );
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 1, vtkIdType (Test.Get_Vertices_Order()[0]) );
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 2, vtkIdType (Test.Get_Vertices_Order()[4]) );
                    TriangleArray->InsertNextCell(ListOfTriangles[triangle_count]);
                    triangle_count++;

                    vtkSmartPointer<vtkTriangle> triangle_Pyramid_4 = vtkSmartPointer<vtkTriangle>::New();
                    ListOfTriangles.push_back(triangle_Pyramid_4);
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 0, vtkIdType (Test.Get_Vertices_Order()[0]) );
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 1, vtkIdType (Test.Get_Vertices_Order()[1]) );
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 2, vtkIdType (Test.Get_Vertices_Order()[3]) );
                    TriangleArray->InsertNextCell(ListOfTriangles[triangle_count]);
                    triangle_count++;

                    vtkSmartPointer<vtkTriangle> triangle_Pyramid_5 = vtkSmartPointer<vtkTriangle>::New();
                    ListOfTriangles.push_back(triangle_Pyramid_5);
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 0, vtkIdType (Test.Get_Vertices_Order()[1]) );
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 1, vtkIdType (Test.Get_Vertices_Order()[2]) );
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 2, vtkIdType (Test.Get_Vertices_Order()[3]) );
                    TriangleArray->InsertNextCell(ListOfTriangles[triangle_count]);
                    triangle_count++;

                    cellArray->InsertNextCell (ListOfPyramids[pyramid_count]);
                    ListOfUgs[i]->InsertNextCell(pyramid->GetCellType(), ListOfPyramids[pyramid_count]->GetPointIds());
                    ListOfMappers[i]->SetInputData(ListOfUgs[i]);
                    ListOfActors[i]->SetMapper(ListOfMappers[i]);
                    col =  Test.Get_Material().GetColour();
                    std::string RGB_Red = col.substr(0,2);
                    std::string RGB_Green = col.substr(2,2);
                    std::string RGB_Blue = col.substr(4,2);

                    int Red = 0;
                    std::istringstream(RGB_Red) >> std::hex >> Red;
                    double Red_remapped = (0.0 + (1.0 - 0.0) * ((Red - 0.0) / (255 - 0.0)));

                    int Green = 0;
                    std::istringstream(RGB_Green) >> std::hex >> Green;
                    double Green_remapped = (0.0 + (1.0 - 0.0) * ((Green - 0.0) / (255 - 0.0)));


                    int Blue = 0;
                    std::istringstream(RGB_Blue) >> std::hex >> Blue;
                    double Blue_remapped = (0.0 + (1.0 - 0.0) * ((Blue - 0.0) / (255 - 0.0)));

                    ListOfActors[i]->GetProperty()->SetColor(Red_remapped,Green_remapped,Blue_remapped);
                    ListOfRenderers[0]->AddActor(ListOfActors[i]);
                    pyramid_count++;
                }

                if (ModelOne.Get_Cell_Order()[i] == 'h')
                {
                    ListOfUgs[i]->SetPoints(points);
                    vtkSmartPointer<vtkHexahedron> hex = vtkSmartPointer<vtkHexahedron>::New();
                    ListOfHexs.push_back(hex);
                    for ( vtkIdType vtkId = 0; vtkId < 8; vtkId++)
                    {
                        ListOfHexs[hexaherdon_cont]->GetPointIds()->SetId(vtkId, vtkIdType (Test.Get_Vertices_Order()[vtkId]) );
                    }
                    //Loading Triangles
                    vtkSmartPointer<vtkTriangle> triangle_Hex_0 = vtkSmartPointer<vtkTriangle>::New();
                    ListOfTriangles.push_back(triangle_Hex_0);
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 0, vtkIdType (Test.Get_Vertices_Order()[0]) );
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 1, vtkIdType (Test.Get_Vertices_Order()[1]) );
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 2, vtkIdType (Test.Get_Vertices_Order()[5]) );
                    TriangleArray->InsertNextCell(ListOfTriangles[triangle_count]);
                    triangle_count++;

                    vtkSmartPointer<vtkTriangle> triangle_Hex_1 = vtkSmartPointer<vtkTriangle>::New();
                    ListOfTriangles.push_back(triangle_Hex_1);
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 0, vtkIdType (Test.Get_Vertices_Order()[0]) );
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 1, vtkIdType (Test.Get_Vertices_Order()[4]) );
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 2, vtkIdType (Test.Get_Vertices_Order()[5]) );
                    TriangleArray->InsertNextCell(ListOfTriangles[triangle_count]);
                    triangle_count++;

                    vtkSmartPointer<vtkTriangle> triangle_Hex_2 = vtkSmartPointer<vtkTriangle>::New();
                    ListOfTriangles.push_back(triangle_Hex_2);
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 0, vtkIdType (Test.Get_Vertices_Order()[1]) );
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 1, vtkIdType (Test.Get_Vertices_Order()[2]) );
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 2, vtkIdType (Test.Get_Vertices_Order()[6]) );
                    TriangleArray->InsertNextCell(ListOfTriangles[triangle_count]);
                    triangle_count++;

                    vtkSmartPointer<vtkTriangle> triangle_Hex_3 = vtkSmartPointer<vtkTriangle>::New();
                    ListOfTriangles.push_back(triangle_Hex_3);
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 0, vtkIdType (Test.Get_Vertices_Order()[1]) );
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 1, vtkIdType (Test.Get_Vertices_Order()[5]) );
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 2, vtkIdType (Test.Get_Vertices_Order()[6]) );
                    TriangleArray->InsertNextCell(ListOfTriangles[triangle_count]);
                    triangle_count++;

                    vtkSmartPointer<vtkTriangle> triangle_Hex_4 = vtkSmartPointer<vtkTriangle>::New();
                    ListOfTriangles.push_back(triangle_Hex_4);
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 0, vtkIdType (Test.Get_Vertices_Order()[2]) );
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 1, vtkIdType (Test.Get_Vertices_Order()[3]) );
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 2, vtkIdType (Test.Get_Vertices_Order()[7]) );
                    TriangleArray->InsertNextCell(ListOfTriangles[triangle_count]);
                    triangle_count++;

                    vtkSmartPointer<vtkTriangle> triangle_Hex_5 = vtkSmartPointer<vtkTriangle>::New();
                    ListOfTriangles.push_back(triangle_Hex_5);
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 0, vtkIdType (Test.Get_Vertices_Order()[2]) );
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 1, vtkIdType (Test.Get_Vertices_Order()[6]) );
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 2, vtkIdType (Test.Get_Vertices_Order()[7]) );
                    TriangleArray->InsertNextCell(ListOfTriangles[triangle_count]);
                    triangle_count++;

                    vtkSmartPointer<vtkTriangle> triangle_Hex_6 = vtkSmartPointer<vtkTriangle>::New();
                    ListOfTriangles.push_back(triangle_Hex_6);
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 0, vtkIdType (Test.Get_Vertices_Order()[3]) );
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 1, vtkIdType (Test.Get_Vertices_Order()[0]) );
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 2, vtkIdType (Test.Get_Vertices_Order()[4]) );
                    TriangleArray->InsertNextCell(ListOfTriangles[triangle_count]);
                    triangle_count++;

                    vtkSmartPointer<vtkTriangle> triangle_Hex_7 = vtkSmartPointer<vtkTriangle>::New();
                    ListOfTriangles.push_back(triangle_Hex_7);
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 0, vtkIdType (Test.Get_Vertices_Order()[3]) );
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 1, vtkIdType (Test.Get_Vertices_Order()[7]) );
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 2, vtkIdType (Test.Get_Vertices_Order()[4]) );
                    TriangleArray->InsertNextCell(ListOfTriangles[triangle_count]);
                    triangle_count++;

                    vtkSmartPointer<vtkTriangle> triangle_Hex_8 = vtkSmartPointer<vtkTriangle>::New();
                    ListOfTriangles.push_back(triangle_Hex_8);
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 0, vtkIdType (Test.Get_Vertices_Order()[0]) );
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 1, vtkIdType (Test.Get_Vertices_Order()[1]) );
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 2, vtkIdType (Test.Get_Vertices_Order()[2]) );
                    TriangleArray->InsertNextCell(ListOfTriangles[triangle_count]);
                    triangle_count++;

                    vtkSmartPointer<vtkTriangle> triangle_Hex_9 = vtkSmartPointer<vtkTriangle>::New();
                    ListOfTriangles.push_back(triangle_Hex_9);
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 0, vtkIdType (Test.Get_Vertices_Order()[0]) );
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 1, vtkIdType (Test.Get_Vertices_Order()[3]) );
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 2, vtkIdType (Test.Get_Vertices_Order()[2]) );
                    TriangleArray->InsertNextCell(ListOfTriangles[triangle_count]);
                    triangle_count++;

                    vtkSmartPointer<vtkTriangle> triangle_Hex_10 = vtkSmartPointer<vtkTriangle>::New();
                    ListOfTriangles.push_back(triangle_Hex_10);
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 0, vtkIdType (Test.Get_Vertices_Order()[4]) );
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 1, vtkIdType (Test.Get_Vertices_Order()[5]) );
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 2, vtkIdType (Test.Get_Vertices_Order()[6]) );
                    TriangleArray->InsertNextCell(ListOfTriangles[triangle_count]);
                    triangle_count++;

                    vtkSmartPointer<vtkTriangle> triangle_Hex_11 = vtkSmartPointer<vtkTriangle>::New();
                    ListOfTriangles.push_back(triangle_Hex_11);
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 0, vtkIdType (Test.Get_Vertices_Order()[4]) );
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 1, vtkIdType (Test.Get_Vertices_Order()[7]) );
                    ListOfTriangles[triangle_count]->GetPointIds()->SetId ( 2, vtkIdType (Test.Get_Vertices_Order()[6]) );
                    TriangleArray->InsertNextCell(ListOfTriangles[triangle_count]);
                    triangle_count++;

                    cellArray->InsertNextCell(ListOfHexs[hexaherdon_cont]);
                    ListOfUgs[i]->InsertNextCell(VTK_HEXAHEDRON, ListOfHexs[hexaherdon_cont]->GetPointIds() );
                    ListOfMappers[i]->SetInputData(ListOfUgs[i]);
                    ListOfActors[i]->SetMapper(ListOfMappers[i]);

                    col =  Test.Get_Material().GetColour();
                    std::string RGB_Red = col.substr(0,2);
                    std::string RGB_Green = col.substr(2,2);
                    std::string RGB_Blue = col.substr(4,2);

                    int Red = 0;
                    std::istringstream(RGB_Red) >> std::hex >> Red;
                    double Red_remapped = (0.0 + (1.0 - 0.0) * ((Red - 0.0) / (255 - 0.0)));

                    int Green  = 0;
                    std::istringstream(RGB_Green) >> std::hex >> Green;
                    double Green_remapped = (0.0 + (1.0 - 0.0) * ((Green - 0.0) / (255 - 0.0)));

                    int Blue  = 0;
                    std::istringstream(RGB_Blue) >> std::hex >> Blue;
                    double Blue_remapped = (0.0 + (1.0 - 0.0) * ((Blue - 0.0) / (255 - 0.0)));

                    ListOfActors[i]->GetProperty()->SetColor(Red_remapped,Green_remapped,Blue_remapped);
                    ListOfRenderers[0]->AddActor(ListOfActors[i]);
                    hexaherdon_cont++;
                }
            }
            ListOfRenderers[0]->ResetCameraClippingRange();

            ListOfRenderers[0]->SetBackground( colors->GetColor3d("Silver").GetData() );
            renderer->ResetCamera();
            renderWindow->Render();
        }
        renderer->SetBackground( colors->GetColor3d("Silver").GetData() );
        renderer->GetActiveCamera()->SetPosition(2.0 ,3.0, 5.0);
        renderer->GetActiveCamera()->SetFocalPoint(0.0 ,0.0, 0.0);
        renderer->ResetCamera();
        renderWindow->Render();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("No file was selected to open.");
        msgBox.exec();
    }
}

void MainWindow::on_actionSave_triggered()
{
    ui->statusBar->showMessage("Save Action Triggered",3000);
    // Function  Made here //
    QString savefile;
    savefile = QFileDialog::getSaveFileName(this,tr("Save File"),"/../../example_models",tr("STL Files(*.stl)"));
    std::string s=savefile.toStdString();
    const char* filename=s.c_str();
    std::cout << savefile.toStdString().c_str() << std::endl;

    if(savefile.isNull())
    {
        QMessageBox savemsg;
        savemsg.setText("No file was selected to save.");
        savemsg.exec();
    }
    else
    {
        //save mod to stl file
        if(triangle_count!=0)
        {
            polydata->Initialize();
            polydata->SetPolys(TriangleArray);
            polydata->SetPoints(points);

            vtkSmartPointer<vtkSTLWriter> stlWriter = vtkSmartPointer<vtkSTLWriter>::New();

            stlWriter->SetFileName(filename);
            stlWriter->SetInputData(polydata);
            stlWriter->Update();
            stlWriter->Write();

            std::cout << "mod save as stl file" << std::endl;
        }
        //save stl as stl file
        else
        {
            vtkSmartPointer<vtkTriangleFilter> tri = vtkSmartPointer<vtkTriangleFilter>::New();
            vtkSmartPointer<vtkSTLWriter> Writer = vtkSmartPointer<vtkSTLWriter>::New();
            tri->SetInputData(reader->GetOutput());

            Writer->SetFileName(filename);
            Writer->SetInputConnection(tri->GetOutputPort());
            Writer->Update();
            Writer->Write();
            std::cout <<"stl save as stl file" << std::endl;
        }
        
    }
}

void MainWindow::on_actionLoad_Lights_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open STL File"), " ", tr("Doc(*.txt)"));
    std::string FilePath= fileName.toUtf8().constData();

    std::ifstream myFile(FilePath);

    if (myFile.is_open()) //Check if file has been opened sucessfully, if so returns true
    {
        std::string currentLine;
        std::string compare ("Camera Light");
        double Data[] = {0.0, 0.0, 0.0};
        int ListofLightsPosition = 1;

        while ( getline (myFile,currentLine) )
        {
            if (currentLine.compare(compare) == 0 )
            {
                for(unsigned int i=0; i<18; i++ )
                {
                    getline (myFile,currentLine);
                    if ((currentLine.compare(5,7, "Ambient")) == 0 )
                    {
                        SetLightData(Data, currentLine);
                        ListOfLights.at(0).light->SetAmbientColor( Data[0], Data[1], Data[2] );
                    }
                    if ((currentLine.compare(5,7, "Diffuse")) == 0 )
                    {
                        SetLightData(Data, currentLine);
                        ListOfLights.at(0).light->SetDiffuseColor( Data[0], Data[1], Data[2] );
                    }
                    if ((currentLine.compare(5,8, "Specular")) == 0 )
                    {
                        SetLightData(Data, currentLine);
                        ListOfLights.at(0).light->SetSpecularColor( Data[0], Data[1], Data[2] );
                    }
                    if ((currentLine.compare(5,11, "Focal Point")) == 0 )
                    {
                        SetLightData(Data, currentLine);
                        ListOfLights.at(0).light->SetFocalPoint( Data[0], Data[1], Data[2] );
                    }
                    if ((currentLine.compare(5,8, "Position")) == 0 )
                    {
                        SetLightData(Data, currentLine);
                        ListOfLights.at(0).light->SetPosition( Data[0], Data[1], Data[2] );
                    }
                    if ((currentLine.compare(5,9, "Intensity")) == 0 )
                    {
                        int Placeholder = 0;
                        std::string temp;
                        for (int currentPosition = 0; currentPosition<currentLine.size(); currentPosition++)
                        {
                            if(currentLine[currentPosition] == ' ')
                            {
                                Placeholder++;
                            }
                            if (Placeholder == 6 )
                            {
                                if(currentLine[currentPosition] != ' ')
                                    temp.push_back(currentLine[currentPosition]);
                            }
                        }
                        ListOfLights.at(0).light->SetIntensity( std::stod (temp) );
                    }
                    if ((currentLine.compare(5,4, "Cone")) == 0 )
                    {
                        int Placeholder = 0;
                        std::string temp;
                        for (int currentPosition = 0; currentPosition<currentLine.size(); currentPosition++)
                        {
                            if(currentLine[currentPosition] == ' ')
                            {
                                Placeholder++;
                            }
                            if (Placeholder == 7 )
                            {
                                if(currentLine[currentPosition] != ' ')
                                    temp.push_back(currentLine[currentPosition]);
                            }
                        }
                        ListOfLights.at(0).light->SetConeAngle( std::stod (temp) );
                    }
                    if ((currentLine.compare(5,6, "Switch")) == 0 )
                    {
                        int Placeholder = 0;
                        std::string temp;
                        for (int currentPosition = 0; currentPosition<currentLine.size(); currentPosition++)
                        {
                            if(currentLine[currentPosition] == ' ')
                            {
                                Placeholder++;
                            }
                            if (Placeholder == 6 )
                            {
                                if(currentLine[currentPosition] != ' ')
                                    temp.push_back(currentLine[currentPosition]);
                            }
                        }

                        if (temp.compare(0, 3, "Off") == 0)
                        {
                            ListOfLights.at(0).light->SwitchOff();
                        }
                        else
                        {
                            ListOfLights.at(0).light->SwitchOn();
                        }
                    }
                }
            }
            else
            {
                vtkLight_WithName light;
                light.SetName((light.GetName().fromStdString(currentLine)));
                ListOfLights.push_back(light);
                ui->Select_Light->addItem(light.GetName());
                ListOfLights.back().light->SetLightTypeToSceneLight();
                for(unsigned int i=0; i<18; i++ )
                {
                    getline (myFile,currentLine);
                    if ((currentLine.compare(5,7, "Ambient")) == 0 )
                    {
                        SetLightData(Data, currentLine);
                        ListOfLights.back().light->SetAmbientColor( Data[0], Data[1], Data[2] );
                    }
                    if ((currentLine.compare(5,7, "Diffuse")) == 0 )
                    {
                        SetLightData(Data, currentLine);
                        ListOfLights.back().light->SetDiffuseColor( Data[0], Data[1], Data[2] );
                    }
                    if ((currentLine.compare(5,8, "Specular")) == 0 )
                    {
                        SetLightData(Data, currentLine);
                        ListOfLights.back().light->SetSpecularColor( Data[0], Data[1], Data[2] );
                    }
                    if ((currentLine.compare(5,11, "Focal Point")) == 0 )
                    {
                        SetLightData(Data, currentLine);
                        ListOfLights.back().light->SetFocalPoint( Data[0], Data[1], Data[2] );
                    }
                    if ((currentLine.compare(5,8, "Position")) == 0 )
                    {
                        SetLightData(Data, currentLine);
                        ListOfLights.back().light->SetPosition( Data[0], Data[1], Data[2] );
                    }
                    if ((currentLine.compare(5,9, "Intensity")) == 0 )
                    {
                        int Placeholder = 0;
                        std::string temp;
                        for (int currentPosition = 0; currentPosition<currentLine.size(); currentPosition++)
                        {
                            if(currentLine[currentPosition] == ' ')
                            {
                                Placeholder++;
                            }
                            if (Placeholder == 6 )
                            {
                                if(currentLine[currentPosition] != ' ')
                                    temp.push_back(currentLine[currentPosition]);
                            }
                        }
                        ListOfLights.back().light->SetIntensity( std::stod (temp) );
                    }
                    if ((currentLine.compare(5,4, "Cone")) == 0 )
                    {
                        int Placeholder = 0;
                        std::string temp;
                        for (int currentPosition = 0; currentPosition<currentLine.size(); currentPosition++)
                        {
                            if(currentLine[currentPosition] == ' ')
                            {
                                Placeholder++;
                            }
                            if (Placeholder == 7 )
                            {
                                if(currentLine[currentPosition] != ' ')
                                    temp.push_back(currentLine[currentPosition]);
                            }
                        }
                        ListOfLights.back().light->SetConeAngle( std::stod (temp) );
                        //std::cout << ListOfLights.at(ListofLightsPosition).light->GetConeAngle() << std::endl;
                    }
                    if ((currentLine.compare(5,6, "Switch")) == 0 )
                    {
                        int Placeholder = 0;
                        std::string temp;
                        for (int currentPosition = 0; currentPosition<currentLine.size(); currentPosition++)
                        {
                            if(currentLine[currentPosition] == ' ')
                            {
                                Placeholder++;
                            }
                            if (Placeholder == 6 )
                            {
                                if(currentLine[currentPosition] != ' ')
                                    temp.push_back(currentLine[currentPosition]);
                            }
                        }

                        if (temp.compare(0, 3, "Off") == 0)
                        {
                            ListOfLights.back().light->SwitchOff();
                        }
                        else
                        {
                            ListOfLights.back().light->SwitchOn();
                        }
                    }
                    if ((currentLine.compare(5,10, "Positional")) == 0 )
                    {
                        int Placeholder = 0;
                        std::string temp;
                        for (int currentPosition = 0; currentPosition<currentLine.size(); currentPosition++)
                        {
                            if(currentLine[currentPosition] == ' ')
                            {
                                Placeholder++;
                            }
                            if (Placeholder == 6 )
                            {
                                if(currentLine[currentPosition] != ' ')
                                    temp.push_back(currentLine[currentPosition]);
                            }
                        }

                        if (temp.compare(0, 3, "Off") == 0)
                        {
                            ListOfLights.back().light->PositionalOff();
                        }
                        else
                        {
                            ListOfLights.back().light->PositionalOn();
                        }
                    }
                }
                renderer->AddLight( ((ListOfLights.at(ListofLightsPosition)).light) );
                ui->Display_Window->GetRenderWindow()->Render();
                ListofLightsPosition++;
            }
        }
    }
    renderWindow->Render();
}

void MainWindow::on_actionSave_Lights_triggered()
{
    // This opens a Dialog box that sets the PATH and file name of the file to be saved
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                    "Light List",tr("Doc (*.txt)"));
    QFile file(fileName);

    std::streambuf *psbuf;
    auto *coutbuf = std::cout.rdbuf();
    std::ofstream filestr;
    filestr.open ((fileName.toStdString()));//, std::ios::app);

    if (!filestr.is_open())
    {
        QMessageBox::information(this, tr("Unable to open file"),file.errorString());
        return;
    }
    else
    {
        for(int i = 0; i <ListOfLights.size(); i++)
        {
            vtkLight_WithName light = ListOfLights.at(i);
            QString Name = light.GetName();
            psbuf = filestr.rdbuf();        // get file's streambuf
            std::cout.rdbuf(psbuf);         // assign streambuf to cout
            std::cout<< Name.toStdString() << std::endl;
            light.light->PrintSelf( std::cout , vtkIndent(5));
        }
        filestr.flush();
        filestr.close();
        std::cout.rdbuf(coutbuf);
    }
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
        Edit_LightDialog->Open_Dialog(ListOfLights.at(ui->Select_Light->currentIndex()),renderWindow );
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
    if(ui->Select_Light->currentIndex() > 0)
    {
        ui->Select_Light->removeItem(ui->Select_Light->currentIndex());
        renderer->RemoveLight(ListOfLights.at(LightToDelete).light);
        // ListOfLights.at(LightToDelete).light->SwitchOff();
        // add a light recall function and save the list of lights to be loaded later
        ListOfLights.erase(ListOfLights.begin()+LightToDelete);
    }
    else
    {
        ui->statusBar->showMessage("Can Not Delete Camera Light Try Swithcing It OFF",3000);
    }
    renderWindow->Render();
}

void MainWindow::SetLightData(double *Data, std::string currentLine)
{
    std::string temp;
    int Placeholder = 0;
    int counter = 0;
    for (int currentPosition = 0; currentPosition<currentLine.size(); currentPosition++)
    {
        if(currentLine[currentPosition] == '(')
        {
            Placeholder++;
            continue;
        }
        if (Placeholder == 1)
        {
            if(currentLine[currentPosition] == ' ')
            {
                temp.clear();
                continue;
            }
            if((currentLine[currentPosition] == ',')||(currentLine[currentPosition] == ')'))
            {
                for(int subPosition = int (temp.size())-1; subPosition<temp.size(); subPosition++)
                {
                    Data[counter] = std::stod(temp);
                }
                counter++;
                continue;
            }
            temp.push_back(currentLine[currentPosition]);
        }
    }
}

void MainWindow::on_FullScreen_clicked(bool checked)
{

	ui->statusBar->showMessage("FullScreen", 3000);
	isFullScreen() ? showNormal() : showFullScreen(); //for full screen

}


void MainWindow::on_actioncube_triggered()
{

	ui->statusBar->showMessage("Coordinate Axes were Applied", 3000);
	orientationWidget->SetOutlineColor(0.9300, 0.5700, 0.1300);
	orientationWidget->SetOrientationMarker(axes);
	orientationWidget->SetInteractor(renderWindowInteractor);
	orientationWidget->SetViewport(10, 10, 10, 10);
	orientationWidget->SetEnabled(1);
	orientationWidget->InteractiveOn();
	renderer->ResetCamera();

	transform->Translate(-3, -3, 0);
	axes->SetUserTransform(transform);
	renderer->AddActor(axes);
	renderWindow->Render();
}

void MainWindow::on_actionhelicopter_triggered()
{
	ui->statusBar->showMessage("Coordinate Axes were Applied", 3000);
	orientationWidget->SetOutlineColor(0.9300, 0.5700, 0.1300);
	orientationWidget->SetOrientationMarker(axes);
	orientationWidget->SetInteractor(renderWindowInteractor);
	orientationWidget->SetViewport(10, 10, 10, 10);
	orientationWidget->SetEnabled(1);
	orientationWidget->InteractiveOn();
	renderer->ResetCamera();

	transform->Translate(-10, -10, 0);
	axes->SetUserTransform(transform);
	renderer->AddActor(axes);
	renderWindow->Render();
}

void MainWindow::on_actionplane_triggered()
{
	ui->statusBar->showMessage("Coordinate Axes were Applied", 3000);
	orientationWidget->SetOutlineColor(0.9300, 0.5700, 0.1300);
	orientationWidget->SetOrientationMarker(axes);
	orientationWidget->SetInteractor(renderWindowInteractor);
	orientationWidget->SetViewport(10, 10, 10, 10);
	orientationWidget->SetEnabled(1);
	orientationWidget->InteractiveOn();
	renderer->ResetCamera();

	transform->Translate(-5, -6, 0);
	axes->SetUserTransform(transform);
	renderer->AddActor(axes);
	renderWindow->Render();
}

void MainWindow::on_actionsphere_triggered()
{
	ui->statusBar->showMessage("Coordinate Axes were Applied", 3000);
	orientationWidget->SetOutlineColor(0.9300, 0.5700, 0.1300);
	orientationWidget->SetOrientationMarker(axes);
	orientationWidget->SetInteractor(renderWindowInteractor);
	orientationWidget->SetViewport(10, 10, 10, 10);
	orientationWidget->SetEnabled(1);
	orientationWidget->InteractiveOn();
	renderer->ResetCamera();

	transform->Translate(-3, -3, 0);
	axes->SetUserTransform(transform);
	renderer->AddActor(axes);
	renderWindow->Render();
}

void MainWindow::on_actionairbus_triggered()
{
	ui->statusBar->showMessage("Coordinate Axes were Applied", 3000);
	orientationWidget->SetOutlineColor(0.9300, 0.5700, 0.1300);
	orientationWidget->SetOrientationMarker(axes);
	orientationWidget->SetInteractor(renderWindowInteractor);
	orientationWidget->SetViewport(10, 10, 10, 10);
	orientationWidget->SetEnabled(1);
	orientationWidget->InteractiveOn();
	renderer->ResetCamera();
	axes->SetTotalLength(50, 50, 50);
	transform->Translate(50, -50, -40);
	axes->SetUserTransform(transform);
	renderer->AddActor(axes);
	renderWindow->Render();
}

void MainWindow::on_actionThunderbolt_triggered()
{
	ui->statusBar->showMessage("Coordinate Axes were Applied", 3000);
	orientationWidget->SetOutlineColor(0.9300, 0.5700, 0.1300);
	orientationWidget->SetOrientationMarker(axes);
	orientationWidget->SetInteractor(renderWindowInteractor);
	orientationWidget->SetViewport(10, 10, 10, 10);
	orientationWidget->SetEnabled(1);
	orientationWidget->InteractiveOn();
	renderer->ResetCamera();
	axes->SetTotalLength(300, 300, 300);
	transform->Translate(500, -50, -40);
	axes->SetUserTransform(transform);
	renderer->AddActor(axes);
	renderWindow->Render();
}

//void MainWindow::on_BoxW_clicked(bool checked)
//{
//
//	if (checked) {
//		vtkSmartPointer<vtkBoxWidget> boxWidget =
//		vtkSmartPointer<vtkBoxWidget>::New();
//		boxWidget->SetInteractor(interactor);
//
//		boxWidget->SetProp3D(actor);
//		boxWidget->SetPlaceFactor(1.25); // Make the box 1.25x larger than the actor
//		boxWidget->PlaceWidget();
//
//		//vtkSmartPointer<vtkMyCallback> callback =
//		//vtkSmartPointer<vtkMyCallback>::New();
//		boxWidget->AddObserver(vtkCommand::InteractionEvent, callback);
//
//		boxWidget->On();
//		
//		
//	}
//		renderWindow->Render();
//}

void MainWindow::on_actionRuler_triggered()
{
	ui->statusBar->showMessage("Ruler was Applied", 3000);
	renderWindow->AddRenderer(renderer);
	renderWindowInteractor->SetRenderWindow(renderWindow);
	distanceWidget->SetInteractor(renderWindowInteractor);
	distanceWidget->CreateDefaultRepresentation();
	static_cast<vtkDistanceRepresentation*>(distanceWidget->GetRepresentation())
		->SetLabelFormat("%-#6.3g mm");
	renderWindowInteractor->Initialize();
	renderWindow->Render();
	distanceWidget->On();
	renderWindowInteractor->Start();
}

void MainWindow::on_actionRemove_Ruler_triggered()
{

	distanceWidget->Off();
	ui->Display_Window->GetRenderWindow()->Render();
}
