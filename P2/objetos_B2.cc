//**************************************************************************
// Práctica 2 
//**************************************************************************

#include "objetos_B2.h"
#include "file_ply_stl.hpp"


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
int i;
glPointSize(grosor);
glColor3f(r,g,b);
glBegin(GL_POINTS);
for (i=0;i<vertices.size();i++){
	glVertex3fv((GLfloat *) &vertices[i]);
	}
glEnd();
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
int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
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

void _triangulos3D::draw_solido_colores()
{
	
int i;	
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);
  
  for (unsigned int i=0;i<caras.size();i++){
  	glColor3f(colores[i].r, colores[i].g, colores[i].b);
    glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
    glEnd();
}

//*************************************************************************
// dibujar con distintos modos
//*************************************************************************

void _triangulos3D::draw(_modo modo, float r, float g, float b, float grosor)
{
switch (modo)
	{
	case POINTS:
		draw_puntos(r, g, b, grosor);
		break;
	case EDGES:
		draw_aristas(r, g, b, grosor);
		break;
	case SOLID:
		draw_solido(r, g, b);
		break;
	case SOLID_COLORS:
		draw_solido_colores();
		break;
	}
}

//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam)
{
// vertices
vertices.resize(8);
vertices[0].x = 0;vertices[0].y = 0;vertices[0].z = 0;
vertices[1].x = 0;vertices[1].y = 0;vertices[1].z = tam;
vertices[2].x = tam;vertices[2].y = 0;vertices[2].z = tam;
vertices[3].x = tam;vertices[3].y = 0;vertices[3].z = 0;
vertices[4].x = tam;vertices[4].y = tam;vertices[4].z = 0;
vertices[5].x = 0;vertices[5].y = tam;vertices[5].z = 0;
vertices[6].x = 0;vertices[6].y = tam;vertices[6].z = tam;
vertices[7].x = tam;vertices[7].y = tam;vertices[7].z = tam;

// triangulos
caras.resize(12);
caras[0]._0 = 0;caras[0]._1 = 1;caras[0]._2 = 3;
caras[1]._0 = 2;caras[1]._1 = 3;caras[1]._2 = 1;
caras[2]._0 = 1;caras[2]._1 = 2;caras[2]._2 = 6;
caras[3]._0 = 2;caras[3]._1 = 7;caras[3]._2 = 6;
caras[4]._0 = 2;caras[4]._1 = 4;caras[4]._2 = 7;
caras[5]._0 = 2;caras[5]._1 = 3;caras[5]._2 = 4;
caras[6]._0 = 3;caras[6]._1 = 4;caras[6]._2 = 0;
caras[7]._0 = 0;caras[7]._1 = 4;caras[7]._2 = 5;
caras[8]._0 = 0;caras[8]._1 = 5;caras[8]._2 = 6;
caras[9]._0 = 1;caras[9]._1 = 0;caras[9]._2 = 6;
caras[10]._0 = 6;caras[10]._1 = 7;caras[10]._2 = 4;
caras[11]._0 = 4;caras[11]._1 = 5;caras[11]._2 = 6;

//colores
colores.resize(12);
colores[0].r=0.0;colores[0].g=0;colores[0].b=0;
colores[1].r=0.1;colores[1].g=0;colores[1].b=0;
colores[2].r=0.2;colores[2].g=0;colores[2].b=0;
colores[3].r=0.3;colores[3].g=0;colores[3].b=0;
colores[4].r=0.4;colores[4].g=0;colores[4].b=0;
colores[5].r=0.5;colores[5].g=1.0;colores[5].b=0;
colores[6].r=0.5;colores[6].g=0;colores[6].b=0;
colores[7].r=0.6;colores[7].g=0;colores[7].b=0;
colores[8].r=0.7;colores[8].g=0;colores[8].b=0;
colores[9].r=0.8;colores[9].g=0;colores[9].b=0;
colores[10].r=0.9;colores[10].g=0;colores[10].b=0;
colores[11].r=1.0;colores[11].g=1.0;colores[11].b=0;
}


//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al)
{

//vertices 
vertices.resize(5); 
vertices[0].x=-tam;vertices[0].y=0;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=0;vertices[2].z=-tam;
vertices[3].x=-tam;vertices[3].y=0;vertices[3].z=-tam;
vertices[4].x=0;vertices[4].y=al;vertices[4].z=0;

//triangulos
caras.resize(6);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=4;
caras[1]._0=1;caras[1]._1=2;caras[1]._2=4;
caras[2]._0=2;caras[2]._1=3;caras[2]._2=4;
caras[3]._0=3;caras[3]._1=0;caras[3]._2=4;
caras[4]._0=3;caras[4]._1=1;caras[4]._2=0;
caras[5]._0=3;caras[5]._1=2;caras[5]._2=1;


//colores
colores.resize(6);
colores[0].r=0.0;colores[0].g=0;colores[0].b=0;
colores[1].r=0.4;colores[1].g=0;colores[1].b=0;
colores[2].r=0.6;colores[2].g=0;colores[2].b=0;
colores[3].r=0.7;colores[3].g=0;colores[3].b=0;
colores[4].r=0.9;colores[4].g=0;colores[4].b=0;
colores[5].r=1.0;colores[5].g=1.0;colores[5].b=0;
}

//*************************************************************************
// clase cilindro
//*************************************************************************

_cilindro::_cilindro(float radio, float altura, int num) {
  vector<_vertex3f> perfil;
	_vertex3f aux;
	aux.x = radio;
	aux.y = 0;
	aux.z = 0;
	perfil.push_back(aux);

	aux.x = radio;
	aux.y = altura;
	aux.z = 0;
	perfil.push_back(aux);

	parametros(perfil, num);
}

//*************************************************************************
// clase cono
//*************************************************************************

_cono::_cono(float radio, float altura, int num) {
  vector<_vertex3f> perfil;
	_vertex3f aux;
	aux.x = radio;
	aux.y = 0;
	aux.z = 0;
	perfil.push_back(aux);

	aux.x = 0;
	aux.y = altura;
	aux.z = 0;
	perfil.push_back(aux);

	parametros(perfil, num);
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
  int n_ver,n_car;

  vector<float> ver_ply ;
  vector<int>   car_ply ;
  
  _file_ply::read(archivo, ver_ply, car_ply );

  n_ver=ver_ply.size()/3;
  n_car=car_ply.size()/3;

  printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

  //vertices
  vertices.resize(n_ver);
  for(int i = 0; i < n_ver; i++) {
    vertices[i].x = ver_ply[3 * i];
    vertices[i].y = ver_ply[3 * i + 1];
    vertices[i].z = ver_ply[3 * i + 2];
  }

  //caras
  caras.resize(n_car);
  for(int i = 0; i < n_car; i++) {
    caras[i]._0 = car_ply[3 * i];
    caras[i]._1 = car_ply[3 * i + 1];
    caras[i]._2 = car_ply[3 * i + 2];
  }

  //colores
  float sum;
  int n;
  colores.resize(2*(n_car+1));

  for(int i = 0; i < n_car; i++) {
    if(vertices[caras[i]._0].y >= 0) {
      colores[i].r = rand()%1000/1000.0;
      colores[i].b = 0.0;
      colores[i].g = 0.8;
    }
    else {
      colores[i].r = 0.0;
      n = rand()%10;
      sum = rand()%100/400.0;
      if (n > 5) {
        colores[i].b = 0.805 + sum;
        colores[i].g = 0.816 + sum;
      }
      else {
        colores[i].b = 0.805 - sum;
        colores[i].g = 0.816 - sum;
      }
    }
  }
}


//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion()
{

}

// Crear un ply por revolución
_rotacion::_rotacion(const char *archivo, int num){
	int n_ver, n_car;

	vector<float> ver_ply;
	vector<int> car_ply;

	// Leer el archivo ply
	_file_ply::read(archivo, ver_ply, car_ply);

	n_ver = ver_ply.size()/3;
	n_car = car_ply.size()/3;

	// Guardar las caras del perfil
	vector<_vertex3f> perfil;
	_vertex3f aux;

	for(int i=0; i<n_ver; i++){
		aux.x = ver_ply[i*3];
		aux.y = ver_ply[i*3+1];
		aux.z = ver_ply[i*3+2];
		perfil.push_back(aux);
	}

	// Crear el objeto por revolución
	parametros(perfil, num);
}

void _rotacion::parametros(vector<_vertex3f> perfil, int num)
{
int i,j;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int num_aux;

// tratamiento de los vértice

num_aux=perfil.size();
vertices.resize(num_aux*num);
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

// tratamiento de las caras 
  caras.resize(num_aux * num * 2);
	for (j = 0; j < num; j++)
	{
		for (i = 0; i < num_aux - 1; i++)
		{
			if (j < num - 1)
			{
				cara_aux._0 = i + j * num_aux;
				cara_aux._1 = i + (j + 1) * num_aux;
				cara_aux._2 = i + 1 + j * num_aux;
				caras[i * 2 + j * num_aux * 2] = cara_aux;
				cara_aux._0 = i + (j + 1) * num_aux;
				cara_aux._1 = i + 1 + (j + 1) * num_aux;
				cara_aux._2 = i + 1 + j * num_aux;
				caras[i * 2 + 1 + j * num_aux * 2] = cara_aux;
			}
			else
			{
				cara_aux._0 = i + j * num_aux;
				cara_aux._1 = i + num_aux;
				cara_aux._2 = i + 1 + j * num_aux;
				caras[i * 2 + j * num_aux * 2] = cara_aux;
				cara_aux._0 = i + num_aux;
				cara_aux._1 = i + 1 + num_aux;
				cara_aux._2 = i + 1 + j * num_aux;
				caras[i * 2 + 1 + j * num_aux * 2] = cara_aux;
			}
		}
	}

// tapa inferior
if (fabs(perfil[0].x) > 0.0)
	{
		vertice_aux.x = 0.0;
		vertice_aux.y = perfil[0].y;
		vertice_aux.z = 0.0;
		vertices.push_back(vertice_aux);
		for (j = 0; j < num; j++)
		{
			cara_aux._0 = vertices.size() - 1;
			if (j < num - 1)
			{
				cara_aux._1 = j * num_aux;
				cara_aux._2 = (j + 1) * num_aux;
			}
			else
			{
				cara_aux._1 = j * num_aux;
				cara_aux._2 = 0;
			}
			caras.push_back(cara_aux);
		}
	}
 
// tapa superior
if (fabs(perfil[num_aux - 1].x) > 0.0)
	{
		vertice_aux.x = 0.0;
		vertice_aux.y = perfil[num_aux - 1].y;
		vertice_aux.z = 0.0;
		vertices.push_back(vertice_aux);
		for (j = 0; j < num; j++)
		{
			cara_aux._0 = vertices.size() - 1;
			if (j < num - 1)
			{
				cara_aux._1 = (j + 1) * num_aux - 1;
				cara_aux._2 = j * num_aux - 1;
			}
			else
			{
				cara_aux._1 = num_aux - 1;
				cara_aux._2 = j * num_aux - 1;
			}
			caras.push_back(cara_aux);
		}
	}

}


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
}

_esfera::_esfera(float radio, int num1, int num2){
	vector<_vertex3f> perfil;
	_vertex3f aux;

	for (int i = 1; i < num1; i++){
		aux.x = radio * sin(M_PI * i / num1);
		aux.y = radio * cos(M_PI * i / num1);
		aux.z = 0;
		perfil.push_back(aux);
	}

	parametros(perfil, num1);
}