#ifndef __ROBOT_FOLLOWER__H
#define __ROBOT_FOLLOWER__H 

#include "enviro.h"
#include <string>

using namespace enviro;
using namespace std;

/*MyRobotFollower 
* Creates agent that will be chasing Leader based on Train Coordinator position instructions
*/
class MyRobotFollower : public Process, public AgentInterface {

    public:
    MyRobotFollower() : Process(), AgentInterface() {}

    void init();
    void start() {}
    void update(); 
    void stop() {}

    private:
        double x_pos = 0, y_pos = 0; //robot x y position
        string train_coordinator_ch; //unique channel string used to listen to train coordinator instructions

};
/*RobotFollower 
* Adds MyRobotFollower to process manager.
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

/*! Calculates error between the current robot position and the goal position
 *  \param robot_x The robot's X position
 *  \param robot_y The robot's Y position
 *  \param goal_x The goal's X position
 *  \param goal_y The goal's Y position
 *  \returns A double representing the absolute value error between the robot position and goal position
 */
double robot_pos_error(double robot_x, double robot_y, double goal_x, double goal_y); 

DECLARE_INTERFACE(RobotFollower)

#endif