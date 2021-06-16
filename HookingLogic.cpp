#include "MinHook.h"
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>

#pragma comment(lib,"Minhook.x86.lib")

__declspec(noinline) int showNumber(int number,int number2,double number3,double number4,float number5)
{
	std::cout << "My number is :" << number << " " << number2 << " " << number3 << " " << number4 << " " << number5 << std::endl;
	return number;
}

using fn_show_number_t = int(*)(int, int, double, double, float);
fn_show_number_t original_function;

int hk_show_number(int number, int number2, double number3, double number4, float number5)
{
	std::cout << "A" << std::endl;
	return original_function(1000, 1000, 1000, 1000, 1000);
}


int main(){
	
	showNumber(25, 15, 99.55, 19.95, 82.25);
	MH_Initialize();
	MH_CreateHook(showNumber, hk_show_number, (LPVOID*)&original_function);
	MH_EnableHook(showNumber);
	std::cout << showNumber(1,1,1,1,1);
	MH_DisableHook(showNumber);
	MH_Uninitialize();

}		