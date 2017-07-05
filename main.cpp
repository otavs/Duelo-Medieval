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
	double sx = 1.0, sy = 1.0;
	ALLEGRO_BITMAP *cenario = NULL;
	ALLEGRO_BITMAP *cenario1 = NULL;
	ALLEGRO_BITMAP *cenario2 = NULL;
	ALLEGRO_BITMAP *cenario3 = NULL;
	ALLEGRO_BITMAP *cenario4 = NULL;
	ALLEGRO_BITMAP *cenario5 = NULL;
	ALLEGRO_BITMAP *telaInicio = NULL;
	ALLEGRO_BITMAP *telaInstrucoes = NULL;
	ALLEGRO_BITMAP *telaSelecaoPersonagem = NULL;
	ALLEGRO_BITMAP *telaSelecaoCenario = NULL;
	ALLEGRO_BITMAP *telaGameover = NULL;
	ALLEGRO_BITMAP *imgSeletorP1 = NULL;
	ALLEGRO_BITMAP *imgSeletorP2 = NULL;
	Lista<char> secret;

	bool tecla[N_TECLAS];
	for(int i = 0; i < N_TECLAS; i++) tecla[i] = false;

	Lista<Item> listaItens;

	ALLEGRO_DISPLAY *tela = NULL;
	ALLEGRO_EVENT_QUEUE *filaEventos = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_FONT *arial24 = NULL;
	ALLEGRO_FONT *arial32 = NULL;

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
	arial32 = al_load_font("fontes/arial.ttf", 32, 0);

	al_register_event_source(filaEventos, al_get_display_event_source(tela));
	al_register_event_source(filaEventos, al_get_keyboard_event_source());
	al_register_event_source(filaEventos, al_get_timer_event_source(timer));
	al_register_event_source(filaEventos, al_get_mouse_event_source());

	Player player1;
	Player player2;

	Botao botaoJogar(largura/2, 300, "imagens/botao_jogar.png");
	Botao botaoInstrucoes(largura/2, 400, "imagens/botao_instrucoes.png");
	Botao botaoSair(largura/2, 500, "imagens/botao_sair.png");
	Botao botaoMenu(largura/2, 400, "imagens/botao_menu.png");

	Barra barraVidaP1;
	Barra barraVidaP2;
	Barra barraCooldownP1;
	Barra barraCooldownP2;

	Player::inicializarImagens();
    Item::inicializarImagens();
    Projetil::inicializarImagens();

	cenario1 = al_load_bitmap("imagens/cenario1.png");
	cenario2 = al_load_bitmap("imagens/cenario2.png");
	cenario3 = al_load_bitmap("imagens/cenario3.jpg");
	cenario4 = al_load_bitmap("imagens/cenario4.png");
	cenario5 = al_load_bitmap("imagens/cenario5.png");
	telaInicio = al_load_bitmap("imagens/inicio.png");
	telaInstrucoes = al_load_bitmap("imagens/instrucoes.png");
	telaSelecaoPersonagem = al_load_bitmap("imagens/selecaoPersonagem.jpg");
	telaSelecaoCenario = al_load_bitmap("imagens/selecaoCenario.jpg");
	telaGameover = al_load_bitmap("imagens/gameover.jpg");
	imgSeletorP1 = al_load_bitmap("imagens/seletorP1.png");
	imgSeletorP2 = al_load_bitmap("imagens/seletorP2.png");
	
	Timer timerItens(aleatorio(2*60, 3*60));
	timerItens.start();

	//al_hide_mouse_cursor(tela);

	al_start_timer(timer);

	while(!acabou){

		ALLEGRO_EVENT evento;
		al_wait_for_event(filaEventos, &evento);

		if(estado == menu){
			if(evento.type == ALLEGRO_EVENT_TIMER){
                al_set_window_title(tela, "Duelo Medieval");
                botaoJogar.atualiza(mouseX, mouseY);
                botaoInstrucoes.atualiza(mouseX, mouseY);
				botaoSair.atualiza(mouseX, mouseY);
				al_draw_bitmap(telaInicio, 0, 0, 0);
				botaoJogar.desenhar();
				botaoInstrucoes.desenhar();
				botaoSair.desenhar();
				al_draw_text(arial24, al_map_rgb(255, 255, 255), 5, 510, 0, "V 1.0");
				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));
				
				if(secret[6] == 'c' && secret[5] == 'a' && secret[4] == 'r' && secret[3] == 'a' &&
				secret[2] == 'c' && secret[1] == 'o' && secret[0] == 'l'){
                	while(!secret.vazia())
                		secret.removePrimeiro();
                		
                	player1 = Player(240, 400, caracolaladofaminto, 1);
					player2 = Player(700, 400, onigiri, 0);
					cenario = cenario5;

					barraVidaP1 = Barra(50, 30, 200, 30, player1.getVidaMax(), al_map_rgb(0, 255, 0));
					barraVidaP2 = Barra(650, 30, 200, 30, player2.getVidaMax(), al_map_rgb(0, 255, 0));
					barraCooldownP1 = Barra(50, 80, 200, 30, player1.getCooldown().getMaximo(), al_map_rgb(255, 200, 0));
					barraCooldownP2 = Barra(650, 80, 200, 30, player2.getCooldown().getMaximo(), al_map_rgb(255, 200, 0));

					estado = jogando;

					estaSelecionadoP1 = false;
					estaSelecionadoP2 = false;
					estaSelecionadoCenario = false;
					
					while(!listaItens.vazia())
						listaItens.removePrimeiro();
				}
				
				if(secret.getTam() == 8)
					secret.remove(7);
			}
			else if(evento.type == ALLEGRO_EVENT_MOUSE_AXES){
				mouseX = evento.mouse.x / sx;
				mouseY = evento.mouse.y / sy;
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
			else if(evento.type == ALLEGRO_EVENT_DISPLAY_RESIZE){
				al_resize_display(tela, evento.display.width, evento.display.height);
				sx = al_get_display_width(tela) / (float)largura;
				sy = al_get_display_height(tela) / (float)altura;
				ALLEGRO_TRANSFORM trans;
				al_identity_transform(&trans);
				al_scale_transform(&trans, sx, sy);
				al_use_transform(&trans);
			}
			else if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
				acabou = true;
			}
			else if(evento.type == ALLEGRO_EVENT_KEY_DOWN){
				switch(evento.keyboard.keycode){
					case ALLEGRO_KEY_C:
						secret.insereNoInicio('c');
						break;
					case ALLEGRO_KEY_A:
						secret.insereNoInicio('a');
						break;
					case ALLEGRO_KEY_R:
						secret.insereNoInicio('r');
						break;
					case ALLEGRO_KEY_O:
						secret.insereNoInicio('o');
						break;
					case ALLEGRO_KEY_L:
						secret.insereNoInicio('l');
						break;
				}
			}
		}
		else if(estado == escolhaClasse){
			if(evento.type == ALLEGRO_EVENT_TIMER){
                al_set_window_title(tela, "Duelo Medieval");
                
                if(secret[6] == 'c' && secret[5] == 'a' && secret[4] == 'r' && secret[3] == 'a' &&
				secret[2] == 'c' && secret[1] == 'o' && secret[0] == 'l'){
                	while(!secret.vazia())
                		secret.removePrimeiro();
                		
                	player1 = Player(240, 400, caracolaladofaminto, 1);
					player2 = Player(700, 400, onigiri, 0);
					cenario = cenario5;

					barraVidaP1 = Barra(50, 30, 200, 30, player1.getVidaMax(), al_map_rgb(0, 255, 0));
					barraVidaP2 = Barra(650, 30, 200, 30, player2.getVidaMax(), al_map_rgb(0, 255, 0));
					barraCooldownP1 = Barra(50, 80, 200, 30, player1.getCooldown().getMaximo(), al_map_rgb(255, 200, 0));
					barraCooldownP2 = Barra(650, 80, 200, 30, player2.getCooldown().getMaximo(), al_map_rgb(255, 200, 0));

					estado = jogando;

					estaSelecionadoP1 = false;
					estaSelecionadoP2 = false;
					
					while(!listaItens.vazia())
						listaItens.removePrimeiro();
				}
				
				if(secret.getTam() == 8)
					secret.remove(7);
					
				if(estaSelecionadoP2 && estaSelecionadoP1){

					player1 = Player(240, 400, seletorP1, 1);
					player2 = Player(700, 400, seletorP2, 0);

					barraVidaP1 = Barra(50, 30, 200, 30, player1.getVidaMax(), al_map_rgb(0, 255, 0));
					barraVidaP2 = Barra(650, 30, 200, 30, player2.getVidaMax(), al_map_rgb(0, 255, 0));
					barraCooldownP1 = Barra(50, 80, 200, 30, player1.getCooldown().getMaximo(), al_map_rgb(255, 200, 0));
					barraCooldownP2 = Barra(650, 80, 200, 30, player2.getCooldown().getMaximo(), al_map_rgb(255, 200, 0));

					estado = escolhaCenario;

					estaSelecionadoP1 = false;
					estaSelecionadoP2 = false;
				}
                
                al_draw_bitmap(telaSelecaoPersonagem, 0, 0, 0);
                
                al_draw_textf(arial32, al_map_rgb(13, 104, 18), 300, 145, 0, "Escolham suas classes!");
                
                al_draw_rectangle(300, 270, 380, 410, al_map_rgb(255, 255, 255), 5);
				al_draw_rectangle(400, 270, 480, 410, al_map_rgb(255, 255, 255), 5);
				al_draw_rectangle(500, 270, 580, 410, al_map_rgb(255, 255, 255), 5);
				al_draw_rectangle(600, 270, 680, 410, al_map_rgb(255, 255, 255), 5);
				
				if(estaSelecionadoP1){
					if(seletorP1 == 0){
						al_draw_filled_rectangle(300, 270, 380, 410, al_map_rgba(255, 0, 0, 0.5));
					}
					if(seletorP1 == 1){
						al_draw_filled_rectangle(400, 270, 480, 410, al_map_rgba(255, 0, 0, 0.5));
					}
					if(seletorP1 == 2){
						al_draw_filled_rectangle(500, 270, 580, 410, al_map_rgba(255, 0, 0, 0.5));
					}
					if(seletorP1 == 3){
						al_draw_filled_rectangle(600, 270, 680, 410, al_map_rgba(255, 0, 0, 0.5));
					}
				}
				if(estaSelecionadoP2){
					if(seletorP2 == 0){
						al_draw_filled_rectangle(300, 270, 380, 410, al_map_rgba(0, 0, 255, 0.5));
					}
					if(seletorP2 == 1){
						al_draw_filled_rectangle(400, 270, 480, 410, al_map_rgba(0, 0, 255, 0.5));
					}
					if(seletorP2 == 2){
						al_draw_filled_rectangle(500, 270, 580, 410, al_map_rgba(0, 0, 255, 0.5));
					}
					if(seletorP2 == 3){
						al_draw_filled_rectangle(600, 270, 680, 410, al_map_rgba(0, 0, 255, 0.5));
					}
				}

				Player::desenharImagem(0, 270, 290);
				Player::desenharImagem(1, 370, 290);
				Player::desenharImagem(2, 470, 290);
                Player::desenharImagem(3, 570, 290);
				
                if(seletorP1 != seletorP2){
                    if(seletorP1 == 0){
                    	al_draw_rectangle(300, 270, 380, 410, al_map_rgb(255, 0, 0), 5);
                    	al_draw_bitmap(imgSeletorP1, 307, 201, 0);
					}   
                    else if(seletorP1 == 1){
                    	al_draw_rectangle(400, 270, 480, 410, al_map_rgb(255, 0, 0), 5);
                    	al_draw_bitmap(imgSeletorP1, 407, 201, 0);
					}   
                    else if(seletorP1 == 2){
                    	al_draw_rectangle(500, 270, 580, 410, al_map_rgb(255, 0, 0), 5);
                    	al_draw_bitmap(imgSeletorP1, 507, 201, 0);
					}
                    else if(seletorP1 == 3){
                    	al_draw_rectangle(600, 270, 680, 410, al_map_rgb(255, 0, 0), 5);
                    	al_draw_bitmap(imgSeletorP1, 607, 201, 0);
					}
					
                    if(seletorP2 == 0){
                    	al_draw_rectangle(300, 270, 380, 410, al_map_rgb(0, 0, 255), 5);
                    	al_draw_bitmap(imgSeletorP2, 307, 425, 0);
					}
                    else if(seletorP2 == 1){
                    	al_draw_rectangle(400, 270, 480, 410, al_map_rgb(0, 0, 255), 5);
                    	al_draw_bitmap(imgSeletorP2, 407, 425, 0);
					}
                    else if(seletorP2 == 2){
                    	al_draw_rectangle(500, 270, 580, 410, al_map_rgb(0, 0, 255), 5);
                    	al_draw_bitmap(imgSeletorP2, 507, 425, 0);
					}
                    else if(seletorP2 == 3){
                    	al_draw_rectangle(600, 270, 680, 410, al_map_rgb(0, 0, 255), 5);
                    	al_draw_bitmap(imgSeletorP2, 607, 425, 0);
					}
                        
                }
                else{
                    if(seletorP1 == 0){
                    	al_draw_rectangle(295, 265, 385, 415, al_map_rgb(255, 0, 0), 5);
                    	al_draw_bitmap(imgSeletorP1, 307, 201, 0);
					}
                    else if(seletorP1 == 1){
                    	al_draw_rectangle(395, 265, 485, 415, al_map_rgb(255, 0, 0), 5);
                    	al_draw_bitmap(imgSeletorP1, 407, 201, 0);
					} 
                    else if(seletorP1 == 2){
                    	al_draw_rectangle(495, 265, 585, 415, al_map_rgb(255, 0, 0), 5);
                    	al_draw_bitmap(imgSeletorP1, 507, 201, 0);
					}
                    else if(seletorP1 == 3){
                    	al_draw_rectangle(595, 265, 685, 415, al_map_rgb(255, 0, 0), 5);
                    	al_draw_bitmap(imgSeletorP1, 607, 201, 0);
					}

                    if(seletorP2 == 0){
                    	al_draw_rectangle(300, 270, 380, 410, al_map_rgb(0, 0, 255), 5);
                    	al_draw_bitmap(imgSeletorP2, 307, 425, 0);
					}
                    else if(seletorP2 == 1){
                    	al_draw_rectangle(400, 270, 480, 410, al_map_rgb(0, 0, 255), 5);
                    	al_draw_bitmap(imgSeletorP2, 407, 425, 0);
					}
                    else if(seletorP2 == 2){
                    	al_draw_rectangle(500, 270, 580, 410, al_map_rgb(0, 0, 255), 5);
                    	al_draw_bitmap(imgSeletorP2, 507, 425, 0);
					}
                    else if(seletorP2 == 3){
                    	al_draw_rectangle(600, 270, 680, 410, al_map_rgb(0, 0, 255), 5);
                    	al_draw_bitmap(imgSeletorP2, 607, 425, 0);
					}
                }

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
						if(!estaSelecionadoP2){
							seletorP2++;
							if(seletorP2 > 3)
								seletorP2 = 3;
						}
						break;
					case ALLEGRO_KEY_LEFT:
						if(!estaSelecionadoP2){
							seletorP2--;
							if(seletorP2 < 0)
								seletorP2 = 0;
						}
						break;
					case ALLEGRO_KEY_H:
						if(!estaSelecionadoP1){
							seletorP1++;
							if(seletorP1 > 3)
								seletorP1 = 3;
						}
						break;
					case ALLEGRO_KEY_F:
						if(!estaSelecionadoP1){
							seletorP1--;
							if(seletorP1 < 0)
								seletorP1 = 0;
						}
						break;
					case ALLEGRO_KEY_I:
						estaSelecionadoP2 = !estaSelecionadoP2;
						break;
					case ALLEGRO_KEY_Q:
						estaSelecionadoP1 = !estaSelecionadoP1;
						break;
					case ALLEGRO_KEY_C:
						secret.insereNoInicio('c');
						break;
					case ALLEGRO_KEY_A:
						secret.insereNoInicio('a');
						break;
					case ALLEGRO_KEY_R:
						secret.insereNoInicio('r');
						break;
					case ALLEGRO_KEY_O:
						secret.insereNoInicio('o');
						break;
					case ALLEGRO_KEY_L:
						secret.insereNoInicio('l');
						break;
				}
			}
			else if(evento.type == ALLEGRO_EVENT_DISPLAY_RESIZE){
				al_resize_display(tela, evento.display.width, evento.display.height);
				sx = al_get_display_width(tela) / (float)largura;
				sy = al_get_display_height(tela) / (float)altura;
				ALLEGRO_TRANSFORM trans;
				al_identity_transform(&trans);
				al_scale_transform(&trans, sx, sy);
				al_use_transform(&trans);
			}
			else if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
				acabou = true;
			}
		}
		else if(estado == instrucoes){
			if(evento.type == ALLEGRO_EVENT_TIMER){
                al_set_window_title(tela, "Duelo Medieval");
                al_draw_bitmap(telaInstrucoes, 0, 0, 0);
                botaoMenu.atualiza(mouseX, mouseY);
				botaoMenu.desenhar();
				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));
			}
			else if(evento.type == ALLEGRO_EVENT_MOUSE_AXES){
				mouseX = evento.mouse.x / sx;
				mouseY = evento.mouse.y / sy;
			}
			else if(evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
				if(evento.mouse.button == 1){
					if(botaoMenu.estaSelecionado()){
						estado = menu;
					}
				}
			}
			else if(evento.type == ALLEGRO_EVENT_DISPLAY_RESIZE){
				al_resize_display(tela, evento.display.width, evento.display.height);
				sx = al_get_display_width(tela) / (float)largura;
				sy = al_get_display_height(tela) / (float)altura;
				ALLEGRO_TRANSFORM trans;
				al_identity_transform(&trans);
				al_scale_transform(&trans, sx, sy);
				al_use_transform(&trans);
			}
			else if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
				acabou = true;
			}
		}
		else if(estado == escolhaCenario){
			if(evento.type == ALLEGRO_EVENT_TIMER){
                al_set_window_title(tela, "Duelo Medieval");
                al_draw_bitmap(telaSelecaoCenario, 0, 0, 0);
                
                al_draw_textf(arial32, al_map_rgb(13, 104, 18), 290, 90, 0, "Escolham o campo de batalha!");
                
                al_draw_rectangle(294, 160, 485, 269, al_map_rgb(255, 255, 255), 5);
				al_draw_rectangle(614, 152, 807, 261, al_map_rgb(255, 255, 255), 5);
				al_draw_rectangle(299, 332, 487, 441, al_map_rgb(255, 255, 255), 5);
				al_draw_rectangle(612, 333, 802, 442, al_map_rgb(255, 255, 255), 5);

				if(estaSelecionadoCenario){
					if(seletorCenario == 0)
						cenario = cenario1;
					else if(seletorCenario == 1)
						cenario = cenario2;
					else if(seletorCenario == 2)
						cenario = cenario3;
					else if(seletorCenario == 3)
						cenario = cenario4;
                    for(int i = 0; i < listaItens.getTam(); i++)
						listaItens.removePrimeiro();
					estado = jogando;
					estaSelecionadoCenario = false;
				}

				if(seletorCenario == 0)
                    al_draw_rectangle(294, 160, 485, 269, al_map_rgb(255, 0, 0), 8);
				else if(seletorCenario == 1)
					al_draw_rectangle(614, 152, 807, 261, al_map_rgb(255, 0, 0), 8);
				else if(seletorCenario == 2)
					al_draw_rectangle(299, 332, 487, 441, al_map_rgb(255, 0, 0), 8);
				else if(seletorCenario == 3)
					al_draw_rectangle(612, 333, 802, 442, al_map_rgb(255, 0, 0), 8);

				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));
			}
			else if(evento.type == ALLEGRO_EVENT_MOUSE_AXES){
				mouseX = evento.mouse.x / sx;
				mouseY = evento.mouse.y / sy;
			}

			else if(evento.type == ALLEGRO_EVENT_KEY_DOWN){
				switch(evento.keyboard.keycode){
					case ALLEGRO_KEY_RIGHT:
						if(seletorCenario == 0)
							seletorCenario = 1;
						else if(seletorCenario == 2)
							seletorCenario = 3;
						break;
					case ALLEGRO_KEY_LEFT:
						if(seletorCenario == 1)
							seletorCenario = 0;
						else if(seletorCenario == 3)
							seletorCenario = 2;
						break;
                    case ALLEGRO_KEY_UP:
                        if(seletorCenario == 2)
                            seletorCenario = 0;
                        else if(seletorCenario == 3)
                            seletorCenario = 1;
                            break;
                    case ALLEGRO_KEY_DOWN:
                        if(seletorCenario == 0)
                            seletorCenario = 2;
                        else if(seletorCenario == 1)
                            seletorCenario = 3;
                            break;
					case ALLEGRO_KEY_H:
						if(seletorCenario == 0)
							seletorCenario = 1;
						else if(seletorCenario == 2)
							seletorCenario = 3;
						break;
					case ALLEGRO_KEY_F:
						if(seletorCenario == 1)
							seletorCenario = 0;
						else if(seletorCenario == 3)
							seletorCenario = 2;
						break;
                    case ALLEGRO_KEY_T:
                        if(seletorCenario == 2)
                            seletorCenario = 0;
                        else if(seletorCenario == 3)
                            seletorCenario = 1;
                            break;
                    case ALLEGRO_KEY_G:
                        if(seletorCenario == 0)
                            seletorCenario = 2;
                        else if(seletorCenario == 1)
                            seletorCenario = 3;
                            break;
					case ALLEGRO_KEY_I:
						estaSelecionadoCenario = true;
						break;
					case ALLEGRO_KEY_Q:
						estaSelecionadoCenario = true;
						break;
				}
			}
			else if(evento.type == ALLEGRO_EVENT_DISPLAY_RESIZE){
				al_resize_display(tela, evento.display.width, evento.display.height);
				sx = al_get_display_width(tela) / (float)largura;
				sy = al_get_display_height(tela) / (float)altura;
				ALLEGRO_TRANSFORM trans;
				al_identity_transform(&trans);
				al_scale_transform(&trans, sx, sy);
				al_use_transform(&trans);
			}
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

                //Pra um player não passar em cima do outro
				if(player1.getY() < player2.getY()){
                    player1.desenhar(tecla[T] || tecla[G] || tecla[F] || tecla[H]);
					player2.desenhar(tecla[UP] || tecla[DOWN] || tecla[LEFT] || tecla[RIGHT]);

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

                al_draw_filled_rectangle(50, 140, 250, 190, al_map_rgb(200, 200, 200));
                al_draw_filled_rectangle(650, 140, 850, 190, al_map_rgb(200, 200, 200));

				al_draw_text(arial24, al_map_rgb(255, 255, 255), 60, 150, 0, "1:");
				al_draw_text(arial24, al_map_rgb(255, 255, 255), 120, 150, 0, "2:");
				al_draw_text(arial24, al_map_rgb(255, 255, 255), 180, 150, 0, "3:");
				int x = 80;
				for(int i = 0; i < player1.getListaItens().getTam(); i++){
					if(player1.getListaItens()[i].getTipo() == pocao)
						Item::desenharImagem(player1.getListaItens()[i].getTipo(), x, 150);
					else if(player1.getListaItens()[i].getTipo() == runa)
						Item::desenharImagem(player1.getListaItens()[i].getTipo(), x, 150);
					else if(player1.getListaItens()[i].getTipo() == gema)
						Item::desenharImagem(player1.getListaItens()[i].getTipo(), x, 150);
					x += 60;
				}

                al_draw_text(arial24, al_map_rgb(255, 255, 255), 660, 150, 0, "8:");
				al_draw_text(arial24, al_map_rgb(255, 255, 255), 720, 150, 0, "9:");
				al_draw_text(arial24, al_map_rgb(255, 255, 255), 780, 150, 0, "0:");
				x = 680;
				for(int i = 0; i < player2.getListaItens().getTam(); i++){
					if(player2.getListaItens()[i].getTipo() == pocao)
                        Item::desenharImagem(player2.getListaItens()[i].getTipo(), x, 150);
					else if(player2.getListaItens()[i].getTipo() == runa)
                        Item::desenharImagem(player2.getListaItens()[i].getTipo(), x, 150);
					else if(player2.getListaItens()[i].getTipo() == gema)
                        Item::desenharImagem(player2.getListaItens()[i].getTipo(), x, 150);
					x += 60;
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
				mouseX = evento.mouse.x / sx;
				mouseY = evento.mouse.y / sy;
			}
			else if(evento.type == ALLEGRO_EVENT_DISPLAY_RESIZE){
				al_resize_display(tela, evento.display.width, evento.display.height);
				sx = al_get_display_width(tela) / (float)largura;
				sy = al_get_display_height(tela) / (float)altura;
				ALLEGRO_TRANSFORM trans;
				al_identity_transform(&trans);
				al_scale_transform(&trans, sx, sy);
				al_use_transform(&trans);
			}
		}
		else if(estado == gameOver){
			if(evento.type == ALLEGRO_EVENT_TIMER){
                al_set_window_title(tela, "Duelo Medieval");
                botaoMenu.atualiza(mouseX, mouseY);
                al_draw_bitmap(telaGameover, 0, 0, 0);
				if(player1.getVida() == 0)
					al_draw_text(arial32, al_map_rgb(20, 0, 255), largura/2-134, 110, 0,"Player 2 venceu !!!");
				else
					al_draw_text(arial32, al_map_rgb(255, 0, 20), largura/2-134, 110, 0,"Player 1 venceu !!!");
				botaoMenu.desenhar();
				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));
			}
			else if(evento.type == ALLEGRO_EVENT_MOUSE_AXES){
				mouseX = evento.mouse.x / sx;
				mouseY = evento.mouse.y / sy;
			}
			else if(evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
				if(evento.mouse.button == 1){
					if(botaoMenu.estaSelecionado()){
						estado = menu;
					}
				}
			}
			else if(evento.type == ALLEGRO_EVENT_DISPLAY_RESIZE){
				al_resize_display(tela, evento.display.width, evento.display.height);
				sx = al_get_display_width(tela) / (float)largura;
				sy = al_get_display_height(tela) / (float)altura;
				ALLEGRO_TRANSFORM trans;
				al_identity_transform(&trans);
				al_scale_transform(&trans, sx, sy);
				al_use_transform(&trans);
			}
			else if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
				acabou = true;
			}
		}
	}

	return 0;
}
