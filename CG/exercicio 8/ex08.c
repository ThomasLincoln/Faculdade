
//  _________  ___  ___  ________  _____ ______   ________  ________
// |\___   ___\\  \|\  \|\   __  \|\   _ \  _   \|\   __  \|\   ____\     
// \|___ \  \_\ \  \\\  \ \  \|\  \ \  \\\__\ \  \ \  \|\  \ \  \___|_
//      \ \  \ \ \   __  \ \  \\\  \ \  \\|__| \  \ \   __  \ \_____  \   
//       \ \  \ \ \  \ \  \ \  \\\  \ \  \    \ \  \ \  \ \  \|____|\  \  
//        \ \__\ \ \__\ \__\ \_______\ \__\    \ \__\ \__\ \__\____\_\  \ 
//         \|__|  \|__|\|__|\|_______|\|__|     \|__|\|__|\|__|\_________\
//                                                            \|_________|

#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

int altura = 500;
int largura = 600;
int raio = 80;
float xGlobal = 250;
float yGlobal = 300;
float espessura = 1.0;

void init(void);
void display(void);
void keyboard(unsigned char key, int x, int y);
void bresenDraw(int x, int y, int raio);
void pontosDaCircunferencia(int x, int y, int xc, int yc);
void mouse(int button, int state, int x, int y);

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(largura, altura);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Desenhando um circulo");
  init();
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
  glutMainLoop();
  return 0;
}

void init(void)
{
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glOrtho(0, largura, 0, altura, -1, 1);
}

void display(void)
{
  glPointSize(espessura);

  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_POINTS);

  bresenDraw(xGlobal, yGlobal, raio);

  glEnd();
  glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
  switch (key)
  {
  case 'e':
    exit(0);
    break;
  case 'i':
    raio += 10;
    break;
  case 'I':
    raio += 10;
    break;
  case 'd':
    raio -= 10;
    break;
  case 'D':
    raio -= 10;
    break;
  default:
    break;
  }
}

void mouse(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
    xGlobal = x;
    yGlobal = altura - y;
  }
  // Solicita que a função de exibição seja chamada para atualizar a janela
  glutPostRedisplay();
}

void bresenDraw(int xc, int yc, int raio)
{
  int x = 0;
  int y = raio;
  int d = 1 - raio;
  pontosDaCircunferencia(x, y, xc, yc);
  while (y > x)
  {
    if (d < 0)
    {
      d = d + 2 * x + 3;
      x = x + 1;
    }
    else
    {
      d = d + 2 * (x - y) + 5;
      x = x + 1;
      y = y - 1;
    }
    pontosDaCircunferencia(x, y, xc, yc);
  }
}

void pontosDaCircunferencia(int x, int y, int xc, int yc)
{
  // Octantes
  glVertex2i(x + xc, y + yc);   // 1
  glVertex2i(y + xc, x + yc);   // 2
  glVertex2i(y + xc, -x + yc);  // 3
  glVertex2i(x + xc, -y + yc);  // 4
  glVertex2i(-x + xc, -y + yc); // 5
  glVertex2i(-y + xc, -x + yc); // 6
  glVertex2i(-y + xc, x + yc);  // 7
  glVertex2i(-x + xc, y + yc);  // 8
}
