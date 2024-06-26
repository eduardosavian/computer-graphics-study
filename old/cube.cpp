#ifndef CUBE_CPP
#define CUBE_CPP


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>

#include "cube.hpp"


Cube::Cube() {
    vertices = {
        -1.0, -1.0, -1.0,  // Vertex 0
        1.0, -1.0, -1.0,  // Vertex 1
        1.0,  1.0, -1.0,  // Vertex 2
        -1.0,  1.0, -1.0,  // Vertex 3
        -1.0, -1.0,  1.0,  // Vertex 4
        1.0, -1.0,  1.0,  // Vertex 5
        1.0,  1.0,  1.0,  // Vertex 6
        -1.0,  1.0,  1.0   // Vertex 7
    };

    // Define as 12 arestas do cubo
    edges = {
        0, 1, // Aresta 0
        1, 2, // Aresta 1
        2, 3, // Aresta 2
        3, 0, // Aresta 3
        4, 5, // Aresta 4
        5, 6, // Aresta 5
        6, 7, // Aresta 6
        7, 4, // Aresta 7
        0, 4, // Aresta 8
        1, 5, // Aresta 9
        2, 6, // Aresta 10
        3, 7  // Aresta 11
    };
}

GLfloat colors[32][3] = {
    {0.0f, 1.0f, 0.0f},    // Green
    {1.0f, 0.5f, 0.0f},    // Orange
    {1.0f, 0.0f, 0.0f},    // Red
    {1.0f, 1.0f, 0.0f},    // Yellow
    {0.0f, 0.0f, 1.0f},    // Blue
    {1.0f, 0.0f, 1.0f},    // Magenta
    {0.5f, 0.5f, 0.5f},    // Gray
    {0.0f, 1.0f, 1.0f},    // Cyan
    {1.0f, 0.0f, 0.5f},    // Violet
    {0.5f, 0.0f, 0.5f},    // Purple
    {0.0f, 0.5f, 0.5f},    // Teal
    {0.5f, 0.5f, 1.0f},    // Sky Blue
    {0.8f, 0.8f, 0.8f},    // Light Gray
    {0.5f, 0.0f, 0.0f},    // Maroon
    {0.0f, 0.5f, 0.0f},    // Lime
    {0.0f, 0.0f, 0.5f},    // Navy
    {0.7f, 0.7f, 0.0f},    // Olive
    {0.5f, 0.0f, 0.5f},    // Indigo
    {1.0f, 0.5f, 0.5f},    // Light Red
    {0.5f, 1.0f, 0.5f},    // Light Green
    {1.0f, 1.0f, 0.5f},    // Light Yellow
    {0.5f, 0.5f, 1.0f},    // Light Blue
    {1.0f, 0.5f, 1.0f},    // Light Magenta
    {0.8f, 0.8f, 0.0f},    // Dark Yellow
    {0.5f, 1.0f, 1.0f},    // Light Cyan
    {1.0f, 0.0f, 0.8f},    // Dark Magenta
    {0.0f, 0.8f, 1.0f},    // Lighter Blue
    {0.7f, 0.0f, 0.7f},    // Dark Purple
    {0.0f, 0.7f, 0.7f},    // Dark Cyan
    {0.7f, 0.7f, 0.7f},    // Dark Gray
    {0.3f, 0.3f, 0.3f},    // Very Dark Gray
    {0.5f, 0.0f, 0.2f}    // Dark Maroon
};


// Global variable to hold the rotation angles
GLfloat angleX = 0.0f;
GLfloat angleY = 0.0f;
GLfloat angleZ = 0.0f;
GLfloat factor = 1.0f;
GLfloat XX = 0.0f;
GLfloat YY = 0.f;
GLfloat ZZ = -7.0f;

Cube cube;

// Handle key press events
void handleKeypress(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': // Rotate clockwise around X axis when 'w' is pressed
            angleX += 1.0f;
            break;
        case 's': // Rotate counterclockwise around X axis when 's' is pressed
            angleX -= 1.0f;
            break;
        case 'a': // Rotate clockwise around Y axis when 'a' is pressed
            angleY += 1.0f;
            break;
        case 'd': // Rotate counterclockwise around Y axis when 'd' is pressed
            angleY -= 1.0f;
            break;
        case 'z': // Rotate clockwise around Z axis when 'q' is pressed
            angleZ += 1.0f;
            break;
        case 'x': // Rotate counterclockwise around Z axis when 'e' is pressed
            angleZ -= 1.0f;
            break;
        case 'f': // Make the cube bigger
            factor += 0.1; // Increase size by 10%
            break;
        case 'r': // Make the cube smaller
            factor -= 0.1; // Decrease size by 10%
            break;
        case 'h': // Translate left
            XX -= 0.1f;
            break;
        case 'j': // Translate down
            YY -= 0.1f;
            break;
        case 'k': // Translate up
            YY += 0.1f;
            break;
        case 'l': // Translate right
            XX += 0.1f;
            break;
        case 'i': // Translate up
            ZZ += 0.1f;
            break;
        case 'o': // Translate right
            ZZ -= 0.1f;
            break;

    }
    glutPostRedisplay(); // Notify GLUT that the display needs to be redrawn
}


// Rotation around X axis
void  Cube::rotateX(std::vector<double>& vertices, double angle) {
    double c = cos(angle * 3.141592653589793 / 180.0);
    double s = sin(angle * 3.141592653589793 / 180.0);

    for (size_t i = 0; i < vertices.size(); i += 3) {
        double y = vertices[i + 1];
        double z = vertices[i + 2];
        vertices[i + 1] = y * c - z * s;
        vertices[i + 2] = y * s + z * c;
    }
}


// Rotation around Y axis
void Cube::rotateY(std::vector<double>& vertices, double angle) {
    double c = cos(angle * 3.141592653589793 / 180.0);
    double s = sin(angle * 3.141592653589793 / 180.0);

    for (size_t i = 0; i < vertices.size(); i += 3) {
        double x = vertices[i];
        double z = vertices[i + 2];
        vertices[i] = x * c + z * s;
        vertices[i + 2] = -x * s + z * c;
    }
}

// Rotation around Z axis
void Cube::rotateZ(std::vector<double>& vertices, double angle) {
    double c = cos(angle * 3.141592653589793 / 180.0);
    double s = sin(angle * 3.141592653589793 / 180.0);

    for (size_t i = 0; i < vertices.size(); i += 3) {
        double x = vertices[i];
        double y = vertices[i + 1];
        vertices[i] = x * c - y * s;
        vertices[i + 1] = x * s + y * c;
    }
}


// Display the cube
void displayCube() {
    srand(time(NULL));

    cube = Cube();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpa o buffer de cor e o de profundidade
    glMatrixMode(GL_MODELVIEW);     // Operar na matriz de ModelView

    glLoadIdentity(); // Reseta para a matriz identidade

    for (size_t i = 0; i < cube.vertices.size(); ++i) {
        cube.vertices[i] *= factor;
    }

    // Apply rotation around X axis
    cube.rotateX(cube.vertices, angleX);
    // Apply rotation around Y axis
    cube.rotateY(cube.vertices, angleY);
    // Apply rotation around Z axis
    cube.rotateZ(cube.vertices, angleZ);

    for (size_t i = 0; i < cube.vertices.size(); i += 3) {
        cube.vertices[i] += XX;
        cube.vertices[i + 1] += YY;
        cube.vertices[i + 2] += ZZ;
    }

    for (size_t i = 0; i < cube.vertices.size(); i += 3) {
        std::cout << "VerStex " << i / 3 << ": (" << cube.vertices[i] << ", " << cube.vertices[i + 1] << ", " << cube.vertices[i + 2] << ")" << std::endl;
    }

    glBegin(GL_LINES);                // Começa a desenhar as linhas do cubo
    for (uint i = 0; i < cube.edges.size(); i += 2) {
        // Muda a cor a cada iteração
        int colorIndex = rand() % 32;  // Gera um índice aleatório dentro do intervalo de cores
        glColor3fv(colors[colorIndex]);

        // Desenha as arestas do cubo
        for (uint j = 0; j < 2; ++j) {
            int vertexIndex = cube.edges[i + j];
            double x = cube.vertices[vertexIndex * 3];
            double y = cube.vertices[vertexIndex * 3 + 1];
            double z = cube.vertices[vertexIndex * 3 + 2];
            glVertex3d(x, y, z);
        }
    }

    glEnd();
    glutSwapBuffers();  // Double Buffer, troca o atual pelo que está aguardando
}


#endif