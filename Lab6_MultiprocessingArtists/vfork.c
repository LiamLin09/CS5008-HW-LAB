// CS 5008 LAB 6
// Author: Nianlong Lin
// Date: 10/15/2023

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define CANVAS_WIDTH 64
#define CANVAS_HEIGHT 64


// define a structure for representing a pixel with RGB color channels.
typedef struct pixel {
    int r, g, b;
} pixel_t;


// define a canvas as a 2D array of pixels.
pixel_t canvas[CANVAS_WIDTH][CANVAS_HEIGHT];


// define a structure to represent an artist.
typedef struct artist {
    // current vertical position on the canvas.
    int y;
} artist_t;

// initialize the canvas.
void initCanvas() {
    for (int x = 0; x < CANVAS_WIDTH; ++x) {
        for (int y = 0; y < CANVAS_HEIGHT; ++y) {
            canvas[x][y].r = 255;
            canvas[x][y].g = 255;
            canvas[x][y].b = 255;
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
    for (int x= 0; x < CANVAS_HEIGHT; ++x) {
        for (int y = 0; y < CANVAS_WIDTH; ++y) {
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


// function to paint a row of the canvas with random colors.
void paint(int args) {
    int x = args;
    int row_r = rand() % 256;
    int row_g = rand() % 256;
    int row_b = rand() % 256;
    for(int y=0;y<CANVAS_HEIGHT;y++){
        // set the RGB values for each pixel in the row based on the random value.
        canvas[x][y].r = (row_r+args*4)%256;
        canvas[x][y].g = (row_g+args*4)%256;
        canvas[x][y].b = (row_b+args*4)%256;
    }
}

int main(int argc, char** argv){
    // initialize the canvas with white pixels.
    initCanvas(); 
    int numberOfArtists = 64;
    pid_t pid;

    // create multiple child processes to pain the canvas.
    for(int i =0; i < numberOfArtists; i++){
        pid = vfork(); 
        if(pid==0){ 
            paint(i); 
            exit(0);
        }
        // parent process prints the child process ID.
        printf("Child created: %d\n",pid); 
    }
    // output the final canvas to a file.
    outputCanvas(); 
    return 0;
}
