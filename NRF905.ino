#include <MsTimer2.h>
#include <NRF905.h>
#include <SPI.h>

#define BUF_LEN          32
#define CONF_LEN         10
#define NRF905_CSN       10

unsigned char tx_buf[BUF_LEN]= "Hi, Arduino   \r\n";
unsigned char rx_buf2[BUF_LEN]= {0};
unsigned char read_config_buf[CONF_LEN];

//setup address
byte tx_address[4]= {0xcc,0xcc,0xcc,0xcc};
unsigned char rx_address[4]= {0xcc,0xcc,0xcc,0xcc};

void putstring(unsigned char *str)//output string
{
    while(*str){
        Serial.write(*str++);
    }
}

void setup()
{
    unsigned char i;
    
    pinMode(NRF905_CSN,OUTPUT); //to make sure SPI works
    
    nrf905=NRF905(NRF905_CSN);
    
    nrf905.init();
    MsTimer2::set(200, flash);//enter flash function every 200 milliseconds
   //Start counting
    MsTimer2::start(); 

    /**
        default configuration, need to specify frequency
        choose Z-Wave frequency band, support :
        US    908.42Mhz
        EUROPE    868.42MHz
        AFRICA    868.42MHz
        CHINA   868.42MHz
        HK    919.82MHz
        JAPAN   853.42MHz
        AUSTRALIA 921.42MHz
        NEW_ZEALAND 921.42MHz
        BRASIL    921.42MHz
        RUSSIA    896MHz
    */
    nrf905.write_config(EUROPE);
  
  
    nrf905.read_config(read_config_buf);

    Serial.begin(9600);

    for(i=0; i<10; i++)
    {
        Serial.print(read_config_buf[i],HEX);
        Serial.print(' ');
    }
    
    tx_buf[12] = '0';
}

void flash()
{         
    //send data in flash      
            
    nrf905.TX(tx_buf);
    tx_buf[12]++;
    if(tx_buf[12] == 0x3A)
    {
      tx_buf[12] = '0';
    }
}

void loop()
{
    //Receive data in loop
 
    nrf905.RX(rx_buf2);
    putstring(rx_buf2);
    
}
