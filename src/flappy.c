#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define LEBAR 66
#define TINGGI 15 // index dr atas/kiri mulai 0 (for position loop)
#define BORDERV '|'
#define BORDERH '-'
#define EMPTY ' '

#define PLAYER '@'
#define SCOREINC 10

#define WALL '#'
#define PILLARGAP 16 // pillar di index ke 16

const int holemin = 2, holemax = 10; // paling atas dr index 2, paling bawah dari index 10
int randomNum(){ 
    return (rand() % (holemax - holemin + 1) + holemin); }
int holep1 = holemin, holep2 = holemin, holep3 = holemin, holep4 = holemin; // hole heights, randomize

int main() {
    srand(time(NULL)); // set seed

    int x = 6, y = 7; // initial player pos
    int pil1 = PILLARGAP, pil2 = pil1+PILLARGAP, pil3 = pil2 + PILLARGAP, pil4 = pil3 + PILLARGAP; // init pillar xpos
    int dy = 1; // 1 falling, -1 jumping

    //init hole pos
    int holep1 = randomNum();
    int holep2 = randomNum();
    int holep3 = randomNum();
    int holep4 = randomNum();

    int skor = 0;
    int gameOver = 0;
    char key;

    while (!gameOver) {
        //input
        if (kbhit()){
            key = getch();
            if (key == 'w' || key == 'W') {
                y -= 2;
            }
            if (key == 'q' || key == 'Q') {
                break;
            }
        }

        //movement: space turns dy to 1, afterwars back to -1
        y += 1;
        //dy = -1; //set back to fallingww 
        //collision: hit pillar, ground, ceiling


        // bersihkan layar
        system("cls");

        //game info
        printf("%s", "FLAPPY BIRD\n");
        printf("Skor: %d\n", skor);
        printf("%s", "W = Jump | Q = Quit\n\n");

        // draw screen
        for (int Y = 0; Y < TINGGI; Y++){
            for (int X = 0; X < LEBAR; X++){
                if (Y == 0 || Y == TINGGI - 1) {
                    printf("%c", BORDERH);
                }else if (X == 0 || X == LEBAR - 1){
                    printf("%c", BORDERV);
                }else if (X == pil1 || X == pil2 || X == pil3 || X == pil4){ // kalo i dan j di posisi awal player (var x dan y)
                    //kenapa ada kondisi dulu, dan nggk sama kondisi lain?
                    //biar misahin logika print wall sama lobang dgn print empty space
                    if (X == pil1){ // kalo index di lobang dan 2 index dibawahnya (hasilnya lobang tinggi 3)
                        if (Y == holep1 || Y == holep1+1 || Y == holep1+2){
                            // if player currently through hole, might be issues if plr moves up while in hole, causing double points
                            // prolly doesnt get called cause player draw call above gets called first (YEP, FIXED)
                            if (x == X && y == Y){ skor += SCOREINC; printf("%c", PLAYER); }
                            printf ("%c", EMPTY);
                        }else{ printf("%c", WALL); }
                    }else if (X == pil2){
                        if (Y == holep2 || Y == holep2+1 || Y == holep2+2){
                            if (x == X && y == Y){ skor += SCOREINC; printf("%c", PLAYER); }
                            printf ("%c", EMPTY);
                        }else{ printf("%c", WALL); }
                    }else if (X == pil3){
                        if (Y == holep3 || Y == holep3+1 || Y == holep3+2){
                            if (x == X && y == Y){ skor += SCOREINC; printf("%c", PLAYER); }
                            printf ("%c", EMPTY);
                        }else{ printf("%c", WALL); }
                    }else if (X == pil4){
                        if (Y == holep4 || Y == holep4+1 || Y == holep4+2){
                            if (x == X && y == Y){ skor += SCOREINC; printf("%c", PLAYER); }
                            printf ("%c", EMPTY);
                        }else{ printf("%c", WALL); }
                    }
                }else if (Y == y && X == x){ // set player position (setelah pillar check cuz scoring)
                    printf("%c", PLAYER);
                }
                else{ printf("%c", EMPTY); }
            }
            printf("%s", "\n");
        }

        //move pillars to the left
        pil1--; pil2--; pil3--; pil4--;
        //reached edge, change hole height and reset to right
        if (pil1 == 0) {pil1 = LEBAR - 2; holep1 = randomNum();}
        else if (pil2 == 0) {pil2 = LEBAR - 2; holep2 = randomNum();}
        else if (pil3 == 0) {pil3 = LEBAR - 2; holep3 = randomNum();}
        else if (pil4 == 0) {pil4 = LEBAR - 2; holep4 = randomNum();}

        Sleep(250); // ms
    }

    printf("%s", "\nGAME OVER!\n");
    printf("Skor akhir: %d\n\n", skor);

    return 0;
}
