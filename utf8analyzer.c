#include <stdint.h>
#include <stdio.h>
#include <string.h>

int32_t is_ascii(char str[]);
int32_t capitalize_ascii(char str[]);
int32_t width_from_start_byte(char start_byte);
int32_t utf8_strlen(char str[]);
int32_t codepoint_index_to_byte_index(char str[], int32_t cpi);
void utf8_substring(char str[], int32_t cpi_start, int32_t cpi_end, char result[]);
int32_t codepoint_at(char str[], int32_t cpi);
char is_animal_emoji_at(char str[], int32_t cpi);

int main() {
    char buffer[50];  
    char input[50];
    char result[50];
    char animal_emojis[50];
    int32_t index = 0;
    int32_t byte_length = 0;
    
    printf("%s", "Enter a UTF-8 encoded string: ");
    fgets(buffer, 50, stdin);

    strcpy(input, buffer);

    printf("\nValid ASCII: %s\n", is_ascii(buffer) ? "true" : "false");
    capitalize_ascii(buffer);
    printf("Uppercased ASCII: %s\n", buffer);

    while(input[index] != 0) {
        byte_length += width_from_start_byte(index);
        index += width_from_start_byte(index);
    }
    //subtracting 1 for new line character
    printf("Length in bytes: %d\n", (byte_length - 1));
    printf("Number of code points: %d\n", (utf8_strlen(input) - 1));
    printf("Bytes per code point: ");
    for(int i = 0; i < utf8_strlen(input) - 1; i += 1){
        printf("%d ", width_from_start_byte(input[codepoint_index_to_byte_index(input, i)]));
    }
    utf8_substring(input, 0, 6, result);
    printf("\nSubstring of the first 6 code points: %s\n", result);
    printf("Code points as decimal numbers: ");
    for(int i = 0; i < utf8_strlen(input) - 1; i += 1){
        printf("%d ", codepoint_at(input, i));
    }
    printf("\nAnimal emojis: ");
    for(int i = 0; i < utf8_strlen(input) - 1; i+= 1){
        if(is_animal_emoji_at(input, i) == 1) {
            utf8_substring(input, i, i + 1, animal_emojis);
            printf("%s ", animal_emojis);
        }
               
    }
    printf("\n");

    return 0;
}