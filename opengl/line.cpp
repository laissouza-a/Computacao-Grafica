#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

void initializeGLFW(){
    if(!glfwInit()){
        cerr<<"Fail"<<endl;
        exit(EXIT_FAILURE);
    }
}

void initializeGLEW(){
    glewExperimental = GL_TRUE;
    if(glewInit()!= GLEW_OK){
        cerr<<"Fail"<<endl;
        exit(EXIT_FAILURE);
    }
}

GLFWwindow* createWindow(){
    GLFWwindow* window = glfwCreateWindow(800,600,"line", NULL,NULL);
    if(!window){
        cerr<<"Fail"<<endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    return window;
}

void draw(){
    glBegin(GL_LINES);
    glVertex2f(-0.5f, 0.0f);
    glVertex2f(0.5f,0.0f);
    glEnd();
    glFlush();
}

int main(){
    GLFWwindow* window = createWindow();
    glfwMakeContextCurrent(window);
    initializeGLEW();
    glViewport(0,0,800,600);

    while(glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT);
        draw();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}