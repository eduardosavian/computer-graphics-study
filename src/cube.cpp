#ifndef CUBE_CPP
#define CUBE_CPP


#include "cube.hpp"


Cube::Cube() {
    // Define the 8 vertices of the cube
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
    }
    glutPostRedisplay(); // Notify GLUT that the display needs to be redrawn
}

void cube() {
    Cube cube = Cube();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpa o buffer de cor e o de profundidade
    glMatrixMode(GL_MODELVIEW);     // Operar na matriz de ModelView

    srand(time(NULL));
    glLoadIdentity();                 // Reseta para a matriz identidade
    glTranslatef(0.0f, 0.0f, -7.0f);  // Move para a direita da view o que será desenhado
    glRotatef(angleX, 1.0f, 0.0f, 0.0f); // Rotaciona o cubo em torno do eixo X
    glRotatef(angleY, 0.0f, 1.0f, 0.0f); // Rotaciona o cubo em torno do eixo Y

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