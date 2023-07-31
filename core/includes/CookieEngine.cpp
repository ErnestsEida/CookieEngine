#pragma once
#include <iostream>
#include <chrono>

#include <SFML/Graphics.hpp>

#include "Alerts.cpp"
#include "Gametime.cpp"
#include "Gameroom.cpp"
#include "Gameobject.cpp"
#include "Input.cpp"

using namespace sf;
using namespace std;

class CookieCore {
private:
  RenderWindow* window = nullptr;
  GameRoom* room = nullptr;
  bool closeWindowFlag = false;
  vector<GameObject*> current_objects = vector<GameObject*>();

  void Validate() {
    if (this->window == nullptr) Alerts::Error("Trying to start the engine without creating a window!");
    if (this->room == nullptr) Alerts::Error("Please set a room, before trying to start the engine!");
  }

  bool RecursiveObjectDestruction(vector<GameObject*>* search_vector = nullptr, GameObject* object = nullptr) {
    if (search_vector == nullptr) search_vector = &this->current_objects;  
    if (object == nullptr) Alerts::Error("No object specified for destruction!");

    for(size_t i = 0; i < search_vector->size(); i++) {
      if (search_vector->at(i)->id == object->id) {
        search_vector->erase(search_vector->begin()+i);
        return true;
      } else if (search_vector->at(i)->children.size() > 0) {
        bool children_result = RecursiveObjectDestruction(&search_vector->at(i)->children, object);
        if (children_result) return true;
      }
    }

    return false;
  }

public:
  static CookieCore *singleton;

  CookieCore() {
    if (CookieCore::singleton == nullptr) {
      CookieCore::singleton = this;
    } else {
      Alerts::Error("Can't make another instance of CookieCore, when there is already one present!");
    }
  }

  // WINDOW MANAGEMENT

  void CreateWindow(unsigned int width = 0, unsigned int height = 0, string title = "CookieEngine Window", ContextSettings settings = ContextSettings()) {
    if (width == 0) {
      width = VideoMode::getDesktopMode().width;
    }

    if (height == 0) {
      height = VideoMode::getDesktopMode().height;
    }

    this->window = new RenderWindow(VideoMode(width, height), title, Style::Default, settings);
  }

  void CloseWindow() {
    this->closeWindowFlag = true;
  };

  // GAME-OBJECT MANAGEMENT

  void DestroyObject(GameObject * object) {
    bool destroyed = RecursiveObjectDestruction(nullptr, object);
    if (!destroyed) Alerts::Error("Couldn't find the specified object to destroy in current GameRooms objects!");
  }
  
  // This method should be used to create new gameobjects, otherwise pointers might get screwed up, and objects might not update
  void CreateObject(GameObject* object = nullptr, string id = "" ) {
    if (object == nullptr) Alerts::Error("No gameobject was passed to be created!");
    if (id == "") {
      this->current_objects.push_back(object);
    } else {
      bool parent_found = false;
      for(size_t i = 0; i < this->current_objects.size(); i++) {
        if (this->current_objects.at(i)->id == id) {
          this->current_objects.at(i)->PushChild(object);
          parent_found = true;
          break;
        }
      }
      if (!parent_found) Alerts::Error("Couldn't find an object in currently available objects with given ID("+id+"), to attach the child to!");
    }
  }

  // GAME-ROOM MANAGEMENT

  void ChangeRoom(string name) {
    GameRoom* room = GameRoom::GetRoom(name);
    if (room == nullptr) Alerts::Error("Couldn't find a room with name '"+ name +"'");
    
    this->room = room;
    this->current_objects = room->GenerateObjects();
  }

  // STARTING THE ENGINE

  void Start() {
    this->Validate();

    auto tp1 = chrono::system_clock::now();
    auto tp2 = chrono::system_clock::now();

    vector<IDrawable> vecToDraw = vector<IDrawable>();

    // Start of Mainloop
    while(this->window->isOpen()) {
      if (this->closeWindowFlag) this->window->close();
      Input::UpdateKeyStates();

      // Calculate deltaTime
      tp2 = chrono::system_clock::now();
      chrono::duration<float> elapsedTime = tp2 - tp1;
      tp1 = tp2;
      Gametime::deltaTime = elapsedTime.count();
      // ==================

      // SFML Events
      Event event;
      while(this->window->pollEvent(event)) {
        if (event.type == Event::Closed) this->window->close();
      }
      // ============

      // Gameobject management & Drawing
      vecToDraw = vector<IDrawable>();
      for(size_t i = 0; i < this->current_objects.size(); i++) {
        GameObject* object = this->current_objects.at(i);
        // Updates
        object->Update();
        object->UpdateChildren();
        object->UpdateDrawables();
        // Drawables
        if (object->isVisible) {
          vector<IDrawable> objDrawables = object->getDrawables();
          vecToDraw.insert(vecToDraw.end(), objDrawables.begin(), objDrawables.end());
        }
      }


      vecToDraw = IDrawable::SortByZ(vecToDraw);

      this->window->clear();
      for(size_t i = 0; i < vecToDraw.size(); i++) {
        this->window->draw(*vecToDraw.at(i).drawable);
      }
      this->window->display();
      // =====================
      
    } // End of mainloop
    
  }
};

CookieCore* CookieCore::singleton = nullptr;