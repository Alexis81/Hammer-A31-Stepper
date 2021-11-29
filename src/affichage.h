#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library
#include <TFT_eFEX.h>
#include "FT62XXTouchScreen.h"

TFT_eSPI tft = TFT_eSPI();
TFT_eFEX  fex = TFT_eFEX(&tft);


void affiche_reel(float mm) {
    if((actuelMillis - precedentMillis > INTERVAL) && !stepper.motionComplete()) {
        tft.setCursor(300, 50);
        tft.setTextFont(7);
        tft.setTextSize(1);
        tft.setTextColor(TFT_WHITE, TFT_WHITE);
        tft.printf("888.8");
        tft.setCursor(300, 50);
        tft.setTextColor(TFT_RED,  TFT_WHITE);
        tft.printf("%05.1f", mm);
        precedentMillis = actuelMillis; 
    }
}

void affiche_reel_first(float mm) {
    tft.setCursor(300, 50);
    tft.setTextFont(7);
    tft.setTextSize(1);
    tft.setTextColor(TFT_WHITE, TFT_WHITE);
    tft.printf("888.8");
    tft.setCursor(300, 50);
    tft.setTextColor(TFT_RED,  TFT_WHITE);
    tft.printf("%05.1f", mm); 
}

void affiche_consigne(float mm) {
        tft.setCursor(300, 120);
        tft.setTextFont(7);
        tft.setTextSize(1);
        tft.setTextColor(TFT_WHITE, TFT_WHITE);
        tft.printf("888.8");
        tft.setCursor(300, 120);
        tft.setTextColor(TFT_GREEN,  TFT_WHITE);
        tft.printf("%05.1f", mm);
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