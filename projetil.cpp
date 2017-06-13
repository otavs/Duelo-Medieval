#include "projetil.h"

Projetil::Projetil(){
	this->x = 0; 
	this->y = 0;
	this->v = 0;
	this->largura = 0;
	this->altura = 0;
	this->sentido = 0;
	this->tipo = 0;
}

Projetil::Projetil(int x, int y, int largura, int altura, int v, int sentido, int tipo){
	this->x = x;
	this->y = y;
	this->v = v;
	this->largura = largura;
	this->altura = altura;
	this->sentido = sentido;
	this->tipo = tipo;
}

void Projetil::andar(){
	if(sentido == 1)
		x += v;
	else
		x -= v;
}

void Projetil::desenhar(){
	al_draw_filled_rectangle(x-largura/2, y-altura/2, x+largura/2, y+altura/2, al_map_rgb(0, 0, 255));
}

bool Projetil::operator==(Projetil p){
	return true;
}

void Projetil::setX(int x){
	this->x = x;
}
int Projetil::getX(){
	return x;
}

void Projetil::setY(int y){
	this->y = y;
}
int Projetil::getY(){
	return y;
}

void Projetil::setV(int v){
	this->v = v;
}
int Projetil::getV(){
	return v;
}

void Projetil::setLargura(int largura){
	this->largura = largura;
}
int Projetil::getLargura(){
	return largura;
}

void Projetil::setAltura(int altura){
	this->altura = altura;
}
int Projetil::getAltura(){
	return altura;
}
