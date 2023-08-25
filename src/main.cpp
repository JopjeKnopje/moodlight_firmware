#include <Arduino.h>

#define PIN_LED_RED 9
#define PIN_LED_GREEN 10
#define PIN_LED_BLUE 5
#define PIN_LED_WHITE 6


bool is_valid_param(String s)
{
    for (size_t i = 0; i < s.length(); i++)
    {
        if (!isdigit(s.charAt(i)))
            return false;
    }
    return true;
}


int parse_serial()
{
    String s = Serial.readString();
    s.trim();
    int val;

    if (is_valid_param(s))
    {
        val = s.toInt();
        if (val > 255)
            val = -1;
    }
    return val;
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
        int pwm_val = parse_serial();
        if (pwm_val == -1)
        {
            Serial.println("Error invalid value try [0-255]");
        }
        else
        {
            Serial.print("Pwm @ ");
            Serial.println(pwm_val);
            analogWrite(PIN_LED_GREEN, pwm_val);
            analogWrite(PIN_LED_RED, pwm_val);
        }
    }
}