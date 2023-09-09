#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

float location_x = 0.0; 
float location_y = 0.0;

void ponto(){
    glPointSize(5.0);
    glColor3f(0,0,1.0);
    glBegin(GL_POINTS);
    glVertex2f(location_x, location_y);
    glEnd();
    glFlush();
}

void desenha(){
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,1.0,1.0);
    ponto();
    glFlush();
}

void mouseInteraction(int botao, int estado, int x, int y){
    switch (botao)
    {
    case GLUT_LEFT_BUTTON : 
        if(estado == GLUT_DOWN){
            float mouseX = (float) x /glutGet(GLUT_WINDOW_WIDTH) * 2.0 - 1.0;
            float mouseY = 1.0 - (float) y /glutGet(GLUT_WINDOW_HEIGHT) * 2.0;
            location_x = mouseX;
            location_y = mouseY;
        }
        break;
    
    default:
        break;
    }
    glutPostRedisplay();
}

int main ( int argc , char * argv [] ){
    glutInit(&argc , argv); 
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (50 ,100);
    glutInitWindowSize (1000 ,1000);
    glutCreateWindow ("Exercicio 1");
    glutDisplayFunc(desenha);
    glutMouseFunc(mouseInteraction);
    glutMainLoop ();
    return 0;
}