"""
Determine whether or not a C header file is self-sufficient.

That is, determine if a C header file satisfies these two properties:
    1. Is self-contained: the header can be included on its own, with no other context provided
    2. Is idempotent: the header can be included more than once

We determine if both of these properties are satisfied by producing C source code that does nothing other than
include the header file twice and then we check to see if such a source file can be successfully compiled.

This script allows the user to provide paths to multiple header files, and the script checks each one in turn.

This script produces an exit code with a value of:
    0: if all mentioned header files pass the described test
    1: if any mentioned header files do NOT pass the described test

The user is expected to provide these two things to this script
    1. A non-empty list of paths to header files to test
    2. A shell expression that executes a compiler appropriately configured to compile each of the header files, and accepts source code from STDIN
        - We expect that the compilation of the source code was successful if and only if this compiler shell expression returns 0 when executed

FYI: the approach taken in this script was inspired by this Stackoverflow answer: https://stackoverflow.com/a/1892332
"""

import argparse
import logging
import subprocess
import sys


def header_is_self_sufficient(path_to_header: str, compiler_command: str) -> bool:
    """Return True if an only if the header satisfies our definition of self-sufficient"""

    source_code = f"""
        #include "{path_to_header}" /* Check self-containment */
        #include "{path_to_header}" /* Check idempotency */

        int main(void) {{
            return 0;
        }}
        """

    result = subprocess.run(compiler_command, shell=True, input=source_code.encode())
    # We assume that compilation was successful if and only if the call to the compiler resulted in a return code of 0.
    return result.returncode == 0


######################################################
# Set up command line argument parsing
######################################################

parser = argparse.ArgumentParser(
    description=__doc__,
    formatter_class=argparse.RawDescriptionHelpFormatter
)

parser.add_argument('--paths_to_headers', nargs='+', required=True, help='Paths to header files')
parser.add_argument('--compiler_shell_expression', nargs='?', required=True, help='The shell expression for compiling the header file, which should accept input C source code on stdin, and return a non-zero exit code exactly when compilation is not successful')

args = parser.parse_args()


######################################################
# Test each header files in turn,
# and produce an exit code of 0 if and only if all of them are self-sufficient.
######################################################

exit_code = 0
for path_to_header in args.paths_to_headers:
    logging.info(f'Checking the self-sufficiency of header: {path_to_header}')

    is_self_sufficient = header_is_self_sufficient(path_to_header, args.compiler_shell_expression)

    if not is_self_sufficient:
        logging.error(f'This header was found to be NOT self-sufficient: {path_to_header}')
        exit_code = 1

sys.exit(exit_code)
