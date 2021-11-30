#include <ESP_FlexyStepper.h>

// create the stepper motor object
ESP_FlexyStepper stepper;

int previousDirection = 1;


bool buttonStateChangeDetected = false;



//----------------------------------------------------------------------------------
// Permet d'aller à une position données en mmm vers le haut
//----------------------------------------------------------------------------------
void stepper_go_to(float mm) {

    stepper.setTargetPositionInMillimeters(mm);
}


//----------------------------------------------------------------------------------
// Permet de savoir que nous avons atteind la cible
//----------------------------------------------------------------------------------
void is_goal() {
    // 0 = Pas atteinte
    // 1 = Atteinte
    if(stepper.getCurrentPositionInMillimeters() == consigne) {
        flag_Goal = true;
        etat = 0;
    }else{
        flag_Goal = false;
    }
}


//----------------------------------------------------------------------------------
// Permet de savoir si le moteur tourne
//----------------------------------------------------------------------------------
void is_move() {
    // 1 ou - 1 = se deplace
    // 0 =  arrêt
    if(stepper.getDirectionOfMotion()) {
        flag_move = true;
    }else {
        flag_move = false;
    }
}


//----------------------------------------------------------------------------------
// Permet de mettre à zéro le compteur soit Home
//----------------------------------------------------------------------------------
void set_home() {
    stepper.setTargetPositionInMillimeters((float)HAUTEUR_MAX);
    stepper.setCurrentPositionInMillimeters((float)HAUTEUR_MAX);
}