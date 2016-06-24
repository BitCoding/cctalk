/**
 * Copyright (c) 2016 BitCoding
 */

#ifndef CCTALK_BILL_H
#define CCTALK_BILL_H 1

#include <cctalk/core/global.h>
#include <cctalk/core/tty.h>
#include <cctalk/devices/device.h>

struct cctalk_billvalidator {
	/* Host this device can be reached through. */
	struct cctalk_device *device;
	
	BillType *bills;
	uint8_t billcount;
	
};

struct cctalk_billvalidator* new_cctalk_billvalidator(struct cctalk_device *);

void setBillOpertingMode(struct cctalk_billvalidator* ,T_METHOD_BILL_OPERTING_MODE);


void destroy_cctalk_billvalidator(struct cctalk_billvalidator*);



#endif