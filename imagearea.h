#ifndef IMAGEAREA_H
#define IMAGEAREA_H

#include <QtWidgets>

class ImageArea : public QWidget
{
public:
    ImageArea(QWidget *parent = 0);

    bool openImage(const QString &fileName);
    bool saveImage(const QString &fileName, const char *fileFormat);
    void switchTFMode();
    void transform(double xt, double yt, double r, double xs, double ys, boolean tf);
    void editTarget();
    void editSource();
    void repeat();
    void undo();
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
private:
    QPixmap image;
    QPixmap beforeImage;
    QPixmap backupImage;

    boolean edit_rect;
    boolean editing_rect;
    QPoint firstPoint;
    QRect curr_rect;
    QPoint ui_firstPoint;
    QRect target_rect;

    boolean scaleup;

    double ratio;
    double bxt;
    double byt;
    double br;
    double bxs;
    double bys;
    boolean btf;
};

#endif // IMAGEAREA_H
