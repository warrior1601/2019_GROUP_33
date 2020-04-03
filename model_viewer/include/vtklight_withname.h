//--------------vtklight_withname.h--------------//


// vtklight_withname.h
// Worksheet 6 Computing Project
// Edited By Jedidiah Paterson on 02/22/2020
// Copyright @ 2020 Jedidiah Paterson. All rights reserved.
// This file contains members of a class of the same name.
// This class helps the users see what light they are editing
// Allowing them to name the light as the user se fit.

#ifndef VTKLIGHT_WITHNAME_H
#define VTKLIGHT_WITHNAME_H

#include <QString>

#include <vtkLight.h>
#include <vtkSmartPointer.h>

class vtkLight_WithName
{

public:
//--------------Constructors--------------//

      vtkLight_WithName() :
          light( vtkSmartPointer<vtkLight>::New() ), Name("Light_Name") {}
      
    vtkLight_WithName(const char * n,  vtkSmartPointer<vtkLight> l ) :
          light( l ), Name( n ) {}
//--------------Destructor--------------//

      ~vtkLight_WithName()  {}
// This function is public is called in MainWindow.cpp which allows
// Access to the name of the light

//--------------Special Member Functions--------------//
    void SetName(const QString & name );
// This function allows the name to be accessed

    QString GetName();
// This checks if the light is swithced ON or OFF

    Qt::CheckState Check_State();

// Overloaded function

    vtkLight_WithName operator=(const vtkLight_WithName& Copy);
    
    
// The vtkLight is pubic because it has its own accessor functions
// Found in vtkLight.h

    vtkSmartPointer<vtkLight> light;
    
private:
    QString Name;
};

#endif // VTKLIGHT_WITHNAME_H
