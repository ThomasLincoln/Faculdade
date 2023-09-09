#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

float location_x = 0.0;
float location_y = 0.0;
float location_x2 = 0.0;
float location_y2 = 0.0;
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

void linha(float x1, float y1, float x2, float y2)
{
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void desenha()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    // desenhar a linha
    linha(location_x, location_y, location_x2, location_y2);

    glColor3f(1.0, 1.0, 1.0);
    ponto(location_x, location_y, color1, color2, color3);
    glFlush();
}

void mouseInteraction(int botao, int estado, int x, int y)
{
    static int count = 0;
    switch (botao)
    {
    case GLUT_LEFT_BUTTON:
        if (estado == GLUT_DOWN)
        {
            float mouseX = (float)x / glutGet(GLUT_WINDOW_WIDTH) * 2.0 - 1.0;
            float mouseY = 1.0 - (float)y / glutGet(GLUT_WINDOW_HEIGHT) * 2.0;

            if (count == 0)
            {
                location_x = mouseX;
                location_y = mouseY;
                count++;
            } else if (count == 1){
                location_x2 = mouseX;
                location_y2 = mouseY;
                count = 0;
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
    glutCreateWindow("Exercicio 3");
    glutDisplayFunc(desenha);
    glutMouseFunc(mouseInteraction);
    glutKeyboardFunc(keyboardInteraction);
    glutMainLoop();
    return 0;
}