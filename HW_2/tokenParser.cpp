#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <functional>

class TokenParser {
public:
    TokenParser() = default;

    void setStartCallback(const std::function<void()> &callback) {
        startCallback = callback;
    }

    void setEndCallback(const std::function<void()> &callback) {
        endCallback = callback;
    }

    void setDigitTokenCallback(const std::function<void(const uint64_t)> &callback) {
        digitTokenCallback = callback;
    }

    void setStringTokenCallback(const std::function<void(const std::string &)> &callback) {
        stringTokenCallback = callback;
    }

    void parse(const std::string &input) {
        if (startCallback) startCallback();

        std::istringstream in(input);
        std::string token;
        while (in >> token) {

            if (isNumber(token) && isValidUint64(token)) {
                parseNumber(token);
            } else if(stringTokenCallback){
                stringTokenCallback(token);
            }
        }

        if (endCallback){
            endCallback();
        }
    }

private:
    std::function<void()> startCallback;
    std::function<void()> endCallback;
    std::function<void(uint64_t)> digitTokenCallback;
    std::function<void(std::string)> stringTokenCallback;

    static bool isNumber(const std::string &token) {
        if (token.empty()) {
            return false;
        }

        for (char ch : token) {
            if (!isdigit(ch)) {
                return false;
            }
        }
        return true;
    }


    static bool isValidUint64(const std::string &token) {
        const uint64_t maxUint64 = std::numeric_limits<uint64_t>::max();
        uint64_t number = 0;

        for (char digit : token) {
            if (number > (maxUint64 - (digit - '0')) / 10) {
                return false;
            }
            number = number * 10 + (digit - '0');
        }

        return true;
    }

    void parseNumber(const std::string &token) const {
        uint64_t number = 0;
        for (char digit: token) {
            number = number * 10 + (digit - '0');
        }
        if (digitTokenCallback) {
            digitTokenCallback(number);
        }
    }

};

