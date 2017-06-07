#ifndef PLAYER_H
#define PLAYER_H

class Player{
	
	private:
		int x, y, vx, vy, largura, altura, vida, poder, sentido, larguraAtaque, alturaAtaque, classe;
		Lista<Projetil*> listaProjeteis;
		
	public:
		Player();
		Player(int x, int y, int vx, int vy, int largura, int altura, int vida, int poder, int sentido,
			int larguraAtaque, int alturaAtaque, int classe);
		void atacar(Player&);
		void andarDireita();
		void andarEsquerda();
		void andarCima();
		void andarBaixo();
		void desenhar();
		void atualizaProjeteis(Player&);
		void desenhaProjeteis();
		
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
		
		void levaDano(int dano);
		
};

#endif
