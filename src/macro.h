/**
 * @file macro.h
 * @brief Helpful macros.
 * @author Thomas Reidemeister <treideme@gmail.com>
 * @copyright 2023 Thomas Reidemeister
 * @license Apache-2.0
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef _macro_h_
#define _macro_h_

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#endif // ARRAY_SIZE

#ifndef CLAMP
#define CLAMP(x, low, high)  (((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))
#endif // CLAMP



#endif // _macro_h_