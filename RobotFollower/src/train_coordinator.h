#ifndef __TRAIN_COORDINATOR__H
#define __TRAIN_COORDINATOR__H 

#include "enviro.h"

using namespace enviro;
using namespace std;
/*MyTrainCoordinator
*Creates agent that checks for "Spawn Follower" button click to add follower.
*If follower is clicked, follower agent is removed.
*/
class MyTrainCoordinator : public Process, public AgentInterface {

    public:
    MyTrainCoordinator() : Process(), AgentInterface() {}

    void init(); 
    void start() {}
    void update() {}
    void stop() {}

    private:
        double x_pos = 0, y_pos = 0; 
};
/*TrainCoordinator
Addes MyTrainCoordinator agent to process
*/
class TrainCoordinator : public Agent {
    public:
    TrainCoordinator(json spec, World& world) : Agent(spec, world) 
    {
        add_process(c);
    }
    private:
        MyTrainCoordinator c;
};

DECLARE_INTERFACE(TrainCoordinator)

#endif