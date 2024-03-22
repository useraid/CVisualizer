#include <SDL2/SDL.h>
#include <bits/stdc++.h>
#include <random>
#include <vector>

void drawState(std::vector<int>& v, SDL_Renderer* renderer, int red, int blue){
    for (int i = 0; i < v.size(); i++){
        if(i == red){
            SDL_SetRenderDrawColor(renderer, 255,0,0,255);
        }
        else if(i == blue){
            SDL_SetRenderDrawColor(renderer, 0,0,255,255);
        }
        else{
            SDL_SetRenderDrawColor(renderer, 255,255,255,255);
        }
        SDL_RenderDrawLine(renderer, i,99,i,v[i]);
    }
}

int main(){
    // window state
    int running = 1;
    SDL_Event q;

    // fill vec
    std::random_device rd;
    std::uniform_int_distribution d(1,99);
    std::vector<int> v;
    for(int i = 0; i < 100; i++){v.push_back(d(rd));}

    // Init SDL
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    SDL_CreateWindowAndRenderer(100*5,100*5,0,&window,&renderer);
    SDL_RenderSetScale(renderer,5,5);

    // Algo
    while(running){
        for (int i = 0; i < v.size(); i++){
            for(int j = i; j < v.size(); j++){
                if(v[j]<v[i]){
                    std::swap(v[i],v[j]);
                }
                //Clear
                SDL_SetRenderDrawColor(renderer,0,0,0,255);
                SDL_RenderClear(renderer);
                drawState(v, renderer,i,j);

                // Render
                SDL_RenderPresent(renderer);
                SDL_Delay(1);

            }
        }
        while(SDL_PollEvent(&q)){
            if(q.type == SDL_QUIT){running = 0;break;}
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}