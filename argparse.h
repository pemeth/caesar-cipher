#include <errno.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct progopts
{
    int8_t key;             //!< Key for the cipher
    char alphabet_toggle;   //!< Toggles alphabet / printable characters
} progopts_t;

void print_help(char * const binary_name)
{
    printf("Usage: %s [-k key] [-p]\n", binary_name);
    printf("Encode a message via the ceasar cipher with specified key.\n");
    printf("\n");
    printf(
        "  -k key\tuse this cipher key (may be [%d,%d], defaults to 1)\n",
        INT8_MIN,
        INT8_MAX
    );
    printf("  -p\t\tuse all printable ASCII characters as alphabet\n");
}

int argparse(int argc, char * const argv[], progopts_t *options)
{
    int opt;
    int const base = 10;
    char *endptr;

    while ((opt = getopt(argc, argv, "hk:p")) != -1) {
        switch (opt)
        {
        case 'k':
            // Key to the cipher
            errno = 0;
            options->key = strtol(optarg, &endptr, base);
            if (errno == ERANGE || errno == EINVAL) {
                fprintf(stderr, "Invalid key value\n");
                return -1;
            }
            break;
        case 'p':
            // Mode of the cipher
            options->alphabet_toggle = 'p';
            break;
        case 'h':
            print_help(argv[0]);
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
