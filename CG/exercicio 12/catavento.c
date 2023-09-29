#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <stdbool.h>

/*
  _________  ___  ___  ________  _____ ______   ________  ________
 |\___   ___\\  \|\  \|\   __  \|\   _ \  _   \|\   __  \|\   ____\     
 \|___ \  \_\ \  \\\  \ \  \|\  \ \  \\\__\ \  \ \  \|\  \ \  \___|_
      \ \  \ \ \   __  \ \  \\\  \ \  \\|__| \  \ \   __  \ \_____  \   
       \ \  \ \ \  \ \  \ \  \\\  \ \  \    \ \  \ \  \ \  \|____|\  \  
        \ \__\ \ \__\ \__\ \_______\ \__\    \ \__\ \__\ \__\____\_\  \ 
         \|__|  \|__|\|__|\|_______|\|__|     \|__|\|__|\|__|\_________\
  
*/

const double PI = 3.141592654;
int NumeroFrames = 0;
double Velocidade = 1.0; 
bool Girar = true;
const double VelocidadeMinima = 0.1; 
const double IncrementoVelocidade = 0.05; 

void catavento() {
    int i;
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.05f, 0);
    glVertex2f(0.05f, 0);
    glVertex2f(0.05f, 3);
    glVertex2f(-0.05f, 3);
    glEnd();
    glTranslatef(0, 3, 0);
    glRotated((1 * (NumeroFrames * (180.0/70))), 0, 0, 1);
    glColor3f(1.0f, 1.0f, 1.0f);
    for (i = 0; i < 4; i++) {
        glRotated(90, 0, 0, 1);
        glBegin(GL_POLYGON);
        glVertex2f(0, 0);
        glVertex2f(0.5f, 0.3f);
        glVertex2f(0.9f, -1.0f);
        glEnd();
    }

    glColor3f(1.0f, 1.0f, 1.0f); 
    glBegin(GL_POLYGON);
    glVertex2f(-0.2f, -0.2f);
    glVertex2f(0.2f, -0.2f);
    glVertex2f(0.2f, 0.2f);
    glVertex2f(-0.2f, 0.2f);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glPushMatrix();
    glTranslated(3.5, -0.7, 1);
    glScaled(1.0, 1.0, 1);
    catavento();
    glPopMatrix();
    glutSwapBuffers();
}

void doFrame(int v) {
    NumeroFrames++;
    glutPostRedisplay();
    if (Girar) {
        glutTimerFunc(20 / Velocidade, doFrame, 0);
    }
}

void aumentarVelocidade() {
    Girar = true;
    Velocidade += IncrementoVelocidade;
    glutTimerFunc(20 / Velocidade, doFrame, 0);
}

void diminuirVelocidade() {
    Velocidade -= IncrementoVelocidade;
    if (Velocidade < VelocidadeMinima) {
        Velocidade = VelocidadeMinima;
        Girar = false;
    }
}

void init() {
	glClearColor(0.0f, 0.0f, 0, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 7, -1, 4, -1, 1);
	glMatrixMode(GL_MODELVIEW);
}

void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            aumentarVelocidade();
            break;
        case GLUT_KEY_DOWN:
            diminuirVelocidade();
            break;
        default:
            break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(800,800);
    glutCreateWindow("Catavento");
    init();
    glutDisplayFunc(display);   
    glutTimerFunc(200,doFrame,0);
    glutSpecialFunc(specialKeys);
    glutMainLoop(); 
    return 0;
}    