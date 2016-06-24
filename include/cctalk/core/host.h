/**
 * Copyright (c) 2016 BitCoding
 */

#ifndef CCTALK_HOST_H
#define CCTALK_HOST_H 1

// #define CCTALK_WRITEDEBUG 1
// #define CCTALK_READDEBUG 1

#include <cctalk/core/global.h>
#include <cctalk/core/tty.h>

/*Host*/  
struct cctalk_host {
    /* Serial Interface. */
    struct cctalk_tty* tty;

    /* Host identifier. */
    uint8_t id;

    /* Selected CRC mode to send and to expect. */
    enum cctalk_crc_mode crc_mode;    
}; 


struct cctalk_host* new_cctalk_host(const char *,int,enum cctalk_crc_mode,uint8_t);
/*
* write(2) wrapper that attempts to write the whole buffer.
* Returns either the original count or -1 to signal failure.
* The timeout parameter specifies how long can the function
* block until it is allowed to write next byte.
*/
int write_cctalk_host(struct cctalk_host*, struct cctalk_message*);

/*
* read(2) wrapper that attempts to fill the whole buffer.
* Returns either the original count or -1 to signal failure.
* The timeout parameter specifies how long can the function
* block until it is allowed to write next byte.
*/
struct cctalk_message* read_cctalk_host(struct cctalk_host*);

int read_status_cctalk_host(struct cctalk_host*);

void destroy_cctalk_host(struct cctalk_host*);
#endif