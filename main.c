#include <stdio.h>
#include <io.h>
#include <wchar.h>
#include <locale.h>
#include <windows.h>

//Custom strstr Function (Reverse)
char* rstrstr (char *str1, const char *str2) {
	char *cp = str1;
	char *s1, *s2;

	if (!*str2) return str1;

	while (*cp) {
		s1 = cp;
		s2 = (char *) str2;
		while (*s1 && *s2 && !(*s1 - *s2)) {
			s1--;
			s2++;
		}
		if (!*s2) return s1;
		cp--;
	}

	return NULL;
}

//Reverse System Directory Traversal
char* FindSC2Path (char* lp_pathString) {
	char *lv_findPath;
	char *lv_tempPointer;
	char lv_tempChar;
	
	while (1) {
		lv_findPath = strstr(lp_pathString, "StarCraft II");
		if (!lv_findPath) {
			//Could Not Find StarCraft II
			return NULL;
		}
		lv_tempPointer = &lv_findPath[12];
		lv_tempChar = lv_findPath[12];
		*lv_tempPointer = '\0';
		lv_findPath = rstrstr(lv_findPath, "/:");
		if (lv_findPath) {
			//Found StarCraft II Directory
			return lv_findPath;
		}
		*lv_tempPointer = lv_tempChar;
	}
	return NULL;
}

//Return Base#Ver# String
char* FindRecentSC2Version (char* lp_versionPath, char* lp_output) {
	struct _finddata_t lv_fd;
	intptr_t lv_handle;
	char lv_tempPath[260];
	int lv_tempVersion = 0;
	int lv_returnVersion = 0;
	
	strcpy(lv_tempPath, lp_versionPath);
	strcat(lv_tempPath, "/Versions/*");
 
	if ((lv_handle = _findfirst(lv_tempPath, &lv_fd)) == -1) {
		return NULL;
	}
 
	while (_findnext(lv_handle, &lv_fd) == 0) {
		if (lv_fd.attrib & _A_SUBDIR) {
			lv_tempVersion = atoi(&lv_fd.name[4]);
			if (lv_tempVersion > lv_returnVersion) {
				lv_returnVersion = lv_tempVersion;
			}
		}
	}
	_findclose(lv_handle);
	if (lv_returnVersion) {
		sprintf(lp_output, "Base%d", lv_returnVersion);
		return lp_output;
	} else {
		return NULL;
	}
}
//Check Program Processer/0: Could Not Found /1: x86 /2: x64
int CheckSC264Bit (char* lp_initPath, char* lp_pathString) {
	struct _finddata_t lv_fd;
	intptr_t lv_handle;
	char lv_tempPath[260];
	int lv_forced32;
	
	lv_forced32 = GetPrivateProfileInt("option", "Forced32", 0, lp_initPath);
	printf("Run StarCraft II In 32-Bit: %s\n", lv_forced32 ? "On" : "Off");
	if (!lv_forced32) {
		strcpy(lv_tempPath, lp_pathString);
		strcat(lv_tempPath, "/Support64");
		lv_handle = _findfirst(lv_tempPath, &lv_fd);
		if (lv_fd.attrib & _A_SUBDIR ) {
			_findclose(lv_handle);
			puts("64-Bit Program Recognized.");
			return 2;
		}
	}
	
	strcpy(lv_tempPath, lp_pathString);
	strcat(lv_tempPath, "/Support");
	lv_handle = _findfirst(lv_tempPath, &lv_fd);
	if (lv_fd.attrib & _A_SUBDIR) {
		_findclose(lv_handle);
		puts("32-Bit Program Recognized.");
		return 1;
	} else {
		_findclose(lv_handle);
		return 0;
	}
	
	return 0;
}

void AddParameterFromInitFile (char* lp_initPath, char* lp_parameter, char* lp_targetMap) {
	char lv_tempString[260];
	int lv_tempInt;
	int lv_windowSwitch = 0;
	int lv_debugSwitch = 0;
	int lv_seedSwitch = 0;
	
	puts("Parameter List:");
	
	//Execution Map
	if (strlen(lp_targetMap) == 0) {
		GetPrivateProfileString("config", "DefaultMap", "Test\\EditorTest.SC2Map", lp_targetMap, 260, lp_initPath);
	}
	printf(" >Execution Map: \"%s\"\n", lp_targetMap);
	sprintf(lp_parameter, "%s -run \"%s\"", lp_parameter, lp_targetMap);
	
	//Display Mode
	lv_windowSwitch = GetPrivateProfileInt("config", "DisplayMode", 0, lp_initPath);
	if (lv_windowSwitch < 0 || lv_windowSwitch > 2) {
		lv_windowSwitch = 0;
	}
	printf(" >Display Mode: %d ", lv_windowSwitch);
	switch(lv_windowSwitch) {
		case 0: {
			puts("(Windowed)");
			break;
		}
		case 1: {
			puts("(Windowed [Fullscreen])");
			break;
		}
		case 2: {
			puts("(Fullscreen)");
			break;
		}
	}
	sprintf(lp_parameter, "%s -displaymode %d", lp_parameter, lv_windowSwitch);
	
	//Show Trigger Debug
	lv_debugSwitch = GetPrivateProfileInt("config", "TriggerDebug", 0, lp_initPath);
	if (lv_debugSwitch) {
		printf(" >Show Trigger Debug Window - On");
		if (!lv_windowSwitch) {
			puts("");
			strcat(lp_parameter, " -trigdebug");
		} else {
			puts(" (Ignored)");
			lv_debugSwitch = 0;
		}
	} else {
		puts(">Show Trigger Debug Window - Off");
	}
	
	//Break On Trigger Error
	lv_tempInt = GetPrivateProfileInt("config", "BreakOnError", 0, lp_initPath);
	printf("  *Break On Trigger Error - %s", lv_tempInt ? "On" : "Off");
	if (lv_debugSwitch && lv_tempInt) {
		puts("");
		strcat(lp_parameter, " -breakOnError");
	} else if (lv_tempInt) {
		puts(" (Ignored)");
	} else {
		puts("");
	}
	
	//Break On Trigger Debug Window Open
	lv_tempInt = GetPrivateProfileInt("config", "BreakOnOpen", 0, lp_initPath);
	printf("  *Break On Trigger Debug Window Open - %s", lv_tempInt ? "On" : "Off");
	if (lv_debugSwitch && lv_tempInt) {
		puts("");
		strcat(lp_parameter, " -breakOnStart");
	} else if (lv_tempInt) {
		puts(" (Ignored)");
	} else {
		puts("");
	}
	
	//Enable Preloading
	lv_tempInt = GetPrivateProfileInt("config", "Preload", 0, lp_initPath);
	printf(" >Enable Preloading - %s\n", lv_tempInt ? "On" : "Off");
	sprintf(lp_parameter, "%s -preload %d", lp_parameter, lv_tempInt ? 1 : 0);
	
	//No User Cheats|Reload Check (??)
	strcat(lp_parameter, " -NoUserCheats -reloadcheck");
	
	//Use Fixed Random Seed
	lv_seedSwitch = GetPrivateProfileInt("config", "RandomSeed", 0, lp_initPath);
	printf(" >Use Fixed Random Seed - %s\n", lv_seedSwitch ? "On" : "Off");
	if (lv_seedSwitch) {
		strcat(lp_parameter, " -fixedseed");
	}
	
	//Seed Value
	lv_tempInt = GetPrivateProfileInt("config", "SeedValue", 0, lp_initPath);
	printf("  *Seed Value: %d", lv_tempInt);
	if (lv_seedSwitch) {
		puts("");
		sprintf(lp_parameter, "%s -seedvalue %d", lp_parameter, lv_tempInt);
	} else {
		puts(" (Ignored)");
	}
	
	//Melee Expansion
	lv_tempInt = GetPrivateProfileInt("config", "Melee", 0, lp_initPath);
	if (lv_tempInt < 0 || lv_tempInt > 3) {
		lv_tempInt = 0;
	}
	printf(" >Melee Expansion: %d ", lv_tempInt);
	strcat(lp_parameter, " -meleeMod");
	switch(lv_tempInt) {
		case 1: {
			puts("(Liberty)");
			strcat(lp_parameter, " Liberty");
			break;
		}
		case 2: {
			puts("(Swarm)");
			strcat(lp_parameter, " Swarm");
			break;
		}
		case 0:
		case 3: {
			strcat(lp_parameter, " Void");
			printf("(Void%s\n", lv_tempInt ? ")" : " [Default])");
			break;
		}
	}
	
	//Game Difficulty
	lv_tempInt = GetPrivateProfileInt("config", "Difficulty", 1, lp_initPath);
	if (lv_tempInt < 1 || lv_tempInt > 10) {
		lv_tempInt = 1;
	}
	printf(" >Game Difficulty: %d ", lv_tempInt);
	sprintf(lp_parameter, "%s -difficulty %d", lp_parameter, lv_tempInt );
	switch (lv_tempInt) {
		case 1: puts("(Very Easy)"); break;
		case 2: puts("(Easy)"); break;
		case 3: puts("(Medium)"); break;
		case 4: puts("(Hard)"); break;
		case 5: puts("(Harder)"); break;
		case 6: puts("(Very Hard)"); break;
		case 7: puts("(Elite)"); break;
		case 8: puts("(Cheater 1[Vision])"); break;
		case 9: puts("(Cheater 2[Resources])"); break;
		case 10: puts("(Cheater 3[Insane])"); break;
	}
	
	//Game Speed
	lv_tempInt = GetPrivateProfileInt("config", "Speed", 0, lp_initPath);
	if (lv_tempInt < 0 || lv_tempInt > 4) {
		lv_tempInt = 0;
	}
	printf(" >Game Speed: %d ", lv_tempInt);
	sprintf(lp_parameter, "%s -speed %d", lp_parameter, lv_tempInt);
	switch (lv_tempInt) {
		case 0: puts("(Slower)"); break;
		case 1: puts("(Slow)"); break;
		case 2: puts("(Normal)"); break;
		case 3: puts("(Fast)"); break;
		case 4: puts("(faster)"); break;
	}
}

int main (int argc, char* argv[]) {
	char lv_targetMap[260] = {0, };

	//Set Init Path
	char* lv_initPath = (char*)malloc(sizeof(char)*(strlen(argv[0])+20));
	strcpy(lv_initPath, argv[0]);
	*(rstrstr(&lv_initPath[strlen(lv_initPath)-1], "\\")+1) = '\0';
	strcat(lv_initPath, "\\data.ini");
	
	//Drop File Check
	if (argc > 1) {
		printf("File Recognized: \"%s\"\n", argv[1]);
		//Check ".SC2Map" (No Sensitive)
		if (stricmp(&argv[1][strlen(argv[1])-7], ".SC2Map") != 0) {
			puts("File Is Not StarCraft II Document. Use Default Map.");
		} else {
			strcpy(lv_targetMap, argv[1]);
		}
	} else {
		puts("File Not Recongnized. Use Default Map");
	}
	puts("");
	
	//Set Battle Net Data Directory
	char lv_productFile[60];
	strcpy(lv_productFile, getenv("SystemDrive"));
	strcat(lv_productFile, "\\ProgramData\\Battle.net\\Agent\\product.db");
	
	FILE *lv_pathCheck = fopen(lv_productFile, "rb");
	
	//Open File
	if (lv_pathCheck == NULL) {
		puts("Could Not Find Battle.Net Install Data");
		goto End;
	}
	//Get File Size
	fseek(lv_pathCheck, 0, SEEK_END);
	int lv_count = ftell(lv_pathCheck);
	fseek(lv_pathCheck, 0, SEEK_SET);
	
	char *lv_checkString = (char*)malloc(sizeof(char)*(lv_count+2));
	memset(lv_checkString, 0, sizeof(char)*(lv_count+2));
	
	//Get Char From File
	int lv_arr = -1;
	while (lv_count--) {
		fread(&lv_checkString[++lv_arr], sizeof(char), 1, lv_pathCheck);
		if (lv_checkString[lv_arr] == '\0') {
			lv_checkString[lv_arr] = '\20';
		}
	}
	
	//Find Path
	char* lv_sc2Folder = (char*)malloc(sizeof(char)*(strlen(FindSC2Path(lv_checkString))+40));
	strcpy(lv_sc2Folder, FindSC2Path(lv_checkString));
	free(lv_checkString);
	if (!lv_sc2Folder) {
		puts("Could Not Found StarCraft II Installed Folder.");
		free(lv_sc2Folder);
		goto End;
	} else {
		printf("Found StarCraft II Installed Folder: \"%s\"\n", lv_sc2Folder);
	}

	//Find Recent Version Folder
	char lv_version[12];
	if (!FindRecentSC2Version(lv_sc2Folder, lv_version)) {
		printf("Could Not Found Installed Version.\n");
		free(lv_sc2Folder);
		goto End;
	} else {
		printf("Found Installed Version: %s\n", lv_version);
	}
	
	puts("");
	
	char* lv_parameterString = (char*)malloc(sizeof(char)*500);
	char lv_addtionalString[10];
	char lv_executeFile[260];
	
	switch (CheckSC264Bit(lv_initPath, lv_sc2Folder)) {
		case 2: {
			puts("Run StarCraft II (x64)");
			strcpy(lv_addtionalString, "_x64.exe");
			sprintf(lv_executeFile, "%s/Support64/SC2Switcher_x64.exe", lv_sc2Folder);
			break;
		}
		case 1: {
			puts("Run StarCraft II (x86)");
			strcpy(lv_addtionalString, ".exe");
			sprintf(lv_executeFile, "%s/Support/SC2Switcher.exe", lv_sc2Folder);
			break;
		}
		case 0: {
			puts("Could Not Find Correct Support Folder.");
			free(lv_parameterString);
			free(lv_sc2Folder);
			goto End;
		}
	}	

	puts("");
	//Parameter: Version
	sprintf(lv_parameterString, "\"%s/Versions/%s/SC2%s\"", lv_sc2Folder, lv_version, lv_addtionalString);

	//Parameter: Document Test
	AddParameterFromInitFile(lv_initPath, lv_parameterString, lv_targetMap);
	
	//Execute StarCraft II
	ShellExecute(NULL, "open", lv_executeFile, lv_parameterString, NULL, SW_SHOW);
	
	//Free Memory
	free(lv_parameterString);
	free(lv_sc2Folder);

	End:
	puts("");
	system("pause");
    return 0;
}