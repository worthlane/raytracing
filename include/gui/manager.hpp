#ifndef _MANAGER_HPP_
#define _MANAGER_HPP_

#include "graphics/visual.hpp"
#include "gui/controls.hpp"

class Manager
{
    public:
        Manager();
        ~Manager();

        void add_button(Button& button);

        void update(Graphics::Window& window, void* params);

    private:
        std::vector<Button> buttons_;
};

#endif // _MANAGER_HPP_
