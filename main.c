#include <stdio.h>
#include <stdint.h>

#include "argparse.h"

#define ASCII_SIZE 128
#define PRINTABLE_SIZE 95
#define PRINTABLE_START 32
#define ALPHA_SIZE 26
#define CAP_MASK 0xE0           // 0b11100000
#define LETTER_MASK ~CAP_MASK   // 0b00011111

int ceasar_printable(int8_t key)
{
    char input;
    char encoded;
    size_t const input_len = 1;
    size_t const input_num = 1;

    key = key % PRINTABLE_SIZE;

    while (fread(&input, input_len, input_num, stdin) == input_len) {
        encoded = input; // TODO it is possible to use only one variable

        if (input >= 32 && input <= 126) {
            // Printables except <space>

            // Normalize to 0-indexed and shift by key
            char const input_normalized = input - PRINTABLE_START;
            uint8_t const shifted =
                (input_normalized + key + PRINTABLE_SIZE) % PRINTABLE_SIZE;

            encoded = shifted + PRINTABLE_START;
        }

        // TODO test if this would be quicker through a buffer print (it would)
        printf("%c", encoded);
    }

    return 0;
}

int ceasar_alpha(int8_t key)
{
    char input;
    char encoded;
    size_t const input_len = 1;
    size_t const input_num = 1;

    key = key % ALPHA_SIZE;

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

    return 0;
}

int main(int argc, char* const argv[])
{
    progopts_t options = { .alphabet_toggle='a', .key=0 };

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

    if (options.alphabet_toggle == 'a') {
        ceasar_alpha(options.key);
    } else { /* options.alphabet_toggle == 'p' */
        ceasar_printable(options.key);
    }

    return 0;
}