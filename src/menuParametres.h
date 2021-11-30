#include <TFT_eSPI.h> // Hardware-specific library
FT62XXTouchScreen touchScreen = FT62XXTouchScreen(DISPLAY_HEIGHT, PIN_SDA, PIN_SCL);

void parametres() {

    tft.setTextSize(1);
    
    // Efface l'écran
    tft.fillScreen(TFT_WHITE);

    // Création du titre
    tft.fillRect(0, 0, 480, 40, TFT_WHITE);
    fex.drawJpgFile(SPIFFS, "/Close.jpg", 440, 0);
    tft.drawLine(0,40,480,42, TFT_DARKGREY);
    tft.setTextDatum(TL_DATUM);
    tft.setTextColor(TFT_DARKGREY, TFT_WHITE);
    tft.setFreeFont(&FreeSans18pt7b);  // Choose a nicefont that fits box
    tft.drawString("Settings", 4, 4);

    // Création des paramètres
    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    tft.setTextSize(1);
    tft.setFreeFont(&FreeMonoBold12pt7b);
    tft.drawString("- Hauteur Maxi :", 4, 50);
    tft.drawString("- Hauteur Mini :", 4, 80);
    tft.drawString("- Rattape jeu  :", 4, 110);
    tft.drawString("- Increments   :", 4, 140);
    tft.drawString("- Backlight    :", 4, 170);
    tft.drawString("- Fade screen  :", 4, 200);

     // Hauteur Maxi
    tft.drawNumber(HAUTEUR_MAX, 240, 50);

    // Hauteur Mini
    tft.drawNumber(HAUTEUR_MINI, 240, 80);

    // Rattrape jeu
    tft.drawNumber(RATTRAPE_JEU, 240, 110);

    // Increment
    tft.drawNumber(INCREMENT, 240, 140);

    // Blacklight
    tft.drawNumber(BACKLIGHT, 240, 170);

    // fade screen
    tft.drawNumber(TIME_FADE, 240, 200);

    fex.drawJpgFile(SPIFFS, "/Bouton_Edit.jpg", 162, 260);


}

void editParametres() {

    tft.setTextSize(1);
    
    // Efface l'écran
    tft.fillScreen(TFT_WHITE);

    // Création du titre
    fex.drawJpgFile(SPIFFS, "/Close.jpg", 440, 0);
    tft.drawLine(0,40,480,42, TFT_DARKGREY);
    tft.setTextDatum(TL_DATUM);
    tft.setTextColor(TFT_DARKGREY, TFT_WHITE);
    tft.setFreeFont(&FreeSans18pt7b);  // Choose a nicefont that fits box
    tft.drawString("Settings Edit", 4, 4);

    while(flag_boucle) {
        switch (compteurParametres)
        {
        case 0:
            nomParametre = "Hauteur Maxi";
            parametre = HAUTEUR_MAX;
            unite = "mm";
            compteur = 0;
            break;

            case 1:
            nomParametre = "Hauteur Mini ";
            parametre = HAUTEUR_MINI;
            unite = "mm";
            compteur = 1;
            break;

            case 2:
            nomParametre = "Rattrape jeu";
            parametre = RATTRAPE_JEU;
            unite = "mm";
            compteur = 2;
            break;

            case 3:
            nomParametre = "Increment      ";
            parametre = INCREMENT;
            unite = "mm";
            compteur = 3;
            break;

            case 4:
            nomParametre = "Backlight";
            parametre = BACKLIGHT;
            unite = "";
            compteur = 4;
            break;

            case 5:
            nomParametre = "Fade screen";
            parametre = TIME_FADE;
            unite = "secondes";
            compteur = 5;
            break;

            case 99:
            break;

        default:
            break;
        }

        if(compteurParametres != old_compteurParametres || flag_refresh) {

            tft.setTextSize(2);
            tft.setTextPadding(90);

            tft.setTextColor(TFT_BLACK, TFT_WHITE);
            tft.setFreeFont(&FreeMonoBold12pt7b);
            tft.drawString(nomParametre, 70, 50);
            tft.setTextDatum(TC_DATUM);
            tft.setTextColor(TFT_BLACK, TFT_YELLOW);
            tft.drawNumber(parametre, 235, 140);
            tft.setTextColor(TFT_DARKGREY, TFT_WHITE);
            tft.drawString(unite, 235,190);

            tft.setTextDatum(TL_DATUM);

            fex.drawJpgFile(SPIFFS, "/Bouton_Plus.jpg", 365, 140);
            fex.drawJpgFile(SPIFFS, "/Bouton_Moins.jpg", 70, 140);

            fex.drawJpgFile(SPIFFS, "/Fleche_Precedent.jpg", 0, 260);
            fex.drawJpgFile(SPIFFS, "/Fleche_Suivant.jpg", 420, 260);

            if(flag_save) {
                fex.drawJpgFile(SPIFFS, "/Bouton_Save.jpg", 120, 260);                
            }

            old_compteurParametres = 99;
            compteurParametres = 99;
            
            flag_refresh = false;
        }
        TouchPoint touchPos = touchScreen.read();

        if(Menu == 2) {
        if( touchPos.touched) {

                time_now_fader = millis();

                int x = touchPos.xPos;
                int y = touchPos.yPos;

                // Touche menu -
                if ((x >=70 ) && (x <= 115) && (y >= 140) && (y <= 185)) {
                    parametre = parametre - 1;
                    if(compteur == 4) {
                        ledcWrite(pwmChannel, parametre);
                    }
                    flag_refresh = true;
                    flag_save = true;
                }

                // Touche menu +
                if ((x >=365 ) && (x <= 410) && (y >= 140) && (y <= 185)) {
                    parametre = parametre + 1;
                    if(compteur == 4) {
                        ledcWrite(pwmChannel, parametre);
                    }
                    flag_refresh = true;
                    flag_save = true;
                }

                // Fléche précédente
                if ((x >=0 ) && (x <= 60) && (y >= 260) && (y <= 320)) {
                    if(compteur > 0) {
                        compteur = compteur - 1;
                        compteurParametres = compteur;
                    }
                    flag_refresh = true;
                }

                // Fléche suivante
                if ((x >=420 ) && (x <= 480) && (y >= 260) && (y <= 320)) {
                    if(compteur < 5) {
                        compteur = compteur + 1;
                        compteurParametres = compteur;
                    }
                    flag_refresh = true;
                }

                if(flag_save) {
                        // Bouton save
                    if ((x >=120 ) && (x <= 360) && (y >= 260) && (y <= 320)) {
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
            if ((x >=440 ) && (x <= 480) && (y >= 0) && (y <= 40)) {
                Menu = 0;
                flag_keyboard = true;
                flag_boucle = false;
                afficheMenuPrincipal();
                
            }
        }
    }



    }
}