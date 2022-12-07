#pragma once

#include <iostream>
#include <SFML/Audio.hpp>
#include "GameObject.hpp"

using namespace sf;

class AudioPlayer : public GameObject {
private:
    SoundSource* source = NULL;

    void eraseSlots() {
        this->source = NULL;
    }

    bool notEmpty() {
        if (this->source == NULL) {
            Alerts::WarningMessage("No audio source is set on AudioPlayer. It won't play until there is one!");
            return false;
        }
        return true;
    }
public:
    AudioPlayer() : GameObject(0, 0) {}
    AudioPlayer(float x, float y) : GameObject(x, y) {}
    AudioPlayer(string sourcePath) : GameObject(0, 0) {
        this->setSource(sourcePath);
    }

    void OnUpdate() override {}
    void OnStart() override {}

    void setSource(SoundSource* source) {
        this->eraseSlots();
        this->source = source;
    }

    void setSource(string pathToSource) {
        this->eraseSlots();
        Music* musicbox = new Music();
        if(!musicbox->openFromFile(pathToSource)) {
            Alerts::ErrorMessage("Couldn't open source audio from \"" + pathToSource + "\"");
            return;
        }
        this->source = musicbox;
    }

    // CONTROLLING AUDIO GOES BELOW ...
    void Play() { 
        if (this->notEmpty() && this->source->getStatus() != this->source->Playing){
            this->source->play();
        } else
            return; 
    }

    void Pause() {
        if (this->notEmpty())
            this->source->pause();
        else
            return;
    }

    void Stop() {
        if (this->notEmpty())
            this->source->stop();
        else
            return;
    }

    float getVolume() {
        if (this->notEmpty())
            return this->source->getVolume();
        else
            return -1;
    }

    void setVolume(float volume) {
        if (this->notEmpty())
            this->source->setVolume(volume);
        else
            return;
    }

    float getPitch() {
        if (this->notEmpty())
            return this->source->getPitch();
        else
            return -1;
    }

    void setPitch(float pitch) {
        if (this->notEmpty())
            this->source->setPitch(pitch);
        else
            return;
    }

    void setLoop(bool loop) {
        if (this->notEmpty()) {
            Music* asMusic = dynamic_cast<Music*>(this->source);
            asMusic->setLoop(loop);
        } else
            return;
    }

};