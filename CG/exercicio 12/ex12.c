#include <GL/glut.h>

float angX = 0;
float angY = 0;
float angZ = 0;

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'a':
        if (angY > 0)
        {
            angY = 0;
        }
        angY -= 0.1f; // Rotaciona a esfera para a esquerda.
        break;
    case 'd':
        if (angY < 0)
        {
            angY = 0;
        }
        angY += 0.1f; // Rotaciona a esfera para a direita.
        break;
    case 'w':
        if (angX < 0)
        {
            angX = 0;
        }
        angX += 0.1f; // Rotaciona a esfera para a direita.
        break;
    case 's':
        if (angX < 0)
        {
            angX = 0;
        }
        angX -= 0.1f; // Rotaciona a esfera para a direita.
    default:
        break;
    }
    glutPostRedisplay(); // Solicita uma atualização da janela.
}

void palhaco()
{
    glPushMatrix();
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(0, 0, 0.25);
    glutSolidSphere(0.25, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0, -0.05, 0.4);
    glutSolidSphere(0.12, 20, 20);
    glPopMatrix();

    // Adicione dois olhos usando glutSolidSphere
    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);        // Cor preta para os olhos.
    glTranslatef(-0.08, 0.05, 0.45); // Posição do primeiro olho.
    glutSolidSphere(0.03, 20, 20);   // Primeiro olho.
    glTranslatef(0.16, 0.0, 0.0);    // Posição do segundo olho (deslocado horizontalmente).
    glutSolidSphere(0.06, 20, 20);   // Segundo olho.
    glPopMatrix();

    // Adicione um cone verde na cabeça do palhaço
    glPushMatrix();
    glColor3f(0.0, 1.0, 0.0);        // Cor verde para o cone.
    glTranslatef(0, 0.2, 0.3);       // Posição do cone na cabeça.
    glRotatef(-90, 1, 0, 0);         // Rotação do cone para que a base esteja voltada para cima.
    glutSolidCone(0.1, 0.2, 20, 20); // Desenha o cone.
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);
    glTranslatef(-0.2, 0, 0.2);
    glutSolidSphere(0.12, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);
    glTranslatef(0.2, 0, 0.2);
    glutSolidSphere(0.12, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);
    glTranslatef(0.15, 0, 0.1);
    glutSolidSphere(0.12, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);
    glTranslatef(0.09, 0, 0.05);
    glutSolidSphere(0.12, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);
    glTranslatef(0.05, 0, 0.02);
    glutSolidSphere(0.12, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);
    glTranslatef(0.02, 0, 0);
    glutSolidSphere(0.12, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);
    glTranslatef(-0.02, 0, 0);
    glutSolidSphere(0.12, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);
    glTranslatef(-0.05, 0, 0);
    glutSolidSphere(0.12, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);
    glTranslatef(-0.09, 0, 0);
    glutSolidSphere(0.12, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);
    glTranslatef(-0.15, 0, -0.02);
    glutSolidSphere(0.12, 20, 20);
    glPopMatrix();



    glPopMatrix();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glRotatef(angY, 0, 1, 0);
    glRotatef(angX, 1, 0, 0);

    palhaco(); // Desenhe o palhaço, que permanecerá fixo.

    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Palhaço 3D");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard); // Adicione a função de teclado.
    glMatrixMode(GL_MODELVIEW);
    glutMainLoop();
    return 0;
}
