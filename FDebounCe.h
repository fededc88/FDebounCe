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

// Number of Debounce Ticks the app count before change Sw[n] state to PRESSED 
#define DEBOUNCE_TICKS 20  // 1 Tick = 1 mS

// Number of Bebounce Tick the app count before change Sw[n] State to HOLD
#define DEBOUNCE_HOLD 1500 // 2,5 S
 
// Define to get the LasState of a Sw[n]
#define _Sw[a] Sw[a].LastState 

// Number of Switches
// User should define the Sw number
typedef enum {
    SW_1 = 0,
    SW_2,
    SW_3,
    SW_4,
    SW_TOTAL
} _Sw

// Sw[n possible estates
typedef enum{
    IDLE = 0,
    RELEASED,
    PRESSED,
    HOLD,
    }_KeyState;

typedef enum{
  NO_CHANGED = 0,
  CHANGED  
}_StateChanged;

//
// Sw[n] handler
//
typedef struct 
{
    _StateChanged StateChange;	// New event flag
    _KeyState LastState;	// Actual Sw[n] state 
    void * call;		// Pointer to the function that return pin value
    uint8_t Ticks;		// Number of Debounce Ticks
    uint16_t TicksHold;		// Number of ticks to HOLD
    uint8_t On_State;		// On value call() return

 } SWn_Handler; 
 
 //Public Functions Declarations
 void Sw_app(void);
 _Bool _Swn(int);
void debouncingSwn(SWnState *,int);
void FDebounCe_Sw_Init(void);
#endif
