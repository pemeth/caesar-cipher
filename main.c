#include <stdio.h>

#include "argparse.h"

int main(int argc, char* const argv[])
{
    progopts_t options = { .alphabet_toggle='a', .key=0 };
    if (argparse(argc, argv, &options) < 0) {
        return 0;
    }

    if (options.key == 0) {
        options.key = 1;
    }


    return 0;
}