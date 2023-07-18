/* SPDX-License-Identifier: BSD-3-Clause
 *
 * Xiaomi FOD Wakeup
 * Tiny service for tap-to-AOD for Xiaomi devices
 * on ROMs that don't support the feature.
 *
 * Copyright (c) 2019 Nanda Oktavera
 * Originally for Samsung devices 2021, John Vincent
 * Xiaomi Extensions 2023, John Vincent
 * Released under the terms of 3-clause BSD License
 *
 */

// #define DEBUG

#ifndef GOODIXTS_WAKEUP_H
#define GOODIXTS_WAKEUP_H

#ifdef __GNUC__
#define likely(x)       __builtin_expect(!!(x), 1)
#define unlikely(x)     __builtin_expect(!!(x), 0)
#else
#define likely(x)       (x)
#define unlikely(x)     (x)
#endif

#define EVDEV   "/dev/input/event5" // goodix_ts input event path
#define BLDEV   "/sys/class/backlight/panel0-backlight/bl_power"
#define KEY_GOTO 162 // when screen is touched while screen is off for singletap
#define DELAY   10000

#ifdef DEBUG
#define dbg printf
#else
#define dbg(fmt,...) do {} while (0)
#endif

#ifdef GOODIXTS_SEND_INPUT
int send_input(char *input, uint16_t type, uint16_t code, uint16_t value);
#endif
int readfint(char *file);

#define APP_VERSION "1.5"
#endif
