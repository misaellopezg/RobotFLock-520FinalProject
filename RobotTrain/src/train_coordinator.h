#ifndef __TRAIN_COORDINATOR__H
#define __TRAIN_COORDINATOR__H 

#include "enviro.h"
#include <deque>

using namespace enviro;
using namespace std;

/*MyTrainCoordinator
*Coordinator agent that listens to Leader for position information, spawns followers, and gives followers
/ x y theta positions to follow leader
*/
class MyTrainCoordinator : public Process, public AgentInterface {

    public:
    MyTrainCoordinator() : Process(), AgentInterface() {}

    void init(); 
    void start() {}
    void update(); 
    void stop() {}

    private:
        double leader_x_pos = 0, leader_y_pos = 0, leader_theta = 0; // used to store leader current position
        double prev_leader_x_pos = 0, prev_leader_y_pos = 0; //used to store leader previous snapshot positions
        int train_size = 0; //contains train size (leader + followers)
        deque< pair<double,double> > robot_train_pos; //stores robot leader x y positions
        deque<double> robot_train_theta; //stores robot leader thetas
        bool spawnflag = 1; 
        int f1 = 0, f2 = 0, f3 = 0; //contain agent references to spawned followers to capture IDs

};

class TrainCoordinator : public Agent {
    public:
    TrainCoordinator(json spec, World& world) : Agent(spec, world) 
    {
        add_process(c);
    }
    private:
        MyTrainCoordinator c;
};

/*! Calculates radial distance between robot leader and it's last known position
*\param cx Leader's current x position
*\param cy Leader's current y position
*\param px Leader's previous x position
*\param py Leader's previous y position
*/
bool check_leader_distance(double cx, double cy, double px, double py); 

DECLARE_INTERFACE(TrainCoordinator)

#endif