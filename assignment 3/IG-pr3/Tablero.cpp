#include "Tablero.h"


Tablero::Tablero(int dimX, int dimY, int dimZ){
	// borrar atributos
	numHijos = dimX * dimY * dimZ;
	hijos = new Objeto3D*[numHijos];

	for (int ii=0; ii<numHijos; ii++)
		hijos[ii] = new Cubo();
	
	for (int y=0; y<dimY; y++)
		for (int z=0; z<dimZ; z++)
			for (int x=0; x<dimX; x++)
				hijos[ y*dimX*dimZ + z*dimX + x ]->traslada(new PV3D(x-dimX/2.0+0.5, y-dimY/2.0+0.5, z-dimZ/2.0+0.5, 1));//(x,y,z,1));//
			
}

Tablero::~Tablero(void)
{
}
