#include <GL/glut.h>
#include <math.h>

#define PI 3.141592654

int altura = 500;
int largura = 600;
float anguloRotacao = 0.0f;
float posicaoX = 0.0f; // Posição horizontal das esferas

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

void desenhaRodas(float raioBase)
{
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glTranslatef(-0.5, 0, 0.0f); // Adicione posicaoX para mover a esfera
    circulo(0.125, 10);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glTranslatef(0.5, 0, 0.0f); // Adicione posicaoX para mover a esfera
    circulo(0.125, 10);
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

    int quantidade = 6;
    float raioBase = 0.2;

    // chão
    glPushMatrix();
    glColor3f(0.1f, 0.1f, 0.1f);
    glTranslatef(0.0f, -1, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-1, 0.2);
    glVertex2f(1, 0.2);
    glVertex2f(1, -0.2);
    glVertex2f(-1, -0.2);
    glEnd();
    glPopMatrix();

    // Rodas
    glPushMatrix();
    glColor3f(0.5f, 0.5f, 0.5f);
    glTranslatef(-0.3f + posicaoX, -0.8f, 0.0f); // Translação para a posição da primeira roda
    glRotatef(anguloRotacao, 0.0f, 0.0f, 1.0f);  // Aplica a rotação no eixo Z.
    circulo(0.125, 4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.3f + posicaoX, -0.8f, 0.0f); // Translação para a posição da segunda roda
    glRotatef(anguloRotacao, 0.0f, 0.0f, 1.0f); // Aplica a rotação no eixo Z.
    circulo(0.125, 4);
    glPopMatrix();

    // ---------------------------------------------------------------------------------

    // carcaça do carro
    glPushMatrix();
    glColor3f(0.1f, 1, 0.1f);
    glTranslatef(0.0f+posicaoX, -0.65, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.5, 0.1);
    glVertex2f(0.5, 0.1);
    glVertex2f(0.5, -0.1);
    glVertex2f(-0.5, -0.1);
    glEnd();
    glPopMatrix();

        // carcaça do carro
    glPushMatrix();
    glColor3f(0.1f, 1, 0.1f);
    glTranslatef(0.0f+posicaoX, -0.45, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.25, 0.1);
    glVertex2f(0.25, 0.1);
    glVertex2f(0.25, -0.1);
    glVertex2f(-0.25, -0.1);
    glEnd();
    glPopMatrix();

    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'a':
        anguloRotacao += 10.0f; // Rotaciona para a esquerda.
        posicaoX -= 0.01;
        break;
    case 'd':
        anguloRotacao -= 10.0f; // Rotaciona para a direita.
        posicaoX += 0.01;
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
    glutCreateWindow("Desenhando um carro");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
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
//  