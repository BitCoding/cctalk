/**
 * Copyright (c) 2016 BitCoding
 */

#include <cctalk/core/host.h>
#include <cctalk/core/tty.h>
#include <cctalk/core/global.h>

#include <cctalk/devices/device.h>
#include <cctalk/devices/bill.h>

void setBillOpertingMode(struct cctalk_billvalidator* bill,T_METHOD_BILL_OPERTING_MODE mode){	
    write_cctalk_device(bill->device,CCTALK_METHOD_MODIFY_BILL_OPERATING_MODE,&mode,sizeof(mode));
    free(read_cctalk_device(bill->device));
}

struct cctalk_billvalidator* new_cctalk_billvalidator(struct cctalk_device *dev){
  struct cctalk_billvalidator *bill = calloc(1, sizeof(*bill));
  bill->device = dev;
    
  uint8_t d = 1;
  BillType type [16];
  
  for(d=1;d<16;d++){
    write_cctalk_device(bill->device,CCTALK_METHOD_REQUEST_BILL_ID,&d,1);    
    struct cctalk_message* msg = read_cctalk_device(bill->device);
  
    if(!msg)
      continue;
  
    if(msg->data[0] == 0)
      break;
  
    memcpy(type[d-1].data, msg->data, msg->length);
  }
  --d;
  
  bill->bills = calloc(d+1, sizeof(BillType));
  bill->billcount = d;
  
  uint8_t i = 0;
  for(i=0;i<d;i++){
    bill->bills[i] = type[i];
  }
  
  return bill;
  
  
  /*
uint8_t d = 1;
      BillType type [17];
      
      for(d=1;d<16;d++){
      write_cctalk_device(BillValidator,CCTALK_METHOD_REQUEST_BILL_ID,&d,1);
      struct cctalk_message* msg = read_cctalk_device(BillValidator);
      if(!msg)
	continue;
      memcpy(type[d].data, msg->data, msg->length);
      
      printf("%c%c : %i : %c \n",type[d].countryCode[0],type[d].countryCode[1],atoi((const char*)&type[d].value),type[d].i);
	
      }
      CCTALK_METHOD_REQUEST_COUNTRY_SCALING_FACTOR  */
    
  
}

void destroy_cctalk_billvalidator(struct cctalk_billvalidator* bill){
  if (NULL == bill)
	  return;
  free(bill);
};





