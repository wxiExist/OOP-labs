#ifndef LAB2_H
#define LAB2_H

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <string>

unsigned char charToHex(char c);
char hexToChar(unsigned char c);

class Array {
protected:
    unsigned char* _digits;
    size_t _capacity;
    size_t _size;

public:
    Array(); 
    Array(size_t capacity); 
    Array(const std::initializer_list<unsigned char>& digits);
    Array(const Array& other);
    Array(Array&& other) noexcept;
    virtual ~Array() noexcept;

    Array& operator=(const Array& other);
    Array& operator=(Array&& other) noexcept;

    size_t size() const;
    unsigned char& operator[](size_t index);
    const unsigned char& operator[](size_t index) const;

    Array& operator+=(const Array& other);
    Array& operator-=(const Array& other);

    bool operator==(const Array& other) const;
    bool operator!=(const Array& other) const;
    bool operator<(const Array& other) const;
    bool operator>(const Array& other) const;
};

class Hex : public Array {
public:
    Hex();
    Hex(const std::string& hexStr);
    Hex(const Hex& other);
    Hex(Hex&& other) noexcept;
    virtual ~Hex() noexcept;

    Hex& operator=(const Hex& other);
    Hex& operator=(Hex&& other) noexcept;

    Hex& operator+=(const Hex& other);
    Hex& operator-=(const Hex& other);

    bool operator==(const Hex& other) const;
    bool operator!=(const Hex& other) const;
    bool operator<(const Hex& other) const;
    bool operator>(const Hex& other) const;

    std::string toString() const;

private:
    unsigned char charToHex(char c) const;
    char hexToChar(unsigned char hexVal) const;

    std::string hexOperation(const std::string& hex1, const std::string& hex2, char operation);
    int hexCompare(const std::string& hex1, const std::string& hex2) const;
};

#endif