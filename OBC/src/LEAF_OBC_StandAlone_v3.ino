// New leaf charger Canbus Data VCM simulator October 2021
// Revised and optimized post success March 2022
// Version 3.0
// This implementation based on concepts from Darrell Sveistrup
// Original message data from Issac Kelly, Dala the great and others.
// Thanks to Muxan, all of the above and others for technical support
// Otherwise this code written by Peter Luckham known as 49thdiver
// Do not share without permission va7dvr@gmail.com
  #include <DueTimer.h> //© 2021 GitHub, Inc.
  #include "variant.h"  //due support
  #include <due_can.h> // Collin Kidder et alb
  #include "definitions.h"

  void setup(){
  // setup 10ms 100MS and 500ms timers  
    Timer3.attachInterrupt(SendChargeStateCan10msMessage);
    Timer3.start(10000); // Calls every 10ms
    Timer4.attachInterrupt(SendChargingSimBattery100msMessage);
    Timer4.start(100000); // Calls every 100ms
    Timer5.attachInterrupt(SendChargingSimBattery500msMessage);
    Timer5.start(500000); // Calls every 500ms
    Timer2.attachInterrupt(StatusLed_On);
    Timer2.start(1000000);// bink led 
    pinMode(buttonPin, INPUT_PULLUP); // output indicators and button inout for diagnostics
    pinMode(RelayLED, OUTPUT);
  // Initialize serial I/O for debug messages
    Serial.begin(115200); delay(100);
  // Initialize CAN0 and CAN1, Set the proper baud rates here
    Can0.begin(CAN_BPS_500K); //Transmit
  //Can1.begin(CAN_BPS_500K); //Monitor, not used in this version
    Can0.watchFor();
   
  // Send first 500ms message to get things started and sync charger
    SendChargingSimBattery500msMessage(); 
  }
  
  void loop(){}  // Nothing here all interupt driven
  // Blink status LED
  void StatusLed_On(){
          digitalWrite(RelayLED, LOW); //Inititalize relay to BMS ON
  }
  
  // Send 11A message every 10ms
  void VCM_11a_Charging_Message(){
    bool sendState = false;
    switch(counter_11a){
      case 0:
        sendState = SendCanMessage(0x11a,0, 8, message11A_0);
        break;
      case 1:
        sendState = SendCanMessage(0x11a,0, 8, message11A_1);
        break;
      case 2:
        sendState = SendCanMessage(0x11a,0, 8, message11A_2);
        break;
      case 3:
        sendState = SendCanMessage(0x11a,0, 8, message11A_3);
        break;}
      counter_11a++;
      if (counter_11a >= 4)
       counter_11a = 0;  
    return;
  }
  
  // Send 1F2 message every 10ms
  void VCM_1F2_Charging_Message(){
    bool sendState = false;
    switch(counter_1f2){
      case 0:
        sendState = SendCanMessage(0x1f2,0, 8, message1f2_0);
        break;
      case 1:
        sendState = SendCanMessage(0x1f2,0, 8, message1f2_1);
        break;
      case 2:
        sendState = SendCanMessage(0x1f2,0, 8, message1f2_2);
        break;
      case 3:
        sendState = SendCanMessage(0x1f2,0, 8, message1f2_3);
        break;}
      counter_1f2++;
      if (counter_1f2 >= 4)
       counter_1f2 = 0;  
    return;
  }
  // Send 1d4 message every 10ms
  void VCM_1d4_Charging_Message(){
    bool sendState = false;
    switch(counter_1d4){
      case 0:
        sendState = SendCanMessage(0x1d4,0, 8, message1d4_0);
        break;
      case 1:
        sendState = SendCanMessage(0x1d4,0, 8, message1d4_1);
        break;
      case 2:
        sendState = SendCanMessage(0x1d4,0, 8, message1d4_2);
        break;
      case 3:
        sendState = SendCanMessage(0x1d4,0, 8, message1d4_3);
        break;}
      counter_1d4++;
      if (counter_1d4 >= 4)
       counter_1d4 = 0;  
    return;
  }
  // Send 1dc message every 10ms
  void VCM_1DC_Charging_Message(){
    bool sendState = false;
    switch(counter_1dc){
      case 0:
        sendState = SendCanMessage(0x1dc,0, 8, message1dc_0);
        break;
      case 1:
        sendState = SendCanMessage(0x1dc,0, 8, message1dc_1);
        break;
      case 2:
        sendState = SendCanMessage(0x1dc,0, 8, message1dc_2);
        break;
      case 3:
        sendState = SendCanMessage(0x1dc,0, 8, message1dc_3);
        break;}
      counter_1dc++;
      if (counter_1dc >= 4)
       counter_1dc = 0;  
    return;
  }
  // Send 1db message every 10ms
  void HVB_1DB_Charging_Message(){
    bool sendState = false;
    switch(counter_1db){
      case 0:
        sendState = SendCanMessage(0x1db,0, 8, message1db_0);
        break;
      case 1:
        sendState = SendCanMessage(0x1db,0, 8, message1db_1);
        break;
      case 2:
        sendState = SendCanMessage(0x1db,0, 8, message1db_2);
        break;
      case 3:
        sendState = SendCanMessage(0x1db,0, 8, message1db_3);
        break;}
      counter_1db++;
      if (counter_1db >= 4)
       counter_1db = 0;  
    return;
  }
  // Send 55b message every 100ms
  void HVB_55B_Charging_Message(){
    bool sendState = false;
    switch(counter_55b){
      case 0:
        sendState = SendCanMessage(0x55b,0, 8, message55b_0);
        break;
      case 1:
        sendState = SendCanMessage(0x55b,0, 8, message55b_1);
        break;
      case 2:
        sendState = SendCanMessage(0x55b,0, 8, message55b_2);
        break;
      case 3:
        sendState = SendCanMessage(0x55b,0, 8, message55b_3);
        break;}
      counter_55b++;
      if (counter_55b >= 4)
       counter_55b = 0;  
    return;
  }
  // Send 5bc message every 100ms
  void HVB_5BC_Charging_Message(){
    bool sendState = SendCanMessage(0x5bc,0, 8, message5bc);
    return;
  }
  // Send 50b message every 100ms
  void VCM_50B_Charging_Message(){
    bool sendState = SendCanMessage(0x50b,0, 7, message50b);
    return;
  }
  // Send 59e message every 500ms
  void HVB_59E_Charging_Message(){
    bool sendState =    SendCanMessage(0x59e,0, 8, message59e);
    return;
  }
  
  void SendChargeStateCan10msMessage()
  {
      VCM_11a_Charging_Message();
      VCM_1F2_Charging_Message();
      VCM_1d4_Charging_Message();
      HVB_1DB_Charging_Message();
      VCM_1DC_Charging_Message();    
  }
  
  void SendChargingSimBattery100msMessage()
  {
      HVB_55B_Charging_Message();
      HVB_5BC_Charging_Message();   
      VCM_50B_Charging_Message();
  }
  
  void SendChargingSimBattery500msMessage(){
      HVB_59E_Charging_Message();
      digitalWrite(RelayLED, HIGH); // turn status led off
  }
  
  bool SendCanMessage(unsigned int messageId, unsigned short extendedId, unsigned int payloadLength, byte * messageData)
  { 
    OBCFrame.id = messageId;
    OBCFrame.length = payloadLength;
    OBCFrame.extended = false;
    OBCFrame.rtr=1;
    OBCFrame.priority = 15;
    for( int i=0; i< payloadLength;i++)
    {
      OBCFrame.data.bytes[i] = messageData[i];  
    }
    bool sent = Can0.sendFrame(OBCFrame);
       return sent;
}
