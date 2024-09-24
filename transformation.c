#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

void desenharTriangulo();
void recebeTecla(unsigned char key, int x, int y);
void init();
void display();
void transladar(GLfloat x, GLfloat y);
void calculaBaricentro(GLfloat * baricentro);
void rotacao(GLfloat angulo);
void escala(GLfloat scale);


GLfloat pox = 0, poy = 0;
GLfloat angle = 0.0;
GLfloat triangulo[3][2] = {{-0.3, -0.3}, {0.3, -0.3}, {0.0, 0.3}};

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1600, 900);
    glutCreateWindow("Triangulo"); 
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(recebeTecla);
    glutMainLoop();
}

void desenharTriangulo(){ 
    glColor3f(0.0, 0.0, 1.0);  
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 3; i++) { 
        glVertex2fv(triangulo[i]);
    }
    glEnd();
} 

void recebeTecla(unsigned char key, int x, int y){
    switch(key) {
        case 'a':
            transladar(-0.01, 0.0);
            break;;
        case 'd':
            transladar(0.01, 0.0);
            break;
        case 'w':
            transladar(0.0, 0.01);
            break;
        case 's':
            transladar(0.0, -0.01);
            break;
        case 'q':
            rotacao(10);
            break;
        case 'e':
            rotacao(-10);
            break;
        case 'z':
            escala(1.1);
            break;
        case 'x':
            escala(0.9);
            break;
        case 27:
            exit(0);
            break;
    }
    glutPostRedisplay();
} 

void init(){
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
} 

void display(){ 
    glClear(GL_COLOR_BUFFER_BIT);
    desenharTriangulo();
    glutSwapBuffers();
}

void transladar(GLfloat x, GLfloat y){
    for(int i = 0; i < 3; i++){
        triangulo[i][0] += x;
        triangulo[i][1] += y;
    }
}

void calculaBaricentro(GLfloat * baricentro){
    baricentro[0] = 0;
    baricentro[1] = 0;

    for(int i = 0; i < 3; i++){
        baricentro[0] += triangulo[i][0];
        baricentro[1] += triangulo[i][1];
    }

    baricentro[0] = baricentro[0]/3;
    baricentro[1] = baricentro[1]/3;
}

void rotacao(GLfloat angulo){
    GLfloat baricentro[2];
    calculaBaricentro(baricentro);
    GLfloat cos_angulo = cos(angulo * 3.1429 / 180); 
    GLfloat sin_angulo = sin(angulo * 3.1429 / 180); 
    for (int i = 0; i < 3; i++) {
        GLfloat x = triangulo[i][0] - baricentro[0];
        GLfloat y = triangulo[i][1] - baricentro[1];
        triangulo[i][0] = x * cos_angulo - y * sin_angulo + baricentro[0]; 
        triangulo[i][1] = x * sin_angulo + y * cos_angulo + baricentro[1];

    } 
}

void escala(GLfloat scale){
    GLfloat baricentro[2];
    calculaBaricentro(baricentro);
    
    for(int i = 0; i < 3; i++)
    {
        GLfloat x = triangulo[i][0] - baricentro[0];
        GLfloat y = triangulo[i][1] - baricentro[1]; 
        triangulo[i][0] = scale * x + baricentro[0];
        triangulo[i][1] = scale * y + baricentro[1];
    }
}
