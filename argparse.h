#ifndef ARGPARSE_H
#define ARGPARSE_H

#include <errno.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct progopts
{
    int8_t key;             //!< Key for the cipher
    char alphabet_toggle;   //!< Toggles alphabet / printable characters
    uint8_t help_flag;      //!< Set if help is printed
    char codec_toggle;      //!< Set encoder / decoder beaviour
} progopts_t;

void print_help(char * const binary_name)
{
    printf("Usage: %s [-k key] [-p] [-e | -d] [-h]\n", binary_name);
    printf("Encode a message via the Caesar cipher with the specified key.\n");
    printf("\n");
    printf("Encodes only characters of the alphabet unless -p is specified,\n");
    printf("in which case all printable characters are encoded.\n");
    printf("\n");
    printf(
        "  -k key\tuse this cipher key (may be [%d,%d], defaults to 1)\n",
        INT8_MIN,
        INT8_MAX
    );
    printf("  -p\t\tuse all printable ASCII characters as alphabet\n");
    printf("  -e\t\tencode with specified key - this is the default\n");
    printf("  -d\t\tdecode with specified key that was used for encoding\n");
    printf("  -h\t\tprint this message and exit\n");
}

int argparse(int argc, char * const argv[], progopts_t *options)
{
    int opt;
    int const base = 10;
    char *endptr;

    while ((opt = getopt(argc, argv, "hk:pde")) != -1) {
        switch (opt)
        {
        case 'k':
            // Key to the cipher
            errno = 0;
            long const parsed_key = strtol(optarg, &endptr, base);

            if (errno == ERANGE || errno == EINVAL) {
                fprintf(stderr, "Key value error\n");
                return -2;
            }
            if (parsed_key < INT8_MIN || parsed_key > INT8_MAX) {
                fprintf(stderr, "Key value out of range\n");
                return -1;
            }

            options->key = parsed_key;

            break;
        case 'p':
            // Mode of the cipher
            options->alphabet_toggle = 'p';
            break;
        case 'e':
            // Encode
            options->codec_toggle = 'e';
            break;
        case 'd':
            // Decode
            options->codec_toggle = 'd';
            break;
        case 'h':
            print_help(argv[0]);
            options->help_flag = 1;
            return 0;
            break;
        default:
            print_help(argv[0]);
            return -1;
            break;
        }

    }

    return 0;
}

#endif /* ARGPARSE_H */
