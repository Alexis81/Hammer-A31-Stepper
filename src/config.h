#include <TFT_eSPI.h> // Hardware-specific library

// IO pin assignments
#define MOTOR_STEP_PIN                        4
#define MOTOR_DIRECTION_PIN                   2
#define EMERGENCY_STOP_PIN                   38          //define the IO pin the emergency stop switch is connected to
#define LIMIT_SWITCH_PIN                     32           //define the IO pin where the limit switches are connected to (switches in series in normally closed setup against ground)

// Speed settings
#define SPEED_IN_STEPS_PER_SECOND           15000
#define ACCELERATION_IN_STEPS_PER_SECOND    800
#define DECELERATION_IN_STEPS_PER_SECOND    800

#define STEP_PER_MILLIMETER                 320         // Avec un ration de poulie de 1,6, il 320 pas pour faire 1 mm (soit 640 pas pour un tours de manivelle)

// Définition de la table de raboteuse
#define HAUTEUR_MINI    2               // en mm
#define HAUTEUR_MAX     230             // en mm
#define RATTRAPE_JEU    1               // en mm
#define INCREMENT       2               // en mm

//-- Back Light LCD
#define pwmChannel  1
#define frequence   500
#define resolution  8

#define DISPLAY_WIDTH  480
#define DISPLAY_HEIGHT 320
#define INTERVAL 100                // P�riode entre chaque rafraîchissement de l'écran en ms (ici 5 Hz (1/200 ms))


// variables for consigne
float consigne = (float)HAUTEUR_MINI;

//variables for software debouncing of the limit switches
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 100;              //the minimum delay in milliseconds to check for bouncing of the switch. Increase this slighlty if you switches tend to bounce a lot

//variables for software debouncing keyboard
unsigned long lastDebounceTimeKeyboard = 0;
unsigned long debounceDelayKeyboard = 250;

unsigned long actuelMillis = 0;     // Pour l'affichage
unsigned long precedentMillis = 0;

int keyboard = 0;
int etat = 0;



bool flag_keyboard = true;      // Permet de savoir si nous avons l'autorisation de capter une touche
bool flag_button_ok = true;     // Flag pour signaler si le bouton Ok est affiché
bool flag_move = false;         // Flag pour signaler si le moteur tourne
bool flag_Goal = false;                 // Flag pour signaler que nous sommes à la target
bool flag_Back = false;

bool flag_digit1 = true;
bool flag_digit2 = false;
bool flag_digit3 = false;
bool flag_point = false;
bool flag_affiche_ok = true;

