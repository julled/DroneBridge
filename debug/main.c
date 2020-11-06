/*
 Copyright (c) 2015, befinitiv
 Copyright (c) 2012, Broadcom Europe Ltd
 modified by Samuel Brucksch https://github.com/SamuelBrucksch/wifibroadcast_osd
 modified by Rodizio
 modified by Wolfgang Christl (seeul8er)

 Uses https://github.com/paeryn/openvg library with enhanced font loading

All rights reserved.
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
* Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.
* Neither the name of the copyright holder nor the
names of its contributors may be used to endorse or promote products
derived from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANrenderY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include <stdio.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <locale.h>
#include <unistd.h>

#include "render.h"
//#include "osdconfig.h"
#include "telemetry.h"
//#ifdef FRSKY
//#include "frsky.h"
//#elif defined(LTM)
//#include "ltm.h"

//#include "osd_mavlink.h"
//#elif defined(SMARTPORT)
//#include "smartport.h"
//#endif

//long long current_timestamp() {
//    struct timeval te;
//    gettimeofday(&te, NULL); // get current time
//    long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // caculate milliseconds
//    return milliseconds;
//}

fd_set set;

struct timeval timeout;

int main(int argc, char *argv[]) {
    fprintf(stderr,"DEBUG started\n=====================================\n\n");

    setpriority(PRIO_PROCESS, 0, 10);

    setlocale(LC_ALL, "en_GB.UTF-8");

    fprintf(stderr,"DEBUG: Initializing sharedmem ...\n");
    telemetry_data_t td;
    telemetry_init(&td);
    fprintf(stderr,"DEBUG: Sharedmem init done\n");

    while(1) {
        render(&td);
        usleep(1000000);
    }
    return 0;
}
