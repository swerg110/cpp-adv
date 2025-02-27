#include <iostream>
#include <sstream>
#include <cassert>
#include "Data.h"
#include "Deserializer.h"
#include "Serializer.h"

int main() {
    Data x{1, true,2};

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    Data y { 0, false, 0 };

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    assert(err == Error::NoError);

    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);
}
