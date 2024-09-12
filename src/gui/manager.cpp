#include "gui/manager.hpp"

// ----------------------------------------------------------------------

Manager::Manager()
{
    std::vector<Button> button_;
}

// ----------------------------------------------------------------------

Manager::~Manager()
{
}

// ----------------------------------------------------------------------

void Manager::add_button(Button& button)
{
    buttons_.push_back(button);
}

// ----------------------------------------------------------------------

void Manager::update(Graphics::Window& window, void* params)
{
    size_t size = buttons_.size();

    for (size_t i = 0; i < size; i++)
    {
        buttons_[i].update_condition(window, params);
    }
}
