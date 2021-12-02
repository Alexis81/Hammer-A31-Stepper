#include "menuParametres.h"
// FT62XXTouchScreen touchScreen = FT62XXTouchScreen(DISPLAY_HEIGHT, PIN_SDA, PIN_SCL);

void scan_keyboard()
{

    TouchPoint touchPos = touchScreen.read();

    if (flag_keyboard && Menu == 0)
    {

        if (touchPos.touched)
        {

            time_now_fader = millis();

            int x = touchPos.xPos;
            int y = touchPos.yPos;

            // Touche menu
            if ((x >= 285) && (x <= 478) && (y >= 2) && (y <= 35))
            {
                flag_keyboard = false;
                Menu = 1;
                parametres();
            }

            // Touche Dégo
            if ((x >= 282) && (x <= 387) && (y >= 174) && (y <= 244))
            {
                flag_keyboard = false;
                Menu = 0;
                affiche_voyant_dego(true);
                stepper_go_to_degau();
            }

            // Touche Del
            if ((x >= 0) && (x <= 89) && (y >= 241) && (y <= 319))
            {
                flag_keyboard = true;
                flag_digit1 = true;
                flag_digit2 = false;
                flag_digit3 = false;
                flag_point = false;
                consigne = 0.0;
                stepper.emergencyStop();
                affiche_consigne(consigne);
                affiche_button_ok();
                affiche_voyant_home(false);
                Etat = 0;
            }

            // Touche 0
            if ((x >= 93) && (x <= 181) && (y >= 241) && (y <= 319))
            {
                keyboard = 0;
                flag_keyboard = false;
            }

            // Touche .
            if ((x >= 184) && (x <= 275) && (y >= 241) && (y <= 319))
            {
                flag_point = true;
                flag_keyboard = true;
            }

            // Touche 1
            if ((x >= 0) && (x <= 89) && (y >= 162) && (y <= 237))
            {
                keyboard = 1;
                flag_keyboard = false;
            }

            // Touche 2
            if ((x >= 93) && (x <= 181) && (y >= 162) && (y <= 237))
            {
                keyboard = 2;
                flag_keyboard = false;
            }

            // Touche 3
            if ((x >= 184) && (x <= 275) && (y >= 162) && (y <= 237))
            {
                keyboard = 3;
                flag_keyboard = false;
            }

            // Touche 4
            if ((x >= 0) && (x <= 89) && (y >= 81) && (y <= 157))
            {
                keyboard = 4;
                flag_keyboard = false;
            }

            // Touche 5
            if ((x >= 93) && (x <= 181) && (y >= 81) && (y <= 157))
            {
                keyboard = 5;
                flag_keyboard = false;
            }

            // Touche 6
            if ((x >= 184) && (x <= 275) && (y >= 81) && (y <= 157))
            {
                keyboard = 6;
                flag_keyboard = false;
            }

            // Touche 7
            if ((x >= 0) && (x <= 89) && (y >= 2) && (y <= 78))
            {
                keyboard = 7;
                flag_keyboard = false;
            }

            // Touche 8
            if ((x >= 93) && (x <= 181) && (y >= 2) && (y <= 78))
            {
                keyboard = 8;
                flag_keyboard = false;
            }

            // Touche 9
            if ((x >= 184) && (x <= 275) && (y >= 2) && (y <= 78))
            {
                keyboard = 9;
                flag_keyboard = false;
            }

            //-- Touche déplacement incrémental
            // Touche Up
            if ((x >= 440) && (x <= 478) && (y >= 162) && (y <= 279))
            {
                float Increment = stepper.getCurrentPositionInMillimeters() + INCREMENT;
                if (Increment <= (float)HAUTEUR_MAX + OFFSET_MACHINE_FLOAT)
                {
                    stepper_go_to(Increment);
                }
                flag_keyboard = false;
            }

            // Touche Down
            if ((x >= 440) && (x <= 478) && (y >= 38) && (y <= 157))
            {
                float Increment = stepper.getCurrentPositionInMillimeters() - INCREMENT;
                if (Increment >= (float)HAUTEUR_MINI)
                {
                    stepper_go_to(Increment);
                }
                flag_keyboard = false;
            }

            //-- Bouton OK ou arrêt d'urgence
            if ((x >= 285) && (x <= 440) && (y >= 250) && (y <= 316))
            {
                flag_keyboard = false;
                flag_digit1 = false;
                flag_digit2 = false;
                flag_digit3 = false;
                flag_point = false;

                // Etat :
                //        0 - Moteur en mouvement
                //        1 - Arrêt urgence
                //        2 - Reprise arrêt urgence

                switch (Etat)
                {
                // Bouton OK
                case 0:
                    affiche_button_stop();
                    flag_affiche_ok = true;
                    flag_permit_run = true;
                    Etat = 1;
                    if (consigne < (float)HAUTEUR_MINI)
                    {
                        consigne = (float)HAUTEUR_MINI;
                    }

                    if (stepper.getCurrentPositionInMillimeters() < consigne)
                    {
                        stepper_go_to(consigne + (float)RATTRAPE_JEU);
                        flag_Back = true;
                    }
                    else
                    {
                        stepper_go_to(consigne);
                        flag_Back = false;
                    }
                    break;

                case 1:
                    affiche_button_ok_urgence();
                    stepper.emergencyStop(true);
                    flag_permit_run = false;
                    Etat = 2;
                    break;

                case 2:
                    flag_permit_run = true;
                    affiche_button_stop();
                    stepper.releaseEmergencyStop();
                    stepper_go_to(consigne);
                    Etat = 1;
                    break;

                default:
                    break;
                }
            }

            //-- Création de la consigne
            if (!flag_keyboard)
            {
                if (flag_point)
                {
                    flag_digit1 = false;
                    flag_digit2 = false;
                    flag_digit3 = false;
                    flag_point = false;
                    consigne = consigne + ((float)keyboard / 10);
                }

                if (flag_digit3)
                {
                    consigne = consigne * 10;
                    consigne = (float)keyboard + consigne;
                    flag_digit1 = false;
                    flag_digit2 = false;
                    flag_digit3 = false;
                    flag_point = true;
                }

                if (flag_digit2)
                {
                    consigne = consigne * 10;
                    consigne = (float)keyboard + consigne;
                    flag_digit1 = false;
                    flag_digit2 = false;
                    flag_digit3 = true;
                    flag_point = false;
                }

                if (flag_digit1)
                {
                    consigne = (float)keyboard;
                    flag_digit1 = false;
                    flag_digit2 = true;
                    flag_digit3 = false;
                    flag_point = false;
                }

                //-- Empêche de dépasser les limites de la table

                if (consigne > HAUTEUR_MAX + OFFSET_MACHINE_FLOAT)
                {
                    consigne = HAUTEUR_MAX + OFFSET_MACHINE_FLOAT;
                }
            }

            affiche_consigne(consigne);

            lastDebounceTimeKeyboard = millis();
        }
    }

    if (Menu == 1)
    {
        if (touchPos.touched)
        {

            time_now_fader = millis();

            int x = touchPos.xPos;
            int y = touchPos.yPos;

            // Touche menu Edit
            if ((x >= 338) && (x <= 480) && (y >= 240) && (y <= 306))
            {
                flag_refresh = true;
                flag_boucle = true;
                compteurParametres = 0;
                old_compteurParametres = 99;
                Menu = 2;
                editParametres();
            }

            // Fléche close
            if ((x >= 440) && (x <= 480) && (y >= 0) && (y <= 40))
            {
                Menu = 0;
                flag_keyboard = true;
                flag_boucle = false;
                afficheMenuPrincipal();
            }
        }
    }
}