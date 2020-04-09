#ifndef TRANSFO_H
#define TRANSFO_H

#include <QDialog>
#include <QtWidgets>
#include <imagearea.h>
#include "ui_transformationform.h"

class TransformationForm : public QDialog
{
    Q_OBJECT

public:
    explicit TransformationForm(QWidget *parent = nullptr);
    ~TransformationForm();
    void linkImageArea(ImageArea*);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::TransformationForm *ui;
    ImageArea *image_area;
};

#endif // TRANSFOFORM_H
