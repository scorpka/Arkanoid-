/* 
 *
 *
*/

#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_image.h>

#define LVL1 0
#define MAINMENU 1
#define GAMEOVER 2
#define HEROBOARDTAB 3
#define WRITELEADER 4

#define WIDTH 800
#define HEIGHT 600

struct ball {
    int posX;
    int posY;
    int dirMoveX;
    int dirMoveY;
    int speed;
};

void writeLeaderBoardName(char *text2,SDL_RWops* fileWrite, char* fakenameLeader, int scoreHero ) {
 char *newLeaderBoard =(char*)malloc(105);
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

void heroBoardTextShow(SDL_Renderer* gRenderer,char *text2,TTF_Font* textFont) 
{
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

  SDL_Texture* textTexture = SDL_CreateTextureFromSurface(gRenderer,textSurface);

  for(int i = 0;i<8;i++) 
  {
    zapis3 = zapis3 - 13;
    textSurface = TTF_RenderText_Solid(textFont,zapis3,textColor);
    textTexture = SDL_CreateTextureFromSurface(gRenderer,textSurface);
    textRect.w = textSurface->w; textRect.h=textSurface->h;
    textRect.y = textRect.y + 50;
    SDL_RenderCopy(gRenderer,textTexture,NULL,&textRect); 
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    SDL_Delay(100);
  }

}

void wallDraw(SDL_Renderer* gRenderer,int *wallExist, int *x, int *y,int *scoreNumber, int i,int j)
{
 //TODO two basis massive 
 
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

//check hit ball with square and redirect move
void collision(struct ball *someBall, SDL_Rect brickRect,SDL_Rect controlRect) 
{
     if ( (((*someBall).posX == brickRect.x || (*someBall).posX+1 == brickRect.x)  &&  (*someBall).posY >= brickRect.y && (*someBall).posY <= brickRect.y+brickRect.h)  || (((*someBall).posX == brickRect.x + brickRect.w ||((*someBall).posX-1 == brickRect.x + brickRect.w))  &&  (*someBall).posY  >= brickRect.y && (*someBall).posY  <= brickRect.y+brickRect.h)){ (*someBall).dirMoveX = -1* ((*someBall).dirMoveX) ; if((*someBall).posX==brickRect.x  || (*someBall).posX == brickRect.x - 1){(*someBall).posX = (*someBall).posX-5;}else if ((*someBall).posX==brickRect.x+brickRect.w  || (*someBall).posX-1 == brickRect.x+brickRect.w){(*someBall).posX = (*someBall).posX +5;}}

   if (( ((*someBall).posY == brickRect.y || (*someBall).posY-1 == brickRect.y) && (*someBall).posX >= brickRect.x && (*someBall).posX <= brickRect.x+brickRect.w) || (((*someBall).posY == brickRect.y + brickRect.h || ((*someBall).posY-1 ==brickRect.y + brickRect.h)) && (*someBall).posX >= brickRect.x && (*someBall).posX <= brickRect.x+brickRect.w)){ (*someBall).dirMoveY = -1* (*someBall).dirMoveY; if((*someBall).posY==brickRect.y  || (*someBall).posY == brickRect.y - 1){(*someBall).posY = (*someBall).posY-5;}else if((*someBall).posY==brickRect.y+brickRect.h || (*someBall).posY-1 == brickRect.y+brickRect.h){(*someBall).posY =(*someBall).posY+5;}}

if ( (((*someBall).posX == controlRect.x || (*someBall).posX+1 == controlRect.x)  &&  (*someBall).posY >= controlRect.y && (*someBall).posY <= controlRect.y+controlRect.h)  || (((*someBall).posX == controlRect.x + controlRect.w ||((*someBall).posX-1 == controlRect.x + controlRect.w))  &&  (*someBall).posY  >= controlRect.y && (*someBall).posY  <= controlRect.y+controlRect.h)){ (*someBall).dirMoveX = -1* (*someBall).dirMoveX; if((*someBall).posX==controlRect.x  || (*someBall).posX == controlRect.x - 1){(*someBall).posX = (*someBall).posX-5;}else if ((*someBall).posX==controlRect.x+controlRect.w  || (*someBall).posX-1 == controlRect.x+controlRect.w){(*someBall).posX = (*someBall).posX +5;}}

   if (( ((*someBall).posY == controlRect.y || (*someBall).posY-1 == controlRect.y) && (*someBall).posX >= controlRect.x && (*someBall).posX <= controlRect.x+controlRect.w) || (((*someBall).posY == controlRect.y + controlRect.h || ((*someBall).posY-1 ==controlRect.y + controlRect.h)) && (*someBall).posX >= controlRect.x && (*someBall).posX <= controlRect.x+controlRect.w)){ (*someBall).dirMoveY = -1* (*someBall).dirMoveY; if((*someBall).posY==controlRect.y  || (*someBall).posY == controlRect.y - 1){(*someBall).posY = (*someBall).posY-5;}else if((*someBall).posY==controlRect.y+controlRect.h || (*someBall).posY-1 == controlRect.y+controlRect.h){(*someBall).posY =(*someBall).posY+5;}}


}
//drawBall and calculate collision
//

void pixelDraw(SDL_Rect pixelPos,SDL_Rect brickRect,SDL_Renderer* gRenderer,struct ball *someBall, SDL_Texture* dotTexture, SDL_Texture* redTexture, SDL_Texture* greenTexture, SDL_Texture* blueTexture,SDL_Rect controlRect,int *mainTheme)
{
  if ((*someBall).posY == 598) {
    *mainTheme = 2; return;
  }
  SDL_Texture* RGB_Texture = NULL;
   (*someBall).posX = (*someBall).posX+(*someBall).dirMoveX;
   (*someBall).posY = (*someBall).posY+(*someBall).dirMoveY;
   if ( (*someBall).posX == WIDTH - 1){ (*someBall).dirMoveX =-1; }else if((*someBall).posX == 1){(*someBall).dirMoveX = 1;};
   if ( (*someBall).posY == HEIGHT - 1){ (*someBall).dirMoveY =-1; }else if((*someBall).posY == 1){(*someBall).dirMoveY = 1;};

  collision( someBall, brickRect, controlRect);

 if ((*someBall).posX>WIDTH) (*someBall).posX = WIDTH -3; 
 if ((*someBall).posY>HEIGHT) (*someBall).posY = HEIGHT -3;

  pixelPos.x = (*someBall).posX;
  pixelPos.y = (*someBall).posY;
   
 SDL_RenderCopy(gRenderer,dotTexture,NULL,&pixelPos); 

  //added colored way after pixel
 if ((*someBall).dirMoveX == -1) pixelPos.x = (*someBall).posX + 5+(rand()%25);;
 if ((*someBall).dirMoveY == -1) pixelPos.y = (*someBall).posY + 5+(rand()%25);;
 if ((*someBall).dirMoveX == 1) pixelPos.x = (*someBall).posX + 5-(rand()%25);;
 if ((*someBall).dirMoveY == 1) pixelPos.y = (*someBall).posY + 5-(rand()%25);;
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
  SDL_RenderCopy(gRenderer,barTexture,NULL,&controlRect);
}

void scoreDraw(TTF_Font* scoreFont,SDL_Renderer* gRenderer,int scoreNumber)
{
  char* scoreText; scoreText = (char*)malloc(4);
 
  if (scoreNumber >= 10) {  
    *(scoreText+1) = scoreNumber%10 +'0';
    *(scoreText) = (scoreNumber/10)%10+'0';
    *(scoreText+2) = '\0';
  }else {
  *scoreText = scoreNumber +'0';
  *(scoreText+1) = '\0';
  }
  SDL_Color textColor = {255,255,255};
  
 SDL_Surface* scoreSurface = TTF_RenderText_Solid(scoreFont,scoreText,textColor);
 SDL_Rect scoreRect = {WIDTH -60,5,scoreSurface->w,scoreSurface->h}; 
 SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(gRenderer,scoreSurface);

 SDL_RenderCopy(gRenderer,scoreTexture,NULL,&scoreRect);
}

void finalCreate(int scoreNumber,SDL_Renderer* gRenderer,SDL_Texture* finalTexture,int quit, int *finalNumber, SDL_Rect brickRect,int *wallExist, int  *x, int *y,SDL_Rect pixelPos) {
         for (int i=0;i<=18;i++){ wallExist[i] = 1;}

          brickRect.x =300;brickRect.y=220;brickRect.w=80;brickRect.h=40;
 //         scoreNumber++;
          *x = 30; *y=30;    
          pixelPos.x=0;pixelPos.y=0;pixelPos.w=20;pixelPos.h=20;

//        SDL_RenderCopy(gRenderer,finalTexture,NULL,NULL);
//        SDL_RenderPresent(gRenderer);
//        quit = 1;
//  }


}




int main(void) {
 SDL_Init(SDL_INIT_VIDEO);
 TTF_Init();
 SDL_Window* window = SDL_CreateWindow("moving",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,WIDTH,HEIGHT,SDL_WINDOW_SHOWN); 
 SDL_Renderer *gRenderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

 SDL_Surface* barSurface = IMG_Load("image/sprite1.PNG");
 SDL_Surface* finalSurface = IMG_Load("image/youwin.jpg");
 SDL_Surface* dotSurface = SDL_LoadBMP("image/dot.bmp");
 SDL_Surface* redSurface = SDL_LoadBMP("image/red.bmp");
 SDL_Surface* greenSurface = SDL_LoadBMP("image/green1.bmp");
 SDL_Surface* blueSurface = SDL_LoadBMP("image/blue.bmp");

 TTF_Font* scoreFont = TTF_OpenFont("fonts/v_DigitalStrip_v1.5.ttf",52);
 TTF_Font* mainFont = TTF_OpenFont("fonts/IrinaCTT.ttf",70);

 SDL_SetColorKey(dotSurface,SDL_TRUE,SDL_MapRGB(dotSurface->format,0,0xFF,0xFF));
 SDL_SetColorKey(redSurface,SDL_TRUE,SDL_MapRGB(redSurface->format,0,0xFF,0xFF));
 SDL_SetColorKey(greenSurface,SDL_TRUE,SDL_MapRGB(greenSurface->format,0xFF,0xFF,0xFF));
 SDL_SetColorKey(blueSurface,SDL_TRUE,SDL_MapRGB(blueSurface->format,0,0xFF,0xFF));

 SDL_Texture* dotTexture = SDL_CreateTextureFromSurface(gRenderer,dotSurface);
 SDL_Texture* barTexture = SDL_CreateTextureFromSurface(gRenderer,barSurface);
 SDL_Texture* redTexture = SDL_CreateTextureFromSurface(gRenderer,redSurface);
 SDL_Texture* greenTexture = SDL_CreateTextureFromSurface(gRenderer, greenSurface);
 SDL_Texture* blueTexture = SDL_CreateTextureFromSurface(gRenderer,blueSurface);
 SDL_Texture* finalTexture = SDL_CreateTextureFromSurface(gRenderer,finalSurface);

 SDL_FreeSurface(blueSurface);
 SDL_FreeSurface(greenSurface);
 SDL_FreeSurface(redSurface);
 SDL_FreeSurface(dotSurface);
 SDL_FreeSurface(finalSurface);
 SDL_FreeSurface(barSurface);

 SDL_SetRenderDrawColor(gRenderer,0,0,0,0xFF);
 SDL_RenderClear(gRenderer); 
 
 SDL_SetRenderDrawColor(gRenderer,0,0xFF,0xFF,0xFF);
 //this is score
 int scoreNumber = 0;
 int finalNumber = 0;
 //this is first position
 int polBrick = 0;
 int wallExist[]= {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,};
struct ball firstBall;
firstBall.dirMoveX=1; firstBall.dirMoveY=1;
firstBall.posX = 20, firstBall.posY =20;

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
  SDL_RWops* fileWrite = SDL_RWFromFile("data/nums2.bin","w");
  SDL_RWops* fileRead = SDL_RWFromFile("data/nums.bin","r+b"); 
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
    if (mainTheme == MAINMENU ) {
      
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
   }else if (mainTheme == LVL1 ) {
   while(SDL_PollEvent(&e) != 0)
   {
      if(e.type == SDL_QUIT) {
           quit = 1;
      }else if(e.type == SDL_KEYDOWN) {
       if (e.key.keysym.sym == SDLK_1) { 
          for (int i=0;i<=18;i++){ wallExist[i] = 1;}

          brickRect.x =300;brickRect.y=220;brickRect.w=80;brickRect.h=40;
          scoreNumber = 0;
          firstBall.posX  = 20; firstBall.posY =20;    
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
   
  if (scoreNumber % 18 == 0 && scoreNumber != 0 ){
 finalCreate(scoreNumber,gRenderer,finalTexture,quit,&scoreNumber,brickRect, wallExist,&firstBall.posX ,&firstBall.posY ,pixelPos);
 scoreNumber++;
  }
 SDL_SetRenderDrawColor(gRenderer,0,80,10,10);
 SDL_RenderClear(gRenderer); 
 
 SDL_SetRenderDrawColor(gRenderer,0,0xFF,0xFF,0xFF);

 brickDraw(brickRect, &polBrick,gRenderer,&(brickRect.x),barTexture);

 controlDraw(controlRect, &polBrick,gRenderer,&(controlRect.x),barTexture);
 pixelDraw(pixelPos,brickRect,gRenderer,&firstBall,dotTexture,redTexture,greenTexture,blueTexture,controlRect,&mainTheme); 

 for (int i = 0; i<9;i++) 
 {
   for (int j = 0;j<2;j++)
 wallDraw( gRenderer,wallExist, &firstBall.posX , &firstBall.posY , &scoreNumber,i,j);

 }

 scoreDraw(scoreFont,gRenderer,scoreNumber);
 SDL_RenderPresent(gRenderer);
 SDL_Delay(4); 

 }else if(mainTheme == GAMEOVER) {
 
    for (int i=0;i<=18;i++){ wallExist[i] = 1;}

    brickRect.x =300;brickRect.y=220;brickRect.w=80;brickRect.h=40;
    scoreNumber = 0;
    firstBall.posX  = 20; firstBall.posY =20;    
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
  }else if( mainTheme == HEROBOARDTAB ) {
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
 }else if( mainTheme == WRITELEADER ) {

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
