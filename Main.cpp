// compile:  g++ Main.cpp -o Main -std=c++11 -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl && ./Main
// compile:  g++ Main.cpp -o Main -std=c++11 -lGL -lglfw3 -lX11 -lpthread -ldl && ./Main

#include <GLFW/glfw3.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <thread>
#include <string>
//#include <vector>
#include <cmath>

//#include "SaveScreenshot.cpp"
#include "Rendering.cpp"
//#include "World.cpp"

using namespace std;



int main(int argc, char* argv[])
{
    auto func1 = [] (int argc, char* argv[])
    {
        startRendering();
    };

    auto func2 = [] (int argc, char* argv[])
    {
        startCalculating();
    };

    thread thread1(func1, argc, argv), thread2(func2, argc, argv);
    thread1.join();
    thread2.join();

    cout << "\n\n --- Success ;) --- \n\n";
    return 0;
}
