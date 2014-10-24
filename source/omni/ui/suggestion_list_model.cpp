#include <omni/ui/suggestion_list_model.hpp>

void omni::ui::suggestion_list_model::addSuggestion (omni::core::input::syntax_suggestion suggestion)
{
    beginInsertRows (QModelIndex (), _suggestions.size (), _suggestions.size () + 1);
    _suggestions.push_back (suggestion);
    endInsertRows ();
}

omni::core::input::syntax_suggestion omni::ui::suggestion_list_model::getSuggestion (int row) const
{
    return _suggestions [row];
}

omni::core::input::syntax_suggestion omni::ui::suggestion_list_model::getSuggestion (QString suggestionText) const
{
    std::string text = suggestionText.toStdString ();
    for (auto const & suggestion : _suggestions) {
        if (suggestion.text == text) {
            return suggestion;
        }
    }
    throw std::out_of_range ("No such suggestion: " + text);
}

void omni::ui::suggestion_list_model::clear ()
{
    if (_suggestions.size () > 0) {
        beginRemoveRows (QModelIndex (), 0, _suggestions.size () - 1);
        _suggestions.clear ();
        endRemoveRows ();
    }
}

int omni::ui::suggestion_list_model::rowCount (QModelIndex const &) const
{
    return _suggestions.size ();
}

QVariant omni::ui::suggestion_list_model::data (QModelIndex const & index, int role) const
{
    switch (role) {
    case Qt::DisplayRole:
    case Qt::EditRole:
        return QString::fromStdString (_suggestions [index.row ()].text);
    default:
        return QVariant ();
    }
}