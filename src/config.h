#include <TFT_eSPI.h> // Hardware-specific library

// Définition du display
#define DISPLAY_WIDTH 480
#define DISPLAY_HEIGHT 320

// IO pin assignments
#define MOTOR_STEP_PIN 4
#define MOTOR_DIRECTION_PIN 2
#define EMERGENCY_STOP_PIN 38 // define the IO pin the emergency stop switch is connected to
#define LIMIT_SWITCH_PIN 32   // define the IO pin where the limit switches are connected to (switches in series in normally closed setup against ground)

// Speed settings
#define SPEED_IN_STEPS_PER_SECOND 8000
#define ACCELERATION_IN_STEPS_PER_SECOND 800
#define DECELERATION_IN_STEPS_PER_SECOND 800
#define STEP_PER_MILLIMETER 320 // Avec un ratio de poulie de 1,6, il 320 pas pour faire 1 mm (soit 640 pas pour un tours de manivelle)

// Définition des charatéristiques de la machine
int HAUTEUR_MINI; // en mm (Table tout en haut)
int HAUTEUR_MAX;  // en mm (Table tout en bas)
int RATTRAPE_JEU; // en mm (Millimetres à faire pour rattraper le jeu de la table, lors de la descente de celle-ci)
int INCREMENT;    // en mm (Increment en mm pour monter ou descendre la table depuis es flèches de l'afficheur)
int UP_AFTER_HOME; // en mm (Millimètre pour remonter une fois Home trouvé, pour relacher l'interrupteur)
int OFFSET_MACHINE; // en mm (Offset pour ajuster la mesure de la machine en Int)
float OFFSET_MACHINE_FLOAT; // en centième de mm (0,01) - (Offset pour ajuster la mesure de la machine en Int)

//-- Back Light LCD
#define pwmChannel 1    // Canal du PWM
#define frequence 500   // Fréquence du PWM
#define resolution 8    // Résolution sur B bits le PWM

int BACKLIGHT;  // Valeur du backlight

unsigned long time_now_fader = 0; // Compteur de temps pour le fade du LCD
unsigned long timer_fade = 0;     // Compteur pour le fade du LCD
unsigned long TIME_FADE = 0;  // Temps avant de baisser le brightness de l'écran (valoriser par la lecture EEprom)

// Définitions pour les sauvegardes en EEprom
#define LENGTH(x) (strlen(x) + 1) // length of char string
#define EEPROM_SIZE 300           // EEPROM size

// variables for consigne
float consigne = (float)HAUTEUR_MINI;

// variables for software debouncing of the limit switches
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 100; // the minimum delay in milliseconds to check for bouncing of the switch. Increase this slighlty if you switches tend to bounce a lot

// variables for software debouncing keyboard
unsigned long lastDebounceTimeKeyboard = 0;
unsigned long debounceDelayKeyboard = 250;


int keyboard = 0; // Chiffre saisie au clavier
int Etat = 0; // Etat bouton Ok - Stop etc...
int Menu = 0; // Niveau du menu en cours
int compteurParametres = 0; // Compteur pour les menus
int old_compteurParametres = 99; // Compteur pour les menus
int compteur = 0; // Compteur pour les menus

// Utilisé dans les menus
String nomParametre = "";
String sauveNomParametre = "";
String unite = "";
int parametre = 0;

unsigned long maxi = 0;
unsigned long mini = 0;

bool flag_keyboard = true; // Permet de savoir si nous avons l'autorisation de capter une touche
bool flag_move = false; // Flag pour signaler si le moteur tourne
bool flag_Goal = false; // Flag pour signaler que nous sommes à la target
bool flag_Back = false; // Flag pour signaler que nous devons rattraper le jeu de la table

bool flag_digit1 = true;
bool flag_digit2 = false;
bool flag_digit3 = false;
bool flag_point = false;
bool flag_affiche_ok = true;
bool flag_boucle = true;
bool flag_refresh = false;
bool flag_first_run = true; // Flag pour signaler que nous venons de lancer le programme
bool flag_save = false; // Flag pour savoir si nous devons sauvegarder
bool flag_home_on = false; // Signale que nous avons une interuption avec l'inter Home
byte limitSwitchState = 1;
byte oldConfirmedLimitSwitchState = 0;

bool buttonStateChangeDetected = false;
