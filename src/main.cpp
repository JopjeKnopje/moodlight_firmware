#include <Arduino.h>

// #define DEBUG

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

void print_string(String name, String s)
{
    Serial.print(name);
    Serial.print(" [");
    Serial.print(s);
    Serial.println("]");
}

int parse_serial(String str, ColorRBGW *c)
{
    uint8_t *base = &(*c).r;
    str.trim();

    const char *s = str.c_str();
    size_t i = 0;
    while (*s && i <= 4)
    {
        while (*s && !isdigit(*s))
            s++;
        int val = atoi(s);
        base[i] = val;
        while (*s && isdigit(*s))
            s++;
        i++;
    }
    

    return 1;
}

void set_pwm(ColorRBGW c)
{
    uint8_t *base = &c.r;
    for (size_t i = 0; i < PIN_COUNT; i++)
    {
        uint8_t color = (uint8_t) base[i];
        analogWrite(PINOUT[i], color);

#ifdef DEBUG
        Serial.print("writing to pin: ");
        Serial.print(PINOUT[i]);
        Serial.print(" with value: ");
        Serial.println(color);
#endif
    }
}

void print_color(ColorRBGW *c)
{
    Serial.print("r: ");
    Serial.println(c->r);
    Serial.print("g: ");
    Serial.println(c->g);
    Serial.print("b: ");
    Serial.println(c->b);
    Serial.print("w: ");
    Serial.println(c->w);
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
        int pwm_val = parse_serial(Serial.readString(), &c);
        if (pwm_val == -1)
        {
#ifdef DEBUG
            Serial.println("Error invalid value try [0-255]");
#endif
        }
        else
        {
#ifdef DEBUG
            print_color(&c);
#endif
            set_pwm(c);
        }

    }
}