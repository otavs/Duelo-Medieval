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
    if(sentido == 1){
        if(tipo == flecha){
            //al_draw_filled_rectangle(x-largura/2, y-altura/2, x+largura/2, y+altura/2, al_map_rgb(0, 0, 255));
            al_draw_bitmap(img_flecha, x-largura/2, y-altura/2, 0);
        }
        else if(tipo == magia){
            //al_draw_filled_rectangle(x-largura/2, y-altura/2, x+largura/2, y+altura/2, al_map_rgb(0, 255, 0));
            al_draw_bitmap(img_magia, x-largura/2, y-altura/2, 0);
        }
        else if(tipo == runaPoder){
            //al_draw_filled_rectangle(x-largura/2, y-altura/2, x+largura/2, y+altura/2, al_map_rgb(255, 0, 0));
            al_draw_bitmap(img_runaPoder, x-largura/2, y-altura/2, 0);
        }
        else if(tipo == laser){
            al_draw_filled_rounded_rectangle(x-largura/2, y-altura/2, x+largura/2, y+altura/2, 4, 4, al_map_rgb(12, 12, 137));
            al_draw_rounded_rectangle(x-largura/2, y-altura/2, x+largura/2, y+altura/2, 4, 4, al_map_rgb(145, 238, 255), 3);
        }
    }
    if(sentido == 0){
        if(tipo == flecha){
            //al_draw_filled_rectangle(x-largura/2, y-altura/2, x+largura/2, y+altura/2, al_map_rgb(0, 0, 255));
            al_draw_bitmap(img_flecha, x-largura/2, y-altura/2, ALLEGRO_FLIP_HORIZONTAL);
        }
        else if(tipo == magia){
            //al_draw_filled_rectangle(x-largura/2, y-altura/2, x+largura/2, y+altura/2, al_map_rgb(0, 255, 0));
            al_draw_bitmap(img_magia, x-largura/2, y-altura/2, ALLEGRO_FLIP_HORIZONTAL);
        }
        else if(tipo == runaPoder){
            //al_draw_filled_rectangle(x-largura/2, y-altura/2, x+largura/2, y+altura/2, al_map_rgb(255, 0, 0));
            al_draw_bitmap(img_runaPoder, x-largura/2, y-altura/2, ALLEGRO_FLIP_HORIZONTAL);
        }
        else if(tipo == laser){
            al_draw_filled_rounded_rectangle(x-largura/2, y-altura/2, x+largura/2, y+altura/2, 4, 4, al_map_rgb(12, 12, 137));
            al_draw_rounded_rectangle(x-largura/2, y-altura/2, x+largura/2, y+altura/2, 4, 4, al_map_rgb(145, 238, 255), 3);
        }
    }
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
void Projetil::setTipo(int tipo){
	this->tipo = tipo;
}
int Projetil::getTipo(){
	return tipo;
}

ALLEGRO_BITMAP* Projetil::img_flecha;
ALLEGRO_BITMAP* Projetil::img_runaPoder;
ALLEGRO_BITMAP* Projetil::img_magia;

void Projetil::inicializarImagens(){
	img_flecha = al_load_bitmap("imagens/flecha.png");
	img_runaPoder = al_load_bitmap("imagens/runaPoder.png");
	img_magia = al_load_bitmap("imagens/magia.png");
}
