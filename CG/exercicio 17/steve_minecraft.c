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

typedef struct JPGImage
{
    int   width;
    int   height;
    char *data;
}JPGImage;

/* Qtd máxima de texturas a serem usadas no programa */
#define MAX_NO_TEXTURES 1

/* vetor com os números das texturas */
GLuint texture_id[MAX_NO_TEXTURES];

char* filenameArray[MAX_NO_TEXTURES] = {
        "surface2.bmp",
};

GLUquadricObj *obj;

GLfloat angleX = 0.0f;
GLfloat angleY = 0.0f;

void getJpgImageData( char *pFileName, JPGImage *pImage )
{
    FILE *pFile = NULL;
    unsigned short nNumPlanes;
    unsigned short nNumBPP;
    int i;

    if( (pFile = fopen(pFileName, "rb") ) == NULL )
        printf("ERROR: getJpgImageData - %s not found.\n", pFileName);

    // Seek forward to width and height info
    fseek( pFile, 18, SEEK_CUR );

    if( (i = fread(&pImage->width, 4, 1, pFile) ) != 1 )
        printf("ERROR: getJpgImageData - Couldn't read width from %s.\n ", pFileName);

    if( (i = fread(&pImage->height, 4, 1, pFile) ) != 1 )
        printf("ERROR: getJpgImageData - Couldn't read height from %s.\n ", pFileName);

    if( (fread(&nNumPlanes, 2, 1, pFile) ) != 1 )
        printf("ERROR: getJpgImageData - Couldn't read plane count from %s.\n", pFileName);

    if( nNumPlanes != 1 )
        printf("ERROR: getJpgImageData - Plane count from %s.\n ", pFileName);

    if( (i = fread(&nNumBPP, 2, 1, pFile)) != 1 )
        printf( "ERROR: getJpgImageData - Couldn't read BPP from %s.\n ", pFileName);

    if( nNumBPP != 24 )
        printf("ERROR: getJpgImageData - BPP from %s.\n ", pFileName);

    fseek( pFile, 24, SEEK_CUR );

    int nTotalImagesize = (pImage->width * pImage->height) * 3;

    pImage->data = (char*) malloc( nTotalImagesize );

    if( (i = fread(pImage->data, nTotalImagesize, 1, pFile) ) != 1 )
        printf("ERROR: getJpgImageData - Couldn't read image data from %s.\n ", pFileName);

    char charTemp;
    for( i = 0; i < nTotalImagesize; i += 3 )
    {
        charTemp = pImage->data[i];
        pImage->data[i] = pImage->data[i+2];
        pImage->data[i+2] = charTemp;
    }
}


/*Função para Carregar uma imagem .BMP */
void CarregaTexturas()
{
    JPGImage textura;

    /* Define quantas texturas serão usadas no programa  */
    glGenTextures(MAX_NO_TEXTURES, texture_id); 

    int i;
    for ( i=0; i<MAX_NO_TEXTURES; i++ ) {
        getJpgImageData( filenameArray[i], &textura);
        glBindTexture(GL_TEXTURE_2D, texture_id[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, textura.width, textura.height, 0, GL_RGB, GL_UNSIGNED_BYTE, textura.data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    }
}

void initTexture (void)
{

    /* Habilita o uso de textura bidimensional  */
    glEnable ( GL_TEXTURE_2D );
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    /*Carrega os arquivos de textura */
  //  CarregaTextura("tunnelTexture.bmp");
    //CarregaTextura("tex2.bmp");
    CarregaTexturas("surface2.bmp");

}

void cubo()
{
    glColor3f(1.0, 0.0, 0.0);

     for (i = 5; i >= 0; i--) {
         glBegin(GL_QUADS);
            glNormal3fv(&n[i][0]);
            glTexCoord2f(0.0f,0.0f);
            glVertex3fv(&v[faces[i][0]][0]);
            glTexCoord2f(1.0f,0.0f);
            glVertex3fv(&v[faces[i][1]][0]);
            glTexCoord2f(1.0f,1.0f);
            glVertex3fv(&v[faces[i][2]][0]);
            glTexCoord2f(0.0f,1.0f);
            glVertex3fv(&v[faces[i][3]][0]);
         glEnd();
     }
    
    glBindTexture(GL_TEXTURE_2D, texture_id[0]);
    
    // FACE 1
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-0.25, 0.25, 0.25);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(0.25, 0.25, 0.25);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(0.25, -0.25, 0.25);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-0.25, -0.25, 0.25);
    glEnd();


    // glColor3f(0.0, 1.0, 0.0);
    // glBegin(GL_POLYGON);
    // glVertex3f(-0.25, 0.25, -0.25);
    // glVertex3f(0.25, 0.25, -0.25);
    // glVertex3f(0.25, -0.25, -0.25);
    // glVertex3f(-0.25, -0.25, -0.25);
    // glEnd();
    
    
    // glColor3f(0.0, 0.0, 1.0);
    // glBegin(GL_POLYGON);
    // glVertex3f(0.25, -0.25, 0.25);
    // glVertex3f(0.25, 0.25, 0.25);
    // glVertex3f(0.25, 0.25, -0.25);
    // glVertex3f(0.25, -0.25, -0.25);
    // glEnd();


    // glColor3f(1.0, 1.0, 0.0);
    // glBegin(GL_POLYGON);
    // glVertex3f(-0.25, -0.25, 0.25);
    // glVertex3f(-0.25, 0.25, 0.25);
    // glVertex3f(-0.25, 0.25, -0.25);
    // glVertex3f(-0.25, -0.25, -0.25);
    // glEnd();
    
    
    // glColor3f(1.0, 0.0, 1.0);
    // glBegin(GL_POLYGON);
    // glVertex3f(-0.25, 0.25, 0.25);
    // glVertex3f(0.25, 0.25, 0.25);
    // glVertex3f(0.25, 0.25, -0.25);
    // glVertex3f(-0.25, 0.25, -0.25);
    // glEnd();
    
    // glColor3f(0.0, 1.0, 1.0);
    // glBegin(GL_POLYGON);
    // glVertex3f(-0.25, -0.25, 0.25);
    // glVertex3f(0.25, -0.25, 0.25);
    // glVertex3f(0.25, -0.25, -0.25);
    // glVertex3f(-0.25, -0.25, -0.25);
    // glEnd();
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
    initTexture();
    glutMainLoop();
    return 0;
}