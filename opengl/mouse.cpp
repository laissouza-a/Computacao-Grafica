#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
using namespace std;

GLsizei winWidth = 400, winHeight = 300;
vector <pair<int, int>> points; // Store the points

void init() {
    // Set the clear color to blue
    glClearColor(0.0, 0.0, 1.0, 1.0);

    // Set up the projection matrix for 2D rendering
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, winWidth, 0.0, winHeight, -1.0, 1.0);
}

void plotPoint(GLint x, GLint y) {
    glPointSize(10.0f);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

// Mouse button callback
void mousePtPlot(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xMouse, yMouse;
        glfwGetCursorPos(window, &xMouse, &yMouse);
        int x1 = static_cast<int>(xMouse);
        int y1 = winHeight - static_cast<int>(yMouse); // Adjust y coordinate
        plotPoint(x1, y1); // Plot the point

        glfwSwapBuffers(window); // Swap buffers to show the point
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    for (const auto& point : points) {
        plotPoint(point.first, point.second);
    }

    glFlush();
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        cerr << "Failed to initialize GLFW" << endl;
        return -1;
    }

    // Set window properties and create a window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    GLFWwindow* window = glfwCreateWindow(winWidth, winHeight, "Points using Mouse", nullptr, nullptr);
    if (!window) {
       cerr << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        cerr << "Failed to initialize GLEW" << endl;
        return -1;
    }

    init();

    // Set callback for mouse input
    glfwSetMouseButtonCallback(window, mousePtPlot);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        display();
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
