#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

float location_x = 0;
float location_y = 0;
float location_x2 = 0;
float location_y2 = 0;
float color1 = 0.0;
float color2 = 0.0;
float color3 = 1.0;

void mouseInteraction(int botao, int estado, int x, int y)
{
    static int count = 0;
    switch (botao)
    {
    case GLUT_LEFT_BUTTON:
        if (estado == GLUT_DOWN)
        {
            if (count == 0)
            {
                location_x = x;
                location_y = 500 - y;
                count++;
            }
            else if (count == 1)
            {
                location_x2 = x;
                location_y2 = 500 -y;
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

void ponto(float x, float y, float r, float g, float b)
{
    glPointSize(3.0);
    glColor3f(color1, color2, color3);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}

void invertPoint(int xi, int yi, int xf, int yf)
{
    int aux = xi;
    xi = xf;
    xf = aux;
    //
    aux = yi;
    yi = yf;
    yf = aux;
}

void bresenham(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx, sy;

    if (x1 < x2) sx = 1;
    else sx = -1;

    if (y1 < y2) sy = 1;
    else sy = -1;

    int err = dx - dy;

    while (1) {
        ponto(x1, y1, color1, color2, color3);

        if (x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;

        if (e2 > -dy) {
            err = err - dy;
            x1 = x1 + sx;
        }

        if (e2 < dx) {
            err = err + dx;
            y1 = y1 + sy;
        }
    }
}

void desenha()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    ponto(location_x, location_y, color1, color2, color3);
    ponto(location_x2, location_y2, color1, color2, color3);

    bresenham(location_x, location_y, location_x2, location_y2);
    glFlush();
}

void init()
{
    glViewport(0, 0, 500, 500);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Exercicio 6");
    glutDisplayFunc(desenha);
    glutMouseFunc(mouseInteraction);
    glutKeyboardFunc(keyboardInteraction);
    glutReshapeFunc(init);
    glutMainLoop();
    return 0;
}

//  _________  ___  ___  ________  _____ ______   ________  ________      
// |\___   ___\\  \|\  \|\   __  \|\   _ \  _   \|\   __  \|\   ____\     
// \|___ \  \_\ \  \\\  \ \  \|\  \ \  \\\__\ \  \ \  \|\  \ \  \___|_    
//      \ \  \ \ \   __  \ \  \\\  \ \  \\|__| \  \ \   __  \ \_____  \   
//       \ \  \ \ \  \ \  \ \  \\\  \ \  \    \ \  \ \  \ \  \|____|\  \  
//        \ \__\ \ \__\ \__\ \_______\ \__\    \ \__\ \__\ \__\____\_\  \ 
//         \|__|  \|__|\|__|\|_______|\|__|     \|__|\|__|\|__|\_________\
//                                                            \|_________|
                                                                       
                                                                       