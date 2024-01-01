//
// Created by Rachel Shohet on 12/29/23.
#include <string.h>
#include <stdio.h>
#include <malloc/_malloc.h>
#include <stdlib.h>
#include <wchar.h>

int my_utf8_strlen(char *string){
    int i = 0;
    int length = 0;
    while (string[i] != '\0') {
        // check the hex of the character and compare it to the max hex value for the first byte to determine how many
        // bytes the char is (based on the wiki page). Skip that many chars and add 1 to the length
        if (string[i] >= '\x0' && string[i] < '\x7F') { // this means the ith char is 1 byte
            i += 1;
            length += 1;
        }else if (string[i] >= '\xF0') { // this means the ith char is 4 bytes
            i += 4;
            length += 1;
        } else if (string[i] >= '\xE0' && string[i] < '\xF0') { // this means the ith char is 3 bytes
            i += 3;
            length += 1;
        } else if (string[i] >= '\xC0' && string[i] <= '\xE0') { // this means the ith char is 2 bytes
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

char* find_bin(char hexDigit){
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

char find_hex(char* binary){
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

int my_utf8_encode(char *input, char *output) {
//    int ch = 0;
    int loop = 0;
    char *fullUnicode = input;
    while (fullUnicode[0] != '\0') {
        fullUnicode = fullUnicode + 2; // strip off u+
        printf("new input %s\n", fullUnicode);

        int unic = 0;
        int len_unic = 0;
//        char unicode[100];
        char unicode[] = "0000";
        printf("UNICODE PRE %s\n", unicode);
        while (fullUnicode[unic] != 'u' && fullUnicode[unic] != '\0'){ // find length of the char by stopping once hit next char or end of string
            printf("FULL UNIC: %c %d\n", fullUnicode[unic], unic);
            unicode[unic] = fullUnicode[unic];
            unic++;
        }
        unicode[unic] = '\0';
        printf("UNICODE POST %s\n", unicode);
        len_unic = unic;
        fullUnicode = fullUnicode + unic;
        printf("fullunic = %s and unicode = %s\n", fullUnicode, unicode);

        char *hexBin;
        char *binaryUTF = NULL; // used malloc for binaryUTF so I can alter the size and use that later
        binaryUTF = (char *) malloc(50);
        if (binaryUTF == NULL) {
            fprintf(stderr, "Memory allocation error\n");
            exit(EXIT_FAILURE);
        }

        int input_length = my_utf8_strlen(unicode);
        char fullBinary[] = "000000000000000000000";

        int num_bytes = 0;

        // if called with 4 hex digits, it can be either 1, 2, or 3 bytes in UTF-8
        if (input_length == 4) {
            if (unicode[0] == '0' && unicode[1] == '0' && unicode[2] < '8') { // it requires 1 byte
                printf("1 BYTES\n");
                num_bytes = 1;
                binaryUTF[0] = '0'; // first bit is 0

                // only want to convert the last 2 hex digits to binaryUTF and use only the last 3 bits of first digit,
                int j = 0; // keep track of which binaryUTF digit we're up to in the binaryUTF array
                hexBin = find_bin(unicode[2]);
                binaryUTF[++j] = hexBin[1];
                binaryUTF[++j] = hexBin[2];
                binaryUTF[++j] = hexBin[3];
                printf("ANSWER byte %s\n", binaryUTF);
                hexBin = find_bin(unicode[3]);
                binaryUTF[++j] = hexBin[0];
                binaryUTF[++j] = hexBin[1];
                binaryUTF[++j] = hexBin[2];
                binaryUTF[++j] = hexBin[3];
                printf("ANSWER byte %s\n", binaryUTF);
            }
            if (unicode[0] == '0' && unicode[1] < '8' && unicode[2] >= '8') { // it requires 2 bytes
                printf("2 BYTES\n");
                num_bytes = 2;
                int binLength = 12; // length of binary string since 2 or 3 hex digits
                int j = -1; // keep track of which binary digit we're up to in the binary array
                for (int i = 0; i < input_length - 1; i++) { // skip the first hex digit bc always 0
                    hexBin = find_bin(unicode[i + 1]); // skip the first hex digit bc always 0
                    printf("hexBin %s\n", hexBin);
                    for (int k = 0;
                         k < 4; k++) { // go through the binary converted string and append to the full binary string
                        fullBinary[++j] = hexBin[k];
                        printf("i = %d and k = %c and index = %d\n", i, hexBin[k], j);
                    }
                }
                printf("full binaryUTF %s\n", fullBinary);

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
                        printf("i = %d and adding %c and count = %d and full is %s \n", i, fullBinary[i], j, binaryUTF);
                        j++;
                    } else if (j == 8) {// skip locations 8 and 9 and add after
                        j = 10;
                        binaryUTF[j] = fullBinary[i];
                        printf("i = %d and adding %c and count = %d and full is %s \n", i, fullBinary[i], j, binaryUTF);
                        j++;
                    }
                }
            }
            if (unicode[0] >= '1' ||
                unicode[1] >= '8') { //'0' && unicode[1] < '8' && unicode[2] >= '8') { // it requires 3 bytes
                printf("3 BYTES\n");
                num_bytes = 3;
                int binLength = 16; // length of binary string since 3 or 4 hex digits
                int j = -1; // keep track of which binary digit we're up to in the binary array
                for (int i = 0; i < input_length; i++) {
                    hexBin = find_bin(unicode[i]);
                    printf("hexBin %s\n", hexBin);
                    for (int k = 0;
                         k < 4; k++) {// go through the binary converted string and append to the full binary string
                        fullBinary[++j] = hexBin[k];
                        printf("i = %d and k = %c and index = %d\n", i, hexBin[k], j);
                    }
                }
                printf("full binaryUTF %s\n", fullBinary);
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
                        printf("i = %d and adding %c and count = %d and full is %s \n", i, fullBinary[i], j, binaryUTF);
                        j++;
                    } else if (j == 8) {// skip locations 8 and 9 and add after
                        j = 10;
                        binaryUTF[j] = fullBinary[i];
                        printf("i = %d and adding %c and count = %d and full is %s \n", i, fullBinary[i], j, binaryUTF);
                        j++;
                    } else if (j == 16) {// skip locations 16 and 17 and add after
                        j = 18;
                        binaryUTF[j] = fullBinary[i];
                        printf("i = %d and adding %c and count = %d and full is %s \n", i, fullBinary[i], j, binaryUTF);
                        j++;
                    }
                }
                int lenUTF = my_utf8_strlen(binaryUTF);
                printf("binary = %s, binaryUTF = %s, length of utf = %d\n", fullBinary, binaryUTF, lenUTF);
            }

            // if called with more than 4 hex digits, it is 4 bytes in UTF-8
        } else if (input_length > 4) {
            printf("4 BYTES\n");
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
                hexBin = find_bin(unicode[i]);
                printf("hexBin %s\n", hexBin);
                for (int k = 0;
                     k < 4; k++) {// go through the binary converted string and append to the full binary string
                    fullBinary[++j] = hexBin[k];
                    printf("i = %d and k = %c and index = %d\n", i, hexBin[k], j);
                }
            }
            printf("full binaryUTF %s\n", fullBinary);
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
                    printf("i = %d and adding %c and count = %d and full is %s \n", i, fullBinary[i], j, binaryUTF);
                    j++;
                } else if (j == 8) {// skip locations 8 and 9 and add after
                    j = 10;
                    binaryUTF[j] = fullBinary[i];
                    printf("i = %d and adding %c and count = %d and full is %s \n", i, fullBinary[i], j, binaryUTF);
                    j++;
                } else if (j == 16) {// skip locations 16 and 17 and add after
                    j = 18;
                    binaryUTF[j] = fullBinary[i];
                    printf("i = %d and adding %c and count = %d and full is %s \n", i, fullBinary[i], j, binaryUTF);
                    j++;
                } else if (j == 24) {// skip locations 24 and 25 and add after
                    j = 26;
                    binaryUTF[j] = fullBinary[i];
                    printf("i = %d and adding %c and count = %d and full is %s \n", i, fullBinary[i], j, binaryUTF);
                    j++;
                }
            }
            int lenUTF = my_utf8_strlen(binaryUTF);
            printf("binary = %s, binaryUTF = %s, length of utf = %d\n", fullBinary, binaryUTF, lenUTF);
        }
        printf("out of if\n");
        printf("binary = %s, binaryUTF = %s\n", fullBinary, binaryUTF);

        // convert the binaryUTF string to hex
        int lenUTF = my_utf8_strlen(binaryUTF);
        char hexUTF8[3 * num_bytes]; // Assuming 2 characters per byte and space for null terminator

        int j = 0; // keep track of where in hex array we are
        for (int i = 0; i < lenUTF; i += 4) {
            printf("i = %d\n", i);
            char bin[4];
            for (int k = 0; k < 4; k++) { // get the 4 bits of the binaryUTF
                bin[k] = binaryUTF[i + k];
            }
            char hex_dig = find_hex(bin);
            printf("i = %d, j = %d, binary = %s hex_dig = %c\n", i, j, bin, hex_dig);
            if (j == 2 || j == 5 || j == 8) { // skip the spaces
                hexUTF8[j++] = ' ';
            }
            hexUTF8[j++] = hex_dig;
        }
        hexUTF8[j] = '\0'; // Null-terminate the hex string

        printf("Here is hex %s\n", hexUTF8);

        for (int c = 0; c < my_utf8_strlen(hexUTF8); c++){
            output[loop + c] = hexUTF8[c];
            printf("LOPP I c=%d output=%s bini=%c hexi=%c\n", c, output, binaryUTF[c], hexUTF8[c]);
        }
        printf("OUTPUT %s\n", output);
        free(binaryUTF);
        loop = loop + my_utf8_strlen(hexUTF8);
        if (fullUnicode[0] != '\0') { // add a space between the encoding of each character, so long as not the last one
            output[loop] = ' ';
            loop++;
        }
    }
}


// a hex UTF-8 can never begin with A or B - only 0, 1, C, D, E, F & the subsequent bytes can only begin with 8,9,A,B
int my_utf8_check(char *string){
    if (my_utf8_strlen(string) > 2) {
        if (string[0] != 'C' && string[0] != 'D' && string[0] != 'E' && string[0] != 'F') {
            printf("1 ERROR: %s is not a valid UTF-8 hex\n", string);
            return 0;
        }
        for (int i = 1; i <= my_utf8_strlen(string); i++) {
            if (i == 3 || i == 6 || i == 9) { // if it's the first digit of subsequent bytes it can only be 8,9,A,B
                if (string[i] != 'A' && string[i] != 'B' && string[i] != '8' && string[i] != '9') {
                    printf("2 ERROR: %s is not a valid UTF-8 hex\n", string);
                    return 0;
                }
            }else if (i == 2 || i == 5 || i == 8 || i == 11){ // skip the spaces
                continue;
            }else{
                if (string[i] < '0' || (string[i] > '9' && string[i] < 'A') || string[i] > 'F') {
                    printf("3 ERROR: %s is not a valid UTF-8 hex\n", string);
                    return 0;
                }
            }
        }
        // it's 1 byte, so it is ascii and must be between 00 and 7F
    }else{
//        printf("string = %s, int1 = %d int2 = %d\n", string, string[0], string[1]);
        if (string[0] < '0' || string[0] > '7') {
            printf("4 ERROR: %s is not a valid UTF-8 hex\n", string);
            return 0;
        }
        if (strlen(string) == 2){
//            printf("sting[1] = %c int = %d\n", string[1], string[1]);
            if (string[1] < '0' || (string[1] > '9' && string[1] < 'A') || string[1] > 'F') {
                printf("5 ERROR: %s is not a valid UTF-8 hex\n", string);
                return 0;
            }
        }
    }
    printf("%s is a valid UTF-8 hex\n", string);
    return 1;
}

//Returns the UTF8 encoded character at the location specified.
char *my_utf8_charat(char *string, int index) {
    int i = 0; // to loop through the bytes of the string
    int j = 0; // to loop through the actual characters of the string
    int previ = 0; // to keep track of the previous character bytes to can ultimately calculate the bytes of the char
    int prevj = 0; // to keep track of the actual index bc will loop one extra time to find its bytes
    int bytes = 0; // bytes of the char at index
    while (prevj != index) {
        // check the hex of the character and compare it to the max hex value for the first byte to determine how many
        // bytes the char is (based on the wiki page). Skip that many chars and add 1 to the length
        previ = i;
        prevj = j;
        if (string[i] >= '\x0' && string[i] < '\x7F') { // this means the ith char is 1 byte
            i += 1;
            j += 1;
        } else if (string[i] >= '\xF0') { // this means the ith char is 4 bytes
            i += 4;
            j += 1;
        } else if (string[i] >= '\xE0' && string[i] < '\xF0') { // this means the ith char is 3 bytes
            i += 3;
            j += 1;
        } else if (string[i] >= '\xC0' && string[i] <= '\xE0') { // this means the ith char is 2 bytes
            i += 2;
            j += 1;
        }
        bytes = i - previ; // find out how many bytes the ith character was so can know when fall out of the loop how many bytes the character at index is
    }

    unsigned char st[bytes * 2];

    for (int b = 0; b < bytes; b++) {
        st[b] = string[previ + b];
    }
    printf("char at index %d = %s\n", index, st);
}

int my_utf8_strcmp(char *string1, char *string2){
    int i = 0;
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

int my_utf8_strchr(char* str, int ch){
    // check how many bytes the input character is
    int bytes = 0;
    if (ch >= '\x0' && ch < '\x7F') { // this means the ith char is 1 byte
        bytes = 1;
    } else if (ch >= '\xF0') { // this means the ith char is 4 bytes
        bytes = 4;
    } else if (ch >= '\xE0' && ch < '\xF0') { // this means the ith char is 3 bytes
        bytes = 3;
    } else if (ch >= '\xC0' && ch <= '\xE0') { // this means the ith char is 2 bytes
        bytes = 2;
    }
    printf("bytes = %d\n", bytes);

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
    return 0;
}

// Takes a UTF8 encoded string, and returns a string, with ASCII representation where possible, and UTF8 character
// representation for non-ASCII characters.
int my_utf8_decode(char *input, char *output){
    // check how many bytes the input utf8 is
    int bytes = 0;
    if (input[0] < '0' || input[0] > '7') { // know 1 byte if begins with 0-7 - so ascii
        bytes = 1;
    }
    if (input[0] == 'C' || input[0] == 'D') { // know 2 bytes if begins with C or D
        bytes = 2;
    }
    if (input[0] == 'E') { // know 3 bytes if begins with E
        bytes = 3;
    }
    if (input[0] == 'F') { // know 3 bytes if begins with E
        bytes = 4;
    }



    return 0;
}


int main(void) {
    char output[100];
//    my_utf8_encode("u+0001", output); // 1 byte ones need to be b4 2 byte ones bc output gets messed up
//    printf("ANSWER %s\n", output);
//    printf("\n");

//    my_utf8_encode("u+007F", output); // 7F
//    printf("ANSWER %s\n", output);
//    printf("\n");
//
//    my_utf8_encode("u+008F", output); //C2 8F
//    printf("ANSWER %s\n", output);
//    printf("\n");

//    my_utf8_encode("u+07FF", output); // DF BF
//    printf("ANSWER %s\n", output);
//    printf("\n");

//    my_utf8_encode("u+0080", output); // C2 80
//    printf("ANSWER %s\n", output);
//    printf("\n");

//    my_utf8_encode("u+0800", output); // E0 A0 80
//    printf("ANSWER %s\n", output);
//    printf("\n");

//    my_utf8_encode("u+FFFF", output); // EF BF BF
//    printf("ANSWER %s\n", output);
//    printf("\n");

//    my_utf8_encode("u+0C9A", output); // E0 B2 9A
//    printf("ANSWER %s\n", output);
//    printf("\n");

//    my_utf8_encode("u+20AC", output); // E2 82 AC
//    printf("ANSWER %s\n", output);
//    printf("\n");

//    my_utf8_encode("u+D55C", output); // ED 95 9C
//    printf("ANSWER %s\n", output);
//    printf("\n");

//    my_utf8_encode("u+10000", output); // F0 90 80 80
//    printf("ANSWER %s\n", output);
//    printf("\n");

//    my_utf8_encode("u+10FFFF", output); // F4 8F BF BF
//    printf("ANSWER %s\n", output);
//    printf("\n");

//    my_utf8_encode("u+10348", output); // F0 90 8D 88
//    printf("ANSWER %s\n", output);
//    printf("\n");

//    my_utf8_encode("u+0048u+0065u+006Cu+006Cu+006Fu+0021", output); // 48 65 6C 6C 6F 21
//    printf("ANSWER %s\n", output);
//    printf("\n");
//
//    my_utf8_encode("u+10FFFFu+0065u+D55Cu+006C", output); // F4 8F BF BF - 65 - ED 95 9C - 6C
//    printf("ANSWER %s\n", output);
//    printf("\n");

//    my_utf8_encode("u+10FFFFu+0080u+D55Cu+10348", output); // F4 8F BF BF - C2 80 - ED 95 9C - F0 90 8D 88
//    printf("ANSWER %s\n", output);
//    printf("\n");

//    char* string1 = "אריה";
//    printf("Length of %s = %d\n", string1, my_utf8_strlen(string1)); //4
//    char* string2 = "אA•";
//    printf("Length of %s = %d\n", string2, my_utf8_strlen(string2)); //3
//    char* string3 = "Arieh";
//    printf("Length of %s = %d\n", string3, my_utf8_strlen(string3)); //5
//    printf("\n");

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

//    my_utf8_charat("אריה", 3); //r
//    my_utf8_charat("א•שלי", 1); //r
//    my_utf8_charat("אש•לי", 3); //r

    char source[] = "שלום";
    char dest[20];

    char source1[] = "א•שלי";
    char dest1[20];

    char source2[] = "Arieh";
    char dest2[20];

    // Copying the source string to dest
    my_utf8_strncpy(dest, source, 3);
    my_utf8_strncpy(dest1, source1, 2);
    my_utf8_strncpy(dest2, source2, 2);

    // printing result
    printf("Source: %s\n", source);
    printf("Destination: %s\n", dest);
    // printing result
    printf("Source: %s\n", source1);
    printf("Destination: %s\n", dest1);
    // printing result
    printf("Source: %s\n", source2);
    printf("Destination: %s\n", dest2);

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


//    my_utf8_strchr("שלום",'ל');


//    char* string1 = "אריה";
//    char* string2 = "ריה";
//    my_utf8_strcmp(string1, string2); // 1
//    char* string3 = "ריה";
//    char* string4 = "אריה";
//    my_utf8_strcmp(string3, string4); // -1
//    my_utf8_strcmp(string1, string4); // 0
//    char* string5 = "אריה";
//    char* string6 = "Arieh";
//    my_utf8_strcmp(string5, string6); // does it need to work with other languages???????
//    char* string7 = "אריה";
//    char* string8 = "ארי";
//    my_utf8_strcmp(string7, string8); // 1
    return 1;
}
