#ifndef VTKLIGHT_WITHNAME_H
#define VTKLIGHT_WITHNAME_H

#include <QString>

#include <vtkLight.h>
#include <vtkSmartPointer.h>

class vtkLight_WithName
{

public:
      vtkLight_WithName() :
          Name("Light_Name"), light( vtkSmartPointer<vtkLight>::New()) {}
      vtkLight_WithName(const char * n,  vtkSmartPointer<vtkLight> l ) :
          Name( n ), light( l ) {}
      ~vtkLight_WithName()  {}

    void SetName(const QString & name );
    QString GetName();
    vtkLight_WithName operator=(const vtkLight_WithName& Copy);
    vtkSmartPointer<vtkLight> light;
private:
    QString Name;

};

#endif // VTKLIGHT_WITHNAME_H
