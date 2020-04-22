//--------------------filters.h --------------------//
#ifndef FILTERS_H
#define FILTERS_H


// filters.h
// Worksheet 6 Computing Project
// Edited By Jedidiah Paterson on 02/22/2020.
// Copyright @ 2020 Jedidiah Paterson. All rights reserved.
// This file contains a list of functions and variable that are connected
// To the buttons on the filters.ui window. These function all the object
// That is presentedon MainWindow.ui to be manipluated. This file is
// Desgined to allow for future updates and addtions to filtering functions

#include <QDialog>

#include <vtkClipDataSet.h>
#include <vtkDataSetMapper.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkNew.h>
#include <vtkPlane.h>
#include <vtkPolyData.h>
#include <vtkShrinkFilter.h>
#include <vtkSTLReader.h>
#include <vtkSmartPointer.h>


namespace Ui {
class Filters;
}

class Filters : public QDialog
{
    Q_OBJECT

public:
// Constructor

    explicit Filters(QWidget *parent = nullptr);
// Destructor

    ~Filters();
// Overloaded function found in other files. Without this function
// MainWindow will not be able to be updated from the filters page.
// The Open function is called from the MainWindow.cpp file

    void Open_Dialog(vtkSmartPointer<vtkSTLReader> &Passedreader,
              vtkSmartPointer<vtkDataSetMapper> &Passmapper,
              vtkSmartPointer<vtkGenericOpenGLRenderWindow> &PassedWindow,
              bool &PassedFilterWindowOpenStatus);

private slots:

// This function ensures that only one checkBox can be checked at a time.

    void checked_Box_Status_Updater(int CheckBox_Number);

// This functionsare connected to SIGNALS and SLOTS that are triggered on the filters.ui
// Interface

    void on_Shrink_Filter_toggled(bool Shrink_Filter_Status);
    void on_Clipper_Filter_toggled(bool Clipper_Filter_Status);
    void on_X_Origin_valueChanged(int value);
    void on_Y_Origin_valueChanged(int value);
    void on_Z_Origin_valueChanged(int value);
    void on_X_Normal_valueChanged(int value);
    void on_Y_Normal_valueChanged(int value);
    void on_Z_Normal_valueChanged(int value);
    void on_Scale_valueChanged(int value);
    void on_Close_clicked();

private:
    Ui::Filters *ui;
    bool *FilterWindowOpenStatus;

// The smart pointers are created and only initilized when the open function is called
// The smaprt pointer that are over written are denoted by *_Local and *_Revert to return the model to its
// Original settings when the window closes.

    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow_Local = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    vtkSmartPointer<vtkSTLReader> reader_Local = vtkSmartPointer<vtkSTLReader>::New();
    vtkSmartPointer<vtkDataSetMapper> mapper_Local = vtkSmartPointer<vtkDataSetMapper>::New();
    std::vector<vtkSmartPointer<vtkDataSetMapper>> ListOfMappers_Local;

    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow_Revert = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    vtkSmartPointer<vtkSTLReader> reader_Revert = vtkSmartPointer<vtkSTLReader>::New();
    vtkSmartPointer<vtkDataSetMapper> mapper_Revert = vtkSmartPointer<vtkDataSetMapper>::New();
// These are filter specific smart pointers

    vtkSmartPointer<vtkClipDataSet> Clipper_Filter = vtkSmartPointer<vtkClipDataSet>::New();
    vtkSmartPointer<vtkShrinkFilter> Shrink_Filter = vtkSmartPointer<vtkShrinkFilter>::New();
    vtkSmartPointer<vtkPlane> planeLeft = vtkSmartPointer<vtkPlane>::New();
};

#endif // FILTERS_H
