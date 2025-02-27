#pragma once

#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <cctype>

int argument_count = 0;
std::string *arguments = nullptr;

class FormatException : public std::runtime_error {
public:
    explicit FormatException(const std::string &message) : runtime_error(message) {}
};

void inline convertArguments() {
    throw FormatException("Function called without arguments.");
}

template<typename T>
void inline convertArguments(T &&value) {
    std::stringstream buffer;
    buffer << std::forward<T>(value);
    arguments[argument_count++] = buffer.str();
}

template<typename FirstT, typename ...Args>
void inline convertArguments(FirstT &&first, Args &&...remaining) {
    convertArguments(std::forward<FirstT>(first));
    convertArguments(std::forward<Args>(remaining)...);
}

size_t validate_template(const std::string &template_str, size_t argument_count) {
    size_t position = 0;
    int open_braces = 0;
    size_t argument_index = 0;
    std::vector<bool> argument_used(argument_count, false);

    for (size_t i = 0; i < template_str.size(); ++i) {
        switch (template_str[i]) {
            case '{':
                if (open_braces == 1) {
                    throw FormatException("Nested '{' detected.");
                }
                open_braces = 1;
                argument_index = 0;
                break;

            case '}':
                if (open_braces == 1) {
                    if (argument_index >= argument_count) {
                        throw FormatException("Argument index exceeds the number of arguments provided.");
                    }
                    argument_used[argument_index] = true;
                    open_braces = 0;
                } else {
                    throw FormatException("Unmatched '}' detected.");
                }
                break;

            default:
                if (open_braces == 1) {
                    if (!isdigit(template_str[i])) {
                        throw FormatException("Invalid character '" + std::string(1, template_str[i]) + "' inside {}.");
                    }
                    argument_index = argument_index * 10 + (template_str[i] - '0');
                }
                break;
        }
    }

    if (open_braces == 1) {
        throw FormatException("Unmatched '{' detected.");
    }

    for (size_t i = 0; i < argument_count; ++i) {
        if (!argument_used[i]) {
            throw FormatException("Argument " + std::to_string(i) + " is unused.");
        }
    }

    return position;
}

std::string construct_result_string(const std::string &template_str) {
    std::string result;
    size_t open_braces = 0;
    size_t argument_index = 0;

    for (size_t i = 0; i < template_str.size(); ++i) {
        switch (template_str[i]) {
            case '{':
                if (open_braces == 1) {
                    throw FormatException("Nested '{' detected.");
                }
                open_braces = 1;
                argument_index = 0;
                break;

            case '}':
                if (open_braces == 1) {
                    open_braces = 0;
                    result += arguments[argument_index];
                } else {
                    throw FormatException("Unmatched '}' detected.");
                }
                break;

            default:
                if (open_braces == 1) {
                    if (!isdigit(template_str[i])) {
                        throw FormatException("Invalid character inside '{}'.");
                    }
                    argument_index = argument_index * 10 + (template_str[i] - '0');
                } else {
                    result += template_str[i];
                }
                break;
        }
    }

    if (open_braces == 1) {
        throw FormatException("Unmatched '{' detected.");
    }

    return result;
}

template<typename ...Params>
std::string format(const std::string &template_str, Params &&... params) {
    argument_count = 0;
    std::string result;

    if (arguments == nullptr) {
        arguments = new std::string[500];
    }

    if (sizeof...(params) > 0) {
        convertArguments(std::forward<Params>(params)...);
    }

    if (template_str.find('{') != std::string::npos || template_str.find('}') != std::string::npos) {
        validate_template(template_str, argument_count);
        result = construct_result_string(template_str);
    } else {
        result = template_str;
    }

    delete[] arguments;
    arguments = nullptr;

    return result;
}

