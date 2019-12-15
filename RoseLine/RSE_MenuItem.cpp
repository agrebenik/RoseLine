#include "RSE_MenuItem.h"

RSE_MenuItem::RSE_MenuItem() { }

RSE_MenuItem::RSE_MenuItem(string sdata) {
	data = sdata;
}

RSE_MenuItem* RSE_MenuItem::getLink(ENM_Direction direction) {
	RSE_MenuItem* directionLink = getItemFromDirection(direction);
	if (directionLink == nullptr || direction == NoDirection) {
		throw new exception("Invalid direction passed into [getLink] function");
	}
	return directionLink;
}

void RSE_MenuItem::linkItem(RSE_MenuItem* item, ENM_Direction direction) {
	if (direction == NULL) {
		throw new exception("Null direction passed into [linkItem] function");
	}
	RSE_MenuItem* directionLink = getItemFromDirection(direction);
	directionLink = item; // relink our item

}

RSE_MenuItem* RSE_MenuItem::getItemFromDirection(ENM_Direction direction) {
	if (direction == NULL) {
		throw new exception("Null direction passed into [getItemFromDirection] function");
	}
	switch (direction)
	{
		case Left: {
			return _left;
		}
		case Right: {
			return _right;
		}
		case Up: {
			return _up;
		}
		case Down: {
			return _down;
		}
		default: {
			return nullptr;
		}
	}
}

RSE_MenuItem::~RSE_MenuItem() { }
