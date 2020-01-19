/**************************************************************
   USBspazo is a library for the Arduino platform
   inspired by:
   http://
   Built by Polupraneeth https://github.com/polupraneeth
   Licensed under MIT license
 **************************************************************/

#ifndef USDspazo_h
#define USDspazo_h

// extern "C" {
//   #include "user_interface.h"
// }

class USDspazo
{
  public:
    USDspazo(int pin);
    void dot();
    void dash();
  private:
    int _pin;
};

#endif
