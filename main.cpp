//
// Created by Rachel Shohet on 12/29/23.
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int regular_strlen(unsigned char *string){
    int len = 0;
    while (string[len] != '\0'){
        len++;
    }
    return len;
}
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
//        else if (string[i] >= '\x80' && string[i] <= '\xA') { // this means the ith char is 1 byte
//            i += 1;
//            length += 1;
//        }
    }
//    printf("LENGTH of %s is : %d\n", string, length);
    return length;
}

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

char bin_to_hex(char* binary){
    char digit;
//    printf("BINARY = %s\n", binary);

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
//    printf("HEX DIGIT %c\n", digit + '0');
    return digit;
}

int num_bytes(unsigned char string) {
    int bytes = 0;
    if (string >= 0x00 && string <= 0x7F) { // this means the ith char is 1 byte
        bytes = 1;
    } else if (string >= 0xF0 && string <= 0xF4) { // this means the ith char is 4 bytes
        bytes = 4;
    } else if (string >= 0xE0 && string <= 0xEF) { // this means the ith char is 3 bytes
        bytes = 3;
    } else if (string >= 0xC2 && string <= 0xDF) { // this means the ith char is 2 bytes
        bytes = 2;
    }else
        printf("Invalid: %c\n", string);
    return bytes; // return the number of bytes the char is
}

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
    return bytes; // return the number of bytes the char is
}

int my_utf8_encode(unsigned char *input, unsigned char *output) {
    int loop = 0;
    int while_int = 0;
    unsigned char *fullUnicode = input;
    int p = 0;
    unsigned char letters[50];
    while (regular_strlen(fullUnicode) > 0 && fullUnicode[while_int] != '\0') {
        if (fullUnicode[0] == ' ') {
            int len_out = regular_strlen(output);
            output[len_out] = ' ';
            output[len_out + 1] = '\0';
            fullUnicode = fullUnicode + 1;
        }
        if (fullUnicode[0] == '\\') { // if input is as unicode, then strip off the \u
            fullUnicode = fullUnicode + 2;
//            printf("new input %s\n", fullUnicode);

            int unic = 0;
            int len_unic = 0;
//        char unicode[100];
            unsigned char unicode[] = "0000";
//            printf("UNICODE PRE %s\n", unicode);
            while (fullUnicode[unic] != '\\' && fullUnicode[unic] != ' ' && fullUnicode[unic] !=
                                                '\0') { // find length of the char by stopping once hit next char or end of string
//                printf("FULL UNIC: %c %d\n", fullUnicode[unic], unic);
                unicode[unic] = fullUnicode[unic];
                unic++;
            }
            unicode[unic] = '\0';
//            printf("UNICODE POST %s\n", unicode);
            len_unic = unic;
            fullUnicode = fullUnicode + unic;
//            printf("fullunic = %s and unicode = %s\n", fullUnicode, unicode);

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
//                            printf("i = %d and adding %c and count = %d and full is %s \n", i, fullBinary[i], j,
//                                   binaryUTF);
                            j++;
                        } else if (j == 8) {// skip locations 8 and 9 and add after
                            j = 10;
                            binaryUTF[j] = fullBinary[i];
//                            printf("i = %d and adding %c and count = %d and full is %s \n", i, fullBinary[i], j,
//                                   binaryUTF);
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
//                            printf("i = %d and adding %c and count = %d and full is %s \n", i, fullBinary[i], j,
//                                   binaryUTF);
                            j++;
                        }
                    }
//                    printf("BINAR UTF %s\n", binaryUTF);
                    int lenUTF = my_utf8_strlen(binaryUTF);
//                    printf("binary = %s, binaryUTF = %s, length of utf = %d\n", fullBinary, binaryUTF, lenUTF);
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
//                        printf("i = %d and adding %c and count = %d and full is %s \n", i, fullBinary[i], j, binaryUTF);
                        j++;
                    } else if (j == 8) {// skip locations 8 and 9 and add after
                        j = 10;
                        binaryUTF[j] = fullBinary[i];
//                        printf("i = %d and adding %c and count = %d and full is %s \n", i, fullBinary[i], j, binaryUTF);
                        j++;
                    } else if (j == 16) {// skip locations 16 and 17 and add after
                        j = 18;
                        binaryUTF[j] = fullBinary[i];
//                        printf("i = %d and adding %c and count = %d and full is %s \n", i, fullBinary[i], j, binaryUTF);
                        j++;
                    } else if (j == 24) {// skip locations 24 and 25 and add after
                        j = 26;
                        binaryUTF[j] = fullBinary[i];
//                        printf("i = %d and adding %c and count = %d and full is %s \n", i, fullBinary[i], j, binaryUTF);
                        j++;
                    }
                }
                int lenUTF = my_utf8_strlen(binaryUTF);
//                printf("binary = %s, binaryUTF = %s, length of utf = %d\n", fullBinary, binaryUTF, lenUTF);
            }
//            printf("out of if\n");
//            printf("binary = %s, binaryUTF = %s\n", fullBinary, binaryUTF);

            // convert the binaryUTF string to hex
            int lenUTF = my_utf8_strlen(binaryUTF);
            unsigned char hexUTF8[3 * num_bytes]; // Assuming 2 characters per byte and space for null terminator
            int hi = 0;
            unsigned char temp[10];
            temp[0] = '\\';
            temp[1] = 'x';
            int t = 2;
            int x = 0;
            int j = 0; // keep track of where in hex array we are
            char prev;
            int z = 0;
            for (int i = 0; i < lenUTF; i += 4) {
                hi++;
//                printf("i = %d\n", i);
                char bin[4];
                for (int k = 0; k < 4; k++) { // get the 4 bits of the binaryUTF
                    bin[k] = binaryUTF[i + k];
                }
                char hex_dig = bin_to_hex(bin);
//                printf("i = %d, j = %d, binary = %s hex_dig = %d\n", i, j, bin, hex_dig);
//                if (j == 2 || j == 5 || j == 8) { // skip the spaces
////                    hexUTF8[j++] = ' ';
//                    continue;
//                }
                if (hi % 2 == 0){
                    temp[t++] = prev;
                    temp[t++] = hex_dig;
                    temp[t] = '\0';
//                    printf("TEMP %s\n", temp);


                    char hexEncode[3] = {temp[t-2], temp[t-1], '\0'};
                    int len_output = regular_strlen(output);
                    sscanf(hexEncode, "%2hhX", &output[len_output]);
                    output[len_output + 1] = '\0';
                }
//                printf("TEMP FINA%x\n", temp);
                prev = hex_dig;
                hexUTF8[j++] = hex_dig;
            }

//            printf("OUTPUT %s\n", output);
            free(binaryUTF);
            loop = loop + my_utf8_strlen(hexUTF8);

        }

        else{ // it's a real character
            int i = 0;
            char hexchar[3];
//            printf("UNIC CHAR = %c\n", fullUnicode[0]);
            int len_output = regular_strlen(output);
            output[len_output] = fullUnicode[0];
            output[len_output+1] = '\0';
//            output[loop++] = fullUnicode[0];
//            output[loop] = '\0';
            fullUnicode = fullUnicode + 1;
            int full_len = regular_strlen(fullUnicode);

        }
        while_int++;

    }
    unsigned char heb[] = "אריה";
    unsigned char heb1[] = "ר";

    printf("OUTPUT %s\n", output);
    return 1;
//    printf("OUTPUT %d\n", heb1);

}

//E0 to EF hex (224 to 239): first byte of a three-byte sequence.
//F0 to FF hex (240 to 255): first byte of a four-byte sequence.
//https://www.fileformat.info/info/unicode/utf8.htm
// a hex UTF-8 can never begin with A or B - only 0, 1, C, D, E, F & the subsequent bytes can only begin with 8,9,A,B
int my_utf8_check(unsigned char *string){
    if (my_utf8_strlen(string) > 2) {
        if (string[0] != 'C' && string[0] != 'D' && string[0] != 'E' && string[0] != 'F') {
            printf("1 ERROR: %s is not a valid UTF-8 hex\n", string);
            return 0;
        }
        if (string[0] == 'C' && string[1] < '2') { // if C is the start of a 2-byte sequence , can't be less than C2
            printf("1 ERROR: %s is not a valid UTF-8 hex\n", string);
            return 0;
        }
        if (string[0] == 'F' && !(string[1] >= '0' && string[1] <= '7')) {
            printf("2 ERROR: %s is not a valid UTF-8 hex\n", string);
            return 0;
        }
        for (int i = 1; i <= my_utf8_strlen(string); i++) {
            if (i == 3 || i == 6 || i == 9) { // if it's the first digit of subsequent bytes it can only be 8,9,A,B
                if (string[i] != 'A' && string[i] != 'B' && string[i] != '8' && string[i] != '9') {
                    printf("3 ERROR: %s is not a valid UTF-8 hex\n", string);
                    return 0;
                }
            }else if (i == 2 || i == 5 || i == 8 || i == 11){ // skip the spaces
                continue;
            }else{
                if (string[i] < '0' || (string[i] > '9' && string[i] < 'A') || string[i] > 'F') {
                    printf("4 ERROR: %s is not a valid UTF-8 hex\n", string);
                    return 0;
                }
            }
        }
    // it's 1 byte, so it is ascii and must be between 00 and 7F
    }else{
        if (string[0] < '0' || string[0] > '7') {
            printf("5 ERROR: %s is not a valid UTF-8 hex\n", string);
            return 0;
        }
        if (my_utf8_strlen(string) == 2){
//            printf("sting[1] = %c int = %d\n", string[1], string[1]);
            if (string[1] < '0' || (string[1] > '9' && string[1] < 'A') || string[1] > 'F') {
                printf("6 ERROR: %s is not a valid UTF-8 hex\n", string);
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


int my_utf8_strcmp(unsigned char *string1, unsigned char *string2){
    int i = 0;
    printf("LENGTH %d %s\n", my_utf8_strlen(string2), string2);
    if (my_utf8_strlen(string1) == 1 && my_utf8_strlen(string2) == 1){
        printf("here\n");
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


int my_utf8_strncpy(char *dest, char *source, int num_char) {
    int i = 0; // to loop through the bytes of the string
    int j = 0; // to loop through the actual characters of the string
    while (j < num_char) {
        // check the hex of the character and compare it to the max hex value for the first byte to determine how many
        // bytes the char is (based on the wiki page). Skip that many chars and add 1 to the length
        if (source[i] >= '\x0' && source[i] < '\x7F') { // this means the ith char is 1 byte
            dest[j] = source[i];
            i += 1;
            j += 1;
        } else if (source[i] >= '\xF0') { // this means the ith char is 4 bytes
            for (int b = 0; b < 4; b++) {
                dest[i + b] = source[i + b];
            }
            i += 4;
            j += 1;
        } else if (source[i] >= '\xE0' && source[i] < '\xF0') { // this means the ith char is 3 bytes
            for (int b = 0; b < 3; b++) {
                dest[i + b] = source[i + b];
            }
            i += 3;
            j += 1;
        } else if (source[i] >= '\xC0' && source[i] <= '\xE0') { // this means the ith char is 2 bytes
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

int my_utf8_chr_count(unsigned char* str, unsigned char* ch){
    // check how many bytes the input character is
    int bytes = 0;
//    printf("string %s\n", str);
    char whole[2];
    whole[0] = ch[0];
    whole[1] = ch[1];
//    printf("WHOLE %s\n", whole);
//    if (ch[0] >= '\x0' && ch[0] <= '\x7F') { // this means the ith char is 1 byte
//        bytes = 1;
//    } else if (ch[0] >= 0xF0 && ch[0] <= 0xF4) { // this means the ith char is 4 bytes
//        bytes = 4;
//    } else if (ch[0] >= 0xE0 && ch[0] <= 0xEF) { // this means the ith char is 3 bytes
//        bytes = 3;
//    } else if (ch[0] >= 0xC2 && ch[0] <= 0xDF) { // this means the ith char is 2 bytes
//        bytes = 2;
//    }
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

unsigned char* my_utf8_substring(unsigned char* string, int start, int end){
    unsigned char* new_string = my_utf8_charat(string, start); // use my_utf8_charat to get the char at the start index, so the string begins at that character
//    printf("string = %s\n", new_string);
    int j = 0; // to loop through the actual characters of the string
    int bytes = 0; // bytes of the chars thus far in the string
    int len = end - start + 1; // length of the substring
    while ((j < len) && new_string[bytes] != '\0') {
//        if (j == 0 || j % 2 == 0) {
            unsigned char *heb = my_utf8_charat(string, start + j);
            bytes += num_bytes(new_string[bytes]); // strip off one character from the string at a time until find the index and do this by incrementing by how many bytes the char is
//            printf("J = %d and bytes = %d sub = %s \n", j, bytes, new_string);
//        }
        j++;
    }
//    printf("J = %d sub  = %c \n", j, new_string[j]);
    int last_byte = num_bytes(new_string[j]);
    new_string[bytes] = '\0'; // need to terminate w null character
//    printf("SUBSTRING = %s\n", new_string);
    return new_string;
}
//    int i = 0; // to loop through the bytes of the string
//    int j = 0; // to loop through the actual characters of the string
//    int previ = 0; // to keep track of the previous character bytes to can ultimately calculate the bytes of the char
//    int prevj = 0; // to keep track of the actual index bc will loop one extra time to find its bytes
//    int bytes = 0; // bytes of the char at index
//    while (prevj != index) {
//        // check the hex of the character and compare it to the max hex value for the first byte to determine how many
//        // bytes the char is (based on the wiki page). Skip that many chars and add 1 to the length
//        previ = i;
//        prevj = j;
//        if (str[i] >= '\x0' && str[i] < '\x7F') { // this means the ith char is 1 byte
//            i += 1;
//            j += 1;
//        } else if (str[i] >= '\xF0') { // this means the ith char is 4 bytes
//            i += 4;
//            j += 1;
//        } else if (str[i] >= '\xE0' && str[i] < '\xF0') { // this means the ith char is 3 bytes
//            i += 3;
//            j += 1;
//        } else if (str[i] >= '\xC0' && str[i] <= '\xE0') { // this means the ith char is 2 bytes
//            i += 2;
//            j += 1;
//        }
//        bytes = i - previ; // find out how many bytes the ith character was so can know when fall out of the loop how many bytes the character at index is
//    }


// Takes a UTF8 encoded string, and returns a string, with ASCII representation where possible, and UTF8 character
// representation for non-ASCII characters.
int my_utf8_decode(unsigned char *input, unsigned char *output){
    // loop through the input string and convert each utf hex to binary, then to unicode hex and add to output string (unless ascii then convert to ascii)
    unsigned char hex[7];
    int index1 = 0;
    int len_input = my_utf8_strlen(input);
    printf("len input %d\n", len_input);
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
//        index1 += 1;
        printf("HEX %s \n", hex);
        printf("INPUT INDEXXXX input = %s ind = %d prev = %c inputind = %c\n", input, index1, prev, input[index1]); // index1 shld be 3, 6, 9...
        while ((prev == 'C' || prev == 'D' || prev == 'E' || prev == 'F') && ((input[index1] >= '0' && input[index1] <= '9') || ( input[index1] == 'A' ||  input[index1] == 'B'))){ // until reach next hex that signals a new char
            printf("WHILE\n");
            hex[h++] = ' ';// add spaces between each byte

            hex[h++] = input[index1++];
            hex[h++] = input[index1++];

            if (input[index1] != '\0')  // if not at the end of the input string
                index1 += 1; // increment by 2 so always at the beginning of a new byte of the utf string and then add 1 for spaces between bytes
            printf("HERE IS HEX %s index = %d \n", hex, index1);

        }
        hex[h] = '\0'; // need to terminate w null character
        int len_hex = my_utf8_strlen(hex);
        printf("HERE IS HEX %s len = %d \n", hex, len_hex);

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
            printf("ASCII %c\n", ascii);
            output[o++] = (char) ascii;
            output[o] = '\0'; // need to terminate w null character
            printf("OUTPUT %s\n", output);

        }else { // not ascii
            printf("HEX NON ASCII %s\n", hex);
            if (hex[0] == 'C' || hex[0] == 'D') { // know 2 bytes if begins with C or D
                bytes = 2;
                int j = 0; // keep track of where we are at in the binary string
                for (; j < 5; j++) { // fill in the first 5 bit of the binary string with 0s
                    binary[j] = '0';
                }

                utf_len = (bytes * 2) + (bytes - 1); // the length of the utf8 string is 2 bytes, each with 2 hex digits + (bytes - 1) for the space
                for (int i = 0; i < utf_len; i++) {
                    // skip the spaces
                    if (i == 2) // skip the spaces in the utf8 string
                        continue;
                    else {
                        // convert the hex to binary
                        char *bin = hex_to_bin(hex[i]);
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
                    printf("2 binary = %s\n", binary);
                }
                binary[j] = '\0'; // need to terminate w null character
                printf("2 binary = %s\n", binary);
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
                        printf("CONVEETING HEX DIG %c of hex = %s\n", hex[i], hex);
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
                    printf("3 binary = %s\n", binary);
                }
                binary[j] = '\0'; // need to terminate w null character
                printf("3 binary = %s\n", binary);
            } else if (hex[0] == 'F') { // know 4 bytes if begins with F
                printf("HEXXXXXXX %s\n", hex);
                bytes = 4;
                utf_len = (bytes * 2) + (bytes -
                                         1); // the length of the utf8 string is 2 bytes, each with 2 hex digits + (bytes - 1) for the space
//                binary[0] = '0'; // the 0th binary digit is always a 0
//                binary[1] = '0'; // the 1st binary digit is always a 0
//                binary[2] = '0'; // the 2nd binary digit is always a 0
                int j = 0; // keep track of where we are at in the binary string
                for (int i = 1; i < utf_len; i++) { // completely skip first utf char since it's always 1111
                    // skip the spaces
                    if (i == 2 || i == 5 || i == 8) // skip the spaces in the utf8 string
                        continue;
                    else {
                        // convert the hex to binary
                        printf("CONVEETING HEX DIG %c of hex = %s len = %d\n", hex[i], hex, len_hex);
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
                        printf("i = %d BIN = %s binary = %s\n", i, bin, binary);

                    }
                }
                binary[j] = '\0'; // need to terminate w null character
            }
            printf("final binary = %s o = %d\n", binary, o);
            int len_output = my_utf8_strlen(binary);
            printf("len out %d\n", len_output);
            printf("pre pre J = %d\n", o);
            output[o++] = '\\'; // add u+ to the beginning of the output
            output[o++] = 'u';
            printf("pre loop J = %d\n", o);
            for (int i = 0; i < len_output; i += 4) {
                char bin[4];
                int b = 0;
                for (; b < 4; b++) { // get the binary to convert to hex
                    bin[b] = binary[i + b];
                }
                char hex_con = bin_to_hex(bin); // convert the binary to hex
                printf("loop J = %d\n", o);
                output[o++] = hex_con; // add the hex to the output
            }
            printf("post loop J = %d\n", o);
            output[o] = '\0'; // need to terminate w null character
            printf("OUTPUT %s\n", output);
        }
    }
    printf("OUT %s\n", output);
    return 0;
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

//test encode
int test_encode(unsigned char *input, unsigned char *expected) {
    unsigned char output[100] = {0};
    printf("expected = %s\n", expected);
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
    printf("expected = %s\n", expected);
    unsigned char* ans = my_utf8_substring(input, start, end);
    printf("ANS = %s\n", ans);
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
    printf("expected = %d\n", expected);
    int output = my_utf8_chr_count(input, ch);
    if (output == expected) {
        printf("SUCCESS: %d -> %d \n", output, expected);
        return 1;
    } else {
        printf("FAILURE: %d but expected %d \n", output, expected);
        return 0;
    }
}

int main(void) {
    printf("TESTING STR LEN\n");
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


//    printf("TESTING SUBSTRNG:");
//    unsigned char insub1[] = "שeלוAם אaריdה שלום";
//    unsigned char outsub1[] = "אaריdה";
//    test_substring(insub1, 7, 12, outsub1);


//    unsigned char s1[] = "א•שלי";
//    unsigned char* ans1 = my_utf8_substring(s1, 0, 2); //א•ש
//    printf("character is %s\n", ans1);

//    unsigned char s2[] = "שeלוAם אaריdה שלום";
//    unsigned char* ans2 = my_utf8_substring(s2, 0, 2); //לeש
//    printf("character is %s\n", ans2);
//    unsigned char* ans2 = my_utf8_charat(s1, 0); //ל
//    printf("character is %x\n", *ans2);

//    unsigned char s3[] = "שלום אריה שלום";
//    unsigned char* ans3 = my_utf8_substring(s3, 8, 12); //ה שלו
//    printf("substring is %s\n", ans3);

//    unsigned char s4[] = "שלום אריה שלום";
//    unsigned char* ans4 = my_utf8_substring(s4, 5, 8); //אריה
//    printf("substring is %s\n", ans4);

//    printf("TESTING CHR COUNT:");
//    unsigned char st1[] = "שלולם";
//    unsigned char let[] = {0xD7, 0x9C}; //ל
//    test_chr_count(st1, let, 2);

//    unsigned char st2[] = "שלום";
//    unsigned char let2[] = "\xD7\x90";
//    int seen1 = my_utf8_chr_count(st2, let2);
//    printf("SEEN in string = %d\n", seen1);
//
//    unsigned char st3[] = "שלום";
//    unsigned char let4[] = "ל";
//    int seen2 = my_utf8_chr_count(st3, let4);
//    printf("SEEN in string = %d\n", seen2);
//
//    unsigned char st0[] = "שםםלום";
//    unsigned char let0[] = "ם";
//    int seen3 = my_utf8_chr_count(st0, let0);
//    printf("SEEN in string = %d\n", seen3);
//
//    unsigned char st4[] = "שלום";
//    unsigned char let5[] = "A";
//    int seen4 = my_utf8_chr_count(st4, let5);
//    printf("SEEN in string = %d\n", seen4);


//    unsigned char in[] = "48 45 4C 4C 4F E0 A4 B9"; // FIXXX THISSS - hello with 3 bytes and hello w 4 bytes and on own 3 and 4 bytes
//    my_utf8_decode(in, output); // Hellou\00A3u\0939
//    unsigned char in[] = "48 45 4C 4C 4F 7B 24";
//    my_utf8_decode(in, output); // Hello{$
//    unsigned char in[] = "D0 98 C2 A3";
//    my_utf8_decode(in, output); // \u0418\u00A3
//    unsigned char in[] = "7B 24 C2 A3";
//    my_utf8_decode(in, output); // {u\00A3$
//    unsigned char in[] = "48 45 4C 4C 4F C2 A3 24"; // FIXXX THIS - HELLO W 2 BYTES THEN 1 BYTE
//    my_utf8_decode(in, output); // Hellou\00A3$
//    unsigned char in[] = "48 45 4C 4C 4F C2 A3";
//    my_utf8_decode(in, output); // Hellou\00A3
//    unsigned char in[] = "48 45 4C 4C 4F 24";
//    my_utf8_decode(in, output); // Hello$
//    unsigned char in[] = "48 45 4C 4C 4F";
//    my_utf8_decode(in, output); // Hello
//    unsigned char in[] = "24";
//    my_utf8_decode(in, output); // U+0024 $
//    unsigned char in[] = "7B";
//    my_utf8_decode(in, output); // U+0024 {
//    unsigned char in[] = "C2 A3";
//    my_utf8_decode(in, output); // u\00A3
//    unsigned char in[] = "D0 98";
//    my_utf8_decode(in, output); // U+0418
//    unsigned char in[] = "E0 A4 B9";
//    my_utf8_decode(in, output); // U+0939
//    unsigned char in[] = "E2 82 AC";
//    my_utf8_decode(in, output); // U+20AC
//    unsigned char in[] = "ED 95 9C";
//    my_utf8_decode(in, output); // U+D55C
//    unsigned char in[] = "F0 90 8D 88"; // FIIXXXXXXX THISSSSSSS
//    my_utf8_decode(in, output); // U+10348
//    unsigned char in[] = "F4 8F BF BF";  // FIIXXXXXXX THISSSSSSS
//    my_utf8_decode(in, output); // U+10FFFF

//    printf("ANSWER IS %s\n", output);


//    printf("TESTING ENCODE: \n");
//    unsigned char i[] = "\\u01D1";
//    unsigned char o[] = {0xC7, 0x91, '\0'};
//    test_encode(i, o);
//
//
//    unsigned char i1[] = "\\u0080";
//    unsigned char o1[] = {0xC2, 0x80, '\0'};
//    test_encode(i1, o1);
//
//    unsigned char i2[] = "\\u0021"; /// doesnr work
//    unsigned char o2[] = "!";
//    test_encode(i2, output);


//    unsigned char i2[] = "\\u0008\\u0061"; // 01
//    unsigned char o2[] = {0x08, 0x61, '\0'}; // it's backspace a, so should just be a
//    test_encode(i2, o2);


//    unsigned char s1[] = "\\u0001"; // 01
//    my_utf8_encode("\\u007F", output); // 7F
//    printf("ANSWER %s\n", output);
//    printf("\n");

//    unsigned char s1[] = "\\u008F";
//    my_utf8_encode(s1, output); //C2 8F
//    printf("ANSWER %s\n", output);
//    printf("\n");

//    unsigned char s1[] = "\\u07FF";
//    my_utf8_encode(s1, output); // DF BF
//    printf("ANSWER %s\n", output);
//    printf("\n");

//    my_utf8_encode(s1, output); // C2 80
//    printf("ANSWER %s\n", output);
//    printf("\n");

//    unsigned char s1[] = "\\u05D0";
//    my_utf8_encode(s1, output); // D7 90
//    printf("ANSWER %s\n", output);
//    printf("\n");

//    unsigned char s1[] ="\\u0800";
//    my_utf8_encode(s1, output); // E0 A0 80
//    printf("ANSWER %s\n", output);
//    printf("\n");

//    unsigned char s1[] = "\\uFFFF";
//    my_utf8_encode(s1, output); // EF BF BF
//    printf("ANSWER %s\n", output);
//    printf("\n");

//    unsigned char s1[] = "\\u0C9A";
//    my_utf8_encode(s1, output); // E0 B2 9A
//    printf("ANSWER %s\n", output);
//    printf("\n");

//    unsigned char s1[] = "\\u20AC";
//    my_utf8_encode(s1, output); // E2 82 AC
//    printf("ANSWER %s\n", output);
//    printf("\n");

//    unsigned char s1[] = "\\uD55C";
//    my_utf8_encode(s1, output); // ED 95 9C
//    printf("ANSWER %s\n", output);
//    printf("\n");

//    unsigned char s1[] = "\\u10000";
//    my_utf8_encode(s1, output); // F0 90 80 80
//    printf("ANSWER %s\n", output);
//    printf("\n");

//    unsigned char s1[] = "\\u10FFFF";
//    my_utf8_encode(s1, output); // F4 8F BF BF
//    printf("ANSWER %s\n", output);
//    printf("\n");

//    unsigned char s1[] = "\\u10348";
//    my_utf8_encode(s1, output); // F0 90 8D 88
//    printf("ANSWER %s\n", output);
//    printf("\n");

//    unsigned char s1[] = "\\u0048\\u0065\\u006C\\u006C\\u006F\\u0021";
//    my_utf8_encode(s1, output); // 48 65 6C 6C 6F 21
//    printf("ANSWER %s\n", output);
//    printf("\n");

//    unsigned char s1[] = "\\u10FFFF\\u0065\\uD55C\\u006C";
//    my_utf8_encode(s1, output); // F4 8F BF BF - 65 - ED 95 9C - 6C
//    printf("ANSWER %s\n", output);
//    printf("\n");

//    unsigned char s1[] = "\\u10FFFF\\u0080\\uD55C\\u10348";
//    my_utf8_encode(s1, output); // F4 8F BF BF - C2 80 - ED 95 9C - F0 90 8D 88
//    printf("ANSWER %s\n", output);
//    printf("\n");

//    unsigned char a[] = "\\u05D0\\u05E8\\u05D9\\u05D4";
//    my_utf8_encode(a, output); // D7 90 D7 A8 D7 99 D7 94 אריה
//    printf("ANSWER %s\n", output);
//    printf("\n");

//    unsigned char b[] = "HELLO\\u05E8\\u05D9\\u05D4"; // HELLO D7 A8 D7 99 D7 94 - HELLO ריה
//    my_utf8_encode(b, output);
//    printf("ANSWER %s\n", output);
//    printf("\n");

//    unsigned char b[] = "HELLO \\u05D0\\u05E8\\u05D9\\u05D4 \\u1F601"; // HELLO אריה 😁
//    my_utf8_encode(b, output);
//    printf("ANSWER %s\n", output);
//    printf("\n");

//    unsigned char b[] = "HELLO \\u05D0\\u05E8\\u05D9\\u05D4 Hello"; // HELLO אריה Hello
//    my_utf8_encode(b, output);
//    printf("ANSWER %s\n", output);
//    printf("\n");

//    unsigned char b[] = "\\u05E8\\u05D9\\u05D4HELLO"; // HELLO D7 A8 D7 99 D7 94 - HELLO ריה
//    my_utf8_encode(b, output); // FIX THISSSSSSSSS
//    printf("ANSWER %s\n", output);
//    printf("\n");

//      char i[] = "\xD7\xA8";
//      printf("CAR = %s\n", i);
//
//
//    char myChar = 'D';
//    char hexValue[3];  // Assuming a single character and null terminator
//
//    // Use sprintf to format the string and store it in hexValue
//    sprintf(hexValue, "%x", myChar);
//
//    // Now hexValue contains the hexadecimal representation of myChar
//    printf("Hex value of %c is %s\n", myChar, hexValue);


//    my_utf8_check("C2 A3");//VALID
//    my_utf8_check("EF BF BF");//VALID
//    my_utf8_check("E0 82 AC");//VALID
//    my_utf8_check("24"); //VALID
//    my_utf8_check("F0 90 8D 88"); //VALID
//    my_utf8_check("A3");//INVALID
//    my_utf8_check("7H");//INVALID
//    my_utf8_check("!6");//INVALID
//    my_utf8_check("!6");//INVALID
//    my_utf8_check("6=");//INVALID
//    my_utf8_check("=6");//INVALID
//    my_utf8_check("B2 A3");//INVALID
//    my_utf8_check("F0 38");//INVALID
//    my_utf8_check("$0 38");//INVALID
//    my_utf8_check("F0 9$ 8D 88"); //INVALID
//    my_utf8_check("F0 90 @D 88"); //INVALID
//    my_utf8_check("F8 90 8D 88"); //INVALID
//    my_utf8_check("C1 A8 81"); //INVALID


//    unsigned char s[] = "אריה";
//    unsigned char* ans = my_utf8_charat(s, 3); //ה
//    printf("character is %x\n", *ans);
//    unsigned char s1[] = "א•שלי";
//    unsigned char* ans1 = my_utf8_charat(s1, 2); //•
//    printf("character is %x\n", *ans1);
//    unsigned char* ans2 = my_utf8_charat(s1, 0); //ל
//    printf("character is %x\n", *ans2);


//    char source[] = "שלום";
//    char dest[20];
//
//    char source1[] = "א•שלי";
//    char dest1[20];
//
//    char source2[] = "Arieh";
//    char dest2[20];
//
//    // Copying the source string to dest
//    my_utf8_strncpy(dest, source, 3);
//    my_utf8_strncpy(dest1, source1, 2);
//    my_utf8_strncpy(dest2, source2, 2);
//
//    // printing result
//    printf("Source: %s\n", source);
//    printf("Destination: %s\n", dest);
//    // printing result
//    printf("Source: %s\n", source1);
//    printf("Destination: %s\n", dest1);
//    // printing result
//    printf("Source: %s\n", source2);
//    printf("Destination: %s\n", dest2);

//    char strh[] = "שלום";
////
//    wchar_t chh = L'ל';
//    if (strh[1] == "ל"){
//        printf("yes\n");
//    }
//    else{
//        printf("NO %x %x\n", chh, strh[1]);
//    }
//    printf("chh = %x\n", strh[1]);
//    char str[] = "amamzi";

//    char ch = 'm';
//    // Search for the character 'e' in the string
//    // Use the strchr function to find the first occurrence
//    // of 'e' in the string
//    char* result = strchr(str, ch);
//
//    // Character 'e' is found, calculate the index by
//    // subtracting the result pointer from the str pointer
//    if (result != NULL) {
//        printf("The character '%c' is found at index %ld\n",
//               ch, result - str);
//    }
//    else {
//        printf("The character '%c' is not found in the "
//               "string\n",
//               ch);
//    }


//    unsigned char string1[] = "אריה";
//    unsigned char string2[] = "ריה";
//    int ans = my_utf8_strcmp(string1, string2); // 1
//    unsigned char string3[] = "ריה";
//    unsigned char string4[] = "אריה";
//    int ans =my_utf8_strcmp(string3, string4); // -1
//    my_utf8_strcmp(string1, string4); // 0
//    unsigned char string7[] = "אריה";
//    unsigned char string8[] = "ארי";
//    int ans = my_utf8_strcmp(string7, string8); // -1
//    printf("ANSWER = %d\n", ans);

    return 1;
}
