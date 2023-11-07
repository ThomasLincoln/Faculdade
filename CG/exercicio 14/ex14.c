#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glu.h>
#include <GL/glut.h>

float xMin = -0.5, xMax = 0.5, yMin = -0.5, yMax = 0.5;
float pos_x1 = -0.7, pos_y1 = -0.6;
float pos_x2 = 0.6, pos_y2 = 0.9;

int count = 0;

// dados para poder adicionar bits no código
int ESQUERDA = 1;
int DIREITA = 2;
int BOT = 4;
int TOP = 8;

// flags para saber se passa pelo código de clip ou não
int Clip_Flag = 0, Flag = 1;

int C1, C2;

int ObterCodigo(float x, float y)
{
    int Code = 0;
    if (x < xMin)
        Code = Code | ESQUERDA;
    if (x > xMax)
        Code = Code | DIREITA;
    if (y < yMin)
        Code = Code | BOT;
    if (y > yMax)
        Code = Code | TOP;
    return Code;
}

void Clip()
{
    int C;
    float x, y;
    if (C1)
    {
        C = C1;
    }
    else
    {
        C = C2;
    }

    if (C & ESQUERDA)
    {
        x = xMin;
        y = pos_y1 + (pos_y2 - pos_y1) * ((xMin - pos_x1) / (pos_x2 - pos_x1));
    }

    if (C & DIREITA)
    {
        x = xMax;
        y = pos_y1 + (pos_y2 - pos_y1) * ((xMax - pos_x1) / (pos_x2 - pos_x1));
    }
    if (C & BOT)
    {
        y = yMin;
        x = pos_x1 + (pos_x2 - pos_x1) * ((yMin - pos_y1) / (pos_y2 - pos_y1));
    }

    if (C & TOP)
    {
        y = yMax;
        x = pos_x1 + (pos_x2 - pos_x1) * ((yMax - pos_y1) / (pos_y2 - pos_y1));
    }

    if (C == C1)
    {
        pos_x1 = x;
        pos_y1 = y;
    }
    else
    {
        pos_x2 = x;
        pos_y2 = y;
    }
}

void desenha()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    // retangulo
    glColor3f(1, 1, 1);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xMin, yMin);
    glVertex2f(xMax, yMin);
    glVertex2f(xMax, yMax);
    glVertex2f(xMin, yMax);
    glEnd();

    glColor3f(1, 0, 0);
    // se ele estiver dentro ele desenha sem recortar
    if (Flag == 1)
    {

        glBegin(GL_LINES);
        glVertex2f(pos_x1, pos_y1);
        glVertex2f(pos_x2, pos_y2);
        glEnd();
    }

    // se tivermos ligado o valor de corte ele vai começar a recortar
    while (1 & Clip_Flag == 1)
    {

        C1 = ObterCodigo(pos_x1, pos_y1);
        C2 = ObterCodigo(pos_x2, pos_y2);

        if ((C1 | C2) == 0)
        {
            break;
        }
        else if ((C1 & C2) != 0)
        {
            Flag = 0;
            break;
        }
        else
            Clip();
    }
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

            if (count == 0)
            {
                pos_x1 = mouseX;
                pos_y1 = mouseY;
                count++;
            }
            else if (count == 1)
            {
                pos_x2 = mouseX;
                pos_y2 = mouseY;
                count = 0;
            }
        }
        break;

    default:
        break;
    }
    glutPostRedisplay();
}

void key(unsigned char ch, int x, int y)
{
    Clip_Flag = 1;
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(50, 100);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Exercicio 14");
    glutDisplayFunc(desenha);
    glutKeyboardFunc(key);
    glutMouseFunc(mouseInteraction);
    glutMainLoop();

    return 0;
}