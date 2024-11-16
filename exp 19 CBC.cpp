#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/des.h>
void three_des_cbc_encrypt(const unsigned char *plaintext, const unsigned char *key, const unsigned char *iv, unsigned char *ciphertext) {
    DES_cblock key_schedule[3];
    DES_key_schedule key1, key2, key3;
    DES_set_key((DES_cblock *)key, &key1);
    DES_set_key((DES_cblock *)(key + 8), &key2);
    DES_set_key((DES_cblock *)(key + 16), &key3);
    memcpy(key_schedule[0], &key1, sizeof(DES_key_schedule));
    memcpy(key_schedule[1], &key2, sizeof(DES_key_schedule));
    memcpy(key_schedule[2], &key3, sizeof(DES_key_schedule));
    DES_ede3_cbc_encrypt(plaintext, ciphertext, strlen(plaintext), key_schedule, (DES_cblock *)iv, DES_ENCRYPT);
}
void aes_cbc_encrypt(const unsigned char *plaintext, const unsigned char *key, const unsigned char *iv, unsigned char *ciphertext) {
    AES_KEY enc_key;
    AES_set_encrypt_key(key, 128, &enc_key);
    AES_cbc_encrypt(plaintext, ciphertext, strlen(plaintext), &enc_key, (AES_cblock *)iv, AES_ENCRYPT);
}
int main() {
    unsigned char plaintext[] = "Hello, World!";
    unsigned char key_3des[24] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                                  0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10,
                                  0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18};
    unsigned char iv_3des[8] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};

    unsigned char key_aes[16] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                                 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10};
    unsigned char iv_aes[16] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                                0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10};

    unsigned char ciphertext_3des[strlen(plaintext)];
    unsigned char ciphertext_aes[strlen(plaintext)];

    three_des_cbc_encrypt(plaintext, key_3des, iv_3des, ciphertext_3des);
    aes_cbc_encrypt(plaintext, key_aes, iv_aes, ciphertext_aes);

    printf("3DES CBC Ciphertext: ");
    for (int i = 0; i < strlen(plaintext); i++) {
        printf("%02x", ciphertext_3des[i]);
    }
    printf("\n");

    printf("AES CBC Ciphertext: ");
    for (int i = 0; i < strlen(plaintext); i++) {
        printf("%02x", ciphertext_aes[i]);
    }
    printf("\n");

    return 0;
}
