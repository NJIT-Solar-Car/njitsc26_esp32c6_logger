#include <kbl/kbl.h>

const uint8_t CCP_MONITOR2[8] = {0x37};

const twai_frame_t KBL_CCP_MONITOR2 = {
    .header = {
        .id = 0x6B,
        .ide = false
    },
    .buffer = CCP_MONITOR2,
    .buffer_len = sizeof(CCP_MONITOR2)
};

uint16_t kbl_getRPM(uint8_t data[8]) {
    return data[0] << 8 | data[1];
}

uint16_t kbl_getCurrent(uint8_t data[8]) {
    return data[3];
}