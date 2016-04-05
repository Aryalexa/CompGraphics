#pragma once
class VerticeNormal
{
private:
	int indiceVertice, indiceNormal;
public:
	VerticeNormal();
	VerticeNormal(int indiceVertice, int indiceNormal);
	~VerticeNormal();
	int getIndiceVertice();
	int getIndiceNormal();
};

