#ifndef H_MOUSEEVENTHANDLER
#define H_MOUSEEVENTHANDLER

#include <SFML/Graphics.hpp>

#include <vector>
#include <iostream>

#include "vec2f.h"

namespace zen
{
    struct MouseData
    {
        Vec2f position;
        Vec2f moved;
    };

    //Interface for classes that need to listen to mouse events
    class MouseListener
    {
    public:
        virtual void onMouseMove(MouseData mouseData){};
        virtual void onMouseMove(MouseData mouseData, sf::RenderWindow* window){};
        virtual void onMouseButtonChange(sf::Mouse::Button button, Vec2f position, bool pressed){};
        virtual void onMouseButtonChange(sf::Mouse::Button button, Vec2f position, bool pressed, sf::RenderWindow* window){};
    };

    class MouseEventHandler
    {
    public:
        void setup(sf::RenderWindow* window);
        void addListener(MouseListener* listener);

        void handleMoveEvent(sf::Event* event);
        void handleMousePressed(sf::Event* event);
        void handleMouseReleased(sf::Event* event);
    private:
        std::vector<MouseListener*> listeners;

        Vec2f oldPos;

        sf::RenderWindow* window;
    };
}
#endif
