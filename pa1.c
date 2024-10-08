#include <stdio.h>
#include <stdint.h>

int32_t is_ascii(char str[]) {
    int32_t ascii = 1;

    for(int i = 0; str[i] != 0; i+= 1) {
        if(str[i] > 127 || str[i] < 0)
            ascii = 0;
    }
    
    return ascii;
}

int32_t capitalize_ascii(char str[]) {
    int32_t updated = 0;

    int index = 0;
    while(str[index] != 0) {
        
        if(str[index] >= 97 && str[index] <= 122) {
            str[index] = str[index] - 32;
            updated += 1;
        }
        index += 1;
    }
    return updated;
}

int32_t width_from_start_byte(char start_byte) {
    int32_t width = 0;
    int32_t firstFour = (start_byte & 0b11110000);

    if(firstFour == 0b01000000) 
        width = 1;
    else if (firstFour == 0b11000000)
        width = 2;
    else if (firstFour == 0b11100000)
        width = 3;
    else if (firstFour == 0b11110000)
        width = 4;
    else
        width = -1;

    return width;
}

int32_t utf8_strlen(char str[]) {
    int32_t length = 0;
    int32_t index = 0;

    while(str[index] != 0) {
        if(width_from_start_byte(str[index]) >= 1 && width_from_start_byte(str[index]) <= 4) {
            length += 1;
            index += width_from_start_byte(str[index]);
        }         
        else 
            length = -1;
    }

    return length;
}


int main() {
    printf("Is 🔥 ASCII? %d\n", is_ascii("🔥"));
    printf("Is abcd ASCII? %d\n", is_ascii("abcd"));

    int32_t ret = 0;
    char str[] = "abcd";
    ret = capitalize_ascii(str);
    printf("Capitalized String: %s\nCharacters updated: %d\n", str, ret);

    char s[] = "Héy"; // same as { 'H', 0xC3, 0xA9, 'y', 0 },   é is start byte + 1 cont. byte
    printf("Width: %d bytes\n", width_from_start_byte(s[1])); // start byte 0xC3 indicates 2-byte sequence
    printf("Width: %d bytes\n", width_from_start_byte(s[2]));
    

    char str2[] = "Joséph";
    printf("Length of string %s is %d\n", str2, utf8_strlen(str2));

    return 0;
}