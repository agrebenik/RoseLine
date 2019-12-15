
#include "RSE_PhysicsObject.h"

#include <cmath>
#include <math.h>
#include <iostream>

#include "ENM_Direction.h"
#include "ENM_CollisionType.h"
#include "RSE_MAN_GameObject.h"
#include "ENM_CollisionAction.h"


using namespace std;

int RSE_PhysicsObject::update() {	
	if (!rigid) {
		if (falling && gravity) {
			bump(0.0, GRAVITY);
			// if object is falling update by related gravity acceleration vector
		}

		// before movement remove collision index from grid
		int sq = RSE_MAN_GameObject::SQUARE_SIZE;
		float xpos = position->x - w / 2;
		float ypos = position->y - h / 2;
		int dw = floor((xpos + w) / sq) - floor(xpos / sq);
		int dh = floor((ypos + h) / sq) - floor(ypos / sq);
		for (int y = 0; y < dh; y++) {
			for (int x = 0; x < dw; x++) {
				int realX = x + floor(xpos / sq);
				int realY = y + floor(ypos / sq);
				float collisionArrayRows = ceil(RSE_MAN_GameObject::SCREEN_HEIGHT / RSE_MAN_GameObject::SQUARE_SIZE);
				float collisionArrayColumns = ceil(RSE_MAN_GameObject::SCREEN_WIDTH / RSE_MAN_GameObject::SQUARE_SIZE);
				if (realX > collisionArrayColumns - 1 || realX < 0) {
					continue;
				}
				if (realY > collisionArrayRows - 1 || realY < 0) {
					continue;
				}
				if (RSE_MAN_GameObject::collisionArray[realY][realX] == index) {
					RSE_MAN_GameObject::collisionArray[realY][realX] = 0;
				}
			}
		}

		// move object using movemenet vector
		position->x += movementVector->dx;
		position->y += movementVector->dy;

		float dx = movementVector->dx;
		float dy = movementVector->dy;

		bool moving = dx != 0 && dy != 0;

		// if the object isnt moving there is no point in checking collisions
		int collisions = 0;
		if (moving || true) {

			// some detection will be ignored based on what movement is happening
			// IE: if we arent moving down we dont need to care about reactions with a downwards facing platform

			xpos = position->x - w / 2;
			ypos = position->y - h / 2;
			dw = floor((xpos + w) / sq) - floor(xpos / sq);
			dh = floor((ypos + h) / sq) - floor(ypos / sq);
			int reaction = None;
			int reactant = 0;
			int mainCollisionValue = 0;
			for (int y = 0; y < dh; y++) {
				for (int x = 0; x < dw; x++) {
					int realX = x + floor(xpos / sq);
					int realY = y + floor(ypos / sq);
					float collisionArrayRows = ceil(RSE_MAN_GameObject::SCREEN_HEIGHT / RSE_MAN_GameObject::SQUARE_SIZE);
					float collisionArrayColumns = ceil(RSE_MAN_GameObject::SCREEN_WIDTH / RSE_MAN_GameObject::SQUARE_SIZE);
					if (realX > collisionArrayColumns - 1 || realX < 0) {
						continue;
					}
					if (realY > collisionArrayRows - 1 || realY < 0) {
						continue;
					}
					int v = RSE_MAN_GameObject::collisionArray[realY][realX];
					// if non zero index intersection occurs we have a collision
					if (v != 0 && v != index) {
						int upVal = y == realY ? 0 : RSE_MAN_GameObject::collisionArray[realY - 1][realX];
						int downVal = y == collisionArrayColumns - 1 ? 0 : RSE_MAN_GameObject::collisionArray[realY + 1][realX];
						int leftVal = x == realX ? 0 : RSE_MAN_GameObject::collisionArray[realY][realX - 1];
						int rightVal = x == collisionArrayRows - 1 ? 0 : RSE_MAN_GameObject::collisionArray[realY][realX + 1];

						// proccess the collision
						int collisionValue = getCollisionValue(v, upVal, downVal, leftVal, rightVal);
						int expectedReaction = getPriorityFromCollisionValue(collisionValue);
						if (expectedReaction > reaction) {
							reaction = expectedReaction;
							reactant = v;
							mainCollisionValue = collisionValue;
							/*cout << " " << expectedReaction << " = = =\n";
							cout << "     " << upVal << "\n";
							cout << "   " << leftVal << " " << v << " " << rightVal << "\n";
							cout << "     " << downVal << "\n\n";*/
						}
					}
					else {
						RSE_MAN_GameObject::collisionArray[realY][realX] = index;
					}
				}
			}
			if (reaction != None && reactant != 0) {
				collisions++;
				//cout << " Reacting to #" << reactant << " with a " << reaction << " reaction \n";
				RSE_PhysicsObject* ptr_reactantObj = (RSE_PhysicsObject*)RSE_MAN_GameObject::pObjectsArray[reactant-1];
				// if reaction is (RL limit)
				float bounce_this = 0.5f;
				float bounce_that = 0.5f;
				int action = getActionFromValueAndPriority(mainCollisionValue, reaction);
				if (action == LimitLeft || action == LimitRight) {
					movementVector->dx *= -bounce_this;
					if (!ptr_reactantObj->rigid) {
						ptr_reactantObj->movementVector->dx *= -bounce_that;
					}
				}
				if (action == LimitUp || action == LimitDown) {
					movementVector->dy *= -bounce_this;
					if (!ptr_reactantObj->rigid) {
						ptr_reactantObj->movementVector->dy *= -bounce_that;
					}
				}
				if ((action == LimitLeft + LimitDown) ||
					(action == LimitLeft + LimitUp) ||
					(action == LimitRight + LimitDown) ||
					(action == LimitRight + LimitUp)) {
					movementVector->dy *= -bounce_this;
					movementVector->dx *= -bounce_this;
					if (!ptr_reactantObj->rigid) {
						ptr_reactantObj->movementVector->dy *= -bounce_that;
					}
					if (!ptr_reactantObj->rigid) {
						ptr_reactantObj->movementVector->dx *= -bounce_that;
					}
				}
			}
		}
		falling = collisions == 0;
	}

	// restrict object movements to limits of colisions
	// if no colisions object must be mid air
	return 0;
}

int RSE_PhysicsObject::getDirectionsToLimit(int d1=NoDirection, int d2=NoDirection, int d3=NoDirection, int d4=NoDirection) {
	float upChange = -movementVector->dy;
	float downChange = movementVector->dy;
	float leftChange = -movementVector->dx;
	float rightChange = movementVector->dx;
	bool left = (d1 == Left || d2 == Left || d3 == Left || d4 == Left);
	bool right = (d1 == Right || d2 == Right || d3 == Right || d4 == Right);
	bool up = (d1 == Up || d2 == Up || d3 == Up || d4 == Up);
	bool down = (d1 == Down || d2 == Down || d3 == Down || d4 == Down);
	if (up && down && left && right) {
		float maxVal = upChange;
		if (downChange > maxVal) {
			maxVal = downChange;
		}
		if (leftChange > maxVal) {
			maxVal = leftChange;
		}
		if (rightChange > maxVal) {
			maxVal = rightChange;
		}
		return (maxVal == upChange ? LimitUp : LimitNone) + 
			   (maxVal == downChange ? LimitDown : LimitNone) + 
			   (maxVal == leftChange ? LimitLeft : LimitNone ) + 
			   (maxVal == rightChange ? LimitRight : LimitNone);
	}
	else if (up && down && right) {
		if (upChange > downChange && upChange > rightChange) {
			return LimitUp;
		}
		else if (downChange > upChange && downChange > rightChange) {
			return LimitDown;
		}
		else if (rightChange > upChange && rightChange > downChange) {
			return LimitRight;
		}
		else if (upChange == rightChange && upChange > downChange) {
			return LimitUp + LimitRight;
		}
		else if (downChange == rightChange && downChange > upChange) {
			return LimitDown + LimitRight;
		}
	}
	else if (up && down && left) {
		if (upChange > downChange && upChange > leftChange) {
			return LimitUp;
		}
		else if (downChange > upChange && downChange > leftChange) {
			return LimitDown;
		}
		else if (leftChange > upChange && leftChange > downChange) {
			return LimitLeft;
		}
		else if (upChange == leftChange && upChange > downChange) {
			return LimitUp + LimitLeft;
		}
		else if (downChange == leftChange && downChange > upChange) {
			return LimitDown + LimitLeft;
		}
	}
	else if (left && right && up) {
		if (leftChange > rightChange && leftChange > upChange) {
			return LimitLeft;
		}
		else if (rightChange > leftChange && rightChange > upChange) {
			return LimitRight;
		}
		else if (upChange > leftChange && upChange > rightChange) {
			return LimitUp;
		}
		else if (leftChange == upChange && leftChange > rightChange) {
			return LimitLeft + LimitUp;
		}
		else if (rightChange == upChange && rightChange > leftChange) {
			return LimitRight + LimitUp;
		}
	}
	else if (left && right && down) {
		if (leftChange > rightChange && leftChange > downChange) {
			return LimitLeft;
		}
		else if (rightChange > leftChange && rightChange > downChange) {
			return LimitRight;
		}
		else if (downChange > leftChange && downChange > rightChange) {
			return LimitDown;
		}
		else if (leftChange == downChange && leftChange > rightChange) {
			return LimitLeft + LimitDown;
		}
		else if (rightChange == downChange && rightChange > leftChange) {
			return LimitRight + LimitDown;
		}
	}
	else if (up && left) {
		if (upChange > leftChange) {
			return LimitUp;
		}
		else if (upChange < leftChange) {
			return LimitLeft;
		}
		else if (upChange == leftChange) {
			return LimitUp + LimitLeft;
		}
	}
	else if (up && right) {
		if (upChange > rightChange) {
			return LimitUp;
		}
		else if (upChange < rightChange) {
			return LimitRight;
		}
		else if (upChange == rightChange) {
			return LimitUp + LimitRight;
		}
	}
	else if (down && left) {
		if (downChange > leftChange) {
			return LimitDown;
		}
		else if (downChange < leftChange) {
			return LimitLeft;
		}
		else if (downChange == leftChange) {
			return LimitDown + LimitLeft;
		}
	}
	else if (down && right) {
		if (downChange > rightChange) {
			return LimitDown;
		}
		else if (downChange < rightChange) {
			return LimitRight;
		}
		else if (downChange == rightChange) {
			return LimitDown + LimitRight;
		}
	}
	else if (down && up) {
		if (downChange > upChange) {
			return LimitDown;
		}
		else if (downChange < upChange) {
			return LimitUp;
		}
		else if (downChange == upChange) {
			return LimitNone;
		}
	}
	else if (left && right) {
		if (leftChange > rightChange) {
			return LimitLeft;
		}
		else if (leftChange < rightChange) {
			return LimitRight;
		}
		else if (leftChange == rightChange) {
			return LimitNone;
		}
	}
	else if (left) {
		return LimitLeft;
	}
	else if (right) {
		return LimitRight;
	}
	else if (down) {
		return LimitDown;
	}
	else if (up) {
		return LimitUp;
	}
	return LimitNone;
}

int RSE_PhysicsObject::getActionFromValueAndPriority(int value, int priority) {
	switch (priority) {
		case Direct:
			if (value == Up + Down + Right) {
				return LimitRight;
			} 
			else if (value == Up + Down + Left) {
				return LimitLeft;
			}
			else if (value == Left + Right + Up) {
				return LimitUp;
			}
			else if (value == Left + Right + Down) {
				return LimitDown;
			}
			break;
		case Corner:
			if (value == Up + Right) {
				return getDirectionsToLimit(Up, Right);
			}
			else if (value == Up + Left) {
				return getDirectionsToLimit(Up, Left);
			}
			else if (value == Down + Right) {
				return getDirectionsToLimit(Down, Right);
			}
			else if (value == Down + Left) {
				return getDirectionsToLimit(Down, Left);
			}
			break;
		case Bar:
			if (value == Up + Down) {
				return getDirectionsToLimit(Left, Right);
			}
			else if (value == Left + Right) {
				return getDirectionsToLimit(Up, Down);
			}
			break;
		case Double:
			if (value == Up) {
				return getDirectionsToLimit(Up, Left, Right);
			}
			if (value == Down) {
				return getDirectionsToLimit(Down, Left, Right);
			}
			if (value == Left) {
				return getDirectionsToLimit(Left, Up, Down);
			}
			if (value == Right) {
				return getDirectionsToLimit(Right, Up, Down);
			}
 			break;
		case Single:
			break;
		default:
			break;
	};
	return LimitNone;
}

int RSE_PhysicsObject::getPriorityFromCollisionValue(int value) {
	float dx = movementVector->dx;
	float dy = movementVector->dy;
	bool movingRight = dx > 0;
	bool movingLeft = dx < 0;
	bool movingUp = dy < 0;
	bool movingDown = dy > 0;
	if ((value == Up + Down + Left) && movingLeft) {
		return Direct;
	}
	else if ((value == Up + Down + Right) && movingRight) {
		return Direct;
	}
	else if ((value == Right + Left + Up) && movingUp) {
		return Direct;
	}
	else if ((value == Right + Left + Down) && movingDown) {
		return Direct;
	}
	else if ((value == Down + Right) && (movingRight || movingDown)) {
		return Corner;
	}
	else if ((value == Down + Left) && (movingLeft || movingDown)) {
		return Corner;
	}
	else if ((value == Up + Right) && (movingRight || movingUp)) {
		return Corner;
	}
	else if ((value == Up + Left) && (movingLeft || movingUp)) {
		return Corner;
	}
	else if ((value == Up + Down) && (movingRight || movingLeft)) {
		return Bar;
	}
	else if ((value == Left + Right) && (movingUp || movingDown)) {
		return Bar;
	}
	else if (value == Left && (movingDown || movingUp || movingLeft)) {
		return Double;
	}
	else if (value == Right && (movingDown || movingUp || movingRight)) {
		return Double;
	}
	else if (value == Up && (movingLeft || movingRight || movingUp)) {
		return Double;
	}
	else if (value == Down && (movingLeft || movingRight || movingDown)) {
		return Double;
	}
	else if (value == 0) {
		return Single;
	}
	return None;
}

int RSE_PhysicsObject::getCollisionValue(int otherIndex, int upVal, int downVal, int leftVal, int rightVal) {
	bool eU = upVal == otherIndex;
	bool eD = downVal == otherIndex;
	bool eL = leftVal == otherIndex;
	bool eR = rightVal == otherIndex;
	return (eU ? Up : 0) + (eD ? Down : 0) + (eL ? Left : 0) + (eR ? Right : 0);
}

bool RSE_PhysicsObject::collidesWith(RSE_PhysicsObject* ptr_pobj) {
	return collision->collidesWith(ptr_pobj->collision);
}

void RSE_PhysicsObject::bump(float dx, float dy) {
	RSE_Vector* ptr_vec = new RSE_Vector(dx, dy);
	movementVector->operator+=(ptr_vec);
	delete ptr_vec;
}

void RSE_PhysicsObject::reset() {
	movementVector->dx = 0;
	movementVector->dy = 0;
}

void RSE_PhysicsObject::setCollision() {
	int sq = RSE_MAN_GameObject::SQUARE_SIZE;
	float xpos = position->x - w / 2;
	float ypos = position->y - h / 2;
	int dw = floor((xpos + w) / sq) - floor(xpos / sq);
	int dh = floor((ypos + h) / sq) - floor(ypos / sq);
	for (int y = 0; y < dh; y++) {
		for (int x = 0; x < dw; x++) {
			int realX = x + floor(xpos / sq);
			int realY = y + floor(ypos / sq);
			float collisionArrayRows = ceil(RSE_MAN_GameObject::SCREEN_HEIGHT / RSE_MAN_GameObject::SQUARE_SIZE);
			float collisionArrayColumns = ceil(RSE_MAN_GameObject::SCREEN_WIDTH / RSE_MAN_GameObject::SQUARE_SIZE);
			if (realX > collisionArrayColumns - 1 || realX < 0) {
				continue;
			}
			if (realY > collisionArrayRows - 1 || realY < 0) {
				continue;
			}
			int value = RSE_MAN_GameObject::collisionArray[realY][realX];
			if (value == 0) {
				RSE_MAN_GameObject::collisionArray[realY][realX] = index;
			}
		}
	}
}

RSE_PhysicsObject::RSE_PhysicsObject(float x, float y, string imageId) : RSE_GameObject(x, y, imageId) {
	movementVector = new RSE_Vector(0, 0);
}


RSE_PhysicsObject::RSE_PhysicsObject(float x, float y) : RSE_GameObject(x, y) {
	movementVector = new RSE_Vector(0, 0);
}

RSE_PhysicsObject::~RSE_PhysicsObject() { }