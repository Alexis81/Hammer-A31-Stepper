#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library
#include <TFT_eFEX.h>
#include "FT62XXTouchScreen.h"

TFT_eSPI tft = TFT_eSPI();
TFT_eFEX  fex = TFT_eFEX(&tft);


void affiche_reel(float mm) {
    if(Menu == 0) {
        tft.setTextFont(7);
        tft.setTextSize(1);
        tft.setTextPadding(140);
        tft.setTextDatum(R_BASELINE);
        tft.setTextColor(TFT_RED,  TFT_WHITE);
        tft.drawFloat(mm, 1, 440, 100);
    }
}

void affiche_consigne(float mm) {
    if(Menu == 0) {
        tft.setTextFont(7);
        tft.setTextSize(1);
        tft.setTextPadding(140);
        tft.setTextDatum(R_BASELINE);
        tft.setTextColor(TFT_GREEN,  TFT_WHITE);
        tft.drawFloat(mm, 1, 440, 170);
    }
}

void affiche_button_ok() {
    fex.drawJpgFile(SPIFFS, "/Bouton_Ok.jpg", 285, 251);
}

void affiche_button_ok_urgence() {
    fex.drawJpgFile(SPIFFS, "/Bouton_Ok_Urgence.jpg", 285, 251);
}

void affiche_button_stop() {
    fex.drawJpgFile(SPIFFS, "/Bouton_Stop.jpg", 285, 251);    
}

void afficheMenuPrincipal() {
  tft.fillScreen(TFT_BLACK);
  fex.drawJpgFile(SPIFFS, "/Clavier.jpg", 0, 0);
  affiche_reel(consigne);
  affiche_consigne(0.0);
  affiche_button_ok();
}