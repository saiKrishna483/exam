#include <stdio.h>
int is_valid_a(int a) {
    int gcd = a;
    int b = 26;
    while (b != 0) {
        int temp = gcd;
        gcd = b;
        b = temp % b;
    }
    return (gcd == 1);
}
int mod_inverse(int a) {
    for (int x = 1; x < 26; x++) {
        if ((a * x) % 26 == 1) {
            return x;
        }
    }
    return -1; 
}
void encrypt(int a, int b, char plaintext[]) {
    int ciphertext['z' + 1];
    int i = 0;
    while (plaintext[i]) {
        int p = plaintext[i] - 'a';
        ciphertext[i] = (a * p + b) % 26;
        ciphertext[i] = ciphertext[i] + 'a';
        i++;
    }
    ciphertext[i] = '\0'; 
    printf("Encrypted text: %s\n", ciphertext);
}
void decrypt(int a, int b, char ciphertext[]) {
    int inverse_a = mod_inverse(a);
    if (inverse_a == -1) {
        printf("Decryption not possible: No modular inverse for a.\n");
        return;
    }
    int plaintext['z' + 1]; 
    int i = 0;
    while (ciphertext[i]) {
        
        int c = ciphertext[i] - 'a';
        
        plaintext[i] = (inverse_a * (c - b + 26)) % 26; 
       
        plaintext[i] = plaintext[i] + 'a';
        i++;
    }
    plaintext[i] = '\0'; 
    printf("Decrypted text: %s\n", plaintext);
}

int main() {
    
    printf("Limitations:\n");
    printf("a must be relatively prime to 26 (gcd(a, 26) == 1).\n");
    printf("No limitations on b.\n");

    
    int a = 5; 
    int b = 3;
    char plaintext[] = "hello";
    encrypt(a, b, plaintext);
    decrypt(a, b, "khoor");

    return 0;
}

