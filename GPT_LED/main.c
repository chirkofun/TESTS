#include <ch.h>
#include <hal.h>

#include <gpt1_fl.h>

#include <chprintf.h>

void gpt1_CB(void)
{
    palToggleLine(LINE_LED1);
    palToggleLine(LINE_LED2);
    palToggleLine(LINE_LED3);
}

GPTConfig GPT1cfg = {
    .frequency    = 100000,
    .callback     = gpt1_CB,
    .cr2          = 0,
    .dier         = 0
};

int main(void)
{
    chSysInit();
    halInit();

    GPTDriver *delayDriver    = &GPTD1;

    gptStart( delayDriver, &GPT1cfg );
    gptStartContinuous( delayDriver, 100000 );

}
