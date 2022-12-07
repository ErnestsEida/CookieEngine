#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;
using namespace std;

class Collider {
public:
    FloatRect* area;
    float width, height;
    void* holder;

    Collider(float width = 1.0f, float height = 1.0f) {
        this->width = width;
        this->height = height;
        this->area = new FloatRect(0, 0, width, height);
    }

    void setPosition(float x, float y) {
        this->area->left = x;
        this->area->top = y;
    }

    void setHolder(void* holder) { this->holder = holder; }

    float bottom() { return this->area->top + height; }
    float right() { return this->area->left + width; }
    float left() { return this->area->left; }
    float top() { return this->area->top; }
};