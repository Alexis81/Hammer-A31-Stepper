// https://cloudconvert.com/jpg-to-bmp
// https://www.flaticon.com/fr/packs/material-design/9


#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library
#include <TFT_eFEX.h>
#include "FT62XXTouchScreen.h"

TFT_eSPI tft = TFT_eSPI();
TFT_eFEX fex = TFT_eFEX(&tft);

/*------------------------------------------------------------------------------
  Permet d'afficher la position réelle de la table
------------------------------------------------------------------------------*/
void affiche_reel(float mm)
{
    if (Menu == 0)
    {
        tft.setTextFont(7);
        tft.setTextSize(1);
        tft.setTextPadding(140);
        tft.setTextDatum(R_BASELINE);
        tft.setTextColor(TFT_RED, TFT_WHITE);
        tft.drawFloat(mm, 1, 440, 100);
    }
}

/*------------------------------------------------------------------------------
  Permet d'afficher la consigne
------------------------------------------------------------------------------*/
void affiche_consigne(float mm)
{
    if (Menu == 0)
    {
        tft.setTextFont(7);
        tft.setTextSize(1);
        tft.setTextPadding(140);
        tft.setTextDatum(R_BASELINE);
        tft.setTextColor(TFT_GREEN, TFT_WHITE);
        tft.drawFloat(mm, 1, 440, 170);
    }
}

/*------------------------------------------------------------------------------
  Affiche voyant Run
------------------------------------------------------------------------------*/
void affiche_voyant_run(bool On)
{
    if(On) {
      tft.fillCircle(418, 197, 9, TFT_GREEN);
    }else{
      tft.fillCircle(418, 197, 9, TFT_WHITE);
    }
}

/*------------------------------------------------------------------------------
  Affiche voyant Home
------------------------------------------------------------------------------*/
void affiche_voyant_home(bool On)
{
    if(On) {
      tft.fillCircle(363, 197, 9, TFT_RED);
    }else{
      tft.fillCircle(363, 197, 9, TFT_WHITE);
    }
}

/*------------------------------------------------------------------------------
  Affiche voyant Dego
------------------------------------------------------------------------------*/
void affiche_voyant_dego(bool On)
{
    if(On) {
      tft.fillCircle(306, 197, 9, TFT_ORANGE);
    }else{
      tft.fillCircle(306, 197, 9, TFT_WHITE);
    }
}

/*------------------------------------------------------------------------------
  Permet d'afficher le bouton OK
------------------------------------------------------------------------------*/
void affiche_button_ok()
{
    fex.drawBmp("/Bouton_Ok.bmp", 285, 251);
}

/*------------------------------------------------------------------------------
  Permet d'afficher le bouton Ok après appuye sur Stop
------------------------------------------------------------------------------*/
void affiche_button_ok_urgence()
{
    fex.drawBmp("/Bouton_Ok_Urgence.bmp", 285, 251);
}

/*------------------------------------------------------------------------------
  Permet d'afficher le bouton stop
------------------------------------------------------------------------------*/
void affiche_button_stop()
{
    fex.drawBmp("/Bouton_Stop.jpg", 285, 251);
}

/*------------------------------------------------------------------------------
  Permet d'afficher le bouton Alarme
------------------------------------------------------------------------------*/
void affiche_alarm()
{
    fex.drawBmp("/Alarm.bmp", 285, 251);
}



/*------------------------------------------------------------------------------
  Permet d'afficher le logo
------------------------------------------------------------------------------*/
void affiche_logo()
{
    tft.fillScreen(TFT_WHITE);
    fex.drawJpgFile(SPIFFS, "/Hammer.jpg", 80, 15);
    delay(2000);
}

/*------------------------------------------------------------------------------
  Permet d'afficher le bouton edit des paramètres
------------------------------------------------------------------------------*/
void affiche_bouton_edit()
{
    fex.drawBmp("/Bouton_Edit.bmp", 338, 260);
}

/*------------------------------------------------------------------------------
  Permet d'afficher le titre d'un menu
------------------------------------------------------------------------------*/
void affiche_titre_menu(String Name)
{
    tft.fillRect(0, 0, 480, 40, TFT_WHITE);
    fex.drawBmp("/Close.bmp", 440, 0);
    tft.drawLine(0, 40, 480, 42, TFT_DARKGREY);
    tft.setTextDatum(TL_DATUM);
    tft.setTextColor(TFT_DARKGREY, TFT_WHITE);
    tft.setFreeFont(&FreeSans18pt7b); // Choose a nicefont that fits box
    tft.drawString(Name, 4, 4);
}

/*------------------------------------------------------------------------------
  Permet d'afficher la page principale
------------------------------------------------------------------------------*/
void afficheMenuPrincipal()
{
    tft.fillScreen(TFT_WHITE);
    fex.drawJpgFile(SPIFFS, "/Clavier.jpg", 0, 0);
    affiche_reel(consigne);
    affiche_consigne(0.0);
    affiche_button_ok();
}