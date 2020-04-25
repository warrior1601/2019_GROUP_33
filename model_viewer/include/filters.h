//filters.h
//Computing Project
//Created by Jedidiah Paterson on 02/22/2020.
// Copyright @ 2020 Jedidiah Paterson. All rights reserved.

/** @file This file contains a list of functions and variable that are connected
 * To the buttons on the filters.ui window. These functions apply filters to the
 * model that is present on the MainWindow. This file is
 * Desgined to allow for future updates and addtions to filtering functions
 * @author Jedidiah Paterson
 */

#ifndef FILTERS_H
#define FILTERS_H
// Header files from QT
#include <QDialog>
// Header files from vtk
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

/** @class Filters filters.h "fitlers.h"
 *  @brief The Filters class enables the model to be manipulated. Revertering all changes when the window is closed
 */
class Filters : public QDialog
{
    Q_OBJECT

public:
    //Constructor
    /** @brief Blank constuctor (empty)
     */
    explicit Filters(QWidget *parent = nullptr);
    //Destructor
    /** @brief Blank destructor (empty)
     */
    ~Filters();
    /**
     * @brief This function is called from the parent window, this function is overloaded in other files.
     * @param PassedFilterWindowOpenStatus this ensures that only one window can be opened at a time.
     */
    void Open_Dialog(vtkSmartPointer<vtkSTLReader> &aReader,
                     vtkSmartPointer<vtkDataSetMapper> &aMapper,
                     vtkSmartPointer<vtkGenericOpenGLRenderWindow> &aWindow,
                     bool &PassedFilterWindowOpenStatus);

private slots:
    /**
     * @brief This function turns regular checkboxes into grouped radio buttons.
     * @param CheckBox_Number this number is required for the for the filter to know which case of the switch statement to enter.
     */
    void checked_Box_Status_Updater(int CheckBox_Number);
    /**
     * @brief Turns on and off the Shrink filter
     */
    void on_Shrink_Filter_toggled(bool Shrink_Filter_Status);
    /**
     * @brief Turns on and off the Clipper Filter
     */
    void on_Clipper_Filter_toggled(bool Clipper_Filter_Status);
    /**
     * @brief This creates an X-Coordinate in 3D space that initializes a plane where the clipping begins.
     */
    void on_X_Origin_valueChanged(int value);
    /**
     * @brief This creates an Y-Coordinate in 3D space that initializes a plane where the clipping begins.
     */
    void on_Y_Origin_valueChanged(int value);
    /**
     * @brief This creates an Z-Coordinate in 3D space that initializes a plane where the clipping begins.
     */
    void on_Z_Origin_valueChanged(int value);
    /**
     * @brief Changes the direction of the clipping in the X-Axis direction.
     */
    void on_X_Normal_valueChanged(int value);
    /**
     * @brief Changes the direction of the clipping in the Y-Axis direction.
     */
    void on_Y_Normal_valueChanged(int value);
    /**
     * @brief Changes the direction of the clipping in the Z-Axis direction.
     */
    void on_Z_Normal_valueChanged(int value);
    /**
     * @brief Changes how much shrinking is applied to the model.
     */
    void on_Scale_valueChanged(int value);
    /**
     * @brief Runs the close procedures for the Filters window. Reverting the model and resetting the Filter Window Open Status.
     */
    void on_Close_clicked();
    /** @brief This is a standard close even for a window. inside of this close even calls the function on_close_clicked()
     */
    void closeEvent(QCloseEvent *event);

private:
    Ui::Filters *ui;          ////< @brief This it is the user interface.
    bool *FilterWindowOpenStatus;          ////< @brief This tracks the window is open or not.

    // The smart pointers are created and only initilized when the open function is called
    // The smart pointers are denoted by *_Local
    // *_Local smart pointers are overwritten by the  passed smart pointers

    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow_Local = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New(); ////< This is a locally created renderwindow that is overwriting by the renderwindow from the mainwindow
    vtkSmartPointer<vtkSTLReader> reader_Local = vtkSmartPointer<vtkSTLReader>::New(); ///< @brief This is a locally created reader that is overwriting by the renderwindow from the mainwindow
    vtkSmartPointer<vtkDataSetMapper> mapper_Local = vtkSmartPointer<vtkDataSetMapper>::New(); ///< @brief This is a locally created mapper that is overwriting by the renderwindow from the mainwindow

    vtkSmartPointer<vtkClipDataSet> Clipper_Filter = vtkSmartPointer<vtkClipDataSet>::New(); ///< @brief Required vtkSmartpointer for appling the Clipper Filter
    vtkSmartPointer<vtkShrinkFilter> Shrink_Filter = vtkSmartPointer<vtkShrinkFilter>::New(); ///< @brief Required vtkSmartpointer for appling the Shrink Filter
    vtkSmartPointer<vtkPlane> planeLeft = vtkSmartPointer<vtkPlane>::New(); ///< @brief Required vtkSmartpointer for creating a plane that is used in the Clipper Filter
};

#endif // FILTERS_H
