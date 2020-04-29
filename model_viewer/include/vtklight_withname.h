//--------------vtklight_withname.h--------------//
// Computing Project
// Created By Jedidiah Paterson on 02/22/2020
// Copyright @ 2020 Jedidiah Paterson. All rights reserved.
/** @file This file contains members of a class of the same name.
 * This class helps the users see what light they are editing
 * Allowing them to name the light as the user se fit.
 * @author Jedidiah Paterson
 */

#ifndef VTKLIGHT_WITHNAME_H
#define VTKLIGHT_WITHNAME_H
// Header files from QT
#include <QString>
// Header files from vtk
#include <vtkLight.h>
#include <vtkSmartPointer.h>

class vtkLight_WithName
{

public:
    //--------------Constructors--------------//
    /** @brief Blank Constuctor initilizes a vtkLight_WithName with two members
     * First member is the vtkLight and the Second Member is a string with the
     * defualt setting as "Light_Name"
     */
    vtkLight_WithName() :
        light( vtkSmartPointer<vtkLight>::New() ), Name("Light_Name") {}
    /**
     * @brief Non-Blank Constuctor
     */
    vtkLight_WithName(const char * n,  vtkSmartPointer<vtkLight> l ) :
        light( l ), Name( n ) {}
    //--------------Destructor--------------//
    /** @brief Blank destructor (empty)
     */
    ~vtkLight_WithName()  {}
    // This function is public is called in MainWindow.cpp which allows
    // Access to the name of the light

    //--------------Special Member Functions--------------//
    /** @brief This function allows the private member name to be set
     */
    void SetName(const QString & name );
    // This function allows the name to be accessed
    /** @brief Gets the string that allows the name to be used and displayed in a list
     */
    QString GetName();
    // This checks if the light is swithced ON or OFF
    /** @brief This function allows the access to the On/Off state of the light so it can be turned on or off from the ui
     */
    Qt::CheckState Check_State();
    // Overloaded function
    /** @brief This allows for a light to be copied. This is currently not implimited but future releases of the program will allow the user to make copies of lights they have created
     */
    vtkLight_WithName operator=(const vtkLight_WithName& Copy);
    // The vtkLight is pubic because it has its own accessor functions
    // Found in vtkLight.h
    vtkSmartPointer<vtkLight> light; ///< @brief All information about vtkLight can be found at https://vtk.org/doc/nightly/html/classvtkLight.html
    
private:
    QString Name; ///< @brief This is the name of the light. This allows the user to recognize their lights by their own implementation
};

#endif // VTKLIGHT_WITHNAME_H
