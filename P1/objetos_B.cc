//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include "objetos_B.h"


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
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam)
{
	//vertices
	vertices.resize(8);
  vertices[0].x = 0;vertices[0].y = 0;vertices[0].z = 0;
  vertices[1].x = 0;vertices[1].y = 0;vertices[1].z = tam;
  vertices[2].x = tam;vertices[2].y = 0;vertices[2].z = tam;
  vertices[3].x = tam;vertices[3].y = 0;vertices[3].z = 0;
  vertices[4].x = tam;vertices[4].y = tam;vertices[4].z = 0;
  vertices[5].x = 0;vertices[5].y = tam;vertices[5].z = 0;
  vertices[6].x = 0;vertices[6].y = tam;vertices[6].z = tam;
  vertices[7].x = tam;vertices[7].y = tam;vertices[7].z = tam;

	//caras
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

	//caras
	caras.resize(6);
	caras[0]._0=0;caras[0]._1=1;caras[0]._2=4;
	caras[1]._0=1;caras[1]._1=2;caras[1]._2=4;
	caras[2]._0=2;caras[2]._1=3;caras[2]._2=4;
	caras[3]._0=3;caras[3]._1=0;caras[3]._2=4;
	caras[4]._0=3;caras[4]._1=1;caras[4]._2=0;
	caras[5]._0=3;caras[5]._1=2;caras[5]._2=1;

	//colores
	colores.resize(6);
	colores[0].r=0.2;colores[0].g=0;colores[0].b=0;
	colores[1].r=0.4;colores[1].g=0;colores[1].b=0;
	colores[2].r=0.6;colores[2].g=0;colores[2].b=0;
	colores[3].r=0.7;colores[3].g=0;colores[3].b=0;
	colores[4].r=0.9;colores[4].g=0;colores[4].b=0;
	colores[5].r=1.0;colores[5].g=1.0;colores[5].b=0;
	
	/*
	float ini = 1.0;
	int i = 0;
	
	for (i=0; i<6; i++) {
		
	}
	*/
}
