#include <iostream>
#include "designer.h"




int main() {

	int cameraX, cameraY, totalX;

	std::cout << "Camera X.......: "; std::cin >> cameraX;
	std::cout << "Camera Y.......: "; std::cin >> cameraY;
	std::cout << "Total Screen X.: "; std::cin >> totalX;


	designer *desingArea = new designer(cameraX, cameraY, totalX);
	desingArea->createScreen();
	desingArea->ScreenEvent();


}
