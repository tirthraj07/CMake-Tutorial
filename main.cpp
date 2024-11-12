#include "GLFW/glfw3.h"
#include <stdlib.h>
#include <stdio.h>

void drawTriangle() {
    glBegin(GL_TRIANGLES); // Start drawing a triangle
    glColor3f(1.0f, 0.0f, 0.0f); // Red vertex
    glVertex2f(-0.5f, -0.5f);

    glColor3f(0.0f, 1.0f, 0.0f); // Green vertex
    glVertex2f(0.5f, -0.5f);

    glColor3f(0.0f, 0.0f, 1.0f); // Blue vertex
    glVertex2f(0.0f, 0.5f);
    glEnd(); // End drawing
}

int main() {
    GLFWwindow* window;

    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
    window = glfwCreateWindow(300, 300, "Simple Triangle", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to open GLFW window\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Clear the screen with a background color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Dark teal color
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw a triangle
        drawTriangle();

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
