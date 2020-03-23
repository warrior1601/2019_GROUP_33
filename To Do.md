---Jedidiah---
finish the doxygen comment for semester 2
automate test code testing :nerd_face: Working on this one starting 21/3/2020

QT/VTK objectives - need a measuring tool, ability to select cells, Display stats. of Model and individual cells, a few VTK widgets  <-- Jedidiah
- Mainwindow line 160 unused variable CameraLocation
- Filters line 51 gives warning - but not used as Open_Dialog is used
- I get the following error that cause the build to fail: (do you get that)?

Undefined symbols for architecture x86_64:
  "Cell::Get_Material()", referenced from:
      MainWindow::on_actionOpen_triggered() in mainwindow.o
  "Cell::Get_Vertices_Order()", referenced from:
      MainWindow::on_actionOpen_triggered() in mainwindow.o
  "Cell::~Cell()", referenced from:
      MainWindow::on_actionOpen_triggered() in mainwindow.o
  "Model::Load_Model(std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > const&)", referenced from:
      MainWindow::on_actionOpen_triggered() in mainwindow.o
  "Model::Get_Vectors()", referenced from:
      MainWindow::on_actionOpen_triggered() in mainwindow.o
  "Model::Get_Cell_Order()", referenced from:
      MainWindow::on_actionOpen_triggered() in mainwindow.o
  "Model::Get_Cells()", referenced from:
      MainWindow::on_actionOpen_triggered() in mainwindow.o
  "Model::Model()", referenced from:
      MainWindow::on_actionOpen_triggered() in mainwindow.o
  "Model::~Model()", referenced from:
      MainWindow::on_actionOpen_triggered() in mainwindow.o
  "Vectors::GetXVector()", referenced from:
      MainWindow::on_actionOpen_triggered() in mainwindow.o
  "Vectors::GetYVector()", referenced from:
      MainWindow::on_actionOpen_triggered() in mainwindow.o
  "Vectors::GetZVector()", referenced from:
      MainWindow::on_actionOpen_triggered() in mainwindow.o
  "Vectors::~Vectors()", referenced from:
      std::__1::allocator<Vectors>::destroy(Vectors*) in mainwindow.o
  "Material::GetColour()", referenced from:
      MainWindow::on_actionOpen_triggered() in mainwindow.o
  "Material::~Material()", referenced from:
      MainWindow::on_actionOpen_triggered() in mainwindow.o
  "vtable for Cell", referenced from:
      Cell::Cell(Cell const&) in mainwindow.o
  NOTE: a missing vtable usually means the first non-inline virtual member function has no definition.
ld: symbol(s) not found for architecture x86_64
clang: error: linker command failed with exit code 1 (use -v to see invocation)

Clean up code and make sure all indented nicely and commented + model_viewer cmakelist

---Junaid---
Root readme file then macos readme update and intro update
Windows installer + moving dlls + moving example files + shortcut to desktop + icon file
macos installer + moving dlls + moving example files + icon file

extension:
- IMAGE_PATH for doxy_images to model/images/
- generateDocumentationAndDeploy.h comments  and tetra to triangle test.txt model delete
- link the model_viewer CMakeList with model cmakelist
- cmake list in root directory
- build model_viewer in travis ci for testing (QTest) (model_viewer test code)

delete to do
