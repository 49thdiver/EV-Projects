/* New leaf charger Canbus Data VCM simulator October 2021
 Revised and optimized post success March 2022
 Version 3.0
 Runs on Arduino Due with a Can Bus Shield
 I have used both EVTV and Togglebit due shields with success, and can recomend them. /I have also used those tiny can bus  boards o uno's with only some issues and even soldered MCP2551 driver chips for the Due with some success.
 I started with arduino UNO's but they are simply too slow to be useful and the CAN libraries are more primitive in my opinion.
 
Timing is everything, you have to use the interrupt timers to make it work.
 You need to look at the LEAF can data base on the Kvaser system maintained if not developed by DALA. A great resource, if   you want to adjust the charge current you can find the bytes to tweak by studying the data. Amongst other things.
 The service manuals are available on a Nissan owners Forum, page 32 and 33 in the VC section of the 2014 are what you need. The diagram that you   will want to familiarize your self with is labled F23. Note H.S. in the corner means harness side to reference the connector numbers   and wire colours according to the diagram.

 You will also need to identify the 12 volt connection , the ground and the J1772   connections.
 The pins you need to connect on F23 are as follows:
	10- J1772 plug in signal
	11- Can Low
	12- HV interlock connect to 15
Note: there are two interlocks in the PDPM, one that connects to the Inverter and one for the lid of the PDPM.
	15- HV interlock connect to 12
	16- Battery +12 volts
	18- Battery +12 volts
	27- Can High
	29- J1772 EVSE connect signal
	30- J1772 EVSE communication ie PWM

 Be careful there are lots of things that can go wrong when playing with high voltage that include hurting yourself or burning   down your house. Fuses, fire extingiushers and buckets of water recommended. Do not try this if this is your first project or you   have no experince with electrconics or high voltage, not to mention programming and control systems.
 
 This implementation based on concepts from Darrell Sveistrup
 Original message data from Issac Kelly, Dala the great and others.
 Thanks to Muxan, and others for technical support
 Otherwise this code written by Peter Luckham known as 49thdiver
 Please do not use commercially without permission and a kickback va7dvr@gmail.com
*/