//--------------------edit_light.h--------------------//
//Computing Project
//Created by Jedidiah Paterson on 02/22/2020.
//Copyright @ 2020 Jedidiah Paterson. All rights reserved.

/** @file This file contains a list of functions and variable that are connected
 * to the buttons on the edit_light.ui window. These function on the object
 * that is presented on MainWindow. This file is designed to allow for future updates
 * and additions.
 * @author Jedidiah Paterson
 */

#ifndef EDIT_LIGHT_H
#define EDIT_LIGHT_H
// Header files from QT
#include <QDialog>
// Header files from vtk
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkRenderer.h>
// Project header files
#include "vtklight_withname.h"

namespace Ui {
class Edit_Light;
}

/** @class Edit_Light edit_light.h "edit_light.h"
 *  @brief The Edit_Light class enables the user to adjust light settings. Many instences of this dialog box can be opened at one time.
 *  This enbles the user to edit a single light from each dialog box. Future upgrades will ensure that only one dialog box can be opened per light.
 */
class Edit_Light : public QDialog
{
    Q_OBJECT
public:
    /** @brief Blank construtor
     */
    explicit Edit_Light(QWidget *parent = nullptr);
    /** @brief Blank destructor
     */
    ~Edit_Light();
    /** @brief This function enables the rendering process fron a second window
     */
    void Open_Dialog(vtkLight_WithName &l, vtkSmartPointer<vtkGenericOpenGLRenderWindow> &PassedWindow);

private slots:
    /** @brief This function allows the cone angle to be changed on a light
     */
    void on_Light_Cone_Angle_valueChanged(int value);
    /** @brief This function allows the light intensity to be change on a light
     */
    void on_Light_Intensity_valueChanged(int value);
    /** @brief This function allows the specular light colour to be change on a light
     */
    void on_Specular_Colour_released();
    /** @brief This function allows the diffuse light colour to be change on a light
     */
    void on_Diffuse_Colour_released();
    /** @brief This function allows the ambient light colour to be change on a light
     */
    void on_Ambient_Colour_released();
    /** @brief This function allows for the X-coordinate of the origin of the light to be changed
     */
    void on_Light_X_Coordinate_Origin_valueChanged(int arg1);
    /** @brief This function allows for the Y-coordinate of the origin of the light to be changed
     */
    void on_Light_Y_Coordinate_Origin_valueChanged(int arg1);
    /** @brief This function allows for the Z-coordinate of the origin of the light to be changed
     */
    void on_Light_Z_Coordinate_Origin_valueChanged(int arg1);
    /** @brief This function allows for the X-coordinate of the focal of the light to be changed
     */
    void on_Light_X_Coordinate_Focal_Point_valueChanged(int arg1);
    /** @brief This function allows for the Y-coordinate of the focal of the light to be changed
     */
    void on_Light_Y_Coordinate_Focal_Point_valueChanged(int arg1);
    /** @brief This function allows for the Z-coordinate of the focal of the light to be changed
     */
    void on_Light_Z_Coordinate_Focal_Point_valueChanged(int arg1);
    /** @brief Toggles the light On/Off
     */
    void on_Light_Switch_toggled(bool checked);

private:
    Ui::Edit_Light *ui; ///< @brief This is the user interface
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow =vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New(); ///< @brief This allows the MainWindow to be rendered from the edit light dialog box
    vtkLight_WithName *light_Local; ///< @brief This allow the editing of the light to take place, only for the selected light that is in the title of the Edit Light dialog box
};

#endif // EDIT_LIGHT_H
