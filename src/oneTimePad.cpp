/*
 * Written and Copyright (c) 2025 gbamber
 * Licensed under the EUPL-1.2
 * SPDX-License-Identifier: EUPL-1.2
 * License URL: https://joinup.ec.europa.eu/collection/eupl
 * https://joinup.ec.europa.eu/collection/eupl/eupl-text-eupl-12
 */

#include <fstream>
#include <iostream>
#include <memory>
#include <utility>

#include "oneTimePad.hpp"

#include "unistd.h"

#if 0
Gbamber::OneTimePad::OneTimePad(int argc, char **argv) {
    int opt;
    while ((opt = getopt(argc, argv, ":i:p:o:v")) != -1) {
        switch (opt) {
            case 'i':
                if (!open(optarg, mIn, std::to_underlying(Flag::flagIn)))
                    return;
                continue;
            case 'p':
                if (!open(optarg, mPad, std::to_underlying(Flag::flagPad)))
                    return;
                continue;
            case 'o':
                if (!open(optarg, mOut, std::to_underlying(Flag::flagOut)))
                    return;
                continue;
            case 'v':
                mVerbose = true;
            case -1:
            case ':':
            case '?':
            default:
                break;
        }
    }
}
#endif  // 0

Gbamber::OneTimePad::~OneTimePad() {
    if (mIn.is_open()) mIn.close();
    if (mPad.is_open()) mPad.close();
    if (mOut.is_open()) mOut.close();
}

/**
 * @brief Open a filestream and set the corresponding flag.
 *
 * @tparam T a typename satisfying the 'IsFileStream' concept, i.e. either
 * std::ifstream or std::ofstream
 * @param filename a std::string containing the filename
 * @param file the stream variable the file shall be opened to
 * @param s the Gbamber::OneTimePad::Flag flag to be used
 * @return file.good() i.e.
 * @return true on success;
 * @return false on error
 */
template <IsFileStream T>
bool Gbamber::OneTimePad::open(const std::string &filename, T &file,
                               const Flag &f) {
    if (std::is_same_v<T, std::fstream>)
        file.open(filename, std::ios::binary | std::ios::in | std::ios::out);
    else if (std::is_same_v<T, std::ofstream>)
        file.open(filename, std::ios::binary | std::ios::out);
    else
        file.open(filename, std::ios::binary);
    file.is_open() ? mState |= std::to_underlying(f)
                   : mState &= ~std::to_underlying(f);
    if (mVerbose) {
        if (file.good())
            std::cerr << "open: " << filename << " opened" << std::endl;
        else
            std::cerr << "open: " << filename << " NOT opened" << std::endl;
    }
    return file.good();
}

unsigned int Gbamber::OneTimePad::state() const { return mState; }

bool Gbamber::OneTimePad::good() const {
    if (mState & mBadFlag) return false;
    if (((mState & mGoodFlag) == mGoodFlag)) return true;
    return false;
}

bool Gbamber::OneTimePad::apply() {
    if (mLocked) {
        if (mVerbose)
            std::cerr << "Cannot encrypt/decrypt: locked." << std::endl;
        return false;
    }
    mLocked = true;

    open(inFileName, mIn, Flag::flagIn);
    open(outFileName, mOut, Flag::flagOut);
    open(padFileName, mPad, Flag::flagPad);

    if (!good()) return false;
    char in, pad, out;
    while (mIn.get(in)) {
        if (!mPad.good()) {
            mState |= std::to_underlying(Flag::padExausted);
            break;  // cannot encrypt/dectrypt if OTP is exausted
        }
        while ((pad = mPad.peek()) == '\0') {
            mPad.get();
            if (!mPad.good()) {
                mState |= std::to_underlying(Flag::padExausted);
                break;  // cannot encrypt/dectrypt if OTP is exausted
            }
        }
        mPad.put('\0');  // overwrite pad data after use
        out = in ^ pad;
        mOut.put(out);
    }
    mOut.flush();
    mLocked = false;
    return this->good();
}

Gbamber::OneTimePad &Gbamber::OneTimePad::setFileName(
    std::string_view fName, Gbamber::OneTimePad::Flag f) {
    if (mLocked) return *this;
    mLocked = true;
    switch (std::to_underlying(f)) {
        case std::to_underlying(Gbamber::OneTimePad::Flag::flagIn):
            inFileName = std::string(fName);
            break;
        case std::to_underlying(Gbamber::OneTimePad::Flag::flagOut):
            outFileName = std::string(fName);
            break;
        case std::to_underlying(Gbamber::OneTimePad::Flag::flagPad):
            padFileName = std::string(fName);
            break;
        default:
            break;
    }
    mLocked = false;
    return *this;
}

void Gbamber::OneTimePad::verbose() { mVerbose = true; }
