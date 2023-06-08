#pragma once

#include <stdio.h>
#include <conio.h>
#include <wchar.h>
#include <locale.h>
#include <windows.h>

#define c_keyUp 0x48
#define c_keyDown 0x50

typedef void (*WINDOW)();

typedef struct SC2PARAM {
	int display = 0;
	bool triggerDbg = false;
	bool breakOnError = false;
	bool breakOnWindow = false;
	bool preload = false;
	bool fixedSeed = false;
	int seedVal = 0;
	int melee = 1;
	int difficulty = 1;
	int speed = 0;
} SC2PARAM;

extern short cursorPos;
extern short cursorMax;
extern WINDOW enterFunc[30];
extern SC2PARAM params;
extern char icon[260];
extern HKEY file;
extern HKEY directory;
extern char execute[260];

//Const
extern const char* textDisplay[3];
extern const char* textMelee[3];
extern const char* textDifficulty[10];
extern const char* textSpeed[5];

//main.cpp
void KeyExecute (unsigned char key, bool special);
void InputLoop ();
int main ();

//common.cpp
void Init ();
void ParameterSettings ();
void ClearStructure ();
void CreateSetting ();
void RemoveList ();
void RemoveSetting ();
void Close ();

//parameters.cpp
void ParameterDisplay ();
void ParameterTriggerDebug ();
void ParameterBreakOnError ();
void ParameterBreakOnWindow ();
void ParameterPreload ();
void ParameterFixedSeed ();
void ParameterSeedValue ();
void ParameterMelee ();
void ParameterDifficulty ();
void ParameterSpeed ();