// IRcount.cpp
#include "IRcount.h"

int countvalue = 0;
IRcounting::IRcounting(int ircountPin): _ircountPin(ircountPin) {
}


void IRcounting::initialize() {
    pinMode(_ircountPin, INPUT);

    // You can add initialization code here if needed
}

void IRcounting::readSensor() {

    if (digitalRead(_ircountPin) == LOW){
        countvalue++;
        Serial.print("Pills count: ");
        Serial.println(countvalue);
        delay(1500);
    }
    
}

