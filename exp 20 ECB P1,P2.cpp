#include <stdio.h>
#include <string.h>
#include <openssl/des.h>
void handleErrors(void) {
    ERR_print_errors_fp(stderr);
    abort();
}

int main(void) {
    
    DES_cblock key1, key2, key3;
    DES_cblock iv;
    DES_key_schedule ks1, ks2, ks3;

    
    DES_string_to_key("key1", &key1);
    DES_string_to_key("key2", &key2);
    DES_string_to_key("key3", &key3);
    DES_set_odd_parity(&iv);
    DES_random_key(&iv);

    DES_set_key_checked(&key1, &ks1);
    DES_set_key_checked(&key2, &ks2);
    DES_set_key_checked(&key3, &ks3);

    
    const char *plaintext = "This is a test message.";

   
    unsigned char ciphertext[1024];

    
    DES_ede3_cbc_encrypt((unsigned char *)plaintext, ciphertext, strlen(plaintext) + 1, &ks1, &ks2, &ks3, &iv, DES_ENCRYPT);

    printf("Ciphertext is:\n");
    for(int i = 0; i < strlen(plaintext) + 1; i++) {
        printf("%02x ", ciphertext[i]);
    }
    printf("\n");

    return 0;
}

