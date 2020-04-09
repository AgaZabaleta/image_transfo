#include "transformationform.h"
#include "ui_transformationform.h"

TransformationForm::TransformationForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TransformationForm)
{
    ui->setupUi(this);
}

TransformationForm::~TransformationForm()
{
    delete ui;
}

void TransformationForm::linkImageArea(ImageArea* i_a) {
    image_area = i_a;
}

void TransformationForm::on_buttonBox_accepted()
{
    double x_t = 0.0;
    double y_t = 0.0;
    double r = 0.0;
    double x_s = 1.0;
    double y_s = 1.0;
    boolean smooth = false;

    x_t = ui->x_translate->value();
    y_t = ui->y_translate->value();

    r = ui->rotate_deg->value();

    x_s = ui->x_scale->value();
    y_s = ui->y_scale->value();

    smooth = ui->smooth->isChecked();

    image_area->transform(x_t, y_t, r, x_s, y_s, smooth);

}
