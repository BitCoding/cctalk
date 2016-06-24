/**
 * Copyright (c) 2016 BitCoding
 */

#ifndef CCTALK_DEVICE_H
#define CCTALK_DEVICE_H 1

#include <cctalk/core/global.h>
#include <cctalk/core/tty.h>

struct cctalk_device {
	/* Host this device can be reached through. */
	struct cctalk_host *host;

	/* Address to use when communicating with the device. */
	uint8_t id;
	/* Detected comms version of the device. */
	R_METHOD_REQUEST_COMMS_REVISION version;


	/* Detected device features. */
	uint8_t HAS_MASTER_INHIBIT_STATUS:1;
	uint8_t HAS_INHIBIT_STATUS:1;
	
	MASTER_INHIBIT_STATUS master;
	INHIBIT_STATUS inhibit;
	POLLING_PRIORITY polling;
	
	uint8_t* ManufactureId;
	uint8_t* EquipmentCategory;
	uint8_t* SoftwareRevision;
	uint8_t* ProductCode;
};

struct cctalk_device* new_cctalk_device(struct cctalk_host*,uint8_t);
/*
* write(2) wrapper that attempts to write the whole buffer.
* Returns either the original count or -1 to signal failure.
* The timeout parameter specifies how long can the function
* block until it is allowed to write next byte.
*/
int write_cctalk_device_m(struct cctalk_device*, struct cctalk_message*);

int write_cctalk_device(struct cctalk_device* , uint8_t ,void *,uint8_t);

void cctalk_device_inhibit_status(struct cctalk_device*,MASTER_INHIBIT_STATUS *,INHIBIT_STATUS *);

/*
* read(2) wrapper that attempts to fill the whole buffer.
* Returns either the original count or -1 to signal failure.
* The timeout parameter specifies how long can the function
* block until it is allowed to write next byte.
*/
struct cctalk_message* read_cctalk_device(struct cctalk_device*);
void destroy_cctalk_device(struct cctalk_device*);

#endif