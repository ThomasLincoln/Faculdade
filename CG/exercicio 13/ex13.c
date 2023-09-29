#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*

Thomas Lincoln - 156603
Pedro Ito - 159515
Leonardo Scadelai - 156690

*/

float thetaX = 0.0;
float thetaY = 0.0;
float angulo = -45.0;
bool praFrente = false;

void cubo()
{
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.25, 0.25, 0.25);
    glVertex3f(0.25, 0.25, 0.25);
    glVertex3f(0.25, -0.25, 0.25);
    glVertex3f(-0.25, -0.25, 0.25);
    glEnd();
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.25, 0.25, -0.25);
    glVertex3f(0.25, 0.25, -0.25);
    glVertex3f(0.25, -0.25, -0.25);
    glVertex3f(-0.25, -0.25, -0.25);
    glEnd();
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(0.25, -0.25, 0.25);
    glVertex3f(0.25, 0.25, 0.25);
    glVertex3f(0.25, 0.25, -0.25);
    glVertex3f(0.25, -0.25, -0.25);
    glEnd();
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.25, -0.25, 0.25);
    glVertex3f(-0.25, 0.25, 0.25);
    glVertex3f(-0.25, 0.25, -0.25);
    glVertex3f(-0.25, -0.25, -0.25);
    glEnd();
    glColor3f(1.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.25, 0.25, 0.25);
    glVertex3f(0.25, 0.25, 0.25);
    glVertex3f(0.25, 0.25, -0.25);
    glVertex3f(-0.25, 0.25, -0.25);
    glEnd();
    glColor3f(0.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.25, -0.25, 0.25);
    glVertex3f(0.25, -0.25, 0.25);
    glVertex3f(0.25, -0.25, -0.25);
    glVertex3f(-0.25, -0.25, -0.25);
    glEnd();
}

void desenha()
{
    glClearColor(0, 0, 0, 0); // Preto
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // CABEÇA
    glPushMatrix();
    glRotatef(thetaX, 1.0, 0.0, 0.0);
    glRotatef(thetaY, 0.0, 1.0, 0.0);
    glScalef(0.7, 0.7, 0.7);
    glTranslatef(0, 0.6, 0);
    cubo();
    glPopMatrix();

    // CORPO
    glPushMatrix();
    glRotatef(thetaX, 1.0, 0.0, 0.0);
    glRotatef(thetaY, 0.0, 1.0, 0.0);
    glScalef(0.7, 1, 0.4);
    glTranslatef(0, 0, 0);
    cubo();
    glPopMatrix();

    // BRAÇO
    glPushMatrix();
    glRotatef(thetaX, 100.0, 0.0, 0.0);
    glRotatef(thetaY, 0.0, 1.0, 0.0);

    glPushMatrix();
    glTranslatef(0.0, 0.25, 0.0);
    glRotatef(angulo, 1.0, 0.0, 0.0);
    glTranslatef(0.0, -0.25, 0.0);
    glScalef(-0.35, 1, 0.4);
    glTranslatef(-0.7, 0, 0);
    cubo();
    glPopMatrix();

    glPopMatrix();

    // BRAÇO
    glPushMatrix();
    glRotatef(thetaX, 100.0, 0.0, 0.0);
    glRotatef(thetaY, 0.0, 1.0, 0.0);

    glPushMatrix();

    glTranslatef(0.0, 0.25, 0.0);
    glRotatef(-angulo, 1.0, 0.0, 0.0);
    glTranslatef(0.0, -0.25, 0.0);

    glScalef(0.35, 1, 0.4);
    glTranslatef(-0.7, 0, 0);
    cubo();
    glPopMatrix();

    glPopMatrix();

    // PERNA
    glPushMatrix();
    glRotatef(thetaX, 100.0, 0.0, 0.0);
    glRotatef(thetaY, 0.0, 1.0, 0.0);

    glPushMatrix();
    glTranslatef(0.425, 0.15, -0.3);
    glRotatef(-45, 1.0, 0.0, 0.0);
    glTranslatef(-0.25, -0.25, 0.0);
    glScalef(-0.35, 1, 0.4);
    glTranslatef(0.28, -0.5, 0);
    cubo();
    glPopMatrix();

    glPopMatrix();

    // PERNA
    glPushMatrix();
    glRotatef(thetaX, 100.0, 0.0, 0.0);
    glRotatef(thetaY, 0.0, 1.0, 0.0);

    glPushMatrix();
    glTranslatef(-0.425, 0.15, 0.3);
    glRotatef(45, 1.0, 0.0, 0.0);
    glTranslatef(0.25, -0.25, 0.0);
    glScalef(-0.35, 1, 0.4);
    glTranslatef(-0.28, -0.5, 0);
    cubo();
    glPopMatrix();

    glFlush();
}

void tecladoEspecial(unsigned char tecla, int x, int y)
{
    switch (tecla)
    {
    case 'd':
        thetaY += 2;
        break;
    case 'a':
        thetaY -= 2;
        break;
    case 'w':
        thetaX += 2;
        break;
    case 's':
        thetaX -= 2;
        break;
    case 'e':
        if (praFrente)
        {
            angulo -= 5;
        }
        else
        {
            angulo +=5;
        }
        if (angulo == 45)
        {
            praFrente = !praFrente;
        }
        if (angulo == -45)
        {
            praFrente = !praFrente;
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
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("STEVEMINECRAFT");
    glutDisplayFunc(desenha);
    glutKeyboardFunc(tecladoEspecial);
    glutMainLoop();
    return 0;
}