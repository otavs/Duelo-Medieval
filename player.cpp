#include "includes.h"

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

Player::Player(int x, int y, int vx, int vy, int largura, int altura, int vida, int poder, int sentido,
int larguraAtaque, int alturaAtaque, int classe){
	this->x = x;
	this->y = y;
	this->vx= vx;
	this->vy = vy;
	this->largura = largura;
	this->altura = altura;
	this->vida = vida;
	this->poder = poder;
	this->sentido = sentido;
	this->larguraAtaque = larguraAtaque;
	this->alturaAtaque = alturaAtaque;
	this->classe = classe;
}

void Player::atacar(Player& p2){
	
	if(classe == guerreiro){
		
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
	}
	
	
	if(classe == mago){	
		listaProjeteis.insereNoInicio(new Projetil(x, y, 20, 20, 5, sentido, 0));
		
	}
	
}



void Player::andarDireita(){
	x += vx;
	sentido = 1;
}

void Player::andarEsquerda(){
	x -= vx;
	sentido = 0;
}

void Player::andarCima(){
	y -= vy;
}

void Player::andarBaixo(){
	y += vy;
}

void Player::desenhar(){
	switch(classe){
		case guerreiro: 
			al_draw_filled_rectangle(x-largura/2, y-altura/2, x+largura/2, y+altura/2, al_map_rgb(255, 255, 255));
			break;
		case mago: 
			al_draw_filled_rectangle(x-largura/2, y-altura/2, x+largura/2, y+altura/2, al_map_rgb(0, 255, 0));
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
