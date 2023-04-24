#pragma once

#include <Arduino.h>

namespace settings{

class picked_list{
public:
    picked_list(
        print_data& data,
        uint8_t idx
    ): data(data), idx(idx) {}

    picked_list() = default;
    
    print_data data;
    uint8_t idx;
};

}

