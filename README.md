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

After navigating to a sub-project start the project with the enviro command: 
```bash
enviro
```
To stop the project, press Ctrl+c

Sub-project RobotFollower is the only project that requires user input. When starting a project, a moving target is spawned. To spawn a robot that follows the target, press the "Spawn Follower" button on the top-right side. To eliminate a robot follower, click on the desired robot. 

# Challenges

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

README has an overview of what the goal of the project is                                                                                                   |
| 10     | README has a description of key challenges and how they were addressed                                                                                      |
| 10     | README describes how to install and run the code (assuming the user has docker installed)                                                                   |
| 10     | README describes how to run and/or use the project                                                                                                            
