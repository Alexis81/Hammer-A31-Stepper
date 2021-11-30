#include <TFT_eSPI.h> // Hardware-specific library

// IO pin assignments
#define MOTOR_STEP_PIN                        4
#define MOTOR_DIRECTION_PIN                   2
#define EMERGENCY_STOP_PIN                   38          //define the IO pin the emergency stop switch is connected to
#define LIMIT_SWITCH_PIN                     32           //define the IO pin where the limit switches are connected to (switches in series in normally closed setup against ground)

// Speed settings
#define SPEED_IN_STEPS_PER_SECOND           8000
#define ACCELERATION_IN_STEPS_PER_SECOND    800
#define DECELERATION_IN_STEPS_PER_SECOND    800

#define STEP_PER_MILLIMETER                 320         // Avec un ration de poulie de 1,6, il 320 pas pour faire 1 mm (soit 640 pas pour un tours de manivelle)

// Définition de la table de raboteuse
int HAUTEUR_MINI;               // en mm
int HAUTEUR_MAX;             // en mm
int RATTRAPE_JEU;               // en mm
int INCREMENT;               // en mm

//-- Back Light LCD
#define pwmChannel  1
#define frequence   500
#define resolution  8
int BACKLIGHT;

#define DISPLAY_WIDTH  480
#define DISPLAY_HEIGHT 320

#define LENGTH(x) (strlen(x) + 1)   // length of char string
#define EEPROM_SIZE 200             // EEPROM size



// variables for consigne
float consigne = (float)HAUTEUR_MINI;

//variables for software debouncing of the limit switches
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 100;              //the minimum delay in milliseconds to check for bouncing of the switch. Increase this slighlty if you switches tend to bounce a lot

//variables for software debouncing keyboard
unsigned long lastDebounceTimeKeyboard = 0;
unsigned long debounceDelayKeyboard = 250;

unsigned long time_now_fader = 0;     // Compteur de temps pour le fade du LCD
unsigned long timer_fade = 0;         // Compteur pour le fade du LCD
unsigned long TIME_FADE = 20000;       // Temps avant de baisser le brightness de l'écran

int keyboard = 0;
int etat = 0;                       // Etat bouton Ok - Stop etc...
int Menu = 0;   
int compteurParametres = 0;  
int old_compteurParametres = 99;
int compteur= 0;
bool flag_save = false;

String nomParametre = "";
String sauveNomParametre = "";
String unite = "";
int parametre = 0;


bool flag_keyboard = true;      // Permet de savoir si nous avons l'autorisation de capter une touche

bool flag_move = false;         // Flag pour signaler si le moteur tourne
bool flag_Goal = false;                 // Flag pour signaler que nous sommes à la target
bool flag_Back = false;

bool flag_digit1 = true;
bool flag_digit2 = false;
bool flag_digit3 = false;
bool flag_point = false;
bool flag_affiche_ok = true;
bool flag_boucle = true;
bool flag_refresh = false;
byte limitSwitchState = 1;
byte oldConfirmedLimitSwitchState = 1;


