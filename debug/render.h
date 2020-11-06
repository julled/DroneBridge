#pragma once

//#include "bcm_host.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include "VG/openvg.h"
//#include "VG/vgu.h"
//#include "fontinfo.h"
//#include "shapes.h"
#include <math.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <utime.h>
#include <unistd.h>
#include <getopt.h>
#include <endian.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdbool.h>
//#include <fontinfo.h>
#include <time.h>
#include "telemetry.h"

#define TO_DEG 180.0f / M_PI


void render(telemetry_data_t *td);


void draw_total_signal(int8_t signal, int goodblocks, int badblocks, int packets_lost, int packets_received,
                       int lost_per_block, float pos_x, float pos_y, float scale);

void draw_card_signal(int8_t signal, int signal_good, int card, int adapter_cnt, int restart_count, int packets,
                      int wrongcrcs, int type, int totalpackets, int totalpacketslost, float pos_x, float pos_y,
                      float scale,
                      db_gnd_status_t *db_gnd_status);
