#include <Arduino.h>

enum PINOUT {
    PIN_LED_RED,
    PIN_LED_GREEN,
    PIN_LED_BLUE,
    PIN_LED_WHITE,
    PIN_COUNT,
};

const static int PINOUT[PIN_COUNT] = {
    [PIN_LED_RED] = 9,
    [PIN_LED_GREEN] = 10,
    [PIN_LED_BLUE] = 5,
    [PIN_LED_WHITE] = 6,
};

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t w;
} ColorRBGW;



bool is_valid_param(String s)
{
    for (size_t i = 0; i < s.length(); i++)
    {
        if (!isdigit(s.charAt(i)))
            return false;
    }
    return true;
}

int parse_serial(ColorRBGW *c)
{
    uint8_t *base = &(*c).r;
    const static int PARAM_COUNT = 4;
    String s = Serial.readString();

    for (size_t i = 0; i < PARAM_COUNT; i++)
    {
        base[i] = s.substring(0, s.indexOf(',', 1)).toInt();
        
    }
    return 1;
}

// data.remove(data.indexOf(','));
// Serial.println("X: " + data);
// return data.toInt();

void set_pwm(ColorRBGW c)
{
    uint8_t *base = &c.r;
    for (int pin : PINOUT)
    {
        uint8_t color = (uint8_t) base[pin];
        analogWrite(pin, color);
    }
}

void print_color(ColorRBGW *c)
{
    Serial

}

void setup()
{
    Serial.begin(9600);
    Serial.setTimeout(250);
}

void loop()
{
    if (Serial.available())
    {
        ColorRBGW c;
        int pwm_val = parse_serial(&c);
        if (pwm_val == -1)
        {
            Serial.println("Error invalid value try [0-255]");
        }
        else
        {
            // set_pwm(c);
            Serial.print("pwm val: ");
            Serial.println(pwm_val);
        }
    }
}