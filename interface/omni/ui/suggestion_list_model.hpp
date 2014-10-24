#ifndef OMNI_UI_SUGGESTION_LIST_MODEL_HPP
#define OMNI_UI_SUGGESTION_LIST_MODEL_HPP

#include <omni/ui/ui.hpp>

#include <omni/core/input/syntax_suggestion.hpp>

#include <QAbstractListModel>

namespace omni {
namespace ui {

class OMNI_UI_API suggestion_list_model : public QAbstractListModel {
    Q_OBJECT

public:
    void addSuggestion (omni::core::input::syntax_suggestion suggestion);
    omni::core::input::syntax_suggestion getSuggestion (int row) const;
    omni::core::input::syntax_suggestion getSuggestion (QString suggestionText) const;
    void clear ();

    int rowCount (QModelIndex const & parent) const override;

    QVariant data (QModelIndex const & index, int role) const override;

private:
    std::vector <omni::core::input::syntax_suggestion> _suggestions;
};

}
}


#endif // include guard
