#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <string.h>

float vertices[6];
int vertex_count;
float color1 = 0.0;
float color2 = 0.0;
float color3 = 1.0;

void ponto(float x, float y, float r, float g, float b)
{
    glPointSize(5.0);
    glColor3f(r, g, b);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
    glFlush();
}

void triangulo(float *vertices)
{
    // cria o triangulo usando os valores do array vertices, que tem valores do mouse
    glColor3f(color1, color2, color3);
    glBegin(GL_TRIANGLES);
    glVertex2f(vertices[0], vertices[1]);
    glVertex2f(vertices[2], vertices[3]);
    glVertex2f(vertices[4], vertices[5]);
    glEnd();
}

void desenha()
{
    // resetar a tela
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    // desenhar o triangulo
    if (vertex_count == 6)
    {
        triangulo(vertices);
    }

    // desenhar os pontos
    glColor3f(1.0, 1.0, 1.0);
    for (int i = 0; i < vertex_count; i += 2)
    {
        ponto(vertices[i], vertices[i + 1], color1, color2, color3);
    }

    // atualizar a tela
    glFlush();
}

void mouseInteraction(int botao, int estado, int x, int y)
{
    switch (botao)
    {
    case GLUT_LEFT_BUTTON:
        if (estado == GLUT_DOWN)
        {
            float mouseX = (float)x / glutGet(GLUT_WINDOW_WIDTH) * 2.0 - 1.0;
            float mouseY = 1.0 - (float)y / glutGet(GLUT_WINDOW_HEIGHT) * 2.0;

            if (vertex_count == 6)
            {
                vertex_count == 0;
            }
            else if (vertex_count < 6)
            {
                vertices[vertex_count++] = mouseX;
                vertices[vertex_count++] = mouseY;
            }
        }
        break;

    default:
        break;
    }
    glutPostRedisplay();
}

void keyboardInteraction(unsigned char key, int x, int y)
{
    switch (key)
    {
    case '1':
        color1 = 1.0;
        color2 = 0.0;
        color3 = 0.0;
        break;
    case '2':
        color1 = 0.0;
        color2 = 1.0;
        color3 = 0.0;
        break;
    case '3':
        color1 = 1.0;
        color2 = 1.0;
        color3 = 0.0;
        break;
    case '4':
        color1 = 1.0;
        color2 = 1.0;
        color3 = 1.0;
        break;
    case '5':
        color1 = 0.5;
        color2 = 0.5;
        color3 = 0.0;
        break;
    case '6':
        color1 = 0.2;
        color2 = 0.4;
        color3 = 0.6;
        break;
    case '7':
        color1 = 1.0;
        color2 = 0.75;
        color3 = 0.8;
        break;
    case '8':
        color1 = 1.0;
        color2 = 0.5;
        color3 = 0.0;
        break;
    case '9':
        color1 = 0.5;
        color2 = 0.0;
        color3 = 1.0;
        break;
    case 'r':
        // resetar a tela
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);

        // resetar as variaveis
        vertex_count = 0;
        memset(vertices, 0, sizeof(vertices));
        color1 = 0.0;
        color2 = 0.0;
        color3 = 1.0;

        // reesetar a tela
        glutSwapBuffers();
        break;
    case 'R':
        // resetar a tela
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);

        // resetar as variaveis
        vertex_count = 0;
        memset(vertices, 0, sizeof(vertices));
        color1 = 0.0;
        color2 = 0.0;
        color3 = 1.0;

        // reesetar a tela
        glutSwapBuffers();
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("Exercicio 4");
    glutDisplayFunc(desenha);
    glutMouseFunc(mouseInteraction);
    glutKeyboardFunc(keyboardInteraction);
    glutMainLoop();
    return 0;
}