#ifndef LEDCtrl_Plugins_h
#define LEDCtrl_Plugins_h
#include "Arduino.h"
#include <DS1302.h>
    void ClearRangeEEPROM(int start, int end);
    String GetStringEEPROM(int startAddress, int maxLength);
	void StoreStringEEPROM(char str[], int address);	
    void StoreBoolEEPROM(bool value, int address);
	void ClearEEPROM();
	
	String midString(String str, String start, String finish, bool resetIndex);
	void SendSerialCommand(char cmd[3], int flag, int param);
	void SyncRTC(DS1302 rtc, int secondsOffset);
	void CheckHitbox(int pixel_x,int pixel_y);
	int locStart;
	int locFinish;
#endif