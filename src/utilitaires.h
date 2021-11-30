#ifndef _SAVEPREFERENCE_H_
#define _SAVEPREFERENCE_H_

#include <Preferences.h>



/*------------------------------------------------------------------------------
  Permet de lire une clé, valeur de type String
------------------------------------------------------------------------------*/
String getPreferencesString(String key)
{
  Preferences preferences;

  preferences.begin("Hammer", true);

  // convert String to char*, see https://coderwall.com/p/zfmwsg/arduino-string-to-char
  char *ch_KEY = const_cast<char *>(key.c_str());
  String value = preferences.getString(ch_KEY);
  //Serial.print("Pref " + key + " : ");
  //Serial.println(value);
  preferences.end();

  return value;
}

/*------------------------------------------------------------------------------
  Permet de sauver une clé, valeur de type String
------------------------------------------------------------------------------*/
size_t putPreferencesString(String key, String value)
{
  Preferences preferences;

  preferences.begin("Hammer", false);

  // convert String to char*, see https://coderwall.com/p/zfmwsg/arduino-string-to-char
  char *ch_KEY = const_cast<char *>(key.c_str());
  size_t ret = preferences.putString(ch_KEY, value);
  //Serial.print("Return : ");
  //Serial.println(ret);

  return ret;
}

/*------------------------------------------------------------------------------
  Permet de lire une clé, valeur de type Int
------------------------------------------------------------------------------*/
int getPreferencesInt(String key, int defaut)
{
  Preferences preferences;

  preferences.begin("Hammer", true);

  // convert String to char*, see https://coderwall.com/p/zfmwsg/arduino-string-to-char
  char *ch_KEY = const_cast<char *>(key.c_str());
  int value = preferences.getInt(ch_KEY, defaut);
  //Serial.print("Pref " + key + " : ");
  //Serial.println(value);
  preferences.end();

  return value;
}

int getPreferencesInt(String key)
{
  Preferences preferences;

  preferences.begin("Hammer", true);

  // convert String to char*, see https://coderwall.com/p/zfmwsg/arduino-string-to-char
  char *ch_KEY = const_cast<char *>(key.c_str());
  int value = preferences.getInt(ch_KEY);
  //Serial.print("Pref " + key + " : ");
  //Serial.println(value);
  preferences.end();

  return value;
}

/*------------------------------------------------------------------------------
  Permet de sauver une clé, valeur de type Bool
------------------------------------------------------------------------------*/
size_t putPreferencesInt(String key, int value)
{
  Preferences preferences;

  preferences.begin("Hammer", false);

  // convert String to char*, see https://coderwall.com/p/zfmwsg/arduino-string-to-char
  char *ch_KEY = const_cast<char *>(key.c_str());
  size_t ret = preferences.putInt(ch_KEY, value);
  //Serial.print("Return : ");
  //Serial.println(ret);

  return ret;
}

/*------------------------------------------------------------------------------
  Permet de lire une clé, valeur de type Bool
------------------------------------------------------------------------------*/
bool getPreferencesBool(String key)
{
  Preferences preferences;

  preferences.begin("Hammer", true);

  // convert String to char*, see https://coderwall.com/p/zfmwsg/arduino-string-to-char
  char *ch_KEY = const_cast<char *>(key.c_str());
  bool value = preferences.getBool(ch_KEY);
  //Serial.print("Pref " + key + " : ");
  //Serial.println(value);
  preferences.end();

  return value;
}

/*------------------------------------------------------------------------------
  Permet de sauver une clé, valeur de type Bool
------------------------------------------------------------------------------*/
size_t putPreferencesBool(String key, bool value)
{
  Preferences preferences;

  preferences.begin("Hammer", false);

  // convert String to char*, see https://coderwall.com/p/zfmwsg/arduino-string-to-char
  char *ch_KEY = const_cast<char *>(key.c_str());
  size_t ret = preferences.putBool(ch_KEY, value);
  //Serial.print("Return : ");
  //Serial.println(ret);

  return ret;
}

void readAllParameters() {
    HAUTEUR_MAX = getPreferencesInt("hauteur_max", 230);
    HAUTEUR_MINI = getPreferencesInt("hauteur_mini", 2);
    RATTRAPE_JEU = getPreferencesInt("rattrape_jeu", 1);
    INCREMENT = getPreferencesInt("increment", 2);
    BACKLIGHT = getPreferencesInt("backlight", 200);
    TIME_FADE = getPreferencesInt("fade_screen", 20);
}


#endif