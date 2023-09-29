#include <GL/glut.h>
#include <math.h>

#define PI 3.141592654

int altura = 500;
int largura = 600;
float anguloBracos = 0.0f;
float anguloPernas = 0.0f;
float anguloMax = 45.0f;  // Ângulo máximo das pernas
float anguloMin = -45.0f; // Ângulo mínimo das pernas
float anguloMinBraco = -150.0f; // Ângulo mínimo das pernas

void circulo(float raio, int segmentos)
{
    int i;
    float angulo = 0.0;
    glBegin(GL_POLYGON);
    for (i = 0; i < segmentos; i++) // Alterei de 15 para o número de segmentos desejados.
    {
        angulo = 2 * PI * i / segmentos;
        glVertex2f(raio * cos(angulo), raio * sin(angulo));
    }
    glEnd();
}

void desenhaBracos()
{
    // BRAÇO ESQUERDO
    glPushMatrix();
    glColor3f(0.5, 0.5, 0.5);
    glTranslatef(-0.15, 0.15, 0);               // Posição do braço esquerdo
    anguloBracos = fmax(anguloMinBraco, fmin(anguloMax, anguloBracos)); // Limita o ângulo

    glRotatef(anguloBracos, 0.0f, 0.0f, 1.0f); // Rotação do braço

    glBegin(GL_POLYGON);
    glVertex2f(-0.05, 0.0);
    glVertex2f(0.05, 0.0);
    glVertex2f(0.05, -0.4);
    glVertex2f(-0.05, -0.4);
    glEnd();

    glPopMatrix();

    // BRAÇO DIREITO
    glPushMatrix();
    glColor3f(0.5, 0.5, 0.5);
    glTranslatef(0.15, 0.15, 0);                 // Posição do braço direito
    anguloBracos = fmax(anguloMinBraco, fmin(anguloMax, anguloBracos)); // Limita o ângulo
    glRotatef(-anguloBracos, 0.0f, 0.0f, 1.0f); // Rotação do braço

    glBegin(GL_POLYGON);
    glVertex2f(-0.05, 0.0);
    glVertex2f(0.05, 0.0);
    glVertex2f(0.05, -0.4);
    glVertex2f(-0.05, -0.4);
    glEnd();

    glPopMatrix();
}

void desenhaPernas()
{
    // PERNA ESQUERDA
    glPushMatrix();
    glColor3f(0.5, 0.5, 0.5);
    glTranslatef(-0.1, -0.4, 0);                                               // Posição da perna esquerda
    anguloPernas = fmax(anguloMin, fmin(anguloMax, anguloPernas)); // Limita o ângulo
    glRotatef(anguloPernas, 0.0f, 0.0f, 1.0f);                                 // Rotação da perna

    glBegin(GL_POLYGON);
    glVertex2f(-0.05, 0.0);
    glVertex2f(0.05, 0.0);
    glVertex2f(0.05, -0.4);
    glVertex2f(-0.05, -0.4);
    glEnd();

    glPopMatrix();

    // PERNA DIREITA
    glPushMatrix();
    glColor3f(0.5, 0.5, 0.5);
    glTranslatef(0.1, -0.4, 0);                                                // Posição da perna direita
    anguloPernas = fmax(anguloMin, fmin(anguloMax, anguloPernas)); // Limita o ângulo
    glRotatef(-anguloPernas, 0.0f, 0.0f, 1.0f);                                // Rotação da perna

    glBegin(GL_POLYGON);
    glVertex2f(-0.05, 0.0);
    glVertex2f(0.05, 0.0);
    glVertex2f(0.05, -0.4);
    glVertex2f(-0.05, -0.4);
    glEnd();

    glPopMatrix();
}

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

void display(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    // chão
    glPushMatrix();
    glColor3f(0.1f, 0.1f, 0.1f);
    glTranslatef(0.0f, -1, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-1, 0.3);
    glVertex2f(1, 0.3);
    glVertex2f(1, -0.3);
    glVertex2f(-1, -0.3);
    glEnd();
    glPopMatrix();

    // BRAÇOS DO ROBO
    desenhaBracos();

    // Pernas
    desenhaPernas();

    // ---------------------------------------------------------------------------------
    // PESCOÇO DO ROBO
    glPushMatrix();
    glColor3f(0, 0, 0.8);
    glTranslatef(0, 0.3, 0);

    glBegin(GL_POLYGON);
    glVertex2f(-0.08, 0.1);
    glVertex2f(0.08, 0.1);
    glVertex2f(0.08, -0.1);
    glVertex2f(-0.08, -0.1);
    glEnd();

    glPopMatrix();

    // ---------------------------------------------------------------------------------
    // CABEÇA DO ROBO
    glPushMatrix();
    glColor3f(0, 0, 1);
    glTranslatef(0, 0.5, 0);

    circulo(0.2, 8);

    glPopMatrix();

    // ---------------------------------------------------------------------------------
    // TRONCO DO ROBO
    glPushMatrix();
    glColor3f(0, 0.9, 0.3);
    glTranslatef(0, 0.01, 0);

    glBegin(GL_POLYGON);
    glVertex2f(-0.2, 0.25);
    glVertex2f(0.2, 0.25);
    glVertex2f(0.2, -0.25);
    glVertex2f(-0.2, -0.25);
    glEnd();

    glPopMatrix();

    // ---------------------------------------------------------------------------------
    // CINTURA DO ROBÔ
    glPushMatrix();
    glColor3f(0.5, 0.5, 0.5);
    glTranslatef(0, -0.4, 0);

    glBegin(GL_POLYGON);
    glVertex2f(-0.2, 0.1);
    glVertex2f(0.2, 0.1);
    glVertex2f(0.15, -0.1);
    glVertex2f(-0.15, -0.1);
    glEnd();

    glColor3f(0, 0, 0);
    glBegin(GL_QUADS);
    glVertex2f(-0.2, 0.1);
    glVertex2f(0.2, 0.1);
    glVertex2f(0.2, 0.2);
    glVertex2f(-0.2, 0.2);
    glEnd();

    glPopMatrix();

    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'a':
        anguloBracos += 10.0f; // Rotaciona os braços para a esquerda.
        break;
    case 'd':
        anguloBracos -= 10.0f; // Rotaciona os braços para a direita.
        break;
    case 'w':
        anguloPernas += 10.0f; // Rotaciona as pernas para a esquerda.
        break;
    case 's':
        anguloPernas -= 10.0f; // Rotaciona as pernas para a direita.
        break;
    default:
        break;
    }
    glutPostRedisplay(); // Solicita uma atualização da janela.
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(largura, altura);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Desenhando um robo");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}


/*
  _________  ___  ___  ________  _____ ______   ________  ________
 |\___   ___\\  \|\  \|\   __  \|\   _ \  _   \|\   __  \|\   ____\
 \|___ \  \_\ \  \\\  \ \  \|\  \ \  \\\__\ \  \ \  \|\  \ \  \___|_
      \ \  \ \ \   __  \ \  \\\  \ \  \\|__| \  \ \   __  \ \_____  \
       \ \  \ \ \  \ \  \ \  \\\  \ \  \    \ \  \ \  \ \  \|____|\  \
        \ \__\ \ \__\ \__\ \_______\ \__\    \ \__\ \__\ \__\____\_\  \
         \|__|  \|__|\|__|\|_______|\|__|     \|__|\|__|\|__|\_________\

*/