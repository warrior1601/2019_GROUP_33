#ifndef FILTERS_H
#define FILTERS_H

#include <QDialog>

#include <vtkClipDataSet.h>
#include <vtkDataSetMapper.h>
#include <vtkShrinkFilter.h>

#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkNew.h>
#include <vtkPlane.h>
#include <vtkSTLReader.h>
#include <vtkSmartPointer.h>


namespace Ui {
class Filters;
}

class Filters : public QDialog
{
    Q_OBJECT

public:
    explicit Filters(QWidget *parent = nullptr);
    ~Filters();

    void open(vtkSmartPointer<vtkSTLReader> &Passedreader,
              vtkSmartPointer<vtkDataSetMapper> &Passmapper,
              vtkSmartPointer<vtkGenericOpenGLRenderWindow> &PassedWindow);

private slots:

    void on_Shrink_Filter_toggled(bool checked);
    void on_Clipper_Filter_toggled(bool checked);
    void on_X_valueChanged(int value);
    void on_Y_valueChanged(int value);
    void on_Z_valueChanged(int value);

private:
    Ui::Filters *ui;
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow_Local = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    vtkSmartPointer<vtkSTLReader> reader_Local = vtkSmartPointer<vtkSTLReader>::New();
    vtkSmartPointer<vtkDataSetMapper> mapper_Local = vtkSmartPointer<vtkDataSetMapper>::New();
    vtkSmartPointer<vtkClipDataSet> Clipper_Filter = vtkSmartPointer<vtkClipDataSet>::New();
    vtkSmartPointer<vtkShrinkFilter> Shrink_Filter = vtkSmartPointer<vtkShrinkFilter>::New();
    vtkSmartPointer<vtkPlane> planeLeft = vtkSmartPointer<vtkPlane>::New();

};

#endif // FILTERS_H
