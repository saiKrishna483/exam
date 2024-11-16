#include <stdio.h>
#include <stdlib.h>
#include <openssl/rsa.h>
#include <openssl/dsa.h>
#include <openssl/sha.h>

// Function to generate RSA signature
void rsa_sign(const unsigned char *message, int message_len, RSA *rsa, unsigned char *signature) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(message, message_len, hash);
    RSA_sign(NID_sha256, hash, SHA256_DIGEST_LENGTH, signature, &rsa->n, rsa);
}

// Function to verify RSA signature
int rsa_verify(const unsigned char *message, int message_len, RSA *rsa, unsigned char *signature) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(message, message_len, hash);
    return RSA_verify(NID_sha256, hash, SHA256_DIGEST_LENGTH, signature, &rsa->n, rsa);
}

// Function to generate DSA signature
void dsa_sign(const unsigned char *message, int message_len, DSA *dsa, unsigned char *signature) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(message, message_len, hash);
    DSA_sign(NID_sha256, hash, SHA256_DIGEST_LENGTH, signature, NULL, dsa);
}

// Function to verify DSA signature
int dsa_verify(const unsigned char *message, int message_len, DSA *dsa, unsigned char *signature) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(message, message_len, hash);
    return DSA_verify(NID_sha256, hash, SHA256_DIGEST_LENGTH, signature, NULL, dsa);
}

int main() {
    // Generate RSA key pair
    RSA *rsa = RSA_new();
    BIGNUM *rsa_b = BN_new();
    BN_set_word(rsa_b, 65537);
    RSA_generate_key_ex(rsa, 2048, rsa_b, NULL);

    // Generate DSA key pair
    DSA *dsa = DSA_new();
    DSA_generate_parameters(dsa, 2048, NULL, 0, NULL, NULL, NULL);
    DSA_generate_key(dsa);

    unsigned char message[] = "Hello, World!";
    int message_len = strlen(message);

    // RSA signing and verification
    unsigned char rsa_signature[256];
    rsa_sign(message, message_len, rsa, rsa_signature);
    printf("RSA Signature: ");
    for (int i = 0; i < 256; i++) {
        printf("%02x", rsa_signature[i]);
    }
    printf("\n");
    printf("RSA Verification: %s\n", rsa_verify(message, message_len, rsa, rsa_signature) == 1 ? "Success" : "Failure");

    // Sign the same message again
    unsigned char rsa_signature2[256];
    rsa_sign(message, message_len, rsa, rsa_signature2);
    printf("RSA Signature 2: ");
    for (int i = 0; i < 256; i++) {
        printf("%02x", rsa_signature2[i]);
    }
    printf("\n");
    printf("RSA Verification 2: %s\n", rsa_verify(message, message_len, rsa, rsa_signature2) == 1 ? "Success" : "Failure");

    // DSA signing and verification
    unsigned char dsa_signature[256];
    dsa_sign(message, message_len, dsa, dsa_signature);
    printf("DSA Signature: ");
    for (int i = 0; i < 256; i++) {
        printf("%02x", dsa_signature[i]);
    }
    printf("\n");
    printf("DSA Verification: %s\n", dsa_verify(message, message_len, dsa, dsa_signature) == 1 ? "Success" : "Failure");

    // Sign the same message again
    unsigned char dsa_signature2[256];
    dsa_sign(message, message_len, dsa, dsa_signature2);
    printf("DSA Signature 2: ");
    for (int i = 0; i < 256; i++) {
        printf("%02x", dsa_signature2[i]);
    }
    printf("\n");
    printf("DSA Verification 2: %s\n", dsa_verify(message, message_len, dsa, dsa_signature2) == 1 ? "Success" : "Failure");

    return 0;
}
