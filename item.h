#ifndef ITEM_H
#define ITEM_H

#include "includes.h"

class Item{

	private:
		int x, y, altura, largura, tipo;
        static ALLEGRO_BITMAP *img_pocao;
		static ALLEGRO_BITMAP *img_runa;
		static ALLEGRO_BITMAP *img_gema;

	public:
		Item();
		Item(int x, int y, int tipo);

		void desenhar();

		bool operator==(Item);

		void setX(int x);
		int getX();
		void setY(int y);
		int getY();
		void setLargura(int largura);
		int getLargura();
		void setAltura(int altura);
		int getAltura();
		void setTipo(int tipo);
		int getTipo();
		static void inicializarImagens();
		static void desenharImagem(int seletor, int x, int y);
};

#endif
