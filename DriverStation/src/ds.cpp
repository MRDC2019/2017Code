#include <SFML/Graphics.hpp>
#include <iostream>
#include "gui/gui.h"
#include "gui/appRes.h"
#include "utils/Comms.h"
#include "robot/Robot.h"
#include "robot/RobotIO.h"
using namespace sf;

AppRes* appRes;

int main(){
	RenderWindow window(VideoMode(600, 588), "Transfarmers Driver Station");
	window.setFramerateLimit(60);

	AppRes res;
	appRes = &res;
	GUI gui;
	Comms comms;
	Robot robot;
    comms.begin();

	while(window.isOpen()){
		Event event;
		while(window.pollEvent(event)){
			if(event.type == Event::Closed)
				window.close();
			if(event.type == Event::Resized){
				Vector2u size = window.getSize();
				View view = View(FloatRect(0.0f, 0.0f, (float)size.x, (float)size.y));
				window.setView(view);
			}
		}

		if(comms.maintainConnection()){
			if(comms.read()){
				robot.periodic(comms.getRobotIn(), comms.getRobotOut());
				comms.write();
			}
		}

		gui.update(window);
		window.clear(Color(24,24,24));
		window.draw(gui);
		window.display();
	}

	return 0;
}
