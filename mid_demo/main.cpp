#include "mbed.h"
#include "uLCD_4DGL.h"

using namespace std::chrono;

uLCD_4DGL uLCD(D1, D0, D2); // serial tx, serial rx, reset pin;
InterruptIn but1(A1);         // up button
InterruptIn but2(A2);         // down button 
InterruptIn but3(A3);         // selection button
AnalogOut Aout(PA_4);       // set the analog output

char pre_slew_rate = 1;  // 1~4 (1 is the biggest)
char slew_rate = 1; 
float amp = 1.0f;
Timer debounce_up; // define debounce timer
Timer debounce_down; // define debounce timer
Timer debounce_sel; // define debounce timer
EventQueue queue;
EventQueue wavequeue;


void print_on_uLCD_up(void) { // print the pre_freq on the uLCD
    if (pre_slew_rate == 1) {
        uLCD.cls();
        uLCD.color(WHITE);
	    uLCD.locate(0, 0);
	    uLCD.printf("pre_slew_rate = 1\n");
    }
    else if (pre_slew_rate == 2) {
        uLCD.cls();
        pre_slew_rate = 1;
        uLCD.color(WHITE);
	    uLCD.locate(0, 0);
	    uLCD.printf("pre_slew_rate = 1\n");
    }
    else if (pre_slew_rate == 3) {
        pre_slew_rate = 2;
        uLCD.color(WHITE);
	    uLCD.locate(0, 0);
	    uLCD.printf("pre_slew_rate = 1/2\n");
    }
    else if (pre_slew_rate == 4) {
        pre_slew_rate = 3;
        uLCD.color(WHITE);
	    uLCD.locate(0, 0);
	    uLCD.printf("pre_slew_rate = 1/4\n");
    }
	
	return;
}

void print_on_uLCD_down(void) { // print the pre_freq on the uLCD
    if (pre_slew_rate == 1) {
        pre_slew_rate = 2;
        uLCD.color(WHITE);
	    uLCD.locate(0, 0);
	    uLCD.printf("pre_slew_rate = 1/2\n");
    }
    else if (pre_slew_rate == 2) {
        pre_slew_rate = 3;
        uLCD.color(WHITE);
	    uLCD.locate(0, 0);
	    uLCD.printf("pre_slew_rate = 1/4\n");
    }
    else if (pre_slew_rate == 3) {
        pre_slew_rate = 4;
        uLCD.color(WHITE);
	    uLCD.locate(0, 0);
	    uLCD.printf("pre_slew_rate = 1/8\n");
    }
    else if (pre_slew_rate == 4) {
        pre_slew_rate = 4;
        uLCD.color(WHITE);
	    uLCD.locate(0, 0);
	    uLCD.printf("pre_slew_rate = 1/8\n");
    }
	
	return;
}

void gen_wave(void) {
    float change;
    if (slew_rate == 1) {
        change = 1.0/39/1.1;
    }
    else if (slew_rate == 2) {
        change = 1.0/19/1.1;
    }
    else if (slew_rate == 3) {
        change = 1.0/9/1.1;
    }
    else if (slew_rate == 4) {
        change = 1.0/4/1.1;
    }

    while (1) {
        amp = 0.0f;
        while (amp < 0.91) {
            Aout = amp;
            ThisThread::sleep_for(2ms);
            amp += change;
        }
        if (slew_rate == 1) ThisThread::sleep_for(80ms);
        else if (slew_rate == 2) ThisThread::sleep_for(160ms);
        else if (slew_rate == 3) ThisThread::sleep_for(200ms);
        else if (slew_rate == 4) ThisThread::sleep_for(220ms);
        amp = 1.0/1.1;
        while (amp > 0.0) {
            Aout = amp;
            ThisThread::sleep_for(2ms);
            amp -= change;
        }

    }
}

void print_on_uLCD_sel(void) { // print the pre_freq on the uLCD
    if (pre_slew_rate == 1) {
        slew_rate = 1;
        uLCD.color(RED);
	    uLCD.locate(0, 3);
	    uLCD.printf("slew_rate = 1\n");
    }
    else if (pre_slew_rate == 2) {
        slew_rate = 2;
        uLCD.color(RED);
	    uLCD.locate(0, 3);
	    uLCD.printf("slew_rate = 1/2\n");
    }
    else if (pre_slew_rate == 3) {
        slew_rate = 3;
        uLCD.color(RED);
	    uLCD.locate(0, 3);
	    uLCD.printf("slew_rate = 1/4\n");
    }
    else if (pre_slew_rate == 4) {
        slew_rate = 4;
        uLCD.color(RED);
	    uLCD.locate(0, 3);
	    uLCD.printf("slew_rate = 1/8\n");
    }

    wavequeue.call(gen_wave);
	
	return;
}

void toggle_up()
{
   if (duration_cast<milliseconds>(debounce_up.elapsed_time()).count() > 1000)
   {
      //only allow toggle if debounce timer has passed 1s
      queue.call(print_on_uLCD_up);
      debounce_up.reset(); //restart timer when the toggle is performed
   }
}

void toggle_down()
{
   if (duration_cast<milliseconds>(debounce_down.elapsed_time()).count() > 1000)
   {
      //only allow toggle if debounce timer has passed 1s
      queue.call(print_on_uLCD_down);
      debounce_down.reset(); //restart timer when the toggle is performed
   }
}

void toggle_sel()
{
   if (duration_cast<milliseconds>(debounce_sel.elapsed_time()).count() > 1000)
   {
      //only allow toggle if debounce timer has passed 1s
      queue.call(print_on_uLCD_sel);
      debounce_sel.reset(); //restart timer when the toggle is performed
   }
}


int main(void)
{
    debounce_up.start();
    debounce_down.start();
    debounce_sel.start();
    Aout = 1.0f;

    but1.rise(toggle_up);
    but2.rise(toggle_down);
    but3.rise(toggle_sel);
    Thread t(osPriorityNormal);
    t.start(callback(&queue, &EventQueue::dispatch_forever));

    Thread waveThread(osPriorityNormal);
    waveThread.start(callback(&wavequeue, &EventQueue::dispatch_forever));

    while(1) ;

}
