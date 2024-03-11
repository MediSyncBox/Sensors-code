// Weightnotify.h
#ifndef weightnotify_h
#define weightnotify_h

#include <Arduino.h>

class weightnotify { // class define
public:
    weightnotify(int weightPin, int buzzerPin); //constructor including the attributes

    void initialize(); 
    void checkWeight();

private:
    int _weightPin;
    int _buzzerPin;
    unsigned long _timer;


};

#endif
