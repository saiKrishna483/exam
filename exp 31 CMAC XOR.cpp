#include <stdio.h>
#include <stdint.h>

#define BLOCK_SIZE_64 64
#define BLOCK_SIZE_128 128
uint64_t left_shift(uint64_t value, int shift_amount) {
    return (value << shift_amount) | (value >> (64 - shift_amount));
}
void generate_subkeys(int block_size, uint64_t key, uint64_t *subkey1, uint64_t *subkey2) {
    uint64_t const1, const2;

    if (block_size == BLOCK_SIZE_64) {
        const1 = 0x0000000000000001;
        const2 = 0x0000000000000080;
    } else if (block_size == BLOCK_SIZE_128) {
        const1 = 0x00000000000000000000000000000001;
        const2 = 0x00000000000000000000000000000087;
    } else {
        printf("Unsupported block size\n");
        return;
    }
    *subkey1 = (key << 1); 
    if ((key & (1 << (block_size - 1))) != 0) { 
        *subkey1 ^= const1; 
    }
    *subkey2 = (*subkey1 << 1); 
    if ((*subkey1 & (1 << (block_size - 1))) != 0) { 
        *subkey2 ^= const2; 
    }
}
int main() {
    uint64_t key = 0x0123456789ABCDEF;
    uint64_t subkey1, subkey2;

    printf("Subkeys for block size 64:\n");
    generate_subkeys(BLOCK_SIZE_64, key, &subkey1, &subkey2);
    printf("Subkey 1: %llx\n", subkey1);
    printf("Subkey 2: %llx\n", subkey2);

    printf("\nSubkeys for block size 128:\n");
    generate_subkeys(BLOCK_SIZE_128, key, &subkey1, &subkey2);
    printf("Subkey 1: %llx\n", subkey1);
    printf("Subkey 2: %llx\n", subkey2);

    return 0;
}

