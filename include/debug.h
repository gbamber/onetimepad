/**
 * Written and Copyright (c) 2024 gbamber
 * Licensed under the EUPL-1.2
 * SPDX-License-Identifier: EUPL-1.2
 * License URL: https://joinup.ec.europa.eu/collection/eupl
 * https://joinup.ec.europa.eu/collection/eupl/eupl-text-eupl-12
 */

#ifndef _DEBUG_H_
#define _DEBUG_H_

#ifdef _DEBUG
#define DEBUG_PRINTF(...) printf(__VA_ARGS__)
#else
#define DEBUG_PRINTF(...) \
    do {                  \
    } while (0)
#define DEBUG_PROGRESS(x) \
    do {                  \
    } while (0)
#endif

#endif  // _DEBUG_H_