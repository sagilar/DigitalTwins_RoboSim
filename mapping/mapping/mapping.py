#Author: Santiago Gil

import io
import types
'''***** CoppeliaSim Remote API (via ZMQ)*****'''
## Be sure the Python package is installed, and the SIMZMQ Plugin is installed in your CoppeliaSim installation
## Visit https://github.com/CoppeliaRobotics/zmqRemoteApi for more information
from coppeliasim_zmqremoteapi_client import RemoteAPIClient


'''***** Specific to the flex-cell case study*****'''
from robots_flexcell import robots # Library for Flex-cell robots -> based on the Robotics Toolbox






class Operation():

    def __init__(self,name="",actions=[],**kwargs):
        self.name = name
        self.actions = actions
        self.arguments = kwargs

    def update_args(self,args):
        self.arguments = args

    def update_actions(self,actions):
        self.actions = actions

    def add_arg(self,dict):
        for key,value in dict.items():
            self.arguments[key] = value

    # This method overwrites all the objects of the same class
    def add_action(self,action):
        self.actions.append(action)

    def delete_actions(self):
        self.actions = []

    def delete_args(self):
        self.arguments = {}

    def execute(self,args):
        results_actions = []
        for action in self.actions:
            action_arguments = None
            idx = self.actions.index(action)
            if idx < len(self.arguments):
                action_arguments = tuple(self.arguments["action_" + str(idx)])
            if action_arguments != None:
                result = action(*action_arguments)
            else:
                result = action()
            if result != None:
                results_actions.append(result)
            else:
                results_actions.append("")
        return results_actions



class InputEvent():
    def __init__(self,name="",equations=[],**kwargs):
        self.name = name
        self.equations = equations
        self.arguments = kwargs

    def update_args(self,args):
        self.arguments = args

    def update_equations(self,equations):
        self.equations = actions

    def add_arg(self,dict):
        for key,value in dict.items():
            self.arguments[key] = value

    ## This method overwrites all the objects of the same class
    def add_equation(self,action):
        self.equations.append(equation)

    def delete_equations(self):
        self.equations = []

    def delete_args(self):
        self.arguments = {}

    def get_event_result(self,args):
        results_equations = []
        for equation in self.equations:
            equation_arguments = None
            idx = self.equations.index(equation)
            if idx < len(self.arguments):
                equation_arguments = tuple(self.arguments["equation_" + str(idx)])
            if equation_arguments != None:
                result = equation(*equation_arguments)
            else:
                result = equation()
            if result != None:
                results_equations.append(result)
            else:
                results_equations.append("")
        return results_equations

class Mapping():

    def __init__(self,host="localhost",port=23000):
        self.client = RemoteAPIClient(host='localhost', port=23000) ### Client
        self.sim = self.client.getObject('sim') ### Sim Object: the objects are handled from this object serialization

        '''Specific to the flex-cell case study'''
        self.ur_robot_model = robots.UR5e_RoboSim_Simulation(mqtt_enabled=False,zmq_enabled=False)
        self.ur_robot_model.set_motion_time(2.0)## Definition of the trajectory time

        '''These objects are to be initialized from the mapping generator'''
        self.base_name = "/1_base_link_collision/"
        self.j0 = self.sim.getObject(self.base_name + "17_shoulder_pan_joint") # J0
        self.j1 = self.sim.getObject(self.base_name + "11_shoulder_lift_joint") # J1
        self.j2 = self.sim.getObject(self.base_name +"16_elbow_joint") # J2
        self.j3 = self.sim.getObject(self.base_name + "15_wrist_1_joint") # J3
        self.j4 = self.sim.getObject(self.base_name + "18_wrist_2_joint") # J4
        self.j5 = self.sim.getObject(self.base_name + "14_wrist_3_joint") # J5
        self.r_fg = self.sim.getObject(self.base_name + "13_rightFingerGripper") # Right finger gripper (OnRobot 2FG7)
        self.l_fg = self.sim.getObject(self.base_name + "12_leftFingerGripper") # Left finger gripper (OnRobot 2FG7)


        '''Actions'''
        ## Here the tricky part comes in
        # The functions here should be assigned according to object type and simulation engine API
        actions_movejoint = []
        actions_movejoint.append(lambda target_q0: self.sim.setJointTargetPosition(self.j0,target_q0))
        actions_movejoint.append(lambda target_q1: self.sim.setJointTargetPosition(self.j1,target_q1))
        actions_movejoint.append(lambda target_q2: self.sim.setJointTargetPosition(self.j2,target_q2))
        actions_movejoint.append(lambda target_q3: self.sim.setJointTargetPosition(self.j3,target_q3))
        actions_movejoint.append(lambda target_q4: self.sim.setJointTargetPosition(self.j4,target_q4))
        actions_movejoint.append(lambda target_q5: self.sim.setJointTargetPosition(self.j5,target_q5))


        actions_movediscrete = [self._movediscrete] # Condensed action. These perhaps require annotations to generate a function

        actions_movecartesian = [self._movecartesian] # Condensed action. These perhaps require annotations to generate a function

        actions_movejoint = [self._movejoint] # Condensed action. These perhaps require annotations to generate a function

        actions_stop = [self._stop] # Condensed action. These perhaps require annotations to generate a function

        actions_pick = [self._pick] # Condensed action. These perhaps require annotations to generate a function

        actions_place = [self._place] # Condensed action. These perhaps require annotations to generate a function

        actions_setvelocity = []
        actions_setvelocity.append(lambda target_qd0: self.sim.setJointTargetVelocity(self.j0,target_qd0))
        actions_setvelocity.append(lambda target_qd1: self.sim.setJointTargetVelocity(self.j1,target_qd1))
        actions_setvelocity.append(lambda target_qd2: self.sim.setJointTargetVelocity(self.j2,target_qd2))
        actions_setvelocity.append(lambda target_qd3: self.sim.setJointTargetVelocity(self.j3,target_qd3))
        actions_setvelocity.append(lambda target_qd4: self.sim.setJointTargetVelocity(self.j4,target_qd4))
        actions_setvelocity.append(lambda target_qd5: self.sim.setJointTargetVelocity(self.j5,target_qd5))

        '''actions_stop = []
        actions_setvelocity.append(lambda: self.sim.setJointTargetVelocity(self.j0,0.0))
        actions_setvelocity.append(lambda: self.sim.setJointTargetVelocity(self.j1,0.0))
        actions_setvelocity.append(lambda: self.sim.setJointTargetVelocity(self.j2,0.0))
        actions_setvelocity.append(lambda: self.sim.setJointTargetVelocity(self.j3,0.0))
        actions_setvelocity.append(lambda: self.sim.setJointTargetVelocity(self.j4,0.0))
        actions_setvelocity.append(lambda: self.sim.setJointTargetVelocity(self.j5,0.0))'''

        '''Equations'''
        #equations_moveDiscreteCommand = [lambda x: x=="flexcellCartesianPosition[position]"] ## From the controller

        equations_nonfeasibleMoveDiscreteCommand = [lambda target_X,target_Y,target_Z: self._calculate_feasibility(target_X,target_Y,target_Z) == False]

        equations_feasibleMoveDiscreteCommand = [lambda target_X,target_Y,target_Z: self._calculate_feasibility(target_X,target_Y,target_Z) == True]

        #equations_moveCompleted = [lambda x: x=="flexcellAngularPosition[completed]"] ## To be corrected
        equations_moveCompleted = []
        equations_moveCompleted.append(lambda : round(self.sim.getJointPosition(self.j0),2) == round(self.sim.getJointTargetPosition(self.j0),2))
        equations_moveCompleted.append(lambda : round(self.sim.getJointPosition(self.j1),2) == round(self.sim.getJointTargetPosition(self.j1),2))
        equations_moveCompleted.append(lambda : round(self.sim.getJointPosition(self.j2),2) == round(self.sim.getJointTargetPosition(self.j2),2))
        equations_moveCompleted.append(lambda : round(self.sim.getJointPosition(self.j3),2) == round(self.sim.getJointTargetPosition(self.j3),2))
        equations_moveCompleted.append(lambda : round(self.sim.getJointPosition(self.j4),2) == round(self.sim.getJointTargetPosition(self.j4),2))
        equations_moveCompleted.append(lambda : round(self.sim.getJointPosition(self.j5),2) == round(self.sim.getJointTargetPosition(self.j5),2))


        equations_robotStopped = []
        #equations_robotStopped.append(lambda x: (x == "flexcellAngularPosition[completed]") or ("flexcellAngularPosition[stopped]")) ## To be corrected
        #equations_robotStopped.append(lambda qd0: qd0==0.0)
        #equations_robotStopped.append(lambda qd1: qd1==0.0)
        #equations_robotStopped.append(lambda qd2: qd2==0.0)
        #equations_robotStopped.append(lambda qd3: qd3==0.0)
        #equations_robotStopped.append(lambda qd4: qd4==0.0)
        #equations_robotStopped.append(lambda qd5: qd5==0.0)
        equations_robotStopped.append(lambda : round(self.sim.getJointVelocity(self.j0),2)<0.1)
        equations_robotStopped.append(lambda : round(self.sim.getJointVelocity(self.j1),2)<0.1)
        equations_robotStopped.append(lambda : round(self.sim.getJointVelocity(self.j2),2)<0.1)
        equations_robotStopped.append(lambda : round(self.sim.getJointVelocity(self.j3),2)<0.1)
        equations_robotStopped.append(lambda : round(self.sim.getJointVelocity(self.j4),2)<0.1)
        equations_robotStopped.append(lambda : round(self.sim.getJointVelocity(self.j5),2)<0.1)

        equations_gripperClosed = []
        equations_gripperClosed.append(lambda rf,opening: rf<(opening/2 + 0.005))
        equations_gripperClosed.append(lambda lf,opening: lf<(opening/2 + 0.005))


        equations_gripperOpened = []
        equations_gripperOpened.append(lambda rf,opening: rf>(opening/2 - 0.005))
        equations_gripperOpened.append(lambda lf,opening: lf>(opening/2 - 0.005))

        #equations_openGripperCommand = [lambda x: x=="gripperCommand[open]"] # from the controller

        #equations_closeGripperCommand = [lambda x: x=="gripperCommand[close]"] # from the controller

        equations_collision = []
        equations_collision.append(lambda qd0,t0,speed_collision,torque_collision: (qd0<speed_collision) and (t0 > torque_collision))
        equations_collision.append(lambda qd1,t1,speed_collision,torque_collision: (qd1<speed_collision) and (t1 > torque_collision))
        equations_collision.append(lambda qd2,t2,speed_collision,torque_collision: (qd2<speed_collision) and (t2 > torque_collision))
        equations_collision.append(lambda qd3,t3,speed_collision,torque_collision: (qd3<speed_collision) and (t3 > torque_collision))
        equations_collision.append(lambda qd4,t4,speed_collision,torque_collision: (qd4<speed_collision) and (t4 > torque_collision))
        equations_collision.append(lambda qd5,t5,speed_collision,torque_collision: (qd5<speed_collision) and (t5 > torque_collision))


        '''Initialization of services -> Operations and Input Events. This should be initialized automatically from the mapping generator'''
        self.operations_list = []
        self.operations = types.SimpleNamespace() # To be refined with a proper dot notation
        self.operations.movediscrete = Operation(name="movediscrete",actions=actions_movediscrete)
        self.operations.movejoint = Operation(name="movejoint",actions=actions_movejoint)
        self.operations.movecartesian = Operation(name="movecartesian",actions=actions_movecartesian)
        self.operations.setvelocity = Operation(name="setvelocity",actions=actions_setvelocity)
        self.operations.stop = Operation(name="stop",actions=actions_stop)
        self.operations.pick = Operation(name="pick",actions=actions_pick)
        self.operations.place = Operation(name="place",actions=actions_place)
        self.operations_list.extend([self.operations.movediscrete,
                                     self.operations.movejoint,
                                     self.operations.movecartesian,
                                     self.operations.setvelocity,
                                     self.operations.stop,
                                     self.operations.pick,
                                     self.operations.place,])

        self.input_events_list = []
        self.input_events = types.SimpleNamespace()
        #self.input_events.moveDiscreteCommand = InputEvent(name="moveDiscreteCommand",equations=equations_moveDiscreteCommand)
        self.input_events.nonfeasibleMoveDiscreteCommand = InputEvent(name="nonfeasibleMoveDiscreteCommand",equations=equations_nonfeasibleMoveDiscreteCommand)
        self.input_events.feasibleMoveDiscreteCommand = InputEvent(name="feasibleMoveDiscreteCommand",equations=equations_feasibleMoveDiscreteCommand)
        self.input_events.moveCompleted = InputEvent(name="moveCompleted",equations=equations_moveCompleted)
        self.input_events.robotStopped = InputEvent(name="robotStopped",equations=equations_robotStopped)
        self.input_events.gripperClosed = InputEvent(name="gripperClosed",equations=equations_gripperClosed)
        self.input_events.gripperOpened = InputEvent(name="gripperOpened",equations=equations_gripperOpened)
        #self.input_events.openGripperCommand = InputEvent(name="openGripperCommand",equations=equations_openGripperCommand)
        #self.input_events.closeGripperCommand = InputEvent(name="closeGripperCommand",equations=equations_closeGripperCommand)
        self.input_events.collision = InputEvent(name="collision",equations=equations_collision)
        self.input_events_list.extend([self.input_events.nonfeasibleMoveDiscreteCommand,
                                     self.input_events.feasibleMoveDiscreteCommand,
                                     self.input_events.moveCompleted,
                                     self.input_events.robotStopped,
                                     self.input_events.gripperClosed,
                                     self.input_events.gripperOpened,
                                     self.input_events.collision,])

    def start_simulation(self):
        self.sim.startSimulation()

    def stop_simulation(self):
        self.sim.stopSimulation()

    def execute_operation(self,operation_name,args=None):
        exec_op = None
        #for op in self.operations: # Does not work yet
        for op in self.operations_list:
            if op.name == operation_name:
                exec_op = op
        if args != None:
            exec_op.update_args(args)
        #print("Executing operation")
        result = exec_op.execute(exec_op.arguments)
        #print("Operation executed")
        return result

    def get_event(self,input_event_name,args=None):
        event = None
        for ev in self.input_events_list:
            if ev.name == input_event_name:
                event = ev
        if args != None:
            event.update_args(args)
        #print("Reading event")
        result = event.get_event_result(event.arguments)
        #print("Event read")
        return result

    def get_joint_position(self,joint_name):
        return self._get_joint_position(joint_name)

    def get_joint_velocity(self,joint_name):
        return self._get_joint_velocity(joint_name)

    def get_joint_force(self,joint_name):
        return self._get_joint_force(joint_name)

    def set_joint_position(self,joint_name,val):
        self._set_joint_position(joint_name,val)

    def set_joint_velocity(self,joint_name,val):
        self._set_joint_velocity(joint_name,val)

    def set_joint_force(self,joint_name,val):
        self._set_joint_force(joint_name,val)

    def get_cartesian_positions(self):
        return self._get_cartesian_positions()

    '''CoppeliaSim Implementations'''
    def _get_joint_position(self,joint_name):
        if (joint_name == "j0"):
            return self.sim.getJointPosition(self.j0)
        elif (joint_name == "j1"):
            return self.sim.getJointPosition(self.j1)
        elif (joint_name == "j2"):
            return self.sim.getJointPosition(self.j2)
        elif (joint_name == "j3"):
            return self.sim.getJointPosition(self.j3)
        elif (joint_name == "j4"):
            return self.sim.getJointPosition(self.j4)
        elif (joint_name == "j5"):
            return self.sim.getJointPosition(self.j5)
        elif (joint_name == "r_fg"):
            return self.sim.getJointPosition(self.r_fg)
        elif (joint_name == "l_fg"):
            return self.sim.getJointPosition(self.l_fg)
        else:
            print("Joint name '" + str(joint_name) + "' does not exist" )

    def _get_joint_velocity(self,joint_name):
        if (joint_name == "j0"):
            return self.sim.getJointVelocity(self.j0)
        elif (joint_name == "j1"):
            return self.sim.getJointVelocity(self.j1)
        elif (joint_name == "j2"):
            return self.sim.getJointVelocity(self.j2)
        elif (joint_name == "j3"):
            return self.sim.getJointVelocity(self.j3)
        elif (joint_name == "j4"):
            return self.sim.getJointVelocity(self.j4)
        elif (joint_name == "j5"):
            return self.sim.getJointVelocity(self.j5)
        elif (joint_name == "r_fg"):
            return self.sim.getJointVelocity(self.r_fg)
        elif (joint_name == "l_fg"):
            return self.sim.getJointVelocity(self.l_fg)
        else:
            print("Joint name '" + str(joint_name) + "' does not exist" )

    def _get_joint_force(self,joint_name):
        if (joint_name == "j0"):
            return self.sim.getJointForce(self.j0)
        elif (joint_name == "j1"):
            return self.sim.getJointForce(self.j1)
        elif (joint_name == "j2"):
            return self.sim.getJointForce(self.j2)
        elif (joint_name == "j3"):
            return self.sim.getJointForce(self.j3)
        elif (joint_name == "j4"):
            return self.sim.getJointForce(self.j4)
        elif (joint_name == "j5"):
            return self.sim.getJointForce(self.j5)
        elif (joint_name == "r_fg"):
            return self.sim.getJointForce(self.r_fg)
        elif (joint_name == "l_fg"):
            return self.sim.getJointForce(self.l_fg)
        else:
            print("Joint name '" + str(joint_name) + "' does not exist" )

    def _get_joint_target_position(self,joint_name):
        if (joint_name == "j0"):
            return self.sim.getJointTargetPosition(self.j0)
        elif (joint_name == "j1"):
            return self.sim.getJointTargetPosition(self.j1)
        elif (joint_name == "j2"):
            return self.sim.getJointTargetPosition(self.j2)
        elif (joint_name == "j3"):
            return self.sim.getJointTargetPosition(self.j3)
        elif (joint_name == "j4"):
            return self.sim.getJointTargetPosition(self.j4)
        elif (joint_name == "j5"):
            return self.sim.getJointTargetPosition(self.j5)
        elif (joint_name == "r_fg"):
            return self.sim.getJointTargetPosition(self.r_fg)
        elif (joint_name == "l_fg"):
            return self.sim.getJointTargetPosition(self.l_fg)
        else:
            print("Joint name '" + str(joint_name) + "' does not exist" )

    def _get_joint_target_velocity(self,joint_name):
        if (joint_name == "j0"):
            return self.sim.getJointTargetVelocity(self.j0)
        elif (joint_name == "j1"):
            return self.sim.getJointTargetVelocity(self.j1)
        elif (joint_name == "j2"):
            return self.sim.getJointTargetVelocity(self.j2)
        elif (joint_name == "j3"):
            return self.sim.getJointTargetVelocity(self.j3)
        elif (joint_name == "j4"):
            return self.sim.getJointTargetVelocity(self.j4)
        elif (joint_name == "j5"):
            return self.sim.getJointTargetVelocity(self.j5)
        elif (joint_name == "r_fg"):
            return self.sim.getJointTargetVelocity(self.r_fg)
        elif (joint_name == "l_fg"):
            return self.sim.getJointTargetVelocity(self.l_fg)
        else:
            print("Joint name '" + str(joint_name) + "' does not exist" )

    def _get_joint_target_force(self,joint_name):
        if (joint_name == "j0"):
            return self.sim.getJointTargetForce(self.j0)
        elif (joint_name == "j1"):
            return self.sim.getJointTargetForce(self.j1)
        elif (joint_name == "j2"):
            return self.sim.getJointTargetForce(self.j2)
        elif (joint_name == "j3"):
            return self.sim.getJointTargetForce(self.j3)
        elif (joint_name == "j4"):
            return self.sim.getJointTargetForce(self.j4)
        elif (joint_name == "j5"):
            return self.sim.getJointTargetForce(self.j5)
        elif (joint_name == "r_fg"):
            return self.sim.getJointTargetForce(self.r_fg)
        elif (joint_name == "l_fg"):
            return self.sim.getJointTargetForce(self.l_fg)
        else:
            print("Joint name '" + str(joint_name) + "' does not exist" )

    def _set_joint_position(self,joint_name,val):
        if (joint_name == "j0"):
            self.sim.setJointTargetPosition(self.j0,val)
        elif (joint_name == "j1"):
            self.sim.setJointTargetPosition(self.j1,val)
        elif (joint_name == "j2"):
            self.sim.setJointTargetPosition(self.j2,val)
        elif (joint_name == "j3"):
            self.sim.setJointTargetPosition(self.j3,val)
        elif (joint_name == "j4"):
            self.sim.setJointTargetPosition(self.j4,val)
        elif (joint_name == "j5"):
            self.sim.setJointTargetPosition(self.j5,val)
        elif (joint_name == "r_fg"):
            self.sim.setJointTargetPosition(self.r_fg,val)
        elif (joint_name == "l_fg"):
            self.sim.setJointTargetPosition(self.l_fg,val)
        else:
            print("Joint name '" + str(joint_name) + "' does not exist" )

    def _set_joint_velocity(self,joint_name,val):
        if (joint_name == "j0"):
            self.sim.setJointTargetVelocity(self.j0,val)
        elif (joint_name == "j1"):
            self.sim.setJointTargetVelocity(self.j1,val)
        elif (joint_name == "j2"):
            self.sim.setJointTargetVelocity(self.j2,val)
        elif (joint_name == "j3"):
            self.sim.setJointTargetVelocity(self.j3,val)
        elif (joint_name == "j4"):
            self.sim.setJointTargetVelocity(self.j4,val)
        elif (joint_name == "j5"):
            self.sim.setJointTargetVelocity(self.j5,val)
        elif (joint_name == "r_fg"):
            self.sim.setJointTargetVelocity(self.r_fg,val)
        elif (joint_name == "l_fg"):
            self.sim.setJointTargetVelocity(self.l_fg,val)
        else:
            print("Joint name '" + str(joint_name) + "' does not exist" )

    def _set_joint_force(self,joint_name,val):
        if (joint_name == "j0"):
            self.sim.setJointTargetForce(self.j0,val)
        elif (joint_name == "j1"):
            self.sim.setJointTargetForce(self.j1,val)
        elif (joint_name == "j2"):
            self.sim.setJointTargetForce(self.j2,val)
        elif (joint_name == "j3"):
            self.sim.setJointTargetForce(self.j3,val)
        elif (joint_name == "j4"):
            self.sim.setJointTargetForce(self.j4,val)
        elif (joint_name == "j5"):
            self.sim.setJointTargetForce(self.j5,val)
        elif (joint_name == "r_fg"):
            self.sim.setJointTargetForce(self.r_fg,val)
        elif (joint_name == "l_fg"):
            self.sim.setJointTargetForce(self.l_fg,val)
        else:
            print("Joint name '" + str(joint_name) + "' does not exist" )

    def _get_cartesian_positions(self):
        fk_matrix = self.ur_robot_model.compute_fk(self.j0,self.j1,self.j2,self.j3,self.j4,self.j5)
        pose = fk_matrix[:,3]
        x = fk_matrix[:,3][0]
        y = fk_matrix[:,3][1]
        z = fk_matrix[:,3][2]
        rx = fk_matrix[0,0]
        ry = fk_matrix[1,1]
        rz = fk_matrix[2,2]
        return [x,y,z,rx,ry,rz]

    def _movediscrete(self,target_X,target_Y,target_Z):
        # To be initialized manually or with annotations
        x,yc,zc = self.ur_robot_model.compute_xyz_flexcell(target_X,target_Y,Z=target_Z)
        yj,zj = self.ur_robot_model.compute_yz_joint(yc,zc)
        target_position = self.ur_robot_model.compute_q(x,yj,zj)[0]
        self.sim.setJointTargetPosition(self.j0,target_position[0])
        self.sim.setJointTargetPosition(self.j1,target_position[1])
        self.sim.setJointTargetPosition(self.j2,target_position[2])
        self.sim.setJointTargetPosition(self.j3,target_position[3])
        self.sim.setJointTargetPosition(self.j4,target_position[4])
        self.sim.setJointTargetPosition(self.j5,target_position[5])

    def _movecartesian(self, target_x,target_y,target_z): # target_rx,target_ry,target_rz not available for now
        # To be initialized manually or with annotations
        target_position = self.ur_robot_model.compute_q(target_x,target_y,target_z)[0]
        self.sim.setJointTargetPosition(self.j0,target_position[0])
        self.sim.setJointTargetPosition(self.j1,target_position[1])
        self.sim.setJointTargetPosition(self.j2,target_position[2])
        self.sim.setJointTargetPosition(self.j3,target_position[3])
        self.sim.setJointTargetPosition(self.j4,target_position[4])
        self.sim.setJointTargetPosition(self.j5,target_position[5])

    def _movejoint(self,q0,q1,q2,q3,q4,q5):
        # To be initialized manually or with annotations
        '''self.sim.setJointTargetPosition(self.j0,q0)
        self.sim.setJointTargetPosition(self.j1,q1)
        self.sim.setJointTargetPosition(self.j2,q2)
        self.sim.setJointTargetPosition(self.j3,q3)
        self.sim.setJointTargetPosition(self.j4,q4)
        self.sim.setJointTargetPosition(self.j5,q5)'''

    def _stop(self): # Method not available
        self.sim.setJointTargetVelocity(self.j0,0.0)
        self.sim.setJointTargetVelocity(self.j1,0.0)
        self.sim.setJointTargetVelocity(self.j2,0.0)
        self.sim.setJointTargetVelocity(self.j3,0.0)
        self.sim.setJointTargetVelocity(self.j4,0.0)
        self.sim.setJointTargetVelocity(self.j5,0.0)

    def _pick(self): # To be implemented with a gripper
        print("Picking method to be implemented")

    def _place(self): # To be implemented with a gripper
        print("Placing method to be implemented")

    def _calculate_feasibility(self,target_X,target_Y,target_Z):
        feasible_motion = self.ur_robot_model.compute_ik_validity(target_X,target_Y,target_Z) # feasibleMoveDiscreteCommand
        return feasible_motion

'''if __name__=='__main__':
    mapping = Mapping()
    try:
        mapping.start_simulation()
        ## The args should come from the c++ code
        # The args could also come as a dict of dicts (with the variable names)
        args = {
            "equation_0": ["flexcellAngularPosition[completed]"]
        }
        result = mapping.get_event("moveCompleted",args=args)
        print(result)

        args = {
            "equation_0": ["flexcellAngularPosition[completed]"],
        }
        result = mapping.get_event("robotStopped",args=args)
        print(result)

        args = {
            "action_0":[0],
            "action_1":[-3.1415/2],
            "action_2":[-3.1415/2],
            "action_3":[0],
            "action_4":[0],
            "action_5":[0]
        }
        mapping.execute_operation("movejoint",args=args)
        time.sleep(5.0)
    finally:
        mapping.stop_simulation()
        print("Application stopped")
'''
