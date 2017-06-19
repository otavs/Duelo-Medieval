#include "item.h"

Item::Item(){
	this->x = 0;
	this->y = 0;
	this->largura = 0;
	this->altura = 0;
	this->tipo = 0;
}

Item::Item(int x, int y, int tipo){
	this->x = x;
	this->y = y;
	this->tipo = tipo;
	if(tipo == pocao){
		largura = 30;
		altura = 30;
	}
	else if(tipo == runa){
		largura = 30;
		altura = 30;
	}
	else if(tipo == gema){
		largura = 30;
		altura = 30;
	}
}

void Item::setX(int x){
	this->x = x;
}
int Item::getX(){
	return x;
}

void Item::setY(int y){
	this->y = y;
}
int Item::getY(){
	return y;
}

void Item::setLargura(int largura){
	this->largura = largura;
}
int Item::getLargura(){
	return largura;
}

void Item::setAltura(int altura){
	this->altura = altura;
}
int Item::getAltura(){
	return altura;
}

void Item::setTipo(int tipo){
	this->tipo = tipo;
}
int Item::getTipo(){
	return tipo;
}

void Item::desenhar(){
	if(tipo == pocao){
		al_draw_filled_rectangle(x-largura/2, y-altura/2, x+largura/2, y+altura/2, al_map_rgb(255, 0, 0));
	}
	else if(tipo == runa){
		al_draw_filled_rectangle(x-largura/2, y-altura/2, x+largura/2, y+altura/2, al_map_rgb(0, 255, 0));
	}
	else if(tipo == gema){
		al_draw_filled_rectangle(x-largura/2, y-altura/2, x+largura/2, y+altura/2, al_map_rgb(0, 0, 255));
	}
	
}

bool Item::operator==(Item x){
	return true;
}
