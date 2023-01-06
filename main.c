#include <stdio.h>
#include <stdint.h>

#include "argparse.h"

#define ASCII_SIZE 128
#define PRINTABLE_SIZE 95
#define PRINTABLE_START 32
#define ALPHA_SIZE 26
#define CAP_MASK 0xE0           // 0b11100000
#define LETTER_MASK ~CAP_MASK   // 0b00011111

/**
 * @brief Codec function to be used for processing all printable
 * ASCII characters.
 *
 * @param key the cipher key
 */
void caesar_printable(int8_t key)
{
    char input;
    char encoded;
    size_t const input_len = 1;
    size_t const input_num = 1;

    while (fread(&input, input_len, input_num, stdin) == input_len) {
        encoded = input;

        if (input >= 32 && input <= 126) {
            // Printables

            // Normalize to 0-indexed and shift by key
            char const input_normalized = input - PRINTABLE_START;
            uint8_t const shifted =
                (input_normalized + key + PRINTABLE_SIZE) % PRINTABLE_SIZE;

            encoded = shifted + PRINTABLE_START;
        }

        printf("%c", encoded);
    }
}

/**
 * @brief Codec function to be used for processing only alphabet characters.
 *
 * @param key the cipher key
 */
void caesar_alpha(int8_t key)
{
    char input;
    char encoded;
    size_t const input_len = 1;
    size_t const input_num = 1;

    while (fread(&input, input_len, input_num, stdin) == input_len) {
        encoded = input;

        if ((input >= 65 && input <= 90) || (input >= 97 && input <= 122)) {
            // Any alphabet character

            // Save the capitalization bits and the letter bits
            char const capitalization = input & CAP_MASK;
            char const letter = input & LETTER_MASK;

            // Normalize to 0-indexed and shift by key
            char const normalization_constant = 1;
            char const letter_normalized = letter - normalization_constant;
            char const shifted =
                (letter_normalized + key + ALPHA_SIZE) % ALPHA_SIZE;

            encoded = (shifted + normalization_constant) | capitalization;
        }

        printf("%c", encoded);
    }
}

/**
 * @brief Encodes a message from `stdin` based on specified options.
 *
 * @param key the cipher key
 * @param alphabet 'a' for alphabet only, 'p' for all printables
 * @param codec_toggle 'e' for encoding, 'd' for decoding
 */
void caesar(int8_t key, char alphabet, char codec_toggle)
{
    // Calculate key modulo based on alphabet used
    int key_mod = alphabet == 'a' ? key % ALPHA_SIZE : key % PRINTABLE_SIZE;

    // If the -d option was entered, find the reverse key to the entered key
    key = codec_toggle == 'd' ? key_mod * (-1) : key_mod;

    // Encode based on alphabet
    if (alphabet == 'a') {
        caesar_alpha(key);
    } else { /* alphabet == 'p' */
        caesar_printable(key);
    }
}

int main(int argc, char* const argv[])
{
    progopts_t options = {
        .alphabet_toggle='a',
        .key=0,
        .help_flag=0,
        .codec_toggle='e'
    };

    int const argpase_retval = argparse(argc, argv, &options);
    if (argpase_retval < 0) {
        return argpase_retval;
    }

    if (options.help_flag != 0) {
        // Help printed, exit
        return 0;
    }

    if (options.key == 0) {
        options.key = 1;
    }

    caesar(options.key, options.alphabet_toggle, options.codec_toggle);

    return 0;
}