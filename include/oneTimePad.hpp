/*
 * Written and Copyright (c) 2025 gbamber
 * Licensed under the EUPL-1.2
 * SPDX-License-Identifier: EUPL-1.2
 * License URL: https://joinup.ec.europa.eu/collection/eupl
 * https://joinup.ec.europa.eu/collection/eupl/eupl-text-eupl-12
 */

#pragma once
#ifndef _ONE_TTIME_PAD_HPP
#define _ONE_TTIME_PAD_HPP

template <typename T>
concept IsFileStream =
    std::is_same_v<T, std::ifstream> || std::is_same_v<T, std::ofstream> ||
    std::is_same_v<T, std::fstream>;

namespace Gbamber {
class OneTimePad {
   public:
    enum class Flag : unsigned int;
    // OneTimePad();
    // OneTimePad(int argc, char **argv);
    ~OneTimePad();
    unsigned int state() const;
    /**
     * @brief Returns true if the OneTimePad class has been instatiated w/out
     * error
     *
     * @return true
     * @return false
     */
    bool good() const;
    bool apply();
    OneTimePad &setFileName(std::string_view in,
                            const Gbamber::OneTimePad::Flag f);
    void verbose();

   public:  // classes/enum
    enum class Flag : unsigned int {
        init = 0x00,
        flagIn = 0x01,
        flagPad = 0x02,
        flagOut = 0x04,
        padExausted = 0x08,
    };

   private:  // members
    std::string inFileName{}, outFileName{}, padFileName{};
    std::ifstream mIn;
    std::fstream mPad;
    std::ofstream mOut;
    unsigned int mState = std::to_underlying(OneTimePad::Flag::init);
    bool mVerbose = false;
    bool mLocked = false;
    const unsigned int mGoodFlag = std::to_underlying(Flag::flagIn) |
                                   std::to_underlying(Flag::flagPad) |
                                   std::to_underlying(Flag::flagOut);
    const unsigned int mBadFlag = std::to_underlying(Flag::padExausted);

   private:  // methods
    template <IsFileStream T>
    bool open(const std::string &filename, T &file, const Flag &f);
};
}  // namespace Gbamber
#endif  // _ONE_TTIME_PAD_HPP