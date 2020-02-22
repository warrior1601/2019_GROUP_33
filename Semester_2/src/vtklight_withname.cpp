#include "vtklight_withname.h"

#include <QInputDialog>
#include <QString>

void vtkLight_WithName::SetName(const QString & name)
{
    this->Name = name;
}

QString vtkLight_WithName::GetName()
{
    return this->Name;

}

vtkLight_WithName vtkLight_WithName::operator=(const vtkLight_WithName &Copy)
{
    this->Name = Copy.Name;
    this->light = Copy.light;

    return (*this);
}
