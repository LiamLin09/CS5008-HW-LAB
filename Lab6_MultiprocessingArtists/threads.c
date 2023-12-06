// CS 5008 LAB 6
// Author: Nianlong Lin
// Date: 10/15/2023

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#define CANVAS_WIDTH 64
#define CANVAS_HEIGHT 64


// define pixel structures.
typedef struct pixel {
    int r, g, b;
    // mutex for thread synchronization.
    pthread_mutex_t lock; 
} pixel_t;


// define the canvas.
pixel_t canvas[CANVAS_WIDTH][CANVAS_HEIGHT];


// define the artist structures.
typedef struct artist {
    int y; 
} artist_t;

// initialize the canvas with white pixels.
void initCanvas() {
    for (int x = 0; x < CANVAS_WIDTH; ++x) {
        for (int y = 0; y < CANVAS_HEIGHT; ++y) {
            canvas[x][y].r = 255;
            canvas[x][y].g = 255;
            canvas[x][y].b = 255;
            // initialize mutex locks.
            pthread_mutex_init(&canvas[x][y].lock, NULL); 
        }
    }
}

// output the canvas to a PPM file.
void outputCanvas() {
    FILE *fp;
    fp = fopen("canvas.ppm", "w+"); 
    if (fp == NULL) {
        printf("Failed to open file.\n");
        exit(1);
    }
    fputs("P3\n", fp);
    fputs("64 64\n", fp);
    fputs("255\n", fp);
    for (int y = 0; y < CANVAS_HEIGHT; ++y) {
        for (int x = 0; x < CANVAS_WIDTH; ++x) {
            fprintf(fp, "%d ", canvas[x][y].r);
            fprintf(fp, "%d ", canvas[x][y].g);
            fprintf(fp, "%d", canvas[x][y].b);
            if (x != CANVAS_WIDTH - 1) {
                fprintf(fp, " ");
            }
        }
        fputs("\n", fp);
    }
    fclose(fp); 
}


// painting function executed by threads.
void *paint(void *args) {
    artist_t *painter = (artist_t *) args;
    srand(time(NULL));
    
    int row_r = rand() % 256;
    int row_g = rand() % 256;
    int row_b = rand() % 256;
    for (int x = 0; x < CANVAS_WIDTH; ++x) {
        // lock
        pthread_mutex_lock(&canvas[x][painter->y].lock); 
        canvas[x][painter->y].r = (row_r+*(int*)args*4)%256;
        canvas[x][painter->y].g = (row_g+*(int*)args*4)%256;
        canvas[x][painter->y].b = (row_b+*(int*)args*4)%256;
        // unlock
        pthread_mutex_unlock(&canvas[x][painter->y].lock);
    }
    return NULL;
}

int main() {
    // initialize the canvas.
    initCanvas(); 
    artist_t *artists[CANVAS_HEIGHT];
    for (int y = 0; y < CANVAS_HEIGHT; ++y) {
        // allocate memory for artist structures.
        artists[y] = malloc(sizeof(artist_t)); 
        artists[y]->y = y;
    }
    pthread_t threads[CANVAS_HEIGHT];
    srand(time(NULL));
    for (int y = 0; y < CANVAS_HEIGHT; ++y) {
        // create threads.
        pthread_create(&threads[y], NULL, paint, artists[y]); 
    }
    for (int y = 0; y < CANVAS_HEIGHT; ++y) {
        // wait for threads to finish
        pthread_join(threads[y], NULL); 
    }
    outputCanvas();
    for (int y = 0; y < CANVAS_HEIGHT; ++y) {
        // free memeory allocated for artist sturectures.
        free(artists[y]); 
    }
    return 0;
}
