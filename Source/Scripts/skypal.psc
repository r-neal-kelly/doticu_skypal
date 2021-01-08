; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname skypal hidden

; Use this to check that the .dll is available
bool function Has_DLL() native global

; These can be used for performance timers.
float function Milliseconds() native global
float function Seconds() native global

float function Performance_Milliseconds(float start_time, float stop_time) global
    float time = stop_time - start_time

    start_time = Milliseconds()
    Milliseconds()
    stop_time = Milliseconds()

    return time - ((stop_time - start_time) / 3 * 2)
endFunction

float function Performance_Seconds(float start_time, float stop_time) global
    float time = stop_time - start_time

    start_time = Seconds()
    Seconds()
    stop_time = Seconds()
    
    return time - ((stop_time - start_time) / 3 * 2)
endFunction
