#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



size_t getline(char **lineptr, size_t *n, FILE *stream)
{
    char* buf = *lineptr;
    size_t c,i = 0;
    if(buf == NULL || *n == 0)
    {
        *lineptr = malloc(10);
        buf = *lineptr;
        *n = 10;
    }
    while((c = fgetc(stream)) != '\n')
    {
        if(c == EOF)
        {
            return - 1;
        }
        if(i < *n - 2) //留给'\n'和'\0'
        {
            *(buf + i) = c;
            i++;
        }
        else
        {
            *n = *n + 10;
            buf = realloc(buf, *n);
            *(buf + i++) = c;
        }
    }
    *(buf + i++) = '\n';
    *(buf + i) = '\0';
    return i;
}

typedef struct 
{
    char* buffer;
    size_t buffer_length;
    size_t input_length;
} InputBuffer;

InputBuffer* new_input_buffer() 
{
    InputBuffer* input_buffer = malloc(sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;

    return input_buffer;
}

void print_prompt() 
{
    printf("db > ");
}

void read_input(InputBuffer* input_buffer)
{
    size_t bytes_read = getline(&(input_buffer->buffer),&(input_buffer->buffer_length),stdin);
    if(bytes_read <= 0)
    {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }
    input_buffer->input_length = bytes_read - 1;
    input_buffer->buffer[bytes_read - 1] = 0;
}

void close_input_buffer(InputBuffer* input_buffer)
{
    free(input_buffer->buffer);
    free(input_buffer);
}


int main(int argc, char* argv[])
{
    InputBuffer* input_buffer = new_input_buffer();
    while(true)
    {
        print_prompt();
        read_input(input_buffer);
        if(strcmp(input_buffer->buffer, ".exit") == 0)
        {
            close_input_buffer(input_buffer);
            exit(EXIT_SUCCESS);
        }
        else{
            printf("Unrecognized command '%s'.\n", input_buffer->buffer);
        }
    }
}