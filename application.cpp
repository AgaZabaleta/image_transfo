#include "application.h"


//! [0]
Application::Application(QWidget* parent) :
    QWidget(parent),
    image_area(new ImageArea(this))
{

    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    main_layout = new QHBoxLayout();
    menu_layout = new QVBoxLayout();

    openButton = new QPushButton("Open", this);
    saveButton = new QPushButton("Save", this);
    undoButton = new QPushButton("Undo", this);
//    eSourceButton = new QPushButton("Edit source selection", this);
    repeatButton = new QPushButton("Repeat", this);
    formButton = new QPushButton("Transform", this);

    connect(openButton, SIGNAL(released()), this, SLOT(open()));
    connect(saveButton, SIGNAL(released()), this, SLOT(save()));
    connect(undoButton, SIGNAL(released()), this, SLOT(undo()));
//    connect(switchButton, SIGNAL(released()), this, SLOT(switchTF()));
//    connect(eSourceButton, SIGNAL(released()), this, SLOT(editSource()));
    connect(repeatButton, SIGNAL(released()), this, SLOT(repeat()));
    connect(formButton, SIGNAL(released()), this, SLOT(form()));

    menu_layout->addWidget(openButton);
    menu_layout->addWidget(saveButton);
    menu_layout->addWidget(undoButton);
//    menu_layout->addWidget(eSourceButton);
    menu_layout->addWidget(repeatButton);
    menu_layout->addWidget(formButton);

    main_layout->addLayout(menu_layout, 1);
    main_layout->addWidget(image_area, 3);

    setLayout(main_layout);
}

void Application::open()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                               tr("Open File"), QDir::currentPath());
    if (!fileName.isEmpty()) {
        image_area->openImage(fileName);
    }
}

void Application::undo()
{
    image_area->undo();
}

//void Application::editSource()
//{
//    image_area->editSource();
//}

void Application::repeat()
{
    image_area->repeat();
}

void Application::save()
{
    QAction *action = qobject_cast<QAction *>(sender());
    QByteArray fileFormat = action->data().toByteArray();
    saveFile(fileFormat);
}

bool Application::saveFile(const QByteArray &fileFormat)
{
    QString initialPath = QDir::currentPath() + "/untitled." + fileFormat;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                               initialPath,
                               tr("%1 Files (*.%2);;All Files (*)")
                               .arg(QString::fromLatin1(fileFormat.toUpper()))
                               .arg(QString::fromLatin1(fileFormat)));
    if (fileName.isEmpty()) {
        return false;
    } else {
        return image_area->saveImage(fileName, fileFormat.constData());
    }
}

void Application::form(){
    dialog = new TransformationForm();
    dialog->linkImageArea(image_area);
    dialog->exec();
}
