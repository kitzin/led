#include <Wire.h>

typedef struct led_proto_s {
  byte version;
  byte red;
  byte green;
  byte blue;
} led_proto_t;

typedef struct led_pins_s {
  byte red;
  byte green;
  byte blue;
} led_pins_t;

const int PROTOCOL_SIZE = sizeof(led_proto_t);
byte proto_buf[PROTOCOL_SIZE];
led_pins_t pins[2];

void setup() {
  Wire.begin(5);
  Wire.onReceive(event);
  Serial.begin(9600);
  
  pins[0].red = 3;
  pins[0].green = 5;
  pins[0].blue = 6;
  pins[1].red = 9;
  pins[1].green = 10;
  pins[1].blue = 11;
  
  for(int i = 0; i<2; i++) {
    pinMode(pins[i].red, OUTPUT);
    pinMode(pins[i].green, OUTPUT);
    pinMode(pins[i].blue, OUTPUT);
  }
}

void loop() {
  delay(1000);
}

void change_color(byte w_pins, byte r, byte g, byte b) {
  Serial.println(r);
  Serial.println(g);
  Serial.println(b);
  Serial.println(w_pins);
  analogWrite(pins[w_pins].red, r);
  analogWrite(pins[w_pins].green, g);
  analogWrite(pins[w_pins].blue, b);
}
  
void read_protocol(byte *buf) {
  led_proto_t *led = (led_proto_t*)buf;
  byte w_pins = led->version & 1;
  Serial.println(led->version>>1);
  change_color(w_pins, led->red, led->green, led->blue);
}

void event(int bytes)  {
  int b = 0;
  byte command;
  
  if(Wire.available() > 1)
    command = Wire.read(); // Ignore this
    
  while(Wire.available() > 0) {
    byte by = Wire.read();
    if(b < PROTOCOL_SIZE-1) {
      proto_buf[b] = by;
      ++b;
    } else {
     proto_buf[b] = by;
     read_protocol(proto_buf);
     b = 0;
    }
  }
}

