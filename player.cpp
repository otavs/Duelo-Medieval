#include "player.h"

Player::Player(){
	this->x = 0;
	this->y = 0;
	this->vx= 0;
	this->vy = 0;
	this->largura = 0;
	this->altura = 0;
	this->vida = 0;
	this->poder = 0;
	this->sentido = 0;
	this->larguraAtaque = 0;
	this->alturaAtaque = 0;
	this->classe = 0;
}

Player::Player(int x, int y, int classe, int sentido){
	this->x = x;
	this->y = y;
	this->classe = classe;
	this->sentido = sentido;
	if(classe == guerreiro){
		vx = 5;
		vy = 4;
		largura = 40;
		altura = 80;
		vida = 100;
		poder = 5;
		larguraAtaque = 40;
		alturaAtaque = 20;
		cooldown = Timer(3*60);
	}
	else if(classe == mago){
		vx = 5;
		vy = 4;
		largura = 40;
		altura = 80;
		vida = 100;
		poder = 8;
		larguraAtaque = 40;
		alturaAtaque = 20;
		cooldown = Timer(3*60);
	}
	else if(classe == arqueiro){
		vx = 6;
		vy = 4;
		largura = 40;
		altura = 80;
		vida = 80;
		poder = 3;
		larguraAtaque = 40;
		alturaAtaque = 20;
		cooldown = Timer(1*60);
	}
	else if(classe == barbaro){
		vx = 3;
		vy = 2;
		largura = 50;
		altura = 100;
		vida = 150;
		poder = 25;
		larguraAtaque = 50;
		alturaAtaque = 20;
		cooldown = Timer(4*60);
	}
	
	
}

void Player::atacar(Player& p2){
	
	if(classe == guerreiro || classe == barbaro){
		if(!cooldown.estaAtivo()){
			if(sentido == 1){
				al_draw_filled_rectangle(x, y-alturaAtaque/2, x+largura/2+larguraAtaque, y+alturaAtaque/2, al_map_rgb(255, 0, 0));
				double x1 = x;
				double y1 = y-alturaAtaque/2;
				double w1 = largura/2+larguraAtaque;
				double h1 = alturaAtaque;
				double x2 = p2.getX()-p2.getLargura()/2;
				double y2 = p2.getY()-p2.getAltura()/2;
				double w2 = p2.getLargura();
				double h2 = p2.getAltura();
				if( verificaColisao(x1, y1, w1, h1, x2, y2, w2, h2) ){
					p2.levaDano(getPoder());
				}
			}
			else{
				al_draw_filled_rectangle(x, y-alturaAtaque/2, x-largura/2-larguraAtaque, y+alturaAtaque/2, al_map_rgb(255, 0, 0));
				double x1 = x-(largura/2+larguraAtaque);
				double y1 = y-alturaAtaque/2;
				double w1 = largura/2+larguraAtaque;
				double h1 = alturaAtaque;
				double x2 = p2.getX()-p2.getLargura()/2;
				double y2 = p2.getY()-p2.getAltura()/2;
				double w2 = p2.getLargura();
				double h2 = p2.getAltura();
				if( verificaColisao(x1, y1, w1, h1, x2, y2, w2, h2) ){
					p2.levaDano(getPoder());
				}
			}
			cooldown.start();
		}
		
		
	}
	
	if(classe == mago){	
		if(!cooldown.estaAtivo()){
			listaProjeteis.insereNoInicio(new Projetil(x, y, 20, 20, 5, sentido, 0));
			cooldown.start();
		}
	}
	
	if(classe == arqueiro){	
		if(!cooldown.estaAtivo()){
			listaProjeteis.insereNoInicio(new Projetil(x, y, 20, 20, 10, sentido, 0));
			cooldown.start();
		}
	}
	
	
}



void Player::andarDireita(int limite){
	x += vx;
	if(x > limite){
		x = limite;
	}
	sentido = 1;
}

void Player::andarEsquerda(int limite){
	x -= vx;
	if(x < limite){
		x = limite;
	}
	sentido = 0;
}

void Player::andarCima(int limite){
	y -= vy;
	if(y < limite){
		y = limite;
	}
}

void Player::andarBaixo(int limite){
	y += vy;
	if(y > limite){
		y = limite;
	}
}

void Player::desenhar(){
	switch(classe){
		case guerreiro: 
			al_draw_filled_rectangle(x-largura/2, y-altura/2, x+largura/2, y+altura/2, al_map_rgb(255, 255, 255));
			break;
		case mago: 
			al_draw_filled_rectangle(x-largura/2, y-altura/2, x+largura/2, y+altura/2, al_map_rgb(0, 255, 0));
			break;
		case barbaro:
			al_draw_filled_rectangle(x-largura/2, y-altura/2, x+largura/2, y+altura/2, al_map_rgb(255, 255, 0));
			break;
		case arqueiro:
			al_draw_filled_rectangle(x-largura/2, y-altura/2, x+largura/2, y+altura/2, al_map_rgb(0, 255, 255));
			break;
	}
}

void Player::atualizaProjeteis(Player& p2){
	for(int i = 0; i < listaProjeteis.getTam(); i++){
		listaProjeteis[i]->andar();
		double x1 = listaProjeteis[i]->getX() - listaProjeteis[i]->getLargura()/2;
		double y1 = listaProjeteis[i]->getY() - listaProjeteis[i]->getAltura()/2;
		double w1 = listaProjeteis[i]->getLargura();
		double h1 = listaProjeteis[i]->getAltura();
		double x2 = p2.getX()-p2.getLargura()/2;
		double y2 = p2.getY()-p2.getAltura()/2;
		double w2 = p2.getLargura();
		double h2 = p2.getAltura();
		if( verificaColisao(x1, y1, w1, h1, x2, y2, w2, h2) ){
			p2.levaDano(getPoder());
			listaProjeteis.remove(i);
		}
	}
}
void Player::desenhaProjeteis(){
	for(int i = 0; i < listaProjeteis.getTam(); i++){
		listaProjeteis[i]->desenhar();
	}
}

void Player::atualizaTimers(){
	cooldown.update();
}

int Player::getValorCooldown(){
	return cooldown.getContador();
}

void Player::setX(int x){
	this->x = x;
}
int Player::getX(){
	return x;
}

void Player::setY(int y){
	this->y = y;
}
int Player::getY(){
	return y;
}

void Player::setVx(int vx){
	this->vx = vx;
}
int Player::getVx(){
	return vx;
}

void Player::setVy(int vy){
	this->vy = vy;
}
int Player::getVy(){
	return vy;
}

void Player::setLargura(int largura){
	this->largura = largura;
}
int Player::getLargura(){
	return largura;
}

void Player::setAltura(int altura){
	this->altura = altura;
}
int Player::getAltura(){
	return altura;
}

void Player::setVida(int vida){
	this->vida = vida;
}

int Player::getVida(){
	return vida;
}

void Player::setPoder(int poder){
	this->poder = poder;
}

int Player::getPoder(){
	return poder;
}

bool Player::operator==(Player x){
	return true;
}

void Player::levaDano(int dano){
	vida -= dano;
	if(vida < 0){
		vida = 0;
	}
}
