#pragma once
#include "interfaces/IDisplayWindow.cpp"

class GameRoomBuilder : public IDisplayWindow {
  void create() override {
    if (this->is_open) {
      ImGui::Begin("GameRoom Builder", &this->is_open);
      ImGui::End();
    }
  }
};