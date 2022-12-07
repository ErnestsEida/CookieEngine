#pragma once

#include "../includes/GameObject.hpp"

class Child : public GameObject {
public:
    Child(int x, int y) : GameObject(x, y, 0, "child", "child") {
        RectangleShape *shape = new RectangleShape(Vector2f(50, 50));
        this->setCollider(50, 50);
        shape->setFillColor(Color::Blue);
        this->addDrawable(shape);
    }

    void OnStart() {}

    void OnUpdate() {}
};