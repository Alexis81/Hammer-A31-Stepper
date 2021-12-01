#include <ESP_FlexyStepper.h>

// create the stepper motor object
ESP_FlexyStepper stepper;

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
        Etat = 0;
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

    delay(1000);
    stepper.clearLimitSwitchActive();
    stepper.moveRelativeInSteps(-(STEP_PER_MILLIMETER * UP_AFTER_HOME));
    stepper.setCurrentPositionInMillimeters((float)HAUTEUR_MAX + (OFFSET_MACHINE_FLOAT));
    stepper.setTargetPositionInMillimeters((float)HAUTEUR_MAX + (OFFSET_MACHINE_FLOAT));

    // Si l'inter home est activé
    if(flag_home_on) {
        affiche_alarm_ampoule_home(false);
        flag_home_on = false;
    }
    //Serial.println((float)HAUTEUR_MAX + (OFFSET_MACHINE_FLOAT));
}