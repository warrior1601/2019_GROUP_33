// filters.h
// Computing Project
// Created by Jedidiah Paterson on 02/22/2020.
// Copyright @ 2020 Jedidiah Paterson. All rights reserved.

/** @file filters.h This file contains a list of functions and variable that are connected
 * To the buttons on the filters.ui window. These functions apply filters to the
 * model that is present on the MainWindow. This file is
 * Designed to allow for future updates and additions to filtering functions
 * @author Jedidiah Paterson
 */

#ifndef FILTERS_H
#define FILTERS_H
// Header files from QT
#include <QDialog>
// Header files from vtk
#include <vtkClipDataSet.h>
#include <vtkDataSet.h>
#include <vtkDataSetMapper.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkNew.h>
#include <vtkPlane.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
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
    /** @brief This function is called from the parent window, this function is overloaded in other files.
     *  @param PassedFilterWindowOpenStatus ensures that only one window can be opened at a time.
     */
    void Open_Dialog(vtkSmartPointer<vtkSTLReader> &aReader,
                     vtkSmartPointer<vtkDataSetMapper> &aMapper,
                     vtkSmartPointer<vtkGenericOpenGLRenderWindow> &aWindow,
                     bool &PassedFilterWindowOpenStatus);

    /** @brief This function is call from the parent window, it allows for filtering when a reader is not available.
     * NOTE It is very important to return data back to orginal state before exiting the current filter.
     * @param PassedFilterWindowOpenStatus ensures that only one window can be opened at a time.
     */
    void Open_Dialog(std::vector<vtkSmartPointer<vtkDataSetMapper>> &aListOfMappers,
                     vtkSmartPointer<vtkGenericOpenGLRenderWindow> &aWindow,
                     bool &PassedFilterWindowOpenStatus);

private slots:
    /** @brief This function turns regular checkboxes into grouped radio buttons.
     * @param CheckBox_Number this number is required for the for the filter to know which case of the switch statement to enter.
     */
    void checked_Box_Status_Updater(int CheckBox_Number);
    /** @brief Turns on and off the shrink filter
     */
    void on_Shrink_Filter_toggled(bool Shrink_Filter_Status);
    /** @brief Turns on and off the clipper Filter
     */
    void on_Clipper_Filter_toggled(bool Clipper_Filter_Status);
    /** @brief This creates an X-coordinate in 3D space that initializes a plane where the clipping begins.
     */
    void on_X_Origin_valueChanged(int value);
    /** @brief This creates an Y-Coordinate in 3D space that initializes a plane where the clipping begins.
     */
    void on_Y_Origin_valueChanged(int value);
    /** @brief This creates an Z-Coordinate in 3D space that initializes a plane where the clipping begins.
     */
    void on_Z_Origin_valueChanged(int value);
    /** @brief Changes the direction of the clipping in the X-axis direction.
     */
    void on_X_Normal_valueChanged(int value);
    /** @brief Changes the direction of the clipping in the Y-axis direction.
     */
    void on_Y_Normal_valueChanged(int value);
    /** @brief Changes the direction of the clipping in the Z-axis direction.
     */
    void on_Z_Normal_valueChanged(int value);
    /** @brief Changes how much shrinking is applied to the model.
     */
    void on_Scale_valueChanged(int value);
    /** @brief Runs the close procedures for the filters window. Reverting the model and resetting the filter FilterWindowOpenStatus boolean.
     */
    void on_Close_clicked();
    /** @brief This is a standard close even for a window. This close event calls the function on_close_clicked()
     */
    void closeEvent(QCloseEvent *event);

private:
    Ui::Filters *ui; ///< @brief This it is the user interface.
    bool *FilterWindowOpenStatus; ///< @brief This tracks the window is open or not.
    bool FileTypeSTL = true; ///< @brief This bool tracks the file type loaded for Filtering

    // The smart pointers are created and only initilized when the open function is called
    // The smart pointers that are denoted by *_Local are overwritten by the  passed smart pointers
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow_Local = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New(); ///<@brief This is a locally created renderwindow that is overwriting by the renderwindow from the mainwindow
    vtkSmartPointer<vtkSTLReader> reader_Local = vtkSmartPointer<vtkSTLReader>::New(); ///< @brief This is a locally created reader that is overwriting by the reader from the mainwindow
    vtkSmartPointer<vtkDataSetMapper> mapper_Local = vtkSmartPointer<vtkDataSetMapper>::New(); ///< @brief This is a locally created mapper that is overwriting by the mapper from the mainwindow
    vtkSmartPointer<vtkRenderer> renderer_Local = vtkSmartPointer<vtkRenderer>::New(); ///< @brief This is a locally created renderer that is overwriting by the renderer from the mainwindow

    std::vector<vtkSmartPointer<vtkDataSetMapper>> ListOfMappers_Local; ///< @brief This is a list of all the Mappers, Each mapper hold one cell and has one actor acting in it. This allows for each cell to maintain its own colour while being filtered
    std::vector<vtkSmartPointer<vtkShrinkFilter>> ListOfShrink_Filters; ///< @brief This list of shrink filters each takes one input and has one output. Which is data from the mapper and back into the mapper. There is one filter for each mapper
    std::vector<vtkSmartPointer<vtkClipDataSet>> ListOfClipper_Filters; ///< @brief This list of cliper filters each takes one input and has one output. Which is data from the mapper and back into the mapper. There is one filter for each mapper

    vtkSmartPointer<vtkClipDataSet> Clipper_Filter = vtkSmartPointer<vtkClipDataSet>::New(); ///< @brief Required vtkSmartpointer for appling the clipper filter for more information visit https://vtk.org/doc/nightly/html/classvtkClipDataSet.html
    vtkSmartPointer<vtkShrinkFilter> Shrink_Filter = vtkSmartPointer<vtkShrinkFilter>::New(); ///< @brief Required vtkSmartpointer for appling the shrink filter for more information visit https://vtk.org/doc/nightly/html/classvtkShrinkFilter.html
    vtkSmartPointer<vtkPlane> planeLeft = vtkSmartPointer<vtkPlane>::New(); ///< @brief Required vtkSmartpointer for creating a plane that is used in the clipper filter for more information visit https://vtk.org/doc/nightly/html/classvtkPlane.html
};

#endif // FILTERS_H
