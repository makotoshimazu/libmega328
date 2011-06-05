/* main.c */
#include "library.h"
#include "api.h"
#include <avr/eeprom.h>
#include <math.h>

#define pushed_on(id) ((old_sw[(id)]==0 && get_sw((id))==1)?1:0)
#define save_sw_condition(id) (old_sw[(id)] = get_sw((id)))



int main(void){

    init();                     /* 初期化 */
    sei();                      /* 割り込み許可 */


    /* 本文 */
    printf("_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n"
           "Semi in 2011 Summer\n"
           "Sample Program\n"
           "by Shimazu Makoto\n"
           "Date: 11-06-02\n"
           "_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n");
    load_accel_horizontal();

    /* メインループ */
    while(1){
        static uint8_t old_sw[8]={0};
        int16_t buf[4]={0};
        uint8_t id;
        uint8_t i;
        
        if(pushed_on(0))
            save_accel_horizontal();
        
        save_sw_condition(0);

        buf[X]=get_accel(X);
        buf[Y]=get_accel(Y);
        buf[Z]=get_accel(Z);

        if(buf[X]<0){
            id=3-(uint8_t)(abs(buf[X])/50);
        }else{
            id=4+(uint8_t)(abs(buf[X])/50);
        }
        for(i=0;i<8;i++){
            if(i==id)
                set_led(i,255);
            else
                set_led(i,0);
        }
        set_color_led(abs((buf[X]*2))%255,abs((buf[Y]*2))%255,abs((buf[Z]*2))%255);
        printf("%4d %4d %4d LED:%d\n",abs((buf[X]*2))%255,abs((buf[Y]*2))%255,abs((buf[Z]*2))%255,id);
        
        
        /* printf("%5d %5d %5d %5d\n", */
        /*        buf[X],buf[Y],buf[Z],buf[3]); */
        
        
        /* set_color_led(buf[X]+0x7F,buf[Y]+0x7F,buf[Z]+0x7F); */
        
        
/* uint8_t buf[3]; */
        /* uint8_t i; */
        /* for(i=0;i<3;i++){ */
        /*     buf[i] = (read_adc(i)>>2 & 0xFF) * 2 - 0x80; */
        /* } */
        /* printf("%04d %04d %04d\n", */
        /*        buf[2], */
        /*        buf[1], */
        /*        buf[0]); */
        /* set_color_led( */
        /*     buf[2], */
        /*     buf[1], */
        /*     buf[0]); */


        
        /* static uint8_t i=0; */
        /* set_led(RED,0,i); */
        /* set_led(RED,1,i*2); */
        /* set_led(RED,2,i*3); */
        /* set_led(RED,3,i*4); */
        /* set_led(COLOR,R,i); */
        /* set_led(COLOR,G,i*2); */
        /* set_led(COLOR,B,i*4); */
        /* set_led(GREEN,0,0xFF-i); */
        /* set_led(GREEN,1,0xFF-i*2); */
        /* set_led(GREEN,2,0xFF-i*3); */
        /* set_led(GREEN,3,0xFF-i*4); */
        /* set_led(COLOR,R,i); */
        /* set_color_led(0,255,255); */
        /* if(i<250) i++; */
        /* else i=0; */
        
        
        delay_ms(10);
    }
    
    
    return 0;
}
