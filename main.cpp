#include "includes.h"

#include "lista.h"
#include "projetil.h"
#include "player.h"
#include "item.h"
#include "timer.h"
#include "barra.h"
#include "botao.h"

int main(){	
	
	int largura = 960;
	int altura = 540;
	int fps = 60;
	bool acabou = false;
	int mouseX = 0, mouseY = 0;
	int estado = menu;
	int seletorP1 = 0, seletorP2 = 0, seletorCenario = 0;
	bool estaSelecionadoP1 = false, estaSelecionadoP2 = false, estaSelecionadoCenario = false;
	ALLEGRO_BITMAP *cenario = NULL;
	ALLEGRO_BITMAP *cenario1 = NULL;
	ALLEGRO_BITMAP *cenario2 = NULL;
	ALLEGRO_BITMAP *cenario3 = NULL;
	ALLEGRO_BITMAP *cenario4 = NULL;
	ALLEGRO_BITMAP *cenario5 = NULL;
	
	bool tecla[N_TECLAS];
	for(int i = 0; i < N_TECLAS; i++) tecla[i] = false;
	
	Lista<Item> listaItens;
	
	ALLEGRO_DISPLAY *tela = NULL;
	ALLEGRO_EVENT_QUEUE *filaEventos = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_FONT *arial24 = NULL;
	
	srand(time(NULL));
	
	al_init();
    al_install_keyboard();
    al_install_mouse();
	al_install_audio();
	
	al_init_image_addon();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_acodec_addon();
	
	al_reserve_samples(15);
	
	al_set_new_display_flags(ALLEGRO_RESIZABLE);
	tela = al_create_display(largura, altura);
	timer = al_create_timer(1.0 / fps);
	filaEventos = al_create_event_queue();
	arial24 = al_load_font("fontes/arial.ttf", 24, 0);
	
	al_register_event_source(filaEventos, al_get_display_event_source(tela));
	al_register_event_source(filaEventos, al_get_keyboard_event_source());
	al_register_event_source(filaEventos, al_get_timer_event_source(timer));
	al_register_event_source(filaEventos, al_get_mouse_event_source());
	
	Player player1;
	Player player2;
	
	Botao botaoJogar(largura/2, 180, "imagens/botao_jogar.png");
	Botao botaoInstrucoes(largura/2, 300, "imagens/botao_instrucoes.png");
	Botao botaoSair(largura/2, 420, "imagens/botao_sair.png");
	Botao botaoMenu(largura/2, 420, "imagens/botao_menu.png");
	
	Barra barraVidaP1;
	Barra barraVidaP2;
	Barra barraCooldownP1;
	Barra barraCooldownP2;
		
	Player::inicializarImagens();
	
	cenario1 = al_load_bitmap("imagens/cenario1.png");
	cenario2 = al_load_bitmap("imagens/cenario2.png");
	cenario3 = al_load_bitmap("imagens/cenario3.png");
	cenario4 = al_load_bitmap("imagens/cenario4.png");
	cenario5 = al_load_bitmap("imagens/cenario5.png");
	
	Timer timerItens(aleatorio(2*60, 3*60));
	timerItens.start();
	
	//al_hide_mouse_cursor(tela);
	
	al_start_timer(timer);
	
	while(!acabou){
		
		ALLEGRO_EVENT evento;
		al_wait_for_event(filaEventos, &evento);
		
		if(estado == menu){
			if(evento.type == ALLEGRO_EVENT_TIMER){
                al_set_window_title(tela, "Nome");
                botaoJogar.atualiza(mouseX, mouseY);
                botaoInstrucoes.atualiza(mouseX, mouseY);
				botaoSair.atualiza(mouseX, mouseY);
				al_clear_to_color(al_map_rgb(10, 0, 0));
				botaoJogar.desenhar();
				botaoInstrucoes.desenhar();
				botaoSair.desenhar();
				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));
			}
			else if(evento.type == ALLEGRO_EVENT_MOUSE_AXES){
				mouseX = evento.mouse.x;
				mouseY = evento.mouse.y;
			}
			else if(evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
				if(evento.mouse.button == 1){
					if(botaoJogar.estaSelecionado()){
						estado = escolhaClasse;
					}
					if(botaoInstrucoes.estaSelecionado()){
						estado = instrucoes;
					}
					if(botaoSair.estaSelecionado()){
						acabou = true;
					}	
				}
			}
			/*else if(evento.type == ALLEGRO_EVENT_DISPLAY_RESIZE){
				al_resize_display(tela, evento.display.width, evento.display.height);	
				sx = al_get_display_width(tela) / (float)largura;
				sy = al_get_display_height(tela) / (float)altura;
				ALLEGRO_TRANSFORM trans;
				al_identity_transform(&trans);
				al_scale_transform(&trans, sx, sy);
				al_use_transform(&trans);
			}*/
			else if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
				acabou = true;
			}
		}
		else if(estado == escolhaClasse){
			if(evento.type == ALLEGRO_EVENT_TIMER){
                al_set_window_title(tela, "Nome");
                al_clear_to_color(al_map_rgb(0, 0, 0));
                
				if(estaSelecionadoP2 && estaSelecionadoP1){
					
					player1 = Player(100, 400, seletorP1, 1);
					player2 = Player(700, 400, seletorP2, 0);
					
					barraVidaP1 = Barra(50, 30, 200, 30, player1.getVidaMax(), al_map_rgb(0, 255, 0));
					barraVidaP2 = Barra(650, 30, 200, 30, player2.getVidaMax(), al_map_rgb(0, 255, 0));
					barraCooldownP1 = Barra(50, 80, 200, 30, player1.getCooldown().getMaximo(), al_map_rgb(255, 200, 0));
					barraCooldownP2 = Barra(650, 80, 200, 30, player2.getCooldown().getMaximo(), al_map_rgb(255, 200, 0));
					
					estado = escolhaCenario;
					
					estaSelecionadoP1 = false;
					estaSelecionadoP2 = false;
				}
				
					
				if(seletorP1 == 0)
					al_draw_rectangle(200, 200, 200+80, 340, al_map_rgb(255, 0, 0), 5);
				else if(seletorP1 == 1)
					al_draw_rectangle(200+80, 200, 200+80+80, 340, al_map_rgb(255, 0, 0), 5);
				else if(seletorP1 == 2)
					al_draw_rectangle(200+80+80, 200, 200+80+80+80, 340, al_map_rgb(255, 0, 0), 5);
				else if(seletorP1 == 3)
					al_draw_rectangle(200+80+80+80, 200, 200+80+80+80+80, 340, al_map_rgb(255, 0, 0), 5);
				
				if(seletorP2 == 0)
					al_draw_rectangle(200, 200, 200+80, 340, al_map_rgb(0, 0, 255), 5);
				else if(seletorP2 == 1)
					al_draw_rectangle(200+80, 200, 200+80+80, 340, al_map_rgb(0, 0, 255), 5);
				else if(seletorP2 == 2)
					al_draw_rectangle(200+80+80, 200, 200+80+80+80, 340, al_map_rgb(0, 0, 255), 5);
				else if(seletorP2 == 3)
					al_draw_rectangle(200+80+80+80, 200, 200+80+80+80+80, 340, al_map_rgb(0, 0, 255), 5);
				
				
				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));
			}
			else if(evento.type == ALLEGRO_EVENT_MOUSE_AXES){
				mouseX = evento.mouse.x;
				mouseY = evento.mouse.y;
			}
			else if(evento.type == ALLEGRO_EVENT_KEY_DOWN){
				switch(evento.keyboard.keycode){
					case ALLEGRO_KEY_RIGHT:
						seletorP2++;
						if(seletorP2 > 3)
							seletorP2 = 3;
						break;
					case ALLEGRO_KEY_LEFT:
						seletorP2--;
						if(seletorP2 < 0)
							seletorP2 = 0;
						break;
					case ALLEGRO_KEY_H:
						seletorP1++;
						if(seletorP1 > 3)
							seletorP1 = 3;
						break;
					case ALLEGRO_KEY_F:
						seletorP1--;
						if(seletorP1 < 0)
							seletorP1 = 0;
						break;
					case ALLEGRO_KEY_I:
						estaSelecionadoP2 = true;
						break;
					case ALLEGRO_KEY_Q:
						estaSelecionadoP1 = true;
						break;
				}
			}
			/*else if(evento.type == ALLEGRO_EVENT_DISPLAY_RESIZE){
				al_resize_display(tela, evento.display.width, evento.display.height);	
				sx = al_get_display_width(tela) / (float)largura;
				sy = al_get_display_height(tela) / (float)altura;
				ALLEGRO_TRANSFORM trans;
				al_identity_transform(&trans);
				al_scale_transform(&trans, sx, sy);
				al_use_transform(&trans);
			}*/
			else if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
				acabou = true;
			}
		}
		else if(estado == instrucoes){
			if(evento.type == ALLEGRO_EVENT_TIMER){
                al_set_window_title(tela, "Nome");
                botaoMenu.atualiza(mouseX, mouseY);
                al_clear_to_color(al_map_rgb(0, 0, 0));
				botaoMenu.desenhar();
				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));
			}
			else if(evento.type == ALLEGRO_EVENT_MOUSE_AXES){
				mouseX = evento.mouse.x;
				mouseY = evento.mouse.y;
			}
			else if(evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
				if(evento.mouse.button == 1){
					if(botaoMenu.estaSelecionado()){
						estado = menu;
					}				
				}
			}
			
			/*else if(evento.type == ALLEGRO_EVENT_DISPLAY_RESIZE){
				al_resize_display(tela, evento.display.width, evento.display.height);	
				sx = al_get_display_width(tela) / (float)largura;
				sy = al_get_display_height(tela) / (float)altura;
				ALLEGRO_TRANSFORM trans;
				al_identity_transform(&trans);
				al_scale_transform(&trans, sx, sy);
				al_use_transform(&trans);
			}*/
			else if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
				acabou = true;
			}
		}
		else if(estado == escolhaCenario){
			if(evento.type == ALLEGRO_EVENT_TIMER){
                al_set_window_title(tela, "Nome");
                al_clear_to_color(al_map_rgb(0, 0, 0));
                
				if(estaSelecionadoCenario){
					if(seletorCenario == 0)
						cenario = cenario1;
					else if(seletorCenario == 1)
						cenario = cenario2;
					else if(seletorCenario == 2)
						cenario = cenario3;
					else if(seletorCenario == 3)
						cenario = cenario4;
					estado = jogando;
					estaSelecionadoCenario = false;
				}
					
				if(seletorCenario == 0)
					al_draw_rectangle(200, 200, 200+80, 340, al_map_rgb(255, 0, 0), 5);
				else if(seletorCenario == 1)
					al_draw_rectangle(200+80, 200, 200+80+80, 340, al_map_rgb(255, 0, 0), 5);
				else if(seletorCenario == 2)
					al_draw_rectangle(200+80+80, 200, 200+80+80+80, 340, al_map_rgb(255, 0, 0), 5);
				else if(seletorCenario == 3)
					al_draw_rectangle(200+80+80+80, 200, 200+80+80+80+80, 340, al_map_rgb(255, 0, 0), 5);
				
				
				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));
			}
			else if(evento.type == ALLEGRO_EVENT_MOUSE_AXES){
				mouseX = evento.mouse.x;
				mouseY = evento.mouse.y;
			}
		
			else if(evento.type == ALLEGRO_EVENT_KEY_DOWN){
				switch(evento.keyboard.keycode){
					case ALLEGRO_KEY_RIGHT:
						seletorCenario++;
						if(seletorCenario > 3)
							seletorCenario = 3;
						break;
					case ALLEGRO_KEY_LEFT:
						seletorCenario--;
						if(seletorCenario < 0)
							seletorCenario = 0;
						break;
					case ALLEGRO_KEY_H:
						seletorCenario++;
						if(seletorCenario > 3)
							seletorCenario = 3;
						break;
					case ALLEGRO_KEY_F:
						seletorCenario--;
						if(seletorCenario < 0)
							seletorCenario = 0;
						break;
					case ALLEGRO_KEY_I:
						estaSelecionadoCenario = true;
						break;
					case ALLEGRO_KEY_Q:
						estaSelecionadoCenario = true;
						break;
				}
			}
			/*else if(evento.type == ALLEGRO_EVENT_DISPLAY_RESIZE){
				al_resize_display(tela, evento.display.width, evento.display.height);	
				sx = al_get_display_width(tela) / (float)largura;
				sy = al_get_display_height(tela) / (float)altura;
				ALLEGRO_TRANSFORM trans;
				al_identity_transform(&trans);
				al_scale_transform(&trans, sx, sy);
				al_use_transform(&trans);
			}*/
			else if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
				acabou = true;
			}
		}
		else if(estado == jogando){		
			if(evento.type == ALLEGRO_EVENT_TIMER){
				
				if(tecla[UP]){
					player2.andarCima(altura/2);
				}
				if(tecla[DOWN]){
					player2.andarBaixo(altura);
				}
				if(tecla[LEFT]){
					player2.andarEsquerda(0);
				}
				if(tecla[RIGHT]){
					player2.andarDireita(largura);
				}
				if(tecla[T]){
					player1.andarCima(altura/2);
				}
				if(tecla[G]){
					player1.andarBaixo(altura);
				}
				if(tecla[F]){
					player1.andarEsquerda(0);
				}
				if(tecla[H]){
					player1.andarDireita(largura);
				}

				player1.atualizaProjeteis(player2);
				player2.atualizaProjeteis(player1);
				timerItens.update();
				player1.atualizaTimers();
				player2.atualizaTimers();
				
				if(player1.getVida() == 0 || player2.getVida() == 0){
					estado = gameOver;
					for(int i = 0; i < N_TECLAS; i++) tecla[i] = false;
				}
				for(int i = 0; i < listaItens.getTam(); i++){
					if(verificaColisao(listaItens[i].getX()-listaItens[i].getLargura()/2, listaItens[i].getY() - listaItens[i].getAltura()/2, listaItens[i].getLargura(), listaItens[i].getAltura(),
					player1.getX()-player1.getLargura()/2, player1.getY()-player1.getAltura()/2, player1.getLargura(), player1.getAltura())){
						if(player1.getListaItens().getTam() < 3){
							player1.pegaItem(listaItens[i]);
							listaItens.remove(i);
						}
					}
				}
				for(int i = 0; i < listaItens.getTam(); i++){
					if(verificaColisao(listaItens[i].getX()-listaItens[i].getLargura()/2, listaItens[i].getY() - listaItens[i].getAltura()/2, listaItens[i].getLargura(), listaItens[i].getAltura(),
					player2.getX()-player2.getLargura()/2, player2.getY()-player2.getAltura()/2, player2.getLargura(), player2.getAltura())){
						if(player2.getListaItens().getTam() < 3){
							player2.pegaItem(listaItens[i]);
							listaItens.remove(i);
						}
					}
				}
				
				if(!timerItens.estaAtivo()){
					listaItens.insereNoFim(Item(aleatorio(0, largura), aleatorio(altura/2, altura), aleatorio(0, 2)));
					timerItens.setMaximo(aleatorio(10*60, 20*60));
					timerItens.start();
				}
				// Renderizacao:
				al_draw_bitmap(cenario, 0, 0, 0);
				
				for(int i = 0; i < listaItens.getTam(); i++){
					listaItens[i].desenhar();
				}
				if(player1.getY() < player2.getY()){
					player2.desenhar(tecla[UP] || tecla[DOWN] || tecla[LEFT] || tecla[RIGHT]);
					player1.desenhar(tecla[T] || tecla[G] || tecla[F] || tecla[H]);
				}else{
					player2.desenhar(tecla[UP] || tecla[DOWN] || tecla[LEFT] || tecla[RIGHT]);
					player1.desenhar(tecla[T] || tecla[G] || tecla[F] || tecla[H]);	
				}
				player1.desenhaProjeteis();
				player2.desenhaProjeteis();
				
				barraVidaP1.desenhar(player1.getVida());
				barraVidaP2.desenhar(player2.getVida());
				
				if(player1.getCooldown().getContador() == 0)
					barraCooldownP1.desenhar(player1.getCooldown().getMaximo());
				else
					barraCooldownP1.desenhar(player1.getCooldown().getContador());
					
				if(player2.getCooldown().getContador() == 0)
					barraCooldownP2.desenhar(player2.getCooldown().getMaximo());
				else
					barraCooldownP2.desenhar(player2.getCooldown().getContador());
				
				al_draw_text(arial24, al_map_rgb(255, 255, 255), 100, 150, 0, "Itens:");
				int x = 170;
				for(int i = 0; i < player1.getListaItens().getTam(); i++){
					if(player1.getListaItens()[i].getTipo() == pocao)
						al_draw_filled_rectangle(x, 150, x+20, 150+20, al_map_rgb(255, 0, 0));
					else if(player1.getListaItens()[i].getTipo() == runa)
						al_draw_filled_rectangle(x, 150, x+20, 150+20, al_map_rgb(0, 255, 0));
					else if(player1.getListaItens()[i].getTipo() == gema)
						al_draw_filled_rectangle(x, 150, x+20, 150+20, al_map_rgb(0, 0, 255));
					x += 35;
				}
				
				al_draw_text(arial24, al_map_rgb(255, 255, 255), 700, 150, 0, "Itens:");
				x = 770;
				for(int i = 0; i < player2.getListaItens().getTam(); i++){
					if(player2.getListaItens()[i].getTipo() == pocao)
						al_draw_filled_rectangle(x, 150, x+20, 150+20, al_map_rgb(255, 0, 0));
					else if(player2.getListaItens()[i].getTipo() == runa)
						al_draw_filled_rectangle(x, 150, x+20, 150+20, al_map_rgb(0, 255, 0));
					else if(player2.getListaItens()[i].getTipo() == gema)
						al_draw_filled_rectangle(x, 150, x+20, 150+20, al_map_rgb(0, 0, 255));
					x += 35;
				}
				
				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));
			}
			else if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
				acabou = true;
			}
			else if(evento.type == ALLEGRO_EVENT_KEY_DOWN){
				switch(evento.keyboard.keycode){
					case ALLEGRO_KEY_UP:
						tecla[UP] = true;
						break;
					case ALLEGRO_KEY_DOWN:
						tecla[DOWN] = true;
						break;
					case ALLEGRO_KEY_LEFT:
						tecla[LEFT] = true;
						break;
					case ALLEGRO_KEY_RIGHT:
						tecla[RIGHT] = true;
						break;
					case ALLEGRO_KEY_T:
						tecla[T] = true;
						break;
					case ALLEGRO_KEY_F:
						tecla[F] = true;
						break;
					case ALLEGRO_KEY_G:
						tecla[G] = true;
						break;
					case ALLEGRO_KEY_H:
						tecla[H] = true;
						break;
					case ALLEGRO_KEY_I:
						tecla[I] = true;
						player2.atacar(player1);
						break;
					case ALLEGRO_KEY_Q:
						tecla[Q] = true;
						player1.atacar(player2);
						break;
					case ALLEGRO_KEY_ESCAPE:
						tecla[ESC] = true;
						acabou = true;
						break;
					case ALLEGRO_KEY_1:
						tecla[K1] = true;
						player1.usaItem(0);
						break;
					case ALLEGRO_KEY_2:
						tecla[K2] = true;
						player1.usaItem(1);
						break;
					case ALLEGRO_KEY_3:
						tecla[K3] = true;
						player1.usaItem(2);
						break;
					case ALLEGRO_KEY_8:
						tecla[K8] = true;
						player2.usaItem(0);
						break;
					case ALLEGRO_KEY_9:
						tecla[K9] = true;
						player2.usaItem(1);
						break;
					case ALLEGRO_KEY_0:
						tecla[K0] = true;
						player2.usaItem(2);
						break;
				}
			}
			else if(evento.type == ALLEGRO_EVENT_KEY_UP){
				switch(evento.keyboard.keycode){
					case ALLEGRO_KEY_UP:
						tecla[UP] = false;
						break;
					case ALLEGRO_KEY_DOWN:
						tecla[DOWN] = false;
						break;
					case ALLEGRO_KEY_LEFT:
						tecla[LEFT] = false;
						break;
					case ALLEGRO_KEY_RIGHT:
						tecla[RIGHT] = false;
						break;
					case ALLEGRO_KEY_T:
						tecla[T] = false;
						break;
					case ALLEGRO_KEY_F:
						tecla[F] = false;
						break;
					case ALLEGRO_KEY_G:
						tecla[G] = false;
						break;
					case ALLEGRO_KEY_H:
						tecla[H] = false;
						break;
					case ALLEGRO_KEY_I:
						tecla[I] = false;
						break;
					case ALLEGRO_KEY_Q:
						tecla[Q] = false;
						break;
					case ALLEGRO_KEY_ESCAPE:
						tecla[ESC] = false;
						break;
					case ALLEGRO_KEY_1:
						tecla[K1] = false;
						break;
					case ALLEGRO_KEY_2:
						tecla[K2] = false;
						break;
					case ALLEGRO_KEY_3:
						tecla[K3] = false;
						break;
					case ALLEGRO_KEY_8:
						tecla[K8] = false;
						break;
					case ALLEGRO_KEY_9:
						tecla[K9] = false;
						break;
					case ALLEGRO_KEY_0:
						tecla[K0] = false;
						break;
				}
			}
			else if(evento.type == ALLEGRO_EVENT_MOUSE_AXES){
				mouseX = evento.mouse.x;
				mouseY = evento.mouse.y;
			}
			/*else if(evento.type == ALLEGRO_EVENT_DISPLAY_RESIZE){
				al_resize_display(tela, evento.display.width, evento.display.height);
				sx = al_get_display_width(tela) / (float)largura;
				sy = al_get_display_height(tela) / (float)altura;
				ALLEGRO_TRANSFORM trans;
				al_identity_transform(&trans);
				al_scale_transform(&trans, sx, sy);
				al_use_transform(&trans);
			}*/
		}
		else if(estado == gameOver){
			
			if(evento.type == ALLEGRO_EVENT_TIMER){
				
                al_set_window_title(tela, "Nome");
                botaoMenu.atualiza(mouseX, mouseY);
                al_clear_to_color(al_map_rgb(50, 0, 0));
                al_draw_text(arial24, al_map_rgb(255, 255, 255), 50, 50, 0,"GAME OVER");
				if(player1.getVida() == 0)
					al_draw_text(arial24, al_map_rgb(255, 255, 255), 50, 300, 0,"Player 2 ganhou");
				else
					al_draw_text(arial24, al_map_rgb(255, 255, 255), 50, 300, 0,"Player 1 ganhou");
				
				botaoMenu.desenhar();
				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));
			}
			else if(evento.type == ALLEGRO_EVENT_MOUSE_AXES){
				mouseX = evento.mouse.x;
				mouseY = evento.mouse.y;
			}
			else if(evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
				if(evento.mouse.button == 1){
					if(botaoMenu.estaSelecionado()){
						estado = menu;
					}				
				}
			}
			/*else if(evento.type == ALLEGRO_EVENT_DISPLAY_RESIZE){
				al_resize_display(tela, evento.display.width, evento.display.height);	
				sx = al_get_display_width(tela) / (float)largura;
				sy = al_get_display_height(tela) / (float)altura;
				ALLEGRO_TRANSFORM trans;
				al_identity_transform(&trans);
				al_scale_transform(&trans, sx, sy);
				al_use_transform(&trans);
			}*/
			else if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
				acabou = true;
			}
		}
	}

	return 0;
}
