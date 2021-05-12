/*
 * File: FDebounCe.h
 *
 * Author: Federico D. Ceccarelli (fededc88@gmail.com)
 *
 * Description: FDebounCe try to be a minimalistic Debounce Switches Library
 *
 * NOTE: FDebounCe is a fork from an old switches debounce project originaly
 * implemented on a Microchip PIC32 uController. Any kinde of submissions are
 * welcome.  
 *
 */

#ifndef __FDEBOUNCE_H__
#define __FDEBOUNCE_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// Number of Switches
// User should define the Sw number
#define NUMBER_SWn 4

// Number of Debounce Ticks the app count before change Sw[n] state to PRESSED 
#define DEBOUNCE_TICKS 20  // 1 Tick = 1 mS

// Number of Bebounce Tick the app count before change Sw[n] State to HOLD
#define DEBOUNCE_HOLD 1500 // 2,5 S
 
// Define to get the LasState of a Sw[n]
#define _Sw[a] Sw[a].LastState 

// Sw[n possible estates
typedef enum{
    IDLE = 0,
    PRESSED,
    HOLD,
    RELEASED
}_KeyState;

typedef enum{
  NO_CHANGED = 0,
  CHANGED  
}_StateChanged;

// Sw[n] handler
// Showld be defined one handler by Sw
typedef struct 
{
    _StateChanged StateChange;
    _KeyState LastState;
    uint8_t Ticks;
    uint16_t TicksHold;

 } SWn_Handler; 
 
 //Public Functions Declarations
 void Sw_app(void);
 _Bool _Swn(int);
void debouncingSwn(SWnState *,int);
void FDebounCe_Sw_Init(void);
#endif
