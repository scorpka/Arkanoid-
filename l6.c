#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_image.h>

void wallDraw(SDL_Renderer* gRenderer, SDL_Rect wall1,int *wallExist, int *x, int *y,int *scoreNumber, int i)
{
  
  if (wallExist[i] == 0) return;
 
if ( ((*x == wall1.x || *x+1 == wall1.x)  &&  *y >= wall1.y && *y <= wall1.y+wall1.h)  || (*x == wall1.x + wall1.w &&  *y -100 >= wall1.y && *y -100 <= wall1.y+wall1.h)) {
    if(wallExist[i] !=0) (*scoreNumber)++; 

    wallExist[i] = 0;
   } 

   if (( *y == wall1.y &&  *x >= wall1.x && *x <= wall1.x+wall1.w)||( *y == wall1.y + wall1.h &&  *x +1 >= wall1.x && *x +1 <= wall1.x+wall1.w)) {
    if (wallExist[i] != 0) (*scoreNumber)++;

     wallExist[i] = 0;
   }

 if (*wallExist) SDL_RenderDrawRect(gRenderer, &wall1);
 
}

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
 if (*x>640) *x = 637; 
 if (*y>480) *y = 477;

   pixelPos.x = *x;
  pixelPos.y = *y;
 SDL_RenderCopy(gRenderer,dotTexture,NULL,&pixelPos); 
 //SDL_RenderDrawPoint(gRenderer,*x,*y);
}

void brickDraw(SDL_Rect brickRect,int *polBrick,SDL_Renderer* gRenderer,int *b,SDL_Texture *barTexture)
{
   if (*polBrick == 0) *b  = *b+1;
   if (*polBrick == 1) *b  = *b-1;
   if (*b >= 580)  *polBrick = 1;
   if (*b <= 1)  *polBrick = 0;


//  SDL_RenderDrawRect(gRenderer,&brickRect);
  SDL_RenderCopy(gRenderer,barTexture,NULL,&brickRect);
}

void scoreDraw(TTF_Font* scoreFont,SDL_Renderer* gRenderer,int scoreNumber)
{
 char* scoreText; scoreText = (char*)malloc(3);
 
  *scoreText = scoreNumber +'0';

  *(scoreText+1) = '\0';
 SDL_Color textColor = {255,255,255};
  
 SDL_Surface* scoreSurface = TTF_RenderText_Solid(scoreFont,scoreText,textColor);
 SDL_Rect scoreRect = {600,5,scoreSurface->w,scoreSurface->h}; 
 SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(gRenderer,scoreSurface);

 SDL_RenderCopy(gRenderer,scoreTexture,NULL,&scoreRect);
}

int main(void) {
 SDL_Init(SDL_INIT_VIDEO);
 TTF_Init();
 SDL_Window* window = SDL_CreateWindow("moving",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,640,480,SDL_WINDOW_SHOWN); 
 SDL_Renderer *gRenderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
 SDL_Surface* barSurface = IMG_Load("sprite1.PNG");
 SDL_Surface* dotSurface = SDL_LoadBMP("dot.bmp");
 TTF_Font* scoreFont = TTF_OpenFont("v_DigitalStrip_v1.5.ttf",52);

  SDL_SetColorKey(dotSurface,SDL_TRUE,SDL_MapRGB(dotSurface->format,0xFF,0xFF,0xFF));
 SDL_Texture* dotTexture = SDL_CreateTextureFromSurface(gRenderer,dotSurface);
 SDL_Texture* barTexture = SDL_CreateTextureFromSurface(gRenderer,
barSurface);
 SDL_SetRenderDrawColor(gRenderer,0,0,0,0xFF);
 SDL_Rect wall1 = {400,100,80,40};
 SDL_RenderClear(gRenderer); 
 
 SDL_SetRenderDrawColor(gRenderer,0,0xFF,0xFF,0xFF);
 int scoreNumber = 0;
 int x = 20,y=20;
 int polX = 0;int polY=0;
 int polBrick = 0;
 int wallExist[] = {1};

 SDL_Rect brickRect = {300,220,80,40};
 SDL_Rect pixelPos = {0,0,20,20};

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
 brickDraw(brickRect, &polBrick,gRenderer,&(brickRect.x),barTexture);
 pixelDraw(pixelPos,brickRect,gRenderer,&x,&y,&polX,&polY,dotTexture); 
wallDraw( gRenderer, wall1, wallExist, &x, &y, &scoreNumber,0);

 scoreDraw(scoreFont,gRenderer,scoreNumber);
 SDL_RenderPresent(gRenderer);
 SDL_Delay(5); 

}
 
 SDL_DestroyWindow(window);
 TTF_Quit();
 SDL_Quit();

}
