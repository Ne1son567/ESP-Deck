#ifndef SNAKE_MENU_HPP
#define SNAKE_MENU_HPP

#include "game/menu/GameMenu.hpp"
#include "bitmap/SnakeIconBitmap.hpp"

class SnakeMenu : public GameMenu 
{
    public:
        SnakeMenu();
        void renderMenu() override;
        void advanceSelectionUp() override;
        void advanceSelectionDown() override;
        void executeSelected() override;
        void update() override;
        const unsigned short* getIconBitmap() const override { return snakeIconBitmap; }

    private:
        void highlightSelectedButton();
        void unhighlightSelectedButton();
};

#endif // SNAKE_MENU_HPP