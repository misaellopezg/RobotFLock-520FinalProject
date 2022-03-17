#ifndef __ROBOT_FOLLOWER__H
#define __ROBOT_FOLLOWER__H 

#include "enviro.h"
#include <string>

using namespace enviro;
using namespace std;

/*MyRobotFollower 
* Creates agent that will be chasing Leader based on leader position instructions
*/
class MyRobotFollower : public Process, public AgentInterface {

    public:
    MyRobotFollower() : Process(), AgentInterface() {}

    void init();
    void start() {}
    void update(); 
    void stop() {}

    private:
        double x_pos = 0, y_pos = 0, theta = 0; // robot x y theta info
        double oscil_accum = 0; // oscillation accumulation value
        double oscil_accum_min = -30; // min oscillation value
        double oscil_accum_max = 30; // max oscillation value
        bool tick = 1; // used to tick oscillation up or down
        string leader_ch; // channel used to send info to leader
        string folower_ch; // channel used to listen to leader info

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

/*! Calculates agent new x value to be offset from leader
 *  \param f_offset The distance from leader-agent origin
 *  \param rx The robot's current x position
 *  \param rtheta leader's theta
 *  \returns new agent x position
 */
double x_offset(double f_offset, double rx, double rtheta); 

/*! Calculates agent new y value to be offset from leader
 *  \param f_offset The distance from leader-agent origin
 *  \param ry The robot's current x position
 *  \param rtheta leader's theta
 *  \returns new agent y position
 */
double y_offset(double f_offset, double ry, double rtheta); 

DECLARE_INTERFACE(RobotFollower)

#endif