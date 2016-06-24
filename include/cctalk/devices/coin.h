/**
 * Copyright (c) 2016 BitCoding
 */

#ifndef CCTALK_COIN_H
#define CCTALK_COIN_H 1

#include <cctalk/core/global.h>
#include <cctalk/core/tty.h>
#include <cctalk/devices/device.h>

struct cctalk_coinacceptor {
	/* Host this device can be reached through. */
	struct cctalk_device *device;
	
	COIN_ID *coins;
	uint8_t coincount;
	
};

struct cctalk_coinacceptor* new_cctalk_coinacceptor(struct cctalk_device *);

//void setBillOpertingMode(struct cctalk_coinacceptor* ,T_METHOD_BILL_OPERTING_MODE);


void destroy_cctalk_coinacceptor(struct cctalk_coinacceptor*);



#endif