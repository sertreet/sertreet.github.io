#include <iostream>
#include "Robot.h"
using namespace std;

void displayRobotInfo(const Robot& robot) {
	int x, y, b, p; 
	robot.getStatus(x, y, b);
	p = robot.getPower();
	string name;
	name = robot.getName();
	cout << "robot " << name;
	cout << ": position (" << x << "," << y << ")";
	cout << ", battery level " << b;
	cout << ", power " << p << endl;
}

int main() {
	Robot robot1("test1");
	Robot robot2("test2", 50, 50);
	Robot robot3("test3", 25, 25, 23, 3);
	displayRobotInfo(robot1);
	displayRobotInfo(robot2);
	displayRobotInfo(robot3);
	robot1.moveDown();
	displayRobotInfo(robot1);
	robot1.moveUp();
	displayRobotInfo(robot1);
	/*
	YOUR CODE HERE
	*/
}



