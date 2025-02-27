//
// Created by Sergei on 11/27/24.
//
#pragma once

#include <iostream>
#include <string>
#include <sstream>

enum class Error {
    NoError,
    CorruptedArchive
};

class Serializer {
    static constexpr char Separator = ' ';
public:
    explicit Serializer(std::ostream &out) : out_(out) {}

    ~Serializer() {};

    template<class T>
    Error save(T &object) {
        return object.serialize(*this);
    }

    template<class T, class... ArgsT>
    Error operator()(T &&val, ArgsT &&... args) {
        process(val);
        return (*this)(std::forward<ArgsT>(args)...);
    }

    template<class T>
    Error operator()(T &&val) {
        return process(val);
    }

private:
    std::ostream &out_;

    Error process(bool arg)
    {
        out_ << (arg ? "true" : "false") << Separator;
        return Error::NoError;
    }

    Error process(uint64_t arg)
    {
        out_ << arg << Separator;
        return Error::NoError;
    }
};


