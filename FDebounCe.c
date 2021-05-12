
#include "FDebounCe.h"

SWn_Handler Sw[NUMBER_SWn]; 

void Sw_app(void){
    
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


bool _Swn(int SelectedSw){
    
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

void debouncingSwn(SWnState *pSwn, int n){
     
//TODO: Convertir en Debouncing en una máquina de estado con Switch!

if(_Swn(n)== 0){
    if((*pSwn).LastState == RELEASED){
        if(--pSwn->Ticks < 1){
            pSwn->LastState = PRESSED; 
            pSwn->StateChange = 1;
            pSwn->Ticks = DebounceTicks; 
    }   }
    else if ((*pSwn).LastState == PRESSED){
        if(--pSwn->TicksHold < 1){
            pSwn->LastState = HOLD; 
            pSwn->StateChange = 1;
            pSwn->TicksHold = DebounceTicksHold; 
    }   }
}
else if ((*pSwn).LastState == PRESSED || (*pSwn).LastState == HOLD){
    if(--pSwn->Ticks){
        pSwn->LastState = RELEASED; 
        pSwn->StateChange = 1;
        pSwn->Ticks = DebounceTicks;
     }
}
else{
    pSwn->Ticks = DebounceTicks;
    pSwn->TicksHold = DebounceTicksHold;
 
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
void FDebounCe_Sw_Init(void){

  uint8_t n; // Switch index

  for(n = 0; n < NUMBER_SWn; n++){
    Sw[n].LastState = RELEASED;
    Sw[n].StateChange = NO_CHANGE;
    Sw[n].Ticks = DEBOUNCE_TICKS;
    Sw[n].TicksHold = DEBOUNCE_HOLD;
  }
  return;
}
