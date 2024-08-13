#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <vector>

// Window dimensions
const GLint WIDTH = 800, HEIGHT = 600;

// Function to draw a polygon
void drawPolygon(int n) {
    float radius = HEIGHT / 3.0f / 2.0f; // Radius of the polygon

    glBegin(GL_LINE_LOOP); // Start drawing the polygon's outline
    for (int i = 0; i < n; ++i) {
        float angle = 2.0f * M_PI * i / n;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(x / (WIDTH / 2.0f), y / (HEIGHT / 2.0f)); // Normalize coordinates to [-1, 1]
    }
    glEnd();
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "GLFW initialization failed" << std::endl;
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Polygon", nullptr, nullptr);
    if (!window) {
        std::cerr << "GLFW window creation failed" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "GLEW initialization failed" << std::endl;
        return -1;
    }

    // Set the viewport dimensions
    glViewport(0, 0, WIDTH, HEIGHT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set clear color to black

    int n;
    std::cout << "Digite o número de vértices do polígono: ";
    std::cin >> n;

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT); // Clear the screen
        drawPolygon(n); // Draw the polygon
        glfwSwapBuffers(window); // Swap front and back buffers
        glfwPollEvents(); // Poll for and process events
    }

    glfwTerminate();
    return 0;
}
