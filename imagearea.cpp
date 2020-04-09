#include <QtWidgets>
#include "imagearea.h"

ImageArea::ImageArea(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    edit_rect = false;
    ratio = 1.0;
}

bool ImageArea::openImage(const QString &fileName)
{
    QPixmap loadedImage;
    if (!loadedImage.load(fileName))
        return false;
    backupImage = loadedImage;
    image = loadedImage;
    target_rect = image.rect();
    update();
    return true;
}

bool ImageArea::saveImage(const QString &fileName, const char *fileFormat)
{
    if (image.save(fileName, fileFormat)) {
        return true;
    } else {
        return false;
    }
}

void ImageArea::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);

    if(!image.isNull()){
        QRect dirtyRect = event->rect();

        painter.setRenderHint(QPainter::Antialiasing);

//        QSize pixSize = image.size();
//        pixSize.scale(event->rect().size(), Qt::KeepAspectRatio);

//        ratio = pixSize.height() / image.size().height();

//        QPixmap scaledImage = image.scaled(pixSize,
//                                       Qt::KeepAspectRatio,
//                                       Qt::SmoothTransformation
//                                       );
//        painter.drawPixmap(dirtyRect, scaledImage, dirtyRect);
        painter.drawPixmap(dirtyRect, image, dirtyRect);

        painter.setPen(QPen(Qt::blue, 1, Qt::SolidLine, Qt::RoundCap,
                            Qt::RoundJoin));
        painter.drawRect(curr_rect);
        painter.setPen(QPen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap,
                            Qt::RoundJoin));
        painter.drawRect(target_rect);
    }
}

void ImageArea::mousePressEvent(QMouseEvent *event)
//! [11] //! [12]
{
    if (event->button() == Qt::LeftButton /*&& edit_rect*/) {
        firstPoint = event->pos() / ratio;
        ui_firstPoint = event->pos();
        editing_rect = true;
//        edit_rect = false;
    }
}

void ImageArea::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() == Qt::LeftButton) && editing_rect) {
        target_rect = QRect(firstPoint, event->pos() / ratio);
        curr_rect = QRect(ui_firstPoint, event->pos());
    }
    update();
}

void ImageArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && editing_rect) {
//        curr_rect = QRect();
//        target_rect = image.rect();
        editing_rect = false;
    }
}

void ImageArea::transform(double xt, double yt, double r, double xs, double ys, boolean tf_mode) {
    beforeImage = image;
    bxt = xt;
    byt = yt;
    br = r;
    bxs = xs;
    bys = ys;
    btf = tf_mode;

    QPixmap source = image.copy(target_rect);

    QPainter painter(&image);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, tf_mode);
    painter.translate(target_rect.center());
    painter.translate(xt, yt);
    painter.rotate(r);
    painter.scale(xs, ys);
    painter.translate(-target_rect.width()/2, -target_rect.height()/2);
    painter.drawPixmap(0, 0, source);
    update();
}

void ImageArea::repeat() {
    transform(bxt, byt, br, bxs, bys, btf);
}

void ImageArea::undo() {
    image = beforeImage;
    update();
}
