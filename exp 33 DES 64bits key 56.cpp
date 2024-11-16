

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to permute bits
unsigned long permute(unsigned long block, unsigned char *table, int size) {
    unsigned long result = 0;
    for (int i = 0; i < size; i++) {
        int index = table[i] - 1;
        (result <<= 1) |= (block >> index) & 1;
    }
    return result;
}

// Function to left shift
unsigned long left_shift(unsigned long block, int shifts) {
    return (block << shifts) | (block >> (32 - shifts));
}

// Function to apply S-boxes
unsigned long apply_sbox(unsigned long block, unsigned char *sbox) {
    unsigned long result = 0;
    for (int i = 0; i < 4; i++) {
        int row = (block >> (24 - i * 6)) & 0x3F;
        int col = (block >> (20 - i * 6)) & 0x3F;
        result |= sbox[row * 64 + col] << (24 - i * 6);
    }
    return result;
}

// Function to DES encryption
void des_encrypt(unsigned char *plaintext, unsigned char *ciphertext, unsigned char *key) {
    unsigned long block = *(unsigned long *)plaintext;
    unsigned long key_schedule[16];

    // Initial permutation
    unsigned char ip_table[] = {58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
                                62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
                                57, 49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3,
                                61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7};
    block = permute(block, ip_table, 64);

    // Key schedule
    unsigned char pc1_table[] = {57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18,
                                 10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36,
                                 63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22,
                                 14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4};
    unsigned long key_block = *(unsigned long *)key;
    key_block = permute(key_block, pc1_table, 56);

    for (int i = 0; i < 16; i++) {
        key_schedule[i] = left_shift(key_block, i * 4);
    }

    // Rounds
    unsigned char pc2_table[] = {14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10,
                                 23, 19, 12, 4, 26, 8, 16, 7, 27, 20, 13, 2,
                                 41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
                                 44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32};
    for (int i = 0; i < 16; i++) {
        unsigned long left = block >> 32;
        unsigned long right = block & 0xFFFFFFFF;

        // Expansion
        unsigned char expansion_table[] = {32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8

