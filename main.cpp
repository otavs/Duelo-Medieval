#include "includes.h"

int main(){	
	
	int largura = 960;
	int altura = 540;
	int fps = 60;
	bool acabou = false;
	int mouseX = 0, mouseY = 0;
	
	bool tecla[N_TECLAS];
	for(int i = 0; i < N_TECLAS; i++) tecla[i] = false;
	
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
	Player player1(100, 400, 6, 6, 40, 80, 100, 10, 1, 40, 20, guerreiro);
	Player player2(700, 400, 6, 6, 40, 80, 100, 10, 0, 40, 20, mago);
	
	al_hide_mouse_cursor(tela);
	
	al_start_timer(timer);
	
	while(!acabou){
		
			ALLEGRO_EVENT evento;
			al_wait_for_event(filaEventos, &evento);
		
			if(evento.type == ALLEGRO_EVENT_TIMER){
				if(tecla[UP]){
					player1.andarCima();
				}
				if(tecla[DOWN]){
					player1.andarBaixo();
				}
				if(tecla[LEFT]){
					player1.andarEsquerda();
				}
				if(tecla[RIGHT]){
					player1.andarDireita();
				}
				if(tecla[T]){
					player2.andarCima();
				}
				if(tecla[F]){
					player2.andarEsquerda();
				}
				if(tecla[G]){
					player2.andarBaixo();
				}
				if(tecla[H]){
					player2.andarDireita();
				}

				player1.atualizaProjeteis(player2);
				player2.atualizaProjeteis(player1);
				
				// Renderizacao:
				player1.desenhar();
				player2.desenhar();
				player1.desenhaProjeteis();
				player2.desenhaProjeteis();
				al_draw_textf(arial24, al_map_rgb(255, 255, 255), 100, 50, 0, "Vida P1: %d", player1.getVida());
				al_draw_textf(arial24, al_map_rgb(255, 255, 255), 700, 50, 0, "Vida P2: %d", player2.getVida());
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
