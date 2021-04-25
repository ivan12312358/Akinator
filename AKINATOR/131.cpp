#include <stdio.h>
#include <stdlib.h>


void ahu(char** str){
    *str = (char*)calloc(10, sizeof(char));
}

int main(){

    char* str = nullptr;
    ahu(&str);

    for(int i = 0; i < 10; i++){
        str[i] = i;
    }

    free(str);

    return 0;
}
