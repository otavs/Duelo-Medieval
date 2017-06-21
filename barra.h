#ifndef BARRA_H
#define BARRA_H

#include "includes.h"

class Barra{
	private:
		int x1, y1, largura, altura, valorMax;
		ALLEGRO_COLOR cor;
	public:
		Barra();
		Barra(int x1, int y1, int largura, int altura, int valorMax, ALLEGRO_COLOR cor);	
		desenhar(int valor);
};


#endif
