#ifndef OMNI_UI_BLUEPRINT_HPP
#define OMNI_UI_BLUEPRINT_HPP

#include <omni/ui/ui.hpp>

#include <QWidget>

namespace omni {
namespace ui {

class OMNI_UI_API blueprint : public QWidget {
    Q_OBJECT

public:
    blueprint (QWidget * parent);

protected:
    void paintEvent (QPaintEvent * event) override;
};

}
}

#endif // include guard
