EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:switches
LIBS:Switch_Board-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L SW_Push SW1
U 1 1 5ACAD56B
P 3900 2350
F 0 "SW1" H 3950 2450 50  0000 L CNN
F 1 "SW_Push" H 3900 2290 50  0000 C CNN
F 2 "Buttons_Switches_THT:SW_PUSH-12mm" H 3900 2550 50  0001 C CNN
F 3 "" H 3900 2550 50  0001 C CNN
	1    3900 2350
	0    1    1    0   
$EndComp
$Comp
L SW_Push SW2
U 1 1 5ACAD5C1
P 4600 2350
F 0 "SW2" H 4650 2450 50  0000 L CNN
F 1 "SW_Push" H 4600 2250 50  0000 C CNN
F 2 "Buttons_Switches_THT:SW_PUSH-12mm" H 4600 2550 50  0001 C CNN
F 3 "" H 4600 2550 50  0001 C CNN
	1    4600 2350
	0    1    1    0   
$EndComp
$Comp
L CONN_01X04 J1
U 1 1 5ACAD6D5
P 2550 2200
F 0 "J1" H 2550 2450 50  0000 C CNN
F 1 "CONN_01X04" V 2650 2200 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04_Pitch2.54mm" H 2550 2200 50  0001 C CNN
F 3 "" H 2550 2200 50  0001 C CNN
	1    2550 2200
	-1   0    0    1   
$EndComp
Wire Wire Line
	4600 1500 4600 2150
Wire Wire Line
	3900 1500 3900 2150
$Comp
L GND #PWR01
U 1 1 5ACADD58
P 3900 3100
F 0 "#PWR01" H 3900 2850 50  0001 C CNN
F 1 "GND" H 3900 2950 50  0000 C CNN
F 2 "" H 3900 3100 50  0001 C CNN
F 3 "" H 3900 3100 50  0001 C CNN
	1    3900 3100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 5ACADD79
P 4600 3100
F 0 "#PWR02" H 4600 2850 50  0001 C CNN
F 1 "GND" H 4600 2950 50  0000 C CNN
F 2 "" H 4600 3100 50  0001 C CNN
F 3 "" H 4600 3100 50  0001 C CNN
	1    4600 3100
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 5ACADD90
P 3650 2400
F 0 "C1" H 3675 2500 50  0000 L CNN
F 1 "0.1uF" H 3675 2300 50  0000 L CNN
F 2 "Capacitors_THT:C_Disc_D4.3mm_W1.9mm_P5.00mm" H 3688 2250 50  0001 C CNN
F 3 "" H 3650 2400 50  0001 C CNN
	1    3650 2400
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 5ACADDC3
P 4300 2400
F 0 "C2" H 4325 2500 50  0000 L CNN
F 1 "0.1uF" H 4325 2300 50  0000 L CNN
F 2 "Capacitors_THT:C_Disc_D4.3mm_W1.9mm_P5.00mm" H 4338 2250 50  0001 C CNN
F 3 "" H 4300 2400 50  0001 C CNN
	1    4300 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3650 2250 3650 2150
Wire Wire Line
	3650 2150 3900 2150
Wire Wire Line
	4300 2250 4300 2150
Wire Wire Line
	4300 2150 4600 2150
Wire Wire Line
	3900 3100 3900 2550
Wire Wire Line
	3650 2550 3650 2650
Wire Wire Line
	3650 2650 3900 2650
Connection ~ 3900 2650
Wire Wire Line
	4300 2550 4300 2650
Wire Wire Line
	4300 2650 4600 2650
Wire Wire Line
	4600 2550 4600 3100
Connection ~ 4600 2650
Text Label 3900 1500 0    60   ~ 0
SW_A
Text Label 4600 1500 0    60   ~ 0
SW_B
Wire Wire Line
	2750 2050 3000 2050
Wire Wire Line
	2750 2250 3000 2250
Wire Wire Line
	2750 2350 2900 2350
Wire Wire Line
	2900 2150 2900 2600
Connection ~ 2900 2350
Wire Wire Line
	2750 2150 2900 2150
Text Label 3000 2050 0    60   ~ 0
SW_A
Text Label 3000 2250 0    60   ~ 0
SW_B
$Comp
L GND #PWR03
U 1 1 5ACAE218
P 2900 2600
F 0 "#PWR03" H 2900 2350 50  0001 C CNN
F 1 "GND" H 2900 2450 50  0000 C CNN
F 2 "" H 2900 2600 50  0001 C CNN
F 3 "" H 2900 2600 50  0001 C CNN
	1    2900 2600
	1    0    0    -1  
$EndComp
$EndSCHEMATC
