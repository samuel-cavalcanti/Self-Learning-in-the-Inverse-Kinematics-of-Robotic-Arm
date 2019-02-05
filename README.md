# Self-Learning-in-the-Inverse-Kinematics-of-Robotic-Arm

this project needed OpenCV library, before to compile, install Opencv
<https://opencv.org/>

How to install OpenCV in linux
<https://docs.opencv.org/3.4/d7/d9f/tutorial_linux_install.html>

go to RemoteAPI and create temporary directory

``` shell
$ cd RemoteAPI
$ mkdir build
```

compile the project
```shell
$ cd build
$ cmake ..
$ make 
```

open Vrep scene in `Scene_Vrep/AuraRoboticArm.ttt` play the simulation

run aplication cppremoteapi

```shell
[samuel@ArchLinux RemoteAPI/build]$ ./cppremoteapi 
```

see the paper [Self-Learning-in-the-Inverse-Kinematics-of-Robotic-Arm](paper.md)