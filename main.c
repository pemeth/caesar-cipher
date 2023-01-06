#include <stdio.h>

#include "argparse.h"

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


    return 0;
}