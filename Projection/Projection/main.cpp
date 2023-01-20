/**
 * @file main.cpp
 * @author Jovan Ivosevic
 * @brief Projections showcase
 * R - Changers rendered object
 * W, A, S, D - Rotates camera
 * Scroll - Changes scale
 * @version 0.1
 * @date 2022-10-09
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <chrono>
#include <functional>
#include <thread>
#include "ibufferable.hpp"
#include "irenderable.hpp"
#include "shader.hpp"
#include "cube.hpp"
#include "tent.hpp"
#include "fish.hpp"
#include "stick.hpp"
#include "hole.hpp"
#include "buffer.hpp"
#include "camera.hpp"
#include "model.hpp"

const int WindowWidth = 900;
const int WindowHeight = 900;
const std::string WindowTitle = "Projection";
const float TargetFPS = 60.0f;

float
Clamp(float value, float min, float max) {
    return value < min ? min : value > max ? max : value;
}

struct Input {
    bool Left;
    bool Right;
    bool Up;
    bool Down;
};

struct Renderer {
    unsigned mCurrRenderableIdx;
    std::vector<IRenderable*> mRenderables;
    glm::vec2 mFramebufferSize;
    float mScalingFactor;
};

struct EngineState {
    OrbitalCamera* mOrbitalCamera;
    Input* mInput;
    Renderer* mRenderer;
    float mDT;
};

/**
 * @brief Error callback function for GLFW. See GLFW docs for details
 *
 * @param error Error code
 * @param description Error message
 */
static void
ErrorCallback(int error, const char* description) {
    std::cerr << "GLFW Error: " << description << std::endl;
}

/**
 * @brief Keyboard callback function for GLFW. See GLFW docs for details
 *
 * @param window GLFW window context object
 * @param key Triggered key GLFW code
 * @param scancode Triggered key scan code
 * @param action Triggered key action: pressed, released or repeated
 * @param mode Modifiers
 */
static void
KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    EngineState* State = (EngineState*)glfwGetWindowUserPointer(window);
    Input* UserInput = State->mInput;
    bool IsDown = action == GLFW_PRESS || action == GLFW_REPEAT;
    switch (key) {
        case GLFW_KEY_A: UserInput->Left = IsDown; break;
        case GLFW_KEY_D: UserInput->Right = IsDown; break;
        case GLFW_KEY_W: UserInput->Up = IsDown; break;
        case GLFW_KEY_S: UserInput->Down = IsDown; break;
        case GLFW_KEY_ESCAPE: glfwSetWindowShouldClose(window, GLFW_TRUE); break;
    }
}

/**
 * @brief Scroll callback
 * 
 * @param window GLFW window context object
 * @param xoffset Scroll offset on x-axis
 * @param yoffset Scroll offset on y-axis (used on most mouse wheels)
 */
static void
ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    EngineState* State = (EngineState*)glfwGetWindowUserPointer(window);
    State->mRenderer->mScalingFactor += yoffset * State->mDT;
}

/**
 * @brief Framebuffer resize callback
 *
 * @param window GLFW window context object
 * @param width New framebuffer width
 * @param height New framebuffer height
 */
static void
FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
    EngineState* State = (EngineState*)glfwGetWindowUserPointer(window);
    Renderer* Renderer = State->mRenderer;
    Renderer->mFramebufferSize = glm::vec2(width, height);
}

/**
 * @brief Updates engine state based on input
 *
 * @param state Engine State
 */
static void
HandleInput(EngineState* state) {
    Input* UserInput = state->mInput;
    OrbitalCamera* Camera = state->mOrbitalCamera;
    Renderer* Renderer = state->mRenderer;
    float dt = state->mDT;
    if(UserInput->Left) Camera->Rotate(-0.5f, 0.0f, dt);
    if(UserInput->Right) Camera->Rotate(0.5f, 0.0f, dt);
    if(UserInput->Down) Camera->Rotate(0.0f, 0.5f, dt);
    if(UserInput->Up) Camera->Rotate(0.0f, -0.5f, dt);
}

float GetRadians(float angle) {
    return 3.14 * angle / 180;
}

static void
MoveCube(GLFWwindow* context, float& x, float& y, float& z) {
    if (glfwGetKey(context, GLFW_KEY_UP) == GLFW_PRESS) {
        if (z < 0) {
            z += 0.05;
        }
    }
    if (glfwGetKey(context, GLFW_KEY_DOWN) == GLFW_PRESS) {
        if (z > -4.0) {
            z -= 0.05;
        }
    }
}

int main() {
    GLFWwindow* Window = 0;
    if (!glfwInit()) {
        std::cerr << "Failed to init glfw" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwSetErrorCallback(ErrorCallback);
    Window = glfwCreateWindow(WindowWidth, WindowHeight, WindowTitle.c_str(), 0, 0);
    if (!Window) {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(Window);
    glfwSetKeyCallback(Window, KeyCallback);
    glfwSetScrollCallback(Window, ScrollCallback);
    glfwSetFramebufferSizeCallback(Window, FramebufferSizeCallback);

    GLenum GlewError = glewInit();
    if (GlewError != GLEW_OK) {
        std::cerr << "Failed to init glew: " << glewGetErrorString(GlewError) << std::endl;
        glfwTerminate();
        return -1;
    }

    OrbitalCamera Camera(45.0f, 14.0f);

    Shader BasicShader("shaders/basic.vert", "shaders/basic.frag");
    float RenderDistance = 100.0f;
    glm::mat4 ModelMatrix(1.0f);
    glm::mat4 FreeView = glm::lookAt(Camera.mPosition, Camera.mPosition + Camera.mFront, Camera.mUp);
    glm::mat4 FrontView = glm::lookAt(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 LeftView = glm::lookAt(glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 TopView = glm::lookAt(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    Cube BasicCube;
    Tent Tent;
    Hole Hole;
    Stick Stick;
    Fish Fish;
    Model FIsherMan("../EskimoChild_V1_L1.123c93483ff7-ff4e-4b5a-887f-d965dfd3c059/17831_EskimoChild_V1.obj");
    if(!FIsherMan.Load()) {
        std::cerr << "Failed to load model" << std::endl;
        glfwTerminate();
        return -1;
    }

    Renderer Renderer = { 0 };
    Renderer.mFramebufferSize = glm::vec2(WindowWidth, WindowHeight);
    Renderer.mRenderables.push_back(&BasicCube);
    Renderer.mRenderables.push_back(&FIsherMan);
    Renderer.mRenderables.push_back(&Tent);
    Renderer.mRenderables.push_back(&Hole);
    Renderer.mRenderables.push_back(&Stick);
    Renderer.mRenderables.push_back(&Fish);
    Renderer.mScalingFactor = 1.0f;

    EngineState State = { 0 };
    Input UserInput = { 0 };
    glfwSetWindowUserPointer(Window, &State);
    State.mOrbitalCamera = &Camera;
    State.mInput = &UserInput;
    State.mRenderer = &Renderer;

    float StartTime = glfwGetTime();
    float EndTime = glfwGetTime();
    float TargetFrameTime = 1.0f / TargetFPS;

    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_BACK);

    float x = 0, y = 0, z = 0;
    while (!glfwWindowShouldClose(Window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwPollEvents();
        glClearColor(0.3, 0.7, 1, 1);
        HandleInput(&State);

        StartTime = glfwGetTime();

        glUseProgram(BasicShader.GetId());
        FreeView = glm::lookAt(Camera.mPosition, Camera.mPosition + Camera.mFront, Camera.mUp);
        BasicShader.SetView(FreeView);

        float WindowWidth = Renderer.mFramebufferSize.x;
        float WindowHeight = Renderer.mFramebufferSize.y;

        glm::mat4 m(1.0f);
        glm::mat4 identity(1.0f);
        // NOTE(Jovan): These calls are expensive and should be optimized by executing
        // them only when the framebuffer's size changes. This is for demo purposes only
        glm::mat4 Perspective = glm::perspective(45.0f, Renderer.mFramebufferSize.x / (float)Renderer.mFramebufferSize.y, 0.1f, RenderDistance);

        // NOTE(Jovan): Since ortho's values are constant, when the window is resized it gives "stretched" results
        glm::mat4 Ortho = glm::ortho(-0.5f, 0.5f, -0.5f, 0.5f, 0.1f, RenderDistance);

        // NOTE(Jovan): Bottom right viewport
        glViewport(0, 0, WindowWidth, WindowHeight);
        BasicShader.SetProjection(Perspective);
        ModelMatrix = glm::mat4(1.0f);
        ModelMatrix = glm::scale(ModelMatrix, glm::vec3(Renderer.mScalingFactor));
        BasicShader.SetModel(ModelMatrix);

        m = glm::scale(identity, glm::vec3(20.0f, 1.5f, 20.0f));
        BasicShader.SetModel(m);
        Renderer.mRenderables[0]->Render();

        //model
        m = glm::rotate(identity, GetRadians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
        m = glm::rotate(m, GetRadians(-20.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        m = glm::scale(m, glm::vec3(0.2f, 0.2f, 0.2f));
        m = glm::translate(m, glm::vec3(12.0f, 4.0f, 4.0f));
        BasicShader.SetModel(m);
        Renderer.mRenderables[1]->Render();

        //tent
        m = glm::rotate(identity, GetRadians(-40.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        m = glm::rotate(m, GetRadians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        m = glm::rotate(m, GetRadians(20.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        m = glm::scale(m, glm::vec3(4.0f, 5.0f, 1.5f));
        m = glm::translate(m, glm::vec3(-0.6f, 0.6f, 2.5f));
        BasicShader.SetModel(m);
        Renderer.mRenderables[2]->Render();

        //hole
        m = glm::rotate(identity, GetRadians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        m = glm::scale(m, glm::vec3(2.0f, 2.5f, 0.15f));
        m = glm::translate(m, glm::vec3(1.0f, 1.5f, -4.5f));
        BasicShader.SetModel(m);
        Renderer.mRenderables[3]->Render();

        //stick
        m = glm::rotate(identity, GetRadians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        m = glm::rotate(m, GetRadians(40.0f), glm::vec3(0.0f, 0.0f, -1.0f));
        m = glm::scale(m, glm::vec3(0.1f, 3.5f, 0.1f));
        m = glm::translate(m, glm::vec3(10.0f, 0.6f, -20.0f));
        BasicShader.SetModel(m);
        Renderer.mRenderables[4]->Render();

        MoveCube(Window, x, y, z);

        m = glm::scale(identity, glm::vec3(0.5f, 0.5f, 0.5f));
        m = glm::translate(m, glm::vec3(4.0f, 4.0f+z, 7.0f));
        BasicShader.SetModel(m);
        Renderer.mRenderables[5]->Render();


        glUseProgram(0);
        glfwSwapBuffers(Window);

        //NOTE(Jovan): Clear user input values after each frame
        UserInput = { 0 };

        // NOTE(Jovan): Time management (might not work :'c)
        EndTime = glfwGetTime();
        float WorkTime = EndTime - StartTime;
        if(WorkTime < TargetFrameTime) {
            int DeltaMS = (int)((TargetFrameTime - WorkTime) * 1000.0f);
            std::this_thread::sleep_for(std::chrono::milliseconds(DeltaMS));
            EndTime = glfwGetTime();
        }
        State.mDT = EndTime - StartTime;
    }
    glfwTerminate();
    return 0;
}





