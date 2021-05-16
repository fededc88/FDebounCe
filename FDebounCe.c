
#include "FDebounCe.h"


// Switches Handlers declaration
// NOTE: Are declared one handler per Switch. Users should add new switches by
// editing _Sw enum.
SWn_Handler Sw[SW_TOTAL]; 

//
// function: FDebounCe_app()
// 
// imput: none
// output: none
//
// descriotion: Proccess user's responses to switches acctions.
// 
void FDebounCe_app(void){
    
    char buff[60];

    if (Sw1.StateChange == 1 && Sw1.LastState == PRESSED) {
        Sw1.StateChange = 0;
        sprintf(buff, "Sw1() PUSSHH!! \r\n");
        SendStringPolling(buff);
    }
    if (Sw1.LastState == HOLD && Sw1.StateChange == 1) {
        Sw1.StateChange = 0;
        sprintf(buff, "Sw1() HOLD \r\n");
        SendStringPolling(buff);
    }

    if (Sw2.StateChange == 1 && Sw2.LastState == PRESSED) {
        Sw2.StateChange = 0;
        sprintf(buff, "Sw2() PUSSHH!! \r\n");
        SendStringPolling(buff);
    }

    if (Sw2.LastState == HOLD && Sw2.StateChange == 1) {
        Sw2.StateChange = 0;
        sprintf(buff, "Sw2() HOLD \r\n");
        SendStringPolling(buff);
    }

    if (Sw3.StateChange == 1 && Sw3.LastState == PRESSED) {
        Sw3.StateChange = 0;
        sprintf(buff, "Sw3() PUSSHH!! \r\n");
        SendStringPolling(buff);
    }
    if (Sw3.LastState == HOLD && Sw3.StateChange == 1) {
        Sw3.StateChange = 0;
        sprintf(buff, "Sw3() HOLD \r\n");
        SendStringPolling(buff);
    }

    if (Sw4.StateChange == 1 && Sw4.LastState == PRESSED) {
        Sw4.StateChange = 0;
        sprintf(buff, "Sw4() PUSSHH!! \r\n");
        SendStringPolling(buff);
    }
    if (Sw4.LastState == HOLD && Sw4.StateChange == 1) {
        Sw4.StateChange = 0;
        sprintf(buff, "Sw4() HOLD \r\n");
        SendStringPolling(buff);
    }
    
    
}


uint8_t _Swn(int SelectedSw){
    
    switch (SelectedSw){
        case 1: 
             return PORTAbits.RA2;
             break;
        case 2: 
            return PORTAbits.RA3;
            break;
        case 3: 
            return PORTBbits.RB4;
            break;
        case 4:
            return PORTAbits.RA4;
            break;
        default:
            return 1;
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
void FDebounCe_debouncing(SWn_Handler *pSw){

    uint8_t Sw_photo; // Saves switch state when read

    // Proccess every switch declared
    for(n = 0; n < SW_TOTAL; n++){
	// Get switch state
	Swn_photo = pSw[n]->call();

	if(Sw_photo == pSw[n]->On_State){
	    // Switch n is pressed! 
	    switch(pSw[n]->LastState){
		case IDLE:
		    pSw[n]->LastState = RELEASED;
		case RELEASED
		    if(--pSw[n]->Ticks < 1)
		    {
			pSw[n]->LastState = PRESSED; 
			pSw[n]->StateChange = CHANGED;
			pSw[n]->Ticks = DEBOUNCE_TICKS; 
		    }   
		break;

		case PRESSED:
		if(--pSw[n]->TicksHold < 1)
		{
		    pSw[n]->LastState = HOLD; 
		    pSw[n]->StateChange = CHANGED;
		    pSw[n]->TicksHold = DEBOUNCE_HOLD; 
		}
		pSw[n]->Ticks = DEBOUNCE_TICKS; // In case a bounce happens
		break;

		case HOLD:
		// Do nothing
		pSw[n]->pSwn->Ticks = DEBOUNCE_TICKS; // In case a bounce happens
		break;
	    }	
	}	
	else {
	    // Switch n is released or a bounce was produced!
	    switch(pSw[n]->LastState){
		
		case PRESSED:
		    if(--pSw[n]->Ticks < 1)
		    {
			pSw[n]->LastState = RELEASED;
			pSw[n]->StateChanged = CHANGED;
			pSw[n]->Ticks = DEBOUNCE_TICKS;
		    }
		    pSw[n]->pSwn->TicksHold = DEBOUNCE_HOLD; // In case a bounce happens
		    break;
		    
		case HOLD:
		    if(--pSw[n]->Ticks < 1)
		    {
			pSw[n]->LastState = RELEASED; 
			pSw[n]->StateChange = CHANGED; 
			pSw[n]->Ticks = DEBOUNCE_TICKS; 
		    }
		    break;

		case RELEASED:
		    pSw[n]->Ticks = DEBOUNCE_TICKS;  // In case a bounce happens
		    pSw[n]->LastState = IDLE;
		    break;

		case IDLE:
		    // Do Nothing
		    break;
		    
	    }
	    return;

	}

/*
 * function: FDebounCe_Sw_Init()
 *
 * input: none
 * output: none
 *
 * description: Initialize Sw[n] handlers with default values
 */
void FDebounCe_Sw_Init(vSWn_Handler *pSw){

  uint8_t n; // Switch index
if(*pSw == NULL){
  for(n = 0; n < NUMBER_SWn; n++){
    Sw[n].LastState = IDLE;
    Sw[n].StateChange = NO_CHANGE;
    Sw[n].Ticks = DEBOUNCE_TICKS;
    Sw[n].TicksHold = DEBOUNCE_HOLD;
  }
}
  return;
}
