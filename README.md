# 520FinalProject
Final Project for EEP 520 Software Engineering for Embedded Applications

# Overview
The following project has the intent of using Enviro to create robot leading/following applications with the intent of realizing flock behvaior with robot agents. The project consists of 4 sub-projects, each one building off the previous one. 
The following 4 subj-projects are explained in order:

1. Looping Leader
   - Creates a robot agent that loops in a circular path. The agent obtains path information from a static CSV file containing X-Y coordinates under the sub-project's "paths" folder. 
2. Robot Follower 
   - Spawns a target agent that loops in a circulat path. A robot agent with sensors can be spawned using the "Spawn Follower" button that will then proceed to chase the target agent. 
3. Robot Train & Better Robot Train
   - Creates a target agent, robot leader agent, robot follower agent, and a train coordinator agent. Building off the two previous sub-projects, the robot leader agent chases the robot target. This time, the train coordinator agent stores leader agent positions. The train coordinator then spawns 3 followers that follow behind the robot leader. Better Robot Train improves on the previous by being able to spawn multiple agents behind the robot as a single unit. 
4. Robot Flock 
   - Creates a robot leader agent and three robot follower agents. Building off of Robot train, this sub-project showcases dynamic movement between the robot leader and the robot followers. While the leader rotates, each follower is able to oscillate on its own with respect to the leader's X-Y-Theta position. Along with this, the flock acts a single unit, providing information on it's front, back, left, and right sensors.  

IMPORTANT: This project uses ENVIRO v1.6 . Other versions may not be compatible.

# Installation
Start a command line terminal.

Clone the project to a directory of your choice. Make sure the directory path has no special characters (!@#$%^&..) or spaces. 
```bash
git clone https://github.com/misaellopezg/520FinalProject.git
```

Docker is required to run the project. Docker can be found and downloaded here: https://www.docker.com/get-started/
Once Docker is installed, run the following command to pull image (if never pulled) and start the docker container with Enviro. 
```bash
docker run -p80:80 -p8765:8765 -v $PWD:/source -it klavins/enviro:v1.6 bash
```

Once the Docker image with ENVIRO is running, type the following command to start the ENVIRO server:
```bash
esm start
```

# Running the Project
The project consists of 4-sub projects. Navigate to each of the following sub-projects by changing directory: 
```bash
cd LoopingLeader
cd RobotFollower
cd RobotTrain
cd BetterRobotTrain
cd RobotFlock
```
NOTE: RobotTrain and BetterRobotTrain are considered to be one sub-project per description, but are launched individually. 

After navigating to a sub-project, use the "make clean" command to remove any accidental executables: 
```bash
make clean
```
After cleaning, use the "make" command to compile sub-project: 
```bash
make
```
Start the project with the enviro command: 
```bash
enviro
```
To see the environment, open your web browswer (preferably Google Chrome) and go to localhost: 
```bash
https://localhost/
```
This should show the ENVIRO environment. 

To stop the project, press Ctrl+c . 

Most projects should be non-interactive and showcase robot flock progresssion. 

## Looping Leader
To add more creative paths for the robot to follow, you can place a static csv file under the /paths folder and edit the init() function under Leader.cc file to specify the static csv file path to read from: 
```bash
void MyRobotController::init()
{
    //Get robot path from paths/ folder in project and store in vector 
    robot_path = get_file_robot_path("paths/circular_path.csv"); 
    ..
    ..
    ..
}
```
The more X - Y coordinates for the robot, the better, as the robot looks ahead 3 coordinates ahead. 

## Robot Follower
Sub-project RobotFollower is the only project that requires user input. When starting a project, a moving target is spawned. To spawn a robot that follows the target, press the "Spawn Follower" button on the top-right side. To eliminate a robot follower, click on the desired robot. Just like in looping leader, other paths can be placed for LoopingLeader.cc . 

## Robot Train and Better Robot Train
Robot Train exhibits static behaviour with 3 robots following a leader. 

Better Robot Train exhibits dynamic follower spawning behind the leader. To extend the robot train, modify the variable *const int flock_heigth* to a value greater than 0. Similar to looping leader, other paths can be placed under RobotTarget.cc . 

## Robot Flock
Robot Flock exhibits static behavior, with the leader spawning 3 follwer robots behind it. The leader is able to position the followers relative to it's X-Y-Theta position. The robot followers are able to oscillate on their own following the leader robot as a reference. This is done through sine and cosine calculations. The follower robots pass sensor information to the leader. The leader is then able to set the flock's front, left, right, and back sensor readings to detect objects around it.  

# Challenges
### ENVIRO Functionality
When trying to create an invisible agent or non-interactive agent, the project would compile but would throw an segmentation fault error. I switched from the alpha version to version 1.2, and the issue persisted. At one point, I did get it to work, but one I remade the files the issue returned. I swtiched to version 1.6, and the issue persisted. 
Workaround: I spawned a static agent far away from the robots that are actually running in the arena. The static agent was mainly used for train coordinator and did not have to be present in the arena. 
### Understanding Sensor Positioning and Data Retreival
After editing the .json file, I kept positioning the sensors wrong. I also kept retreiving the sensors in the wrong order because I would place them wrong. 
Workaround: I spawned a robot in the environment offset from the origin to figure out which sensor was which. I also played around with the .config file until I orderd the sensors in the correct way. 
### Getting the Robot to Target another Robot
It took me a while to understand how to use the sensors to follow a target. 
Workaround: I was able to use the  sensor_reflection_type() method to find the target, as well as use aditional sensors to check to see which direction the target was moving.
### Spawning Unique Follower Robots
This proved to be a challenge because of function inexperience. 
Workaround: I did not know I was supposed to create the .so file for the target agent to be spawned. After reading the ENVIRO documentation, cleaninig and remaking the project, this issue went away.
### Creating Unique Channels for Followers
To have the robot leader or robot coordinator relay information to followers, I had to come up with a way to be able to communicate specific information to each follower. 
Workaround: I used each follower's agent ID to create specific channels. For the leader and/or coordinator, I used the Agent& add_agent() function with a for loop to store the IDs in a vector. This vector was used to keep information from each sequential follower spawned as well as communicate information back to the follower. 
### Retreiving Sensor Information from Flock
With the Robot Flock project, I was trying to spawn dynamic followers behind the leader and retreive their sensor information. I tried to use a for loop with the watch() method to use a vector to store sensor information from the followers. However, I was not able to dynamically do this. 
Workaround: I made the example static, and created 3 static channels to retreive follower sensor information. 
### Spawning Followers with respect to Leader
This took me a while, as it required brushing up on using trigonometry rules to figure out how to position the followers. 
Workaround: Creating functions that represent equations for offsetting followers using trigonometry. 
### Other
Starting a new full-time job during the middle of the class certaintly did not help! 
Workaround: Sleep more and lots of coffee! 

# Acknolwedgements
ENVIRO: The multi-agent, multi-user, multi-everything simulator
- Created by: Klavins Lab Software
- https://github.com/klavinslab/enviro
- http://klavinslab.org/elma/

Elma
- Created by: Klavins Lab Software
- https://github.com/klavinslab/elma_project

Enviro Docker Image
- Created by: Eric Klavins
- https://hub.docker.com/r/klavins/enviro

Course Reference Material
- Created by: Tamara Bonaci
- https://github.com/tbonaciUW/EEP_520_Winter2022                                                                                                       
