//      ***********************************************************************
//      *                            Example  4:                              *
//      * Using a combined (switch at begin and end of track wired in serial) *
//      *            limit switch setup + latching emergency stop switch      *
//      *                                                                     *
//      *               Paul Kerspe               8.6.2020                    *
//      *                                                                     *
//      ***********************************************************************

// This example shows how to use a latching emergency switch (a.k.a. kill switch) in a normaly open configuration with an iterrupt to stop ongoing motion instantly
// as well as the use of two limit switches that are wired in serial to use up only a single IO pin of the ESP.
// all switches are connected to ground with one pin and the other pin connected to the configured IO pin.
// the limit switches are configured in a normaly closed configuration and in serial (output of the first switch connected to the input of the second switch)
//
// NOTE: this example relies on a rather quick processing time of the loop() function. If you are putting too much code in there (and by that increasing the processing time of each loop run) you will delay the trigger of the limit switch.
// if your limit switch is too close to the physical end of your motion track and the stepper is running at high speed, you are running the risk to shoot over the limit switch and into the physical limits of your track.
//
// In order to run the example, change the IO pin numbers to match your configuration (lines 29-32)
// you might also want to change the speed and distance settings according to your setup if needed (lines 35-38)
//
// Documentation for this library can be found at:
//    https://github.com/pkerspe/ESP-FlexyStepper/blob/master/README.md
//

#include <Arduino.h>
#include <stdio.h>
#include <Wire.h>
#include "config.h"
#include "utilitaires.h"
#include "affichage.h"
#include "stepper.h"
#include "clavier.h"
#include "SPIFFS.h"

/**
 * the iterrupt service routine (ISR) for the emergency swtich
 * this gets called on a rising edge on the IO Pin the emergency switch is connected
 * it only sets the emergencySwitchTriggered flag and then returns.
 * The actual emergency stop will than be handled in the loop function
 */
/*
void ICACHE_RAM_ATTR emergencySwitchHandler()
{
  // we do not realy need to debounce here, since we only want to trigger a stop, no matter what.
  // So even triggering mutliple times does not realy matter at the end
  if (digitalRead(EMERGENCY_STOP_PIN) == LOW) // Switch is configured in active low configuration
  {
    // the boolean true in the following command tells the stepper to hold the emergency stop until reaseEmergencyStop() is called explicitly.
    // If ommitted or "false" is given, the function call would only stop the current motion and then instanlty would allow for new motion commands to be accepted
    stepper.emergencyStop(true);
  }
  else
  {
    // release a previously enganed emergency stop when the emergency stop button is released
    stepper.releaseEmergencyStop();
  }
}
*/

void limitSwitchHandler()
{
  limitSwitchState = digitalRead(LIMIT_SWITCH_PIN);
  lastDebounceTime = millis();
}

void setup()
{
  Serial.begin(115200);

  //-- Init du FS interne
  Serial.println(F("Inizializing FS..."));
  if (SPIFFS.begin())
  {
    Serial.println(F("SPIFFS mounted correctly."));
  }
  else
  {
    Serial.println(F("!An error occurred during SPIFFS mounting"));
  }

  // Lectures des paramètres sauvegardés
  readAllParameters();

  //-- Init de l'écran
  tft.init();

  //-- Gestion du backlit lCD
  // Configuration du canal 0 avec la fréquence et la résolution choisie
  ledcSetup(pwmChannel, frequence, resolution);
  // Assigne le canal PWM au pin 23
  ledcAttachPin(TFT_BL, pwmChannel);
  // Créer la tension en sortie choisi
  ledcWrite(pwmChannel, BACKLIGHT);

  //-- Init du touch screen
  touchScreen.begin();

  //-- Rotation de l'écran
  tft.setRotation(1);

  // Affichage logo
  affiche_logo();

  // set the pin for the emegrendy switch and limit switch to input with inernal pullup
  // the emergency switch is connected in a Active Low configuraiton in this example, meaning the switch connects the input to ground when closed
  // pinMode(EMERGENCY_STOP_PIN, INPUT_PULLUP);
  pinMode(LIMIT_SWITCH_PIN, INPUT_PULLUP);

  // attach an interrupt to the IO pin of the ermegency stop switch and specify the handler function
  // attachInterrupt(digitalPinToInterrupt(EMERGENCY_STOP_PIN), emergencySwitchHandler, RISING);

  // attach an interrupt to the IO pin of the limit switch and specify the handler function
  attachInterrupt(digitalPinToInterrupt(LIMIT_SWITCH_PIN), limitSwitchHandler, CHANGE);

  // tell the ESP_flexystepper in which direction to move when homing is required (only works with a homing / limit switch connected)
  stepper.setDirectionToHome(1);

  // connect and configure the stepper motor to its IO pins
  stepper.connectToPins(MOTOR_STEP_PIN, MOTOR_DIRECTION_PIN);

  // set the speed and acceleration rates for the stepper motor
  stepper.setSpeedInStepsPerSecond(SPEED_IN_STEPS_PER_SECOND);
  stepper.setAccelerationInStepsPerSecondPerSecond(ACCELERATION_IN_STEPS_PER_SECOND);
  stepper.setDecelerationInStepsPerSecondPerSecond(DECELERATION_IN_STEPS_PER_SECOND);
  stepper.setStepsPerMillimeter(STEP_PER_MILLIMETER);

  stepper.startAsService(0);

  stepper.goToLimitAndSetAsHome(__null, (((HAUTEUR_MAX + OFFSET_MACHINE_FLOAT) * STEP_PER_MILLIMETER) + 1000));

  afficheMenuPrincipal();
}

void loop()
{
  //-- Fade du LCD
  timer_fade = millis();
  if (timer_fade > time_now_fader + (TIME_FADE * 1000))
  {
    ledcWrite(pwmChannel, 5);
  }
  else
  {
    ledcWrite(pwmChannel, BACKLIGHT);
  }

  //-- Si le switch de home est actif
  if (limitSwitchState == oldConfirmedLimitSwitchState && (millis() - lastDebounceTime) > debounceDelay)
  {
    lastDebounceTime = millis();
    affiche_alarm_ampoule_home(true);
    flag_home_on = true;

    //-- Lors du premier run recherche Home
    if (limitSwitchState == LOW && flag_first_run)
    {
      flag_first_run = false;
      oldConfirmedLimitSwitchState = limitSwitchState;
      stepper.setLimitSwitchActive(stepper.LIMIT_SWITCH_COMBINED_BEGIN_AND_END);

      set_home();
    }

    // Si par hazard la table touche le switch Home, arrête le moteur
    if ((limitSwitchState == LOW && !flag_first_run))
    {
      stepper.emergencyStop();
      affiche_alarm();
    }
  }

  //-- Affiche les pas réels en mm
  affiche_reel(stepper.getCurrentPositionInMillimeters());

  //-- Permet de verifier que nous avons atteind l'objectif
  is_goal();

  // Permet d'afficher le bouton OK
  if (flag_Goal && flag_affiche_ok)
  {
    affiche_button_ok();
    flag_keyboard = true;
    flag_digit1 = true;
    flag_digit2 = false;
    flag_digit3 = false;
    flag_point = false;
    flag_affiche_ok = false;
  }

  // Serial.printf("%05.1f\n", stepper.getCurrentPositionInMillimeters());

  // Permet de rattraper le jeu de la table lors d'une descente
  if (flag_Back && stepper.motionComplete())
  {
    stepper_go_to(consigne);
    flag_Back = false;
  }

  //-- Permet de vérifier si le moteur tourne
  is_move();

  //-- Gestion du clavier
  scan_keyboard();

  // Debounce du clavier
  if ((millis() - lastDebounceTimeKeyboard) > debounceDelayKeyboard)
  {
    flag_keyboard = true;
  }

  // Serial.println(stepper.getCurrentPositionInMillimeters());
  stepper.processMovement();
}