#include "main.h"

void Init () {
	system("cls");
	
	cursorPos = 0;
	cursorMax = 2;
	
	enterFunc[0] = ParameterSettings;
	enterFunc[1] = RemoveList;
	enterFunc[2] = Close;
	
	puts(">Add Setting");
	puts(" Remove Setting");
	puts(" Close");
	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0});
}

void ParameterSettings () {
	system("cls");
	
	cursorPos = 0;
	cursorMax = 10;
	
	ClearStructure();
	
	enterFunc[0] = ParameterDisplay;
	enterFunc[1] = ParameterTriggerDebug;
	enterFunc[2] = ParameterBreakOnError;
	enterFunc[3] = ParameterBreakOnWindow;
	enterFunc[4] = ParameterPreload;
	enterFunc[5] = ParameterFixedSeed;
	enterFunc[6] = ParameterSeedValue;
	enterFunc[7] = ParameterMelee;
	enterFunc[8] = ParameterDifficulty;
	enterFunc[9] = ParameterSpeed;
	enterFunc[10] = CreateSetting;
	
	puts(">Display Mode: Windowed");
	puts(" Show Trigger Debug: Off");
	puts(" Break On Trigger Error: Off");
	puts(" Break On Trigger Debug Window Open: Off");
	puts(" Use Preloading: Off");
	puts(" Use Fixed Random Seed: Off");
	puts(" Seed Value: 0");
	puts(" Melee Expansion: Liberty");
	puts(" Game Difficulty: Very Easy");
	puts(" Game Speed: Slower");
	puts(" *Create Setting");
	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0});
}

void ClearStructure () {
	params.display = 0;
	params.triggerDbg = false;
	params.breakOnError = false;
	params.breakOnWindow = false;
	params.preload = false;
	params.fixedSeed = false;
	params.seedVal = 0;
	params.melee = 1;
	params.difficulty = 1;
	params.speed = 0;
}

void CreateSetting () {
	char name[260];
	char* lparam = (char*)malloc(500);
	
	system("cls");
	printf("Enter the name: "); gets(name);
	
	if (!strlen(name)) { goto SettingEnd; }
	
	sprintf(lparam, "%s -run \"%%1\"", execute); //SC2Switcher
	sprintf(lparam, "%s -displaymode %d", lparam, params.display); //Display Mode
	sprintf(lparam, "%s%s", lparam, params.triggerDbg ? " -trigdebug" : ""); //Show Trigger Debug
	sprintf(lparam, "%s%s", lparam, params.breakOnError ? " -breakOnError" : ""); //Break On Trigger Error
	sprintf(lparam, "%s%s", lparam, params.breakOnWindow ? " -breakOnStart" : ""); //Break On Trigger Debug Window Open
	sprintf(lparam, "%s -preload %d", lparam, params.preload ? 1 : 0); //Use Preloading
	sprintf(lparam, "%s%s", lparam, params.fixedSeed ? " -fixedseed" : ""); //Use Fixed Random Seed
	sprintf(lparam, "%s -seedValue %d", lparam, params.seedVal); //Seed Value
	sprintf(lparam, "%s -meleeMod %s", lparam, textMelee[params.melee - 1]); //Melee Expansion
	sprintf(lparam, "%s -difficulty %d", lparam, params.difficulty); //Game Difficulty
	sprintf(lparam, "%s -speed %d", lparam, params.speed); //Game Speed
	
	RegSetKeyValue(fileMap, name, NULL, REG_SZ, name, strlen(name));
	RegSetKeyValue(fileMap, name, "Icon", REG_SZ, icon, strlen(icon));
	RegSetKeyValue(fileMod, name, NULL, REG_SZ, name, strlen(name));
	RegSetKeyValue(fileMod, name, "Icon", REG_SZ, icon, strlen(icon));
	RegSetKeyValue(directory, name, NULL, REG_SZ, name, strlen(name));
	RegSetKeyValue(directory, name, "Icon", REG_SZ, icon, strlen(icon));
	strcat(name, "\\command");
	RegSetKeyValue(fileMap, name, NULL, REG_SZ, lparam, 260);
	RegSetKeyValue(fileMod, name, NULL, REG_SZ, lparam, 260);
	RegSetKeyValue(directory, name, NULL, REG_SZ, lparam, 260);
	
	SettingEnd:
	free(lparam);
	Init();
}

void RemoveList () {
	int idx = 0;
	char name[260];
	
	system("cls");
	
	cursorPos = 0;
	
	while (RegEnumKey(fileMap, idx, name, 260) != ERROR_NO_MORE_ITEMS && idx < 30) {
		printf("%c", idx ? ' ' : '>');
		if (strcmp(name, "open") != 0) {
			printf("%s\n", name);
			enterFunc[idx] = RemoveSetting;
		} else {
			puts("Close");
			enterFunc[idx] = Init;
		}
		idx++;
	}
	cursorMax = idx - 1;
	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0});
}

void RemoveSetting () {
	char name[260];
	
	if (RegEnumKey(fileMap, cursorPos, name, 260) != ERROR_NO_MORE_ITEMS) {
		RegDeleteTree(fileMap, name);
		RegDeleteTree(fileMod, name);
		RegDeleteTree(directory, name);
		RegDeleteKey(fileMap, name);
		RegDeleteKey(fileMod, name);
		RegDeleteKey(directory, name);
	}
	
	Init();
}

void Close () {
	RegCloseKey(fileMap);
	RegCloseKey(fileMod);
	RegCloseKey(directory);
	exit(0);
}