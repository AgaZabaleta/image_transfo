#ifndef APPLICATION_H
#define APPLICATION_H

#include <QtWidgets>

#include<imagearea.h>
#include "transformationform.h"

class Application : public QWidget
{
    Q_OBJECT

public:
    Application(QWidget* parent);

private slots:
    void open();
    void save();
    void form();
    void undo();
    void repeat();
//    void editSource();
private:
    bool saveFile(const QByteArray &fileFormat);

    QHBoxLayout *main_layout;
    QVBoxLayout *menu_layout;

    QPushButton *openButton;
    QPushButton *saveButton;
    QPushButton *undoButton;
    QPushButton *switchButton;
    QPushButton *repeatButton;
    QPushButton *eSourceButton;
    QPushButton *formButton;

    TransformationForm *dialog;

    ImageArea *image_area;
};

#endif
