#include "barra.h"

Barra::Barra(){
	
}

Barra::Barra(int x1, int y1, int largura, int altura, int valorMax, ALLEGRO_COLOR cor){
	this->x1 = x1;
	this->y1 = y1;
	this->largura =largura;
	this->altura = altura;
	this->valorMax = valorMax;
	this->cor = cor;
}

Barra::desenhar(int valor){
	al_draw_filled_rectangle(x1, y1, x1+largura*valor/valorMax, y1+altura, cor);
	al_draw_rectangle(x1, y1, x1+largura, y1+altura, al_map_rgb(255, 255, 255), 3);
}
