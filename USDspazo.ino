/*
  created 25 Aug 2019
  modified 1 Sep 2019
  by Praneeth Polu
*/

#include <Keyboard.h>
#include <Mouse.h>

#define OSX 0
#define WINDOWS 1
#define UBUNTU 2

#define LED_PIN LED_BUILTIN
#define KEY_STOP_PIN 2
#define INTERVAL_DELAY 60000

unsigned long time_millis = 0;
int   ds = 500;
int   cmdKey;
int   platform = WINDOWS;

int mouseRange = 5;              // output range of X or Y movement; affects movement speed
int mouseResponseDelay = 10;     // response delay of the mouse, in ms

void setup() {

  // give us a little time to connect up
  delay(ds * 2);
  // allow controlling LED
  pinMode(LED_PIN, OUTPUT);
  // Button to start
  pinMode(KEY_STOP_PIN, INPUT_PULLUP);

  //startSerial();
  
  //waiting for the drivers to load
  waitForDrivers();

  Keyboard.begin();
  Mouse.begin();

  cmdKey = cmdKeyGet();
  //Serial.print("Start! ");
}

void loop() {

  // loop until the button is not press
  while (digitalRead(KEY_STOP_PIN) == LOW) {
    // do nothing until pin 4 goes low
    delay(ds);
  }
  delay(ds * 2);

  //openApp("terminal");
  //newWindow();

  if(millis() > time_millis + INTERVAL_DELAY){
        time_millis = millis();
        //print_time(time_millis);
        mouseMoveTop();
   }
   
  //mouseMoveRandom();  

  digitalWrite(LED_PIN, HIGH);        // turn the LED on (HIGH is the voltage level)
  delay(ds / 2);                     // wait for a second
  digitalWrite(LED_PIN, LOW);        // turn the LED off by making the voltage LOW
  delay(ds / 2);                     // wait for a second
  
}


void waitForDrivers() {}

void mouseMoveRandom() {

  // move the mouse:
  Mouse.move(8 + mouseRange , 5 + mouseRange , 0);  
  // a delay so the mouse doesn't move too fast:
  delay(mouseResponseDelay);
  
}

void mouseMoveTop() {

  // Move to top left of screen
  for (int i = 0; i < 1000; i++)
  {
    Mouse.move(-10, -10);
    delay(1);
  }

  // If we have hot corners enabled, move out and move back in
  for (int i = 0; i < 100; i++)
  {
    Mouse.move(1, 1);
    delay(5);
  }
  delay(500);

  for (int i = 0; i < 100; i++)
  {
    Mouse.move(-1, -1);
    delay(5);
  }
  delay(500);
  
}

void startSerial(){
   // Open serial communications and wait for port to open:
  //Serial.begin(9600);
  //while (!Serial);  // wait for serial port to connect. Needed for native USB
}

void print_time(unsigned long time_millis){
    Serial.print("Time: ");
    Serial.print(time_millis/1000);
    Serial.print("s - ");
}

int cmdKeyGet()
{

  if (platform == 1 || platform == 2) {
    // use this option for Windows and Linux.
    return KEY_LEFT_CTRL;
  } else {
    // use this option for OSX.
    return KEY_LEFT_GUI;
  }

}

// type a string (pressing enter at the end)
// we have extra delays so we can see what's happening
void typeln(String chars)
{
  Keyboard.print(chars);
  delay(ds);
  Keyboard.println("");
  delay(ds * 4);
}

// open an application
void openApp(String app)
{

  switch (platform) {
    case OSX:
      // open spotlight, then the app
      int keys[] = {cmdKey};
      cmd(32);
      typeln(app);
      break;
    case WINDOWS:
      // Windows Key + R to open Run
      gui('r');
      typeln(app);
      KeyDo(KEY_RETURN);
      break;
    case UBUNTU:

      break;
  }

}

void modifiersKey(int *mod, int arrSize, int key)
{
  for (int i = 0; i < arrSize; i++) {

    if (mod[i] != NULL) {
      Keyboard.press(mod[i]);
    }

  }
  if(platform == 0){delay(ds);}
  if (key != NULL) {
    Keyboard.press(key);
  }
  if(platform != 0){delay(ds);}
  Keyboard.releaseAll();
  delay(ds);

}

void KeyDo(int key)
{
  Keyboard.write(key);
  delay(ds / 2);
}


void cmd(int key)
{
  int keys[] = {cmdKey};
  modifiersKey(keys, 1, key);
}

void shift(int key)
{
  int keys[] = {KEY_LEFT_SHIFT};
  modifiersKey(keys, 1, key);
}

void ctrl(int key)
{
  int keys[] = {KEY_LEFT_CTRL};
  modifiersKey(keys, 1, key);
}

void alt(int key)
{
  int keys[] = {KEY_LEFT_ALT};
  modifiersKey(keys, 1, key);
}

void gui(int key)
{
  int keys[] = {KEY_RIGHT_GUI};
  modifiersKey(keys, 1,  key);
}

void deletePrevious(int number) {
  for (int keystrokes = 0; keystrokes < number; keystrokes++) {
    delay(500);
    Keyboard.write(KEY_BACKSPACE);
  }
}

void deleteAll() {
  // select all
  cmd('a');
  delay(ds);
  // delete the selected text
  KeyDo(KEY_BACKSPACE);
  delay(ds);
}

void newWindow()
{
  // new document:
  cmd('n');
  // wait for new window to open:
  delay(ds * 2);
}

void logOut(int platform = platform)
{
  switch (platform) {
    case OSX:
      // Shift-Q logs out:
      int keys[] = {cmdKey, KEY_LEFT_SHIFT};
      modifiersKey(keys, 2, 'Q');
      delay(100);
      // enter:
      KeyDo(KEY_RETURN);
      break;
    case WINDOWS:
      // CTRL-ALT-DEL:
      int keys2[] = {cmdKey, KEY_LEFT_ALT, KEY_DELETE};
      modifiersKey(keys2, 3, NULL);
      // ALT-l:
      delay(ds * 4);
      alt('l');
      break;
    case UBUNTU:
      // CTRL-ALT-DEL:
      int keys3[] = {cmdKey, KEY_LEFT_ALT, KEY_DELETE};
      modifiersKey(keys3, 3, NULL);
      // Enter to confirm logout:
      KeyDo(KEY_RETURN);
      break;
  }

}
