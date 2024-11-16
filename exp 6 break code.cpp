#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1;
}


char decryptAffine(char ch, int a, int b, int mod) {
    if (!isalpha(ch))
        return ch;
    ch = toupper(ch) - 'A'; 
    int a_inv = modInverse(a, mod); 
    if (a_inv == -1) {
        printf("Error: 'a' has no modular inverse.\n");
        exit(1);
    }
    int decrypted = (a_inv * (ch - b + mod)) % mod;
    return (decrypted < 0 ? decrypted + mod : decrypted) + 'A'; 
}

int main() {
    int mod = 26;
    int c1 = 1, p1 = 4; 
    int c2 = 20, p2 = 19; 

   
    int a = ((c2 - c1) * modInverse(p2 - p1, mod)) % mod;
    if (a < 0) a += mod; 
    int b = (c1 - a * p1) % mod;
    if (b < 0) b += mod; 
    printf("Determined Keys: a = %d, b = %d\n", a, b);

   
    char ciphertext[] = "BU"; 
    printf("Ciphertext: %s\n", ciphertext);

    
    printf("Decrypted text: ");
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        printf("%c", decryptAffine(ciphertext[i], a, b, mod));
    }
    printf("\n");

    return 0;
}

