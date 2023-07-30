#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "includes/main_menu_bar.cpp"

#include <iostream>

const char* glsl_version = "#version 130";

GLFWwindow* mainWindow;

void initializeHandler() {
    if (!glfwInit()) {
        exit(1);
    }

    mainWindow = glfwCreateWindow(1280, 720, "CookieEngine", nullptr, nullptr);
    glfwMakeContextCurrent(mainWindow);
    glfwSwapInterval(1);
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();

    ImGui_ImplGlfw_InitForOpenGL(mainWindow, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

void mainUpdate() {
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(mainWindow, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(mainWindow);
}

void shutDownHandler() {
    ImGui_ImplGlfw_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
}

int main(int argc, char* argv[]) {
    for(int i = 0; i < argc; i++) {
        std::cout << argv[i] << std::endl;
    }

    initializeHandler();
    if (mainWindow == nullptr) {
        std::cout << "Window didnt initialize" << std::endl;
        exit(1);
    }

    while(!glfwWindowShouldClose(mainWindow)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        MainMenuBar::create();

        mainUpdate();
    }

    shutDownHandler();
    return 0;
}