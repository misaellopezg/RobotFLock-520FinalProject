#ifndef __ROBOT_LEADER__H
#define __ROBOT_LEADER__H 

#include "enviro.h"

using namespace enviro;
using namespace std;

/*MyRobotLeader
* Used to create robot leader agent that will be following a target
*/
class MyRobotLeader : public Process, public AgentInterface {

    public:
    MyRobotLeader() : Process(), AgentInterface() {}

    void init(); 
    void start() {}
    void update(); 
    void stop() {}

    private:
        double x_pos = 0, y_pos = 0; 
        double robot_sensor;
        double sweep_rotation = 2.0; 
        double pos_lim_x = 400;
        double pos_lim_y = 250;
        int sensor_magnitude = 0, prev_sensor_magnitude = 0; 
};

/*RobotLeader
* Adds robot leader agent to process manager
*/
class RobotLeader : public Agent {
    public:
    RobotLeader(json spec, World& world) : Agent(spec, world) 
    {
        add_process(c);
    }
    private:
        MyRobotLeader c;
};

DECLARE_INTERFACE(RobotLeader)

#endif