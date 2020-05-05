#pragma once
#include <SFML/Graphics.hpp>

#include <windows.h>
#include "iostream"
#include "MathFunction.h"
#include "Ship.h"

#include <SDKDDKVer.h>

#include <stdio.h>
#include <tchar.h>

#include<TCHAR.H>

#include <sstream>

static HANDLE hSerial;

static HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

static LPCTSTR sPortName = "COM4";

struct Lander_Parametr {
public:
	Lander_Parametr();

	bool en_stat[6];
	sf::Vector2f vel;
	sf::Vector2f acc;

	bool GetP(int x) { return en_stat[x]; }
	void data_update(const Ship* l);
	float data_to_send();
	void data_decode(unsigned char message);
};

void GetReady();

void ReadCOM(Lander_Parametr& par);
void SendCOM(std::string str);
void USART(Lander_Parametr& par ,float x);