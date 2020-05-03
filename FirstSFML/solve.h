//
//  solve.cpp
//  FirstSFML
//
//  Created by Александр on 07.04.2020.
//  Copyright © 2020 Alex. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <cassert>

#define wt(x) std::cout << #x << ": " << x << std::endl;

size_t get_buffer(const char* name_of_input_file, char* *r_buffer) {
    if (name_of_input_file == nullptr)
        throw std::runtime_error("name of file is NULL");

    FILE* input_file = fopen(name_of_input_file, "rb");
    if (input_file == nullptr) {
        *r_buffer = nullptr;
        return 0;
    }

    fseek(input_file, 0, SEEK_END);
    size_t input_file_size = ftell(input_file);
    rewind(input_file);

    char* buffer = (char*)calloc(input_file_size + 2, sizeof(char));
    if (buffer == nullptr)
        throw std::runtime_error("calloc did not allocate memory");

    *r_buffer = buffer;

    size_t buffer_size = fread(buffer, sizeof(char), input_file_size, input_file);
    if (buffer_size != input_file_size)
        throw std::runtime_error("size of file and size of buffer are not equal");

    fclose(input_file);
    return buffer_size;
}

void put_data_in_file(const char* name_of_output_file, char* data, size_t data_size) {
    if (name_of_output_file == nullptr)
        throw std::runtime_error("name of output file is null");
    
    if (data == nullptr)
        throw std::runtime_error("data pointer is null");

    FILE* output_file = fopen(name_of_output_file, "wb");
    size_t code = fwrite(data, sizeof(char), data_size, output_file);
    
    if (code != data_size)
        throw std::runtime_error("Error writing output file");

    fclose(output_file);

    free(data);
}

void solve() {
    
    char* code = nullptr;
    size_t code_size = get_buffer("/Users/alex/Desktop/vzl.com", &code);
    if (code == nullptr)
        throw std::runtime_error("Error opening input file");
    
    wt(code_size);
    
    bool hacked_ = false;
    
    for (int i = 0; i < code_size; i++) {
        printf("%03d: %02x\n", i, (unsigned char)code[i]);
        if (!hacked_ && code[i] == 116) { // 74h, je
            code[i] = (unsigned char)117; // 75h, jne
            std::cout << "Found: " << i << std::endl;
            hacked_ = true;
        }
        if (!hacked_ && code[i] == 117) { // 74h, je
            code[i] = (unsigned char)116; // 74h, jne
            std::cout << "Found: " << i << std::endl;
            hacked_ = true;
        }
    }
        
    put_data_in_file("/Users/alex/Desktop/vzl_hacked.com", code, code_size);
    
}
