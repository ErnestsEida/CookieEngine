# Cookie - V2
Cookie is a **GAME ENGINE** made fully in C++ on top of SFML graphics library
## Table of contents
1. [Prerequisites](#prerequisites)

   - [Linux](#linux)
   - [Windows](#windows)
   - [MacOS](#windows)

2. [Building your first game](#building-your-first-game)
3. [Classes](#classes)

## Prerequisites

### Linux
```
sudo apt-get install libsfml-dev
```
### Windows
> Not available for this version
### MacOS
```
brew install sfml
```

## Building your first game
**STEP 1:** Create a main.cpp that will hold the game main loop  
**STEP 2:** include `Cookie.cpp` file into file created earlier  
**STEP 3:** Initialize Engines window ( without initialization you won't be able to run the game ):
```cpp
#include "{path_to_includes}/Cookie.cpp";
#include <iostream>

using namespace std;

int main(){
  // Create a new instance of engine
  Cookie engine;
  
  // Initialize window
  engine.CreateWindow(1280, 720, "Game Window");
  
  // Run to show game window
  engine.Run();
  return 0;
}
```

Creating GameObjects on screen can be done anywhere before `engine.Run()` call

## Classes
Youy can find information about classes and their methods and functionality in [Class descriptions](includes/readme.md#class-descriptions)
