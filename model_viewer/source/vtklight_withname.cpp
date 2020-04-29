//-----vtklight_withname.cpp--------------//
// vtklight_withname.cpp
// Computing Project
// Edited By Jedidiah Paterson on 02/22/2020
// Copyright @ 2020 Jedidiah Paterson. All rights reserved.
// This file contains the defined functions that are found in vtklight_withname.h

#include <QInputDialog>
#include <QString>

#include "vtklight_withname.h"

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

Qt::CheckState vtkLight_WithName::Check_State()
{
    bool State = light->GetSwitch();

    if (State == true)
        return Qt::Checked;
    else
        return Qt::Unchecked;
}
