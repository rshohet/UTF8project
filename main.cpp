#include <stdio.h>
#include <stdlib.h>

// calculate the length of a string based on bytes
int regular_strlen(unsigned char *string){
    int len = 0;
    while (string[len] != '\0'){
        len++;
    }
    return len;
}

// calculate the length of a string based on characters
int my_utf8_strlen(unsigned char *string){
    int i = 0;
    int length = 0;
    while (string[i] != '\0') {
        // check the hex of the character and compare it to the max hex value for the first byte to determine how many
        // bytes the char is (based on the wiki page). Skip that many chars and add 1 to the length
        if (string[i] >= 0x0 && string[i] < 0x7F) { // this means the ith char is 1 byte
            i += 1;
            length += 1;
        }else if (string[i] >= 0xF0) { // this means the ith char is 4 bytes
            i += 4;
            length += 1;
        } else if (string[i] >= 0xE0 && string[i] < 0xF0) { // this means the ith char is 3 bytes
            i += 3;
            length += 1;
        } else if (string[i] >= 0xC0 && string[i] <= 0xE0) { // this means the ith char is 2 bytes
            i += 2;
            length += 1;
        }
    }
    return length;
}

// convert hex digit to binary (4 bits)
char* hex_to_bin(char hexDigit){
    int num;
    char *binArr[16] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110",
                        "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};

    if (hexDigit >= '0' && hexDigit <= '9') {
        num = hexDigit - '0'; // bc this will subtract the ascii to convert it from string to literal digit

    } else if (hexDigit == 'a' || hexDigit == 'A') {
        num = 10;

    } else if (hexDigit == 'b' || hexDigit == 'B') {
        num = 11;

    } else if (hexDigit == 'c' || hexDigit == 'C') {
        num = 12;

    } else if (hexDigit == 'd' || hexDigit == 'D') {
        num = 13;

    } else if (hexDigit == 'e' || hexDigit == 'E') {
        num = 14;

    } else if (hexDigit == 'f' || hexDigit == 'F') {
        num = 15;

    } else {
        printf("Invalid hex digit: %c\n", hexDigit);
    }
    return binArr[num];
}

// convert binary (4 bits) to hex
char bin_to_hex(char* binary){
    char digit;

    if (binary[0] == '0' && binary[1] == '0' && binary[2] == '0' && binary[3] == '0'){
        digit = '0';
    } else if (binary[0] == '0' && binary[1] == '0' && binary[2] == '0' && binary[3] == '1'){
        digit = '1';
    } else if (binary[0] == '0' && binary[1] == '0' && binary[2] == '1' && binary[3] == '0'){
        digit = '2';
    } else if (binary[0] == '0' && binary[1] == '0' && binary[2] == '1' && binary[3] == '1'){
        digit = '3';
    } else if (binary[0] == '0' && binary[1] == '1' && binary[2] == '0' && binary[3] == '0'){
        digit = '4';
    } else if (binary[0] == '0' && binary[1] == '1' && binary[2] == '0' && binary[3] == '1'){
        digit = '5';
    } else if (binary[0] == '0' && binary[1] == '1' && binary[2] == '1' && binary[3] == '0'){
        digit = '6';
    } else if (binary[0] == '0' && binary[1] == '1' && binary[2] == '1' && binary[3] == '1'){
        digit = '7';
    } else if (binary[0] == '1' && binary[1] == '0' && binary[2] == '0' && binary[3] == '0'){
        digit = '8';
    } else if (binary[0] == '1' && binary[1] == '0' && binary[2] == '0' && binary[3] == '1'){
        digit = '9';
    } else if (binary[0] == '1' && binary[1] == '0' && binary[2] == '1' && binary[3] == '0'){
        digit = 'A';
    } else if (binary[0] == '1' && binary[1] == '0' && binary[2] == '1' && binary[3] == '1'){
        digit = 'B';
    } else if (binary[0] == '1' && binary[1] == '1' && binary[2] == '0' && binary[3] == '0'){
        digit = 'C';
    } else if (binary[0] == '1' && binary[1] == '1' && binary[2] == '0' && binary[3] == '1'){
        digit = 'D';
    } else if (binary[0] == '1' && binary[1] == '1' && binary[2] == '1' && binary[3] == '0'){
        digit = 'E';
    } else if (binary[0] == '1' && binary[1] == '1' && binary[2] == '1' && binary[3] == '1') {
        digit = 'F';
    }
    return digit;
}

// calculates the number of bytes a character is based on the first byte
int num_bytes(unsigned char string) {
    int bytes = 0;
    if (string >= 0x00 && string <= 0x7F) { // this means the char is 1 byte
        bytes = 1;
    } else if (string >= 0xF0 && string <= 0xF4) { // this means the char is 4 bytes
        bytes = 4;
    } else if (string >= 0xE0 && string <= 0xEF) { // this means the char is 3 bytes
        bytes = 3;
    } else if (string >= 0xC2 && string <= 0xDF) { // this means the char is 2 bytes
        bytes = 2;
    }else
        return -1;
    return bytes; // return the number of bytes the char is
}

// calculates the number of bytes a unicode is based on the first digit
int num_byte_unic(unsigned char *input){
    int bytes = 0;
    if (input[0] == '0' && input[1] == '0') { // either 1 or 2 bytes
        if (input[2] >= '0' && input[2] <= '7') // this means 1 byte 0001 - 007F
            bytes = 1;
        else if (input[2] == '8' || input[2] == '9' || (input[2] >= 'A' && input[2] <= 'F')) // this means 2 bytes 0080
            bytes = 2;
    } else if (input[0] == '0' && (input[1] >= '0' && input[1] <= '7')) { // this means 2 bytes 07FF
        bytes = 2;
    } else if (input[0] == '0' && (input[1] == '8' || input[1] == '9'|| (input[2] >= 'A' && input[2] <= 'F'))){ // this  is 3 bytes 0800 - 0FFF
        bytes = 3;
    } else if ((input[0] >= '1' && input[0] <= '9') || (input[0] >= 'A' && input[0] <= 'F')){ // this  is 3 bytes 1000 - FFFF
        bytes = 3;
    } else if (input[0] >= 0xC2 && input[0] <= 0xDF) { // this means the ith char is 2 bytes
        bytes = 2;
    }else
        printf("Invalid: %c\n", input[0]);
    return bytes;
}

// Encoding a UTF8 string, taking as input an ASCII string, with UTF8 characters encoded using the Codepoint numbering
// scheme notation, and returns a UTF8 encoded string.
int my_utf8_encode(unsigned char *input, unsigned char *output) {
    int loop = 0;
    int while_int = 0;
    unsigned char *fullUnicode = input;
    while (regular_strlen(fullUnicode) > 0) {
        if (fullUnicode[0] == '\\') { // if input is as unicode
            fullUnicode = fullUnicode + 2; // strip off the \u
//            printf("new input %s\n", fullUnicode);

            int unic = 0;
            unsigned char unicode[] = "0000";
            while (fullUnicode[unic] != '\\' && fullUnicode[unic] != ' ' && fullUnicode[unic] !=
                                                '\0') { // find length of the char by stopping once hit next char or end of string
                unicode[unic] = fullUnicode[unic];
                unic++;
            }
            unicode[unic] = '\0';
            fullUnicode = fullUnicode + unic;

            char *hexBin;
            unsigned char *binaryUTF = NULL; // used malloc for binaryUTF so I can alter the size and use that later
            binaryUTF = (unsigned char *) malloc(50);
            if (binaryUTF == NULL) {
                fprintf(stderr, "Memory allocation error\n");
                exit(EXIT_FAILURE);
            }

            int input_length = my_utf8_strlen(unicode);
            char fullBinary[] = "000000000000000000000";

            int num_bytes = 0;

            // if this unicode is called with 4 hex digits, it can be either 1, 2, or 3 bytes in UTF-8
            if (input_length == 4) {
                if (unicode[0] == '0' && unicode[1] == '0' && unicode[2] < '8') { // it requires 1 byte
//                    printf("1 BYTES\n");
                    num_bytes = 1;
                    binaryUTF[0] = '0'; // first bit is 0

                    // only want to convert the last 2 hex digits to binaryUTF and use only the last 3 bits of first digit,
                    int j = 0; // keep track of which binaryUTF digit we're up to in the binaryUTF array
                    hexBin = hex_to_bin(unicode[2]);
                    binaryUTF[++j] = hexBin[1];
                    binaryUTF[++j] = hexBin[2];
                    binaryUTF[++j] = hexBin[3];
//                    printf("ANSWER byte %s\n", binaryUTF);
                    hexBin = hex_to_bin(unicode[3]);
                    binaryUTF[++j] = hexBin[0];
                    binaryUTF[++j] = hexBin[1];
                    binaryUTF[++j] = hexBin[2];
                    binaryUTF[++j] = hexBin[3];
//                    printf("ANSWER byte %s\n", binaryUTF);
                }
                if (unicode[0] == '0' && unicode[1] < '8' && unicode[2] >= '8') { // it requires 2 bytes
//                    printf("2 BYTES\n");
                    num_bytes = 2;
                    int binLength = 12; // length of binary string since 2 or 3 hex digits
                    int j = -1; // keep track of which binary digit we're up to in the binary array
                    for (int i = 0; i < input_length - 1; i++) { // skip the first hex digit bc always 0
                        hexBin = hex_to_bin(unicode[i + 1]); // skip the first hex digit bc always 0
//                        printf("hexBin %s\n", hexBin);
                        for (int k = 0;
                             k <
                             4; k++) { // go through the binary converted string and append to the full binary string
                            fullBinary[++j] = hexBin[k];
//                            printf("i = %d and k = %c and index = %d\n", i, hexBin[k], j);
                        }
                    }
//                    printf("full binaryUTF %s\n", fullBinary);

                    binaryUTF[0] = '1'; // 1st bit is 1
                    binaryUTF[1] = '1'; // 2nd bit is 1
                    binaryUTF[2] = '0'; // 3rd bit is 0
                    binaryUTF[8] = '1'; // 8th bit is 1
                    binaryUTF[9] = '0'; // 9th bit is 0

                    j = 3; // keep track of which binaryUTF digit we're up to in the resulting UTF Binary array

                    for (int i = 1;
                         i < binLength; i++) { // start at 1 bc for 2 byte encodings, skip the 0th bit of the 12 bits
                        if (j != 8) {
                            binaryUTF[j] = fullBinary[i];
                            j++;
                        } else if (j == 8) {// skip locations 8 and 9 and add after
                            j = 10;
                            binaryUTF[j] = fullBinary[i];
                            j++;
                        }
                    }
                }
                if (unicode[0] >= '1' ||
                    unicode[1] >= '8') { //'0' && unicode[1] < '8' && unicode[2] >= '8') { // it requires 3 bytes
//                    printf("3 BYTES\n");
                    num_bytes = 3;
                    int binLength = 16; // length of binary string since 3 or 4 hex digits
                    int j = -1; // keep track of which binary digit we're up to in the binary array
                    for (int i = 0; i < input_length; i++) {
                        hexBin = hex_to_bin(unicode[i]);
//                        printf("hexBin %s\n", hexBin);
                        for (int k = 0;
                             k < 4; k++) {// go through the binary converted string and append to the full binary string
                            fullBinary[++j] = hexBin[k];
//                            printf("i = %d and k = %c and index = %d\n", i, hexBin[k], j);
                        }
                    }
//                    printf("full binaryUTF %s\n", fullBinary);
                    binaryUTF[0] = '1'; // 1st bit is 1
                    binaryUTF[1] = '1'; // 2nd bit is 1
                    binaryUTF[2] = '1'; // 3rd bit is 1
                    binaryUTF[3] = '0'; // 4th bit is 0
                    binaryUTF[8] = '1'; // 8th bit is 1
                    binaryUTF[9] = '0'; // 9th bit is 0
                    binaryUTF[16] = '1'; // 16th bit is 1
                    binaryUTF[17] = '0'; // 17th bit is 0

                    j = 4; // keep track of which binaryUTF digit we're up to in the resulting UTF Binary array
                    for (int i = 0; i < binLength; i++) {
                        if (j != 8 && j != 16) {
                            binaryUTF[j] = fullBinary[i];
//                            printf("i = %d and adding %c and count = %d and full is %s \n", i, fullBinary[i], j,
//                                   binaryUTF);
                            j++;
                        } else if (j == 8) {// skip locations 8 and 9 and add after
                            j = 10;
                            binaryUTF[j] = fullBinary[i];
//                            printf("i = %d and adding %c and count = %d and full is %s \n", i, fullBinary[i], j,
//                                   binaryUTF);
                            j++;
                        } else if (j == 16) {// skip locations 16 and 17 and add after
                            j = 18;
                            binaryUTF[j] = fullBinary[i];
                            j++;
                        }
                    }

                }

                // if called with more than 4 hex digits, it is 4 bytes in UTF-8
            } else if (input_length > 4) {
//                printf("4 BYTES\n");
                num_bytes = 4;
                int binLength = 21; // length of binary string since 5 or 6 hex digits

                int j = -1; // keep track of which binary digit we're up to in the binary array
                int i = 0; // for the loop to loop through the binaryUTF string
                if (input_length == 5) { // then need to add an extra 0 bit to the beginning of the binary array
                    fullBinary[0] = '0';
                    j++;
                } else if (input_length ==
                           6) { // then the hex digit begins with a 1 which in binary is 0001 and only use the 1 from the binary conversion in the binary string
                    fullBinary[0] = '1';
                    j++;
                    i = 1; // skip the first digit since just dealt with it
                }

                for (; i < input_length; i++) {
                    hexBin = hex_to_bin(unicode[i]);
//                    printf("hexBin %s\n", hexBin);
                    for (int k = 0;
                         k < 4; k++) {// go through the binary converted string and append to the full binary string
                        fullBinary[++j] = hexBin[k];
//                        printf("i = %d and k = %c and index = %d\n", i, hexBin[k], j);
                    }
                }
//                printf("full binaryUTF %s\n", fullBinary);
                binaryUTF[0] = '1'; // 1st bit is 1
                binaryUTF[1] = '1'; // 2nd bit is 1
                binaryUTF[2] = '1'; // 3rd bit is 1
                binaryUTF[3] = '1'; // 4th bit is 0
                binaryUTF[4] = '0'; // 5th bit is 0
                binaryUTF[8] = '1'; // 8th bit is 1
                binaryUTF[9] = '0'; // 9th bit is 0
                binaryUTF[16] = '1'; // 16th bit is 1
                binaryUTF[17] = '0'; // 17th bit is 0
                binaryUTF[24] = '1'; // 24th bit is 1
                binaryUTF[25] = '0'; // 25th bit is 0

                j = 5; // keep track of which binaryUTF digit we're up to in the resulting UTF Binary array
                for (i = 0; i < binLength; i++) {
                    if (j != 8 && j != 16 && j != 24) {
                        binaryUTF[j] = fullBinary[i];
                        j++;
                    } else if (j == 8) {// skip locations 8 and 9 and add after
                        j = 10;
                        binaryUTF[j] = fullBinary[i];
                        j++;
                    } else if (j == 16) {// skip locations 16 and 17 and add after
                        j = 18;
                        binaryUTF[j] = fullBinary[i];
                        j++;
                    } else if (j == 24) {// skip locations 24 and 25 and add after
                        j = 26;
                        binaryUTF[j] = fullBinary[i];
                        j++;
                    }
                }
            }


            // convert the binaryUTF string to hex
            int lenUTF = my_utf8_strlen(binaryUTF);
            unsigned char hexUTF8[3 * num_bytes]; // Assuming 2 characters per byte and space for null terminator
            int hi = 0;
            unsigned char temp[10];
            temp[0] = '\\';
            temp[1] = 'x';
            int t = 2;
            int j = 0; // keep track of where in hex array we are
            char prev;
            for (int i = 0; i < lenUTF; i += 4) {
                hi++;
//                printf("i = %d\n", i);
                char bin[4];
                for (int k = 0; k < 4; k++) { // get the 4 bits of the binaryUTF
                    bin[k] = binaryUTF[i + k];
                }
                char hex_dig = bin_to_hex(bin); // so have the hex digit

                // if we passed 2 hex digits, then it is 1 byte and convert it to a character and add to the output string
                if (hi % 2 == 0){
                    temp[t++] = prev;
                    temp[t++] = hex_dig;
                    temp[t] = '\0';

                    // convert the hex to a char and add to the hexUTF8 array
                    char hexEncode[3] = {temp[t-2], temp[t-1], '\0'};
                    int len_output = regular_strlen(output);
                    sscanf(hexEncode, "%2hhX", &output[len_output]);
                    output[len_output + 1] = '\0';
                }
                prev = hex_dig;
//                hexUTF8[j++] = hex_dig;
            }
            free(binaryUTF);
            loop = loop + my_utf8_strlen(hexUTF8);

        }

        else{ // it's a real character
            int i = 0;
            char hexchar[3];
            int len_output = regular_strlen(output);
            output[len_output] = fullUnicode[0];
            output[len_output+1] = '\0';
            fullUnicode = fullUnicode + 1;

        }
        while_int++;

    }

    printf("OUTPUT %s\n", output);
    return 1;

}

//E0 to EF hex (224 to 239): first byte of a three-byte sequence.
//F0 to FF hex (240 to 255): first byte of a four-byte sequence.
//https://www.fileformat.info/info/unicode/utf8.htm
// a hex UTF-8 can never begin with A or B - only 0, 1, C, D, E, F & the subsequent bytes can only begin with 8,9,A,B
int my_utf8_check(unsigned char *string){
    if (my_utf8_strlen(string) > 2) {
        if (string[0] != 'C' && string[0] != 'D' && string[0] != 'E' && string[0] != 'F') {
//            printf("1 ERROR: %s is not a valid UTF-8 hex\n", string);
            return 0;
        }
        if (string[0] == 'C' && string[1] < '2') { // if C is the start of a 2-byte sequence , can't be less than C2
//            printf("1 ERROR: %s is not a valid UTF-8 hex\n", string);
            return 0;
        }
        if (string[0] == 'F' && !(string[1] >= '0' && string[1] <= '7')) {
//            printf("2 ERROR: %s is not a valid UTF-8 hex\n", string);
            return 0;
        }
        for (int i = 1; i <= my_utf8_strlen(string); i++) {
            if (i == 3 || i == 6 || i == 9) { // if it's the first digit of subsequent bytes it can only be 8,9,A,B
                if (string[i] != 'A' && string[i] != 'B' && string[i] != '8' && string[i] != '9') {
//                    printf("3 ERROR: %s is not a valid UTF-8 hex\n", string);
                    return 0;
                }
            }else if (i == 2 || i == 5 || i == 8 || i == 11){ // skip the spaces
                continue;
            }else{
                if (string[i] < '0' || (string[i] > '9' && string[i] < 'A') || string[i] > 'F') {
//                    printf("4 ERROR: %s is not a valid UTF-8 hex\n", string);
                    return 0;
                }
            }
        }
    // it's 1 byte, so it is ascii and must be between 00 and 7F
    }else{
        if (string[0] < '0' || string[0] > '7') {
//            printf("5 ERROR: %s is not a valid UTF-8 hex\n", string);
            return 0;
        }
        if (my_utf8_strlen(string) == 2){
            if (string[1] < '0' || (string[1] > '9' && string[1] < 'A') || string[1] > 'F') {
//                printf("6 ERROR: %s is not a valid UTF-8 hex\n", string);
                return 0;
            }
        }
    }
    printf("%s is a valid UTF-8 hex\n", string);
    return 1;
}

//Returns the UTF8 encoded character at the location specified.
unsigned char* my_utf8_charat(unsigned char* string, int index) {
    int j = 0; // to loop through the actual characters of the string
    while (j != index) {
        j++;

        // increment the string's pointer by the number of bytes the char is, so after each loop, string begins with the next char, not the next byte
        string += num_bytes(string[0]); // strip off one character from the string at a time until find the index and do this by incrementing by how many bytes the char is
    }
    printf("char at index %d = %s\n", index, string);
    return &string[0];
}


//Returns whether the two strings are the same
int my_utf8_strcmp(unsigned char *string1, unsigned char *string2){
    int i = 0;
    if (my_utf8_strlen(string1) == 1 && my_utf8_strlen(string2) == 1){
        if (string1[0] < string2[0]) {
            printf("1: string1 %s is before string2 %s\n", string1,
                   string2); // need to write string bc prints weird in hebrew
            return 1;
        } else if (string1[0] > string2[0]){
            printf("-1: string1 %s is after string2 %s\n", string1,
                   string2); // need to write string bc prints weird in hebrew
            return -1;
        }else{
            printf("0: string1 %s = string2 %s\n", string1,
                   string2);
            return 0;
        }
    }
    // while we haven't reached the end of either string
    while (string1[i] != '\0' && string2[i] != '\0'){
        if (string1[i] < string2[i]){
            printf("1: string1 %s is before string2 %s\n", string1, string2); // need to write string bc prints weird in hebrew
            return 1;
        }
        else if (string1[i] > string2[i]){
            printf("-1: string1 %s is after string2 %s\n", string1, string2);
            return -1;
        }
        i++;
    }
    // if we get here, either they're the same or one of the strings is shorter than the other
    //this case, they are the same string
    if (string1[i] == '\0' && string2[i] == '\0'){
        printf("0: string1 %s = string2 %s\n", string1, string2);
        return 0;
    }
        // StringA is shorter so before
    else if (string1[i] == '\0'){
        printf("1: string1 %s is before string2 %s\n", string1, string2); // need to write string bc prints weird in hebrew
        return 1;
    }
    else {
        printf("-1: string1 %s is after string2 %s\n", string1, string2);
        return -1;
    }
}

// take a string and copy it from the  beginning of it until the desired number of characters and append it to destination
int my_utf8_strncpy(unsigned char *dest, unsigned char *source, int num_char) {
    int i = 0; // to loop through the bytes of the string
    int j = 0; // to loop through the actual characters of the string
    while (j < num_char) {
        // check the hex of the character and compare it to the max hex value for the first byte to determine how many
        // bytes the char is (based on the wiki page). Skip that many chars and add 1 to the length
        if (source[i] >= 0x0 && source[i] < 0x7F) { // this means the ith char is 1 byte
            dest[j] = source[i];
            i += 1;
            j += 1;
        } else if (source[i] >= 0xF0) { // this means the ith char is 4 bytes
            for (int b = 0; b < 4; b++) {
                dest[i + b] = source[i + b];
            }
            i += 4;
            j += 1;
        } else if (source[i] >= 0xE0 && source[i] < 0xF0) { // this means the ith char is 3 bytes
            for (int b = 0; b < 3; b++) {
                dest[i + b] = source[i + b];
            }
            i += 3;
            j += 1;
        } else if (source[i] >= 0xC0 && source[i] <= 0xE0) { // this means the ith char is 2 bytes
            for (int b = 0; b < 2; b++) {
                dest[i+b] = source[i+b];
            }
            i += 2;
            j += 1;
        }
    }
    dest[i] = '\0'; // need to terminate w null character
    return 1;
}

// count how many times a character appeared in the string
int my_utf8_chr_count(unsigned char* str, unsigned char* ch){
    // check how many bytes the input character is
    int bytes = 0;
//    printf("string %s\n", str);
    char whole[2];
    whole[0] = ch[0];
    whole[1] = ch[1];

    bytes = num_bytes(ch[0]);
//    printf("bytes = %d\n", bytes);
    int i = 0;
    int ind = 0;
    int seen = 0;
    while (str[i] != '\0'){
        for (int b = 0; b < bytes; b++){ // check that for each byte of the letter, the string's bytes are the same
            if (str[i+b] != ch[b]){ // not equal, so stop checking that byte
                break;
            }
            if (b == bytes - 1){
//                printf("FOUND at index %d !\n", ind);
                seen += 1;
            }
        }
        ind++;
        i += num_bytes(str[i]);
    }
    if (seen == 0){
//        printf("NOT FOUND!\n");
        return 0;
    }
    return seen;
}


// return a substring of a string from the start index to the end index
unsigned char* my_utf8_substring(unsigned char* string, int start, int end){
    unsigned char* new_string = my_utf8_charat(string, start); // use my_utf8_charat to get the char at the start index, so the string begins at that character
//    printf("string = %s\n", new_string);
    int j = 0; // to loop through the actual characters of the string
    int bytes = 0; // bytes of the chars thus far in the string
    int len = end - start + 1; // length of the substring
    while ((j < len) && new_string[bytes] != '\0') {
        bytes += num_bytes(new_string[bytes]); // strip off one character from the string at a time until find the index and do this by incrementing by how many bytes the char is
        j++;
    }
    new_string[bytes] = '\0'; // need to terminate w null character
    return new_string;
}

// Takes a UTF8 encoded string, and returns a string, with ASCII representation where possible, and UTF8 character
// representation for non-ASCII characters.
int my_utf8_decode(unsigned char *input, unsigned char *output){
    // loop through the input string and convert each utf hex to binary, then to unicode hex and add to output string (unless ascii then convert to ascii)
    unsigned char hex[7];
    int index1 = 0;
    int len_input = my_utf8_strlen(input);
//    printf("len input %d\n", len_input);
    int o = 0; // keep track of where we are in output string
    char prev; // keep track of the previous char in the input string
    while (input[index1] != '\0' ){
//        int h = 0; // keep track of where we are at in the hex string
        prev = input[index1];
        int h = 0;
        for (; h < 2; h++){
            hex[h] = input[index1++];
        }
        hex[h] = '\0'; // terminate hex with null character

        if (input[index1] != '\0') { // if not at the end of the input string
            index1 += 1; // increment by 2 so always at the beginning of a new byte of the utf string and then add 1 for spaces between bytes
        }

        // loop until reach next hex that signals a new char
        while ((prev == 'C' || prev == 'D' || prev == 'E' || prev == 'F') && ((input[index1] >= '0' && input[index1] <= '9') || ( input[index1] == 'A' ||  input[index1] == 'B'))){
//            printf("WHILE\n");
            hex[h++] = ' ';// add spaces between each byte

            hex[h++] = input[index1++];
            hex[h++] = input[index1++];

            if (input[index1] != '\0')  // if not at the end of the input string
                index1 += 1; // increment by 2 so always at the beginning of a new byte of the utf string and then add 1 for spaces between bytes
//            printf("HERE IS HEX %s index = %d \n", hex, index1);

        }
        // now have the full charachter in hex
        hex[h] = '\0'; // need to terminate w null character

        // check how many bytes the input utf8 is
        int bytes = 0;
        int utf_len = 0;
        unsigned char binary[35];
        if (hex[0] >= '0' && hex[0] <= '7') { // know 1 byte if begins with 0-7 - so ascii

            // convert the string hex to an int so can print the ascii character
            int a = hex[0] - '0';
            int b = 0;
            if (hex[1] >= '0' && hex[1] <= '9'){
                b = hex[1] - '0';
            } else if(hex[1] >= 'A' && hex[1] <= 'F'){
                b = hex[1] - 'A' + 10;
            }
            int ascii = (a * 16) + b; // convert from hex to decimal = ith val * 16^i + i-1val * 16^i-1 + ... + 0val * 16^0
//            printf("ASCII %c\n", ascii);
            output[o++] = (char) ascii;
            output[o] = '\0'; // need to terminate w null character
//            printf("OUTPUT %s\n", output);

        }else { // not ascii
//            printf("HEX NON ASCII %s\n", hex);
            if (hex[0] == 'C' || hex[0] == 'D') { // know 2 bytes if begins with C or D
                bytes = 2;
                int j = 0; // keep track of where we are at in the binary string
                for (; j < 5; j++) { // fill in the first 5 bit of the binary string with 0s
                    binary[j] = '0';
                }

                utf_len = (bytes * 2) + (bytes - 1); // the length of the utf8 string is bytes, each with 2 hex digits + (bytes - 1) for the space
                for (int i = 0; i < utf_len; i++) {
                    // skip the spaces
                    if (i == 2) // skip the spaces in the utf8 string
                        continue;
                    else {
                        // convert the hex to binary
                        char *bin = hex_to_bin(hex[i]); // convert the hex to binary - but this will be UTF8 binary
                        if (i == 0) { // if it's the first utf digit, we only want the last bit of its conversion (bc 110 is a given)
                            binary[j++] = bin[3];
                        } else if (i == 1 || i == 4) { // the 2nd utf digit and the last are completely added
                            binary[j++] = bin[0];
                            binary[j++] = bin[1];
                            binary[j++] = bin[2];
                            binary[j++] = bin[3];
                        } else if (i == 3) { // the 4th utf digit only uses the last 2 bits
                            binary[j++] = bin[2];
                            binary[j++] = bin[3];
                        }
                    }
//                    printf("2 binary = %s\n", binary);
                }
                binary[j] = '\0'; // need to terminate w null character
//                printf("2 binary = %s\n", binary);
            } else if (hex[0] == 'E') { // know 3 bytes if begins with E
                bytes = 3;
                utf_len = (bytes * 2) + (bytes -
                                         1); // the length of the utf8 string is 2 bytes, each with 2 hex digits + (bytes - 1) for the space
                int j = 0; // keep track of where we are at in the binary string
                for (int i = 1; i < utf_len; i++) { // completely skip first utf char since it's always 1111
                    // skip the spaces
                    if (i == 2 || i == 5 || i == 8) // skip the spaces in the utf8 string
                        continue;
                    else {
                        // convert the hex to binary
//                        printf("CONVEETING HEX DIG %c of hex = %s\n", hex[i], hex);
                        char *bin = hex_to_bin(hex[i]);
                        if (i == 1 || i == 4 ||
                            i == 7) { // the 2nd utf digit, the 3 digit, and the last are completely added
                            binary[j++] = bin[0];
                            binary[j++] = bin[1];
                            binary[j++] = bin[2];
                            binary[j++] = bin[3];
                        } else if (i == 3 || i == 6) { // the 4th and 7th utf digit only uses the last 2 bits
                            binary[j++] = bin[2];
                            binary[j++] = bin[3];
                        }
                    }
//                    printf("3 binary = %s\n", binary);
                }
                binary[j] = '\0'; // need to terminate w null character
//                printf("3 binary = %s\n", binary);
            } else if (hex[0] == 'F') { // know 4 bytes if begins with F
//                printf("HEXXXXXXX %s\n", hex);
                bytes = 4;
                utf_len = (bytes * 2) + (bytes -
                                         1); // the length of the utf8 string is 2 bytes, each with 2 hex digits + (bytes - 1) for the space

                int j = 0; // keep track of where we are at in the binary string
                for (int i = 1; i < utf_len; i++) { // completely skip first utf char since it's always 1111
                    // skip the spaces
                    if (i == 2 || i == 5 || i == 8) // skip the spaces in the utf8 string
                        continue;
                    else {
                        // convert the hex to binary
//                        printf("CONVERTING HEX DIG %c of hex = %s len = %d\n", hex[i], hex, len_hex);
                        char *bin = hex_to_bin(hex[i]);
                        if (i == 1) { // skip the first binary of the 2nd hex digit since always 0
                            if (bin[1] == '1') { // if the 2nd binary digit is 1, then need to add an extra hex digits - so 6, but if it's 0, then only 5 hex digits
                                binary[j++] = '0'; // add extra preceding zeros to make an extra hex digit
                                binary[j++] = '0';
                                binary[j++] = '0';
                                binary[j++] = bin[1];
                            }
                            binary[j++] = bin[2];
                            binary[j++] = bin[3];
                        } else if (i == 4 || i == 7 || i == 10) { // the 3rd utf digit and the last are completely added
                            binary[j++] = bin[0];
                            binary[j++] = bin[1];
                            binary[j++] = bin[2];
                            binary[j++] = bin[3];
                        } else if (i == 3 || i == 6 || i == 9) { // the 4th and 7th utf digit only uses the last 2 bits
                            binary[j++] = bin[2];
                            binary[j++] = bin[3];
                        }
//                        printf("i = %d BIN = %s binary = %s\n", i, bin, binary);

                    }
                }
                binary[j] = '\0'; // need to terminate w null character
            }
//            printf("final binary = %s o = %d\n", binary, o);
            int len_output = my_utf8_strlen(binary);

            output[o++] = '\\'; // add u+ to the beginning of the output
            output[o++] = 'u';
            for (int i = 0; i < len_output; i += 4) {
                char bin[4];
                int b = 0;
                for (; b < 4; b++) { // get the binary to convert to hex
                    bin[b] = binary[i + b];
                }
                char hex_con = bin_to_hex(bin); // convert the binary to hex
//                printf("loop J = %d\n", o);
                output[o++] = hex_con; // add the hex to the output
            }
//            printf("post loop J = %d\n", o);
            output[o] = '\0'; // need to terminate w null character
//            printf("OUTPUT %s\n", output);
        }
    }
    printf("OUT %s\n", output);
    return 1;
}

//TEST STRLEN
int test_strlen(unsigned char *input, int expected) {
    int output = my_utf8_strlen(input);
    if (output == expected) {
        printf("SUCCESS: %s --> %d \n", input, output);
        return 1;
    } else {
        printf("FAILURE: %s --> %d (expected %d) \n", input, output, expected);
        return 0;
    }
}

//TEST STRCMP
int test_strcmp(unsigned char *input1, unsigned char *input2, int expected) {
    int output = my_utf8_strcmp(input1, input2);
    if (output == expected) {
        printf("SUCCESS: %s --> %d \n", input1, output);
        return 1;
    } else {
        printf("FAILURE: %s --> %d (expected %d) \n", input1, output, expected);
        return 0;
    }
}

//test encode
int test_encode(unsigned char *input, unsigned char *expected) {
    unsigned char output[100] = {0};
    my_utf8_encode(input, output);

    if (my_utf8_strcmp(output, expected) == 0) {
        printf("SUCCESS: %s -> %s\n", input, output);
        return 1;
    } else {
        printf("FAILURE: %s -> %s (expected %s)\n", input, output, expected);
        return 0;
    }
}


//test substring
int test_substring(unsigned char *input, int start, int end, unsigned char *expected) {
    unsigned char* ans = my_utf8_substring(input, start, end);
    if (my_utf8_strcmp(ans, expected) == 0) {
        printf("SUCCESS: %s \n", ans);
        return 1;
    } else {
        printf("FAILURE: %s)\n", ans);
        return 0;
    }
}

//TEST CHR COUNT
int test_chr_count(unsigned char *input,  unsigned char* ch,  int expected) {
    int output = my_utf8_chr_count(input, ch);
    if (output == expected) {
        printf("SUCCESS: %s found %c -> %d \n", input, ch, output);
        return 1;
    } else {
        printf("FAILURE: %s %d but expected %d \n", input, output, expected);
        return 0;
    }
}

// test strncpy
int test_strncpy(unsigned char *input, int num_char, unsigned char *expected) {
    unsigned char output[100] = {0};
    my_utf8_strncpy(output, input, num_char);
    if (my_utf8_strcmp(output, expected) == 0) {
        printf("SUCCESS: %s -> %s\n", input, output);
        return 1;
    } else {
        printf("FAILURE: %s -> %s (expected %s)\n", input, output, expected);
        return 0;
    }
}

int test_charat(unsigned char *input, int index, unsigned char *expected) {
    unsigned char *output = my_utf8_charat(input, index);
    if (*output == expected[0]) {
        printf("SUCCESS: %c -> %s\n", *output, input);
        return 1;
    } else {
        printf("FAILURE: %s -> %c (expected %c)\n", input, *output, expected[0]);
        return 0;
    }
}

int test_check(unsigned char *input, int expected) {
    int output = my_utf8_check(input);
    if (output == expected) {
        printf("SUCCESS: %s -> %d\n", input, output);
        return 1;
    } else {
        printf("FAILURE: %s -> %d (expected %d)\n", input, output, expected);
        return 0;
    }
}

// test decode
int test_decode(unsigned char *input, unsigned char *expected) {
    unsigned char output[100] = {0};
    my_utf8_decode(input, output);
    if (my_utf8_strcmp(output, expected) == 0) {
        printf("SUCCESS: %s -> %s\n", input, output);
        return 1;
    } else {
        printf("FAILURE: %s -> %s (expected %s)\n", input, output, expected);
        return 0;
    }
}


int main(void) {
    printf("\nTESTING STR LEN\n");
    unsigned char len1[] = "אריה";
    test_strlen(len1, 4); //4
    unsigned char len2[] = "אA•";
    test_strlen(len2, 3); //3
    unsigned char len3[] = "Arieh";
    test_strlen(len3, 5); //5
    unsigned char len4[] = "How are you אריה ? 😀";
    test_strlen(len4, 20); //20
    unsigned char len5[] = "🥳😊";
    test_strlen(len5, 2); //0
    unsigned char len6[] = "";
    test_strlen(len6, 0); //0


    printf("\nTESTING SUBSTRNG:\n");
    unsigned char insub1[] = "שeלוAם אaריdה שלום";
    unsigned char outsub1[] = "אaריdה";
    test_substring(insub1, 7, 12, outsub1);

    unsigned char insub2[] = "א•שלי";
    unsigned char outsub2[] = "א•ש";
    test_substring(insub2, 0, 2, outsub2);

    unsigned char insub3[] = "שeלוAם אaריdה שלום";
    unsigned char outsub3[] = "שeל";
    test_substring(insub3, 0, 2, outsub3);

    unsigned char insub4[] = "שלום אריה שלום";
    unsigned char outsub4[] = "ה שלו";
    test_substring(insub4, 8, 12, outsub4);

    unsigned char insub5[] = "שלום אריה שלום";
    unsigned char outsub5[] = "אריה";
    test_substring(insub5, 5, 8, outsub5);

    printf("\nTESTING CHR COUNT:\n");
    unsigned char st1[] = "שלום";
    unsigned char let[] = {0xD7, 0x9C, '\0'}; //ל
    test_chr_count(st1, let, 1);

    unsigned char st2[] = "שלום";
    unsigned char let2[] = {0xD7,0x90, '\0'}; //א
    test_chr_count(st2, let2, 0);

    unsigned char st3[] = "שלום מה שלומך";
    unsigned char let4[] = {0xD7, 0x9C, '\0'}; //ל
    test_chr_count(st3, let4, 2);

    unsigned char st0[] = " 🥳 😢 🥳 😢";
    unsigned char let0[] = "🥳";
    test_chr_count(st0, let0, 2);

    unsigned char st4[] = "שלום";
    unsigned char let5[] = "A";
    test_chr_count(st4, let5, 0);


    printf("\nTESTING DECODE:\n");

    unsigned char in[] = "48 45 4C 4C 4F 7B 24";
    unsigned char out[] = "HELLO{$";
    test_decode(in, out);

    unsigned char in1[] = "D7 9B D7 9C D7 95 D7 9D D7 90 D7 A8 D7 99 D7 94";
    unsigned char out1[] = "\\u05DB\\u05DC\\u05D5\\u05DD\\u05D0\\u05E8\\u05D9\\u05D4";
    test_decode(in1, out1); // שלום אריה


    unsigned char in2[] = "7B 24 C2 A3";
    unsigned char out2[] = "{$\\u00A3";
    test_decode(in2, out2);

    unsigned char in3[] = "48 45 4C 4C 4F C2 A3";
    unsigned char out3[] = "HELLO\\u00A3";
    test_decode(in3, out3);

    unsigned char in4[] = "48 45 4C 4C 4F 24";
    unsigned char out4[] = "HELLO$";
    test_decode(in4, out4);

    unsigned char in5[] = "48 45 4C 4C 4F";
    unsigned char out5[] = "HELLO";
    test_decode(in5, out5);

    unsigned char in6[] = "24";
    unsigned char out6[] = "$";
    test_decode(in6, out6);

    unsigned char in7[] = "7B";
    unsigned char out7[] = "{";
    test_decode(in7, out7);

    unsigned char in8[] = "C2 A3";
    unsigned char out8[] = "\\u00A3";
    test_decode(in8, out8);

    unsigned char in9[] = "D0 98";
    unsigned char out9[] = "\\u0418";
    test_decode(in9, out9);


    printf("\nTESTING ENCODE: \n");
    unsigned char i[] = "\\u01D1";
    unsigned char o[] = {0xC7, 0x91, '\0'};
    test_encode(i, o);


    unsigned char i1[] = "\\u0080";
    unsigned char o1[] = {0xC2, 0x80, '\0'};
    test_encode(i1, o1);

    unsigned char i2[] = "\\u0021";
    unsigned char o2[] = "!";
    test_encode(i2, o2);


    unsigned char i3[] = "\\u0008\\u0061"; // 01
    unsigned char o3[] = {0x08, 0x61, '\0'}; // it's backspace a, so should just be a
    test_encode(i3, o3);


    unsigned char i4[] = "\\u0001"; // 01
    unsigned char o4[] = {0x01, '\0'};
    test_encode(i4, o4);

    unsigned char i5[] = "\\u01D1 \\u0080 HI";
    unsigned char o5[] = {0xC7, 0x91, ' ', 0xC2, 0x80, ' ', 'H', 'I', '\0'};
    test_encode(i5, o5);


    unsigned char i6[] = "\\u05E9\\u05DC\\u05D5\\u05DD \\u05D0\\u05E8\\u05D9 \\u05DE\\u05D4 \\u05E9\\u05DC\\u05D5\\u05DE\\u05DA";
    unsigned char o6[] = "שלום ארי מה שלומך";
    test_encode(i6, o6);

    unsigned char i7[] = "\\u0048\\u0065\\u006C\\u006C\\u006F\\u0021";
    unsigned char o7[] = "Hello!";
    test_encode(i7, o7);

    unsigned char i8[] = "HELLO \\u05D0\\u05E8\\u05D9\\u05D4 \\u1F601"; // HELLO אריה 😁
    unsigned char o8[] = "HELLO אריה 😁";
    test_encode(i8, o8);

    unsigned char i9[] = "HELLO \\u05D0\\u05E8\\u05D9\\u05D4 Hello";
    unsigned char o9[] = "HELLO אריה Hello";
    test_encode(i9, o9);

    printf("\nTESTING CHECK\n");

    unsigned char check[] = "C2 A3"; //VALID
    test_check(check, 1);
    unsigned char check1[] = "EF BF BF";//VALID
    test_check(check1, 1);
    unsigned char check2[] = "E0 82 AC";//VALID
    test_check(check2, 1);
    unsigned char check3[] = "24"; //VALID
    test_check(check3, 1);
    unsigned char check4[] = "F0 90 8D 88"; //VALID
    test_check(check4, 1);
    unsigned char check5[] = "A3"; //INVALID
    test_check(check5, 0);
    unsigned char check6[] = "7H"; //INVALID
    test_check(check6, 0);
    unsigned char check7[] = "!6"; //INVALID
    test_check(check7, 0);
    unsigned char check8[] = "6="; //INVALID
    test_check(check8, 0);
    unsigned char check9[] = "=6"; //INVALID
    test_check(check9, 0);
    unsigned char check10[] = "B2 A3"; //INVALID
    test_check(check10, 0);
    unsigned char check11[] = "F0 38"; //INVALID
    test_check(check11, 0);
    unsigned char check12[] = "$0 38"; //INVALID
    test_check(check12, 0);
    unsigned char check13[] = "F0 9$ 8D 88"; //INVALID
    test_check(check13, 0);
    unsigned char check14[] = "F0 90 @D 88"; //INVALID
    test_check(check14, 0);
    unsigned char check15[] = "F8 90 8D 88"; //INVALID
    test_check(check15, 0);
    unsigned char check16[] = "C1 A8 81"; //INVALID
    test_check(check16, 0);


    printf("\nTESTING CHARAT\n");
    unsigned char s[] = "אריה";
    unsigned char ans[] = "ה";
    test_charat(s, 3, ans);
    unsigned char s1[] = "א•שלי";
    unsigned char ans1[] = "•";
    test_charat(s1, 1, ans1);
    unsigned char s2[] = "א•שלי";
    unsigned char ans2[] = "ל";
    test_charat(s2, 3, ans2);
    unsigned char s3[] = "א•שלי";
    unsigned char ans3[] = "א";
    test_charat(s3, 0, ans3);
    unsigned char s4[] = "😂🥳🤩";
    unsigned char ans4[] = "🥳";
    test_charat(s4, 1, ans4);
    unsigned char s5[] = "שלום אריה";
    unsigned char ans5[] = " ";
    test_charat(s5, 4, ans5);



    printf("\nTESTING STRNCPY\n");
    unsigned char source[] = "שלום";
    unsigned char exp[]= "שלו";
    test_strncpy(source, 3, exp);
    unsigned char source1[] = "א•שלי";
    unsigned char exp1[] = "א•";
    test_strncpy(source1, 2, exp1);
    unsigned char source2[] = "Arieh";
    unsigned char exp2[] = "Ar";
    test_strncpy(source2, 2, exp2);
    unsigned char source3[] = "how are you";
    unsigned char exp3[] = "how a";
    test_strncpy(source3, 5, exp3);
    unsigned char source4[] = "😂🥳🤩";
    unsigned char exp4[] = "😂🥳";
    test_strncpy(source4, 2, exp4);



    printf("\nTESTING STRCMP\n");
    unsigned char comp1[] = "אריה";
    unsigned char to1[] = "ריה";
    test_strcmp(comp1, to1, 1);
    unsigned char comp2[] = "ריה";
    unsigned char to2[] = "אריה";
    test_strcmp(comp2, to2, -1);
    unsigned char comp3[] = "אריה";
    unsigned char to3[] = "ארי";
    test_strcmp(comp3, to3, -1);
    unsigned char comp4[] = "אריה";
    unsigned char to4[] = "אריה";
    test_strcmp(comp4, to4, 0);
    unsigned char comp5[] = "שלום אריה";
    unsigned char to5[] = "לום אריה";
    test_strcmp(comp5, to5, -1);
    unsigned char comp6[] = "😂";
    unsigned char to6[] = "😂";
    test_strcmp(comp6, to6, 0);
    unsigned char comp7[] = "😂😂";
    unsigned char to7[] = "😂";
    test_strcmp(comp7, to7, -1);
    unsigned char comp8[] = "how are you";
    unsigned char to8[] = "how are you";
    test_strcmp(comp8, to8, 0);

    return 1;
}
