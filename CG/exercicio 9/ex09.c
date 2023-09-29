#include <GL/glut.h>
#include <math.h>

#define PI 3.141592654

int altura = 500;
int largura = 600;
float anguloRotacao = 0.0f;


void circulo(float raio)
{
  int i;
  float angulo = 0.0;
  glBegin(GL_POLYGON);
  for (i = 0; i <= 30; i++)
  {
    angulo = 2 * PI * i / 30.0;
    glVertex2f(raio * cos(angulo), raio * sin(angulo));
  }
  glEnd();
}

void desenhaCirculosAoRedorOrigem(int quantidade, float raioBase)
{
  for (int i = 0; i < quantidade; i++)
  {
    float angulo = i * (360.0 / quantidade);
    float x = raioBase * cos(angulo * PI / 180.0);
    float y = raioBase * sin(angulo * PI / 180.0);

    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glTranslatef(x, y, 0.0f);
    circulo(0.125);
    glPopMatrix();
  }
}

void init(void)
{
  glClearColor(1.0, 1.0, 1.0, 1.0);
}

void display(void)
{
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glClearColor(0, 0.4, 1, 0);
  glClear(GL_COLOR_BUFFER_BIT);

  int quantidade = 6;
  float raioBase = 0.2;

    // cabo
  glPushMatrix();
  glColor3f(0.0f, 1.0f, 0.0f);
  glTranslatef(0.0f, -0.8f, 0.0f);
  glBegin(GL_POLYGON);
  glVertex2f(-0.015, 0.7);
  glVertex2f(0.015, 0.7);
  glVertex2f(0.015, -0.7);
  glVertex2f(-0.015, -0.7);
  glEnd();
  glPopMatrix();


  glPushMatrix();
  glRotatef(anguloRotacao, 0.0f, 0.0f, 1.0f); // Aplica a rotação no eixo Z.
  desenhaCirculosAoRedorOrigem(quantidade, raioBase);
  glPopMatrix();


  // circulo
  glPushMatrix();
  glColor3f(1.0f, 1.0f, 0.0f);
  circulo(0.125);
  glPopMatrix();

  glFlush();
  
}

void keyboard(unsigned char key, int x, int y)
{
  switch (key)
  {
    case 'a':
      anguloRotacao -= 10.0f; // Rotaciona para a esquerda.
      break;
    case 'd':
      anguloRotacao += 10.0f; // Rotaciona para a direita.
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
  glutCreateWindow("Desenhando uma flor");
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