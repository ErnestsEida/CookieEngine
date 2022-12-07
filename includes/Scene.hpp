// SCENES HAVE TO BE CREATED AND LOADED !!!! BEFORE ANY OBJECTS ARE CREATED EVEN AS POINTERS, OTHERWISE COLLIDERS WILL SCREW UP !!!!!

#pragma once

#include <vector>
#include <iostream>
#include "Helpers.hpp"
#include "GameObject.cpp"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Scene {
private:
    string name;
    int width, height;
public:
    vector<GameObject*> sceneObjects;

    Scene(string name, int width, int height) {
        this->name = name;
        this->width = width;
        this->height = height;
    }

    void SetupScene() {
        GameObject::gameobjects = &this->sceneObjects;
    }

    void InsertObject(GameObject* object) {
        this->sceneObjects.push_back(object);
    }

    vector<Drawable*> UpdateObjects() {
        vector<GameObject*> parentObjects = Helpers::ParseParentGameObjects(this->sceneObjects);
        parentObjects = Helpers::SortGameObjectsByZ(parentObjects);
        vector<Drawable*> all_drawables;

        for(int i = 0; i < parentObjects.size(); i++) {
            parentObjects[i]->OnUpdate();
            parentObjects[i]->UpdateChildren();
            vector<Drawable*> object_drawables = parentObjects[i]->getCompleteDrawablesWithChildren();
            all_drawables.insert(all_drawables.end(), object_drawables.begin(), object_drawables.end());
        }

        return all_drawables;
    }
};