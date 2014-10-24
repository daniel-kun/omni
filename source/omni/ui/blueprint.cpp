#include <omni/ui/blueprint.hpp>

#include <QPainter>

omni::ui::blueprint::blueprint (QWidget * parent) :
    QWidget (parent)
{
    setAutoFillBackground (true);
    QPalette pal;
    pal.setColor (QPalette::Background, QColor::fromRgb (0xFF, 0xFF, 0xFF));
//    pal.setColor (QPalette::Background, QColor::fromRgb (0x64, 0xA7, 0xC1));
    setPalette (pal);
}

void omni::ui::blueprint::paintEvent (QPaintEvent *)
{
    return;
    QPainter painter (this);
    painter.setPen (QColor::fromRgb (0xE3, 0xE3, 0xE5));
    int w = width ();
    int h = height ();
    const int hstep = 20;
    const int vstep = 20;
    for (int x = 0; x <= w; x += hstep) {
        for (int y = 0; y <= h; y += vstep) {
            painter.drawLine (0, y, w, y);
            painter.drawLine (x, 0 ,x, h);
        }
    }
}
