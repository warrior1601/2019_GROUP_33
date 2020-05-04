//--------------------mainwindow.cpp--------------------//

// MainWindow.cpp
// Computing Project
// Edited By Jedidiah Paterson on 02/22/2020.
// Copyright @ 2020 Jedidiah Paterson. All right reserved.
// This file loads an Image onto a GUI (Grapgical User Interface)
// Impleminting the function defined in MainWindow.h and connected
// To the buttons on MainWindow.ui

#include "mainwindow.h"
#include "ui_mainwindow.h"

//-------------Constructor------------//

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    // This Sets the RinderWindow to the *.ui files Widget named Display_Window
    ui->setupUi(this);
    ui->Display_Window->SetRenderWindow( renderWindow );

    QString fileName = "../example_models/Observer.stl";
    std::string FilePath = fileName.toUtf8().constData();
    std::ifstream myFile(FilePath);

    Init_CameraLight();

    reader->SetFileName(FilePath.data());
    mapper->SetInputConnection( reader->GetOutputPort() );
    reader->Update();
    actor->SetMapper(mapper);
    actor->GetProperty()->EdgeVisibilityOff();  //Turning this on would allow the user to see the triangels that make up the faces of an object
    actor->GetProperty()->SetColor( colors->GetColor3d("Red").GetData() ); //Using ColorSetNames header file you can set folors this way
    renderer->AddActor(actor);
    ui->Display_Window->GetRenderWindow()->AddRenderer( renderer );
    renderWindow->Render();
}
//--------------Destructor-------------//

MainWindow::~MainWindow()
{
    delete ui;
}
//-------Special Member Functions------//

void  MainWindow::Init_CameraLight()
{   //Clears all the lights when new model is loaded
    ListOfLights.clear();
    renderer->RemoveAllLights();
    //If you do not call update() on a combobox before calling clear() it could result in an error that crashes the program
    ui->Light_ComboBox->update();
    ui->Light_ComboBox->clear();
    //Adds a camera light
    vtkLight_WithName light;
    light.SetName("Camera Light");
    ListOfLights.push_back(light);
    ui->Light_ComboBox->addItem(light.GetName());
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
{   //Opens Dialog Box to allow the use to chose a color
    QColor Color = QColorDialog::getColor(Qt::white,this,"Choose Model Colour");
    //checks to ensure that the selector color is valid
    if(Color.isValid())
    {   //converts the QColor to RGB values ranging from 0.0 through 1.0 to be used by SetColor function
        double red = Color.redF();
        double green = Color.greenF();
        double blue = Color.blueF();
        if (LoadedFileType == true)
        {
            actor->GetProperty()->SetColor( red,green,blue );
        }
        else
        {
            vtkSmartPointer<vtkProperty> ModelColor = vtkSmartPointer<vtkProperty>::New();
            ModelColor->SetColor( red,green,blue );
            renderer->GetActors()->ApplyProperties(ModelColor);
        }
    }
    //rerenders the window after the color change
    renderWindow->Render();
}

void MainWindow::on_Add_Light_released()
{
    vtkLight_WithName light;
    light.SetName(InputQString());
    ListOfLights.push_back(light);
    //This checks to ensure a name has been given to the light
    //With out this check clicking the cancel button would cause the program to crash
    if(light.GetName().isEmpty() == false)
    {
        //This establishes default settings for an added light
        ui->Light_ComboBox->addItem(light.GetName());
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

void MainWindow::on_Light_ComboBox_editTextChanged(const QString &text)
{   //This will change the name of the light as the user edits the text in the Combo Box
    ListOfLights.at(ui->Light_ComboBox->currentIndex()).SetName(text);
    ui->Light_ComboBox->setItemText(ui->Light_ComboBox->currentIndex(),ListOfLights.at(ui->Light_ComboBox->currentIndex()).GetName());
}

QString MainWindow::InputQString()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Light Name"),
                                         tr("Light Name:"), QLineEdit::Normal,
                                         tr("Light Name"), &ok);
    if (ok && !text.isEmpty())
        return (text);
    //This keeps the window from crashing when nothing is returned from the input
    else
        return(0);
}

void MainWindow::on_Change_Back_Ground_Color_released()
{
    QColor Color = QColorDialog::getColor(Qt::white,this,"Choose Background Colour");
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
    double* CameraLocation = renderer->GetActiveCamera()->GetPosition();
    std::cout << "Camera Location: " << CameraLocation[0] << " " << CameraLocation[1] << " " << CameraLocation[2] << std::endl;
    renderer->ResetCamera();
    //attach camera loaction to the scroll bars need to get pitch, roll, azimuth, yaw, elevation from the camera
    ui->Horizontal_Shift->setValue(0);
    ui->Vertical_Shift->setValue(0);
    ui->X_Camera_Pos->setValue(0);
    ui->Y_Camera_Pos->setValue(0);
    ui->Z_Camera_Pos->setValue(0);
    renderWindow->Render();
}

void MainWindow::on_Apply_Filters_released()
{
    //This open a Modaless window which allows user interaction with the mainwindow while open but only allowing
    //One window open at a time
    if (LoadedFileType == true)
    {
        if (FilterWindowOpenStatus == false) //This is for stl files since filtering is different for each file type
        {
            FilterWindowOpenStatus = true;
            filters =new Filters(this);
            filters->setWindowTitle("Apply Filters");
            filters->show();
            filters->Open_Dialog(reader, mapper, renderWindow, FilterWindowOpenStatus);
        }
    }
    else //This is for MOD/TXT files.
    {
        FilterWindowOpenStatus = true;
        filters =new Filters(this);
        filters->setWindowTitle("Apply Filters");
        filters->show();
        filters->Open_Dialog(ListOfMappers, renderWindow, FilterWindowOpenStatus);
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
{   //This ensures no error occurs when there was a previously loaded model
    ui->Tetra_Highlight->setCheckState(Qt::Unchecked);
    ui->Pyramid_Highlight->setCheckState(Qt::Unchecked);
    ui->Hexahedron_Highlight->setCheckState(Qt::Unchecked);

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Model File"), "../example_models",
                                                    tr("Model Files(*.stl *.txt *.mod)"));
    std::string FilePath = fileName.toUtf8().constData();
    std::ifstream myFile(FilePath);

    if (myFile.is_open()) //Check if file has been opened sucessfully, if so returns true
    {
        ui->Display_Window->GetRenderWindow()->RemoveRenderer( renderer );
        //Initializes the orientationWidget so it can be used on different file types
        orientationWidget = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
        //Initializes the renderer so it can be used on different file types
        renderer = vtkSmartPointer<vtkRenderer>::New();

        //clearing all previous data ensures there is no overlap of images from one loaded file to the next
        ListOfMappers.clear();
        ListOfUgs.clear();
        ListOfActors_tetra.clear();
        ListOfActors_pyramid.clear();
        ListOfActors_hexahedron.clear();
        ListOfTriangles.clear();
        ui->List_Of_Pyramids->update();
        ui->List_Of_Pyramids->clear();
        ui->List_Of_Tetras->update();
        ui->List_Of_Tetras->clear();
        ui->List_Of_Hexahedrons->update();
        ui->List_Of_Hexahedrons->clear();
        Init_CameraLight(); //This need to be called again since the renderer has changed

        //finds the file extension
        std::size_t found = FilePath.find_last_of(".");
        std::cout << "File type is: " << FilePath.substr(found+1) << std::endl;
        std::string FileType = FilePath.substr(found+1);

        if(FileType.compare("stl") == 0 )
        {
            LoadedFileType = true;
            //Established the pipeline for rendering an image
            reader->SetFileName(FilePath.data());
            mapper->SetInputConnection( reader->GetOutputPort() );
            reader->Update();
            actor->SetMapper(mapper);
            actor->GetProperty()->EdgeVisibilityOff();  //Turning this on would allow the user to see the triangels that make up the faces of an object
            actor->GetProperty()->SetColor( colors->GetColor3d("Green").GetData() ); //Using ColorSetNames header file you can set folors this way
            renderer->AddActor(actor);
            ui->Display_Window->GetRenderWindow()->AddRenderer( renderer );
        }
        else if ((FileType.compare("txt") == 0 ) || (FileType.compare("mod")) == 0)
        {
            LoadedFileType = false;

            std::string currentLine;
            unsigned int tetra_count = 0;
            unsigned int pyramid_count = 0;
            unsigned int hexahedron_count = 0;
            unsigned int triangle_count = 0;
            //Initialiing data sets insures no data from previouly loaded files is present
            points->Initialize();
            TriangleArray->Initialize();
            Model Empty;
            ModelOne = Empty;
            ModelOne.Load_Model(FilePath);
            ui->Display_Window->GetRenderWindow()->AddRenderer( renderer );

            std::string col;
            std::stringstream testing;

            for (unsigned int i = 0; i < ModelOne.Get_Vectors().size(); i++)
            {
                //Loading of the vectors into points to be used by the stlwriter
                double Data[] = { ModelOne.Get_Vectors()[i].GetXVector(),
                                  ModelOne.Get_Vectors()[i].GetYVector(),
                                  ModelOne.Get_Vectors()[i].GetZVector()};
                points->InsertNextPoint(Data);
            }

            for (unsigned int i = 0; i < ModelOne.Get_Cell_Order().size(); i++)
            {   //This creates a Mapper for each cell. This is required so eaxh cell can have a different actor. Colour is the most used property of the actor in this project
                //But future upgrades will enable the the texture aspect of the actor
                vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
                ListOfMappers.push_back(mapper);

                vtkSmartPointer<vtkUnstructuredGrid> ug = vtkSmartPointer<vtkUnstructuredGrid>::New();
                ListOfUgs.push_back(ug);

                vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();

                Cell Test = *ModelOne.Get_Cells()[i];
                //After loading the cell we need to sort them by type. Then we can load the Vector points in the same order
                //As denoted by Cell.hpp
                if (ModelOne.Get_Cell_Order()[i] == 't')
                {
                    ListOfActors_tetra.push_back(actor);
                    ListOfUgs[i]->SetPoints(points);
                    vtkSmartPointer<vtkTetra> tetra = vtkSmartPointer<vtkTetra>::New();
                    ListOfTetras.push_back(tetra);
                    //Sets point ID for each point being loaded in the tetra
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

                    //After the Triangels are loaded the pipeline for rendering needs to be established
                    ListOfUgs[i]->InsertNextCell(tetra->GetCellType(), ListOfTetras[tetra_count]->GetPointIds());
                    ListOfMappers[i]->SetInputData(ListOfUgs[i]);
                    ListOfActors_tetra[tetra_count]->SetMapper(ListOfMappers[i]);

                    //This sets the colour from the material after it is remmapped it is applied to the actor
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
                    //This adds the cell to a Combo Box so that it can be selected for stats from a different button
                    ui->List_Of_Tetras->addItem("Tetrahedron "  + (QString::number(tetra_count + 1)) );

                    tetra_count++;
                }

                if (ModelOne.Get_Cell_Order()[i] == 'p')
                {
                    ListOfActors_pyramid.push_back(actor);
                    ListOfUgs[i]->SetPoints(points);
                    vtkSmartPointer<vtkPyramid> pyramid = vtkSmartPointer<vtkPyramid>::New();
                    ListOfPyramids.push_back(pyramid);

                    for (vtkIdType vtkId = 0; vtkId < 5; vtkId++)
                    {
                        ListOfPyramids[pyramid_count]->GetPointIds()->SetId(vtkId, vtkIdType (Test.Get_Vertices_Order()[vtkId]) );
                    }

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

                    pyramid_count++;
                }

                if (ModelOne.Get_Cell_Order()[i] == 'h')
                {

                    ListOfActors_hexahedron.push_back(actor);
                    ListOfUgs[i]->SetPoints(points);
                    vtkSmartPointer<vtkHexahedron> hex = vtkSmartPointer<vtkHexahedron>::New();
                    ListOfHexs.push_back(hex);

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

                    hexahedron_count++;
                }

                polydata->Initialize();
                polydata->SetPolys(TriangleArray);
                polydata->SetPoints(points);
            }
        }
        //This process is the same for both STL and MOD/TXT files
        renderer->ResetCameraClippingRange();
        renderer->SetBackground( colors->GetColor3d("Black").GetData() );
        renderer->GetActiveCamera()->SetPosition(50.0 ,50.0, 50.0);
        renderer->GetActiveCamera()->SetFocalPoint(0.0 ,0.0, 0.0);
        //This adds the X-Y-Z axis markers and moves them as the view point changes
        orientationWidget->SetOrientationMarker( axes );
        orientationWidget->SetInteractor(ui->Display_Window->GetRenderWindow()->GetInteractor());
        orientationWidget->SetEnabled(1);
        orientationWidget->InteractiveOff();

        renderer->ResetCamera();
        renderWindow->Render();
    }
}

void MainWindow::on_SaveModelButton_released()
{
    if (LoadedFileType == true)
    {   //Saveing an STL file is not needed at this point because there is no manipulation of STL data
        QMessageBox::critical(this, "Runtime Error", "Save function only works on models loaded from .MOD/.TXT files");
    }
    else
    {
        QString NewSTLFilePath = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                              "",tr("Stl (*.stl)"));
        std::string STLFilePath = NewSTLFilePath.toUtf8().constData();
        stlWriter->SetFileName(STLFilePath.c_str());
        //Established data input for the writer
        stlWriter->SetInputData(polydata);
        stlWriter->Write();
    }
}

void MainWindow::on_LoadLightsButton_released()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Light File"), "", tr("Doc(*.txt)"));
    std::string FilePath= fileName.toUtf8().constData();
    std::ifstream myFile(FilePath);

    if (myFile.is_open())
    {
        std::string currentLine;
        std::string OpenFileCheck("List Of Lights");
        getline (myFile,currentLine);
        if(currentLine.compare(OpenFileCheck) != 0)
        {
            QMessageBox::critical(this, "Loading Error", "File is not formatted correctly for loading");
            return;
        }

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
                ui->Light_ComboBox->addItem(light.GetName());
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
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Light File"),
                                                    "",tr("Doc (*.txt)"));
    QFile file(fileName);
    //This redirects the ostream so that the print self function can be diected to a file for saving
    std::streambuf *psbuf;
    auto *coutbuf = std::cout.rdbuf();
    std::ofstream filestr;
    filestr.open ((fileName.toStdString()));

    if (filestr.is_open())
    {   //This line will be the first line written in the file. Upon opening there will be a check for this line
        //If not then the file will be ignored
        psbuf = filestr.rdbuf(); //Get file's streambuf
        std::cout.rdbuf(psbuf);  //Assign streambuf to cout
        std::cout << "List Of Lights" << std::endl;
        for(int i = 0; i <ListOfLights.size(); i++)
        {
            vtkLight_WithName light = ListOfLights.at(i);
            QString Name = light.GetName();
            std::cout<< Name.toStdString() << std::endl;
            light.light->PrintSelf( std::cout , vtkIndent(5));
        }
        filestr.flush();
        filestr.close();
        std::cout.rdbuf(coutbuf); // IMPORTANT // Redirecting the buffer back to the ostream
    }
}

void MainWindow::on_Edit_Light_clicked()
{
    //This ensures a light has been created before it can be selected to be edited
    if(ui->Light_ComboBox->currentIndex() > -1)
    {
        Edit_LightDialog =new Edit_Light(this);
        Edit_LightDialog->setWindowTitle(ListOfLights.at(ui->Light_ComboBox->currentIndex()).GetName());
        Edit_LightDialog->show();
        Edit_LightDialog->Open_Dialog(ListOfLights.at(ui->Light_ComboBox->currentIndex()),renderWindow );
    }
}

void MainWindow::on_Delete_Light_released()
{   //There will be a recall of Deleted light function to recover
    //Accidentally deleted lights during the users current session
    int LightToDelete = ui->Light_ComboBox->currentIndex();
    if(ui->Light_ComboBox->currentIndex() > 0)
    {
        ui->Light_ComboBox->removeItem(ui->Light_ComboBox->currentIndex());
        ui->Light_ComboBox->update();
        renderer->RemoveLight(ListOfLights.at(LightToDelete).light);
        // ListOfLights.at(LightToDelete).light->SwitchOff();  // Code for future upgrade
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
    //Adds a distance widget (Ruler)
    distanceWidget = vtkSmartPointer<vtkDistanceWidget>::New();
    distanceWidget->SetInteractor(ui->Display_Window->GetRenderWindow()->GetInteractor());
    distanceWidget->CreateDefaultRepresentation();
    distanceWidget->On();
    renderWindow->Render();
}

void MainWindow::on_RemoveRulerPushButton_released()
{
    //Turns off the Ruler
    distanceWidget->Off();
    renderWindow->Render();
}

void MainWindow::on_Model_Statistics_released()
{   //This function only works on MOD/TXT files using Semester 1's Library's
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
}

void MainWindow::on_Tetra_Highlight_stateChanged(int state)
{   //This function only works on MOD/STL files. It highlights a selected file. Only one Cell of all types can be highlighted at a time
    if (LoadedFileType == false)
    {
      if(ListOfActors_tetra.size() != 0)
      {
        if (state == 2)
        {   //This stores the current value so that it can be set back to its original colour
            ListOfActors_tetra[(ui->List_Of_Tetras->currentIndex())]->GetProperty()->GetColor(Temp_Tetra_color_red, Temp_Tetra_color_green, Temp_Tetra_color_blue);
            ListOfActors_tetra[(ui->List_Of_Tetras->currentIndex())]->GetProperty()->SetColor(Highlight_red, Highlight_green, Highlight_blue);
            //This prevents the user from changing cells while a checkbox is checked.
            ui->List_Of_Tetras->setEnabled(false);
            // This ensures that the other checkboxes are unchecked. This prevents an error for ocurring
            ui->Pyramid_Highlight->setCheckState(Qt::Unchecked);
            ui->Hexahedron_Highlight->setCheckState(Qt::Unchecked);
        }
        else
        {   //Returns the cell to its original colour
            ListOfActors_tetra[(ui->List_Of_Tetras->currentIndex())]->GetProperty()->SetColor(Temp_Tetra_color_red, Temp_Tetra_color_green, Temp_Tetra_color_blue);
            ui->List_Of_Tetras->setEnabled(true);
        }
        renderWindow->Render();
      }
      else
        ui->Tetra_Highlight->setCheckState(Qt::Unchecked);
    }
    else
      ui->Tetra_Highlight->setCheckState(Qt::Unchecked);
}

void MainWindow::on_Pyramid_Highlight_stateChanged(int state)
{
    if (LoadedFileType == false)
    {
      if(ListOfActors_pyramid.size() != 0)
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
      else
        ui->Pyramid_Highlight->setCheckState(Qt::Unchecked);
    }
    else
      ui->Pyramid_Highlight->setCheckState(Qt::Unchecked);
}

void MainWindow::on_Hexahedron_Highlight_stateChanged(int state)
{
    if (LoadedFileType == false)
    {
      if(ListOfActors_hexahedron.size() != 0)
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
      else
        ui->Hexahedron_Highlight->setCheckState(Qt::Unchecked);
   }
    else
      ui->Hexahedron_Highlight->setCheckState(Qt::Unchecked);
}

void MainWindow::on_Highlight_released()
{
    if (LoadedFileType == false)
    {
        QColor Color = QColorDialog::getColor(Qt::white,this,"Choose Color");
        if(Color.isValid())
        {
            Highlight_red = Color.redF();
            Highlight_green = Color.greenF();
            Highlight_blue = Color.blueF();

            if (Qt::Checked == ui->Tetra_Highlight->checkState() )
              ListOfActors_tetra[(ui->List_Of_Tetras->currentIndex())]->GetProperty()->SetColor(Highlight_red, Highlight_green, Highlight_blue);

            if (Qt::Checked == ui->Pyramid_Highlight->checkState() )
              ListOfActors_pyramid[(ui->List_Of_Pyramids->currentIndex())]->GetProperty()->SetColor(Highlight_red, Highlight_green, Highlight_blue);

            if (Qt::Checked == ui->Hexahedron_Highlight->checkState() )
              ListOfActors_hexahedron[(ui->List_Of_Hexahedrons->currentIndex())]->GetProperty()->SetColor(Highlight_red, Highlight_green, Highlight_blue);

            renderWindow->Render();
        }
    }
}

void MainWindow::on_Cell_Statistics_released()
{   //This function only works on MOD/TXT files
    if (LoadedFileType == false)
    {
        QMessageBox Statistics;
        if(ui->Tetra_Highlight->checkState() == 2)
        {
            Statistics.setWindowTitle("Highlight Tetrahedron Statistics");
            int Tetra_count = 0; // Needs to be int to match type of currentIndex() return value

            for (unsigned int i = 0; i < ModelOne.Get_Cell_Order().size(); i++)
            {
                if (ModelOne.Get_Cell_Order()[i] == 't')
                {
                    if (Tetra_count == ui->List_Of_Tetras->currentIndex() )
                    {
                        //Redirecting the ostream works well in this case because custom std::cout functions where
                        //written for each class Cell, Vectors, and Material
                        auto *coutbuf = std::cout.rdbuf();
                        std::stringstream buffer;
                        std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());

                        Cell *Test = new Tetrahedron(); // Creating a cell of a type is needed here in order to use it overloaded functions
                        Test = ModelOne.Get_Cells()[i];

                        std::cout << Test->Get_Material() << std::endl;
                        std::string redirect = buffer.str();
                        std::cout.rdbuf(coutbuf);  //IMPORTANT // Redirecting the buffer back to the ostream

                        QString Material = QString::fromStdString(redirect);
                        QString Density  = QString::number((Test->Get_Weight()/Test->Get_Volume() ));
                        QString Weight   = QString::number((Test->Get_Weight() ));
                        QString Volume   = QString::number((Test->Get_Volume() ));

                        Vectors Centre_Of_Gravity = Test->Get_Centre_Of_Gravity();
                        QString COG = ("X: " +  QString::number(Centre_Of_Gravity.GetXVector()) + " " +
                                       "Y: " +  QString::number(Centre_Of_Gravity.GetYVector()) + " " +
                                       "Z: " +  QString::number(Centre_Of_Gravity.GetZVector()));

                        std::vector<Vectors> Vertices = Test->Get_Vertices();
                        //Strickly two stream buffers might not be needed but if the buffer is flushed after each use
                        //Doing it this way helps keep it clear what data belongs to each buffer
                        std::stringstream buffer_2;
                        std::streambuf *old_2 = std::cout.rdbuf(buffer_2.rdbuf());

                        for (unsigned int i = 0 ; i < 4 ; i++)
                        {
                            std::cout << Vertices[i] << std::endl;
                        }

                        std::string Tetra_Points = buffer_2.str();
                        std::cout.rdbuf(coutbuf);  //IMPORTANT // Redirecting the buffer back to the ostream

                        QString Points = QString::fromStdString(Tetra_Points);

                        Statistics.setText( "Material: "+ Material+ "\n" +
                                            "Weight: "  + Weight  + "\n" +
                                            "Volume: "  + Volume  + "\n" +
                                            "Centre Of Gravity: " + COG  + "\n" +
                                            "Vectors:\n" + Points);
                        Statistics.exec(); //This window must be closed before the user can interact withthe rest of the program
                    }
                    Tetra_count++;
                }
            }
        }

        if(ui->Pyramid_Highlight->checkState() == 2)
        {   //Same as Tetra but with Pyramid cell functions
            Statistics.setWindowTitle("Highlight Pyramid Statistics");

            int Pyramid_count = 0;

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

                        for (unsigned int i = 0 ; i < Vertices.size() ; i++)
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
        {   //Same as Tetra but with Hexahedron cell functions
            Statistics.setWindowTitle("Highlight Hexahedron Statistics");

            int Hexahedron_count = 0;

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

                        for (unsigned int i = 0 ; i < Vertices.size() ; i++)
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

void MainWindow::on_showAxes_released()
{
    if (LoadedFileType == true)
    {   //Finds the boundaries for a STL file
        AxesActor->SetBounds(actor->GetBounds());
    }
    else
    {   //Finds the boundaries for the polydata loaded from teh MOD/TXT file
        AxesActor->SetBounds(polydata->GetBounds());
    }
    AxesActor->SetCamera(renderer->GetActiveCamera());

    //Shows the grid
    AxesActor->DrawXGridlinesOn();
    AxesActor->DrawYGridlinesOn();
    AxesActor->DrawZGridlinesOn();

    //Sets the axes colour as white.Future upgrade should allow the user to change this colour
    AxesActor->GetXAxesGridlinesProperty()->SetColor(0.5,0.5,0.5);
    AxesActor->GetYAxesGridlinesProperty()->SetColor(0.5,0.5,0.5);
    AxesActor->GetZAxesGridlinesProperty()->SetColor(0.5,0.5,0.5);

    AxesActor->XAxisMinorTickVisibilityOff();
    AxesActor->YAxisMinorTickVisibilityOff();
    AxesActor->ZAxisMinorTickVisibilityOff();

    //Sets the grid line location
    AxesActor->SetGridLineLocation(2);

    renderer->AddActor(AxesActor);
    renderWindow->Render();
}

void MainWindow::on_deleteshowAxes_released()
{
    renderer->RemoveActor(AxesActor);
    renderWindow->Render();
}
