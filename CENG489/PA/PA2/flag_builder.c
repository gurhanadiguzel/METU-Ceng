#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// void letter_builder(char* str, int len) {
//     for (int i = 0; i < len; i++) {
//         str[i] = 'a' + i;
//     }
//     str[len] = '\0';
// }

void letter_builder(char* dest, char letter) {
    sprintf(dest, "%c", letter);
}

void number_builder(char* str, int num) {
    sprintf(str, "%d", num);
}

char* flag_builder() {
    char* flag = malloc(65);
    memset(flag, 0, 65);

    char letters[3];
    letter_builder(letters, 2);
    strcat(flag, letters);

    char number[4];
    number_builder(number, 4);
    strcat(flag, number);

    char letter = 'A' + 5;
    strncat(flag, &letter, 1);

    return flag;
}

char* flag_extender() {
    char* flag = (char*)malloc(64);
    memset(flag, 0, 64);

    int a = 0;
    int b = 1;
    int c = 2;
    int d = 3;
    int e = 4;
    int f = 5;
    int g = 6;
    int h = 7;
    int i = 8;
    int j = 9;

    letter_builder(flag, 'a');
    letter_builder(flag + 1, 'b');
    number_builder(flag + 2, c);
    letter_builder(flag + 4, 'e');
    letter_builder(flag + 5, 'f');
    number_builder(flag + 6, g);
    letter_builder(flag + 8, 'i');
    letter_builder(flag + 9, 'j');
    number_builder(flag + 10, a);
    letter_builder(flag + 12, 'c');
    letter_builder(flag + 13, 'd');
    number_builder(flag + 14, e);
    letter_builder(flag + 16, 'g');
    letter_builder(flag + 17, 'h');
    number_builder(flag + 18, i);
    letter_builder(flag + 20, 'k');
    letter_builder(flag + 21, 'l');
    number_builder(flag + 22, j);

    return flag;
}

int main() {
    char* flag = flag_builder();
    char* flag2 = flag_extender();
    printf("%s\n", flag);
    printf("%s\n", flag2);

    free(flag);
    free(flag2);

    return 0;
}
