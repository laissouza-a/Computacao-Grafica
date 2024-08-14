#include <iostream>
#include <cmath>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
using namespace std;

// Window dimensions
const GLint WIDTH = 800, HEIGHT = 600;
float radius = 10;
float timeElapsed = 0.0f;

void drawHeart(){
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glTranslatef(WIDTH/2, HEIGHT/2, 0.0f);

    glBegin(GL_POLYGON);  
        for (float a = 0; a < 2*(M_PI); a+=0.01){
            float x = radius * (16 * pow(sin(a),3));
            float y = radius*((13*cos(a)) - (5*cos(2*a)) - (2*cos(3*a)) - (cos(4*a)));
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex2f(x,y);
        }
    glEnd();
    glPopMatrix();
}

void animation(){
    // Simulate heartbeat by changing radius over time
    timeElapsed += 0.05f; // Adjust speed of heartbeat here
    radius = 10 + 2 * sin(timeElapsed); // Oscillate radius between 8 and 12
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "GLFW initialization failed" << std::endl;
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Heart Beat Animation", nullptr, nullptr);
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
    // Set up the orthogonal projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WIDTH, 0, HEIGHT, -1, 1);

    // Switch back to modelview matrix mode
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set clear color to black

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT); // Clear the screen

        drawHeart(); // Draw the heart
        animation(); // Animate the heart
        glfwSwapBuffers(window); // Swap front and back buffers
        glfwPollEvents(); // Poll for and process events
    }

    glfwTerminate();
    return 0;
}
