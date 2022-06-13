#define NODE_ID 1    //id of the reciver

#define CE 9    //CE pin connected to NRF24 
#define CSN 10  //CSN pin connected to NRF24 

#define RED_LED A1
#define YELLOW_LED A2
#define GREEN_LED A3

#define LED_TIMEOUT 500 //led startup reset


byte flag_pins[]={RED_LED,YELLOW_LED,GREEN_LED};

uint8_t error= 0; //error id


struct dataStruct  
    {   
    uint8_t targetId =0;             //where is data Finel Target
    char commandSign ='R';             //What type of command / respons is data source
    uint8_t commandValue =0;             //Value of command / respons  
    } sentData,recivedData;                 // This can be accessed in the form:  myData.Xposition  etc.
