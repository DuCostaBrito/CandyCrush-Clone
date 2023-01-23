#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

int main()
{
    int width = 640;
    int height = 480;

    bool done = false;
    int pos_x = width / 2;
    int pos_y = height / 2;

    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *queue;
    ALLEGRO_COLOR color = al_map_rgb(255, 0, 0);

    if (!al_init())
        return -1;
    
    display = al_create_display(width, height);

    if (!display)
        return -1;
    
    al_init_primitives_addon();
    //Declarando mouse e teclado
    al_install_keyboard();
    al_install_mouse();

    queue = al_create_event_queue();

    //Deixando a fila atenta aos eventos do teclado e mouse
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());

    while(!done)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            done = true;
        }

        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch (ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_UP:
                color = al_map_rgb(0, 255, 0);
                break;
            case ALLEGRO_KEY_DOWN:
                color = al_map_rgb(0, 0, 255);
                break;
            case ALLEGRO_KEY_LEFT:
                color = al_map_rgb(0, 255, 255);
                break;
            default:
                break;
            }
        }

        else if(ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) 
                done = true;
        }

        al_draw_filled_circle(pos_x, pos_y, 50, color);
        al_flip_display(); //Buffer
        al_clear_to_color(al_map_rgb(0,0,0)); //Limpa o plano de fundo para preto
    }
    al_destroy_display(display);
}