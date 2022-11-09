//**************************************************************************
// Práctica 2 
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>

// Prueba


const float AXIS_SIZE=5000;
typedef enum{POINTS,EDGES,SOLID,SOLID_COLORS} _modo;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:

  
	_puntos3D();
void 	draw_puntos(float r, float g, float b, int grosor);

vector<_vertex3f> vertices;
vector<_vertex3f> colores_vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
public:

	_triangulos3D();
void 	draw_aristas(float r, float g, float b, int grosor);
void    draw_solido(float r, float g, float b);
void 	draw_solido_colores();
void 	draw(_modo modo, float r, float g, float b, float grosor);

/* asignación de colores */
void 	colors_random();
void 	colors_chess(float r1, float g1, float b1, float r2, float g2, float b2);


vector<_vertex3i> caras;
vector<_vertex3f> colores_caras;
};

//*************************************************************************
// objetos o modelos
//*************************************************************************

//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:

	_cubo(float tam=0.5);
};


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:

	_piramide(float tam=0.5, float al=1.0);
};

//*************************************************************************
// clase objeto ply
//*************************************************************************

class _objeto_ply: public _triangulos3D
{
public:
   _objeto_ply();

void  parametros(char *archivo);
};

//************************************************************************
// objeto por revolución
//************************************************************************
// tipo indica si es una figura por revolución normal o bien un cono o una esfera
// tipo=0 normal, tipo=1 cono, tipo=2 esfera
// tapa_in=0 sin tapa, tapa_in=1 con tapa
// tapa_su=0 sin tapa, tapa_su=1 con tapa

class _rotacion: public _triangulos3D
{
public:
       _rotacion();
       
void  parametros(vector<_vertex3f> perfil, int num, int tipo, int tapa_in, int tapa_su);
};

class _prueba: public _triangulos3D
{
public:
       _prueba();
       
void  parametros(vector<_vertex3f> perfil, int num, int tipo, int tapa_in, int tapa_su);
};

 
//************************************************************************
// cilindro
//************************************************************************

class _cilindro: public _rotacion
{
public:
       _cilindro(float radio=1.0, float altura=2.0, int num=12);
};

//************************************************************************
// cono
//************************************************************************

class _cono: public _rotacion
{
public:
       _cono(float radio=1.0, float altura=2.0, int num=3);
};

//************************************************************************
// esfera
//************************************************************************

class _esfera: public _rotacion
{
public:
       _esfera(float radio, int num1, int num2);
};


//************************************************************************
// rotacion archivo PLY
//************************************************************************

class _rotacion_PLY: public _rotacion
{
public:
       _rotacion_PLY();
void  parametros_PLY(char *archivo, int num);
};


//************************************************************************
// objeto por extrusión
//************************************************************************

class _extrusion: public _triangulos3D
{
public:
       _extrusion(vector<_vertex3f> poligono, float x, float y, float z);
};


//************************************************************************
// práctica 3, objeto jerárquico articulado excavadora
//************************************************************************

//************************************************************************
// piezas
//************************************************************************


//************************************************************************
// ruedas
//************************************************************************
class _rueda_delantera: public _triangulos3D
{
public:
      _rueda_delantera();
void  draw(_modo modo, float r, float g, float b, float grosor);
       
float ancho;
float alto;
float fondo;

float radio;

protected:
_cilindro rueda;
};

class _rueda_trasera: public _triangulos3D
{
public:
      _rueda_trasera();
void  draw(_modo modo, float r, float g, float b, float grosor);
       
float ancho;
float alto;
float fondo;

float radio;

protected:
_cilindro rueda;
};

class _estructura: public _triangulos3D
{
public:
       _estructura();
void draw(_modo modo, float r, float g, float b, float grosor);

float ancho;
float alto;
float fondo;

protected:
_cubo cubo;
};

class _aleron_trasero_base: public _triangulos3D
{
public:
       _aleron_trasero_base();
void draw(_modo modo, float r, float g, float b, float grosor);

float ancho;
float alto;
float fondo;

protected:
_cubo cubo;
};

class _aleron_trasero_sup: public _triangulos3D
{
public:
       _aleron_trasero_sup();
void draw(_modo modo, float r, float g, float b, float grosor);

float ancho;
float alto;
float fondo;

protected:
_cubo cubo;
};

class _apendice: public _triangulos3D
{
public:
       _apendice();
void draw(_modo modo, float r, float g, float b, float grosor);

float ancho;
float alto;
float fondo;

float radio;

protected:
_cono aleron;
};

class _aleron_delantero_base: public _triangulos3D
{
public:
       _aleron_delantero_base();
void draw(_modo modo, float r, float g, float b, float grosor);

float ancho;
float alto;
float fondo;

protected:
_cubo cubo;
};

class _aleron_delantero_sup: public _triangulos3D
{
public:
       _aleron_delantero_sup();
void draw(_modo modo, float r, float g, float b, float grosor);

float ancho;
float alto;
float fondo;

protected:
_cubo cubo;
};


//************************************************************************
// coche (montaje del objeto final)
//************************************************************************

class _coche: public _triangulos3D
{
public:
       _coche();
       
void  draw(_modo modo, float r, float g, float b, float grosor);

float giro_ruedas;
float giro_ruedas_max_min;
float rotacion_ruedas;
float giro_aleron_trasero;
float giro_aleron_trasero_max;
float giro_aleron_min;
float giro_aleron_delantero;
float giro_aleron_delantero_max;

protected:
_rueda_delantera rueda_delantera_der;
_rueda_delantera rueda_delantera_izq;
_rueda_trasera rueda_trasera_der;
_rueda_trasera rueda_trasera_izq;
_estructura estructura;
_aleron_trasero_base aleron_trasero_base_izq;
_aleron_trasero_base aleron_trasero_base_drch;
_aleron_trasero_sup aleron_trasero_sup_inmovil;
_aleron_trasero_sup aleron_trasero_sup_movil;
_apendice apendice;
_aleron_delantero_base aleron_delantero_base_izq;
_aleron_delantero_base aleron_delantero_base_drch;
_aleron_delantero_sup aleron_delantero_sup;
};