#include <stdio.h>
#include <string.h>
#define MAX_LENGTH 100
void decodePlayfair(char *code) {
    char key[5][5] = {
        {'K', 'X', 'J', 'E', 'Y'},
        {'U', 'R', 'E', 'B', 'E'},
        {'Z', 'W', 'E', 'H', 'E'},
        {'W', 'R', 'Y', 'T', 'U'},
        {'H', 'E', 'Y', 'F', 'S'}
    };
    int i, j;
   
    for (i = 0; i < strlen(code); i += 2) {
        char first = code[i];
        char second = code[i + 1];
        int row1, col1, row2, col2;
        
        for (j = 0; j < 5; j++) {
            for (int k = 0; k < 5; k++) {
                if (key[j][k] == first) {
                    row1 = j;
                    col1 = k;
                }
                if (key[j][k] == second) {
                    row2 = j;
                    col2 = k;
                }
            }
        }
        
        if (row1 == row2) {
            printf("%c%c", key[row1][(col1 + 4) % 5], key[row2][(col2 + 4) % 5]);
        }
        
        else if (col1 == col2) {
            printf("%c%c", key[(row1 + 4) % 5][col1], key[(row2 + 4) % 5][col2]);
        }
        
        else {
            printf("%c%c", key[row1][col2], key[row2][col1]);
        }
    }
    printf("\n");
}
int main() {
    char code[MAX_LENGTH] = "KSYCAJPOBOTEIZONTXBYBNTGONEYCUZWRGDSONSXBOUYWRHEBAAHYUSEDQ";

    printf("Decoded Message: ");
    decodePlayfair(code);

    return 0;
}
