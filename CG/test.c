#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glu.h>
#include <GL/glut.h>

typedef struct
{
    float x;
    float y;
} Ponto;

Ponto poligono[100];
int count = 0;
float xMin = -0.5, xMax = 0.5, yMin = -0.5, yMax = 0.5;

// dados para poder adicionar bits no código
int ESQUERDA = 1;
int DIREITA = 2;
int BOT = 4;
int TOP = 8;

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

float interseccaoEmX(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
    float numerador = (x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4);
    float denominador = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    return numerador / denominador;
}

float interseccaoEmY(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
    float numerador = (x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4);
    float denominador = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    return numerador / denominador;
}

void desenharPoligono(Ponto poligonos[])
{
    int n = count; // Obtém o número de vértices do polígono

    // Desenha o polígono

    glColor3f(1, 0, 0);
    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < n; i++)
    {
        glVertex2f(poligonos[i].x, poligonos[i].y);
    }

    glEnd();
}
void recortadorEsquerda(Ponto p1, Ponto p2, Ponto novaForma[], int i)
{

}
void recortaPoligono()
{

}

void desenha()
{
    Ponto poligonoRecortado[100];
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

    desenharPoligono(poligono);
    recortadorEsquerda(poligono[0], poligono[1], poligonoRecortado, 0);
    glColor3f(0, 1, 0);
    // desenharPoligono(poligonoRecortado);

    // if (count == 2)
    // {

        // for (int i = 0; i < count; i++)
        // {
            // poligono[i] = poligonoRecortado[i];
        // }
    // }

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
            if (count < 4)
            {
                poligono[count].x = mouseX;
                poligono[count].y = mouseY;
                count++;
            }
        }
        break;

    default:
        break;
    }
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
    glutMouseFunc(mouseInteraction);
    glutMainLoop();

    return 0;
}