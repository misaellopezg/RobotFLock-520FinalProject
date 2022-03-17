#ifndef __ROBOT_LEADER__H
#define __ROBOT_LEADER__H 

#include "enviro.h"
#include <vector>
#include <cmath>

using namespace enviro;
using namespace std;

/*MyRobotController
*Class used to create agent that follows a path.*/
class MyRobotController : public Process, public AgentInterface {

    public:
    MyRobotController() : Process(), AgentInterface() {}

    void init(); 
    void start() {}
    void update();
    void stop() {}

    private:

        vector< pair<int, int>> robot_path; //vector that contains x y coordinates of path to follow
        pair<int, int> robot_goal; // x y coordinate robot will be targetting
        int path_index = 0; // path index used to traverse robot_path vector
        double x_pos = 0, y_pos = 0; // robot x and y position

};

/*MyRobot
*Class used to add agent to proces.*/
class MyRobot : public Agent {
    public:
    MyRobot(json spec, World& world) : Agent(spec, world) 
    {
        add_process(c);
    }
    private:
    MyRobotController c;
};

/*! Get path for robot to traverse
 *  File contains the following format: 
 *  x coordinate, y coordinate \n
 *  \param filepath The file path for the robot's path to follow
 *  \returns A vector containing a pair of ints representing map coordinates
 */
vector<pair <int,int>> get_file_robot_path(const string filepath);

/*! Calculates error between the current robot position and the goal position
 *  \param robot_x The robot's X position
 *  \param robot_y The robot's Y position
 *  \param goal_x The goal's X position
 *  \param goal_y The goal's Y position
 *  \returns A double representing the absolute value error between the robot position and goal position
 */
double robot_pos_error(double robot_x, double robot_y, double goal_x, double goal_y); 

DECLARE_INTERFACE(MyRobot)

#endif