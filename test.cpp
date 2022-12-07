#include "includes/Cookie.cpp"
#include "includes/Scene.hpp"
#include "demo/Player.hpp"
#include "demo/Child.hpp"

int main(){
    Cookie c;
    c.CreateWindow(1280, 720, "Game1");
    Scene* scene = new Scene("scene1", 100, 100);
    c.LoadScene(scene);
    Player x(50, 50, c.GetViewport());
    scene->InsertObject(&x);

    Child* f;
    for(int i = 0;i < 20;i++){
        f = new Child(100 + (50*i), 500);
        f->setZ(-1);
        scene->InsertObject(f);
    }

    c.Run();
    return 0;
}