SET C51INC=C:\Keil\C51\INC\Cast\;C:\Keil\C51\INC\
SET C51LIB=C:\Keil\C51\LIB
SET CPU_TYPE=R8051XC2
SET CPU_VENDOR=CAST, Inc.
SET UV2_TARGET=CA51F
SET CPU_XTAL=0x016E3600
"C:\Keil\C51\BIN\C51.EXE" @.\hex\main.__i
"C:\Keil\C51\BIN\C51.EXE" @.\hex\delay.__i
"C:\Keil\C51\BIN\C51.EXE" @.\hex\SYSTEM~1.__I
"C:\Keil\C51\BIN\C51.EXE" @.\hex\uart.__i
"C:\Keil\C51\BIN\C51.EXE" @.\hex\INTERR~1.__I
"C:\Keil\C51\BIN\C51.EXE" @.\hex\debug.__i
"C:\Keil\C51\BIN\C51.EXE" @.\hex\ts_api.__i
"C:\Keil\C51\BIN\A51.EXE" @.\hex\STARTUP._ia
"C:\Keil\C51\BIN\LX51.EXE" @.\hex\ca51f3.lnp
"C:\Keil\C51\BIN\OHX51.EXE" ".\hex\ca51f3" HEX
