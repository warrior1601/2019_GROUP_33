//--------------------mainwindow.cpp--------------------//

// MainWindow.cpp
// Computing Project
// Edited By Jedidiah Paterson on 02/22/2020.
// Copyright @ 2020 Jedidiah Paterson. All right reserved.
// This file loads an Image onto a GUI (Grapgical User Interface)
// Impleminting the function defined in MainWindow.h and connected
// To the buttons on MainWindow.ui

//using namespace std;

#include "mainwindow.h"
#include "ui_mainwindow.h"

//-------------Constructor------------//

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    // This Sets the RinderWindow to the *.ui files Widget named Display_Window
    ui->setupUi(this);
    ui->Display_Window->SetRenderWindow( renderWindow );
}
//--------------Destructor-------------//

MainWindow::~MainWindow()
{
    delete ui;
}
//-------Special Member Functions------//

void  MainWindow::Init_CameraLight()
{
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

void MainWindow::on_Change_Object_Color_released()
{
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

void MainWindow::on_Select_Light_editTextChanged(const QString &text)
{
    ListOfLights.at(ui->Select_Light->currentIndex()).SetName(text);
    ui->Select_Light->setItemText(ui->Select_Light->currentIndex(),ListOfLights.at(ui->Select_Light->currentIndex()).GetName());
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
    renderer->ResetCamera();
    double* CameraLocation = renderer->GetActiveCamera()->GetPosition();
    std::cout << "Camera Location: " << CameraLocation[0] << " " << CameraLocation[1] << " " << CameraLocation[2] << std::endl;
    //create a dispaly to show where the camera is currently at and where the focal point of the camera is.
    ui->Horizontal_Shift->setValue(0);
    ui->Vertical_Shift->setValue(0);
    ui->X_Camera_Pos->setValue(0);
    ui->Y_Camera_Pos->setValue(0);
    ui->Z_Camera_Pos->setValue(0);
    renderWindow->Render();
}

void MainWindow::on_Apply_Filters_released()
{
    // This open a Modaless window which allows
    // User interaction with the mainwindow while open
    if (LoadedFileType == true)
    {
        if (FilterWindowOpenStatus == false)
        {
            FilterWindowOpenStatus = true;
            filters =new Filters(this);
            filters->setWindowTitle("Apply Filters");
            filters->show();
            filters->Open_Dialog(reader, mapper, renderWindow, FilterWindowOpenStatus);
        }
    }
    else
    {
        FilterWindowOpenStatus = true;
        filters =new Filters(this);
        filters->setWindowTitle("Apply Filters");
        filters->show();
        filters->Open_Dialog(ListOfPolydata, ListOfMappers, renderWindow, FilterWindowOpenStatus);
       // QMessageBox::critical(this, "Runtime Error", "Filters are only available for models loaded from .stl files");
    }
}

void MainWindow::on_X_Camera_Pos_valueChanged(int value)
{
    static int Last_Value_Azimuth = 0.0;
    int Temp = value;
    value = value-Last_Value_Azimuth;
    renderer->GetActiveCamera()->Azimuth(double (value));
    Last_Value_Azimuth = Temp;
    renderWindow->Render();
}

void MainWindow::on_Y_Camera_Pos_valueChanged(int value)
{
    static double Last_Value_Roll = 0.0;
    int Temp = value;
    value = value-Last_Value_Roll;
    renderer->GetActiveCamera()->Roll(double (value));
    Last_Value_Roll = Temp;
    renderWindow->Render();
}

void MainWindow::on_Z_Camera_Pos_valueChanged(int value)
{
    static double Last_Value_Elevation= 0.0;
    int Temp = value;
    value = value-Last_Value_Elevation;
    renderer->GetActiveCamera()->Elevation(double (value));
    Last_Value_Elevation = Temp;
    renderWindow->Render();
}

void MainWindow::on_Vertical_Shift_valueChanged(int arg1)
{
    static double Last_Value_Pitch = 0.0;
    int Temp = arg1;
    if (( arg1 == 0 )&&( abs(Last_Value_Pitch) == 1.0 ))
    {
        renderer->GetActiveCamera()->Pitch(double (Last_Value_Pitch));
    }
    else if ((arg1 == 0)&&(Last_Value_Pitch =! 0.0))
    {
        renderer->GetActiveCamera()->Pitch(double (arg1));
    }

    else
    {
        arg1 = arg1-Last_Value_Pitch;
        renderer->GetActiveCamera()->Pitch(double (-arg1));
    }
    Last_Value_Pitch = Temp;
    renderWindow->Render();
}

void MainWindow::on_Horizontal_Shift_valueChanged(int arg1)
{
    static double Last_Value_Yaw = 0.0;
    int Temp = arg1;
    if (( arg1 == 0 )&&( abs(Last_Value_Yaw) == 1.0 ))
    {
        renderer->GetActiveCamera()->Yaw(double (-Last_Value_Yaw));
    }
    else if ((arg1 == 0 )&&( Last_Value_Yaw =! 0.0 ))
    {
        renderer->GetActiveCamera()->Yaw(double (-arg1));
    }
    else
    {
        arg1 = arg1-Last_Value_Yaw;
        renderer->GetActiveCamera()->Yaw(double (arg1));
    }
    Last_Value_Yaw = Temp;
    renderWindow->Render();
}

void MainWindow::on_LoadModelButton_released()
{
    ui->Tetra_Highlight->setCheckState(Qt::Unchecked);
    ui->Pyramid_Highlight->setCheckState(Qt::Unchecked);
    ui->Hexahedron_Highlight->setCheckState(Qt::Unchecked);

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "../../../example_models",
                                                    tr("STL Files(*.stl);;Text files (*.txt);;MOD Files(*.mod)"));
    std::string FilePath = fileName.toUtf8().constData();
    std::ifstream myFile(FilePath);

    if (myFile.is_open()) //Check if file has been opened sucessfully, if so returns true
    {
        ui->Display_Window->GetRenderWindow()->RemoveRenderer( renderer );
        //Initializes the orientationWidget so it can be used on different file types
        orientationWidget = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
        renderer = vtkSmartPointer<vtkRenderer>::New();

        Init_CameraLight();

        ListOfMappers.clear();
        ListOfUgs.clear();
        ListOfActors_tetra.clear();
        ListOfActors_pyramid.clear();
        ListOfActors_hexahedron.clear();
        ListOfTriangles.clear();
        ui->List_Of_Pyramids->clear();
        ui->List_Of_Tetras->clear();
        ui->List_Of_Hexahedrons->clear();

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
            renderer->SetBackground( colors->GetColor3d("Black").GetData() );
            renderer->GetActiveCamera()->SetPosition(2.0 ,3.0, 5.0);
            renderer->GetActiveCamera()->SetFocalPoint(0.0 ,0.0, 0.0);

            orientationWidget->SetOrientationMarker( axes );
            orientationWidget->SetInteractor(ui->Display_Window->GetRenderWindow()->GetInteractor());
            orientationWidget->SetEnabled(1);
            orientationWidget->InteractiveOff();

            renderer->ResetCamera();
            renderWindow->Render();

        }
        else if ((FileType.compare("txt") == 0 ) || (FileType.compare("mod")) == 0)
        {
            LoadedFileType = false;

            std::string currentLine;
            unsigned int tetra_count = 0;
            unsigned int pyramid_count = 0;
            unsigned int hexahedron_count = 0;
            unsigned int triangle_count = 0;

            points->Initialize();
            Model Empty;
            ModelOne = Empty;
            ModelOne.Load_Model(FilePath);
            ui->Display_Window->GetRenderWindow()->AddRenderer( renderer );

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
            cellArray->Initialize();
            TriangleArray->Initialize();
            for (unsigned int i = 0; i < ModelOne.Get_Cell_Order().size(); i++)
            {
                vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
                ListOfMappers.push_back(mapper);

                vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();

                vtkSmartPointer<vtkUnstructuredGrid> ug = vtkSmartPointer<vtkUnstructuredGrid>::New();
                ListOfUgs.push_back(ug);

                // This is baics shape reader needs changing for loading more complex shapes
                Cell Test = *ModelOne.Get_Cells()[i];
                if (ModelOne.Get_Cell_Order()[i] == 't')
                {
                    ListOfActors_tetra.push_back(actor);
                    ListOfUgs[i]->SetPoints(points);
                    vtkSmartPointer<vtkTetra> tetra = vtkSmartPointer<vtkTetra>::New();
                    ListOfTetras.push_back(tetra);

                    vtkSmartPointer<vtkPolyData> TetraPoly = vtkSmartPointer<vtkPolyData>::New();
                    vtkSmartPointer<vtkCellArray> TetraCell = vtkSmartPointer<vtkCellArray>::New();

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

                    TetraCell->InsertNextCell(ListOfTetras[tetra_count]);
                    cellArray->InsertNextCell(ListOfTetras[tetra_count]);
                    ListOfUgs[i]->InsertNextCell(tetra->GetCellType(), ListOfTetras[tetra_count]->GetPointIds());
                    ListOfMappers[i]->SetInputData(ListOfUgs[i]);
                    ListOfActors_tetra[tetra_count]->SetMapper(ListOfMappers[i]);

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

                    ListOfActors_tetra[tetra_count]->GetProperty()->SetColor(Red_remapped,Green_remapped,Blue_remapped);
                    renderer->AddActor(ListOfActors_tetra[tetra_count]);

                    ui->List_Of_Tetras->addItem("Tetrahedron "  + (QString::number(tetra_count + 1)) );

                    TetraPoly->SetPolys(TetraCell);
                    ListOfPolydata.push_back(TetraPoly);

                    tetra_count++;
                }

                if (ModelOne.Get_Cell_Order()[i] == 'p')
                {
                    ListOfActors_pyramid.push_back(actor);
                    ListOfUgs[i]->SetPoints(points);
                    vtkSmartPointer<vtkPyramid> pyramid = vtkSmartPointer<vtkPyramid>::New();
                    ListOfPyramids.push_back(pyramid);

                    vtkSmartPointer<vtkPolyData> PyramidPoly = vtkSmartPointer<vtkPolyData>::New();
                    vtkSmartPointer<vtkCellArray> PyramidCell = vtkSmartPointer<vtkCellArray>::New();

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

                    PyramidCell->InsertNextCell(ListOfPyramids[pyramid_count]);
                    cellArray->InsertNextCell(ListOfPyramids[pyramid_count]);
                    ListOfUgs[i]->InsertNextCell(pyramid->GetCellType(), ListOfPyramids[pyramid_count]->GetPointIds());
                    ListOfMappers[i]->SetInputData(ListOfUgs[i]);
                    ListOfActors_pyramid[pyramid_count]->SetMapper(ListOfMappers[i]);

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

                    ListOfActors_pyramid[pyramid_count]->GetProperty()->SetColor(Red_remapped,Green_remapped,Blue_remapped);
                    renderer->AddActor(ListOfActors_pyramid[pyramid_count]);

                    ui->List_Of_Pyramids->addItem("Pyramid " + (QString::number(pyramid_count + 1)) );

                    PyramidPoly->SetPolys(PyramidCell);
                    ListOfPolydata.push_back(PyramidPoly);
                    pyramid_count++;
                }

                if (ModelOne.Get_Cell_Order()[i] == 'h')
                {

                    ListOfActors_hexahedron.push_back(actor);
                    ListOfUgs[i]->SetPoints(points);
                    vtkSmartPointer<vtkHexahedron> hex = vtkSmartPointer<vtkHexahedron>::New();
                    ListOfHexs.push_back(hex);
                    vtkSmartPointer<vtkPolyData> HexPoly = vtkSmartPointer<vtkPolyData>::New();
                    vtkSmartPointer<vtkCellArray> HexCell = vtkSmartPointer<vtkCellArray>::New();

                    for ( vtkIdType vtkId = 0; vtkId < 8; vtkId++)
                    {
                        ListOfHexs[hexahedron_count]->GetPointIds()->SetId(vtkId, vtkIdType (Test.Get_Vertices_Order()[vtkId]) );
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

                    HexCell->InsertNextCell(ListOfHexs[hexahedron_count]);
                    cellArray->InsertNextCell(ListOfHexs[hexahedron_count]);
                    ListOfUgs[i]->InsertNextCell(VTK_HEXAHEDRON, ListOfHexs[hexahedron_count]->GetPointIds() );
                    ListOfMappers[i]->SetInputData(ListOfUgs[i]);
                    ListOfActors_hexahedron[hexahedron_count]->SetMapper(ListOfMappers[i]);

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

                    ListOfActors_hexahedron[hexahedron_count]->GetProperty()->SetColor(Red_remapped,Green_remapped,Blue_remapped);
                    renderer->AddActor(ListOfActors_hexahedron[hexahedron_count]);

                    ui->List_Of_Hexahedrons->addItem("Hexahedron " + (QString::number(hexahedron_count + 1)) );

                    HexPoly->SetPolys(HexCell);
                    ListOfPolydata.push_back(HexPoly);

                    hexahedron_count++;
                    /*
                    polydata->Initialize();
                    polydata->SetPolys(cellArray);
                    polydata->SetPolys(TriangleArray);
                    polydata->SetPoints(points);
                    QString NewSTLFilePath = QFileDialog::getSaveFileName(this, tr("Save File: "),
                                                                          "../../example_models/New stl file",tr("Stl (*.stl)"));
                    std::string STLFilePath = NewSTLFilePath.toUtf8().constData();
                    stlWriter->SetFileName(STLFilePath.c_str());
                    stlWriter->SetInputData(polydata);
                    stlWriter->Write();
*/

                }
            }

            polydata->Initialize();
            //polydata->SetPolys(cellArray);
            polydata->SetPolys(TriangleArray);
            polydata->SetPoints(points);

            QString NewSTLFilePath = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                                  "../../example_models/New stl file",tr("Stl (*.stl)"));
            std::string STLFilePath = NewSTLFilePath.toUtf8().constData();
            stlWriter->SetFileName(STLFilePath.c_str());
            stlWriter->SetInputData(polydata);
            stlWriter->Write();

            std::cout << polydata->GetNumberOfPolys() << std::endl;

            renderer->ResetCameraClippingRange();
            renderer->SetBackground( colors->GetColor3d("Black").GetData() );
            renderer->GetActiveCamera()->SetPosition(50.0 ,50.0, 50.0);
            renderer->GetActiveCamera()->SetFocalPoint(0.0 ,0.0, 0.0);

            orientationWidget->SetOrientationMarker( axes );
            orientationWidget->SetInteractor(ui->Display_Window->GetRenderWindow()->GetInteractor());
            orientationWidget->SetEnabled(1);
            orientationWidget->InteractiveOff();

            renderer->ResetCamera();
            renderWindow->Render();
        }
    }
}

void MainWindow::on_SaveModelButton_released()
{
    QMessageBox::critical(this, "Uncoded Error", "Save function has not been coded for");
}

void MainWindow::on_LoadLightsButton_released()
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

void MainWindow::on_SaveLightsButton_released()
{
    // This opens a Dialog box that sets the PATH and file name of the file to be saved
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Light File"),
                                                    "Light List",tr("Doc (*.txt)"));
    QFile file(fileName);

    std::streambuf *psbuf;
    auto *coutbuf = std::cout.rdbuf();
    std::ofstream filestr;
    filestr.open ((fileName.toStdString()));

    if (filestr.is_open())
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
    // This ensures a light has been created before t can be selected to be edited

    if(ui->Select_Light->currentIndex() > -1)
    {
        Edit_LightDialog =new Edit_Light(this);
        Edit_LightDialog->setWindowTitle(ListOfLights.at(ui->Select_Light->currentIndex()).GetName());
        Edit_LightDialog->show();
        Edit_LightDialog->Open_Dialog(ListOfLights.at(ui->Select_Light->currentIndex()),renderWindow );
    }
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
        QMessageBox::critical(this, "Runtime Error", "Cannot delete Camera Light instead turn it off");
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

void MainWindow::on_AddRulerPushButton_released()
{
    distanceWidget->SetInteractor(ui->Display_Window->GetRenderWindow()->GetInteractor());
    distanceWidget->CreateDefaultRepresentation();
    renderWindow->Render();
    distanceWidget->On();
}

void MainWindow::on_RemoveRulerPushButton_released()
{
    distanceWidget->Off();
    renderWindow->Render();
}

void MainWindow::on_Model_Statistics_released()
{
    if (LoadedFileType == false)
    {
        QMessageBox Statistics;
        Statistics.setWindowTitle("Model Statistics");
        QString Density = QString::number(ModelOne.Get_Weight()/ModelOne.Get_Volume());
        QString Volume =  QString::number(ModelOne.Get_Volume());
        QString Weight =  QString::number(ModelOne.Get_Weight());

        Vectors Centre_Of_Gravity = ModelOne.Get_Centre_Of_Gravity();
        QString COG = ("X: " +  QString::number(Centre_Of_Gravity.GetXVector()) + " " +
                       "Y: " +  QString::number(Centre_Of_Gravity.GetYVector()) + " " +
                       "Z: " +  QString::number(Centre_Of_Gravity.GetZVector()));

        Vectors Geometric_Centre = ModelOne.Get_Geometric_Centre();
        QString Geo_Centre = ("X: " +  QString::number(Geometric_Centre.GetXVector()) + " " +
                              "Y: " +  QString::number(Geometric_Centre.GetYVector()) + " " +
                              "Z: " +  QString::number(Geometric_Centre.GetZVector()));

        Vectors Overall_Dimensions = ModelOne.Get_Overall_Dimensions();
        QString Overall = ("X: " +  QString::number(Overall_Dimensions.GetXVector()) + " " +
                           "Y: " +  QString::number(Overall_Dimensions.GetYVector()) + " " +
                           "Z: " +  QString::number(Overall_Dimensions.GetZVector()));

        Statistics.setText( "Density: " + Density+ "\n\n" +
                            "Weight: "  + Weight + "\n\n" +
                            "Volume: "  + Volume + "\n\n" +
                            "Centre Of Gravity: " + COG + "\n\n" +
                            "Geometric Centre: " + Geo_Centre + "\n\n"
                                                                "Overall Dimensions: " + Overall);
        Statistics.exec();
    }
    else
    {
        QMessageBox::critical(this, "Runtime Error", "Model statiscs are only available for models loaded from .mod or .txt files");
    }
}

void MainWindow::on_Tetra_Highlight_stateChanged(int state)
{
    if (LoadedFileType == false)
    {
        if (state == 2)
        {
            ListOfActors_tetra[(ui->List_Of_Tetras->currentIndex())]->GetProperty()->GetColor(Temp_Tetra_color_red, Temp_Tetra_color_green, Temp_Tetra_color_blue);
            ListOfActors_tetra[(ui->List_Of_Tetras->currentIndex())]->GetProperty()->SetColor(Highlight_red, Highlight_green, Highlight_blue);
            ui->List_Of_Tetras->setEnabled(false);
            ui->Pyramid_Highlight->setCheckState(Qt::Unchecked);
            ui->Hexahedron_Highlight->setCheckState(Qt::Unchecked);
        }
        else
        {
            ListOfActors_tetra[(ui->List_Of_Tetras->currentIndex())]->GetProperty()->SetColor(Temp_Tetra_color_red, Temp_Tetra_color_green, Temp_Tetra_color_blue);
            ui->List_Of_Tetras->setEnabled(true);
        }
        renderWindow->Render();
    }
}

void MainWindow::on_Pyramid_Highlight_stateChanged(int state)
{
    if (LoadedFileType == false)
    {
        if (state == 2)
        {
            ListOfActors_pyramid[(ui->List_Of_Pyramids->currentIndex())]->GetProperty()->GetColor(Temp_Pyramid_color_red, Temp_Pyramid_color_green, Temp_Pyramid_color_blue);
            ListOfActors_pyramid[(ui->List_Of_Pyramids->currentIndex())]->GetProperty()->SetColor(Highlight_red, Highlight_green, Highlight_blue);
            ui->List_Of_Pyramids->setEnabled(false);
            ui->Tetra_Highlight->setCheckState(Qt::Unchecked);
            ui->Hexahedron_Highlight->setCheckState(Qt::Unchecked);
        }
        else
        {
            ListOfActors_pyramid[(ui->List_Of_Pyramids->currentIndex())]->GetProperty()->SetColor(Temp_Pyramid_color_red, Temp_Pyramid_color_green, Temp_Pyramid_color_blue);
            ui->List_Of_Pyramids->setEnabled(true);
        }
        renderWindow->Render();
    }
}

void MainWindow::on_Hexahedron_Highlight_stateChanged(int state)
{
    if (LoadedFileType == false)
    {
        if (state == 2)
        {
            ListOfActors_hexahedron[(ui->List_Of_Hexahedrons->currentIndex())]->GetProperty()->GetColor(Temp_Hexahedron_color_red, Temp_Hexahedron_color_green, Temp_Hexahedron_color_blue);
            ListOfActors_hexahedron[(ui->List_Of_Hexahedrons->currentIndex())]->GetProperty()->SetColor(Highlight_red, Highlight_green, Highlight_blue);
            ui->List_Of_Hexahedrons->setEnabled(false);
            ui->Tetra_Highlight->setCheckState(Qt::Unchecked);
            ui->Pyramid_Highlight->setCheckState(Qt::Unchecked);
        }
        else
        {
            ListOfActors_hexahedron[(ui->List_Of_Hexahedrons->currentIndex())]->GetProperty()->SetColor(Temp_Hexahedron_color_red, Temp_Hexahedron_color_green, Temp_Hexahedron_color_blue);
            ui->List_Of_Hexahedrons->setEnabled(true);
        }
        renderWindow->Render();
    }
}

void MainWindow::on_Highlight_released()
{
    QColor Color = QColorDialog::getColor(Qt::white,this,"Choose Color");
    //checks to ensure that the selector color is valid
    if(Color.isValid())
    {
        //converts the QColor to RGB values ranging from 0.0 through 1.0 to be used by SetColor function
        Highlight_red = Color.redF();
        Highlight_green = Color.greenF();
        Highlight_blue = Color.blueF();
        renderWindow->Render();
    }
}

void MainWindow::on_Cell_Statistics_released()
{
    if (LoadedFileType == false)
    {
        QMessageBox Statistics;
        if(ui->Tetra_Highlight->checkState() == 2)
        {
            Statistics.setWindowTitle("Highlight Tetrahedron Statistics");

            int Tetra_count = 0; // Needs to be int to match type of currentIndex() return

            for (unsigned int i = 0; i < ModelOne.Get_Cell_Order().size(); i++)
            {
                if (ModelOne.Get_Cell_Order()[i] == 't')
                {
                    if (Tetra_count == ui->List_Of_Tetras->currentIndex() )
                    {
                        auto *coutbuf = std::cout.rdbuf();
                        std::stringstream buffer;
                        std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());

                        Cell *Test = new Tetrahedron();
                        Test = ModelOne.Get_Cells()[i];

                        std::cout << Test->Get_Material() << std::endl;
                        std::string redirect = buffer.str();
                        std::cout.rdbuf(coutbuf);

                        QString Material = QString::fromStdString(redirect);
                        QString Density  = QString::number((Test->Get_Weight()/Test->Get_Volume() ));
                        QString Weight   = QString::number((Test->Get_Weight() ));
                        QString Volume   = QString::number((Test->Get_Volume() ));

                        Vectors Centre_Of_Gravity = Test->Get_Centre_Of_Gravity();
                        QString COG = ("X: " +  QString::number(Centre_Of_Gravity.GetXVector()) + " " +
                                       "Y: " +  QString::number(Centre_Of_Gravity.GetYVector()) + " " +
                                       "Z: " +  QString::number(Centre_Of_Gravity.GetZVector()));

                        std::vector<Vectors> Vertices = Test->Get_Vertices();

                        std::stringstream buffer_2;
                        std::streambuf *old_2 = std::cout.rdbuf(buffer_2.rdbuf());

                        for (unsigned int i = 0 ; i < 4 ; i++)
                        {
                            std::cout << Vertices[i] << std::endl;
                        }

                        std::string Tetra_Points = buffer_2.str();
                        std::cout.rdbuf(coutbuf);

                        QString Points = QString::fromStdString(Tetra_Points);

                        Statistics.setText( "Material: "+ Material+ "\n" +
                                            "Weight: "  + Weight  + "\n" +
                                            "Volume: "  + Volume  + "\n" +
                                            "Centre Of Gravity: " + COG  + "\n" +
                                            "Vectors:\n" + Points);
                        Statistics.exec();
                    }
                    Tetra_count++;
                }
            }
        }

        if(ui->Pyramid_Highlight->checkState() == 2)
        {
            Statistics.setWindowTitle("Highlight Pyramid Statistics");

            int Pyramid_count = 0; // Needs to be int to match type of currentIndex() return

            for (unsigned int i = 0; i < ModelOne.Get_Cell_Order().size(); i++)
            {
                if (ModelOne.Get_Cell_Order()[i] == 'p')
                {
                    if (Pyramid_count == ui->List_Of_Pyramids->currentIndex() )
                    {
                        auto *coutbuf = std::cout.rdbuf();
                        std::stringstream buffer;
                        std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());

                        Cell *Test = new Pyramid();
                        Test = ModelOne.Get_Cells()[i];

                        std::cout << Test->Get_Material() << std::endl;
                        std::string redirect = buffer.str();
                        std::cout.rdbuf(coutbuf);

                        QString Material = QString::fromStdString(redirect);
                        QString Density  = QString::number((Test->Get_Weight()/Test->Get_Volume() ));
                        QString Weight   = QString::number((Test->Get_Weight() ));
                        QString Volume   = QString::number((Test->Get_Volume() ));

                        Vectors Centre_Of_Gravity = Test->Get_Centre_Of_Gravity();
                        QString COG = ("X: " +  QString::number(Centre_Of_Gravity.GetXVector()) + " " +
                                       "Y: " +  QString::number(Centre_Of_Gravity.GetYVector()) + " " +
                                       "Z: " +  QString::number(Centre_Of_Gravity.GetZVector()));

                        std::vector<Vectors> Vertices = Test->Get_Vertices();

                        std::stringstream buffer_2;
                        std::streambuf *old_2 = std::cout.rdbuf(buffer_2.rdbuf());

                        for (unsigned int i = 0 ; i < 5 ; i++)
                        {
                            std::cout << Vertices[i] << std::endl;
                        }

                        std::string Pyramid_Points = buffer_2.str();
                        std::cout.rdbuf(coutbuf);

                        QString Points = QString::fromStdString(Pyramid_Points);

                        Statistics.setText( "Material: "+ Material+ "\n" +
                                            "Weight: "  + Weight  + "\n" +
                                            "Volume: "  + Volume  + "\n" +
                                            "Centre Of Gravity: " + COG  + "\n" +
                                            "Vectors:\n" + Points);
                        Statistics.exec();
                    }
                    Pyramid_count++;
                }
            }
        }

        if(ui->Hexahedron_Highlight->checkState() == 2)
        {
            Statistics.setWindowTitle("Highlight Hexahedron Statistics");

            int Hexahedron_count = 0; // Needs to be int to match type of currentIndex() return

            for (unsigned int i = 0; i < ModelOne.Get_Cell_Order().size(); i++)
            {
                if (ModelOne.Get_Cell_Order()[i] == 'h')
                {
                    if (Hexahedron_count == ui->List_Of_Hexahedrons->currentIndex() )
                    {
                        auto *coutbuf = std::cout.rdbuf();
                        std::stringstream buffer;
                        std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());

                        Cell *Test = new Hexahedron();
                        Test = ModelOne.Get_Cells()[i];

                        std::cout << Test->Get_Material() << std::endl;
                        std::string redirect = buffer.str();
                        std::cout.rdbuf(coutbuf);

                        QString Material = QString::fromStdString(redirect);
                        QString Density  = QString::number((Test->Get_Weight()/Test->Get_Volume() ));
                        QString Weight   = QString::number((Test->Get_Weight() ));
                        QString Volume   = QString::number((Test->Get_Volume() ));

                        Vectors Centre_Of_Gravity = Test->Get_Centre_Of_Gravity();
                        QString COG = ("X: " +  QString::number(Centre_Of_Gravity.GetXVector()) + " " +
                                       "Y: " +  QString::number(Centre_Of_Gravity.GetYVector()) + " " +
                                       "Z: " +  QString::number(Centre_Of_Gravity.GetZVector()));

                        std::vector<Vectors> Vertices = Test->Get_Vertices();

                        std::stringstream buffer_2;
                        std::streambuf *old_2 = std::cout.rdbuf(buffer_2.rdbuf());

                        for (unsigned int i = 0 ; i < 8 ; i++)
                        {
                            std::cout << Vertices[i] << std::endl;
                        }

                        std::string Hexahedron_Points = buffer_2.str();
                        std::cout.rdbuf(coutbuf);

                        QString Points = QString::fromStdString(Hexahedron_Points);

                        Statistics.setText( "Material: "+ Material+ "\n" +
                                            "Weight: "  + Weight  + "\n" +
                                            "Volume: "  + Volume  + "\n" +
                                            "Centre Of Gravity: " + COG  + "\n" +
                                            "Vectors:\n" + Points);
                        Statistics.exec();
                    }
                    Hexahedron_count++;
                }
            }
        }
    }
}
