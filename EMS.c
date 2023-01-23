#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <math.h>

#define Rh (2.178 * powf(10,-18))
#define R (1.097 * powf(10,-2))

int get_input(int *final, int *initial);
float Rydberg_Equation(int final, int inital);
float find_wavelength(float E);
const char *Absorbed_Emitted(float E);

const char *Absorbed_Emitted(float E){
    if(E > 0){
        return "Absorbed";
    }
    else if (E < 0){
        return "Emitted";
    }else{
        return "N/A";
    }
    return "ERROR";
}

float find_wavelength(float E){
    E /= Rh;
    return (1 / fabs(E * R));
}

float Rydberg_Equation(int nfinal, int ninitial){
    return -Rh * ((powf((1 / (float)nfinal),2)) - ((powf((1 / (float)ninitial),2))));
}

int get_input(int *final, int *initial){
    char run = 'T';
    while(run == 'T'){
        char line[256];
        fgets(line, sizeof(line), stdin);
        int correctform = sscanf(line, " (%d, %d)", initial, final);
        if(correctform == 0 || correctform < 2){
            printf("Please use the format (inital, final):\n");
        }
        else{
            printf("Successfully grabbed inputs: (%d, %d)\n", *initial, *final);
            run = 'F';
            break;
        }
    }
    return 0;
}

int main(void){
    int Final_Level, Initial_Level;
    float Energy;
    float wave_length;
    const char *Event;

    while(1 == 1){
        //Get input for both inital and final levels
        printf("\nWhat are the inital and final energy levels of the electron?\nPlease use the format (inital, final):\n");
        get_input(&Final_Level, &Initial_Level);

        //Calculate final energy and wave length using the Rydberg Formula
        sleep(1);
        Energy = Rydberg_Equation(Final_Level, Initial_Level);
        wave_length = find_wavelength(Energy);

        Event = Absorbed_Emitted(Energy);

        //Results
        printf("\nHere are your final results:\n%.2E J | %.0f nm\nThe energy was %s\n",Energy,wave_length,Event);
    }
    sleep(3);
    return 0;
}