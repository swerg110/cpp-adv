#include "biginteger.h"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

bigint::bigint() : size_(1), negative_(false) {
    digits_ = new int32_t[size_]();
}

bigint::bigint(const std::string& str) {
    negative_ = (str[0] == '-');
    size_t start = negative_ ? 1 : 0;
    size_ = (str.length() - start + 8) / 9;

    digits_ = new int32_t[size_]();
    int32_t block_index = size_ - 1;
    int32_t curr_block = 0;
    int32_t block_position = 1;

    for (int i = str.length() - 1; i >= static_cast<int>(start); --i) {
        curr_block += (str[i] - '0') * block_position;
        block_position *= 10;

        if (block_position == BLOCK_SIZE || i == static_cast<int>(start)) {
            digits_[block_index--] = curr_block;
            curr_block = 0;
            block_position = 1;
        }
    }
}

bigint::~bigint() {
    delete[] digits_;
}

bigint::bigint(const bigint& other) {
    size_ = other.size_;
    negative_ = other.negative_;
    digits_ = new int32_t[size_];
    for (size_t i = 0; i < size_; ++i) {
        digits_[i] = other.digits_[i];
    }
}

bigint& bigint::operator=(const bigint& other) {
    if (this != &other) {
        delete[] digits_;
        size_ = other.size_;
        negative_ = other.negative_;
        digits_ = new int32_t[size_];
        for (size_t i = 0; i < size_; ++i) {
            digits_[i] = other.digits_[i];
        }
    }
    return *this;
}

bigint::bigint(bigint&& other) : size_(other.size_), negative_(other.negative_), digits_(other.digits_) {
    other.digits_ = nullptr;
    other.size_ = 0;
}

bigint& bigint::operator=(bigint&& other) {
    if (this != &other) {
        delete[] digits_;
        size_ = other.size_;
        negative_ = other.negative_;
        digits_ = other.digits_;
        other.digits_ = nullptr;
        other.size_ = 0;
    }
    return *this;
}

bigint bigint::operator-() const {
    bigint result = *this;
    result.negative_ = !negative_;
    return result;
}

bigint bigint::operator+(int32_t other) const {
    bigint result = *this;
    int carry = other;
    for (int i = result.size_ - 1; i >= 0 && carry != 0; --i) {
        result.digits_[i] += carry;
        if (result.digits_[i] >= BLOCK_SIZE) {
            result.digits_[i] -= BLOCK_SIZE;
            carry = 1;
        } else {
            carry = 0;
        }
    }
    return result;
}

bigint bigint::operator-(int32_t other) const {
    bigint result = *this;
    int carry = -other;
    for (int i = result.size_ - 1; i >= 0 && carry != 0; --i) {
        result.digits_[i] += carry;
        if (result.digits_[i] < 0) {
            result.digits_[i] += BLOCK_SIZE;
            carry = -1;
        } else {
            carry = 0;
        }
    }
    return result;
}

bigint bigint::operator*(int32_t other) const {
    bigint result = *this;
    int carry = 0;
    for (int i = result.size_ - 1; i >= 0; --i) {
        long long prod = static_cast<long long>(result.digits_[i]) * other + carry;
        result.digits_[i] = static_cast<int32_t>(prod % BLOCK_SIZE);
        carry = static_cast<int32_t>(prod / BLOCK_SIZE);
    }
    return result;
}

bigint bigint::operator+(const bigint& other) const {
    bigint result;
    result.size_ = std::max(size_, other.size_) + 1;
    result.digits_ = new int32_t[result.size_]();
    result.negative_ = negative_;
    int carry = 0;
    for (int i = result.size_ - 1; i >= 0; --i) {
        int32_t digit1 = (i < static_cast<int>(size_)) ? digits_[i] : 0;
        int32_t digit2 = (i < static_cast<int>(other.size_)) ? other.digits_[i] : 0;
        result.digits_[i] = digit1 + digit2 + carry;
        if (result.digits_[i] >= BLOCK_SIZE) {
            result.digits_[i] -= BLOCK_SIZE;
            carry = 1;
        } else {
            carry = 0;
        }
    }
    return result;
}

bigint bigint::operator-(const bigint& other) const {
    bigint result = *this;
    int carry = 0;
    for (int i = result.size_ - 1; i >= 0; --i) {
        int32_t digit2 = (i < static_cast<int>(other.size_)) ? other.digits_[i] : 0;
        result.digits_[i] -= digit2 + carry;
        if (result.digits_[i] < 0) {
            result.digits_[i] += BLOCK_SIZE;
            carry = 1;
        } else {
            carry = 0;
        }
    }

    return result;
}

bigint bigint::operator*(const bigint& other) const {
    bigint result;

    result.size_ = size_ + other.size_;
    result.digits_ = new int32_t[result.size_]();
    for (size_t i = 0; i < size_; ++i) {
        int carry = 0;
        for (size_t j = 0; j < other.size_; ++j) {
            long long prod = static_cast<long long>(digits_[size_ - 1 - i]) * other.digits_[other.size_ - 1 - j] + result.digits_[result.size_ - 1 - i - j] + carry;
            result.digits_[result.size_ - 1 - i - j] = static_cast<int32_t>(prod % BLOCK_SIZE);
            carry = static_cast<int32_t>(prod / BLOCK_SIZE);
        }
        if (carry > 0) {
            result.digits_[result.size_ - 1 - i - other.size_] += carry;
        }
    }

    return result;
}

std::ostream& operator<<(std::ostream& os, const bigint& number) {
    if (number.negative_ && !(number.size_ == 1 && number.digits_[0] == 0)) {
        os << "-";
    }

    bool leading_zero = true;
    for (int i = 0; i < number.size_; i++) {
        if (leading_zero && number.digits_[i] == 0) {
            continue;
        }
        leading_zero = false;

//        if (i < number.size_ - 1) {
//            os << std::setfill('0') << std::setw(9);  // Каждый блок из 9 цифр
//        }
        os << number.digits_[i];
    }


    return os;
}
