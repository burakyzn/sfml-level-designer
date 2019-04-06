#include <iostream>
#include "designer.h"
#include "firstSetting.h"

int main() {
	//Page Setting Class
	firstSetting *screenSetting = new firstSetting();
	int* setting = screenSetting->show();

	//Designer Screen Class
	designer *desingArea = new designer(setting);
	desingArea->createScreen();
	desingArea->ScreenEvent();
}
