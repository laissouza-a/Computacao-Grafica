#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

// Window dimensions
const GLint WIDTH = 800, HEIGHT = 600;

void initializeGLFW() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }
}

GLFWwindow* createWindow() {
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Window", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    return window;
}

void initializeGLEW() {
    glewExperimental = GL_TRUE; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(0.0f, 0.5f);

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(-0.5f, -0.5f);

    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(0.5f, -0.5f);
    glEnd();
    //void glfwSwapBuffers(GLFWwindow* window);
    glfwSwapBuffers(glfwGetCurrentContext());
}

int main(int argc, char** argv) {
    initializeGLFW();

    GLFWwindow* window = createWindow();

    // Make the window's context current
    glfwMakeContextCurrent(window);

    initializeGLEW();

    // Set the viewport dimensions
    glViewport(0, 0, WIDTH, HEIGHT);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Draw
        draw();

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

//g++ test.cpp -o test -lglfw -lGL -lGLEW
