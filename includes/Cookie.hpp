#pragma once

// All SFML Includes
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

// STD Includes
#include <iostream>
#include <chrono>

// Engine
#include "Alerts.cpp"
#include "Scene.hpp"
#include "Gametime.cpp"
#include "Helpers.hpp"
#include "Viewport.hpp"

using namespace sf;
using namespace std;

class Cookie {
private:
    // ATTRIBUTES
    bool closeWindowFlag = false;
    bool windowInitializationFlag = false;
    RenderWindow* window;
    Scene* currentScene = NULL;
    Viewport* viewport;
public:
    static Cookie* Engine;

    Cookie() {
        Cookie::Engine == NULL ? Cookie::Engine = this : throw std::invalid_argument("Can't have 2 engines at once!");
        this->viewport = new Viewport(720, 360);
    }

    // GETTERS
    RenderWindow* getWindow() const {
        return this->windowInitializationFlag ? this->window : nullptr;
    }

    // SETTERS
    void setWindow(RenderWindow* window) {
        this->window = window;
        this->viewport->SetSize(this->window->getSize().x, this->window->getSize().y);
        this->viewport->SetCenter(this->window->getSize().x / 2, this->window->getSize().y / 2);
        this->window->setView(*this->viewport->view);
    }

    // MISC
    void CreateWindow(unsigned int width,unsigned int height, string title) {
        this->window = new RenderWindow(VideoMode(width, height), title, Style::Default);
        this->windowInitializationFlag = true;
        this->viewport->SetSize(this->window->getSize().x, this->window->getSize().y);
        this->viewport->SetCenter(this->window->getSize().x / 2, this->window->getSize().y / 2);
        this->window->setView(*this->viewport->view);
    }

    void CreateWindow(unsigned int width,unsigned int height, string title, ContextSettings settings) {
        this->window = new RenderWindow(VideoMode(width, height), title, Style::Default, settings);
        this->windowInitializationFlag = true;
        this->viewport->SetSize(this->window->getSize().x, this->window->getSize().y);
        this->viewport->SetCenter(this->window->getSize().x / 2, this->window->getSize().y / 2);
        this->window->setView(*this->viewport->view);
    }

    Viewport* GetViewport() const {
        return this->viewport;
    }

    void CloseWindow() {
        this->closeWindowFlag = true;
    }

    void LoadScene(Scene* scene) {
        this->currentScene = scene;
        this->currentScene->SetupScene();
    }

    Scene* GetScene() const {
        return this->currentScene;
    }

    void Run() {
        if (!this->windowInitializationFlag) {
            Alerts::ErrorMessage("window has not been initialized!");
            return ;
        }

        if (this->currentScene == NULL) Alerts::WarningMessage("No scene has been loaded!");

        auto tp1 = chrono::system_clock::now();
	    auto tp2 = chrono::system_clock::now();

        vector<GameObject*> all_gameobjects;
        vector<GameObject*> parent_gameobjects;
        vector<Drawable*> all_drawables;
        while(this->window->isOpen()){
            if (this->closeWindowFlag) this->window->close();
            
            tp2 = chrono::system_clock::now();
		    chrono::duration<float> elapsedTime = tp2 - tp1;
		    tp1 = tp2;
		    Gametime::deltaTime = elapsedTime.count();

            Event event;
            while(this->window->pollEvent(event)){
                if (event.type == Event::Closed) this->window->close();
            }

            // GATHER DRAWABLES FROM SCENE
            if (this->currentScene != NULL) all_drawables = currentScene->UpdateObjects();

            this->window->clear();

            for(int i = 0;i < all_drawables.size();i++){
                if (all_drawables[i] == nullptr) continue;
                this->window->draw(*all_drawables[i]);
            }

            this->window->display();

            all_drawables.clear();
            this->window->setView(*this->viewport->view);
        }
    }
};