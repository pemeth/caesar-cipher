# caesar-cipher

A simple Caesar cipher written in C. The plaintext is read from `stdin` until EOF and the ciphertext is printed to `stdout`.

## Usage

    Usage: ./caesar [-k key] [-p] [-e | -d] [-h]
    Encode a message via the Caesar cipher with the specified key.

    Encodes only characters of the alphabet unless -p is specified,
    in which case all printable characters are encoded.

    -k key  use this cipher key (may be [-128,127], defaults to 1)
    -p      use all printable ASCII characters as alphabet
    -e      encode with specified key - this is the default
    -d      decode with specified key that was used for encoding
    -h      print this message and exit

The default behaviour is to encode using key "1" while encoding only alphabet characters. To decode a message,
use the same options as during encoding, only specifying the `-d` option for decoding. If multiple options of
the same type are specified, the last is used (e.g. `./caesar -k 2 -k 6`, the used key is "6").

## Examples

### Encoding

Encode the text "Caesar 0123" with default key "1" and default alphabet:

    printf 'Caesar 0123' | ./caesar

Output:

    Dbftbs 0123

Encode the text "Caesar 0123" with key "15" using all printable ASCII characters:

    printf 'Caesar 0123' | ./caesar -k 15 -p

Output:

    Rpt#p"/?@AB

### Decoding

Decode "Dbftbs 0123" with original key "1":

    printf 'Dbftbs 0123' | ./caesar -d -k 1

Output:

    Caesar 0123

Decode "Rpt#p"/?@AB" with original key "15" using all printable ASCII characters:

    printf 'Rpt#p"/?@AB' | ./caesar -d -k 15 -p

Output:

    Caesar 0123
