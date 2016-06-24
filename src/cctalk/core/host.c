/**
 * Copyright (c) 2016 BitCoding
 */

#include <cctalk/core/host.h>
#include <cctalk/core/tty.h>
#include <cctalk/core/global.h>

struct cctalk_host* new_cctalk_host(const char * path,int time ,enum cctalk_crc_mode mode ,uint8_t id){
  struct cctalk_host *host;
  host = malloc(sizeof(*host));
  host->tty = new_cctalk_tty(path,time);
  
  if(!host->tty){
    free(host);
    return 0;
  }
  host->id = id;
  host->crc_mode = mode;
  
  
  return host;
}
int write_cctalk_host(struct cctalk_host* host, struct cctalk_message* msg){
    uint8_t checksum;
    uint8_t echobuf[sizeof(*msg) + msg->length + 1];
#ifdef CCTALK_WRITEDEBUG    
    printf("msg %i + length %i + 1 = %i\n",sizeof(*msg),msg->length,sizeof(*msg) + msg->length + 1);
#endif   
    if (CCTALK_CRC_CCITT == host->crc_mode)
	  checksum = crc_16_ccitt(msg);
    else
	  checksum = crc_simple(msg);
    /* Write our message to the wire. */
    
    if (-1 == write_cctalk_tty(host->tty, msg, sizeof(struct cctalk_message)))
	    return -1;
    
    if (msg->length && -1 == write_cctalk_tty(host->tty, msg->data, msg->length))
	    return -1;
    if (-1 == write_cctalk_tty(host->tty, &checksum, 1))
	    return -1;
    
#ifdef CCTALK_WRITEDEBUG
    printf("Write complete\n");
    
    if(msg->length){
      printf("%s: %i %i %i %i %i\n",
		"s", msg->destination,
		msg->length ,msg->source,
		msg->header,checksum);
      int i = 0;
      for (i = 0; i < msg->length; i++)
	    printf(" %i", msg->data[i]);
      printf("\n");
    }else
      printf("%s: %i %i %i %i %i\n",
		"s", msg->destination,
		msg->length ,msg->source,
		msg->header,checksum);
      
#endif    
    /* Read our own message from the wire. */
    if (-1 == read_cctalk_tty(host->tty, echobuf, sizeof(echobuf)))
       return -1;
#ifdef CCTALK_WRITEDEBUG    
    printf("Read complete\n");
#endif    
    if (echobuf[sizeof(echobuf) - 1] != checksum)
	    return -1;
#ifdef CCTALK_WRITEDEBUG    
    printf("msg ==  echobufc\n");
#endif    
    return 0;
}
struct cctalk_message* read_cctalk_host(struct cctalk_host* host){
  struct cctalk_message *msg = 0;
  struct cctalk_message header;
  uint8_t data[256] = {0};
  uint8_t checksum, our_checksum;

  if (-1 == read_cctalk_tty(host->tty, &header, sizeof(header)))
	  return NULL;
  
  if (-1 == read_cctalk_tty(host->tty, data, header.length))
	  return NULL;

  if (-1 == read_cctalk_tty(host->tty, &checksum, 1))
	  return NULL;

  msg =malloc(sizeof(header) + header.length + 1);
  memcpy(msg, &header, sizeof(header));
  memcpy(msg->data, data, header.length + 1);
  
  
  #ifdef CCTALK_READDEBUG
    printf("READ complete\n");
    
    if(msg->length){
      printf("%s: %i %i %i %i %i\n",
		"s", msg->destination,
		msg->length ,msg->source,
		msg->header,checksum);
      int i = 0;
      for (i = 0; i < msg->length; i++)
	    printf(" %i", msg->data[i]);
      printf("\n");
    }
    else
      printf("%s: %i %i %i %i %i\n",
		"s", msg->destination,
		msg->length ,msg->source,
		msg->header,checksum);
#endif    
  
  if (CCTALK_CRC_CCITT == host->crc_mode)
	  our_checksum = crc_16_ccitt(msg);
  else
	  our_checksum = crc_simple(msg);
#ifdef CCTALK_READDEBUG
    printf("READ CHECKSUM \n");
#endif        
  if (checksum != our_checksum){
    printf("hmm %i == %i \n",checksum,our_checksum);
    return NULL; 
  }
	  
#ifdef CCTALK_READDEBUG
    printf("CHECKSUM %i == %i \n",checksum,our_checksum);
#endif    
  

  return msg;
}
int read_status_cctalk_host(struct cctalk_host* host)
{
	struct cctalk_message *reply;

	if (NULL == (reply = read_cctalk_host(host)))
		return -1;

	int status = reply->header;

	free(reply);
	return status;
}

void destroy_cctalk_host(struct cctalk_host* host)
{
	if (NULL == host)
		return;
	destroy_cctalk_tty(host->tty);
	free(host);
}

