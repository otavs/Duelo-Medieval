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
	this->vidaMax = 0;
}

Player::Player(int x, int y, int classe, int sentido){
	this->x = x;
	this->y = y;
	this->classe = classe;
	this->sentido = sentido;
	if(classe == guerreiro){
		vx = 5;
		vy = 4;
		largura = 50;
		altura = 80;
		vida = 50;
		vidaMax = 50;
		poder = 5;
		larguraAtaque = 40;
		alturaAtaque = 20;
		cooldown = Timer(3*60);
		timerAnimacaoAndar = Timer(39); // 10/60s para cada frame (sao 4 frames), de 0 a 3
		efeitoGema = Timer(10*60);
	}
	else if(classe == mago){
		vx = 5;
		vy = 4;
		largura = 40;
		altura = 80;
		vida = 50;
		vidaMax = 50;
		poder = 8;
		larguraAtaque = 40;
		alturaAtaque = 20;
		cooldown = Timer(3*60);
		timerAnimacaoAndar = Timer(39); 
		efeitoGema = Timer(10*60);
	}
	else if(classe == arqueiro){
		vx = 6;
		vy = 4;
		largura = 40;
		altura = 80;
		vida = 50;
		vidaMax = 50;
		poder = 3;
		larguraAtaque = 40;
		alturaAtaque = 20;
		cooldown = Timer(1*60);
		timerAnimacaoAndar = Timer(39);
		efeitoGema = Timer(10*60);
	}
	else if(classe == barbaro){
		vx = 3;
		vy = 2;
		largura = 40;
		altura = 80;
		vida = 60;
		vidaMax = 60;
		poder = 10;
		larguraAtaque = 40;
		alturaAtaque = 20;
		cooldown = Timer(4*60);
		timerAnimacaoAndar = Timer(39);
		efeitoGema = Timer(10*60);
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
			listaProjeteis.insereNoInicio(new Projetil(x, y, 20, 20, 5, sentido, magia));
			cooldown.start();
		}
	}
	
	if(classe == arqueiro){	
		if(!cooldown.estaAtivo()){
			listaProjeteis.insereNoInicio(new Projetil(x, y, 50, 20, 10, sentido, flecha));
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

void Player::desenhar(bool movimento){
	switch(classe){
		case guerreiro:
			if(sentido == 1){
				if(!movimento){
					al_draw_bitmap(img_guerreiro[0], x-largura/2-41, y-altura/2-14, 0);
					timerAnimacaoAndar.start();
				}else{
					al_draw_bitmap(img_guerreiro[timerAnimacaoAndar.getContador()/10], x-largura/2-41, y-altura/2-14, 0);
					if(!timerAnimacaoAndar.estaAtivo())
						timerAnimacaoAndar.start();
				}
			}
			else if(sentido == 0){
				if(!movimento){
					al_draw_bitmap(img_guerreiro[0], x-largura/2-47, y-altura/2-14, ALLEGRO_FLIP_HORIZONTAL);
					timerAnimacaoAndar.start();
				}else{
					al_draw_bitmap(img_guerreiro[timerAnimacaoAndar.getContador()/10], x-largura/2-47, y-altura/2-14, ALLEGRO_FLIP_HORIZONTAL);
					if(!timerAnimacaoAndar.estaAtivo())
						timerAnimacaoAndar.start();
				}
			}
			//al_draw_filled_rectangle(x-largura/2, y-altura/2, x+largura/2, y+altura/2, al_map_rgba(255, 0, 0, 0.1));
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
			if(listaProjeteis[i]->getTipo() == runaPoder){
				p2.levaDano(20);
			}
			else{
				p2.levaDano(getPoder());
			}
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
	timerAnimacaoAndar.update();
	efeitoGema.update();
	if(efeitoGema.getContador() == 1){
		poder -= 20;
	}
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

void Player::setVidaMax(int vidaMax){
	this->vidaMax = vidaMax;
}
		
int Player::getVidaMax(){
	return vidaMax;
}

Timer Player::getCooldown(){
	return cooldown;
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

void Player::pegaItem(Item item){
	listaItens.insereNoFim(item);
}

void Player::usaItem(int i){
	if(i < listaItens.getTam()){
		switch(listaItens[i].getTipo()){
			case pocao:
				vida += 20;
				if(vida > vidaMax){
					vida = vidaMax;
				}
				break;
			case runa:
				listaProjeteis.insereNoInicio(new Projetil(x, y, 60, 30, 7, sentido, runaPoder));
				break;
			case gema:
				poder += 20;
				efeitoGema.start();
				break;
		}
		listaItens.remove(i);
	}
}

Lista<Item> Player::getListaItens(){
	return listaItens;
}

ALLEGRO_BITMAP* Player::img_guerreiro[4];

void Player::inicializarImagens(){
	img_guerreiro[0] = al_load_bitmap("imagens/guerreiro_dir_1.png");
	img_guerreiro[1] = al_load_bitmap("imagens/guerreiro_dir_2.png");
	img_guerreiro[2] = al_load_bitmap("imagens/guerreiro_dir_3.png");
	img_guerreiro[3] = al_load_bitmap("imagens/guerreiro_dir_4.png");
}
