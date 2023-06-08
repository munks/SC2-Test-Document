#include "main.h"

short cursorPos = 0;
short cursorMax = 0;
WINDOW enterFunc[30];
SC2PARAM params;
HKEY file;
HKEY directory;
char icon[260];
char execute[260];

void KeyExecute (unsigned char key, bool special) {
	if (special) {
		switch (key) {
			case c_keyUp: {
				if (cursorPos > 0) {
					cursorPos--;
				}
				break;
			}
			case c_keyDown: {
				if (cursorPos < cursorMax) {
					cursorPos++;
				}
				break;
			}
		}
		printf(" ");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, cursorPos});
		printf(">");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, cursorPos});
	} else {
		switch (key) {
			case '\r': {
				enterFunc[cursorPos]();
				break;
			}
		}
	}
}

void InputLoop () {
	unsigned char key;
	
	while (true) {
		key = _getch();
		if (key == 0x00 || key == 0xE0) {
			KeyExecute(_getch(), true);
		} else {
			KeyExecute (key, false);
		}
	}
}

int main () {
	DWORD iconCnt = 260;
	DWORD executeCnt = 260;
	
	RegGetValue(HKEY_CLASSES_ROOT, "SC2.Map\\DefaultIcon", NULL, RRF_RT_REG_SZ, NULL, icon, &iconCnt);
	RegGetValue(HKEY_CLASSES_ROOT, "Blizzard.SC2Map\\DefaultIcon", NULL, RRF_RT_REG_SZ, NULL, execute, &executeCnt);
	*strrchr(execute, ',') = '\0';
	RegOpenKey(HKEY_CLASSES_ROOT, "Blizzard.SC2Map\\shell", &file);
	RegOpenKey(HKEY_CLASSES_ROOT, "Directory\\shell", &directory);
	
	Init();
	InputLoop();
	return 0;
}