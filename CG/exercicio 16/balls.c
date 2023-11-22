#include <GL/glut.h>
#include <math.h>

GLfloat scale = 0.2;

GLfloat angleRed = 0.0;
GLfloat angleGreen = 90.0;
GLfloat angleBlue = 180.0;
GLfloat angleYellow = 270.0;

GLfloat distance = 0.2;

GLfloat lightPosition[] = {0.0, 0.0, 0.3, 1.0};

int mouseX = 0;
int mouseY = 0;

void drawColoredSphere(GLfloat r, GLfloat g, GLfloat b, GLfloat angle) {
    GLfloat materialColor[] = {r, g, b, 1.0};

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);

    glPushMatrix();
    glRotatef(angle, 0.0, 0.0, 1.0);
    glTranslatef(distance, -0.3, 0.0);
    glutSolidSphere(0.5 * scale, 100, 100);
    glPopMatrix();
}

void drawAllSpheres() {
    drawColoredSphere(1.0, 0.0, 0.0, angleRed);
    drawColoredSphere(0.0, 1.0, 0.0, angleGreen);
    drawColoredSphere(0.0, 0.0, 1.0, angleBlue); 
    drawColoredSphere(0.0, 0.0, 1.0, angleBlue); 
    drawColoredSphere(1.0, 0.9, 0.0, angleYellow); 
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 2.0, 
              0.0, 0.0, 0.0, 
              0.0, 1.0, 0.0);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    drawAllSpheres();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void update(int value) {
    angleRed += 2.0;  
    angleGreen += 2.0;
    angleBlue += 2.0;  
    angleYellow += 2.0;  

    if (angleRed > 360.0) {
        angleRed -= 360.0;
    }

    if (angleGreen > 360.0) {
        angleGreen -= 360.0;
    }

    if (angleBlue > 360.0) {
        angleBlue -= 360.0;
    }

    if (angleYellow > 360.0) {
        angleYellow -= 360.0;
    }

    if(angleYellow >= 330){
        scale += 0.05;
    }
    if (angleYellow <= 330){
        scale = 0.2;
    }

    if(angleGreen >= 330){
        scale += 0.05;
    }
    if (angleGreen <= 330){
        scale = 0.2;
    }
    glutPostRedisplay();
    glutTimerFunc(1, update, 0);
}

void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        lightPosition[0] = (GLfloat)x / glutGet(GLUT_WINDOW_WIDTH) * 2.0 - 1.0;
        lightPosition[1] = 1.0 - (GLfloat)y / glutGet(GLUT_WINDOW_HEIGHT) * 2.0;
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500); 
    glutCreateWindow("Balls");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouseClick);
    glutTimerFunc(25, update, 0);
    glutMainLoop();
    return 0;
}

/*
 ______   __  __     ______     __    __     ______     ______    
/\__  _\ /\ \_\ \   /\  __ \   /\ "-./  \   /\  __ \   /\  ___\   
\/_/\ \/ \ \  __ \  \ \ \/\ \  \ \ \-./\ \  \ \  __ \  \ \___  \  
   \ \_\  \ \_\ \_\  \ \_____\  \ \_\ \ \_\  \ \_\ \_\  \/\_____\ 
    \/_/   \/_/\/_/   \/_____/   \/_/  \/_/   \/_/\/_/   \/_____/ 
                                                                  
*/ 