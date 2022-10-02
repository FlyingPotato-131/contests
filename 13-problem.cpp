#include <iostream>
std::int64_t pow(int value, int p) {
    if (p == 0) {
        return 1;
    }
    int result = 1;
    for (int i = 0; i < p; i++)
    {
        result *= value;
    }
    return result;
}
char* itoa(std::int64_t num) {
    int size = 0;
    int temp_copy = num;
    while (temp_copy) {
        temp_copy /= 10;
        size++;
    }
    char* str = static_cast<char*>(std::malloc(size));// static_cast можно заменить на (char*s)
    int position = 0;
    str[size]='\0';
    while (size) {
        int pos=((num % pow(10, size)) / pow(10, size - 1));
        switch (pos) {
            case 0:
                str[position]='0';
                break;
            case 1:
                str[position]='1';
                break;
            case 2:
                str[position]='2';
                break;
            case 3:
                str[position]='3';
                break;
            case 4:
                str[position]='4';
                break;
            case 5:
                str[position]='5';
                break;
            case 6:
                str[position]='6';
                break;
            case 7:
                str[position]='7';
                break;
            case 8:
                str[position]='8';
                break;
            case 9:
                str[position]='9';
                break;
        }
        size--;
        position++;
    }
    return str;
}
