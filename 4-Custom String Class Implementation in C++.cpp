#include <iostream>

using namespace std;

class BaseString {
protected:
    char* p;
    int len;
    int capacity;

public:
    //конструкторы

    BaseString(char* ptr) {
        char* p1 = ptr;
        while (*p1++ != '\0')
            ;

        len = p1 - ptr;
        if (len + 1 > 256)
            capacity = len + 1;
        else
            capacity = 256;
        p = new char[capacity];

        p1 = ptr;
        char* p2 = p;
        while ((*p2++ != *p1++) != '\0')
            ;

        p[len] = '\0';
    }
    BaseString(const char* ptr) {
        int i = 0;
        while (ptr[i] != '\0')
            i++;

        len = i;
        if (len + 1 > 256)
            capacity = len + 1;
        else
            capacity = 256;
        p = new char[capacity];
        for (i = 0; ptr[i] != '\0'; i++)
            p[i] = ptr[i];
        p[len] = '\0';
    }

    BaseString(int Capacity = 256) {
        capacity = Capacity;
        p = new char[capacity];
        len = 0;
    }

    //деструктор

    ~BaseString() {
        if (p != NULL)
            delete[] p;
        len = 0;
    }

    // конструктор копирования

    BaseString(const BaseString& s) {
        capacity = s.capacity;
        len = s.len;
        p = new char[capacity];
        for (int i = 0; s.p[i] != '\0'; i++)
            p[i] = s.p[i];
        p[len] = '\0';
    }

    int Length() { return len; }
    int Capacity() { return capacity; }
    char* get() { return p; }
    char& operator[](int i) { return p[i]; }

    BaseString& operator=(BaseString& s) {
        cout << "\nBase Operator = \n";

        if (capacity < s.capacity) {
            delete[] p;
            capacity = s.capacity;
            p = new char[s.capacity];
        }
        len = s.len;

        for (char* p1 = s.p, *p2 = p; *p1 != '\0'; *p2++ = *p1++)
            ;
        p[len] = '\0';

        return *this;
    }

    virtual void print() {
        int i = 0;
        while (p[i] != '\0') {
            cout << p[i];
            i++;
        }
    }
};

class String : virtual public BaseString {
public:
    String(int Capacity) : BaseString(Capacity) {}
    String(char* s) : BaseString(s) {}
    String(const char* s) : BaseString(s) {}
    String(const String& other) : BaseString(other) {}

    int LongestWordIndex() {
        int maxLength = 0;
        int maxIndex = 0;
        int maxWordIndex = 0;
        int currentLength = 0;
        int currentIndex = 0;
        int currentWordIndex = 0;
        char* ptr = p;

        while (*ptr != '\0') {
            if (*ptr == ' ') {
                if (currentLength > maxLength) {
                    maxLength = currentLength;
                    maxIndex = currentIndex;
                    maxWordIndex = currentWordIndex;
                }
                currentLength = 0;
                currentIndex = ptr - p + 1;
                currentWordIndex++;
            }
            else {
                currentLength++;
            }
            ptr++;
        }

        if (currentLength > maxLength) {
            maxLength = currentLength;
            maxIndex = currentIndex;
            maxWordIndex = currentWordIndex;
        }

        return maxWordIndex;
    }
};


int main()
{
    BaseString s1("123 321 123");
    s1.print();
    cout << '\n';

    String s2("456 654 456");
    s2.print();
    cout << '\n';

    String s3 = "789 987 789";
    s3.print();
    cout << '\n';

    String s4 = "1 22 333 4444 55555 4444 333 22 1";
    cout << s4.LongestWordIndex();

    return 0;
}
