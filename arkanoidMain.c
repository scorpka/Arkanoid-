#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_image.h>
#define WIDTH 800
#define HEIGHT 600

void writeLeaderBoardName(char *text2,SDL_RWops* fileWrite, char* fakenameLeader, int scoreHero ) {
 char *newLeaderBoard =(char*)malloc(105);
// char *fakenameLeader = "lukan     " ;
 int counter = 1, hiddenChecker = 0, solo = 0;
  while (counter <=105) 
  {
    if ((counter-11)%13 == 0 && counter != 0) {
     hiddenChecker = (*text2-'0')*10 + (*(text2+1)-'0');
     if ((hiddenChecker <= scoreHero) && solo == 0) {
            newLeaderBoard-=11;
            text2-=11;counter-=11;
             *newLeaderBoard = '\n'; 
             newLeaderBoard++;counter++;
            while(*fakenameLeader) {
              *newLeaderBoard = *fakenameLeader;
              newLeaderBoard++; fakenameLeader++;counter++;
            }
            //added number to string
            *newLeaderBoard = (scoreHero -scoreHero%10)/10  +'0'; 
            newLeaderBoard++;counter++;
            *newLeaderBoard = scoreHero%10  +'0'; 
            newLeaderBoard++;counter++;
            
            solo++;
      if (solo) printf("%i\n",counter);
     };
    }
    *newLeaderBoard =  *text2;
    counter++; newLeaderBoard++;text2++;
  }
  counter--;
  newLeaderBoard -=counter;
 SDL_RWwrite( fileWrite,newLeaderBoard , 1, counter-1);   
}

void heroBoardTextShow(SDL_Renderer* gRenderer,char *text2,TTF_Font* textFont) {
char *zapis3 = (char*)malloc(105);
int checker = 0;
 for (int i = 0;i<104;i++)
   {
     *zapis3 = *text2;
    if (*text2 == '\n') {
    *zapis3 = '\0';
    }
    zapis3++; text2++; 
    
     checker++;
      
   }   
    
  SDL_Color textColor = {255,0,0};

  SDL_Rect textRect = { 200,100,100,20};
  SDL_Surface* textSurface = NULL;
//  SDL_Rect textPosition = {5,450,100,20};
  SDL_Texture* textTexture = SDL_CreateTextureFromSurface(gRenderer,textSurface);
//SDL_RenderCopy(gRenderer,textTexture,NULL,&textRect); 
for(int i = 0;i<8;i++) {
zapis3 = zapis3 - 13;
textSurface = TTF_RenderText_Solid(textFont,zapis3,textColor);
textTexture = SDL_CreateTextureFromSurface(gRenderer,textSurface);
textRect.w = textSurface->w; textRect.h=textSurface->h;
textRect.y = textRect.y + 50;
SDL_RenderCopy(gRenderer,textTexture,NULL,&textRect); 

SDL_Delay(1);
}
}

void wallDraw(SDL_Renderer* gRenderer,int *wallExist, int *x, int *y,int *scoreNumber, int i,int j)
{
 //TODO two basis massive 
 // if (wallExist[i] == 0) return;
 
 SDL_Rect wall1 = {700-(i*80),100-(j*30),64,22};
  if (j == 1) i = i+9;

if ( ((*x == wall1.x || *x+1 == wall1.x)  &&  *y >= wall1.y && *y <= wall1.y+wall1.h)  || (*x == wall1.x + wall1.w &&  *y  >= wall1.y && *y  <= wall1.y+wall1.h)) {

    if(wallExist[i] !=0) (*scoreNumber)++; 

    wallExist[i] = 0;
   } 

   if (( *y == wall1.y &&  *x >= wall1.x && *x <= wall1.x+wall1.w)||( *y == wall1.y + wall1.h &&  *x +1 >= wall1.x && *x +1 <= wall1.x+wall1.w)) {
    if (wallExist[i] != 0) (*scoreNumber)++;

     wallExist[i] = 0;
   }

 if (wallExist[i]) { 
   SDL_RenderDrawLine(gRenderer,wall1.x,wall1.y,wall1.x+wall1.w,wall1.y);
   SDL_RenderDrawLine(gRenderer,wall1.x,wall1.y,wall1.x,wall1.y+wall1.h);
   SDL_RenderDrawLine(gRenderer,wall1.x+wall1.w,wall1.y,wall1.x+wall1.w,wall1.y+wall1.h);
   SDL_RenderDrawLine(gRenderer,wall1.x,wall1.y+wall1.h,wall1.x+wall1.w,wall1.y+wall1.h);
 }
 
}

void pixelDraw(SDL_Rect pixelPos,SDL_Rect brickRect,SDL_Renderer* gRenderer,int *x,int *y,int *polX,int *polY,SDL_Texture* dotTexture, SDL_Texture* redTexture, SDL_Texture* greenTexture, SDL_Texture* blueTexture,SDL_Rect controlRect,int *mainTheme)
{
  if (*y == 598) {
    *mainTheme = 2; return;
  }
  SDL_Texture* RGB_Texture = NULL;
   if (*polX == 0) *x = *x+1;
   if (*polY == 0) *y = *y+1;
   if ( *x == WIDTH - 1){ *polX =1; }else if(*x == 1){*polX = 0;};
   if ( *y == HEIGHT - 1){ *polY =1; }else if(*y == 1){*polY = 0;};
   //collision
   //TODO make function collision;
   if ( ((*x == brickRect.x || *x+1 == brickRect.x)  &&  *y >= brickRect.y && *y <= brickRect.y+brickRect.h)  || ((*x == brickRect.x + brickRect.w ||(*x-1 == brickRect.x + brickRect.w))  &&  *y  >= brickRect.y && *y  <= brickRect.y+brickRect.h)){ *polX = !(*polX); if(*x==brickRect.x  || *x == brickRect.x - 1){*x = *x-5;}else if (*x==brickRect.x+brickRect.w  || *x-1 == brickRect.x+brickRect.w){*x = *x +5;}} 

   if (( (*y == brickRect.y || *y-1 == brickRect.y) && *x >= brickRect.x && *x <= brickRect.x+brickRect.w) || ((*y == brickRect.y + brickRect.h || (*y-1 ==brickRect.y + brickRect.h)) && *x >= brickRect.x && *x <= brickRect.x+brickRect.w)){ *polY = !*polY; if(*y==brickRect.y  || *y == brickRect.y - 1){*y = *y-5;}else if(*y==brickRect.y+brickRect.h || *y-1 == brickRect.y+brickRect.h){*y =*y+5;}} 
   
if ( ((*x == controlRect.x || *x+1 == controlRect.x)  &&  *y >= controlRect.y && *y <= controlRect.y+controlRect.h)  || ((*x == controlRect.x + controlRect.w ||(*x-1 == controlRect.x + controlRect.w))  &&  *y  >= controlRect.y && *y  <= controlRect.y+controlRect.h)){ *polX = !(*polX); if(*x==controlRect.x  || *x == controlRect.x - 1){*x = *x-5;}else if (*x==controlRect.x+controlRect.w  || *x-1 == controlRect.x+controlRect.w){*x = *x +5;}} 

   if (( (*y == controlRect.y || *y-1 == controlRect.y) && *x >= controlRect.x && *x <= controlRect.x+controlRect.w) || ((*y == controlRect.y + controlRect.h || (*y-1 ==controlRect.y + controlRect.h)) && *x >= controlRect.x && *x <= controlRect.x+controlRect.w)){ *polY = !*polY; if(*y==controlRect.y  || *y == controlRect.y - 1){*y = *y-5;}else if(*y==controlRect.y+controlRect.h || *y-1 == controlRect.y+controlRect.h){*y =*y+5;}} 

   if (*polX == 1) *x = *x-1;
   if (*polY == 1) *y = *y-1;

   //fixed bug: throw behind play zone
 if (*x>WIDTH) *x = WIDTH -3; 
 if (*y>HEIGHT) *y = HEIGHT -3;

  pixelPos.x = *x;
  pixelPos.y = *y;
   
 SDL_RenderCopy(gRenderer,dotTexture,NULL,&pixelPos); 
  //added colored way after pixel
 if (*polX == 1) pixelPos.x = *x + 5+(rand()%25);;
 if (*polY == 1) pixelPos.y = *y + 5+(rand()%25);;
 if (*polX == 0) pixelPos.x = *x + 5-(rand()%25);;
 if (*polY == 0) pixelPos.y = *y + 5-(rand()%25);;
  pixelPos.h = pixelPos.h/3+1;
  pixelPos.w = pixelPos.w/3+1;
  switch( rand() %3)
  {
    case 0: RGB_Texture = redTexture;
            break;
    case 1: RGB_Texture = greenTexture;
            break;
    case 2: RGB_Texture = blueTexture;
            break;
  }
  
 // SDL_SetTextureAlphaMod(redTexture,iRand);

SDL_RenderCopy(gRenderer,RGB_Texture,NULL,&pixelPos); 

}

void brickDraw(SDL_Rect brickRect,int *polBrick,SDL_Renderer* gRenderer,int *b,SDL_Texture *barTexture)
{
   if (*polBrick == 0) *b  = *b+1;
   if (*polBrick == 1) *b  = *b-1;
   if (*b >= (WIDTH-60))  *polBrick = 1;
   if (*b <= 1)  *polBrick = 0;

  SDL_RenderCopy(gRenderer,barTexture,NULL,&brickRect);
}

void controlDraw(SDL_Rect controlRect,int *polBrick,SDL_Renderer* gRenderer,int *b,SDL_Texture *barTexture)
{
  // if (*polBrick == 0) *b  = *b+1;
  // if (*polBrick == 1) *b  = *b-1;
  // if (*b >= (WIDTH-60))  *polBrick = 1;
  // if (*b <= 1)  *polBrick = 0;

   SDL_RenderCopy(gRenderer,barTexture,NULL,&controlRect);
}

void scoreDraw(TTF_Font* scoreFont,SDL_Renderer* gRenderer,int scoreNumber)
{
  char* scoreText; scoreText = (char*)malloc(4);
 
  if (scoreNumber >= 10) {  
    *(scoreText+1) = scoreNumber%10 +'0';
    *(scoreText) = (scoreNumber/10)%10+'0';
    *(scoreText+2) = '\0';
  }else{
  *scoreText = scoreNumber +'0';
  *(scoreText+1) = '\0';
  }
 SDL_Color textColor = {255,255,255};
  
 SDL_Surface* scoreSurface = TTF_RenderText_Solid(scoreFont,scoreText,textColor);
 SDL_Rect scoreRect = {WIDTH -60,5,scoreSurface->w,scoreSurface->h}; 
 SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(gRenderer,scoreSurface);

 SDL_RenderCopy(gRenderer,scoreTexture,NULL,&scoreRect);
}

void finalCreate(int scoreNumber,SDL_Renderer* gRenderer,SDL_Texture* finalTexture,int quit) {
  if (scoreNumber >= 18){
        SDL_RenderCopy(gRenderer,finalTexture,NULL,NULL);
        SDL_RenderPresent(gRenderer);
        quit = 1;
  }


}

int main(void) {
 SDL_Init(SDL_INIT_VIDEO);
 TTF_Init();
 SDL_Window* window = SDL_CreateWindow("moving",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,WIDTH,HEIGHT,SDL_WINDOW_SHOWN); 
 SDL_Renderer *gRenderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

 SDL_Surface* barSurface = IMG_Load("sprite1.PNG");
 SDL_Surface* finalSurface = IMG_Load("youwin.jpg");
 SDL_Surface* dotSurface = SDL_LoadBMP("dot.bmp");
 SDL_Surface* redSurface = SDL_LoadBMP("red.bmp");
 SDL_Surface* greenSurface = SDL_LoadBMP("green1.bmp");
 SDL_Surface* blueSurface = SDL_LoadBMP("blue.bmp");

 TTF_Font* scoreFont = TTF_OpenFont("v_DigitalStrip_v1.5.ttf",52);
 TTF_Font* mainFont = TTF_OpenFont("IrinaCTT.ttf",70);
  SDL_SetColorKey(dotSurface,SDL_TRUE,SDL_MapRGB(dotSurface->format,0xFF,0xFF,0xFF));
  SDL_SetColorKey(redSurface,SDL_TRUE,SDL_MapRGB(redSurface->format,0,0xFF,0xFF));
  SDL_SetColorKey(greenSurface,SDL_TRUE,SDL_MapRGB(greenSurface->format,0xFF,0xFF,0xFF));
  SDL_SetColorKey(blueSurface,SDL_TRUE,SDL_MapRGB(blueSurface->format,0,0xFF,0xFF));

 SDL_Texture* dotTexture = SDL_CreateTextureFromSurface(gRenderer,dotSurface);
 SDL_Texture* barTexture = SDL_CreateTextureFromSurface(gRenderer,barSurface);
 SDL_Texture* redTexture = SDL_CreateTextureFromSurface(gRenderer,redSurface);
 SDL_Texture* greenTexture = SDL_CreateTextureFromSurface(gRenderer, greenSurface);
 SDL_Texture* blueTexture = SDL_CreateTextureFromSurface(gRenderer,blueSurface);
 SDL_Texture* finalTexture = SDL_CreateTextureFromSurface(gRenderer,finalSurface);

 SDL_SetRenderDrawColor(gRenderer,0,0,0,0xFF);
 SDL_RenderClear(gRenderer); 
 
 SDL_SetRenderDrawColor(gRenderer,0,0xFF,0xFF,0xFF);
 int scoreNumber = 0;
 int x = 20,y=20;
 int polX = 0;int polY=0;
 int polBrick = 0;
 int wallExist[]= {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,};

 SDL_Rect brickRect = {300,220,80,40};
 SDL_Rect pixelPos = {0,0,20,20};
 SDL_Rect controlRect = {400,520,80,20};

 SDL_RenderPresent(gRenderer);
 SDL_Event e; 
 int quit = 0;
 int mouseMotionY = HEIGHT/2, mouseMotionX = WIDTH/2;
 int mousePositionY =HEIGHT/2, mousePositionX =WIDTH/2;
 int mainTheme = 1; int mainThemePosition = -1;
 char* newGameText = "New game";
 char* leaderBoardText = "leaderBoard";
 char* exitText = "exit";
 char* gameOverText ="game over";
 char* playAgainText ="play Again?"; 
 char* heroBoardText ="HEROES:";
 char* text2 = (char*)malloc(105); 
 
  SDL_Color mainTextColor = {255,255,255};
 //ReadScoreBoard
  SDL_RWops* fileWrite = SDL_RWFromFile("nums2.bin","w");
  SDL_RWops* fileRead = SDL_RWFromFile("nums.bin","r+b"); 
  SDL_RWread(fileRead,text2,1,104); 
   //new game 
     SDL_Surface* newGameSurface = TTF_RenderText_Solid(mainFont,newGameText,mainTextColor);
     //TODO correct 580 and 500 to newGameSurface.h
     SDL_Rect newGameRect = {WIDTH -580,HEIGHT - 500,newGameSurface->w,newGameSurface->h}; 
     SDL_Texture* newGameTexture = SDL_CreateTextureFromSurface(gRenderer,newGameSurface);
//leaderboard
     SDL_Surface* leaderBoardSurface = TTF_RenderText_Solid(mainFont,leaderBoardText,mainTextColor);
     SDL_Rect leaderBoardRect = {WIDTH -580,HEIGHT - 400,leaderBoardSurface->w,leaderBoardSurface->h}; 
     SDL_Texture* leaderBoardTexture = SDL_CreateTextureFromSurface(gRenderer,leaderBoardSurface);

//exit
     SDL_Surface* exitSurface = TTF_RenderText_Solid(mainFont,exitText,mainTextColor);
     SDL_Rect exitRect = {WIDTH -480,HEIGHT - 300,exitSurface->w,exitSurface->h}; 
     SDL_Texture* exitTexture = SDL_CreateTextureFromSurface(gRenderer,exitSurface);
//game over
     SDL_Surface* gameOverSurface = TTF_RenderText_Solid(mainFont,gameOverText,mainTextColor);
     SDL_Rect gameOverRect = {WIDTH -580,HEIGHT - 500,gameOverSurface->w,gameOverSurface->h}; 
     SDL_Texture* gameOverTexture = SDL_CreateTextureFromSurface(gRenderer,gameOverSurface);
    char* yourName =(char*)malloc(10);
    int lengthName = 0;
// play again
     SDL_Surface* playAgainSurface = TTF_RenderText_Solid(mainFont,playAgainText,mainTextColor);
     SDL_Rect playAgainRect = {WIDTH -580,HEIGHT - 300,playAgainSurface->w,playAgainSurface->h}; 
     SDL_Texture* playAgainTexture = SDL_CreateTextureFromSurface(gRenderer,playAgainSurface);
//HEROBOARD:
    SDL_Surface* heroBoardSurface = TTF_RenderText_Solid(mainFont,heroBoardText,mainTextColor);
     SDL_Rect heroBoardRect = {WIDTH -500,HEIGHT - 580,heroBoardSurface->w,heroBoardSurface->h}; 
     SDL_Texture* heroBoardTexture = SDL_CreateTextureFromSurface(gRenderer,heroBoardSurface);


 while(!quit)
 {
   if (mainTheme == 1) {
      

           while(SDL_PollEvent(&e) != 0)
       {
            if(e.type == SDL_QUIT) {
                quit = 1;
            }else if(e.type == SDL_KEYDOWN) {
             if(e.key.keysym.sym == SDLK_DOWN ) {
                 if (mainThemePosition <= 1){
                    mainThemePosition++;
                 }else {   
                    mainThemePosition = 0;
                 }
              if (mainThemePosition == 0){
                 SDL_SetTextureColorMod(newGameTexture,0,255,0);
                 SDL_SetTextureColorMod(exitTexture,255,255,255);
                 continue;
              }else if (mainThemePosition == 1){
                 SDL_SetTextureColorMod(newGameTexture,255,255,255);
                 SDL_SetTextureColorMod(leaderBoardTexture,0 ,255, 0 );
                 continue;

            }else if (mainThemePosition == 2){
                 SDL_SetTextureColorMod(leaderBoardTexture,255,255,255);
                 SDL_SetTextureColorMod(exitTexture,0,255,0);
                 continue;
              }

             }else if (e.key.keysym.sym == SDLK_UP) {
                 if (mainThemePosition >= 1 ){
                    mainThemePosition--;
                 }else {   
                    mainThemePosition = 2;
                 }
                 if (mainThemePosition == 0){
                   SDL_SetTextureColorMod(newGameTexture,0,255,0);
                   SDL_SetTextureColorMod(leaderBoardTexture,255,255,255);
                 continue;
                 }else if (mainThemePosition == 1){
                   SDL_SetTextureColorMod(exitTexture,255,255,255);
                   SDL_SetTextureColorMod(leaderBoardTexture,0 ,255, 0 );
                 continue;

                 }else if (mainThemePosition == 2){
                 SDL_SetTextureColorMod(newGameTexture,255,255,255);
                 SDL_SetTextureColorMod(exitTexture,0,255,0);
                 continue;
              }
             }else if (e.key.keysym.sym == SDLK_RETURN) {
                 if (mainThemePosition == 0) mainTheme = 0; 
                 if (mainThemePosition == 1) mainTheme = 3; 
                 if (mainThemePosition == 2) quit  = 1; 
                 continue;
             }
              
       }else if(e.type == SDL_MOUSEMOTION) {
       SDL_GetMouseState(&mouseMotionX,&mouseMotionY);           
       //changeColorText
               if(WIDTH -580 < mouseMotionX && mouseMotionX  < (WIDTH -580+(newGameSurface->w)) && (HEIGHT - 500) < mouseMotionY &&  mouseMotionY < ((HEIGHT-500)+ newGameSurface->h)  ) {
                 SDL_SetTextureColorMod(newGameTexture,0,255,0);
               }else  SDL_SetTextureColorMod(newGameTexture,255,255,255);

               if(WIDTH -580 < mouseMotionX && mouseMotionX  < (WIDTH -580+(leaderBoardSurface->w)) && (HEIGHT - 400) < mouseMotionY &&  mouseMotionY < ((HEIGHT-400)+ leaderBoardSurface->h)  ) {
                 SDL_SetTextureColorMod(leaderBoardTexture,0,255,0);
               }else  SDL_SetTextureColorMod(leaderBoardTexture,255,255,255);

               if(WIDTH -480 < mouseMotionX && mouseMotionX  < (WIDTH -480+(exitSurface->w)) && (HEIGHT - 300) < mouseMotionY &&  mouseMotionY < ((HEIGHT-300)+ exitSurface->h)  ){ 
                 SDL_SetTextureColorMod(exitTexture,0,255,0);
               }else  SDL_SetTextureColorMod(exitTexture,255,255,255);

//mouse down

            }else if(e.type == SDL_MOUSEBUTTONDOWN) {
               if(WIDTH -580 < mouseMotionX && mouseMotionX  < (WIDTH -580+(newGameSurface->w)) && (HEIGHT - 500) < mouseMotionY &&  mouseMotionY < ((HEIGHT-500)+ newGameSurface->h)  ) mainTheme = 0; 

               if(WIDTH -580 < mouseMotionX && mouseMotionX  < (WIDTH -580+(leaderBoardSurface->w)) && (HEIGHT - 400) < mouseMotionY &&  mouseMotionY < ((HEIGHT-400)+ leaderBoardSurface->h)  ) mainTheme = 3; 
               if(WIDTH -480 < mouseMotionX && mouseMotionX  < (WIDTH -480+(exitSurface->w)) && (HEIGHT - 300) < mouseMotionY &&  mouseMotionY < ((HEIGHT-300)+ exitSurface->h)  ) quit = 1; 
            
            }
     SDL_SetRenderDrawColor(gRenderer,0,0,0,0);
     SDL_RenderClear(gRenderer); 

     SDL_RenderCopy(gRenderer,newGameTexture,NULL,&newGameRect);
     SDL_RenderCopy(gRenderer,leaderBoardTexture,NULL,&leaderBoardRect);
     SDL_RenderCopy(gRenderer,exitTexture,NULL,&exitRect);

     SDL_RenderPresent(gRenderer);
       }
   }else if (mainTheme == 0 ) {
   while(SDL_PollEvent(&e) != 0)
   {
      if(e.type == SDL_QUIT) {
           quit = 1;
      }else if(e.type == SDL_KEYDOWN) {
       if (e.key.keysym.sym == SDLK_1) { 
          for (int i=0;i<=18;i++){ wallExist[i] = 1;}

          brickRect.x =300;brickRect.y=220;brickRect.w=80;brickRect.h=40;
          scoreNumber = 0;
          x = 20; y=20;    
          pixelPos.x=0;pixelPos.y=0;pixelPos.w=20;pixelPos.h=20;
      
      }else if(e.key.keysym.sym == SDLK_RIGHT) {
             if(controlRect.x < WIDTH -controlRect.w)  controlRect.x = controlRect.x+40; 
             }else if(e.key.keysym.sym == SDLK_LEFT) {
             if (controlRect.x > 0)  controlRect.x = controlRect.x-40; 
             }

      }else if(e.type == SDL_MOUSEMOTION) {
       SDL_GetMouseState(&mouseMotionX,&mouseMotionY);
        if (mouseMotionX > mousePositionX) {
          if(controlRect.x < WIDTH -controlRect.w)  controlRect.x = controlRect.x+5; 
                mousePositionX = mouseMotionX;
        }else if(mouseMotionX < mousePositionX) {
              if (controlRect.x > 0)  controlRect.x = controlRect.x-5; 

                mousePositionX = mouseMotionX;
        }
      }
   }
   
 SDL_SetRenderDrawColor(gRenderer,0,80,10,10);
 SDL_RenderClear(gRenderer); 
 
 SDL_SetRenderDrawColor(gRenderer,0,0xFF,0xFF,0xFF);
 brickDraw(brickRect, &polBrick,gRenderer,&(brickRect.x),barTexture);

 controlDraw(controlRect, &polBrick,gRenderer,&(controlRect.x),barTexture);
 pixelDraw(pixelPos,brickRect,gRenderer,&x,&y,&polX,&polY,dotTexture,redTexture,greenTexture,blueTexture,controlRect,&mainTheme); 

 for (int i = 0; i<9;i++) 
 {
   for (int j = 0;j<2;j++)
 wallDraw( gRenderer,wallExist, &x, &y, &scoreNumber,i,j);
 }

 scoreDraw(scoreFont,gRenderer,scoreNumber);
 finalCreate(scoreNumber,gRenderer,finalTexture,quit);
 SDL_RenderPresent(gRenderer);
 SDL_Delay(5); 
   }else if(mainTheme == 2) {
 
          for (int i=0;i<=18;i++){ wallExist[i] = 1;}

          brickRect.x =300;brickRect.y=220;brickRect.w=80;brickRect.h=40;
          scoreNumber = 0;
          x = 20; y=20;    
          pixelPos.x=0;pixelPos.y=0;pixelPos.w=20;pixelPos.h=20;
      

     SDL_SetRenderDrawColor(gRenderer,0,0,0,0);
     SDL_RenderClear(gRenderer);
     SDL_RenderCopy(gRenderer,gameOverTexture,NULL,&gameOverRect);
     SDL_RenderCopy(gRenderer,playAgainTexture,NULL,&playAgainRect);
     SDL_RenderPresent(gRenderer);
    while(SDL_PollEvent(&e) != 0)
   {
      if(e.type == SDL_QUIT) {
           quit = 1;
      }else if(e.type == SDL_KEYDOWN || e.type == SDL_MOUSEBUTTONDOWN) {
                mainTheme = 1;
      }
    }
 }else if(mainTheme == 3) {
     SDL_SetRenderDrawColor(gRenderer,0,0,0,0);
     SDL_RenderClear(gRenderer);
     SDL_RenderCopy(gRenderer,heroBoardTexture,NULL,&heroBoardRect);

     heroBoardTextShow(gRenderer,text2,scoreFont);
     SDL_RenderPresent(gRenderer);
    while(SDL_PollEvent(&e) != 0)
   {
      if(e.type == SDL_QUIT) {
           quit = 1;
      }else if(e.type == SDL_KEYDOWN || e.type == SDL_MOUSEBUTTONDOWN) {
                mainTheme = 1;
     }
   }
//writeYourName
 }else if(mainTheme == 4) {
      SDL_SetRenderDrawColor(gRenderer,0,0,0,0);
     SDL_RenderClear(gRenderer);
     SDL_RenderCopy(gRenderer,heroBoardTexture,NULL,&heroBoardRect);

     heroBoardTextShow(gRenderer,text2,scoreFont);
     SDL_RenderPresent(gRenderer);
     SDL_StartTextInput();
    while(SDL_PollEvent(&e) != 0)
   {
      if(e.type == SDL_QUIT) {
           quit = 1;
      }else if(e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym ==SDLK_ESCAPE){ 
              if (lengthName != 0) {
                while(lengthName < 10)
                {
                       *yourName=' ';
                        yourName++;lengthName++;

               }
                  yourName -=lengthName;
                  int scoreHero = 47;
                  writeLeaderBoardName(text2, fileWrite, yourName,scoreHero);

              }
                mainTheme = 1;

            }
     }else if(e.type == SDL_TEXTINPUT) {
        *yourName = *e.text.text;
        yourName++;lengthName++;
     }
   } 
    SDL_StopTextInput();
 }
} 
 SDL_RWclose(fileRead);
 TTF_Quit();
 SDL_DestroyWindow(window);
 SDL_Quit();

}
