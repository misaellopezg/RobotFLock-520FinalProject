#ifndef __ROBOT_LEADER__H
#define __ROBOT_LEADER__H 

#include "enviro.h"
#include <vector>
#include <cmath>
using namespace enviro;
using namespace std;


class MyRobotLeader : public Process, public AgentInterface {

    public:
    MyRobotLeader() : Process(), AgentInterface() {}

    void init(); 
    void start() {}
    void update(); 
    void stop() {}

    private:
        double x_pos = 0, y_pos = 0, theta = 0; //leader x y theta info
        double line_velocity_min = 3.0;
        double line_velocity_max = 6.0;
        double theta_velocity_min = 0.5;
        double theta_velocity_max = 1.0; 
        double sweep_rotation = 2.0;
        double front_sensor = 0; 
        double right_sensor = 0; 
        double left_sensor = 0;
        double back_sensor = 0; 
        bool forward = 1; 
        vector<vector<double>> flock_array; //Flock_array represents each agent's x,y pos, theta pos below the leader. 
        vector<vector<double>> flock_sensors; //Flock_sensors represents each follower's x,y pos, theta pos.  
        int sensor_idx = 0; 
        //booleans for flock creation and sensor channel creation
        bool createflock = 1, setsensorchannel = 1;


};

class RobotLeader : public Agent {
    public:
    RobotLeader(json spec, World& world) : Agent(spec, world) 
    {
        add_process(c);
    }
    private:
        MyRobotLeader c;
};

/*! Initialize flock vector 
* \param fh flock height
* \param leader_x leader x position
* \param leader_y leader y position
* \param leader_theta leader theta
* \return vector representing flock
*/
vector<vector<double>> init_flock(int fh, double leader_x, double leader_y, double leader_theta);

/*! Updates flock vector with flock leader positions
* \param v vector representing flock
* \param leader_x leader x position
* \param leader_y leader y position
* \param leader_theta leader theta
* \return Nothing
*/
void update_flock(vector<vector<double>>& v ,double leader_x, double leader_y, double leader_theta);

/*! Return flock agent x position
* \param x x position of leader
* \param theta theta of leader
* \param dist distance from agent
* \return X position of flock agent
*/
double flock_agent_x(double x, double theta, double dist)
{
    return x + dist*cos(theta);
}

/*! Return flock agent x position
* \param y y position of leader
* \param theta theta of leader
* \param dist distance from agent
* \return X position of flock agent
*/
double flock_agent_y(double y, double theta, double dist)
{
    return y+ dist*sin(theta);
}

/*! Init flock sensors array
* \param fh Flock height
* \return vector representing flock agent sensors
*/
vector<vector<double>> init_flock_sensors(int fh);

DECLARE_INTERFACE(RobotLeader)

#endif