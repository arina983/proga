#include <stdio.h>

void addition(char *txt, char *result){
    int i = 0;
    int j = 0;
    for (i = 0; txt[i] != '\0'; i ++){
        result[j ++] = txt[i];
        if(txt[i] == ' ' && txt[i + 1] != ' ' && txt[i + 1] != '\0'){
            result[j ++] = '?';
        }
    }
    result[j] = '\0';
    }

int main() {
    char txt[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
    char result[20000];
    addition(txt, result);
    printf("%s\n", result);
    return 0;
}