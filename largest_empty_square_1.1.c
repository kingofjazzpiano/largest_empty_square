#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <iso646.h>
#include <inttypes.h>
#include <sys/time.h>

#define LENGTH 100
#define WIDTH 100

struct timeval t_begin, t_end;

int16_t min(int16_t cell1, int16_t cell2, int16_t cell3);

void calculation_of_the_largest_square_indices(int16_t map[WIDTH][LENGTH], int16_t *y_crdnt, int16_t *x_crdnt, int16_t *side);

int main(){
    gettimeofday(&t_begin, NULL);

    int16_t map[WIDTH][LENGTH];
    int16_t final_map[WIDTH][LENGTH];
    int16_t x_coordinate = 0;
    int16_t y_coordinate = 0;
    int16_t side_of_square = 0;
    int16_t y_barrier = 0;
    int16_t x_barrier = 0;

    srand(time(NULL));

    for(int16_t y = 0; y < WIDTH; y++){
        for(int16_t x = 0; x < LENGTH; x++){
            if(x == rand() % LENGTH){
                map[y][x] = 0;
                final_map[y][x] = 'o';
                // printf("o ");
            }
            else{
                // printf(". ");
                map[y][x] = 1;
                final_map[y][x] = '.';
            }
        }
        // printf("\n");
    }
    // printf("\n");
    // printf("\n");
    calculation_of_the_largest_square_indices(map, &y_coordinate, &x_coordinate, &side_of_square);

    printf("y_coordinate - %" PRId16 ", x_coordinate - %" PRId16 "\n", y_coordinate, x_coordinate);
    printf("side of biggest square = %" PRId16 "\n", side_of_square);

    // y_barrier = y_coordinate + 1 - side_of_square;
    // x_barrier = x_coordinate + 1 - side_of_square;

    // for(int16_t y = y_coordinate; y >= y_barrier; y--){
    //     for(int16_t x = x_coordinate; x >= x_barrier; x--)
    //         final_map[y][x] = 'x';
    // }

    // for(int16_t y = 0; y < WIDTH; y++){
    //     for(int16_t x = 0; x < LENGTH; x++)
    //         printf("%c ", (char) final_map[y][x]);
    //     printf("\n");
    // }
    gettimeofday(&t_end, NULL);
    printf("time elapsed: %g sec\n", t_end.tv_sec - t_begin.tv_sec + (t_end.tv_usec - t_begin.tv_usec) / 100.0);
}

int16_t min(int16_t cell1, int16_t cell2, int16_t cell3){
    if(cell1 <= cell2 and cell1 <= cell3)
        return cell1;
    else if(cell2 <= cell1 and cell2 <= cell3)
        return cell2;
    else
        return cell3;
}

void calculation_of_the_largest_square_indices(int16_t map[WIDTH][LENGTH], int16_t *y_crdnt, int16_t *x_crdnt, int16_t *side){
    int16_t cash[WIDTH][LENGTH];

    for(int16_t y = 0; y < WIDTH; y++){
        for(int16_t x = 0; x < LENGTH; x++){
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