/**
 * Copyright (c) 2016 BitCoding
 */

#include <cctalk/core/host.h>
#include <cctalk/core/tty.h>
#include <cctalk/core/global.h>
#include <cctalk/devices/device.h>


struct cctalk_device* new_cctalk_device(struct cctalk_host* host,uint8_t id){
    struct cctalk_message *msg;
    
    /* Create the basic device description. */
    struct cctalk_device *dev = calloc(1, sizeof(*dev));
    dev->host = host;
    dev->id = id;
    
    if (-1 == write_cctalk_device(dev,4,NULL,0))
      return NULL;
    
    if (NULL == (msg = read_cctalk_device(dev)))
      return NULL;
        
    memcpy(dev->version.data, msg->data, msg->length);
    free(msg);
    
    if (-1 == write_cctalk_device(dev,227,NULL,0))
      return NULL;
    
    if (NULL != (msg = read_cctalk_device(dev)))
      memcpy(dev->master.data, msg->data, msg->length);
    
    free(msg);
    
    if (-1 == write_cctalk_device(dev,230,NULL,0))
      return NULL;
    
    if (NULL != (msg = read_cctalk_device(dev)))
      memcpy(dev->inhibit.data, msg->data, msg->length);
    
    free(msg);
    if (-1 == write_cctalk_device(dev,249,NULL,0))
      return NULL;
    
    if (NULL != (msg = read_cctalk_device(dev))){
      memcpy(dev->polling.data, msg->data, msg->length);
    }
    
    free(msg);
    
    if (-1 == write_cctalk_device(dev,246,NULL,0))
      return NULL;
    
    if (NULL != (msg = read_cctalk_device(dev))){
      dev->ManufactureId = malloc(msg->length);
      memcpy(dev->ManufactureId, msg->data, msg->length);
    }
    
    free(msg);
    
    if (-1 == write_cctalk_device(dev,245,NULL,0))
      return NULL;
    
    if (NULL != (msg = read_cctalk_device(dev))){
      dev->EquipmentCategory = malloc(msg->length);
      memcpy(dev->EquipmentCategory, msg->data, msg->length);
    }
    
    if (-1 == write_cctalk_device(dev,244,NULL,0))
      return NULL;
    
    if (NULL != (msg = read_cctalk_device(dev))){
      dev->ProductCode = malloc(msg->length);
      memcpy(dev->ProductCode, msg->data, msg->length);
    }
    
    if (-1 == write_cctalk_device(dev,241,NULL,0))
      return NULL;
    
    if (NULL != (msg = read_cctalk_device(dev))){
      dev->SoftwareRevision = malloc(msg->length);
      memcpy(dev->SoftwareRevision, msg->data, msg->length);
    }
    
    return dev;
}

int write_cctalk_device_m(struct cctalk_device* dev, struct cctalk_message* msg){
  msg->destination = dev->id;
  msg->source = dev->host->id;
  return write_cctalk_host(dev->host,msg);  
}

/*
* write(2) wrapper that attempts to write the whole buffer.
* Returns either the original count or -1 to signal failure.
* The timeout parameter specifies how long can the function
* block until it is allowed to write next byte.
*/
int write_cctalk_device(struct cctalk_device* dev, uint8_t header,void *data,uint8_t length){
  struct cctalk_message msg;
  msg.header = header;
  if(data){
    msg.length = length;
    memcpy(msg.data, data, msg.length);
  }
  else{
    msg.data[0] = 0;
    msg.length = 0;
  }
  return write_cctalk_device_m(dev,&msg);  
}

void cctalk_device_inhibit_status(struct cctalk_device* dev,MASTER_INHIBIT_STATUS *master,INHIBIT_STATUS *polling){
      if(!dev)
	return;
      if(master){
	write_cctalk_device(dev,CCTALK_METHOD_MODIFY_MASTER_INHIBIT_STATUS,master,sizeof(*master));
	read_cctalk_device(dev);
      }
      if(polling){
	write_cctalk_device(dev,CCTALK_METHOD_MODIFY_INHIBIT_STATUS,polling,sizeof(*polling));
	read_cctalk_device(dev);
      }
}

/*
* read(2) wrapper that attempts to fill the whole buffer.
* Returns either the original count or -1 to signal failure.
* The timeout parameter specifies how long can the function
* block until it is allowed to write next byte.
*/
struct cctalk_message* read_cctalk_device(struct cctalk_device* dev){
  return read_cctalk_host(dev->host);
}

void destroy_cctalk_device(struct cctalk_device* dev)
{
	if (NULL == dev)
		return;
	free(dev);
}

