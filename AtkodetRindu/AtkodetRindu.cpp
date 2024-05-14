#include <iostream>
#include <string>
#include <bitset>
#include <sstream>

#define sev 0b10000000
#define six 0b1000000
#define fiv 0b100000
#define fou 0b10000
#define thr 0b1000
#define two 0b100
#define one 0b10
#define zer 0b1

using namespace std;

// Функция для кодирования группы из трех символов
string encodeGroup(const string& group) {
    char A, B , C , D ;
    //cout << group << endl;;
    if (group.length() < 3) {
        return " ";
    }
    
    A = (0 << 7  | ((group[0] & sev) >> 1) | 1<<5 | ((group[1] & six) >> 2) | ((group[2] & fiv) >> 2) | ((group[0] & thr) >> 1) | ((group[1] & two) >> 1) | ((group[2] & one) >> 1));
    B = (0 << 7 | ((group[1] & sev) >> 1) | 1 << 5 | ((group[2] & six) >> 2) | ((group[0] & fou) >> 1) | ((group[1] & thr) >> 1) | ((group[2] & two) >> 1) | ((group[0] & zer)));
    C = (0 << 7 | ((group[2] & sev) >> 1) | 1 << 5 | ((group[0] & fiv) >> 1) | ((group[1] & fou) >> 1) | ((group[2] & thr) >> 1) | ((group[0] & one)) | ((group[1] & zer)));
    D = (0 << 7 | ((group[0] & six)) | 1 << 5 | ((group[1] & fiv) >> 1) | ((group[2] & fou) >> 1) | ((group[0] & two)) | ((group[1] & one)) | ((group[2] & zer)));

    string str;
    str += A;
    str += B;
    str += C;
    str += D;

    return str;
}
// Функция для декодирования группы из четырех символов
string decodeGroup(const string& group) {
    char a, b, c;

    if (group.length() != 4) {
        return ""; 
    }

    char A = group[0];
    char B = group[1];
    char C = group[2];
    char D = group[3];

    

    // Декодируем символы из группы
    a = ((A & six) << 1) | ((D & six)) | ((C & fou) << 1) | ((B & thr) << 1) | ((A & two) << 1) | (D & two) | (C & one) | (B & zer);
    b = ((B & six) << 1) | ((A & fou) << 2) | ((D & fou) << 1) | ((C & thr) << 1) | ((B & two) << 1) | ((A & one) << 1) | (D & one) | (C & zer);
    c = ((C & six) << 1) | ((B & fou) << 2) | ((A & thr) << 2) | ((D & thr) << 1) | ((C & two) << 1) | ((B & one) << 1) | ((A & zer) << 1) | (D & zer);

    string original;
    original += a;
    original += b;
    original += c;

    return original;
}

// Функция для разделения строки на группы по три символа
string divideString(const string& input) {
    string divided;
    for (size_t i = 0; i < input.length(); i += 3) {
        string group = input.substr(i, 3); // Получаем группу из трех символов
        while (group.length() < 3) {
            group += '0'; // Дополняем группу нулями, если она короче трех символов
        }
        divided += (encodeGroup(group)); // Кодируем группу и добавляем в результат
    }
    return divided;
}

// Функция для восстановления исходной строки
string decodeString(const string& input) {
    string decoded;
    for (size_t i = 0; i < input.length(); i += 4) {
        string group = input.substr(i, 4); // Получаем группу из четырех символов
        while (group.length() < 4) {
            group += '0';
        }
        string originalGroup = decodeGroup(group); // Декодируем группу
        decoded += originalGroup;
    }
    return decoded;
}

int main() {
    

    string input = "First, solve the problem";
    string divided = divideString(input); // Разделяем строку на группы и кодируем
    cout << "Encoded groups: " << divided << endl;

    string encoded = "9:,s81:w>55u> 3v<!9r=45u)10}9%<|861(:411-;0q>38s92=3>!1t;77r83:s:(1t;83y:?0|*-2p:2;x:0<0:!8p<!9r>63~:0=2-;0y(30t,16u*,0v.%3684\"s:>2s829*:>3{;9:x0)8t";
    string decoded = decodeString(encoded);
    cout << "Decoded string: " << decoded << endl;
    return 0;
}
