#include<iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL_net.h>




SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;


const int win_width = 600;
const int win_height = 600;

const int cell_size = 200;


void DeInit(int error)
{
    if (ren != NULL) SDL_DestroyRenderer(ren);
    if (win != NULL) SDL_DestroyWindow(win);
    SDL_Quit();
    exit(error);
}

void Init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Could not initialize SDL: %s\n", SDL_GetError());
        system("pause");
        DeInit(1);
    }

    win = SDL_CreateWindow("CLIENT", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, win_width, win_height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (win == NULL)
    {
        printf("Could not create window: %s\n", SDL_GetError());
        system("pause");
        DeInit(1);
    }

    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (ren == NULL)
    {
        printf("Could not create renderer: %s\n", SDL_GetError());
        system("pause");
        DeInit(1);
    }
}

SDL_Texture* loadTextureFromFile(const char* filename, SDL_Renderer* renderer)
{
    SDL_Surface* surface = IMG_Load(filename);
    if (surface == NULL)
    {
        printf("Could not load image: %s\n", SDL_GetError());
        system("pause");
        DeInit(1);
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

int count_x = 0; 

int press_right_click(int x, int y, SDL_Rect* rect)
{

    if (x >= 0 && x <= cell_size && y >= 0 && y <= cell_size)
    {
        rect->x = 0; rect->y = 0; 
        count_x = 0; 

    }
    else  if (x >= cell_size && x <= 2 * cell_size && y >= 0 && y <= cell_size)
    {
        rect->x = cell_size; rect->y = 0;
        count_x = 1; 

    }
    else  if (x >= 2 * cell_size && x <= 3 * cell_size && y >= 0 && y <= cell_size)
    {
        rect->x = 2 * cell_size; rect->y = 0; 
        count_x = 2; 

    }
    else  if (x >= 0 && x <= cell_size && y >= cell_size && y <= 2 * cell_size)
    {
        rect->x = 0; rect->y = cell_size; 
        count_x = 3; 

    }
    else  if (x >= cell_size && x <= 2 * cell_size && y >= cell_size && y <= 2 * cell_size)
    {
        rect->x = cell_size; rect->y = cell_size; 
        count_x = 4; 

    }
    else  if (x >= 2 * cell_size && x <= 3 * cell_size && y >= cell_size && y <= 2 * cell_size)
    {
        rect->x = 2 * cell_size; rect->y = cell_size; 
        count_x = 5;

    }
    else  if (x >= 0 && x <= cell_size && y >= 2 * cell_size && y <= 3 * cell_size)
    {
        rect->x = 0; rect->y = 2 * cell_size; 
        count_x = 6; 

    }
    else  if (x >= cell_size && x <= 2 * cell_size && y >= 2 * cell_size && y <= 3 * cell_size)
    {
        rect->x = cell_size; rect->y = 2 * cell_size; 
        count_x = 7; 

    }
    else  if (x >= 2 * cell_size && x <= 3 * cell_size && y >= 2 * cell_size && y <= 3 * cell_size)
    {
        rect->x = 2 * cell_size; rect->y = 2 * cell_size; 
        count_x = 8; 

    }

    return count_x;
}

int start_game = 0; 
void check_turn(int* z_arr)
{ 
    if ((z_arr[0] + z_arr[1] + z_arr[2]) == 3)
    {
           start_game = 1; 
    }
    else	if ((z_arr[3] + z_arr[4] + z_arr[5]) == 3)
    {
       
        start_game = 1;
       
    }
    else	if ((z_arr[6] + z_arr[7] + z_arr[8]) == 3)
    {
        start_game = 1; 
     
    }
    else	if ((z_arr[0] + z_arr[4] + z_arr[8]) == 3)
    {

        start_game = 1; 

    }
    else	if ((z_arr[2] + z_arr[4] + z_arr[6]) == 3)
    {

        start_game = 1; 
    }
    else	if ((z_arr[0] + z_arr[3] + z_arr[6]) == 3)
    {
     
        start_game = 1; 
    }
    else	if ((z_arr[1] + z_arr[4] + z_arr[7]) == 3)
    {
    
        start_game = 1; 
    }
    else	if ((z_arr[2] + z_arr[5] + z_arr[8]) == 3)
    {
      
        start_game = 1; 
    }


    else if ((z_arr[0] + z_arr[1] + z_arr[2]) == 15)
    {
 
        start_game = 1; 
    }
    else	if ((z_arr[3] + z_arr[4] + z_arr[5]) == 15)
    {
  
        start_game = 1; 
    }
    else	if ((z_arr[6] + z_arr[7] + z_arr[8]) == 15)
    {

        start_game = 1; 
    }
    else	if ((z_arr[0] + z_arr[4] + z_arr[8]) == 15)
    {
   
        start_game = 1; 
    }
    else	if ((z_arr[2] + z_arr[4] + z_arr[6]) == 15)
    {
        
        start_game = 1; 
    }
    else	if ((z_arr[0] + z_arr[3] + z_arr[6]) == 15)
    {
      
        start_game = 1; 
    }
    else	if ((z_arr[1] + z_arr[4] + z_arr[7]) == 15)
    {
      
        start_game = 1; 
 
    }
    else	if ((z_arr[2] + z_arr[5] + z_arr[8]) == 15)
    {
        start_game = 1; 

    }

}

int main(int argc, char* args[])
{
    Init();
 


    int u_arr[9] =
    { 0,0,0,
    0,0,0,
    0,0,0 };


    SDL_Rect u_rect = { 0,0,win_width / 3, win_height / 3 };

    SDL_Rect board_rect = { 0,0,win_width, win_height };
    SDL_Rect print_rect1 = { win_width / 4,win_height / 4,win_width / 2, win_height / 2 };
    int print_time = 0; 
    SDL_Rect start_game1 = { win_width / 4,win_height / 4,win_width / 2, win_height / 2 }; 


    SDL_Texture* board_tex = loadTextureFromFile("tic_toe_board.png", ren);
    SDL_Texture* x_tex = loadTextureFromFile("iksi.png", ren);
    SDL_Texture* o_tex = loadTextureFromFile("noli.png", ren);
    SDL_Texture* start_game_tex = loadTextureFromFile("start_game.bmp", ren);

    SDL_Texture* print_text1 = loadTextureFromFile("hello.bmp", ren);
    SDL_SetTextureBlendMode(print_text1, SDL_BLENDMODE_BLEND);
    SDL_Texture* arr_x_o[6];
    arr_x_o[1] = x_tex;
    arr_x_o[5] = o_tex;
    arr_x_o[4] = start_game_tex; 


    int mouseX;
    int mouseY;
    int turn_count = 1;
 

   
    SDL_Event event;
    bool quit = false;
    while (!quit)
    {
        while (SDL_PollEvent(&event) != 0)  
        {
           
     
            if (event.type == SDL_QUIT)
            {
                quit = true;
            } 

            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
          

                if (event.button.button == SDL_BUTTON_LEFT)
                {

                    if (start_game == 0)
                    {

                        mouseX = event.button.x;
                        mouseY = event.button.y;

                        if (u_arr[press_right_click(mouseX, mouseY, &u_rect)] != 0)
                        {

                            print_time = 120;
                        }
                        else {
                            u_arr[press_right_click(mouseX, mouseY, &u_rect)] = turn_count; 
                  
                            if (turn_count == 1) { turn_count = 5; }
                            else { turn_count = 1; }
                        }
                       
                    }
                    else if (start_game == 1 )
                    {
                    
               
                        for (int i = 0; i < 9; ++i)
                        {
                            u_arr[i] = 0;
                        }
                        start_game = 0;
                    }



                }
               
            }
           

        }
        

        check_turn(&u_arr[0]); 
   
        if (print_time > 0) { print_time--; }

       


        SDL_RenderCopy(ren, board_tex, NULL, &board_rect);
        for (int a = 0; a < 9; a++)
        {
            if (u_arr[a] != 0) {
                u_rect.x = cell_size * (a % 3);
                u_rect.y = cell_size * (a / 3);
                SDL_RenderCopy(ren, arr_x_o[u_arr[a]], NULL, &u_rect);
            }

        }
        Uint8 alpha;
        if (print_time > 0) {
            if (print_time < 64) { SDL_SetTextureAlphaMod(print_text1, print_time * 4 - 1); }
            else { SDL_SetTextureAlphaMod(print_text1, 255); }
            SDL_RenderCopy(ren, print_text1, NULL, &print_rect1);
        } // endif 

        if (start_game == 1)
        {
         
            SDL_RenderCopy(ren, board_tex, NULL, &board_rect);
       
            for (int i = 0; i < 9; ++i)
            {
                u_arr[i] = 0;
            } 

    

            SDL_RenderCopy(ren, arr_x_o[4], NULL, &start_game1); 

        } 

        SDL_RenderPresent(ren);  
        SDL_Delay(1000 / 120);


      
    }

    SDLNet_Quit();

    DeInit(0);
    return 0;
}
