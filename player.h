#ifndef PLAYER_H
#define PLAYER_H

#include "includes.h"

#include "timer.h"
#include "lista.h"
#include "projetil.h"
#include "item.h"

class Player{
	
	private:
		int x, y, vx, vy, largura, altura, vida, poder, sentido, larguraAtaque, alturaAtaque, classe, vidaMax;
		Lista<Projetil*> listaProjeteis;
		Timer cooldown;
		Lista<Item> listaItens;
		ALLEGRO_BITMAP *imagem[4];
		static ALLEGRO_BITMAP *img_guerreiro[4];
		static ALLEGRO_BITMAP *img_arqueiro[4];
		static ALLEGRO_BITMAP *img_mago[4];
		static ALLEGRO_BITMAP *img_barbaro[4];
		Timer timerAnimacaoAndar;
		Timer efeitoGema;
		
	public:
		Player();
		Player(int x, int y, int classe, int sentido);
		void atacar(Player&);
		void andarDireita(int limite);
		void andarEsquerda(int limite);
		void andarCima(int limite);
		void andarBaixo(int limite);
		void desenhar(bool movimento);
		void atualizaProjeteis(Player&);
		void desenhaProjeteis();
		
		void atualizaTimers();
		
		int getValorCooldown();
		
		bool operator==(Player);
		
		void setX(int x);
		int getX();
		void setY(int y);
		int getY();
		void setVx(int vx);
		int getVx();
		void setVy(int vy);
		int getVy();
		void setLargura(int largura);
		int getLargura();
		void setAltura(int altura);
		int getAltura();
		void setVida(int vida);
		int getVida();
		void setPoder(int poder);
		int getPoder();
		void setVidaMax(int vidaMax);
		int getVidaMax();
		Timer getCooldown();

		Lista<Item> getListaItens();

		void levaDano(int dano);
		
		void pegaItem(Item item);
		
		void usaItem(int i);
		
		static void inicializarImagens();
		
};

#endif
