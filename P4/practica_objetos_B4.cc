//**************************************************************************
// Práctica 4
//**************************************************************************

#include <GL/glut.h>

#include <ctype.h>
#include <math.h>
#include <vector>
#include "objetos_B4.h"

using namespace std;

// tipos
typedef enum
{
    CUBO,
    PIRAMIDE,
    OBJETO_PLY,
    ROTACION,
    CILINDRO,
    CONO,
    ESFERA,
    EXTRUSION
} _tipo_objeto;
_tipo_objeto t_objeto = CUBO; // por defecto
_modo modo = SOLID;               // por defecto

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Size_x, Size_y, Front_plane, Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int Window_x = 50, Window_y = 50, Window_width = 650, Window_high = 650;

// objetos
_cubo cubo(0.5, true, true);
_piramide piramide(0.85, 1.3, false, true);
_objeto_ply ply;
_rotacion rotacion;
_cilindro cilindro(1, 2, 32, true, false);
_cono cono(1, 2, 6, true, true);
_esfera esfera(1, 6, 50, false, true);
//_excavadora excavadora;
_extrusion *extrusion;

// Luces
bool luz2_on = false;
float alfa = 0.0;

// Materiales
_material oro = {{ 0.24725f, 0.1995f, 0.0745f, 1.0f }, 
                 {0.75164f, 0.60648f, 0.22648f, 1.0f}, 
                 {0.628281f, 0.555802f, 0.366065f, 1.0f}, 
                 51.2f};

//**************************************************************************
//
//***************************************************************************

void clean_window()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // formato(x_minimo,x_maximo, y_minimo, y_maximo,plano_delantero, plano_traser)
    //  plano_delantero>0  plano_trasero>PlanoDelantero)
    glFrustum(-Size_x, Size_x, -Size_y, Size_y, Front_plane, Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación*ply1 de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

    // posicion del observador
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 0, -Observer_distance);
    glRotatef(Observer_angle_x, 1, 0, 0);
    glRotatef(Observer_angle_y, 0, 1, 0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{

    glDisable(GL_LIGHTING);
    glLineWidth(2);
    glBegin(GL_LINES);
    // eje X, color rojo
    glColor3f(1, 0, 0);
    glVertex3f(-AXIS_SIZE, 0, 0);
    glVertex3f(AXIS_SIZE, 0, 0);
    // eje Y, color verde
    glColor3f(0, 1, 0);
    glVertex3f(0, -AXIS_SIZE, 0);
    glVertex3f(0, AXIS_SIZE, 0);
    // eje Z, color azul
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, -AXIS_SIZE);
    glVertex3f(0, 0, AXIS_SIZE);
    glEnd();
}

//**************************************************************************
// Funcion que dibuja los objetos
//****************************2***********************************************

void draw_objects()
{

    switch (t_objeto)
    {
    case CUBO:
        cubo.draw(modo, 0.0, 1.0, 0.0, 5, oro);
        break;
    case PIRAMIDE:
        piramide.draw(modo, 1.0, 0.0, 0.0, 5, oro);
        break;
    case OBJETO_PLY:
        ply.draw(modo, 1.0, 0.6, 0.0, 5, oro);
        break;
    case ROTACION:
        rotacion.draw(modo, 1.0, 0.0, 0.0, 5, oro);
        break;
    case CILINDRO:
        cilindro.draw(modo, 1.0, 0.0, 0.0, 5, oro);
        break;
    case CONO:
        cono.draw(modo, 1.0, 0.0, 0.0, 5, oro);
        break;
    case ESFERA:
        esfera.draw(modo, 1.0, 0.0, 0.0, 5, oro);
        break;
    case EXTRUSION:
        extrusion->draw(modo, 1.0, 0.0, 0.0, 5, oro);
        break;
    }
}

//***************************************************************************
// Funcion para las luces
//***************************************************************************

void luces (float alfa, bool luz2_on){  //float alfa, float beta
	float    luz1[]={0.4, 0.3, 1.0, 1.0}, // azul neon
            luz_blanca[] = {1.0, 1.0, 1.0, 1.0},
			pos1[]= {0, 20.0, 40.0, 1.0}, // Cuidado con no ponerla dentro del objeto

			luz2[]={0.3, 0.0, 0.6, 1.0}, // morado neon
			pos2[]= {-20.0, 0.0, 100.0, 1.0},

            luz3[] = {0.8, 0.0, 0.8, 1.0}; // rosa neon

	glLightfv (GL_LIGHT1, GL_DIFFUSE, luz_blanca); 
	glLightfv (GL_LIGHT1, GL_SPECULAR, luz_blanca); 
    // Si no le ponemos componente especular, no tiene brillo, 
    // por lo que no cambia segun observador

	glPushMatrix();
	glLightfv (GL_LIGHT1, GL_AMBIENT, luz_blanca);
	glPopMatrix();

	glLightfv (GL_LIGHT2, GL_DIFFUSE, luz2); 
	glLightfv (GL_LIGHT2, GL_SPECULAR, luz2);

	glPushMatrix();
	glRotatef(alfa, 1, 0, 0);
	glLightfv (GL_LIGHT2, GL_POSITION, pos2);
	glPopMatrix();

	glDisable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

    if(luz2_on)
	    glEnable(GL_LIGHT2);
    else
        glDisable(GL_LIGHT2);

 }

//**************************************************************************
//
//***************************************************************************

void draw(void)
{
    clean_window();
    change_observer();
    luces(alfa, luz2_on);
    draw_axis();
    draw_objects();
    glutSwapBuffers();
}

//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1, int Alto1)
{
    float Aspect_ratio;

    Aspect_ratio = (float)Alto1 / (float)Ancho1;
    Size_y = Size_x * Aspect_ratio;
    change_projection();
    glViewport(0, 0, Ancho1, Alto1);
    glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_key(unsigned char Tecla1, int x, int y)
{
    switch (toupper(Tecla1))
    {
    case 'Q':
        exit(0);
    case '1':
        modo = POINTS;
        break;
    case '2':
        modo = EDGES;
        break;
    case '3':
        modo = SOLID;
        break;
    case '4':
        modo = SOLID_COLORS;
        break;
    case '5':
        modo = SOLID_FLAT;
        break;
    case '6':
        modo = SOLID_SMOOTH;
        break;
    case 'P':
        t_objeto = PIRAMIDE;
        break;
    case 'C':
        t_objeto = CUBO;
        break;
    case 'O':
        t_objeto = OBJETO_PLY;
        break;
    case 'R':
        t_objeto = ROTACION;
        break;
    case 'L':
        t_objeto = CILINDRO;
        break;
    case 'N':
        t_objeto = CONO;
        break;
    case 'E':
        t_objeto = ESFERA;
        break;
    case 'X':
        t_objeto = EXTRUSION;
        break;
    case 'I':
        if(luz2_on){
            luz2_on = false;
            printf("\nLuz 2 encendida"); // Está al revés porque la primera vez no sale y 
            // siempre se ejecuta después el refresco de la pantalla
        }
        else{
            luz2_on = true;
            printf("\nLuz 2 apagada");
        }
        break;
    case 'V':
        alfa += 5;
        break;
    case 'B':
        alfa -= 5;
        break;
    }
    glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_key(int Tecla1, int x, int y)
{

    switch (Tecla1)
    {
    case GLUT_KEY_LEFT:
        Observer_angle_y -= 5;
        break;
    case GLUT_KEY_RIGHT:
        Observer_angle_y += 15;
        break;
    case GLUT_KEY_UP:
        Observer_angle_x--;
        break;
    case GLUT_KEY_DOWN:
        Observer_angle_x++;
        break;
    case GLUT_KEY_PAGE_UP:
        Observer_distance *= 1.2;
        break;
    case GLUT_KEY_PAGE_DOWN:
        Observer_distance /= 1.2;
        break;
    }
   glutPostRedisplay();
}

//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
    // se inicalizan la ventana y los planos de corte
    Size_x = 0.5;
    Size_y = 0.5;
    Front_plane = 1;
    Back_plane = 1000;

    // se incia la posicion del observador, en el eje z
    Observer_distance = 4 * Front_plane;
    Observer_angle_x = 0;
    Observer_angle_y = 0;

    // se indica el color para limpiar la ventana	(r,v,a,al)
    // blanco=(1,1,1,1) rojo=(1,0,0,1), ...
    glClearColor(1, 1, 1, 1);

    // se habilita el z-bufer
    glEnable(GL_DEPTH_TEST);
    change_projection();
    glViewport(0, 0, Window_width, Window_high);
}

//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char *argv[] )
{
// perfil 

vector<_vertex3f> perfil, poligono;
_vertex3f aux;

/*aux.x=1.0; aux.y=-1.0; aux.z=0.0;
perfil.push_back(aux);
aux.x=1.5; aux.y=0.0; aux.z=0.0;
perfil.push_back(aux);
aux.x=1.0; aux.y=1.0; aux.z=0.0;
perfil.push_back(aux);
aux.x=1.5; aux.y=1.2; aux.z=0.0;
perfil.push_back(aux);


rotacion.parametros(perfil,6,0,1,1);*/

aux.x=1.0; aux.y=0.0; aux.z=1.0;
poligono.push_back(aux);
aux.x=1.0; aux.y=0.0; aux.z=-1.0;
poligono.push_back(aux);
aux.x=-1.2; aux.y=0.0; aux.z=-1.0;
poligono.push_back(aux);
aux.x=-0.8; aux.y=0.0; aux.z=0.0;
poligono.push_back(aux);
aux.x=-1.2; aux.y=0.0; aux.z=1.0;
poligono.push_back(aux);

extrusion= new _extrusion(poligono, 0.25, 1.0, 0.25);

// se llama a la inicialización de glut
glutInit(&argc, argv);

// se indica las caracteristicas que se desean para la visualización con OpenGL
// Las posibilidades son:
// GLUT_SIMPLE -> memoria de imagen simple
// GLUT_DOUBLE -> memoria de imagen doble
// GLUT_INDEX -> memoria de imagen con color indizado
// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
// GLUT_DEPTH -> memoria de profundidad o z-bufer
// GLUT_STENCIL -> memoria de estarcido_rotation Rotation;
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

// posicion de la esquina inferior izquierdad de la ventana
glutInitWindowPosition(Window_x,Window_y);

// tamaño de la ventana (ancho y alto)
glutInitWindowSize(Window_width,Window_high);

// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
// al bucle de eventos)
glutCreateWindow("PRACTICA - 4");

// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw);
// asignación de la funcion llamada "change_window_size" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "normal_key" al evento correspondiente
glutKeyboardFunc(normal_key);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_key);

// funcion de inicialización
initialize();

// creación del objeto ply
ply.parametros(argv[1]);

// mensaje de salida en el terminal para orientar al usuario
cout << endl << endl;
cout << "***Objetos que se pueden visualizar***" << endl;
cout << "Tecla P: Pirámide" << endl;
cout << "Tecla C: Cubo" << endl;
cout << "Tecla O: Objeto Ply" << endl;
cout << "Tecla R: Rotación" << endl;
cout << "Tecla L: Cilindro" << endl;
cout << "Tecla N: Cono" << endl;
cout << "Tecla E: Esfera" << endl;
//cout << "Tecla A: Coche" << endl;
cout << "Tecla X: Extrusión" << endl;

cout << endl << endl;
cout << "***Modos de visualización de los distintos objetos***" << endl;
cout << "Número 1: Puntos" << endl;
cout << "Número 2: Líneas" << endl;
cout << "Número 3: Sólido" << endl;
cout << "Número 4: Sólido colores" << endl;
cout << "Número 3: Sólido plano" << endl;
cout << "Número 4: Sólido suave" << endl;
/*
cout << endl << endl;
cout << "***Movimientos que puede hacer el coche***" << endl;
cout << "Tecla F1: Rotación de las ruedas del coche hacia adelante" << endl;
cout << "Tecla F2: Rotación de las ruedas del coche hacia atrás" << endl;
cout << "Tecla F3: Giro de las ruedas del coche a la izquierda" << endl;
cout << "Tecla F4: Giro de las ruedas del coche a la derecha" << endl;
cout << "Tecla F5: Abertura del alerón trasero" << endl;
cout << "Tecla F6: Cierre del alerón trasero" << endl;
cout << "Tecla F7: Abertura del alerón delantero" << endl;
cout << "Tecla F8: Cierre del alerón delantero" << endl;
*/

//ply = new _objeto_ply(argv[1]);

// inicio del bucle de eventos
glutMainLoop();
return 0;
}
