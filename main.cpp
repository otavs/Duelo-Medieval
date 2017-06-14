#include "includes.h"

#include "lista.h"
#include "projetil.h"
#include "player.h"
#include "item.h"
#include "timer.h"

int main(){	
	
	int largura = 960;
	int altura = 540;
	int fps = 60;
	bool acabou = false;
	int mouseX = 0, mouseY = 0;
	
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
	
	//Player(x, y, vx, vy, largura, altura, vida, poder, sentido, larguraAtaque, alturaAtaque, classe);
	Player player1(100, 400, barbaro, 1);
	Player player2(700, 400, arqueiro, 0);
	
	Timer t(10*60); // timer teste de 10 segundos
	t.start();
	Timer timerItens(aleatorio(2*60, 3*60));
	timerItens.start();
	
	al_hide_mouse_cursor(tela);
	
	al_start_timer(timer);
	
	while(!acabou){
		
			ALLEGRO_EVENT evento;
			al_wait_for_event(filaEventos, &evento);
		
			if(evento.type == ALLEGRO_EVENT_TIMER){
				if(tecla[UP]){
					player1.andarCima(altura/2);
				}
				if(tecla[DOWN]){
					player1.andarBaixo(altura);
				}
				if(tecla[LEFT]){
					player1.andarEsquerda(0);
				}
				if(tecla[RIGHT]){
					player1.andarDireita(largura);
				}
				if(tecla[T]){
					player2.andarCima(altura/2);
				}
				if(tecla[G]){
					player2.andarBaixo(altura);
				}
				if(tecla[F]){
					player2.andarEsquerda(0);
				}
				if(tecla[H]){
					player2.andarDireita(largura);
				}

				player1.atualizaProjeteis(player2);
				player2.atualizaProjeteis(player1);
				t.update();
				timerItens.update();
				player1.atualizaTimers();
				player2.atualizaTimers();
				
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
					timerItens.setMaximo(aleatorio(2*60, 4*60));
					timerItens.start();
				}
				
				// Renderizacao:
				al_draw_filled_rectangle(0, altura/2, largura, altura, al_map_rgba(150, 0, 150, 0.7));
				for(int i = 0; i < listaItens.getTam(); i++){
					listaItens[i].desenhar();
				}
				player1.desenhar();
				player2.desenhar();
				player1.desenhaProjeteis();
				player2.desenhaProjeteis();
				
				al_draw_textf(arial24, al_map_rgb(255, 255, 255), 100, 50, 0, "Vida P1: %d", player1.getVida());
				al_draw_textf(arial24, al_map_rgb(255, 255, 255), 700, 50, 0, "Vida P2: %d", player2.getVida());
				al_draw_textf(arial24, al_map_rgb(255, 255, 255), 400, 50, 0, "Timer: %.0f", ceil(t.getContador()/60.0)); // funcao ceil arredonda para o maior inteiro
				al_draw_textf(arial24, al_map_rgb(255, 255, 255), 100, 100, 0, "Cooldown: %.0f", ceil(player1.getValorCooldown()/60.0));
				al_draw_textf(arial24, al_map_rgb(255, 255, 255), 700, 100, 0, "Cooldown: %.0f", ceil(player2.getValorCooldown()/60.0));
				
				al_draw_text(arial24, al_map_rgb(255, 255, 255), 100, 150, 0, "Itens:");
				int x = 170;
				for(int i = 0; i < player1.getListaItens().getTam(); i++){
					al_draw_textf(arial24, al_map_rgb(255, 255, 255), x, 150, 0, "%d ", player1.getListaItens()[i].getTipo());
					x += 35;
				}
				
				al_draw_text(arial24, al_map_rgb(255, 255, 255), 700, 150, 0, "Itens:");
				x = 770;
				for(int i = 0; i < player2.getListaItens().getTam(); i++){
					al_draw_textf(arial24, al_map_rgb(255, 255, 255), x, 150, 0, "%d ", player2.getListaItens()[i].getTipo());
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
						player1.atacar(player2);
						break;
					case ALLEGRO_KEY_Q:
						tecla[Q] = true;
						player2.atacar(player1);
						break;
					case ALLEGRO_KEY_ESCAPE:
						tecla[ESC] = true;
						acabou = true;
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

	return 0;
}
