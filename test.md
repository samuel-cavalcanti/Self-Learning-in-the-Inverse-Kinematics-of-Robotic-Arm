::: {.mume .markdown-preview}
Self-Learning in the Inverse Kinematics of Robotic Arm {#self-learning-in-the-inverse-kinematics-of-robotic-arm .mume-header}
======================================================

***Samuel Cavalcanti and Orivaldo Santana***

Abstract {#abstract .mume-header}
--------

This work is situated in application of techniques of machine learning
for the pick and place tasks. The purpose of this study is to evaluate
the Map of Kohonen in its process of learning and association of vision
data with control data of a robotic arm. For this, two scenarios were
made, in both of them the arm moves randomly. In first scenario, only
control data of a line movement was captured. In the second, it was
captured control data that allows the arm moves in a plan. After
training the neural networking with the vision and control data. The SOM
with 5184 nodes has Average MSE 0,00242445 for movement in line and
0,00630577 in plane. The results indicate that Kohonen\'s map has the
capacity of learning the control data and position the arm from a visual
stimulus in both scenarios.

I. INTRODUCTION {#i-introduction .mume-header}
---------------

The work presented in this article is related to the pro-\
blem of teaching an articulated robot to perform a pick-and\
place task. In order to solve this type of problem, machine\
learning techniques are usually used in combination with\
Learning by Demonstration (LbD). In this type of approach\
the robot learns to perform a task from actions performed\
by a demonstrator agent, a human being or a robot. There\
are many ways to demonstrate behavior for a robot, for\
example, by using a sequence of captured sensor data on\
the demonstrator agent or a video with the demonstrator\
agent \[[1](#ref1)\], \[[2](#ref2)\]. Recent examples of application of
LbD in\
pick-and place task can be found in \[[3](#ref3)\] that proposed a\
method based on Dynamic Movement Primitives (DMPs),\
and \[[4](#ref4)\] that proposed a method based Gaussian Mixture\
Model (GMM) and Gaussian Mixture Regression (GMR).\
The objective of this work is to investigate solutions for\
LbD in activities involving a vision system and a movement\
control system of an articulated robot focused on the task of\
pick-and place objects. This article going to deal only with\
the learning process of positioning a robotic arm. Therefore,\
it uses visual information and data about the positioning\
control of this arm.\
To contextualize, the solution investigated involves: (i)\
position control of robotic arm based on vision; (ii) trajectory\
construction with the end effector at a starting point to a\
target position of the object location; (iii) to pick up, to\
transport and finally to place the object. This article will deal\
only with position control (i). This article going to deal only\
with position control, stage (i). Therefore, an unsupervised\
machine learning technique will be used. A classic way\
to solve the positioning of the end effector of a robotic\
arm is through inverse kinematics. However, when using an\
unsupervised technique with a vision system, two advantages\
arise: 1 - it is not necessary to create a mathematical model\
for each type of arm, but only a new training of the learning\
system; 2 - It is not necessary to make a transformation\
between the real space (Cartesian plane of the robot) to the\
space of vision (visual signals), because this transformation\
is embedded in the training data. The machine learning\
technique chosen initially is the classic model called Self-\
Organizing Map (SOM) \[[5](#ref5)\].

The validation of the proposed approach was performed\
in two scenarios: a simpler scenario with data distributed\
in a straight line; And a more elaborate scenario with data\
distributed in a plane. New tests should be evaluated, such\
as learning motion in a 3D space from a stereo camera.\
This article is organized as follows, some related works\
are presented in the Section II. The proposed approach to\
address the learning problem of robotic arm positioning is\
discussed in Section III. The validation experiments of the\
approach are described in Section IV. The conclusion is in\
Section V.

II. RELATED WORKS {#ii-related-works .mume-header}
-----------------

This Section presents some models of unsupervised lear-\
ning applied to the control problem of a robotic arm, mainly\
models based on Kohonen maps. Some papers discuss how\
the visual system is used in the process of control of arm\
movement. The Parametrized Self-Organizing Map (PSOM),\
for example, presents a classic approach to training a robotic\
arm with visual information to perform moves in a 3D space.\
This model has as main characteristic the learning with few\
samples of training. The basic idea of a PSOM is to build\
a map manifold from a restricted amount of basis manifolds\
\[[6](#ref6)\]. A disadvantage of this model is the need for prior\
knowledge of training data.\
For the control of manipulator robots in the task of picking\
up and placing Kumar et al. \[[7](#ref7)\], \[[8](#ref8)\] proposed a
system\
based on the SOM neural network. The robot presented in\
this work has 7 degrees of freedom. The positioner of the\
effector is captured by a stereo system of cameras returning\
four coordinates, two for each camera. The control system\
learns to map the four coordinates of the cameras into a six-\
dimensional vector containing the angular positions of the\
joints of the robotic manipulator. Thus, an adapted SOM with\
organized three-dimensional topological structure is used to\
learn such a mapping so that each network node maps the\
inverse kinematics of the manipulator to the imagens of the\
cameras. A relevant point of this work is the encoding of\
neurons with visual and control information.\
Huser et al. presents a demonstration-based approach to\
teach a robotic system with an arm a task of picking objects\
\[[9](#ref9)\]. In this approach, the demonstrator agent through a\
stereoscopic camera takes objects with his hand. To perform\
the tracking of the hand of the demonstrator, some image\
processing techniques are used to segment the hand and\
find its contour. This hand data is processed and the hand\
coordinate in a 3D space is used to train a SOM of a\
dimension that creates a generalization of this input data.\
Thus, the 1D topology SOM network learns the trajectory of\
hand movement of the demonstrator to control the robotic\
hand. This work shows that the SOM can be applied in tasks\
more complex than the learning of inverse kinematics.\
The work of Zhou et al. \[[10](#ref10)\] shows that it is possible to\
apply models based on the Kohonen map for the autonomous\
learning of the control of movement of a robotic arm in\
a visual-motor system. The learning process occurs with a\
camera aimed at the random motion of a robotic arm. The\
visual system is enabled with tilting and rotating actions\
similar to human head movement.

III. SELF-LEARNING TO CONTROL ROBOTIC ARM {#iii-self-learning-to-control-robotic-arm .mume-header}
-----------------------------------------

The approach discussed in this work consists in applying\
machine learning methods to relate sensory data with control\
data in a robot with a vision system and an articulated\
member. The learning process must occur independently and\
the robot must learn alone to relate visual positions with\
control signals of the actuators. After training and from a\
visual stimulus, the articulated robot member should reach\
any feasible visual region.\
The first step in the learning process is to collect data.\
In this stage, the robotic arm performs several movements\
to reach as many points as possible in its field of view. At\
each new point reached a sample is collected and stored in\
a data set. Each sample contains visual information (effector\
position, for example) and arm control information (joint\
angles, for example).\
The learning algorithm has the role of relating a point of\
the field of view to a control signal that makes the robotic\
arm effector reach this point. In this work, the first algorithm\
chosen to investigate this learning process was the classical\
neural network of unsupervised learning, the Kohonen Map\
or the Self-Organizing Map (SOM). This algorithm has\
characteristics that are relevant to the autonomous learning\
process, such as the ability to learn by itself and to self-\
organize the data. With the SOM, the robotic arm can make\
random movements to obtain data with visual and control\
information, and learn to make a relation between visual\
signal and control signal. A collection of many data is\
easily self-organized in its topological structure. Thus, a large\
amount of data can be presented to the neural network, but\
the neural network has the ability to compress this data and\
store in its neurons the most representative samples of all\
input data.\
To use the trained system, simply present a point of\
interest in the image that the learning algorithm will be able\
to retrieve the control information to reach this point. For\
SOM to relate visual information with control commands,\
it is necessary to perform a search for the neuron that best\
represents the desired visual information. Thus, the classic\
SOM search strategy was changed to allow only a part of\
the neuron encoding (part related to visual information).\
Thus, the classical SOM search strategy was changed to\
allow computing only part of the neuron weights (part\
related to visual information). After finding neuron that best\
represents this visual information, automatically the control\
signal encoded in this neuron is extracted and used to move\
the arm. At the end of this process, the robotic arm effector\
is positioned at the desired visual point.

### A. SELF-ORGANIZING MAP {#a-self-organizing-map .mume-header}

A SOM (Self-Organizing Map) is a tool that organizes and\
maps high-dimensional data into a regular low-level lattice.\
Being able to compress information without losing important\
topological and metric relationships of the original data \[[5](#5)\].\
The SOM (Self-Organizing Map) were developed by\
Teuvo Kohonen in the 1980s inspired by the topological\
map of the animal cerebral cortex. It has been observed that

in more complex animals the different areas of the brain\
contain subareas that are responsible for mapping a certain\
sensory organ. It is known that these neurons in the cortex\
are spatially organized, in which the topologically close ones\
tend to respond to similar stimuli \[[11](#ref11)\].\
The SOM network has two layers, input and output. The\
input is where the data is presented to the neural network. In\
the output competition occurs between the neurons to find\
the best-match unit neuron. Usually the Euclidean distance\
between the sample vector and the weight vector of each\
neuron is calculated, after weight of the best-match unit is\
modified to be more similar to the input sample. The weight\
of neighbors neurons are modified like the best-match unit,\
but with a intensity take into account the the distance to the\
best-match unit in the SOM lattice. As samples are presented\
to the network, it organizes itself so that similar samples are\
located in the same region \[[12](#ref12)\].\
The SOM training can be divided into two phases: in\
the first phase, the neurons are initially randomly oriented\
(weights with random values, but preferably all very close),\
the learning rate is high, and occurs the discovery of the\
clusters that it must map. In the second phase, the learning\
rate must be low, the neighborhood radius involves one or no\
neighbor, there is the sophistication of the map, improving\
the grouping performed \[[5](#ref5)\].

IV. EXPERIMENTS {#iv-experiments .mume-header}
---------------

The objective of this Section is to evaluate an unsupervised\
algorithm to learn a mapping between sensory data and\
control data in a robotic arm with a vision system. The\
experiments were made with a simulator, a system for data\
capture and an adapted SOM. To measure the performance\
of the artificial neural network, a visual and a system output\
evaluation was made. The experiments were done in two\
setups: one the robotic arm end effector moving in one\
dimension and another the robotic arm end effector moving\
in two dimensions.\
The experiments were performed with an simulated\
[AURA robotic arm](https://www.thingiverse.com/thing:225513) composed
basically with 3 parts, see\
Figure [1](#fig1). The arm base gives support to the others parts. The\
arm can be divided into two links: A and B, with link A with\
Fig. 5. Arm after neural network control signal.\
14 centimeters and B with 12 centimeters. The movement\
of the AURA is determined by the positions of the three\
joints: alpha, beta and gamma, Figures [3](#fig3) and [2](#fig2). In
every\
experiment the alpha angle was configured to a fixed value.\
The vision sensor is positioning on the side of the robot. The\
Figure [2](#fig2) contains a image of the vision sensor output. Thus,\
each sample contains visual information (x, y) and control\
information (desired alpha and gamma)

![](file:////home/samuel/Documents/Repositories/Self-Learning-in-the-Inverse-Kinematics-of-Robotic-Arm/Pictures/robotic_arm.png){#fig1}

Fig. 1. AURA Robotic Arm.

![](file:////home/samuel/Documents/Repositories/Self-Learning-in-the-Inverse-Kinematics-of-Robotic-Arm/Pictures/betaeGamma.png){#fig2
width="354" height="300"}

Fig. 2. Beta and Gamma joints.

![](file:////home/samuel/Documents/Repositories/Self-Learning-in-the-Inverse-Kinematics-of-Robotic-Arm/Pictures/alpha.png){#fig3
width="354" height="300"}

Fig. 3. Alpha joint.

![](file:////home/samuel/Documents/Repositories/Self-Learning-in-the-Inverse-Kinematics-of-Robotic-Arm/Pictures/TVA_0.png){#fig4
width="354" height="300"}

Fig. 4. Arm before neural network control signal.

![](file:////home/samuel/Documents/Repositories/Self-Learning-in-the-Inverse-Kinematics-of-Robotic-Arm/Pictures/TVA_1.png){#fig5
width="354" height="300"}

Fig. 5. Arm after neural network control signal.

### A. LINE {#a-line .mume-header}

In this scenario the control information was collected with\
the arm effector moving in a single dimension. A red ball\
was associated with the end effector. The vision sensor was\
configured to capture the mass center of the red ball and to\
use relative coordinates, x and y position between 0 to 1. For\
that, an algorithm makes the arm to realize random moves,\
beta and gamma joint values between 0 and 180 degrees.\
But, only values in a rectangular region ware selected. This\
region was defined by a desired Y +/- 0.01 (height in the\
image of the vision sensor, Figure [2](#fig2)) and X has been the\
entire image width.\
After collecting 1700 samples for the training and 1700\
for validation, the SOM neural network was trained with 3\
sizes: 18x18 (324 neurons), 36x36 (1296 neurons) and 72x\
(5,184 neurons). With the following settings: The learning\
rate of 0.2, 10000 interactions and neighborhood radius equal\
to 1.5.\
The performance of the algorithm was evaluated with\
the mean square error (MSE) between the desired output\
and calculated output (the beta and gamma angles). This\
experiment was executed 30 times, the MSE and the standard\
deviation of the MSE were calculated.\
Another way to check the approach performance was visu-\
ally observe the desired position and the simulated position\
of the end effector. For this, it was created an algorithm\
that automatically presents aleatory targets positions to the\
robotic arms. So, if the learning process has occurred with\
success the output control commands of the SOM neural\
network will make the end effector reach the red ball.

### B. PLANE {#b-plane .mume-header}

The experiments in this scenario is similar to the previous,\
but the samples is scattered in a plane rather than a straight\
line. Now, points of interest are: positions where the point\
on the y axis of the ball was greater than or equal to 0.29,\
because below that the arm crossed the ground; Positions\
in which the point on the x-axis was less than or equal\
to 0.45, since it was observed in preliminary tests that the\
network felt difficulties in learn points in the back region of\
the arm. After the collection, was made the same procedure\
as in the previous scenario, that is: the neural network was\
trained with the same 3 sizes, the MSE was calculated and\
the process was repeated 30 times and visually was verified\
the accuracy of the network.\
With the results of the Tables [I](#table1), [II](#table2) and
[III](file:////home/samuel/Documents/Repositories/Self-Learning-in-the-Inverse-Kinematics-of-Robotic-Arm/(#table3))
the SOM\
network was able to learn the movement of the robot in\
plane with errors below 2 zeros. It is possible to note that\
the error decreases as the network size increases, showing\
the smaller error tendencies for larger networks. Also in its\
visual verification we observed that the network can follow\
the ball, see Figures [4](#fig4) and [5](#fig5).

#### TABLE I OUTPUT ERROR FOR BETA JOINT AND SIZE NETWORK OF 18 X 18 {#table-i-output-error-for-beta-joint-and-size-network-of-18-x-18 .mume-header}

  Scenario   Average MSE Standard deviation
  ---------- --------------------------------
  Line       0,00526680
  Plane      0,02460880

#### TABLE II OUTPUT ERROR FOR BETA JOINT AND SIZE NETWORK OF 36 X 36 {#table-ii-output-error-for-beta-joint-and-size-network-of-36-x-36 .mume-header}

  Scenario   Average MSE Standard deviation
  ---------- --------------------------------
  Line       0,00325760
  Plane      0,01014820

#### TABLE III OUTPUT ERROR FOR BETA JOINT AND SIZE NETWORK OF 72 X 72 {#table-iii-output-error-for-beta-joint-and-size-network-of-72-x-72 .mume-header}

  Scenario   Average MSE Standard deviation
  ---------- --------------------------------
  Line       0,002424450
  Plane      0,006305770

V. CONCLUSION {#v-conclusion .mume-header}
-------------

This work presented a solution to the learning problem\
of positioning a robotic arm. This solution is embedded\
in a larger problem that is to make an articulated robot\
with a vision system learn how to manipulate objects. The\
task taken as reference is to take and place object. Thus,\
the solution presented in this paper solves a part of this\
larger problem. With the results obtained in Section ref sec:\
experiments it is possible to conclude that for the evaluated\
scenarios the proposed approach is able to position the arm\
near the object. In this way, allowing future work to advance\
in the task of pick-and place objects and in the investigation\
of strategies of learning by demonstration.

**REFERENCES**

\[1\] B. D. Argall, S. Chernova, M. Veloso, and B. Browning, "A survey
of robot learning from demonstration,"Robotics and Autonomous Systems,
vol. 57, no. 5, pp. 469--483, May 2009.

\[2\] E. A. Billing, "A formalism for learning from
demonstration,"Journal of Behavioral Robotics, vol. 1, no. 1, pp. 1--13,
2010.

\[3\] C. Paxton, G. D. Hager, L. Bascetta,et al., "An incremental
approach to learning generalizable robot tasks from human
demonstration," in Robotics and Automation (ICRA), 2015 IEEE
International Conference on. IEEE, 2015, pp. 5616--5621.

\[4\] R. Cubek, W. Ertel, and G. Palm, "High-level learning from demons-
tration with conceptual spaces and subspace clustering," inRobotics and
Automation (ICRA), 2015 IEEE International Conference on. IEEE, 2015,
pp. 2592--2597.

\[5\] T. Kohonen, "The self-organizing map," Neurocomputing, vol. 21,
no. 1-3, pp. 1 -- 6, 1998. \[Online\]. Avai- lable:
http://www.sciencedirect.com/science/article/B6V10-3V7S70G-
1/2/fd7c0b562382d4fcd8d02759cca

\[6\] J. Walter and H. Ritter, "Rapid learning with parametrized self-
organizing maps,"Neurocomputing, vol. 12, no. 2, pp. 131--153, 1996.

\[7\] S. Kumar, N. Patel, and L. Behera, "Visual motor control of a 7
dof robot manipulator using function decomposition and sub-clustering in
configuration space,"Neural Processing Letters, vol. 28, no. 1, pp.
17--33, 2008.

\[8\] S. Kumar, P. P, A. Dutta, and L. Behera, "Visual motor control of
a 7dof redundant manipulator using redundancy preserving learning
network,"Robotica, vol. 28, pp. 795--810, 2010.

\[9\] M. Huser and J. Zhang, "Visual programming by demonstration ̈ of
grasping skills in the context of a mobile service robot using
1d-topology based self-organizing-maps,"Robotics and Autonomous Systems,
vol. 60, no. 3, pp. 463--472, 2012.

\[10\] T. Zhou, P. Dudek, and B. E. Shi, "Self-organizing neural
population coding for improving robotic visuomotor coordination,"
inNeural Networks (IJCNN), The 2011 International Joint Conference on.
IEEE, 2011, pp. 1437--1444.

\[11\] T. Kohonen, "Self-organized formation of topologically correct
feature maps,"Biological Cybernetics, vol. 43, pp. 59--69, 1982.

\[12\] T. Kohonen and R. Hari, "Where the abstract feature maps of the
brain might come from,"Trends in Neurosciences, vol. 22, pp. 135-- 139,
1999.
:::
