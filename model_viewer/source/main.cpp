// main.cpp-------------------------------------------------------------------
#include <QApplication>
#include <QSurfaceFormat>
#include <QVTKOpenGLWidget.h>
#include <windows.h>
#include "mainwindow.h"

int main( int argc, char** argv )
{
  //This hides the console window for the final applicaation
  FreeConsole();
  // needed to ensure appropriate OpenGL context is created for VTK rendering.
  QSurfaceFormat::setDefaultFormat( QVTKOpenGLWidget::defaultFormat() );

  QApplication a( argc, argv );

  MainWindow window;
  window.show();
  return a.exec();
}
// /main.cpp------------------------------------------------------------------
