//
// Created by Sergei on 11/29/24.
//

#ifndef BIGINT_H
#define BIGINT_H

#include <string>
#include <iostream>

class bigint {
private:
    int32_t* digits_;
    size_t size_;
    bool negative_;

    const int BLOCK_SIZE = 1000000000;

public:
    bigint();
    explicit bigint(const std::string& str);
    ~bigint();
    bigint(const bigint& other);
    bigint& operator=(const bigint& other);
    bigint(bigint&& other);
    bigint& operator=(bigint&& other);

    bigint operator-() const;
    bigint operator+(int32_t other) const;
    bigint operator-(int32_t other) const;
    bigint operator*(int32_t other) const;
    bigint operator+(const bigint& other) const;
    bigint operator-(const bigint& other) const;
    bigint operator*(const bigint& other) const;

    friend std::ostream& operator<<(std::ostream& os, const bigint& number);
};

#endif // BIGINT_H

