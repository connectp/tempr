This is working software that has a robot and some lights and food. To run it, you need nanogui.h which you can include from here https://github.com/memononen/nanovg/blob/master/src/nanovg.h and learn about it from https://nanogui.readthedocs.io/en/latest/api/library_root.html

your task is to do the following:

1. Create a light sensor for the robot that senses the light and reacts like a Braitenberg vehicle that is either it fears light or explores light. This light sensor should be an entity (object) that is on the side of every robot

2. Make sure half the robots exhibit fear and half explore the lights.

2. Create a food sensor for the robot that senses a hunger level of each robot. When first appearing, robots are not hungry. After about 30 seconds, robots get hungry and then they need to sense food.  The food sensor is an object that will be on the other side. 

3. If a robot gets within 5 pixels or less of food, it is considered to have consumed some food and it is no longer hungry. This can happen regardless of whether or not it is sensing food.

4. At the point of food consumption, the robot is no longer hungry, but it will be hungry again after 30 seconds.

5. If a robot is REALLY hungry, it should ignore the lights and just sense food. REALLY hungry means that it's been 2 minutes since its last meal.

6. The number of robots is split -- 5 fear lights and 5 explore lights (i.e. positive/direct, and negative/crossed respectively).

7. Add a GUI element in the menu of simulation control that turns food on or off.


