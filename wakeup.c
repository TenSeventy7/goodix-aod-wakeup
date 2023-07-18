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

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/fb.h>
#include <linux/input.h>
#include "wakeup.h"

static void wakeup_aod()
{
	if (readfint(BLDEV) <= FB_BLANK_NORMAL) { // screen is already on
		usleep(DELAY);
		return;
	}

	dbg(":: Trigger ambient display\n");
	system("am broadcast -a com.android.systemui.doze.pulse --user 0");
}

int main()
{
	int fd, rd;
	struct input_event ev;
	size_t evsize = sizeof(struct input_event);

	dbg("Xiaomi AOD Wakeup %s\n", APP_VERSION);
	dbg("Tiny service for tap-to-AOD on Xiaomi devices\n");
	dbg("Copyright 2019, Nanda Oktavera\n");
	dbg("Originally for Samsung devices 2021, John Vincent\n");
	dbg("Xiaomi Extensions 2023, John Vincent\n");

	if (getuid() != 0) {
		printf("Permission denied, please run as root. exiting\n");
		return 1;
	}

	dbg(":: Reading %s\n", EVDEV);
	fd = open(EVDEV, O_RDONLY | O_NONBLOCK);
	while((rd = read(fd, &ev, evsize))) {
		if (rd == -1) {
			usleep(DELAY);
			continue;
		}

		if (unlikely(ev.value == 1)) {
			switch (ev.code) {
				case KEY_GOTO:
					wakeup_aod();
					break;
				default:
					usleep(DELAY);
					break;
			}
		} else {
			usleep(DELAY);
		}
	}

	dbg(":: Closing %s\n", EVDEV);
	close(fd);
	return 0;
}
