#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/err.h>
void aes_ecb(const unsigned char *key, const unsigned char *plaintext, unsigned char *ciphertext, int plaintext_len) {
    AES_KEY enc_key;
    AES_set_encrypt_key(key, 128, &enc_key);
    for (int i = 0; i < plaintext_len; i += AES_BLOCK_SIZE) {
        AES_encrypt(plaintext + i, ciphertext + i, &enc_key);
    }
}
void aes_cbc(const unsigned char *key, const unsigned char *iv, const unsigned char *plaintext, unsigned char *ciphertext, int plaintext_len) {
    AES_KEY enc_key;
    AES_set_encrypt_key(key, 128, &enc_key);
    AES_cbc_encrypt(plaintext, ciphertext, plaintext_len, &enc_key, iv, AES_ENCRYPT);
}
void aes_cfb(const unsigned char *key, const unsigned char *iv, const unsigned char *plaintext, unsigned char *ciphertext, int plaintext_len) {
    AES_KEY enc_key;
    AES_set_encrypt_key(key, 128, &enc_key);
    AES_cfb128_encrypt(plaintext, ciphertext, plaintext_len, &enc_key, iv, &iv[16], AES_ENCRYPT);
}
void add_padding(unsigned char *plaintext, int plaintext_len) {
    int padding_len = AES_BLOCK_SIZE - (plaintext_len % AES_BLOCK_SIZE);
    for (int i = plaintext_len; i < plaintext_len + padding_len; i++) {
        plaintext[i] = (i == plaintext_len) ? 0x80 : 0x00;
    }
}
int main() {
    unsigned char key[AES_KEYLEN_128] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                                         0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
    unsigned char iv[AES_BLOCK_SIZE] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                                        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
    unsigned char plaintext[] = "Hello, World!";
    int plaintext_len = strlen(plaintext);
    add_padding((unsigned char *)plaintext, plaintext_len);
    unsigned char ciphertext[plaintext_len + AES_BLOCK_SIZE];
    printf("ECB Mode:\n");
    aes_ecb(key, plaintext, ciphertext, plaintext_len + AES_BLOCK_SIZE);
    printf("Ciphertext: ");
    for (int i = 0; i < plaintext_len + AES_BLOCK_SIZE; i++) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");
    printf("CBC Mode:\n");
    aes_cbc(key, iv, plaintext, ciphertext, plaintext_len + AES_BLOCK_SIZE);
    printf("Ciphertext: ");
    for (int i = 0; i < plaintext_len + AES_BLOCK_SIZE; i++) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");
    printf("CFB Mode:\n");
    aes_cfb(key, iv, plaintext, ciphertext, plaintext_len + AES_BLOCK_SIZE);
    printf("Ciphertext: ");
    for (int i = 0; i < plaintext_len + AES_BLOCK_SIZE; i++) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");

    return 0;
}
