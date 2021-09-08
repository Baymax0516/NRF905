
#include <NRF905.h>
#include <SPI.h>
#include <MsTimer2.h>

#define BUF_LEN          32
#define CONF_LEN         10

unsigned char rx_buf[BUF_LEN]= {0};
unsigned char tx_buf2[BUF_LEN]= "Nice   \r\n";
unsigned char read_config_buf[CONF_LEN];

//setup address
unsigned char rx_address[4]= {0xcc,0xcc,0xcc,0xcc};
byte tx_address[4]= {0xcc,0xcc,0xcc,0xcc};

void putstring(unsigned char *str)//output string
{
    while(*str){
        Serial.write(*str++);
    }
}

void setup()
{
    char i;
    pinMode(10,OUTPUT);
    nrf905=NRF905(10);
    nrf905.init(); 
  
    /***************************************************
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
    
    /***********************************************************
  read register configuration, check register value written */
    nrf905.read_config(read_config_buf);
    
    /** serial communication configurate */
    Serial.begin(9600);
    
    /** test configuration */
    for(i=0; i<CONF_LEN; i++){
        Serial.print(read_config_buf[i],HEX);
        Serial.print(' ');
    }
    MsTimer2::set(200, flash);
   //start counting
    MsTimer2::start(); 
}

void flash()
{
    //send data in flash        
    nrf905.TX(tx_buf2);
    /** transmit data packet with specified TX Address */
    //nrf905.TX(tx_buf, tx_address);
    
    // NOTE: TX_Address and RX_Address must be the same
}

void loop()
{
    //receive data in loop
    /** recieve data packet with default RX address */
    nrf905.RX(rx_buf);
    /** recieve data packet with specified RX address */
    //nrf905.RX(rx_buf, rx_address );
    
    // NOTE: TX_Address and RX_Address must be the same
    
    /** send recieved data to PC through serial port */
    putstring(rx_buf);
}
