#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    FILE* f = fopen(argv[1], "r");

    fseek(f, 0, SEEK_END);
    int size = ftell(f);
    rewind(f);

    char* str = (char*) calloc (size, sizeof(char));

    fread(str, sizeof(char), size, f);

    for(int i = 0; i < size; i++){
        if(str[i] == '{' || str[i] == '}')
        {
            str[i] = '\0';
        }
    }


}
