#include <iostream>
#include <cmath>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
using namespace std;

// Window dimensions used on main function to create window
const int winWidth = 800;
const int winHeight = 600;

// Variables for rotation around xy center (windmill circle)
float center_x = 250.0f;
float center_y = 250.0f;
//starting angle
float current_angle = 0.0f;
float step_angle; // Rotation step in degrees


// Initialize OpenGL settings
void init() {
    //black as initial color
    glClearColor(0.0, 0.0, 0.0, 1.0);

    //projection setting
    glMatrixMode(GL_PROJECTION);
    //identity matrix (stating point)
    glLoadIdentity();
    //left, right, bottom, top, near, far
    glOrtho(0.0, winWidth, 0.0, winHeight, -1.0, 1.0);
}

// Function to draw the turbine
void drawWindmill() {
    //clean buffer 
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the tower (vertical line) (the line is fixed so its out of the matrix)
    glBegin(GL_LINES);
        //white
        glColor3f(1.0, 1.0, 1.0);
        //position coordinates
        glVertex2f(251, 252);
        glVertex2f(251, 44);
    glEnd();

    // Rotate object
    //push matrix (view) on a stack to save 
    glPushMatrix();
    //matriz is on  x and y (new center, before it was left corner)
    glTranslatef(center_x, center_y, 0.0f);
    //matrix is gonna spin in z dimension in current degrees (0.0) around the new center
    glRotatef(current_angle, 0, 0, 1);
    //increase 1 degree (step/velocity)
    current_angle += step_angle;
    //if its bigger then 360 then go back to 0
    if (current_angle >= 360.0f) {
        current_angle -= 360.0f;
    }
    //undo the translation
    glTranslatef(-center_x, -center_y, 0.0f);


    // Draw a white triangle
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_TRIANGLES);
        glVertex2f(249.0f, 244.0f);
        glVertex2f(230.0f, 200.0f);
        glVertex2f(270.0f, 200.0f);
    glEnd();

    // Draw a red triangle
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
        glVertex2f(254.0f, 250.0f);
        glVertex2f(300.0f, 230.0f);
        glVertex2f(300.0f, 270.0f);
    glEnd();

    // Draw a green triangle
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_TRIANGLES);
        glVertex2f(250.0f, 254.0f);
        glVertex2f(230.0f, 300.0f);
        glVertex2f(270.0f, 300.0f);
    glEnd();

    // Draw a blue triangle
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_TRIANGLES);
        glVertex2f(245.0f, 249.0f);
        glVertex2f(200.0f, 270.0f);
        glVertex2f(200.0f, 230.0f);
    glEnd();

    // Draw circle in the middle
    float theta;
    glBegin(GL_POLYGON);
        glColor3f(1.0, 1.0, 1.0); // White color
        //circle has 360 degres, so its just many points around the 360:
        for (int i = 0; i <= 360; i++) {
            //trignometric circle:
            theta = i * 3.142 / 180;
            //draw the vertex considering the center (coordenadas polares: x = raio * cos(θ)
            //y = raio * sin(θ))
            //7 seria o raio
            glVertex2f(center_x + 7 * cos(theta), center_y + 7 * sin(theta));

        }
    glEnd();
    glPopMatrix();
}


//function for practical usages (check coordinates on the screen)
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xMouse, yMouse;
        glfwGetCursorPos(window, &xMouse, &yMouse);
        int x1 = static_cast<int>(xMouse);
        int y1 = winHeight - static_cast<int>(yMouse); // Adjust y coordinate
        std::cout << "Mouse clicked at (" << x1 << ", " << y1 << ")" << std::endl;
    }
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_R) {
            step_angle = -1.0f;
        }
        else if (key == GLFW_KEY_L) {
            step_angle= 1.0f;
        }
        else if (key == GLFW_KEY_ESCAPE) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
        else{
            cerr << "press L, or R, or ESC!" <<endl;
        }
    }
}


int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Set GLFW window properties with compatible profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(winWidth, winHeight, "Turbine Simulation", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    //current window = window
    glfwMakeContextCurrent(window);

    // Initialize GLEW allow beta opengl functions
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // Initialize OpenGL settings custom function
    init();
    glfwSetKeyCallback(window, keyCallback);

    //set mouse config (window, function)
    glfwSetMouseButtonCallback(window, mouseButtonCallback);;
    // Main loop with core function (it checks whether to close or not)
    //it will keep spinning while it doesnt close
    while (!glfwWindowShouldClose(window)) {
        // Draw windmill custom function
        drawWindmill();
        // Swap buffers to display what was on buffer and poll for events to check if something happened (input etc)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up and exit
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
