// how to increment timer by exactly 0.01 seconds

//timers are hardware peripherals

//have timer continously running, measure stop state, start state etc

void set_timer( int interval ); // initializes timer to 'interval'
void start_timer(); // starts the timer counting, clears previous timeout flag
void stop_timer(); // stops timer
int check_timer(); // returns 1 if timer is still counting, 0 if timer is done

void wait_for_timer() // loops until timer is finished counting
{
 while( check_timer())
  ;
 // make sure that check_timer() returns 0 if the timer isn't running
 // or make sure that wait_for_timer() is never called unless timer is started
 // otherwise endless loop!
}

// A9 Timer
//load lap value in register
// pick scaling value to decrement every N + 1 clock cycles
// 200 Mhz clock, 100 Hz needed, max scaler is N = 2^8, so N+1 = 257
// so lets make scaler equal to 200, we need to increment timer every 200Mhz/200 = 1Mhz
// remember not to overwrite pre-scaler when changing control bits
// what happens when timer reaches 59:99:99


#define TIMER_A9_BASE 0xFFFEC600
#define HEX0_3 0xFF200020
#define HEX4_7 0xFF200030
#define SW_BASE 0xFF200040
#define PUSH_BTN_BASE 0xFF200050

typedef struct _a9_timer {
    int load;
    int count;
    int control;
    int status;
} a9_timer;

char hex_code[16] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71,0x0};
unsigned int *switch_ptr = (unsigned int *) SW_BASE;
unsigned int *btn_ptr = (unsigned int *) PUSH_BTN_BASE;

void main(){
    volatile a9_timer* const timer_1
        = (a9_timer*)TIMER_A9_BASE;

    bool switch_state; //used for lap vs current time mode
    int button_value; // used to know buttons pressed
    int timer_value; // used to store digital timer value
    int timer_pattern; // used to store hex pattern for timer
    //timer value
    int interval = 500000000; // 5 second interval
    int last_count = interval; // used to measure difference in count
    int current_count; // used to measure difference in count

    //start timer
    timer_1->load = interval;
    start_timer();

    while(true){

        current_count = read_timer();
        if (current_count <)

        //read switch
        switch_value = read_Switches();
        // only keep first four bits
        button_value = read_Buttons();



        if(switch_value){
            //display lap time
        }else{
            //display counting time
        }
        if((button_value & 0b1)){
            // start timer
        }

        if((button_value & 0b10) >> 1){
            // stop timer
        }

        if((button_value & 0b100)>>2){
            // store lap
        }

        if((button_value & 0b1000)>>3){
            //clear the timer
        }

        
    }

}

void display_Timer(int time){
    int hex_code[6];
    int minutes;
    int seconds;
    int hundreds;

    minutes = time/6000;
    seconds = (time%6000)/100;
    hundreds = (time%6000)%100;
    hex_code[5] = minutes/10;
    hex_code[4] = minutes%10;
    hex_code[3] = seconds/10;
    hex_code[2] = seconds%10;
    hex_code[1] = hundreds/10;
    hex_code[0] = hundreds%10;


}

bool read_Switch(){
    // only return first bit
    return (bool)(*switch_ptr & 0x1);
}

int read_Buttons(){
    // only return 4 LSBs
    return (*btn_ptr & 0xF);
}

int read_timer(){
    return timer_1->count;
}

void set_timer(int time){
    timer_1->count = time;
}

void start_timer(){
    //start timer, and set prescaler
    timer_1->control = 3 + (1<<8);
}
