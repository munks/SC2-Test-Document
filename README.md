# SC2-Test-Document
StarCraft II Map File Direct Executor


### data.ini

DefaultMap = Local file to run (with no argument values)

DisplayMode = Display Mode (0: Windowed, 1: Windowed (Fullscreen), 2: Fullscreen)

TriggerDebug = Show Trigger Debug (0: Off, 1: On) - Ignored when DisplayMode is not 0

BreakOnError = Break On Trigger Error (0: Off, 1: On) - Ignored when TriggerDebug is 0

BreakOnOpen = Break On Trigger Debug Window Open (0 : Off, 1: On) - Ignored when TriggerDebug is 0

Preload = Enable Preloading (0: Off, 1: On)

RandomSeed = Use Fixed Random Seed (0: Off, 1: On)

SeedValue = Seed Value - Ignored when RandomSeed is 0

Melee = Melee Expansion (0: Default (Legacy of the Void), 1: Wings of Liberty, 2: Heart of the Swarm, 3: Legacy of the Void)

Difficulty = Game Difficulty (1: Very Easy, 2: Easy, 3: Medium, 4: Hard, 5: Harder, 6: Very Hard, 7: Elite, 8: Cheater 1 (Vision), 9: Cheater 2 (Resources), 
10: Cheater 3 (Insane))

Speed = Game Speed (0: Slower, 1: Slow, 2: Normal, 3: Fast, 4: faster)

### Functions

```char* rstrstr(char*, const char*)```

-Search 'param2' backwards from 'param1'

```char* FindSC2Path(char*)```

-Search StarCraft II Directory From String (From product.db)

```char* FindRecentSC2Version(char*) //return pointer must be free after use```

-Search Recent Version of StarCraft II (From StarCraft II Path)

```int CheckSC264Bit(char*)```

-Check Support Folder (From StarCraft II Path) {Support64: 64-Bit, Support: 32-Bit}

```void AddParameterFromInitFile(char*, char*, char*)```

-Add Strings To 'param2' ('param1' is 'data.ini' directory, 'param3' is map path)

### Naming Rule

Local Variable - lv_#Name#

Global Variable - gv_#Name#

Parameter - lp_#Name#

### Sequence

1. Find 'product.db' file from '%SystemDrive%\ProgramData\Battle.net\Agent'
2. Save file string to variable
3. Get StarCraft II installed folder from string
4. Get Version and Processer from StarCraft II installed folder
5. Create Command Line string, value from 'data.ini' file
6. Run with ShellExecute Function
7. Free memory
