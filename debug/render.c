// characters osdicons.ttf
// round  triangle   
// satellite    
// cpu  
// bars ▁▂▃▄▅▆▇█
// arrows ↥ ↦ ↤    
// warning              
// down/up stream  
// RSSI     
// cam  
// double caret    
// please wait  
// wind      
// thermometer  
// time   
// pressure  
// speed  
// windhose    
// cog    
#include <stdint.h>
#include <sys/time.h>
#include "render.h"
#include "telemetry.h"
#include "osdconfig.h"

#define TO_FEET 3.28084
#define TO_MPH 0.621371
#define CELL_WARNING_PCT1 (CELL_WARNING1-CELL_MIN)/(CELL_MAX-CELL_MIN)*100
#define CELL_WARNING_PCT2 (CELL_WARNING2-CELL_MIN)/(CELL_MAX-CELL_MIN)*100

float scale_factor_font;
bool setting_home;
bool home_set;
float home_lat;
float home_lon;
int home_counter;
char buffer[40];
float mAhDrawRaw, mAhDrawn;
bool first = true;
long long lastT, timeDiff;

int packetslost_last[6];

int fecs_skipped_last;
int injection_failed_last;
int tx_restart_count_last;

bool no_signal = false;


long long current_ts() {
    struct timeval te;
    gettimeofday(&te, NULL); // get current time
    long long milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000; // calculate milliseconds
    return milliseconds;
}


void render(telemetry_data_t *td) {
    printf("###############################################################\n");

#ifdef DOWNLINK_RSSI
    int i;
    int best_dbm = -255;
    int ac = td->rx_status->wifi_adapter_cnt;

    no_signal = false;
    for (i = 0; i < ac; ++i) { // find out which card has best signal (and if at least one card has a signal)
        if (td->rx_status->adapter[i].current_signal_dbm > best_dbm &&
            td->rx_status->adapter[i].current_signal_dbm != 0)
            best_dbm = td->rx_status->adapter[i].current_signal_dbm;
    }

    draw_total_signal(best_dbm, td->rx_status->received_block_cnt, td->rx_status->damaged_block_cnt,
                      td->rx_status->lost_packet_cnt, td->rx_status->received_packet_cnt,
                      td->rx_status->lost_per_block_cnt, DOWNLINK_RSSI_POS_X, DOWNLINK_RSSI_POS_Y,
                      DOWNLINK_RSSI_SCALE * GLOBAL_SCALE);

#ifdef DOWNLINK_RSSI_DETAILED
    for (i = 0; i < ac; ++i) {
        draw_card_signal(td->rx_status->adapter[i].current_signal_dbm, 1, i, ac,
                         td->rx_status->tx_restart_cnt, td->rx_status->adapter[i].received_packet_cnt,
                         td->rx_status->adapter[i].wrong_crc_cnt, td->rx_status->adapter[i].type,
                         td->rx_status->received_packet_cnt,
                         td->rx_status->lost_packet_cnt, DOWNLINK_RSSI_DETAILED_POS_X, DOWNLINK_RSSI_DETAILED_POS_Y,
                         DOWNLINK_RSSI_DETAILED_SCALE * GLOBAL_SCALE, td->rx_status);
    }
#endif
#endif

}


void draw_card_signal(int8_t signal, int signal_good, int card, int adapter_cnt, int restart_count, int packets,
                      int wrongcrcs, int type, int totalpackets, int totalpacketslost, float pos_x, float pos_y,
                      float scale,
                      db_gnd_status_t *db_gnd_status) {
    printf("CARD_SIGNAL######: %i\n",signal);
    printf("signal: %i\n",signal);
    printf("signal_good: %i\n",signal_good);
    printf("restart_count: %i\n",restart_count);
    printf("packets: %i\n",packets);
    printf("wrongcrcs: %i\n",wrongcrcs);
    printf("totalpackets: %i\n",totalpackets);
    printf("totalpacketslost: %i\n",totalpacketslost);

}


void draw_total_signal(int8_t signal, int goodblocks, int badblocks, int packets_lost, int packets_received,
                       int lost_per_block, float pos_x, float pos_y, float scale) {
    printf("TOTAL_SIGNAL######: %i\n",signal);
    printf("signal: %i\n",signal);
    printf("goodblocks: %i\n",goodblocks);
    printf("badblocks: %i\n",badblocks);
    printf("packets_lost: %i\n",packets_lost);
    printf("packets_received: %i\n",packets_received);
    printf("lost_per_block: %i\n",lost_per_block);
}
