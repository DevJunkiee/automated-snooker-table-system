Hardware Components and Their Functions

--ESP32--
#Acts as the main controller, handling all system logic and decision-making.
#Listens to Firebase in real time and controls peripherals based on payment status.

--Servo Motor--
#Mechanically locks or unlocks the snooker table.
#Activated by the ESP32 once payment is confirmed.

--Buzzer--
#Provides audio feedback for system events.
#Signals wifi/payment detection and table activation.

--Traffic Light Indicator--
#Visually displays the current system state.
#Indicates locked, processing, or active gameplay states.

--Buck Converter--
#Regulates and steps down voltage from the power source.
#Protects components by ensuring stable power delivery.

--Capacitor--
#Smooths voltage fluctuations during sudden load changes.
#Prevents resets and unstable behavior in the ESP32.

--Wifi--
#provides Esp with internet connection

--Power Bank--
#Supplies portable power to the entire system.
#Enables operation without reliance on mains electricity.
