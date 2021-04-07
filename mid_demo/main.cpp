#include "mbed.h"
#include "uLCD_4DGL.h"

uLCD_4DGL uLCD(D1, D0, D2); // serial tx, serial rx, reset pin;
InterruptIn but1(A1);         // up button
InterruptIn but2(A2);         // down button 
InterruptIn but3(A3);         // selection button

char pre_slew_rate;  // 1~4 (1 is the biggest)
char slew_rate; // 
Timer debounce_up; // define debounce timer
Timer debounce_down; // define debounce timer
Timer debounce_sel; // define debounce timer
EventQueue queue;

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

    but1.rise(toggle_up);
    but2.rise(toggle_down);
    but3.rise(toggle_sel);

    while(1) ;

}
