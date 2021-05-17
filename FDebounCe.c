
#include "FDebounCe.h"


// Switches Handlers declaration
// NOTE: Are declared one handler per Switch. Users should add new switches by
// editing _Sw enum.
Swn_Handler Sw[SW_TOTAL]; 

//
// function: FDebounCe_app()
// 
// imput: none
// output: none
//
// description: Proccess user's responses to switches acctions.
// 
void FDebounCe_app(Swn_Handler *pSwn)
{

    for(uint8_t n = SW_1; n < SW_TOTAL; n++, pSwn++)
    {
	if(pSwn->StateChange == CHANGED)
	    pSwn->StateChange = NO_CHANGED;
	switch(pSwn->LastState)
	{
	    case PRESSED:
		printf("Sw%d() PUSSHH!! \r\n",n);
		break;
	    case HOLD:
		printf("Sw%d() HOLD \r\n",n);
		break;
	    case RELEASED:
		printf("Sw%d() RELEASED \r\n",n);
		break;

	    default:
		// Do nothing
		break;
	}
    }
    return;
}

/*
 * funtion _Swn()
 *
 * imput: _Sw SelectedSw: Te switch number to be read
 * outbut: uint8_t: the pins selected actual value
 *
 * description: returns the actual value of the SelectedSW.
 *
 * NOTE: Function should be defined by the user. Could be redefined in another
 * location of the code. 
 */

uint8_t __attribute__((weak)) _Swn(_Sw SelectedSw){
    
    switch (SelectedSw){
        case SW_1: 
          //   return PORTAbits.RA2;
             break;
        case SW_2: 
           // return PORTAbits.RA3;
            break;
        case SW_3: 
          //  return PORTBbits.RB4;
            break;
        case SW_4:
           // return PORTAbits.RA4;
            break;
        default:
           // return 1;
            break; 
    }
    return 0;
}

//
// function: FDebounCe_debouncing()
//
// imput: Swn_Handler *pSw: Pointer to Swn Hanldler array 
// output: none
//
// description: Functión reads every switch pin end evolves the corresponding 
// handler state. If evolve also set StateChange event Flag. 
//
// NOTE: This function should be called in the timer handler which will
// function as time base. 
//
void FDebounCe_debouncing(Swn_Handler *pSw){

    uint8_t Swn_photo; // Saves switch state when read
    uint8_t n; // Switch index

    // Proccess every switch declared
    for(n = 0; n < SW_TOTAL; n++, pSw++){
	// Get switch state
	Swn_photo = (uint8_t) pSw->call(n);

	if(Swn_photo == pSw->On_State){
	    // Switch n is pressed! 
	    switch(pSw->LastState){
		case IDLE:
		    pSw->LastState = RELEASED;
		case RELEASED:
		    if(--pSw->Ticks < 1)
		    {
			pSw->LastState = PRESSED; 
			pSw->StateChange = CHANGED;
			pSw->Ticks = DEBOUNCE_TICKS; 
		    }   
		    break;

		case PRESSED:
		    if(--pSw->TicksHold < 1)
		    {
			pSw->LastState = HOLD; 
			pSw->StateChange = CHANGED;
			pSw->TicksHold = DEBOUNCE_HOLD; 
		    }
		    pSw->Ticks = DEBOUNCE_TICKS; // In case a bounce happens
		    break;

		case HOLD:
		    // Do nothing
		    pSw->Ticks = DEBOUNCE_TICKS; // In case a bounce happens
		    break;
	    }	
	}	
	else {
	    // Switch n is released or a bounce was produced!
	    switch(pSw->LastState){

		case PRESSED:
		    if(--pSw->Ticks < 1)
		    {
			pSw->LastState = RELEASED;
			pSw->StateChange = CHANGED;
			pSw->Ticks = DEBOUNCE_TICKS;
		    }
		    pSw->TicksHold = DEBOUNCE_HOLD; // In case a bounce happens
		    break;

		case HOLD:
		    if(--pSw->Ticks < 1)
		    {
			pSw->LastState = RELEASED; 
			pSw->StateChange = CHANGED; 
			pSw->Ticks = DEBOUNCE_TICKS; 
		    }
		    break;

		case RELEASED:
		    pSw->Ticks = DEBOUNCE_TICKS;  // In case a bounce happens
		    pSw->LastState = IDLE;
		    break;

		case IDLE:
		    // Do Nothing
		    break;
	    }

	}
    }

    return;
}

/*
 * function: FDebounce_load_default()
 *
 * imput: pSwn: Swn handler pointer
 * output: uint8_t 1 if passed, 0 if failed
 *
 * description: Loads defaults values to a Swn handler
 * 
 */
static uint8_t FDebounCe_load_default(Swn_Handler *pSwn)
{
    pSwn->LastState = IDLE;
    pSwn->StateChange = NO_CHANGED;
    pSwn->Ticks = DEBOUNCE_TICKS;
    pSwn->TicksHold = DEBOUNCE_HOLD;
    pSwn->call = &_Swn;
}

/*
 * function: FDebounCe_Sw_Init()
 *
 * input: none
 * output: none
 *
 * description: Initialize Sw[n] handlers with default values
 */
void FDebounCe_Sw_Init(Swn_Handler *pSw){

    uint8_t n; // Switch index
    Swn_Handler *pSwn;

    if(pSw == NULL)
    {
	// Function is called with a NULL argument
	pSwn = pSw; // Persist Handler pointer

	for(n = 0; n < SW_TOTAL; n++, pSwn++){
	    FDebounCe_load_default(pSwn);  // Load values by default
	}
    }
    return;

}

//
// End of file.
//
