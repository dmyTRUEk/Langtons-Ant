// this file will RENDER world

#include <GLFW/glfw3.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <cmath>

#include "World.cpp"

using namespace std;



const int window_w = 1920;
const int window_h = 1080;

float zoom = 2.0/world_size;
float cam_x, cam_y;



static void error_callback (int error, const char* description)
{
    fputs(description, stderr);
}



float mratio;
void initInCycle (GLFWwindow* window)
{
    //float ratio;
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    mratio = width / (float) height;
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(-1.0, 1.0, -1.0, 1.0, 0.001, -1000.0);
    glOrtho(-mratio, mratio, -1.0, 1.0, 0.001, -1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}



void drawScene ()
{
    Color col;

    // do all screen black
    /*col = Color(0, 0, 0);
    glBegin(GL_QUADS);
    glColor3ub(col.r, col.g, col.b);
    glVertex2f(-mratio, -1.0);
    glVertex2f( mratio, -1.0);
    glVertex2f( mratio,  1.0);
    glVertex2f(-mratio,  1.0);
    glEnd();*/

    // draw all grey cells
    col = nothing.color;
    glBegin(GL_QUADS);
    glColor3ub(col.r, col.g, col.b);
    glVertex2f((0         -world_size/2-cam_x)*zoom, (0         -world_size/2-cam_y)*zoom);
    glVertex2f((world_size-world_size/2-cam_x)*zoom, (0         -world_size/2-cam_y)*zoom);
    glVertex2f((world_size-world_size/2-cam_x)*zoom, (world_size-world_size/2-cam_y)*zoom);
    glVertex2f((0         -world_size/2-cam_x)*zoom, (world_size-world_size/2-cam_y)*zoom);
    glEnd();

    // draw all another cells
    for (int w = 0; w < world_size; w++)
    {
        for (int h = 0; h < world_size; h++)
        {
            if (world.at[w][h] != -1)       // if not grey
            {
                col = program[world.at[w][h]].color;
                glBegin(GL_QUADS);
                glColor3ub(col.r, col.g, col.b);
                glVertex2f((w  -world_size/2-cam_x)*zoom, (h  -world_size/2-cam_y)*zoom);
                glVertex2f((w+1-world_size/2-cam_x)*zoom, (h  -world_size/2-cam_y)*zoom);
                glVertex2f((w+1-world_size/2-cam_x)*zoom, (h+1-world_size/2-cam_y)*zoom);
                glVertex2f((w  -world_size/2-cam_x)*zoom, (h+1-world_size/2-cam_y)*zoom);
                glEnd();
            }
        }
    }
}



void startMainLoop (GLFWwindow* window)
{
    while (!glfwWindowShouldClose(window))                                      // This is main loop
    {
        initInCycle(window);

        drawScene();
        //world.process2();

        //if (!working) glfwSetWindowShouldClose(window, GL_TRUE);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    cout << "\n --- Rendering finished --- \n";
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}



int screenshot_number = 0;
void prepareSaveScreenshot ()
{
    string m_file_name = "screenshot1";
    m_file_name += screenshot_number+".tga";
    saveScreenshot(m_file_name, window_w, window_h);
    screenshot_number++;
}



static void key_callback (GLFWwindow* window, int key, int scancode, int action, int mods)
{
    float cam_speed = 0.1 / zoom;
    switch (action)
    {
        case GLFW_PRESS:
            switch (key)
            {
                case GLFW_KEY_ESCAPE:
                    //saveScreenshot("screenshotEND.tga", window_w, window_h);
                    glfwSetWindowShouldClose(window, GL_TRUE);
                    break;
                case GLFW_KEY_SPACE:
                    prepareSaveScreenshot();
                    break;
                case GLFW_KEY_LEFT:
                    cam_x -= cam_speed;
                    break;
                case GLFW_KEY_RIGHT:
                    cam_x += cam_speed;
                    break;
                case GLFW_KEY_UP:
                    cam_y += cam_speed;
                    break;
                case GLFW_KEY_DOWN:
                    cam_y -= cam_speed;
                    break;
                case GLFW_KEY_LEFT_SHIFT:
                    //movePosition(0, 0, +10);
                    break;
                case GLFW_KEY_LEFT_CONTROL:
                    //movePosition(0, 0, -10);
                    break;
            }
            break;

        case GLFW_REPEAT:
            switch (key)
            {
                case GLFW_KEY_LEFT:
                    cam_x -= cam_speed;
                    break;
                case GLFW_KEY_RIGHT:
                    cam_x += cam_speed;
                    break;
                case GLFW_KEY_UP:
                    cam_y += cam_speed;
                    break;
                case GLFW_KEY_DOWN:
                    cam_y -= cam_speed;
                    break;
                case GLFW_KEY_LEFT_SHIFT:
                    //movePosition(0, 0, +10);
                    break;
                case GLFW_KEY_LEFT_CONTROL:
                    //movePosition(0, 0, -10);
                    break;
            }
            break;
    }
}



//static?
void scroll_callback (GLFWwindow* window, double xoffset, double yoffset)
{
    float zoom_speed = 1.1;
    if (yoffset > 0)
    {
        zoom *= zoom_speed;
    }
    else if (yoffset < 0)
    {
        zoom /= zoom_speed;
    }
}



void startRendering ()
{
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) exit(EXIT_FAILURE);
    window = glfwCreateWindow(window_w, window_h, "Langton's Ant", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSetScrollCallback(window, scroll_callback);

    startMainLoop(window);
}
