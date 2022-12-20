//**************************************************************************
// Práctica 5
//**************************************************************************

#include "objetos_B5.h"
#include "file_ply_stl.hpp"
#include <time.h> 

// Materiales
// Ambiente, Difuso (base), Especular (highlight), Brillo
_material plastico_rojo = {{0.0, 0.0, 0.0, 1.0}, {0.5, 0.0, 0.0, 1.0}, {0.7, 0.6, 0.6, 1.0}, 32.0};
//_material plastico_rojo = {{0.0, 0.0, 0.0, 1.0}, {1, 0.0, 0.0, 1.0}, {0.7, 0.6, 0.6, 1.0}, 0.25};
_material plastico_negro = {{0.0, 0.0, 0.0, 1.0}, {0.0, 0.0, 0.0, 1.0}, {0.50, 0.50, 0.50, 1.0}, 22.0};
_material plastico_azul = {{0.0, 0.1, 0.6, 1.0}, {0, 0.73, 0.8, 1.0}, {0.7, 0.6, 0.6, 1.0}, 32.0}; // cambiar
_material goma_negra = {{0.02, 0.02, 0.02, 1.0}, {0.01, 0.01, 0.01, 1.0}, {0.4, 0.4, 0.4, 1.0}, 10.0};
_material cristal_negro = {{0.02, 0.02, 0.02, 1.0}, {0.01, 0.01, 0.01, 1.0}, {0.4, 0.4, 0.4, 1.0}, 70.0};


//*************************************************************************
// _puntos3D
//*************************************************************************

_puntos3D::_puntos3D()
{
}

//*************************************************************************
// dibujar puntos
//*************************************************************************

void _puntos3D::draw_puntos(float r, float g, float b, int grosor)
{
//**** usando vertex_array ****
glPointSize(grosor);
glColor3f(r,g,b);

glEnableClientState(GL_VERTEX_ARRAY);
glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
glDrawArrays(GL_POINTS,0,vertices.size()); 

/*int i;
glPointSize(grosor);
glColor3f(r,g,b);
glBegin(GL_POINTS);
for (i=0;i<vertices.size();i++){
	glVertex3fv((GLfloat *) &vertices[i]);
	}
glEnd();*/
}

//*************************************************************************
// Cálculo de normales de caras
//*************************************************************************

void _triangulos3D::calcular_normales_caras()
{
  int i, n_c;
  n_c = caras.size();
  _vertex3f va, vb;
  float modulo;
  normales_caras.resize(n_c);

  for (int i = 0; i < n_c; i++)
  {
    va = vertices[caras[i]._1] - vertices[caras[i]._0];
    vb = vertices[caras[i]._2] - vertices[caras[i]._0];
    // hacemos el producto vectorial (determinante de i,j,k de Va y de Vb)
    normales_caras[i].x = va.y * vb.z - va.z * vb.y;
    normales_caras[i].y = va.z * vb.x - va.x * vb.z;
    normales_caras[i].z = va.x * vb.y - va.y * vb.x;
    modulo = sqrt(normales_caras[i].x * normales_caras[i].x +
                  normales_caras[i].y * normales_caras[i].y +
                  normales_caras[i].z * normales_caras[i].z);
    normales_caras[i].x /= modulo;
    normales_caras[i].y /= modulo;
    normales_caras[i].z /= modulo;
  }
}

//*************************************************************************
// Cálculo de normales de vértices
//*************************************************************************

void _triangulos3D::calcular_normales_vertices(){
  float modulo;
  int num_ver = vertices.size(), num_caras = caras.size();
  normales_vertices.resize(num_ver);

  // Inicializar los vertices
  for(int i = 0; i < num_ver; i++){ 
    normales_vertices[i].x = 0;
    normales_vertices[i].y = 0;
    normales_vertices[i].z = 0;
  }

  for(int i = 0; i < caras.size(); i++){
    normales_vertices[caras[i]._0] += normales_caras[i];
    normales_vertices[caras[i]._1] += normales_caras[i];
    normales_vertices[caras[i]._2] += normales_caras[i];
  }

  for (int i=0; i<caras.size(); i++){
      normales_vertices[caras[i]._0]+=normales_caras[i];
      normales_vertices[caras[i]._1]+=normales_caras[i];
      normales_vertices[caras[i]._2]+=normales_caras[i];
  }

}

//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D()
{
}


//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
//**** usando vertex_array ****
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
glColor3f(r,g,b);

glEnableClientState(GL_VERTEX_ARRAY);
glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
glDrawElements(GL_TRIANGLES,caras.size()*3,GL_UNSIGNED_INT,&caras[0]);

/*int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();*/
}

//*************************************************************************
// dibujar en modo sólido con un único color
//*************************************************************************

void _triangulos3D::draw_solido(float r, float g, float b)
{
int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();

}

//*************************************************************************
// dibujar en modo sólido con colores diferentes para cada cara
//*************************************************************************

void _triangulos3D::draw_solido_colores( )
{
int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glColor3f(colores_caras[i].r,colores_caras[i].g,colores_caras[i].b);
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
}

//*************************************************************************
// dibujar en modo seleccion
//*************************************************************************

void _triangulos3D::draw_seleccion(int r, int g, int b)
{
int i;

glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
glColor3ub(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
}

//*************************************************************************
// dibujar en modo iluminacion para las caras
//*************************************************************************
void _triangulos3D::draw_solido_plano(_material material)
{
  int i;
  glEnable(GL_LIGHTING);
  glShadeModel(GL_FLAT);
  glEnable(GL_NORMALIZE); // Para que se normalicen las normales (en el caso de que haya escalado)

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material.ambiente);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material.difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material.especular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, material.brillo);

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glBegin(GL_TRIANGLES);
  for (i = 0; i < caras.size(); i++)
  {
    //glNormal3f(normales_caras[i].r, normales_caras[i].g, normales_caras[i].b);
    
    glNormal3fv((GLfloat *) &normales_caras[i]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._0]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
  }
  glEnd();

  glDisable(GL_LIGHTING);
}

void _triangulos3D::draw_solido_suave(_material material){
  int i;
  glEnable(GL_LIGHTING);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_NORMALIZE); // Para que se normalicen las normales (en el caso de que haya escalado)

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material.ambiente);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material.difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material.especular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, material.brillo);

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glBegin(GL_TRIANGLES);
  for (i = 0; i < caras.size(); i++)
  {
    glNormal3fv((GLfloat *) &normales_vertices[caras[i]._0]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
    glNormal3fv((GLfloat *) &normales_vertices[caras[i]._1]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
    glNormal3fv((GLfloat *) &normales_vertices[caras[i]._2]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._2]);

    /* // Calcular la normal del primer vértice
    glNormal3f(normales_vertices[caras[i]._0].x, 
              normales_vertices[caras[i]._0].y, 
              normales_vertices[caras[i]._0].z);
    glVertex3fv((GLfloat *)&vertices[caras[i]._0]);

    // Calcular la normal del segundo vértice
    glNormal3f(normales_vertices[caras[i]._1].x, 
              normales_vertices[caras[i]._1].y, 
              normales_vertices[caras[i]._1].z);
    glVertex3fv((GLfloat *)&vertices[caras[i]._1]);

    // Calcular la normal del tercer vértice
    glNormal3f(normales_vertices[caras[i]._2].x, 
              normales_vertices[caras[i]._2].y, 
              normales_vertices[caras[i]._2].z);
    glVertex3fv((GLfloat *)&vertices[caras[i]._2]); */

  }
  glEnd();
  glDisable(GL_LIGHTING); 
}


//*************************************************************************
// dibujar con distintos modos
//*************************************************************************

void _triangulos3D::draw(_modo modo, float r, float g, float b, float grosor, _material material)
{
switch (modo){
	case POINTS:draw_puntos(r, g, b, grosor);break;
	case EDGES:draw_aristas(r, g, b, grosor);break;
	case SOLID:draw_solido(r, g, b);break;
	case SOLID_COLORS:draw_solido_colores();break;
  case SOLID_FLAT:draw_solido_plano(material);break;
  case SOLID_SMOOTH:draw_solido_suave(material);break;
	case SELECT:draw_seleccion(r, g, b);break;
	}
}

//*************************************************************************
// asignación colores
//*************************************************************************

void _triangulos3D::colors_random()
{
int i, n_c;
n_c=caras.size();
colores_caras.resize(n_c);
srand (time(NULL));
for (i=0;i<n_c;i++)  
  {colores_caras[i].r=rand()%1000/1000.0;
   colores_caras[i].g=rand()%1000/1000.0;
   colores_caras[i].b=rand()%1000/1000.0;
  }
}

//*************************************************************************

void _triangulos3D::colors_flat(float r, float g, float b, float p_lx, float p_ly, float p_lz)
{
   int i, num_caras;
  _vertex3f l;
  float modulo, escalar;
  num_caras = caras.size();
  colores_caras.resize(num_caras);

  for (int i = 0; i < num_caras; i++) {
    colores_caras[i].r = 0.1 * r;
    colores_caras[i].g = 0.1 * g;
    colores_caras[i].b = 0.101 * b;
    l.x = p_lx - vertices[caras[i]._0].x;
    l.y = p_ly - vertices[caras[i]._0].y;
    l.z = p_lz - vertices[caras[i]._0].z;
    modulo = sqrt(l.x * l.x + l.y * l.y + l.z * l.z);
    l.x /= modulo;
    l.y /= modulo;
    l.z /= modulo;
    escalar = normales_caras[i].x * l.x + normales_caras[i].y * l.y + normales_caras[i].z * l.z;
    
    if (escalar > 0.0) {
      colores_caras[i].r += r * escalar;
      colores_caras[i].g += g * escalar;
      colores_caras[i].b += b * escalar;
    }
  }
}

void _triangulos3D::colors_smooth(float r, float g, float b, float p_lx, float p_ly, float p_lz){
// First approach
  int i, num_caras;
  _vertex3f l;
  float modulo, escalar;
  num_caras = caras.size();
  colores_caras.resize(num_caras);

  for (int i = 0; i < num_caras; i++) {
    colores_caras[i].r = 0.1 * r;
    colores_caras[i].g = 0.1 * g;
    colores_caras[i].b = 0.101 * b;
    l.x = p_lx - vertices[caras[i]._0].x;
    l.y = p_ly - vertices[caras[i]._0].y;
    l.z = p_lz - vertices[caras[i]._0].z;
    modulo = sqrt(l.x * l.x + l.y * l.y + l.z * l.z);
    l.x /= modulo;
    l.y /= modulo;
    l.z /= modulo;
    escalar = normales_vertices[caras[i]._0].x * l.x + normales_vertices[caras[i]._0].y * l.y + normales_vertices[caras[i]._0].z * l.z;
    
    if (escalar > 0.0) {
      colores_caras[i].r += r * escalar;
      colores_caras[i].g += g * escalar;
      colores_caras[i].b += b * escalar;
    }
  }
}

//*************************************************************************

void _triangulos3D::colors_chess(float r1, float g1, float b1, float r2, float g2, float b2)
{
int i, n_c;
n_c=caras.size();
colores_caras.resize(n_c);
for (i=0;i<n_c;i++)  
  {if (i%2==0) 
     {colores_caras[i].r=r1;
      colores_caras[i].g=g1;
      colores_caras[i].b=b1;
     }
   else 
     {colores_caras[i].r=r2;
      colores_caras[i].g=g2;
      colores_caras[i].b=b2;
     } 
  }
}


//*************************************************************************
// objetos o modelos
//*************************************************************************

//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam, bool tapa_inf, bool tapa_sup)
{
  // vertices
  vertices.resize(8);
  vertices[0].x = -tam;
  vertices[0].y = -tam;
  vertices[0].z = tam;
  vertices[1].x = tam;
  vertices[1].y = -tam;
  vertices[1].z = tam;
  vertices[2].x = tam;
  vertices[2].y = tam;
  vertices[2].z = tam;
  vertices[3].x = -tam;
  vertices[3].y = tam;
  vertices[3].z = tam;
  vertices[4].x = -tam;
  vertices[4].y = -tam;
  vertices[4].z = -tam;
  vertices[5].x = tam;
  vertices[5].y = -tam;
  vertices[5].z = -tam;
  vertices[6].x = tam;
  vertices[6].y = tam;
  vertices[6].z = -tam;
  vertices[7].x = -tam;
  vertices[7].y = tam;
  vertices[7].z = -tam;

  // triangulos
  caras.resize(12);
  
  caras[0]._0 = 0; caras[0]._1 = 1; caras[0]._2 = 3;
  caras[1]._0 = 3; caras[1]._1 = 1; caras[1]._2 = 2;
  caras[2]._0 = 1; caras[2]._1 = 5; caras[2]._2 = 2;
  caras[3]._0 = 5; caras[3]._1 = 6; caras[3]._2 = 2; 
  caras[4]._0 = 5; caras[4]._1 = 4; caras[4]._2 = 6;
  caras[5]._0 = 4; caras[5]._1 = 7; caras[5]._2 = 6;
  caras[6]._0 = 0; caras[6]._1 = 7; caras[6]._2 = 4; 
  caras[7]._0 = 0; caras[7]._1 = 3; caras[7]._2 = 7;

  if(tapa_sup){
    caras[8]._0 = 3; caras[8]._1 = 2; caras[8]._2 = 7;
    caras[9]._0 = 2; caras[9]._1 = 6; caras[9]._2 = 7;
  }

  if(tapa_inf){
    caras[10]._0 = 0; caras[10]._1 = 1; caras[10]._2 = 4;
    caras[11]._0 = 1; caras[11]._1 = 5; caras[11]._2 = 4;
  }

  // colores de las caras
  colors_random();
  calcular_normales_caras();
  calcular_normales_vertices();
  colors_flat(0.9,0.7,0.0,-20.0,20.0,-20.0); // Cambiando los tres ultimos parámetros cambiamos de dónde viene la luz

}

//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al, bool tapa_inf, bool tapa_sup)
{
  int i;
  // vertices
  vertices.resize(5);
  vertices[0].x = -tam;
  vertices[0].y = 0;
  vertices[0].z = tam;
  vertices[1].x = tam;
  vertices[1].y = 0;
  vertices[1].z = tam;
  vertices[2].x = tam;
  vertices[2].y = 0;
  vertices[2].z = -tam;
  vertices[3].x = -tam;
  vertices[3].y = 0;
  vertices[3].z = -tam;
  vertices[4].x = 0;
  vertices[4].y = al;
  vertices[4].z = 0;

  caras.resize(6);
  caras[0]._0 = 0;
  caras[0]._1 = 1;
  caras[0]._2 = 4;
  caras[1]._0 = 1;
  caras[1]._1 = 2;
  caras[1]._2 = 4;
  caras[2]._0 = 2;
  caras[2]._1 = 3;
  caras[2]._2 = 4;
  caras[3]._0 = 3;
  caras[3]._1 = 0;
  caras[3]._2 = 4;

  if (tapa_inf)
  {
    caras[4]._0 = 3;
    caras[4]._1 = 1;
    caras[4]._2 = 0;
    caras[5]._0 = 3;
    caras[5]._1 = 2;
    caras[5]._2 = 1;
  }

  // colores de las caras
  colors_random();
  calcular_normales_caras();
  calcular_normales_vertices();
  colors_flat(0.9,0.7,0.0,-20.0,20.0,-20.0); // Cambiando los tres ultimos parámetros cambiamos de dónde viene la luz
}

//*************************************************************************
// clase objeto ply
//*************************************************************************


_objeto_ply::_objeto_ply() 
{
   // leer lista de coordenadas de vértices y lista de indices de vértices
 
}



void _objeto_ply::parametros(char *archivo)
{
  int i, n_ver, n_car;

  vector<float> ver_ply;
  vector<int> car_ply;

  _file_ply::read(archivo, ver_ply, car_ply);

  n_ver = ver_ply.size() / 3;
  n_car = car_ply.size() / 3;

  printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

  vertices.resize(n_ver);
  caras.resize(n_car);
  
  // vértices
  for (i = 0; i < n_ver; i++)
  {
    vertices[i].x = ver_ply[3 * i];
    vertices[i].y = ver_ply[3 * i + 1];
    vertices[i].z = ver_ply[3 * i + 2];
  }

  // caras
  for (i = 0; i < n_car; i++)
  {
    caras[i].x = car_ply[3 * i];
    caras[i].y = car_ply[3 * i + 1];
    caras[i].z = car_ply[3 * i + 2];
  }

  colores_caras.resize(n_car);
  srand(10);

  // colores
/*   float sum;
  int n;
  colores_caras.resize(caras.size());

  for (i = 0; i < caras.size(); i++)
  {
    if (vertices[caras[i]._0].y >= 0)
    {
      colores_caras[i].r = rand() % 1000 / 1000.0;
      colores_caras[i].b = 0.0;
      colores_caras[i].g = 0.8;
    }
    else
    {
      n = rand() % 10;
      sum = rand() % 100 / 500.0;
      if (n < 5)
        colores_caras[i].r = 0.251 + sum;
      else
        colores_caras[i].r = 0.251 - sum;
      if (n > 5)
        colores_caras[i].b = 0.805 + sum;
      else
        colores_caras[i].b = 0.805 - sum;
      if (n > 5)
        colores_caras[i].g = 0.816 + sum;
      else
        colores_caras[i].g = 0.816 - sum;
    }
  } */

  calcular_normales_caras();
  calcular_normales_vertices();
  colors_flat(0.9,0.7,0.0,-20.0,20.0,-20.0); // Cambiando los tres ultimos parámetros cambiamos de dónde viene la luz

}


//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion()
{

}
/*
  Tipo 0: normal
  Tipo 1: cono
  Tipo 2: esfera
*/
void _rotacion::parametros(vector<_vertex3f> perfil, int num, int tipo, int tapa_in, int tapa_su)
{
int i,j;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int num_aux;
float radio;

// tratamiento de los vértice
radio=sqrt(perfil[0].x*perfil[0].x+perfil[0].y*perfil[0].y);

num_aux=perfil.size();
if (tipo==1) num_aux=num_aux-1;
vertices.resize(num_aux*num+2);
for (j=0;j<num;j++)
  {for (i=0;i<num_aux;i++)
     {
      vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
      vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
      vertice_aux.y=perfil[i].y;
      vertices[i+j*num_aux]=vertice_aux;
     }
  }

caras.resize(2*(num_aux-1)*num+2*num);
int c=0;
for (j=0;j<num;j++)
 {
  for (i=0;i<num_aux-1;i++)
    {caras[c]._0=i+j*num_aux;
     caras[c]._1=((j+1)%num)*num_aux+i;
     caras[c]._2=1+i+j*num_aux;
     c+=1;
     caras[c]._0=((j+1)%num)*num_aux+i;
     caras[c]._1=((j+1)%num)*num_aux+1+i;
     caras[c]._2=1+i+j*num_aux;
     c+=1;
   }
 }
 
 //tapa inferior
 int total=num_aux*num;
 vertices[total].x=0.0;
 if (tipo==2) vertices[total].y=-radio;
 else vertices[total].y=perfil[0].y;
 vertices[total].z=0.0;

for (j=0;j<num;j++)
 {
     caras[c]._0=j*num_aux;
     caras[c]._1=((j+1)%num)*num_aux;
     caras[c]._2=total;
     c+=1;
 } 
 
//tapa superior
 vertices[total+1].x=0.0;
 if (tipo==1) vertices[total+1].y=perfil[1].y;
 if (tipo==0) vertices[total+1].y=perfil[num_aux-1].y;
 if (tipo==2) vertices[total+1].y=radio;
 vertices[total+1].z=0.0;
 
 for (j=0;j<num;j++)
 {
     caras[c]._0=total+1;
     caras[c]._1=((j+1)%num)*num_aux+num_aux-1;
     caras[c]._2=num_aux-1+j*num_aux;
     c+=1;
 }

//colores de las caras
colors_random();
calcular_normales_caras();
  calcular_normales_vertices();

  colors_flat(0.9,0.7,0.0,-20.0,20.0,-20.0); // Cambiando los tres ultimos parámetros cambiamos de dónde viene la luz
}


//************************************************************************
// objeto cilindro (caso especial de rotacion)
//************************************************************************

_cilindro::_cilindro(float radio, float altura, int num, bool tapa_inf, bool tapa_sup)
{
  vector<_vertex3f> perfil;
  _vertex3f aux;

  aux.x = radio;
  aux.y = -altura / 2.0;
  aux.z = 0.0;
  perfil.push_back(aux);
  aux.x = radio;
  aux.y = altura / 2.0;
  aux.z = 0.0;
  perfil.push_back(aux);
  parametros(perfil, num, 0, tapa_inf, tapa_sup);
}


//************************************************************************
// objeto cono (caso especial de rotacion)
//************************************************************************

_cono::_cono(float radio, float altura, int num, bool tapa_inf, bool tapa_sup)
{
  vector<_vertex3f> perfil;
  _vertex3f aux;

  aux.x = radio;
  aux.y = 0;
  aux.z = 0.0;
  perfil.push_back(aux);
  aux.x = 0.0;
  aux.y = altura;
  aux.z = 0.0;
  perfil.push_back(aux);
  parametros(perfil, num, 1, tapa_inf, tapa_sup); // ambas tapas
}

//************************************************************************
// objeto esfera (caso especial de rotacion)
//************************************************************************

_esfera::_esfera(float radio, int num1, int num2, bool tapa_inf, bool tapa_sup)
{
  vector<_vertex3f> perfil;
  _vertex3f aux;
  int i;
  for (i = 1; i < num1; i++)
  {
    aux.x = radio * cos(M_PI * i / (num1 * 1.0) - M_PI / 2.0);
    aux.y = radio * sin(M_PI * i / (num1 * 1.0) - M_PI / 2.0);
    aux.z = 0.0;
    perfil.push_back(aux);
  }
  parametros(perfil, num2, 2, tapa_inf, tapa_sup); // ninguna tapa
}


//************************************************************************
// rotacion archivo PLY (caso especial de rotacion)
//************************************************************************

_rotacion_PLY::_rotacion_PLY()
{

}

void _rotacion_PLY::parametros_PLY(char *archivo, int num)
{

}


//************************************************************************

//************************************************************************
// objeto por extrusión
//************************************************************************


_extrusion::_extrusion(vector<_vertex3f> poligono, float x, float y, float z)
{
int i;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int num_aux;

// tratamiento de los vértice

num_aux=poligono.size();
vertices.resize(num_aux*2);
for (i=0;i<num_aux;i++)
    {
      vertices[2*i]=poligono[i];
      vertices[2*i+1].x=poligono[i].x+x;
      vertices[2*i+1].y=poligono[i].y+y;
      vertices[2*i+1].z=poligono[i].z+z;
    }
    
// tratamiento de las caras 

caras.resize(num_aux*2);
int c=0;
for (i=0;i<num_aux;i++)         
  {
   caras[c]._0=i*2;
   caras[c]._1=(i*2+2)%(num_aux*2);
   caras[c]._2=i*2+1;    
   c=c+1;
   caras[c]._0=(i*2+2)%(num_aux*2);
   caras[c]._1=(i*2+2)%(num_aux*2)+1;
   caras[c]._2=i*2+1;    
   c=c+1;    
   }  
   
//colores de las caras
colors_random();
calcular_normales_caras();
calcular_normales_vertices();
colors_flat(0.9,0.7,0.0,-20.0,20.0,-20.0); // Cambiando los tres ultimos parámetros cambiamos de dónde viene la luz
}


//************************************************************************
// práctica 3, objeto jerárquico articulado
//************************************************************************

//************************************************************************
// piezas
//************************************************************************


//************************************************************************
// ruedas
//************************************************************************

_rueda_delantera::_rueda_delantera()
{
ancho=0.3;
alto=0.3;
fondo=0.25;
radio=0.15;
};

void _rueda_delantera::draw(_modo modo, float r, float g, float b, float grosor)
{
//rueda delantera 
glPushMatrix();
glRotatef(90,1,0,0);
glScalef(radio, fondo/2.2, radio);
rueda.draw(modo, 0, 0, 0, grosor, plastico_rojo);
glPopMatrix();
};

_rueda_trasera::_rueda_trasera()
{
ancho=0.3;
alto=0.3;
fondo=0.25;
radio=0.15;
};

void _rueda_trasera::draw(_modo modo, float r, float g, float b, float grosor)
{
//rueda trasera
glPushMatrix();
glRotatef(90,1,0,0);
glScalef(radio*1.3, fondo/2.2, radio*1.3);
rueda.draw(modo, 0, 0, 0, grosor, plastico_rojo);
glPopMatrix();
};

_estructura::_estructura()
{
ancho=1.3;
alto=0.3;
fondo=0.78;
};

void _estructura::draw(_modo modo, float r, float g, float b, float grosor)
{
glPushMatrix();
glScalef(ancho, alto, fondo);
cubo.draw(modo, r, g, b, grosor, plastico_rojo);
glPopMatrix();
};

_aleron_trasero_base::_aleron_trasero_base()
{
ancho=0.45;
alto=0.03;
fondo=0.25;
};

void _aleron_trasero_base::draw(_modo modo, float r, float g, float b, float grosor)
{
glPushMatrix();
glScalef(ancho, alto, fondo);
cubo.draw(modo, 0, 0, 1, grosor, plastico_rojo);
glPopMatrix();
};

_aleron_trasero_sup::_aleron_trasero_sup()
{
ancho=0.45;
alto=0.03;
fondo=0.25;
};

void _aleron_trasero_sup::draw(_modo modo, float r, float g, float b, float grosor)
{
glPushMatrix();
glScalef(ancho, alto, fondo);
glTranslatef(0, 0, -0.5);  
cubo.draw(modo, 0, 1, 0, grosor, plastico_rojo);
glPopMatrix();
};

_apendice::_apendice()
{
fondo=0.25;
radio=0.05;
};

void _apendice::draw(_modo modo, float r, float g, float b, float grosor)
{
glPushMatrix();
glRotatef(90,1,0,0);
glScalef(0.2, 0.2, 0.2);
aleron.draw(modo, 0.4, 0, 0, grosor, plastico_rojo);
glPopMatrix();
};

_aleron_delantero_base::_aleron_delantero_base()
{
ancho=0.25;
alto=0.03;
fondo=0.15;
};

void _aleron_delantero_base::draw(_modo modo, float r, float g, float b, float grosor)
{
glPushMatrix();
glScalef(0.25, 0.03, 0.15);
cubo.draw(modo, 0, 0.5, 0.5, grosor, plastico_rojo);
glPopMatrix();
};

_aleron_delantero_sup::_aleron_delantero_sup()
{
ancho=0.45;
alto=0.03;
fondo=0.15;
};

void _aleron_delantero_sup::draw(_modo modo, float r, float g, float b, float grosor)
{
glPushMatrix();
glScalef(0.45, 0.03, 0.15);
cubo.draw(modo, 1, 0, 0, grosor, plastico_rojo);
glPopMatrix();
};


//************************************************************************
// coche (montaje del objeto final)
//************************************************************************

_coche::_coche()
{
giro_ruedas = 0;
giro_ruedas_max_min = 25;
rotacion_ruedas = 0;
giro_aleron_trasero = 0;
giro_aleron_trasero_max = -90;
giro_aleron_min = 0;
giro_aleron_delantero = 0;
giro_aleron_delantero_max = -10;

int color=10;
piezas=13;
grosor_select=2;
color_pick=_vertex3f(1.0,0.0,0.0); 
color_select.resize(piezas);
activo.resize(piezas);

for (int i=0;i<piezas;i++)
  {activo[i]=0;
   color_select[i].r=color_select[i].g=color_select[i].b=color;
   color+=10;
  }
}


void _coche::draw(_modo modo, float r, float g, float b, float grosor, _material material)
{
float r_p,g_p,b_p;
int tam=13;

r_p=color_pick.r;
g_p=color_pick.g;
b_p=color_pick.b;

glPushMatrix();
glTranslatef(-2*rueda_delantera_izq.ancho,-rueda_delantera_izq.alto/2.0,-0.5);
glRotatef(rotacion_ruedas, 0, 0, 1);
glRotatef(giro_ruedas, 0, 1, 0);
if (activo[0]==1) rueda_delantera_izq.draw(EDGES, r_p, g_p, b_p, grosor_select);
else rueda_delantera_izq.draw(modo, r, g, b, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(-2*rueda_delantera_der.ancho,-rueda_delantera_der.alto/2.0,0.5);
glRotatef(rotacion_ruedas, 0, 0, 1);
glRotatef(giro_ruedas, 0, 1, 0);
if (activo[1]==1) rueda_delantera_der.draw(EDGES, r_p, g_p, b_p, grosor_select);
else rueda_delantera_der.draw(modo, r, g, b, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(2*rueda_trasera_izq.ancho,-(rueda_trasera_izq.alto/2.0)*0.7,-0.5);
glRotatef(rotacion_ruedas, 0, 0, 1);
if (activo[2]==1) rueda_trasera_izq.draw(EDGES, r_p, g_p, b_p, grosor_select);
else rueda_trasera_izq.draw(modo, r, g, b, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(2*rueda_trasera_der.ancho,-(rueda_trasera_der.alto/2.0)*0.7,0.5);
glRotatef(rotacion_ruedas, 0, 0, 1);
if (activo[3]==1) rueda_trasera_der.draw(EDGES, r_p, g_p, b_p, grosor_select);
else rueda_trasera_der.draw(modo, r, g, b, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(0.08, -0.1, 0);
if (activo[4]==1) estructura.draw(EDGES, r_p, g_p, b_p, grosor_select);
else estructura.draw(modo, r, g, b, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(estructura.ancho/2 - aleron_trasero_base_izq.ancho/8, estructura.alto - aleron_trasero_base_izq.alto/4 - 0.05, -estructura.fondo/2+aleron_trasero_base_izq.fondo/4);
glRotatef(90, 0, 0, 1);
glRotatef(90, 1, 0, 0);
if (activo[5]==1) aleron_trasero_base_izq.draw(EDGES, r_p, g_p, b_p, grosor_select);
else aleron_trasero_base_izq.draw(modo, r, g, b, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(estructura.ancho/2 - aleron_trasero_base_izq.ancho/8, estructura.alto - aleron_trasero_base_izq.alto/4 - 0.05, estructura.fondo/2-aleron_trasero_base_izq.fondo/4);
glRotatef(90, 0, 0, 1);
glRotatef(90, 1, 0, 0);
if (activo[6]==1) aleron_trasero_base_drch.draw(EDGES, r_p, g_p, b_p, grosor_select);
else aleron_trasero_base_drch.draw(modo, r, g, b, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(estructura.ancho/2 -aleron_trasero_sup_inmovil.ancho/8 + 0.13, estructura.alto + aleron_trasero_sup_movil.alto - 0.05, 0);
glRotatef(90, 0, 1, 0);
glScalef(1.5, 1, 1);
if (activo[7]==1) aleron_trasero_sup_inmovil.draw(EDGES, r_p, g_p, b_p, grosor_select);
else aleron_trasero_sup_inmovil.draw(modo, r, g, b, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(estructura.ancho/2 +0.05, estructura.alto + aleron_trasero_sup_movil.alto*4 +0.025, 0);
glRotatef(90, 0, 1, 0);
glRotatef(90, 1, 0, 0);
glScalef(1.5, 1, -0.6);
glRotatef(giro_aleron_trasero, 1, 0, 0);
if (activo[8]==1) aleron_trasero_sup_movil.draw(EDGES, r_p, g_p, b_p, grosor_select);
else aleron_trasero_sup_movil.draw(modo, r, g, b, grosor);
glPopMatrix();

glPushMatrix();
glRotatef(-90, 1, 0, 0);
glRotatef(-90, 0, 1, 0);
glTranslatef(-0.13, 0, 0.57);
if (activo[9]==1) apendice.draw(EDGES, r_p, g_p, b_p, grosor_select);
else apendice.draw(modo, r, g, b, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(-estructura.ancho/2 -aleron_delantero_sup.ancho/8 + 0.13 - aleron_delantero_sup.ancho*0.7 -0.08, -estructura.alto/2 , 0);
glRotatef(90, 0, 1, 0);
glScalef(2.2, 1, 1);
glRotatef(giro_aleron_delantero, 1, 0, 0);
if (activo[10]==1) aleron_delantero_sup.draw(EDGES, r_p, g_p, b_p, grosor_select);
else aleron_delantero_sup.draw(modo, r, g, b, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(-estructura.ancho/2 - aleron_trasero_base_izq.ancho + 0.134, -estructura.alto/4, -estructura.fondo/2 - aleron_delantero_sup.fondo*0.7);
glScalef(1, 0.5, 1);
glRotatef(90, 0, 0, 1);
glRotatef(90, 1, 0, 0);
if (activo[11]==1) aleron_delantero_base_izq.draw(EDGES, r_p, g_p, b_p, grosor_select);
else aleron_delantero_base_izq.draw(modo, r, g, b, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(-estructura.ancho/2 - aleron_trasero_base_izq.ancho + 0.134, -estructura.alto/4, estructura.fondo/2 + aleron_delantero_sup.fondo*0.70);
glScalef(1, 0.5, 1);
glRotatef(90, 0, 0, 1);
glRotatef(90, 1, 0, 0);
if (activo[12]==1) aleron_delantero_base_drch.draw(EDGES, r_p, g_p, b_p, grosor_select);
else aleron_delantero_base_drch.draw(modo, r, g, b, grosor);
glPopMatrix();
};

void _coche::seleccion()
{
_vertex3i color;

glPushMatrix();
glTranslatef(-2*rueda_delantera_izq.ancho,-rueda_delantera_izq.alto/2.0,-0.5);
glRotatef(rotacion_ruedas, 0, 0, 1);
glRotatef(giro_ruedas, 0, 1, 0);
color=color_select[0];
rueda_delantera_izq.draw(SELECT, color.r, color.g, color.b, 1);
glPopMatrix();

glPushMatrix();
glTranslatef(-2*rueda_delantera_der.ancho,-rueda_delantera_der.alto/2.0,0.5);
glRotatef(rotacion_ruedas, 0, 0, 1);
glRotatef(giro_ruedas, 0, 1, 0);
color=color_select[1];
rueda_delantera_der.draw(SELECT, color.r, color.g, color.b, 1);
glPopMatrix();

glPushMatrix();
glTranslatef(2*rueda_trasera_izq.ancho,-(rueda_trasera_izq.alto/2.0)*0.7,-0.5);
glRotatef(rotacion_ruedas, 0, 0, 1);
color=color_select[2];
rueda_trasera_izq.draw(SELECT, color.r, color.g, color.b, 1);
glPopMatrix();

glPushMatrix();
glTranslatef(2*rueda_trasera_der.ancho,-(rueda_trasera_der.alto/2.0)*0.7,0.5);
glRotatef(rotacion_ruedas, 0, 0, 1);
color=color_select[3];
rueda_trasera_der.draw(SELECT, color.r, color.g, color.b, 1);
glPopMatrix();

glPushMatrix();
glTranslatef(0.08, -0.1, 0);
color=color_select[4];
estructura.draw(SELECT, color.r, color.g, color.b, 1);
glPopMatrix();

glPushMatrix();
glTranslatef(estructura.ancho/2 - aleron_trasero_base_izq.ancho/8, estructura.alto - aleron_trasero_base_izq.alto/4 - 0.05, -estructura.fondo/2+aleron_trasero_base_izq.fondo/4);
glRotatef(90, 0, 0, 1);
glRotatef(90, 1, 0, 0);
color=color_select[5];
aleron_trasero_base_izq.draw(SELECT, color.r, color.g, color.b, 1);
glPopMatrix();

glPushMatrix();
glTranslatef(estructura.ancho/2 - aleron_trasero_base_izq.ancho/8, estructura.alto - aleron_trasero_base_izq.alto/4 - 0.05, estructura.fondo/2-aleron_trasero_base_izq.fondo/4);
glRotatef(90, 0, 0, 1);
glRotatef(90, 1, 0, 0);
color=color_select[6];
aleron_trasero_base_drch.draw(SELECT, color.r, color.g, color.b, 1);
glPopMatrix();

glPushMatrix();
glTranslatef(estructura.ancho/2 -aleron_trasero_sup_inmovil.ancho/8 + 0.13, estructura.alto + aleron_trasero_sup_movil.alto - 0.05, 0);
glRotatef(90, 0, 1, 0);
glScalef(1.5, 1, 1);
color=color_select[7];
aleron_trasero_sup_inmovil.draw(SELECT, color.r, color.g, color.b, 1);
glPopMatrix();

glPushMatrix();
glTranslatef(estructura.ancho/2 +0.05, estructura.alto + aleron_trasero_sup_movil.alto*4 +0.025, 0);
glRotatef(90, 0, 1, 0);
glRotatef(90, 1, 0, 0);
glScalef(1.5, 1, -0.6);
glRotatef(giro_aleron_trasero, 1, 0, 0);
color=color_select[8];
aleron_trasero_sup_movil.draw(SELECT, color.r, color.g, color.b, 1);
glPopMatrix();

glPushMatrix();
glRotatef(-90, 1, 0, 0);
glRotatef(-90, 0, 1, 0);
glTranslatef(-0.13, 0, 0.57);
color=color_select[9];
apendice.draw(SELECT, color.r, color.g, color.b, 1);
glPopMatrix();

glPushMatrix();
glTranslatef(-estructura.ancho/2 -aleron_delantero_sup.ancho/8 + 0.13 - aleron_delantero_sup.ancho*0.7 -0.08, -estructura.alto/2 , 0);
glRotatef(90, 0, 1, 0);
glScalef(2.2, 1, 1);
glRotatef(giro_aleron_delantero, 1, 0, 0);
color=color_select[10];
aleron_delantero_sup.draw(SELECT, color.r, color.g, color.b, 1);
glPopMatrix();

glPushMatrix();
glTranslatef(-estructura.ancho/2 - aleron_trasero_base_izq.ancho + 0.134, -estructura.alto/4, -estructura.fondo/2 - aleron_delantero_sup.fondo*0.7);
glScalef(1, 0.5, 1);
glRotatef(90, 0, 0, 1);
glRotatef(90, 1, 0, 0);
color=color_select[11];
aleron_delantero_base_izq.draw(SELECT, color.r, color.g, color.b, 1);
glPopMatrix();

glPushMatrix();
glTranslatef(-estructura.ancho/2 - aleron_trasero_base_izq.ancho + 0.134, -estructura.alto/4, estructura.fondo/2 + aleron_delantero_sup.fondo*0.70);
glScalef(1, 0.5, 1);
glRotatef(90, 0, 0, 1);
glRotatef(90, 1, 0, 0);
color=color_select[12];
aleron_delantero_base_drch.draw(SELECT, color.r, color.g, color.b, 1);
glPopMatrix();
}
