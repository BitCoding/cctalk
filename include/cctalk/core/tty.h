/**
 * Copyright (c) 2016 BitCoding
 */

#ifndef CCTALK_TTY_H
#define CCTALK_TTY_H 1


#include <cctalk/core/global.h>

struct cctalk_tty {
    /* Serial line descriptor. */
    int fd;

    /* Read/write timeout in milliseconds. */
    int timeout;
    
};  

struct cctalk_tty* new_cctalk_tty(const char *,int);
/*
* write(2) wrapper that attempts to write the whole buffer.
* Returns either the original count or -1 to signal failure.
* The timeout parameter specifies how long can the function
* block until it is allowed to write next byte.
*/
ssize_t write_cctalk_tty(struct cctalk_tty*, const void *, size_t);

/*
* read(2) wrapper that attempts to fill the whole buffer.
* Returns either the original count or -1 to signal failure.
* The timeout parameter specifies how long can the function
* block until it is allowed to write next byte.
*/
ssize_t read_cctalk_tty(struct cctalk_tty*, void *, size_t );
    

void destroy_cctalk_tty(struct cctalk_tty*);

#endif