#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Alerts.cpp"
#include "Collider.hpp"

using namespace sf;
using namespace std;

const int DEFAULT_Z = 0;
const string DEFAULT_OBJECT_NAME = "object";
const string DEFAULT_TAG = "none";

class GameObject {
protected:
    void setParent(GameObject* gameObject) { this->parent = gameObject; }

    void childUpdate() {
        Vector2i currentPos = Vector2i(this->x, this->y);
        Vector2i newPos = Vector2i(this->parent->getX() + this->mirrorX, this->parent->getY() + this->mirrorY);
        this->x += (newPos.x - currentPos.x);
        this->y += (newPos.y - currentPos.y);
        this->OnUpdate();
        this->UpdateChildren();
    }

    void changeIsChild(bool value) { this->isChild = value; }
private:
    float x, y, mirrorX, mirrorY;
    float z;
    string objectName, tag;
    Collider* collider;
    Vector2f colliderDimensions;

    vector<GameObject*> children;
    vector<Drawable*> drawables;

public:
    bool isChild = false;
    GameObject* parent = NULL;

    static vector<GameObject*> *gameobjects;

    // CONSTRUCTORS
    GameObject(float x, float y) {
        this->x = x;
        this->mirrorX = x;
        this->y = y;
        this->mirrorY = y;
        this->z = DEFAULT_Z;
        this->objectName = DEFAULT_OBJECT_NAME;
        this->tag = DEFAULT_TAG;
        this->setCollider(1, 1);
    }

    GameObject(float x, float y, float z) {
        this->x = x;
        this->mirrorX = x;
        this->y = y;
        this->mirrorY = y;
        this->z = z;
        this->objectName = DEFAULT_OBJECT_NAME;
        this->tag = DEFAULT_TAG;
        this->setCollider(1, 1);
    }

    GameObject(float x, float y, float z, string objectName) {
        this->x = x;
        this->mirrorX = x;
        this->y = y;
        this->mirrorY = y;
        this->z = DEFAULT_Z;
        this->objectName = objectName;
        this->tag = DEFAULT_TAG;
        this->setCollider(1, 1);
    }

    GameObject(float x, float y, float z, string objectName, string tag) {
        this->x = x;
        this->mirrorX = x;
        this->y = y;
        this->mirrorY = y;
        this->z = DEFAULT_Z;
        this->objectName = objectName;
        this->tag = tag;
        this->setCollider(1, 1);
    }

    // COLLISIONS
    GameObject* isColliding(string tag) {
        vector<GameObject*> objects = *GameObject::gameobjects;
        for(int i = 0;i < objects.size(); i++) {
            if (objects[i] != this && (objects[i]->getTag() == tag || tag == "")) {
                if (this->collider->area->intersects(*objects[i]->collider->area)) {
                    return objects[i];
                }
            }
        }
        return NULL;
    }

    GameObject* isCollidingAtOffset(float x_offset, float y_offset, string tag) {
        vector<GameObject*> objects = *GameObject::gameobjects;
        float x_start = x_offset >= 0 ? this->collider->right() : this->collider->left();
        float y_start = y_offset >= 0 ? this->collider->bottom() : this-> collider->top();

        for(int i = 0; i < objects.size(); i++) {
            if (objects[i] != this && (tag == "" || objects[i]->getTag() == tag)){
                if (objects[i]->getCollider()->area->contains(x_start + x_offset, y_start + y_offset)) {
                    return objects[i];
                }
            }
        }

        return NULL;
    }

    // GETTERS
    float getX() const { return this->x; }
    float getY() const { return this->y; }
    float getZ() const { return this->z; }
    string getObjectName() const { return this->objectName; }
    string getTag() const { return this->tag; }
    vector<GameObject*> getChildren() { return this->children; }
    vector<Drawable*> getDrawables() const { return this->drawables; }
    Collider* getCollider() const { return this->collider; }

    // SETTERS
    void setX(float x) { this->x = x; this->mirrorX = x; }
    void setY(float y) { this->y = y; this->mirrorY = y; }
    void setZ(float z) { this->z = z; }
    void setObjectName(string objectName) { this->objectName = objectName; }
    void setTag(string tag) { this->tag = tag; }
    void setChildren(vector<GameObject*> children) { this->children = children; }
    void setCollider(float width, float height) { 
        this->collider = new Collider(width, height);
        this->collider->setHolder(this);
    }

    // ADDING
    void addChild(GameObject* child) {
        child->changeIsChild(true);
        child->setParent(this);
        this->children.push_back(child);
    }

    void addDrawable(Drawable* drawable) { this->drawables.push_back(drawable); }

    void clearDrawables() { this->drawables.clear(); }

    vector<Drawable*> getCompleteDrawablesWithChildren() {
        vector<Drawable*> result;
        result.insert(result.end(), this->drawables.begin(), this->drawables.end());
        for(int i = 0; i < this->children.size(); i++){
            vector<Drawable*> temp = this->children[i]->getDrawables();
            result.insert(result.end(), temp.begin(), temp.end());
        }
        return result;
    }

    void Move(float x, float y) {
        this->x += x;
        this->y += y;
    }

    void UpdateChildren() {
        for(int i = 0; i < this->children.size(); i++){
            this->children[i]->childUpdate();
        }
        this->UpdateComponents();
    }

    void UpdateComponents() {
        Transformable* asTransformable;
        for(int i = 0; i < this->drawables.size(); i++) {
            asTransformable = dynamic_cast<Transformable*>(this->drawables[i]);
            asTransformable->setPosition(this->x, this->y);
        }

        this->collider->setPosition(this->x, this->y);
    }

    // Virtual
    virtual void OnStart() = 0; // NOT IMPLEMENTED
    virtual void OnUpdate() = 0;
};