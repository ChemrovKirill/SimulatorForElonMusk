#include "Usart.h"

void GetReady() {

	hSerial = ::CreateFile(sPortName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hSerial == INVALID_HANDLE_VALUE)
	{
		if (GetLastError() == ERROR_FILE_NOT_FOUND)
		{
			std::cout << "serial port does not exist.\n";
		}
		std::cout << "some other error occurred.\n";
	}


	DCB dcbSerialParams = { 0 };
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	if (!GetCommState(hSerial, &dcbSerialParams))
	{
		std::cout << "getting state error\n";
	}
	dcbSerialParams.BaudRate = CBR_115200;
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.StopBits = ONESTOPBIT;
	dcbSerialParams.Parity = NOPARITY;
	if (!SetCommState(hSerial, &dcbSerialParams))
	{
		std::cout << "error setting serial port state\n";
	}

	COMMTIMEOUTS tout;
	GetCommTimeouts(hSerial, &tout);
	tout.ReadIntervalTimeout = 1;
	tout.ReadTotalTimeoutConstant = 1;
	tout.ReadTotalTimeoutMultiplier = 1;
	tout.WriteTotalTimeoutConstant = 1;
	tout.WriteTotalTimeoutMultiplier = 1;
	SetCommTimeouts(hSerial, &tout);
	//cout << dwSize << " Bytes in string. " << dwBytesWritten << " Bytes sended. " << endl;

	std::cout << "STM_32 is ready" << std::endl;
} 

void ReadCOM(Lander_Parametr& par)
{
	DWORD iSize;
	unsigned char sReceivedChar;

	ReadFile(hSerial, &sReceivedChar, 1, &iSize, 0);  // получаем 1 байт
	if (iSize > 0) { // если что-то принято, выводим
		//std::cout << sReceivedChar << std::endl;
	}
	else sReceivedChar = 0;
	par.data_decode(sReceivedChar);
}

void SendCOM(std::string str) {
	char* data;		// строка для передачи
	data = new char[str.size()];

	for (int i = 0; i < str.size(); ++i) {
		data[i] = str[i];
	}

	DWORD dwSize = sizeof(data);   // размер этой строки
	DWORD dwBytesWritten;    // тут будет количество собственно переданных байт
	LPOVERLAPPED ov;

	BOOL iRet = WriteFile(hSerial, data, dwSize, &dwBytesWritten, NULL);

	delete[] data;
}

void USART(Lander_Parametr& par, float v) {
	std::ostringstream ss;
	if (v < 100) { ss << 1 << 0 << 0 << 0 << 0; }

	if (v < 1000) { ss << 1 << 0 << v; }
	else { ss << 0 << v; }
	std::string s(ss.str());
	SendCOM(s);
	ReadCOM(par);
}

Lander_Parametr::Lander_Parametr() {
	en_stat[6] = { 0 };

	vel = Vector2f(0, 0);
	acc = Vector2f(0, 0);
}

void Lander_Parametr::data_update(const Ship* l) {
	vel = l->GetVelocity();
	acc = l->GetAcceleration();
}

float Lander_Parametr::data_to_send() {
	return sqal(vel);
}

void Lander_Parametr::data_decode(unsigned char message) {
	if (message >> 7 == 1) {
		if (16 == (message & 16)) { en_stat[1] = 1; }
		else { en_stat[1] = 0; }
		if (32 == (message & 32)) { en_stat[0] = 1; }
		else { en_stat[0] = 0; }
		if (64 == (message & 64)) {	en_stat[2] = 1; }
		else { en_stat[2] = 0; }
	}
}