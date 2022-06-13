void debug()
{
  int i,x;
  Serial.println("DEBUG");
  Serial.println("-----");
  Serial.println("RecivedData:");
  Serial.print("targetId: ");
  Serial.print(recivedData.targetId);
  Serial.print(",Command: ");
  Serial.print(recivedData.commandSign);
  Serial.print(",Value: ");
  Serial.println(recivedData.commandValue);
}

void LedStartUp()//test onboard LEDS 
{

digitalWrite(RED_LED,HIGH);
delay(LED_TIMEOUT);
digitalWrite(RED_LED,LOW);

digitalWrite(GREEN_LED,HIGH);
delay(LED_TIMEOUT);
digitalWrite(GREEN_LED,LOW);

digitalWrite(YELLOW_LED,HIGH);
delay(LED_TIMEOUT);
digitalWrite(YELLOW_LED,LOW);

}
void PinMode()
{
  pinMode(RED_LED,OUTPUT);    //RED LED
  pinMode(YELLOW_LED,OUTPUT);  //YELLOW LED 
  pinMode(GREEN_LED,OUTPUT);  //GREEN LED 
}

void UpdateLed()
{
  int i;
  for(i=1;i<4;i++)
    if(recivedData.commandValue==i)
      digitalWrite(flag_pins[i-1],LOW);
    else
      digitalWrite(flag_pins[i-1],HIGH);
}

void RadioSetup()
{
  radio.begin();// Basically turn on communications with the device
  radio.setDataRate(DATA_RATE);
  radio.setChannel(CHANNEL);
  radio.setPALevel(PA);//RF24_PA_MAX is max power
  radio.setRetries(RETRAY_DELAY,RETRAYS);//This will improve reliability
  radio.openWritingPipe(send_pipe);//Set up the two way communications with the named device
  radio.openReadingPipe(1,recv_pipe);
  radio.startListening();// Start listening for data which gives the device a kick
  radio.printDetails(); //print RF24 radio setting   
}  


bool ReciveData() //read feedback data.
{   
    bool recive=false; //assume no data feedback arrived.
    radio.startListening();//Go back to listening and wait for the ack signal.  
    while(radio.available())//Keep looping while no ack has come in
    {
      radio.read(&recivedData, sizeof(recivedData)); //read the new data
      recive=true;  //report that the function recived new data
    }           

return recive;
}


bool SendData()
{
    radio.stopListening();  //We are sending not listening for now
    if(!radio.write(&sentData, sizeof(sentData))) // Send the message_code and check to see if it comes back false
      {
        error =1; //faild to send
        radio.startListening();
        return false;
      }
    radio.startListening();//Go back to listening and wait for the ack signal.
    return true;
}
