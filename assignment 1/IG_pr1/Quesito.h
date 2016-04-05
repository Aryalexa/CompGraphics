#include "Malla.h"


class Quesito :
	public Malla
{
private:
	int nQ;		//numero de veces en que se divide la parte circular 
	GLfloat r;	//es el radio
	GLfloat h;	//es la altura.
	int N;		//360/N ser�n los grados del quesito

public:
	Quesito(int nQ, GLfloat r, GLfloat h, int N);
	~Quesito();
	void dibujaNquesitos();


};