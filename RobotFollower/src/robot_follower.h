#ifndef __ROBOT_FOLLOWER__H
#define __ROBOT_FOLLOWER__H 

#include "enviro.h"

using namespace enviro;
using namespace std;

/*MyRobotFollower 
* Creates agent that will be targeting leader using 4 sensors. 
*/
class MyRobotFollower : public Process, public AgentInterface {

    public:
    MyRobotFollower() : Process(), AgentInterface() {}

    void init(); 
    void start() {}
    void update(); 
    void stop() {}

    private:
        double x_pos = 0, y_pos = 0; //robot x and y position
        double robot_sensor; // used for sensor readings
        double sweep_rotation = 2.0; //fixed sweep rotation speed
        int sensor_magnitude = 0, prev_sensor_magnitude = 0; //used to store current and previous sensor readings magnitues
};

/*!RobotFollower adds agent to process. 
*/
class RobotFollower : public Agent {
    public:
    RobotFollower(json spec, World& world) : Agent(spec, world) 
    {
        add_process(c);
    }
    private:
        MyRobotFollower c;
};

DECLARE_INTERFACE(RobotFollower)

#endif