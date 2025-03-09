/**
 * Written and Copyright (c) 2025 gbamber
 * Licensed under the EUPL-1.2
 * SPDX-License-Identifier: EUPL-1.2
 * License URL: https://joinup.ec.europa.eu/collection/eupl
 * https://joinup.ec.europa.eu/collection/eupl/eupl-text-eupl-12
 */

#include <string.h>

#include <fstream>
#include <iostream>
#include <memory>
#include <utility>

#include "oneTimePad.hpp"

bool parseOpt(int argc, char **argv, Gbamber::OneTimePad &otp) {
    int opt;
    while ((opt = getopt(argc, argv, ":i:p:o:v")) != -1) {
        switch (opt) {
            case 'i':
                otp.setFileName(optarg, Gbamber::OneTimePad::Flag::flagIn);
                break;
            case 'p':
                otp.setFileName(optarg, Gbamber::OneTimePad::Flag::flagPad);
                break;
            case 'o':
                otp.setFileName(optarg, Gbamber::OneTimePad::Flag::flagOut);
                break;
            case 'v':
                otp.verbose();
                break;
            case -1:
            case ':':
            case '?':
            default:
                return false;
        }
    }
    return true;
}

int main(int argc, char **argv) {
    Gbamber::OneTimePad otp{};
    parseOpt(argc, argv, otp);
#if 0
        if (!otp.good()) {
        std::cerr << "Error opening file: " << strerror(errno) << std::endl;
        return 1;
    };
#endif

    if (otp.apply()) {
        std::cerr << "Success." << std::endl;
    } else {
        std::cerr << "Error." << std::endl;
    }

    return 0;
}
