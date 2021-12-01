#include <TFT_eSPI.h> // Hardware-specific library
FT62XXTouchScreen touchScreen = FT62XXTouchScreen(DISPLAY_HEIGHT, PIN_SDA, PIN_SCL);

/*------------------------------------------------------------------------------
  Permet d'afficher les différents paramètres
------------------------------------------------------------------------------*/
void parametres()
{

    tft.setTextSize(1);

    // Efface l'écran
    tft.fillScreen(TFT_WHITE);

    // Création du titre
    affiche_titre_menu("Settings");

    // Création des paramètres
    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    tft.setTextSize(1);
    tft.setFreeFont(&FreeMonoBold12pt7b);
    tft.drawString("- Hauteur Maxi   :", 4, 50);
    tft.drawString("- Hauteur Mini   :", 4, 80);
    tft.drawString("- Rattape jeu    :", 4, 110);
    tft.drawString("- Increments     :", 4, 140);
    tft.drawString("- Backlight      :", 4, 170);
    tft.drawString("- Fade screen    :", 4, 200);
    tft.drawString("- Up after Home  :", 4, 230);
    tft.drawString("- Offset machine :", 4, 260);

    // Serial.println(tft.textWidth("999"));

    tft.setTextDatum(TR_DATUM);
    tft.setTextPadding(41);

    // Position X des chiffres
    int x = 300;
    // Hauteur Maxi
    tft.drawNumber(HAUTEUR_MAX, x, 50);
    // Hauteur Mini
    tft.drawNumber(HAUTEUR_MINI, x, 80);
    // Rattrape jeu
    tft.drawNumber(RATTRAPE_JEU, x, 110);
    // Increment
    tft.drawNumber(INCREMENT, x, 140);
    // Blacklight
    tft.drawNumber(BACKLIGHT, x, 170);
    // fade screen
    tft.drawNumber(TIME_FADE, x, 200);
    // Up after home
    tft.drawNumber(UP_AFTER_HOME, x, 230);
    // Offset machine
    tft.drawNumber(OFFSET_MACHINE, x, 260);

    tft.setTextDatum(TL_DATUM);
    tft.setTextPadding(0);

    // Affichage du bouton Edit
    affiche_bouton_edit();
}

/*------------------------------------------------------------------------------
  Permet de modifier les différents paramètres
------------------------------------------------------------------------------*/
void editParametres()
{

    tft.setTextSize(1);

    // Efface l'écran
    tft.fillScreen(TFT_WHITE);

    // Création du titre
    affiche_titre_menu("Settings Edit");

    while (flag_boucle)
    {
        switch (compteurParametres)
        {
        case 0:
            nomParametre = "Hauteur Maxi";
            parametre = HAUTEUR_MAX;
            unite = "mm";
            maxi = 9999;
            mini = 1;
            compteur = 0;
            break;

        case 1:
            nomParametre = "Hauteur Mini ";
            parametre = HAUTEUR_MINI;
            unite = "mm";
            compteur = 1;
            maxi = 9999;
            mini = 1;
            break;

        case 2:
            nomParametre = "Rattrape jeu";
            parametre = RATTRAPE_JEU;
            unite = "mm";
            compteur = 2;
            maxi = 9999;
            mini = 1;
            break;

        case 3:
            nomParametre = "Increment      ";
            parametre = INCREMENT;
            unite = "mm";
            compteur = 3;
            maxi = 4;
            mini = 1;
            break;

        case 4:
            nomParametre = "Backlight";
            parametre = BACKLIGHT;
            unite = "";
            compteur = 4;
            maxi = 255;
            mini = 10;
            break;

        case 5:
            nomParametre = "Fade screen";
            parametre = TIME_FADE;
            unite = "secondes";
            compteur = 5;
            maxi = 9999;
            mini = 5;
            break;

        case 6:
            nomParametre = "Up after Home";
            parametre = UP_AFTER_HOME;
            unite = "   mm    ";
            maxi = 10;
            mini = 1;
            compteur = 6;
            break;

        case 7:
            nomParametre = "Offset machine";
            parametre = OFFSET_MACHINE;
            unite = "dixieme mm";
            compteur = 7;
            maxi = 9999;
            mini = 1;
            break;

        default:
            break;
        }

        if (compteurParametres != old_compteurParametres || flag_refresh)
        {
            tft.setTextSize(2);
            tft.setTextPadding(90);

            tft.setTextColor(TFT_BLACK, TFT_WHITE);
            tft.setFreeFont(&FreeMonoBold12pt7b);
            tft.drawString(nomParametre, 70, 50);
            tft.setTextDatum(TC_DATUM);
            tft.setTextColor(TFT_BLACK, TFT_YELLOW);
            tft.drawNumber(parametre, 235, 140);
            tft.setTextColor(TFT_DARKGREY, TFT_WHITE);
            tft.drawString(unite, 235, 190);

            tft.setTextDatum(TL_DATUM);

            fex.drawJpgFile(SPIFFS, "/Bouton_Plus.jpg", 365, 140);
            fex.drawJpgFile(SPIFFS, "/Bouton_Moins.jpg", 70, 140);

            fex.drawJpgFile(SPIFFS, "/Fleche_Precedent.jpg", 0, 260);
            fex.drawJpgFile(SPIFFS, "/Fleche_Suivant.jpg", 420, 260);

            if (flag_save)
            {
                fex.drawJpgFile(SPIFFS, "/Bouton_Save.jpg", 120, 260);
            }

            old_compteurParametres = 99;
            compteurParametres = 99;

            flag_refresh = false;
        }
        TouchPoint touchPos = touchScreen.read();

        if (Menu == 2)
        {
            if (touchPos.touched)
            {

                time_now_fader = millis();

                int x = touchPos.xPos;
                int y = touchPos.yPos;

                // Touche menu -
                if ((x >= 70) && (x <= 115) && (y >= 140) && (y <= 185))
                {
                    if (parametre > mini)
                    {
                        parametre = parametre - 1;
                        // Permet d'ajuster en live la luminosité de l'écran LCD
                        if (compteur == 4)
                        {
                            ledcWrite(pwmChannel, parametre);
                        }
                        flag_refresh = true;
                        flag_save = true;
                    }
                }

                // Touche menu +
                if ((x >= 365) && (x <= 410) && (y >= 140) && (y <= 185))
                {
                    if (parametre < maxi)
                    {
                        parametre = parametre + 1;
                        // Permet d'ajuster en live la luminosité de l'écran LCD
                        if (compteur == 4)
                        {
                            ledcWrite(pwmChannel, parametre);
                        }
                        flag_refresh = true;
                        flag_save = true;
                    }
                }

                // Fléche précédente
                if ((x >= 0) && (x <= 60) && (y >= 260) && (y <= 320))
                {
                    if (compteur > 0)
                    {
                        compteur = compteur - 1;
                        compteurParametres = compteur;
                    }
                    flag_refresh = true;
                }

                // Fléche suivante
                if ((x >= 420) && (x <= 480) && (y >= 260) && (y <= 320))
                {
                    if (compteur < 7)
                    {
                        compteur = compteur + 1;
                        compteurParametres = compteur;
                    }
                    flag_refresh = true;
                }

                if (flag_save)
                {
                    // Bouton save
                    if ((x >= 120) && (x <= 360) && (y >= 260) && (y <= 320))
                    {
                        switch (compteur)
                        {
                        case 0:
                            sauveNomParametre = "hauteur_max";
                            HAUTEUR_MAX = parametre;
                            compteur = 0;
                            break;

                        case 1:
                            sauveNomParametre = "hauteur_mini";
                            HAUTEUR_MINI = parametre;
                            break;

                        case 2:
                            sauveNomParametre = "rattrape_jeu";
                            RATTRAPE_JEU = parametre;
                            break;

                        case 3:
                            sauveNomParametre = "increment";
                            INCREMENT = parametre;
                            compteur = 3;
                            break;

                        case 4:
                            sauveNomParametre = "backlight";
                            BACKLIGHT = parametre;
                            compteur = 4;
                            break;

                        case 5:
                            sauveNomParametre = "fade_screen";
                            TIME_FADE = parametre;
                            compteur = 5;
                            break;

                        case 6:
                            sauveNomParametre = "up_after_home";
                            UP_AFTER_HOME = parametre;
                            compteur = 6;
                            break;

                        case 7:
                            sauveNomParametre = "offset_machine";
                            OFFSET_MACHINE = parametre;
                            compteur = 7;
                            break;

                        case 99:
                            break;

                        default:
                            break;
                        }
                        // Sauvegarde du paramètre
                        putPreferencesInt(sauveNomParametre, parametre);
                        flag_save = false;
                        tft.fillRect(120, 260, 240, 60, TFT_WHITE);
                    }
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
}