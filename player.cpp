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
		poder = 8;
		larguraAtaque = 40;
		alturaAtaque = 28;
		cooldown = Timer(1*60);
		timerAnimacaoAndar = Timer(39); // 10/60s para cada frame (sao 4 frames), de 0 a 3
		efeitoGema = Timer(10*60);
		for(int i = 0; i < 4; i++){
			imagem[i] = img_guerreiro[i];
			imagem_aura[i] = img_guerreiro_aura[i];
		}
        imagem_atacando = img_guerreiro_atacando;
        imagem_aura_atacando = img_guerreiro_atacando_aura;
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
		cooldown = Timer(2*60);
		timerAnimacaoAndar = Timer(39);
		efeitoGema = Timer(10*60);
		for(int i = 0; i < 4; i++){
			imagem[i] = img_mago[i];
			imagem_aura[i] = img_mago_aura[i];
		}
        imagem_atacando = img_mago_atacando;
        imagem_aura_atacando = img_mago_atacando_aura;
	}
	else if(classe == arqueiro){
		vx = 6;
		vy = 4;
		largura = 40;
		altura = 80;
		vida = 50;
		vidaMax = 50;
		poder = 4;
		larguraAtaque = 40;
		alturaAtaque = 20;
		cooldown = Timer(1*60);
		timerAnimacaoAndar = Timer(39);
		efeitoGema = Timer(10*60);
		for(int i = 0; i < 4; i++){
			imagem[i] = img_arqueiro[i];
			imagem_aura[i] = img_arqueiro_aura[i];
		}
        imagem_atacando = img_arqueiro_atacando;
        imagem_aura_atacando = img_arqueiro_atacando_aura;
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
		alturaAtaque = 28;
		cooldown = Timer(3*60);
		timerAnimacaoAndar = Timer(39);
		efeitoGema = Timer(10*60);
		for(int i = 0; i < 4; i++){
			imagem[i] = img_barbaro[i];
			imagem_aura[i] = img_barbaro_aura[i];
		}
        imagem_atacando = img_barbaro_atacando;
        imagem_aura_atacando = img_barbaro_atacando_aura;
	}
	else if(classe == caracolaladofaminto){
		vx = 5;
		vy = 4;
		largura = 62;
		altura = 60;
		vida = 60;
		vidaMax = 60;
		poder = 10;
		larguraAtaque = 40;
		alturaAtaque = 20;
		cooldown = Timer(40);
		timerAnimacaoAndar = Timer(19);
		efeitoGema = Timer(10*60);
		for(int i = 0; i < 2; i++){
			imagem[i] = img_caracolaladofaminto[i];
			imagem_aura[i] = img_caracolaladofaminto_aura[i];
		}
	}
	else if(classe == onigiri){
		vx = 3;
		vy = 2;
		largura = 40;
		altura = 32;
		vida = 60;
		vidaMax = 60;
		poder = 4;
		larguraAtaque = 40;
		alturaAtaque = 20;
		cooldown = Timer(15);
		timerAnimacaoAndar = Timer(1);
		efeitoGema = Timer(10*60);
		imagem[0] = img_onigiri;
		imagem_aura[0] = img_onigiri_aura;
	}

}

void Player::atacar(Player& p2){

	if(classe == guerreiro || classe == barbaro){
		if(!cooldown.estaAtivo()){
			if(sentido == 1){
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
				// al_draw_filled_rectangle(x, y-alturaAtaque/2, x-largura/2-larguraAtaque, y+alturaAtaque/2, al_map_rgb(255, 0, 0));
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
			listaProjeteis.insereNoInicio(new Projetil(x, y, 50, 15, 10, sentido, flecha));
			cooldown.start();
		}
	}
	
	if(classe == caracolaladofaminto){
		if(!cooldown.estaAtivo()){
			listaProjeteis.insereNoInicio(new Projetil(x, y, 40, 10, 10, sentido, laser));
			cooldown.start();
		}
	}
	
	if(classe == onigiri){
		if(!cooldown.estaAtivo()){
			listaProjeteis.insereNoInicio(new Projetil(x, y, 45, 10, 10, sentido, laser));
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
	if(classe != caracolaladofaminto && classe != onigiri){
		if(sentido == 1){
	        if(cooldown.estaAtivo() && ((cooldown.getContador() < cooldown.getMaximo()) && (cooldown.getContador() > cooldown.getMaximo() - 10))){
	            if(efeitoGema.estaAtivo())
	                al_draw_bitmap(imagem_aura_atacando, x-largura/2-41, y-altura/2-14, 0);
	            else
					al_draw_bitmap(imagem_atacando, x-largura/2-41, y-altura/2-14, 0);
	        }
	        else{
	            if(!movimento){
	                if(efeitoGema.estaAtivo()){
	                    al_draw_bitmap(imagem_aura[0], x-largura/2-41, y-altura/2-14, 0);
	                    timerAnimacaoAndar.start();
	                }
	                else{
	                    al_draw_bitmap(imagem[0], x-largura/2-41, y-altura/2-14, 0);
	                    timerAnimacaoAndar.start();
	                }
	            }else{
	                if(efeitoGema.estaAtivo()){
	                    al_draw_bitmap(imagem_aura[timerAnimacaoAndar.getContador()/10], x-largura/2-41, y-altura/2-14, 0);
	                    if(!timerAnimacaoAndar.estaAtivo())
	                        timerAnimacaoAndar.start();
	                }
	                else{
	                    al_draw_bitmap(imagem[timerAnimacaoAndar.getContador()/10], x-largura/2-41, y-altura/2-14, 0);
	                    if(!timerAnimacaoAndar.estaAtivo())
	                        timerAnimacaoAndar.start();
	                }
	            }
	        }
		}
		else if(sentido == 0){
	        if(cooldown.estaAtivo() && ((cooldown.getContador() < cooldown.getMaximo()) && (cooldown.getContador() > cooldown.getMaximo() - 10))){
	            if(efeitoGema.estaAtivo())
	                al_draw_bitmap(imagem_aura_atacando, x-largura/2-47, y-altura/2-14, ALLEGRO_FLIP_HORIZONTAL);
	            else
					al_draw_bitmap(imagem_atacando, x-largura/2-47, y-altura/2-14, ALLEGRO_FLIP_HORIZONTAL);
	                
	        }
	        else{
	            if(!movimento){
	                if(efeitoGema.estaAtivo()){
	                    al_draw_bitmap(imagem_aura[0], x-largura/2-47, y-altura/2-14, ALLEGRO_FLIP_HORIZONTAL);
	                    timerAnimacaoAndar.start();
	                }
	                else{
	                    al_draw_bitmap(imagem[0], x-largura/2-47, y-altura/2-14, ALLEGRO_FLIP_HORIZONTAL);
	                    timerAnimacaoAndar.start();
	                }
	            }else{
	                if(efeitoGema.estaAtivo()){
	                    al_draw_bitmap(imagem_aura[timerAnimacaoAndar.getContador()/10], x-largura/2-47, y-altura/2-14, ALLEGRO_FLIP_HORIZONTAL);
	                    if(!timerAnimacaoAndar.estaAtivo())
	                        timerAnimacaoAndar.start();
	                }
	                else{
	                    al_draw_bitmap(imagem[timerAnimacaoAndar.getContador()/10], x-largura/2-47, y-altura/2-14, ALLEGRO_FLIP_HORIZONTAL);
	                    if(!timerAnimacaoAndar.estaAtivo())
	                        timerAnimacaoAndar.start();
	                }
	            }
	        }
		}
	}
	
	else if(classe == caracolaladofaminto){
		if(sentido == 1){
            if(efeitoGema.estaAtivo()){
                al_draw_bitmap(imagem_aura[timerAnimacaoAndar.getContador()/10], x-largura/2-14, y-altura/2-32, 0);
                if(!timerAnimacaoAndar.estaAtivo())
                    timerAnimacaoAndar.start();
            }
            else{
                al_draw_bitmap(imagem[timerAnimacaoAndar.getContador()/10], x-largura/2-14, y-altura/2-32, 0);
                if(!timerAnimacaoAndar.estaAtivo())
                    timerAnimacaoAndar.start();
            }
		}
		else if(sentido == 0){
            if(efeitoGema.estaAtivo()){
                al_draw_bitmap(imagem_aura[timerAnimacaoAndar.getContador()/10], x-largura/2-14, y-altura/2-32, ALLEGRO_FLIP_HORIZONTAL);
                if(!timerAnimacaoAndar.estaAtivo())
                    timerAnimacaoAndar.start();
            }
            else{
                al_draw_bitmap(imagem[timerAnimacaoAndar.getContador()/10], x-largura/2-14, y-altura/2-32, ALLEGRO_FLIP_HORIZONTAL);
                if(!timerAnimacaoAndar.estaAtivo())
                    timerAnimacaoAndar.start();
            }
		}
	}
	
	else if(classe == onigiri){
		if(sentido == 1){
            if(efeitoGema.estaAtivo()){
                al_draw_bitmap(imagem_aura[timerAnimacaoAndar.getContador()/10], x-largura/2, y-altura/2, ALLEGRO_FLIP_HORIZONTAL);
                if(!timerAnimacaoAndar.estaAtivo())
                    timerAnimacaoAndar.start();
            }
            else{
                al_draw_bitmap(imagem[timerAnimacaoAndar.getContador()/10], x-largura/2, y-altura/2, ALLEGRO_FLIP_HORIZONTAL);
                if(!timerAnimacaoAndar.estaAtivo())
                    timerAnimacaoAndar.start();
            }
		}
		else if(sentido == 0){
            if(efeitoGema.estaAtivo()){
                al_draw_bitmap(imagem_aura[timerAnimacaoAndar.getContador()/10], x-largura/2, y-altura/2, 0);
                if(!timerAnimacaoAndar.estaAtivo())
                    timerAnimacaoAndar.start();
            }
            else{
                al_draw_bitmap(imagem[timerAnimacaoAndar.getContador()/10], x-largura/2, y-altura/2, 0);
                if(!timerAnimacaoAndar.estaAtivo())
                    timerAnimacaoAndar.start();
            }
		}
	}
	
	
	//al_draw_filled_rectangle(x-largura/2, y-altura/2, x+largura/2, y+altura/2, al_map_rgba(255, 0, 0, 0.1));

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
				p2.levaDano(15);
			}
			else{
				p2.levaDano(getPoder());
			}
			listaProjeteis.remove(i);
			i--;
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
		poder -= 10;
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
				poder += 10;
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
ALLEGRO_BITMAP* Player::img_arqueiro[4];
ALLEGRO_BITMAP* Player::img_mago[4];
ALLEGRO_BITMAP* Player::img_barbaro[4];
ALLEGRO_BITMAP* Player::img_caracolaladofaminto[2];
ALLEGRO_BITMAP* Player::img_onigiri;

ALLEGRO_BITMAP* Player::img_guerreiro_aura[4];
ALLEGRO_BITMAP* Player::img_arqueiro_aura[4];
ALLEGRO_BITMAP* Player::img_mago_aura[4];
ALLEGRO_BITMAP* Player::img_barbaro_aura[4];
ALLEGRO_BITMAP* Player::img_caracolaladofaminto_aura[2];
ALLEGRO_BITMAP* Player::img_onigiri_aura;

ALLEGRO_BITMAP* Player::img_guerreiro_atacando;
ALLEGRO_BITMAP* Player::img_mago_atacando;
ALLEGRO_BITMAP* Player::img_arqueiro_atacando;
ALLEGRO_BITMAP* Player::img_barbaro_atacando;

ALLEGRO_BITMAP* Player::img_guerreiro_atacando_aura;
ALLEGRO_BITMAP* Player::img_mago_atacando_aura;
ALLEGRO_BITMAP* Player::img_arqueiro_atacando_aura;
ALLEGRO_BITMAP* Player::img_barbaro_atacando_aura;

void Player::inicializarImagens(){
	img_guerreiro[0] = al_load_bitmap("imagens/guerreiro_1.png");
	img_guerreiro[1] = al_load_bitmap("imagens/guerreiro_2.png");
	img_guerreiro[2] = al_load_bitmap("imagens/guerreiro_3.png");
	img_guerreiro[3] = al_load_bitmap("imagens/guerreiro_4.png");

	img_arqueiro[0] = al_load_bitmap("imagens/arqueiro_1.png");
	img_arqueiro[1] = al_load_bitmap("imagens/arqueiro_2.png");
	img_arqueiro[2] = al_load_bitmap("imagens/arqueiro_3.png");
	img_arqueiro[3] = al_load_bitmap("imagens/arqueiro_4.png");

	img_mago[0] = al_load_bitmap("imagens/mago_1.png");
	img_mago[1] = al_load_bitmap("imagens/mago_2.png");
	img_mago[2] = al_load_bitmap("imagens/mago_3.png");
	img_mago[3] = al_load_bitmap("imagens/mago_4.png");

	img_barbaro[0] = al_load_bitmap("imagens/barbaro_1.png");
	img_barbaro[1] = al_load_bitmap("imagens/barbaro_2.png");
	img_barbaro[2] = al_load_bitmap("imagens/barbaro_3.png");
	img_barbaro[3] = al_load_bitmap("imagens/barbaro_4.png");

    img_guerreiro_aura[0] = al_load_bitmap("imagens/guerreiro_aura_1.png");
	img_guerreiro_aura[1] = al_load_bitmap("imagens/guerreiro_aura_2.png");
	img_guerreiro_aura[2] = al_load_bitmap("imagens/guerreiro_aura_3.png");
	img_guerreiro_aura[3] = al_load_bitmap("imagens/guerreiro_aura_4.png");

	img_arqueiro_aura[0] = al_load_bitmap("imagens/arqueiro_aura_1.png");
	img_arqueiro_aura[1] = al_load_bitmap("imagens/arqueiro_aura_2.png");
	img_arqueiro_aura[2] = al_load_bitmap("imagens/arqueiro_aura_3.png");
	img_arqueiro_aura[3] = al_load_bitmap("imagens/arqueiro_aura_4.png");

	img_mago_aura[0] = al_load_bitmap("imagens/mago_aura_1.png");
	img_mago_aura[1] = al_load_bitmap("imagens/mago_aura_2.png");
	img_mago_aura[2] = al_load_bitmap("imagens/mago_aura_3.png");
	img_mago_aura[3] = al_load_bitmap("imagens/mago_aura_4.png");

	img_barbaro_aura[0] = al_load_bitmap("imagens/barbaro_aura_1.png");
	img_barbaro_aura[1] = al_load_bitmap("imagens/barbaro_aura_2.png");
	img_barbaro_aura[2] = al_load_bitmap("imagens/barbaro_aura_3.png");
	img_barbaro_aura[3] = al_load_bitmap("imagens/barbaro_aura_4.png");

	img_guerreiro_atacando = al_load_bitmap("imagens/guerreiro_atacando.png");
	img_mago_atacando = al_load_bitmap("imagens/mago_atacando.png");
	img_arqueiro_atacando = al_load_bitmap("imagens/arqueiro_atacando.png");
	img_barbaro_atacando = al_load_bitmap("imagens/barbaro_atacando.png");

    img_guerreiro_atacando_aura = al_load_bitmap("imagens/guerreiro_aura_atacando.png");
	img_mago_atacando_aura = al_load_bitmap("imagens/mago_aura_atacando.png");
	img_arqueiro_atacando_aura = al_load_bitmap("imagens/arqueiro_aura_atacando.png");
	img_barbaro_atacando_aura = al_load_bitmap("imagens/barbaro_aura_atacando.png");
	
	img_caracolaladofaminto[0] = al_load_bitmap("imagens/caracolaladofaminto_1.png");
	img_caracolaladofaminto[1] = al_load_bitmap("imagens/caracolaladofaminto_2.png");
	img_onigiri = al_load_bitmap("imagens/onigiri.png");
	
	img_caracolaladofaminto_aura[0] = al_load_bitmap("imagens/caracolaladofaminto_aura_1.png");
	img_caracolaladofaminto_aura[1] = al_load_bitmap("imagens/caracolaladofaminto_aura_2.png");
	img_onigiri_aura = al_load_bitmap("imagens/onigiri_aura.png");
	
}

void Player::desenharImagem(int seletor,int x, int y){
    if(seletor == 0){
        al_draw_bitmap(img_guerreiro[0], x, y, 0);
    }
    else if(seletor == 1){
        al_draw_bitmap(img_mago[0], x, y, 0);
    }else if(seletor == 2){
        al_draw_bitmap(img_arqueiro[0], x, y, 0);
    }else if(seletor == 3){
        al_draw_bitmap(img_barbaro[0], x, y, 0);
    }
}
