#include "Inputs.h"



Inputs::Inputs()
{
	keys = new KeyVal[sf::Keyboard::Key::KeyCount];
	Reset();
}


Inputs::~Inputs()
{
	delete[] keys;
	keys = nullptr;
}

//KEYBOARD INPUT
void Inputs::Press(sf::Keyboard::Key key) {
	keys[key].isPressed = true;
	keys[key].onPressed = true;
	keys[key].onReleased = false;
}

void Inputs::Release(sf::Keyboard::Key key) {
	keys[key].isPressed = false;
	keys[key].onPressed = false;
	keys[key].onReleased = true;
}

void Inputs::Update() {	//called at the end of update to reset onpressed state
	for (int i(0); i < sf::Keyboard::Key::KeyCount; ++i) {
		keys[i].onPressed = false;
		keys[i].onReleased = false;
	}
}

void Inputs::Reset() {
	for (int i(0); i < sf::Keyboard::Key::KeyCount; ++i) {
		keys[i].isPressed = false;
		keys[i].onPressed = false;
		keys[i].onReleased = false;
	}
}

bool Inputs::onPressed(sf::Keyboard::Key k) {
	return keys[k].onPressed;
}
bool Inputs::onReleased(sf::Keyboard::Key k) {
	return keys[k].onReleased;
}
bool Inputs::isPressed(sf::Keyboard::Key k) {
	return keys[k].isPressed;
}

////MOUSE INPUT
//void Inputs::Press(sf::Event::MouseButtonEvent mouseEvent) {
//	if (mouseEvent.button == sf::Mouse::Button::Left)
//	{	//inputs LMB onclicked
//
//	}
//	else {
//		if (mouseEvent.button == sf::Mouse::Button::Right) {
//			//inputs RMB onclicked
//
//		}
//
//	}
//}
