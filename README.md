            
            #include <cctalk/cctalk.h> 
            
            
            char *device = NULL;
            
            device = strdup("/dev/ttyUSB0");
            struct cctalk_host *host;
            
            if (NULL == (host = new_cctalk_host(device,200,CCTALK_CRC_SIMPLE,hostid)))
                error(1, errno, "failed to open device %s", device);
            
            struct cctalk_device* device = new_cctalk_device(host,1);
            struct cctalk_coinacceptor* acceptor = new_cctalk_coinacceptor(device);
            
            
            for(uint8_t i = 0; i< acceptor->coincount;i++){
                COIN_ID* coin = &acceptor->coins[i];
                printf(" %c%c %i  %c\n", coin->country[0], coin->country[1],atoi((const char*)&coin->value),coin->letter);   
            }
            
            acceptor->device->master.master = 1;
            acceptor->device->inhibit.mask1.d = 255;
            acceptor->device->inhibit.mask2.d = 255;
            
            cctalk_device_inhibit_status(acceptor->device,
                        &acceptor->device->master,
                        &acceptor->device->inhibit);
            
            
            uint8_t lastevent = 0;
            write_cctalk_device(device,CCTALK_METHOD_READ_BUFFERED_CREDIT_OR_ERROR_CODES,NULL,0);
            struct cctalk_message* nmsg = read_cctalk_device(device);
            
            if(nmsg){
                R_READ_BUFFERED_CREDIT_OR_ERROR_CODES code;
                memcpy(&code, nmsg->data, nmsg->length);
                printf("%i\n",code.eventcounter);
                lastevent=code.eventcounter;
            }