#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

GLsizei winWidth = 600, winHeight = 400;

void init() {
    // Set the clear color to black
    glClearColor(0.0, 0.0, 0.0, 1.0);

    // Set up the projection matrix for 2D rendering
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, winWidth, 0.0, winHeight, -1.0, 1.0);
}

    void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw first object
    glPushMatrix(); // Save the current matrix
    glTranslatef(50.0f, 50.0f, 0.0f); // Translate
    glColor3f(1.0f, 0.0f, 0.0f); // Set color to red
    glRectf(0.0f, 0.0f, 100.0f, 100.0f); // Draw rectangle
    glPopMatrix(); // Restore the matrix

    // Draw second object
    glPushMatrix(); // Save the current matrix
    glTranslatef(150.0f, 150.0f, 0.0f); // Translate
    glRotatef(45.0f, 0.0f, 0.0f, 1.0f); // Rotate
    glColor3f(0.0f, 1.0f, 0.0f); // Set color to green
    glRectf(0.0f, 0.0f, 100.0f, 100.0f); // Draw rectangle
    glPopMatrix(); // Restore the matrix

    glFlush();
}


void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Set window properties and create a window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    GLFWwindow* window = glfwCreateWindow(winWidth, winHeight, "Rectangles", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    init();

    // Set callback for key input
    glfwSetKeyCallback(window, keyCallback);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
