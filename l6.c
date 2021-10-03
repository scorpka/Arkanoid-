#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_image.h>

void pixelDraw(SDL_Rect pixelPos,SDL_Rect brickRect,SDL_Renderer* gRenderer,int *x,int *y,int *polX,int *polY,SDL_Texture* dotTexture)
{
   if (*polX == 0) *x = *x+1;
   if (*polY == 0) *y = *y+1;
   if ( *x == 639){ *polX =1; }else if(*x == 1){*polX = 0;};
   if ( *y == 479){ *polY =1; }else if(*y == 1){*polY = 0;};
   if ( ((*x == brickRect.x || *x+1 == brickRect.x)  &&  *y >= brickRect.y && *y <= brickRect.y+brickRect.h)  || (*x == brickRect.x + brickRect.w &&  *y -100 >= brickRect.y && *y -100 <= brickRect.y+brickRect.h)){ *polX = !(*polX); if(*x==brickRect.x  || *x == brickRect.x - 1){*x = *x-5;}} 

   if (( *y == brickRect.y &&  *x >= brickRect.x && *x <= brickRect.x+brickRect.w)||( *y == brickRect.y + brickRect.h &&  *x +1 >= brickRect.x && *x +1 <= brickRect.x+brickRect.w)) *polY = !*polY; 
   
   if (*polX == 1) *x = *x-1;
   if (*polY == 1) *y = *y-1;
  pixelPos.x = *x;
  pixelPos.y = *y;

 SDL_RenderCopy(gRenderer,dotTexture,NULL,&pixelPos); 
 //SDL_RenderDrawPoint(gRenderer,*x,*y);
}


void brickDraw(SDL_Rect brickRect,int *polBrick,SDL_Renderer* gRenderer,int *b)
{
   if (*polBrick == 0) *b  = *b+1;
   if (*polBrick == 1) *b  = *b-1;
   if (*b >= 580)  *polBrick = 1;
   if (*b <= 1)  *polBrick = 0;


  SDL_RenderDrawRect(gRenderer,&brickRect);
}

int main(void) {
 SDL_Init(SDL_INIT_VIDEO);
 SDL_Window* window = SDL_CreateWindow("moving",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,640,480,SDL_WINDOW_SHOWN); 
 SDL_Renderer *gRenderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
 SDL_Surface* dotSurface = SDL_LoadBMP("dot.bmp");
 SDL_SetColorKey(dotSurface,SDL_TRUE,SDL_MapRGB(dotSurface->format,0xFF,0xFF,0xFF));
 SDL_Texture* dotTexture = SDL_CreateTextureFromSurface(gRenderer,dotSurface);
 SDL_SetRenderDrawColor(gRenderer,0,0,0,0xFF);
 
 SDL_RenderClear(gRenderer); 
 
 SDL_SetRenderDrawColor(gRenderer,0,0xFF,0xFF,0xFF);
 int x = 20,y=20;
 int polX = 0;int polY=0;
 int polBrick = 0;
 SDL_Rect brickRect = {300,220,80,40};

 SDL_Rect pixelPos = {0,0,20,20};
// SDL_RenderDrawRect(gRenderer,&brickRect);
// SDL_RenderDrawPoint(gRenderer,x,y);
 //SDL_RenderCopy(gRenderer,dotTexture,NULL,&pixelPos); 
 SDL_RenderPresent(gRenderer);
 SDL_Event e; 
 int quit = 0;
 while(!quit)
 {
   while(SDL_PollEvent(&e) != 0)
   {
      if(e.type == SDL_QUIT) {
           quit = 1;
      }

   }
 SDL_SetRenderDrawColor(gRenderer,0,80,10,10);
 SDL_RenderClear(gRenderer); 

 SDL_SetRenderDrawColor(gRenderer,0,0xFF,0xFF,0xFF);
 brickDraw(brickRect, &polBrick,gRenderer,&(brickRect.x));
 pixelDraw(pixelPos,brickRect,gRenderer,&x,&y,&polX,&polY,dotTexture); 
 SDL_RenderPresent(gRenderer);
 SDL_Delay(5); 

}
 SDL_DestroyWindow(window);
 SDL_Quit();

}
