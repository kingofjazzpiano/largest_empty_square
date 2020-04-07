#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <iso646.h>

#define LENGTH 20
#define WIDTH 10

char min(char cell1, char cell2, char cell3){
    if(cell1 <= cell2 and cell1 <= cell3)
        return cell1;
    else if(cell2 <= cell1 and cell2 <= cell3)
        return cell2;
    else
        return cell3;
}

void calculation_of_the_largest_square_indices(char map[WIDTH][LENGTH], char *y_crdnt, char *x_crdnt, char *side){
    char cash[WIDTH][LENGTH];

    for(char y = 0; y < WIDTH; y++){
        for(char x = 0; x < LENGTH; x++){
            if(y == 0 or x == 0)
                cash[y][x] = map[y][x];
            else if(map[y][x] > 0)
                cash[y][x] = 1 + min(cash[y - 1][x], cash[y][x - 1], cash[y - 1][x - 1]);
            else
                cash[y][x] = 0;
            if(cash[y][x] > cash[*y_crdnt][*x_crdnt]){
                *y_crdnt = y;
                *x_crdnt = x;
            }
        }
    }
    *side = cash[*y_crdnt][*x_crdnt];
}

int main(){
    char map[WIDTH][LENGTH];
    char final_map[WIDTH][LENGTH];
    char x_coordinate = 0;
    char y_coordinate = 0;
    char side_of_square = 0;
    char y_barrier = 0;
    char x_barrier = 0;

    srand(time(NULL));

    for(char y = 0; y < WIDTH; y++){
        for(char x = 0; x < LENGTH; x++){
            if(x == rand() % 30){
                map[y][x] = 0;
                final_map[y][x] = 'o';
                printf("o ");
            }
            else{
                printf(". ");
                map[y][x] = 1;
                final_map[y][x] = '.';
            }
        }
        printf("\n");
    }

    calculation_of_the_largest_square_indices(map, &y_coordinate, &x_coordinate, &side_of_square);

    printf("y_coordinate - %d, x_coordinate - %d\n", y_coordinate, x_coordinate);
    printf("side of biggest square = %d\n", side_of_square);

    y_barrier = y_coordinate + 1 - side_of_square;
    x_barrier = x_coordinate + 1 - side_of_square;

    for(char y = y_coordinate; y >= y_barrier; y--){
        for(char x = x_coordinate; x >= x_barrier; x--)
            final_map[y][x] = 'x';
    }

    for(char y = 0; y < WIDTH; y++){
        for(char x = 0; x < LENGTH; x++)
            printf("%c ", final_map[y][x]);
        printf("\n");
    }
}