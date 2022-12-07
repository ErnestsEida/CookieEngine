#pragma once

#include "GameObject.hpp"
#include <iostream>
#include <map>

using namespace std;

enum ShapeType {
    Circle,
    Rectangle,
};

class GraphicsRenderer : public GameObject {
private:
    Vector2f origin;

    // SPRITE ATTRIBUTES
    Texture spritesheet;
    Sprite* sprite = NULL;
    string spriteFilePath = "";
    Vector2i spriteSize;
    int frame_count;

    Clock clock;
public:
    GraphicsRenderer(float x, float y, float z = 0) : GameObject(x, y, z) {}

    void addShape(ShapeType type, float value1 = 0, float value2 = 0) {
        if (type == ShapeType::Circle) {
            CircleShape* shape = new CircleShape(value1);
            this->addDrawable(shape);
        } else if (type == ShapeType::Rectangle) {
            RectangleShape* shape = new RectangleShape(Vector2f(value1, value2));
            this->addDrawable(shape);
        }
        this->setDrawableOrigin(this->origin.x, this->origin.y);
    }

    void addShape(Shape* shape){
        this->addDrawable(dynamic_cast<Drawable*>(shape));
        this->setDrawableOrigin(this->origin.x, this->origin.y);
    }

    void addSprite(string pathToSpritesheet, int frame_width, int frame_height, int frame_count) {
        if (this->sprite != NULL) {
            this->clearDrawables();
        }

        this->spriteFilePath = pathToSpritesheet;
        this->frame_count = frame_count;
        this->spriteSize = Vector2i(frame_width, frame_height);
        this->spritesheet = Texture();
        if (!this->spritesheet.loadFromFile(this->spriteFilePath)) {
            Alerts::ErrorMessage("Couldn't load \"" + this->spriteFilePath + "\"");
            return ;
        }
        this->sprite = new Sprite(this->spritesheet, IntRect(Vector2i(0,0), this->spriteSize));
        this->addDrawable(dynamic_cast<Drawable*>(this->sprite));
    }

    void setDrawableOrigin(float x, float y) {
        this->origin = Vector2f(x, y);
        for(int i = 0; i < this->getDrawables().size(); i++){ 
            Transformable* asTransformable = dynamic_cast<Transformable*>(this->getDrawables()[i]);
            asTransformable->setOrigin(this->origin);
        }
    }

    void TryNextSprite() {
        if (this->clock.getElapsedTime().asSeconds() > 1.0 / this->frame_count) {
            this->NextSprite();
            this->clock.restart();
        }
    }

    void NextSprite() {
        IntRect rect = this->sprite->getTextureRect();
        if (rect.left + this->spriteSize.x >= (this->frame_count * this->spriteSize.x)) {
            rect.left = 0;
        } else {
            rect.left += this->spriteSize.x;
        }
        this->sprite->setTextureRect(rect);
    }

    void OnStart() override {}
    void OnUpdate() override {
        if (this->sprite != NULL) {
            this->TryNextSprite();
        }
    }
};