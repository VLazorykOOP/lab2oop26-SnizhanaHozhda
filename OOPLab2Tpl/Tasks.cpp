#include <iostream>
#include <conio.h>
#include <iomanip>
#include "Tasks.h"
#include "Examples.h"
#include "string"
#include <vector>

using namespace std;

unsigned char my_pbit(unsigned char c) {
    unsigned char t = 1, b = 0;
    for (int j = 0; j < 8; j++) {
        if (c & t) {
            if (b == 0) b = 1; else b = 0;
        }
        t <<= 1;
    }
    return b;
}

void MenuTask()
{
    cout << "     Menu Task   \n";
    cout << "    1.  Calculation of expressions using bitwise operations  \n";
    cout << "    2.  Data encryption using bitwise operations \n";
    cout << "    3.  Data encryption using structures with bit fields \n";
    cout << "    4.  The problem of using bitwise operations \n";
    cout << "    5.  Examples of problems using bitwise operations \n";
    cout << "    6.  Exit \n";
}



void task1() {
    // Обчислення виразів з використанням побітових операцій
    // Calculation of expressions using bitwise operations 
    cout << " Calculation of expressions using bitwise operations  \n";
    int a, b, c, d;
    cout << "Enter a,b,c,d";
    cin >> a >> b >> c >> d;
    long long x = ((b << 5) + b) + (((d << 4) - d) + ((a << 3) + (a << 2)) >> 9) -
        ((c << 6) + c) + ((d << 4) - (d << 1));
    long long y = 33 * b + (d * 15 + 12 * a) / 512 - 65 * c + d * 14;

    cout << "Result (bitwise):   " << x << endl;
    cout << "Result (arithmetic):  " << y << endl;

    if (x == y) {
        cout << " Results match!" << endl;
    }
    else {
        cout << "Error! Check formula logic." << endl;
    }
    cout << "\nPress Enter to return to menu...";
    _getch();

}

void task2()
{
    // Шифрування даних з використання побітових операцій 
    // Data encryption using bitwise operations
    cout << " Data encryption using bitwise operations  \n";
    string text;
    cout << "Enter text: ";

    if (cin.peek() == '\n') cin.ignore();

    getline(cin, text);

    unsigned short encrypted[128] = { 0 };

    for (int i = 0; i < text.length() && i < 128; i++) {
        unsigned char c = (unsigned char)text[i];
        unsigned short pos = (unsigned short)i;

        unsigned short b = 0;
        unsigned char temp_c = c; 
        for (int j = 0; j < 8; j++) {
            if (temp_c & 1) b = !b;
            temp_c >>= 1;
        }
        unsigned short r = 0;
        r |= (b & 1);      ///    b = 0101  01010    0000  0001  
        r |= (c << 1);     
        r |= (pos << 9);   

        encrypted[i] = r;
    }
    cout << "\nEncrypted result (16-bit HEX):" << endl;
    for (int i = 0; i < text.length(); i++) {
        cout << "0x" << hex << uppercase << setw(4) << setfill('0') << encrypted[i] << " ";

        if ((i + 1) % 8 == 0) cout << endl; 
    }
    cout << dec << "\n\nDecrypted text: ";
    for (int i = 0; i < text.length(); i++) {
        unsigned char original_c = (unsigned char)((encrypted[i] >> 1) & 0xFF);
        cout << (char)original_c;
    }
    cout << "\n\nPress any key to return...";
    _getch();

}


void task3()
{
    // Шифрування даних з використання стуктур з бітовими полями 
    // Data encryption using structures with bit fields
    cout << "  Data encryption using structures with bit fields \n";
    struct MyBitFields {
        unsigned short bitp : 1;  
        unsigned short symbol : 8;  // 0  0000 00000  0000 000 
        unsigned short pos : 7;  
    };

    union MyContainer {
        MyBitFields bits;           
        unsigned short full_value; 
    };

    string text;
    cout << "Enter text: ";
    if (cin.peek() == '\n') cin.ignore();
    getline(cin, text);

    MyContainer encrypted[128] = { 0 };

    for (int i = 0; i < text.length() && i < 128; i++) {
        unsigned char c = (unsigned char)text[i];

        encrypted[i].bits.bitp = my_pbit(c);     
        encrypted[i].bits.symbol = c;             
        encrypted[i].bits.pos = (unsigned short)i;
    }

    cout << "\nEncrypted result (16-bit HEX):\n";
    for (int i = 0; i < text.length(); i++) {
        cout << "0x" << hex << uppercase << setw(4) << setfill('0') << encrypted[i].full_value << " ";
        if ((i + 1) % 8 == 0) cout << endl;
    }

    cout << dec << "\n\nDecrypted text: ";
    for (int i = 0; i < text.length(); i++) {
        cout << (char)encrypted[i].bits.symbol;
    }

    cout << "\n\nPress any key to return...";
    _getch();
}




void task4()
{   // Задача із використання побітових операцій
    // The problem of using bitwise operations
    cout << " Data encryption using structures with bit fields \n";
    string text;
    int shift;

    cout << "\n--- Task 4.6 (Cyclic Bit Shift) ---" << endl;
    cout << "Enter text: ";

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, text);

    cout << "Enter shift value: ";
    cin >> shift;

    int n = text.length();
    if (n == 0) return;

    vector<unsigned char> myBytes(text.begin(), text.end());

    for (int s = 0; s < shift; s++) {
        unsigned char first_byte_top_bit = (myBytes[0] & 0x80) ? 1 : 0;

        for (int i = 0; i < n; i++) {
            unsigned char carry;
            if (i < n - 1) {
                carry = (myBytes[i + 1] & 0x80) ? 1 : 0;
            }
            else {
                carry = first_byte_top_bit;
            }

            myBytes[i] <<= 1;

            if (carry) {
                myBytes[i] |= 1;
            }
        }
    }

    cout << "\nResulting HEX: ";
    for (int i = 0; i < n; i++) {
        cout << hex << uppercase << setw(2) << setfill('0') << (int)myBytes[i] << " ";
    }

    cout << dec << "\nResulting text: ";
    for (int i = 0; i < n; i++) {
        cout << (char)myBytes[i];
    }

    cout << "\n\nPress any key to return...";
    _getch();
}




