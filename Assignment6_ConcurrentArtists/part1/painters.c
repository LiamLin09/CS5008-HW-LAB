// CS 5008 ASSIGNMENT 6
// Author: Nianlong Lin
// Date: 11/16/2023

// ===================== 包含库 =====================
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

// ===================== 设置画布 =====================
#define CANVAS_WIDTH 256
#define CANVAS_HEIGHT 256

// my canvas is shared memeory accessible by each artist.
// each pixel has three color components: red, green, and blue.
// since we want to only one artist to work on a pixel at a time,
// each pixel also has a lock.
typedef struct pixel{
    int r,g,b;
    pthread_mutex_t lock;
}pixel_t;

// create canvas as a global variable.
// this canvas will be shared among all threads.
pixel_t canvas[CANVAS_WIDTH][CANVAS_HEIGHT];

// data structure for artist.
typedef struct artist{
    int x,y;   
    int r,g,b;  
}artist_t;


const int moves = 8;
const int movement[][2] ={
    {-1, 0}, 
    {-1, 1}, 
    {0, 1}, 
    {1, 1}, 
    {1, 0}, 
    {1, -1}, 
    {0, -1}, 
    {-1, -1} 
};


void initCanvas(){
    for(int x =0; x < CANVAS_WIDTH; ++x){
        for(int y =0; y < CANVAS_HEIGHT; ++y){
            canvas[x][y].r = 255;
            canvas[x][y].g = 255;
            canvas[x][y].b = 255;
            pthread_mutex_init(&canvas[x][y].lock, NULL);
        }
    }
}


// this function saves the canvas as a PPM format image file.
// it should be called after all painting operations are complete.
void outputCanvas(){
    FILE *fp;
    fp = fopen("canvas.ppm","w+");
    fputs("P3\n",fp);
    fputs("256 256\n",fp);
    fputs("255\n",fp);
    for(int x =0; x < CANVAS_WIDTH; ++x){
        for(int y =0; y < CANVAS_HEIGHT; ++y){
            fprintf(fp,"%d",canvas[x][y].r);
            fputs(" ",fp);      
            fprintf(fp,"%d",canvas[x][y].g);
            fputs(" ",fp);      
            fprintf(fp,"%d",canvas[x][y].b);
            fputs(" ",fp);      
        }
        fputs("\n",fp);
    }
    fclose(fp); 
}


// this function is the painting logic for each artist.
// it takes an artist as an argument and makes them paint on the canvas.
void* paint(void* args){
    artist_t* painter = (artist_t*)args;
    
    static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

    for(int i =0; i < 50; ++i){

        int currentX = painter->x;
        int currentY = painter->y;
        
        int roll = (rand()%8);
        painter->x += movement[roll][0];
        painter->y += movement[roll][1];
        
        if(painter->x < 0) { painter->x = 0; }
        if(painter->x > CANVAS_WIDTH-1) { painter->x  = CANVAS_WIDTH-1; }
        if(painter->y < 0) { painter->y = 0; }
        if(painter->y > CANVAS_HEIGHT-1) { painter->y = CANVAS_HEIGHT-1; }

        
        pthread_mutex_lock(&lock);

       
        if( canvas[painter->x][painter->y].r == 255 &&
            canvas[painter->x][painter->y].g == 255 &&
            canvas[painter->x][painter->y].b == 255){
                canvas[painter->x][painter->y].r = painter->r;
                canvas[painter->x][painter->y].g = painter->g;
                canvas[painter->x][painter->y].b = painter->b;
        }else{
       
            painter->x = currentX;
            painter->y = currentY;
        }

       
        pthread_mutex_unlock(&lock);

       
        usleep(rand() % 1000);
    }
}


int main(){
   
    // initialize the blank canvas.
    initCanvas();
    
    // four expert artists.
    artist_t* Michaelangelo = malloc(sizeof(artist_t));
    artist_t* Donatello  = malloc(sizeof(artist_t));
    artist_t* Raphael = malloc(sizeof(artist_t));
    artist_t* Leonardo = malloc(sizeof(artist_t));
    
    // fill in artist attributes.
    Michaelangelo->x = 0;
    Michaelangelo->y = 0;
    Michaelangelo->r = 255;
    Michaelangelo->g = 0;
    Michaelangelo->b = 165;
   
    Donatello->x = CANVAS_WIDTH-1;
    Donatello->y = 0;
    Donatello->r = 128;
    Donatello->g = 0;
    Donatello->b = 128;
    
    Raphael->x = CANVAS_WIDTH-1;
    Raphael->y = CANVAS_HEIGHT-1;
    Raphael->r = 255;
    Raphael->g = 0;
    Raphael->b = 0; 
    
    Leonardo->x = 0;
    Leonardo->y = CANVAS_HEIGHT-1;
    Leonardo->r = 0;
    Leonardo->g = 0;
    Leonardo->b = 255;

    // save thread IDs.
    pthread_t Michaelangelo_tid;
    pthread_t Donatello_tid;
    pthread_t Raphael_tid;
    pthread_t Leonardo_tid;
   
    srand(time(NULL));
    
    // create a thread for each of expert artists.
    pthread_create(&Michaelangelo_tid,NULL,(void*)paint,Michaelangelo);
    pthread_create(&Donatello_tid,NULL,(void*)paint,Donatello);
    pthread_create(&Raphael_tid,NULL,(void*)paint,Raphael);
    pthread_create(&Leonardo_tid,NULL,(void*)paint,Leonardo);

    // add 50 new artists threads.
    int rookieArtists = 50;
    pthread_t moreArtists_tid[rookieArtists];
    artist_t* moreArtists = malloc(rookieArtists * sizeof(artist_t));
    for(int i = 0; i < rookieArtists; ++i){
        moreArtists[i].x = rand() % CANVAS_WIDTH;
        moreArtists[i].y = rand() % CANVAS_HEIGHT;
        moreArtists[i].r = rand() % 256;
        moreArtists[i].g = rand() % 256;
        moreArtists[i].b = rand() % 256;
        pthread_create(&moreArtists_tid[i], NULL, (void*)paint, &moreArtists[i]);
    }

    // thread each thread with the main thread.
    pthread_join(Michaelangelo_tid, NULL);          
    pthread_join(Donatello_tid, NULL);          
    pthread_join(Raphael_tid, NULL);          
    pthread_join(Leonardo_tid, NULL);          

    // join the 50 new threads here.
    for (int i = 0; i < rookieArtists; ++i) {
        pthread_join(moreArtists_tid[i], NULL);
    }

    // save canvas when the painting seesion is done.
    outputCanvas();
   
    // free the memory.
    free(Michaelangelo);
    free(Donatello);
    free(Raphael);
    free(Leonardo);
    free(moreArtists);

    return 0;
}
