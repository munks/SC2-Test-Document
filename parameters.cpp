#include "main.h"

const char* textDisplay[3] = {"Windowed", "Windowed [Fullscreen]", "Fullscreen"};
const char* textMelee[3] = {"Liberty", "Swarm", "Void"};
const char* textDifficulty[10] = {"Very Easy", "Easy", "Medium", "Hard", "Harder", "Very Hard",
								  "Elite", "Cheater 1[Vision]", "Cheater 2[Resources]", "Cheater 3[Insane]"};
const char* textSpeed[5] = {"Slower", "Slow", "Normal", "Fast", "Faster"};

void ParameterDisplay () {
	
	params.display++;
	if (params.display == 3) { params.display = 0; }
	
	printf(">Display Mode: %-22s", textDisplay[params.display]);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, cursorPos});
}

void ParameterTriggerDebug () {
	
	params.triggerDbg = !params.triggerDbg;
	
	printf(">Show Trigger Debug: %-3s", params.triggerDbg ? "On" : "Off");
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, cursorPos});
}

void ParameterBreakOnError () {
	
	params.breakOnError = !params.breakOnError;
	
	printf(">Break On Trigger Error: %-3s", params.breakOnError ? "On" : "Off");
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, cursorPos});
}

void ParameterBreakOnWindow () {
	
	params.breakOnWindow = !params.breakOnWindow;
	
	printf(">Break On Trigger Debug Window Open: %-3s", params.breakOnWindow ? "On" : "Off");
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, cursorPos});
}

void ParameterPreload () {
	
	params.preload = !params.preload;
	
	printf(">Use Preloading: %-3s", params.preload ? "On" : "Off");
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, cursorPos});
}

void ParameterFixedSeed () {
	
	params.fixedSeed = !params.fixedSeed;
	
	printf(">Use Fixed Random Seed: %-3s", params.fixedSeed ? "On" : "Off");
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, cursorPos});
}

void ParameterSeedValue () {
	char text[20];
	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {13, cursorPos});
	gets(text);
	params.seedVal = atoi(text);
	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {13, cursorPos});
	printf("%-20d", params.seedVal);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, cursorPos});
}

void ParameterMelee () {
	
	params.melee++;
	if (params.melee == 4) { params.melee = 1; }
	
	printf(">Melee Expansion: %-8s", textMelee[params.melee - 1]);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, cursorPos});
}

void ParameterDifficulty () {
	
	params.difficulty++;
	if (params.difficulty == 11) { params.difficulty = 1; }
	
	printf(">Game Difficulty: %-22s", textDifficulty[params.difficulty - 1]);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, cursorPos});
}

void ParameterSpeed () {
	
	params.speed++;
	if (params.speed == 5) { params.speed = 0; }
	
	printf(">Game Speed: %-7s", textSpeed[params.speed]);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, cursorPos});
}