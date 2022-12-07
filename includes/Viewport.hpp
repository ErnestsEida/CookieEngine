#pragma once

#include <SFML/Graphics.hpp>
#include "Alerts.cpp"

#include <iostream>

using namespace sf;

class Viewport {
public:
    View* view = new View();

    Viewport(int width, int height) {
        this->view = new View(Vector2f(width / 2, height / 2), Vector2f(width, height));
    }

    void SetCenter(int x, int y) {
        this->view->setCenter(Vector2f(x, y));
    }

    void SetSize(int width, int height) {
        this->view->setSize(Vector2f(width, height));
    }

    void Move(int x, int y) {
        this->view->move(Vector2f(x, y));
    }
};