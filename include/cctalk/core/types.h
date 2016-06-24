/**
 * Copyright (c) 2016 BitCoding
 */

#ifndef CCTALK_TYPES_H
#define CCTALK_TYPES_H 1
typedef union{
  uint8_t data[0];
} ACK;
typedef union{
  uint8_t val[3];
  struct{
    uint32_t value:24;
  } __attribute__((__packed__)); 
} uint24_t;

typedef union{
  uint8_t data[0];
  struct{
    uint8_t country[2];
    uint8_t value[3];
    uint8_t letter;
  } __attribute__((__packed__)); 
  struct{
    uint8_t coinID1;
    uint8_t coinID2;
    uint8_t coinID3;
    uint8_t coinID4;
    uint8_t coinID5;
    uint8_t coinID6;
  } __attribute__((__packed__)); 
} COIN_ID; 

typedef union{
  uint8_t d;
  struct{
    uint8_t v1:1;
    uint8_t v2:1;
    uint8_t v3:1;
    uint8_t v4:1;
    uint8_t v5:1;
    uint8_t v6:1;
    uint8_t v7:1;
    uint8_t v8:1;
  } __attribute__((__packed__)); 
} INHIBIT;

typedef union{
  uint8_t data[0];
  struct{
    uint8_t CoinCode;
    uint8_t ErrorOrRouteCode;
  } __attribute__((__packed__)); 
} DeviceEvent;

typedef union{
  uint8_t data[0];
  struct{
    uint8_t countryCode[2];
    uint8_t value[4];
    uint8_t i;
  } __attribute__((__packed__)); 
} BillType;

typedef union{
  uint8_t data[0];
  struct{
    time_t time;
  } __attribute__((__packed__)); 
} REAL_TIME_CLOCK; // 115 116

typedef union{
  uint8_t data[0];
  struct{
    uint32_t value;
  } __attribute__((__packed__)); 
  struct{
    uint8_t value1;
    uint8_t value2;
    uint8_t value3;
    uint8_t value4;
  } __attribute__((__packed__)); 
} CASHBOX_VALUE; // 117 118
	
typedef union{
  uint8_t data[0];
  struct{
    uint8_t timeout;
    uint8_t bytesignored;
    uint8_t badchecksums;
  } __attribute__((__packed__)); 
} R_METHOD_REQUEST_COMMS_STATUS_VAR; // 2

typedef union{
  uint8_t data[0];
  struct{
    uint8_t release;
    uint8_t major;
    uint8_t minor;
  } __attribute__((__packed__)); 
} R_METHOD_REQUEST_COMMS_REVISION; // 4
typedef union{
  uint8_t data[0];
  struct{
    uint8_t status;
  } __attribute__((__packed__)); 
} R_METHOD_REQUEST_SERVICE_STATUS; // 104
typedef union{
  uint8_t data[0];
  struct{
    uint8_t operating;
    uint8_t level;
    uint8_t fault;
  } __attribute__((__packed__)); 
} R_METHOD_REQUEST_ESCROW_STATUS; // 106

typedef union{
  uint8_t data[0];
  struct{
    COIN_ID coin;
    uint16_t count;
  } __attribute__((__packed__)); 
} R_METHOD_REQUEST_HOPPER_BALANCE; // 119
typedef union{
  uint8_t data[0];
  struct{
    uint8_t hopper;
    uint16_t count;
  } __attribute__((__packed__)); 
} T_METHOD_MODIFY_HOPPER_BALANCE; // 120

typedef union{
  uint8_t data[0];
  struct{
    uint8_t hopper;
    uint8_t count;
  } __attribute__((__packed__)); 
} T_METHOD_PURGE_HOPPER; // 121

typedef union{
  uint8_t data[0];
  struct{
    uint8_t device;
    uint8_t fault;
  } __attribute__((__packed__)); 
} R_METHOD_REQUEST_ERROR_STATUS; // 122

typedef union{
  uint8_t data[0];
  struct{
    uint8_t register1;
    uint8_t register2;
  } __attribute__((__packed__)); 
} R_METHOD_REQUEST_ACTIVITY_REGISTER; // 123

typedef union{
  uint8_t data[0];
  struct{
    uint8_t eventcounter;
    uint32_t paid;
    uint32_t unpaid;
  } __attribute__((__packed__)); 
} R_METHOD_VERIFY_MONEY_OUT; // 124

typedef union{
  uint8_t data[0];
  struct{
    uint32_t value;
  } __attribute__((__packed__)); 
} T_METHOD_PAY_MONEY_OUT; // 125
typedef union{
  uint8_t data[0];
  struct{
    uint32_t value;
  } __attribute__((__packed__)); 
} R_METHOD_REQUEST_MONEY_OUT; // 127

typedef union{
  uint8_t data[0];
  struct{
    uint32_t value;
  } __attribute__((__packed__)); 
} R_METHOD_REQUEST_MONEY_IN; // 128


typedef union{
  uint8_t data[0];
  struct{
    uint32_t cointype;
  } __attribute__((__packed__)); 
} T_METHOD_REQUEST_INDEXED_HOPPER_DISPENSE_COUNT; // 130

typedef union{
  uint8_t data[0];
  struct{
     uint24_t count;
  } __attribute__((__packed__)); 
} R_METHOD_REQUEST_INDEXED_HOPPER_DISPENSE_COUNT; // 130
typedef union{
  uint8_t data[0];
  struct{
    uint16_t fault;
  } __attribute__((__packed__)); 
} R_METHOD_EMERGENCY_STOP_VALUE; // 132

typedef union{
  uint8_t data[0];
  struct{
    INHIBIT mode_control;
  } __attribute__((__packed__)); 
} T_METHOD_BILL_OPERTING_MODE; // 153



typedef union{
  uint8_t data[0];
  struct{
    uint24_t count;
  } __attribute__((__packed__)); 
} R_METHOD_REQUEST_ACCEPT_COUNTER; // 225

typedef union{
  uint8_t data[0];
  struct{
    uint24_t count;
  } __attribute__((__packed__)); 
} R_METHOD_REQUEST_INSERTION_COUNTER; // 226

typedef union{
  uint8_t data[0];
  struct{
    uint8_t master;
  } __attribute__((__packed__)); 
} MASTER_INHIBIT_STATUS; // 227 && 228

typedef union{
  uint8_t data[0];
  struct{
    uint8_t eventcounter;
    DeviceEvent event[5];
  } __attribute__((__packed__)); 
} R_READ_BUFFERED_CREDIT_OR_ERROR_CODES; // 229




typedef union{
  uint8_t data[0];
  struct{
    INHIBIT mask1;
    INHIBIT mask2;
  } __attribute__((__packed__)); 
} INHIBIT_STATUS; // 230 && 231

typedef union{
  uint8_t data[0];
  struct{
    uint8_t unit;
    uint8_t value;
  } __attribute__((__packed__)); 
} POLLING_PRIORITY; // 249
#endif