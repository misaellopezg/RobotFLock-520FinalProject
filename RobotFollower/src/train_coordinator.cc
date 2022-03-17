#include "train_coordinator.h"
#include "enviro.h"
using namespace enviro;
using namespace std;

void MyTrainCoordinator::init()
{
    std::cout << "Starting train coordinator ID: " << id() << "\n";
    //Spawn follower if "Spawn Follower" is clicked
     watch("button_click", [&](Event& e) 
     {
              std::cout << "Spawning robot! " << e.value()["value"] << "\n";
              add_agent("Robot_Follower", 0, 0, 0, { {"fill", "red"}});
          });
    //Removed follower agent if clicked
    watch("agent_click", [this](Event e) {
                std::cout << "Removing agent, ID: "<< e.value()["id"] << "\n";
                if(e.value()["id"] != 0 && e.value()["id"] != 1)
                {
                    remove_agent(e.value()["id"]); 
                }
        });
}
