//
// Created by Sergei on 11/27/24.
//
#pragma once

#include <iostream>
#include "Data.h"
#include "Serializer.h"

class Deserializer
{
public:
    explicit Deserializer(std::istream& in)
            : in_(in)
    {}
    ~Deserializer() {};

    template <class T>
    Error load(T& object)
    {
        return object.deserialize(*this);
    }

    template <class T, class... ArgsT>
    Error operator()(T&& val, ArgsT&&... args)
    {
        return load(val) == Error::CorruptedArchive ? Error::CorruptedArchive : (*this)(std::forward<ArgsT>(args)...);
    }

    template <class T>
    Error operator()(T&& val)
    {
        return load(val);
    }

    Error load(bool& value)
    {
        std::string text;
        in_ >> text;

        if (text == "true")
            value = true;
        else if (text == "false")
            value = false;
        else
            return Error::CorruptedArchive;

        return Error::NoError;
    }

    Error load(uint64_t& value)
    {
        std::string text;
        in_ >> text;

        if (!isNumeric(text)) {
            return Error::CorruptedArchive;
        }

        std::istringstream iss(text);
        if (!(iss >> value)) {
            return Error::CorruptedArchive;
        }

        return Error::NoError;
    }

private:
    std::istream& in_;

    bool isNumeric(const std::string& str)
    {
        for (char ch : str) {
            if (!std::isdigit(ch)) {
                return false;
            }
        }
        return !str.empty();
    }


};
