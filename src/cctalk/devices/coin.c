/**
 * Copyright (c) 2016 BitCoding
 */

#include <cctalk/core/host.h>
#include <cctalk/core/tty.h>
#include <cctalk/core/global.h>

#include <cctalk/devices/device.h>
#include <cctalk/devices/coin.h>

struct cctalk_coinacceptor* new_cctalk_coinacceptor(struct cctalk_device *dev){
  struct cctalk_coinacceptor *coin = calloc(1, sizeof(*coin));
  coin->device = dev;
    
  uint8_t d = 1;
  COIN_ID type [16];
  
  for(d=1;d<16;d++){
    write_cctalk_device(coin->device,CCTALK_METHOD_REQUEST_COIN_ID,&d,1);    
    struct cctalk_message* msg = read_cctalk_device(coin->device);
  
    if(!msg)
      continue;
  
    if(atoi((const char*)((COIN_ID*)&msg->data[0])->value) == 0)
      break;
  
    memcpy(type[d-1].data, msg->data, msg->length);
  }
  --d;
  
  coin->coins = calloc(d+1, sizeof(COIN_ID));
  coin->coincount = d;
  
  uint8_t i = 0;
  for(i=0;i<d;i++){
    coin->coins[i] = type[i];
  }
  
  return coin;
}
void destroy_cctalk_coinacceptor(struct cctalk_coinacceptor* coin){
  if (NULL == coin)
	  return;
  free(coin);
};





