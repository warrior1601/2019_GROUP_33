#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStatusBar>
#include <vtkRenderer.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <QMessageBox>
#include <QDialog>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <vtkSTLReader.h>
//#include <vtkPlane.h>
//#include <vtkClipDataSet.h>
#include <vtkDataSetMapper.h>
//#include <vtkShrinkFilter.h>
#include "edit_light.h"
#include "filters.h"
#include <QString>
#include <vector>

#include <vtkLight.h>
#include "vtklight_withname.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void statusUpdateMessage( const QString & message, int timeout );

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_Change_Object_Color_released();
    void on_Add_Light_released();
    void on_Change_Back_Ground_Color_released();
    void on_Reset_Camera_released();
    void on_Apply_Filters_released();
    void on_X_Camera_Pos_valueChanged(int value);
    void on_Y_Camera_Pos_valueChanged(int value);
    void on_Z_Camera_Pos_valueChanged(int value);
    void on_Vertical_Shift_valueChanged(int arg1);
    void on_Horizontal_Shift_valueChanged(int arg1);
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_Edit_Light_clicked();
    void on_Delete_Light_released();

private:
    Ui::MainWindow *ui;
    Edit_Light *SecondDialog;
    Filters *filters;
    QString SetLightName();
    std::vector<vtkLight_WithName> ListOfLights;
    vtkSmartPointer<vtkNamedColors> colors = vtkSmartPointer<vtkNamedColors>::New();
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    vtkSmartPointer<vtkSTLReader> reader = vtkSmartPointer<vtkSTLReader>::New();
    vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
};

#endif // MAINWINDOW_H
