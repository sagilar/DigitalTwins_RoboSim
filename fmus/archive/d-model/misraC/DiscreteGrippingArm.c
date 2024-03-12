#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <math.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <ctype.h>

#include "DiscreteGrippingArm.h"

// Specific to FMI

//#include "include/model.h"
//#include "config.h"
//#include "util.h"
#include "fmu.h"

/***** Specific to FMI *****/
ModelInstance* fmiModel;

void init(ModelInstance* comp) {
		fmiModel = comp;
		setStartValues(comp);
		int tmp_x = comp->modelData.TARGET_X;
		int tmp_y = comp->modelData.TARGET_Y;
		int tmp_z = comp->modelData.TARGET_Z;
		printf("TargetX: %d\n", tmp_x);
		printf("TargetY: %d\n", tmp_y);
		printf("TargetZ: %d\n", tmp_z);
		bool tmp_term = comp->terminateSimulation;
		printf("Terminate sim: %d\n", tmp_term);
		//printf("FMIBuffer.booleanBuffer[1]: %d\n", comp->fmiBuffer.booleanBuffer[1]);
		printf("modeldata: %d\n", comp->modelData.TARGET_X);
		/*comp->modelData.MOTION_VEL = 0.0;
		comp->modelData.opening_diameter = 1.0;
		comp->modelData.av = 1.0;
		comp->modelData.TARGET_X = 2;
		comp->modelData.TARGET_Y = 2;
		comp->modelData.TARGET_Z = 2;
		comp->modelData.closing_speed = 1.0;
		comp->modelData.closing_force = 1.0;
		comp->modelData.closing_diameter = 1.0;
		comp->modelData.lv = 1.0;
		comp->modelData.opening_speed = 1.0;
		comp->modelData.opening_force = 1.0;*/
		printf("fmiModel_targetX: %d\n", fmiModel->modelData.target_X);
}




/*****   *****/
//ModelInstance *fmuModel = fmi2Instantiate();

/***** Specific to FMI *****/
void setStartValues(ModelInstance *comp) {
		comp->terminateSimulation = false;
		M(MOTION_VEL) = 0.0;
		M(opening_diameter) = 0.0;
		M(av) = 0.0;
		M(TARGET_X) = 2;
		M(TARGET_Y) = 3;
		M(TARGET_Z) = 4;
		M(target_X) = 1;
		M(target_Y) = 21;
		M(target_Z) = 3;
		M(closing_speed) = 0.0;
		M(closing_force) = 0.0;
		M(closing_diameter) = 0.0;
		M(lv) = 0.0;
		M(opening_speed) = 0.0;
		M(opening_force) = 0.0;

		M(gripperOpened) = false;
		M(robotStopped) = false;
		M(closeGripperCommand) = false;
		M(collision) = false;
		M(feasibleMoveDiscreteCommand) = false;
		M(gripperClosed) = false;
		M(nonfeasibleMoveDiscreteCommand) = false;
		M(moveCompleted) = false;
		M(openGripperCommand) = false;
		M(moveDiscreteCommand) = false;
		//sm_is.moveDiscreteCommand_value = false;

		M(gripperOpened) = false;
		M(robotStopped) = false;
		M(closeGripperCommand) = false;
		M(collision) = false;
		M(feasibleMoveDiscreteCommand) = false;
		M(gripperClosed) = false;
		M(nonfeasibleMoveDiscreteCommand) = false;
		M(moveCompleted) = false;
		M(openGripperCommand) = false;
		M(moveDiscreteCommand) = false;

		M(en_SimDiscreteGrippingArmMovement_ArmStop_1_done) = false;
		M(en_SimDiscreteGrippingArmMovement_ArmStop_1_counter) = 0;
		M(en_SimDiscreteGrippingArmMovement_GripperOpen_1_done) = false;
		M(en_SimDiscreteGrippingArmMovement_GripperOpen_1_counter) = 0;
		M(en_SimDiscreteGrippingArmMovement_GripperClose_1_done) = false;
		M(en_SimDiscreteGrippingArmMovement_GripperClose_1_counter) = 0;
		M(en_SimDiscreteGrippingArmMovement_ArmMove_1_done) = false;
		M(en_SimDiscreteGrippingArmMovement_ArmMove_1_counter) = 0;


}

Status getFloat64(ModelInstance* comp, ValueReference vr, double values[], size_t nValues, size_t* index) {

    //ASSERT_NVALUES(1);

    switch (vr) {
        case vr_time:
            values[(*index)++] = comp->time;
            return OK;
				case vr_MOTION_VEL:
						values[(*index)++] = M(MOTION_VEL);
						return OK;
        case vr_opening_diameter:
            values[(*index)++] = M(opening_diameter);
            return OK;
        case vr_av:
            values[(*index)++] = M(av);
            return OK;
        case vr_closing_speed:
            values[(*index)++] = M(closing_speed);
            return OK;
				case vr_closing_force:
            values[(*index)++] = M(closing_force);
            return OK;
				case vr_closing_diameter:
            values[(*index)++] = M(closing_diameter);
            return OK;
				case vr_lv:
            values[(*index)++] = M(lv);
            return OK;
        case vr_opening_speed:
            values[(*index)++] = M(opening_speed);
            return OK;
        case vr_opening_force:
            values[(*index)++] = M(opening_force);
            return OK;
        default:
            //logError(comp, "Get Float64 is not allowed for value reference %u.", vr);
            return Error;
    }
}

Status setFloat64(ModelInstance* comp, ValueReference vr, const double value[], size_t nValues, size_t* index) {

    //ASSERT_NVALUES(1);

    switch (vr) {
				case vr_MOTION_VEL:
						M(MOTION_VEL) = value[(*index)++];
						return OK;
				case vr_opening_diameter:
						M(opening_diameter) = value[(*index)++];
						return OK;
				case vr_av:
						M(av) = value[(*index)++];
						return OK;
				case vr_closing_speed:
						M(closing_speed) = value[(*index)++];
						return OK;
				case vr_closing_force:
						M(closing_force) = value[(*index)++];
						return OK;
				case vr_closing_diameter:
						M(closing_diameter) = value[(*index)++];
						return OK;
				case vr_lv:
						M(lv) = value[(*index)++];
						return OK;
				case vr_opening_speed:
						M(opening_speed) = value[(*index)++];
						return OK;
				case vr_opening_force:
						M(opening_force) = value[(*index)++];
						return OK;

        case vr_PI:
            //logError(comp, "Variable PI (value reference %u) is constant and cannot be set.", vr_PI);
            return Error;

        default:
            //logError(comp, "Unexpected value reference: %u.", vr);
            return Error;
    }
}

Status getBoolean(ModelInstance* comp, ValueReference vr, bool values[], size_t nValues, size_t* index) {

    //ASSERT_NVALUES(1);

    switch (vr) {
        case vr_en_SimDiscreteGrippingArmMovement_ArmStop_1_done:
            values[(*index)++] = M(en_SimDiscreteGrippingArmMovement_ArmStop_1_done);
            break;
        case vr_en_SimDiscreteGrippingArmMovement_GripperOpen_1_done:
            values[(*index)++] = M(en_SimDiscreteGrippingArmMovement_GripperOpen_1_done);
            break;
				case vr_en_SimDiscreteGrippingArmMovement_GripperClose_1_done:
            values[(*index)++] = M(en_SimDiscreteGrippingArmMovement_GripperClose_1_done);
            break;
				case vr_en_SimDiscreteGrippingArmMovement_ArmMove_1_done:
            values[(*index)++] = M(en_SimDiscreteGrippingArmMovement_ArmMove_1_done);
            break;
				case vr_gripperOpened:
            values[(*index)++] = M(gripperOpened);
            break;
        case vr_robotStopped:
            values[(*index)++] = M(robotStopped);
            break;
				case vr_closeGripperCommand:
            values[(*index)++] = M(closeGripperCommand);
            break;
				case vr_collision:
            values[(*index)++] = M(collision);
            break;
				case vr_feasibleMoveDiscreteCommand:
            values[(*index)++] = M(feasibleMoveDiscreteCommand);
            break;
				case vr_gripperClosed:
            values[(*index)++] = M(gripperClosed);
            break;
				case vr_nonfeasibleMoveDiscreteCommand:
            values[(*index)++] = M(nonfeasibleMoveDiscreteCommand);
            break;
        case vr_moveCompleted:
            values[(*index)++] = M(moveCompleted);
            break;
				case vr_openGripperCommand:
            values[(*index)++] = M(openGripperCommand);
            break;
				case vr_moveDiscreteCommand:
            values[(*index)++] = M(moveDiscreteCommand);
            break;
        default:
            //logError(comp, "Get Boolean is not allowed for value reference %u.", vr);
            return Error;
    }

    return OK;
}

Status setBoolean(ModelInstance* comp, ValueReference vr, const bool values[], size_t nValues, size_t* index) {

    //ASSERT_NVALUES(1);

    switch (vr) {
				case vr_en_SimDiscreteGrippingArmMovement_ArmStop_1_done:
						M(en_SimDiscreteGrippingArmMovement_ArmStop_1_done) = values[(*index)++];
						break;
				case vr_en_SimDiscreteGrippingArmMovement_GripperOpen_1_done:
						M(en_SimDiscreteGrippingArmMovement_GripperOpen_1_done) = values[(*index)++];
						break;
				case vr_en_SimDiscreteGrippingArmMovement_GripperClose_1_done:
						M(en_SimDiscreteGrippingArmMovement_GripperClose_1_done) = values[(*index)++];
						break;
				case vr_en_SimDiscreteGrippingArmMovement_ArmMove_1_done:
						M(en_SimDiscreteGrippingArmMovement_ArmMove_1_done) = values[(*index)++];
						break;
				case vr_gripperOpened:
						M(gripperOpened) = values[(*index)++];
						break;
				case vr_robotStopped:
						M(robotStopped) = values[(*index)++];
						break;
				case vr_closeGripperCommand:
						M(closeGripperCommand) = values[(*index)++];
						break;
				case vr_collision:
						M(collision) = values[(*index)++];
						break;
				case vr_feasibleMoveDiscreteCommand:
						M(feasibleMoveDiscreteCommand) = values[(*index)++];
						break;
				case vr_gripperClosed:
						M(gripperClosed) = values[(*index)++];
						break;
				case vr_nonfeasibleMoveDiscreteCommand:
						M(nonfeasibleMoveDiscreteCommand) = values[(*index)++];
						break;
				case vr_moveCompleted:
						M(moveCompleted) = values[(*index)++];
						break;
				case vr_openGripperCommand:
						M(openGripperCommand) = values[(*index)++];
						break;
				case vr_moveDiscreteCommand:
						M(moveDiscreteCommand) = values[(*index)++];
						break;
        default:
            //logError(comp, "Set Boolean is not allowed for value reference %u.", vr);
            return Error;
    }

    //comp->isDirtyValues = true;

    return OK;
}

Status getInteger(ModelInstance* comp, ValueReference vr, int values[], size_t nValues, size_t* index) {

    //ASSERT_NVALUES(1);

    switch (vr) {
        case vr_en_SimDiscreteGrippingArmMovement_ArmStop_1_counter:
            values[(*index)++] = M(en_SimDiscreteGrippingArmMovement_ArmStop_1_counter);
            break;
        case vr_en_SimDiscreteGrippingArmMovement_GripperOpen_1_counter:
            values[(*index)++] = M(en_SimDiscreteGrippingArmMovement_GripperOpen_1_counter);
            break;
				case vr_en_SimDiscreteGrippingArmMovement_GripperClose_1_counter:
            values[(*index)++] = M(en_SimDiscreteGrippingArmMovement_GripperClose_1_counter);
            break;
				case vr_en_SimDiscreteGrippingArmMovement_ArmMove_1_counter:
            values[(*index)++] = M(en_SimDiscreteGrippingArmMovement_ArmMove_1_counter);
            break;
				case vr_TARGET_Y:
            values[(*index)++] = M(TARGET_Y);
            break;
        case vr_TARGET_X:
            values[(*index)++] = M(TARGET_X);
            break;
				case vr_TARGET_Z:
            values[(*index)++] = M(TARGET_Z);
            break;
				case vr_target_Y:
            values[(*index)++] = M(target_Y);
            break;
        case vr_target_X:
            values[(*index)++] = M(target_X);
            break;
				case vr_target_Z:
            values[(*index)++] = M(target_Z);
            break;
        default:
            //logError(comp, "Get Integer is not allowed for value reference %u.", vr);
            return Error;
    }

    return OK;
}

Status setInteger(ModelInstance* comp, ValueReference vr, const int values[], size_t nValues, size_t* index) {

    //ASSERT_NVALUES(1);

    switch (vr) {
				case vr_en_SimDiscreteGrippingArmMovement_ArmStop_1_counter:
						M(en_SimDiscreteGrippingArmMovement_ArmStop_1_counter) = values[(*index)++];
						break;
				case vr_en_SimDiscreteGrippingArmMovement_GripperOpen_1_counter:
						M(en_SimDiscreteGrippingArmMovement_GripperOpen_1_counter) = values[(*index)++];
						break;
				case vr_en_SimDiscreteGrippingArmMovement_GripperClose_1_counter:
						M(en_SimDiscreteGrippingArmMovement_GripperClose_1_counter) = values[(*index)++];
						break;
				case vr_en_SimDiscreteGrippingArmMovement_ArmMove_1_counter:
						M(en_SimDiscreteGrippingArmMovement_ArmMove_1_counter) = values[(*index)++];
						break;
				case vr_TARGET_Y:
						M(TARGET_Y) = values[(*index)++];
						break;
				case vr_TARGET_X:
						M(TARGET_X) = values[(*index)++];
						break;
				case vr_TARGET_Z:
						M(TARGET_Z) = values[(*index)++];
						break;
				case vr_target_Y:
						M(target_Y) = values[(*index)++];
						break;
				case vr_target_X:
						M(target_X) = values[(*index)++];
						break;
				case vr_target_Z:
						M(target_Z) = values[(*index)++];
						break;
        default:
            //logError(comp, "Set Integer is not allowed for value reference %u.", vr);
            return Error;
    }

    //comp->isDirtyValues = true;

    return OK;
}

Status eventUpdate(ModelInstance *comp) {
		// TO BE UPDATED

    comp->valuesOfContinuousStatesChanged   = false;
    comp->nominalsOfContinuousStatesChanged = false;
    comp->terminateSimulation               = false;
    comp->nextEventTimeDefined              = false;
    return OK;
}


/***** *****/

#define DEBUG

#ifdef DEBUG
# define DPRINTF(arg) printf arg
#else
# define DPRINTF(arg)
#endif

#define err_abort(code,text) do { \
	fprintf(stderr, "%s at \"%s\":%d: %s\n", \
		text, __FILE__, __LINE__, strerror(code)); \
	abort(); \
	} while(0)

#define errno_abort(text) do { \
	fprintf(stderr, "%s at \"%s\":%d: %s\n", \
		text, __FILE__, __LINE__, strerror(errno)); \
	abort(); \
	} while (0)


// Temporary solution to trim strings taken from http://www.martinbroadhurst.com/trim-a-string-in-c.html

char *ltrim(char *str, const char *seps)
{
    size_t totrim;
    if (seps == NULL) {
        seps = "\t\n\v\f\r ";
    }
    totrim = strspn(str, seps);
    if (totrim > 0) {
        size_t len = strlen(str);
        if (totrim == len) {
            str[0] = '\0';
        }
        else {
            memmove(str, str + totrim, len + 1 - totrim);
        }
    }
    return str;
}

char *rtrim(char *str, const char *seps)
{
    int i;
    if (seps == NULL) {
        seps = "\t\n\v\f\r ";
    }
    i = strlen(str) - 1;
    while (i >= 0 && strchr(seps, str[i]) != NULL) {
        str[i] = '\0';
        i--;
    }
    return str;
}

char *trim(char *str, const char *seps)
{
    return ltrim(rtrim(str, seps), seps);
}

char* concat(char *str1, char *str2) {
	char* result = malloc(sizeof(char)*(strlen(str1)+strlen(str2)));
	char* s1 = strcat(result, str1);
	char* s2 = strcat(result, str2);
	return result;
}


FILE* log_file;





/* Declaration of function signatures */
	char* print_STATUS(STATUS_Enum* value);
	void mod_DiscreteGrippingArm_step(C_cm_input_Enum_Channel* start_cm
	                                  , C_cm_output_Enum_Channel* end_cm);
	void ctrl_cm_step(sm_input_Enum_Channel* start_sm
	                  , sm_output_Enum_Channel* end_sm);
	RESULT_Enum SimDiscreteGrippingArmMovement_J4(sm_state* state, sm_inputstate* inputstate, sm_memory* memorystate, sm_output_Enum_Channel* output);
	char* print_sm_state(sm_state* state);
	RESULT_Enum en_SimDiscreteGrippingArmMovement_ArmStop_1(sm_state* state, sm_inputstate* inputstate, sm_memory* memory, sm_output_Enum_Channel* output);
	RESULT_Enum en_SimDiscreteGrippingArmMovement_ArmMove_1(sm_state* state, sm_inputstate* inputstate, sm_memory* memory, sm_output_Enum_Channel* output);
	RESULT_Enum SimDiscreteGrippingArmMovement_J2(sm_state* state, sm_inputstate* inputstate, sm_memory* memorystate, sm_output_Enum_Channel* output);
	RESULT_Enum stm_sm_step(sm_state* state, sm_inputstate* inputstate, sm_memory* memorystate, sm_output_Enum_Channel* output);
	RESULT_Enum SimDiscreteGrippingArmMovement_J5(sm_state* state, sm_inputstate* inputstate, sm_memory* memorystate, sm_output_Enum_Channel* output);
	RESULT_Enum en_SimDiscreteGrippingArmMovement_GripperOpen_1(sm_state* state, sm_inputstate* inputstate, sm_memory* memory, sm_output_Enum_Channel* output);
	char* print_STATES_sm(STATES_sm_Enum* value);
	RESULT_Enum en_SimDiscreteGrippingArmMovement_GripperClose_1(sm_state* state, sm_inputstate* inputstate, sm_memory* memory, sm_output_Enum_Channel* output);
	RESULT_Enum SimDiscreteGrippingArmMovement_J3(sm_state* state, sm_inputstate* inputstate, sm_memory* memorystate, sm_output_Enum_Channel* output);

void *control(void *arg) {
	control_Channels* channels = (control_Channels*) arg;
	M_DiscreteGrippingArm_output_Enum_Channel* end_DiscreteGrippingArm = channels->end_DiscreteGrippingArm;
	M_DiscreteGrippingArm_input_Enum_Channel* start_DiscreteGrippingArm = channels->start_DiscreteGrippingArm;
{
	bool terminate__ = false;
	//while (!terminate__) {
		//terminate__ = true;
	while (!fmiModel->terminateSimulation) { // Model FMU until termination
		printf("Control loop\n");
		printf("TargetX2: %d\n", fmiModel->modelData.target_X);
		printf("TargetY2: %d\n", fmiModel->modelData.target_Y);
		printf("TargetZ2: %d\n", fmiModel->modelData.target_Z);
		fmiModel->modelData.moveDiscreteCommand = true;
		{

			bool inputdone = false;
			while (!inputdone) {
				inputdone = true;
				/*{
					char _s0[256];
					sprintf(_s0, "%s", "Enter an event:");
					printf("%s", _s0);
				}*
				char* _event_;
				char _temp_0[256];
				if (fgets(_temp_0, sizeof(_temp_0), stdin) == NULL) exit (0);
				_event_ = trim(_temp_0,NULL);
				if (strcmp(_event_, "closeGripperCommand") == 0) {*/
				if (fmiModel->modelData.closeGripperCommand){
					{
						char _s0[256];
						sprintf(_s0, "%s", "Found event closeGripperCommand");
						printf("%s\n", _s0);}
					{
						pthread_barrier_wait(&start_DiscreteGrippingArm->can_write);
						start_DiscreteGrippingArm->value = create_M_DiscreteGrippingArm_input_closeGripperCommand();
						pthread_barrier_wait(&start_DiscreteGrippingArm->can_read);
					}
				}
				//else if (strcmp(_event_, "nonfeasibleMoveDiscreteCommand") == 0) {
				else if (fmiModel->modelData.nonfeasibleMoveDiscreteCommand) {
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%s", "Found event nonfeasibleMoveDiscreteCommand");
				     		printf("%s\n", _s0);}
				     	{
				     		pthread_barrier_wait(&start_DiscreteGrippingArm->can_write);
				     		start_DiscreteGrippingArm->value = create_M_DiscreteGrippingArm_input_nonfeasibleMoveDiscreteCommand();
				     		pthread_barrier_wait(&start_DiscreteGrippingArm->can_read);
				     	}
				     }
				/*else if (strcmp(_event_, "") == 0) {
				     	{
				     		pthread_barrier_wait(&start_DiscreteGrippingArm->can_write);
				     		start_DiscreteGrippingArm->value = create_M_DiscreteGrippingArm_input__done_();
				     		pthread_barrier_wait(&start_DiscreteGrippingArm->can_read);
				     	}
				     	inputdone = true;
						}*/
				//else if (strcmp(_event_, "collision") == 0) {
				else if (fmiModel->modelData.collision) {
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%s", "Found event collision");
				     		printf("%s\n", _s0);}
				     	{
				     		pthread_barrier_wait(&start_DiscreteGrippingArm->can_write);
				     		start_DiscreteGrippingArm->value = create_M_DiscreteGrippingArm_input_collision();
				     		pthread_barrier_wait(&start_DiscreteGrippingArm->can_read);
				     	}
				     }
				//else if (strcmp(_event_, "gripperOpened") == 0) {
				else if (fmiModel->modelData.gripperOpened) {
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%s", "Found event gripperOpened");
				     		printf("%s\n", _s0);}
				     	{
				     		pthread_barrier_wait(&start_DiscreteGrippingArm->can_write);
				     		start_DiscreteGrippingArm->value = create_M_DiscreteGrippingArm_input_gripperOpened();
				     		pthread_barrier_wait(&start_DiscreteGrippingArm->can_read);
				     	}
				     }
				//else if (strcmp(_event_, "feasibleMoveDiscreteCommand") == 0) {
				else if (fmiModel->modelData.feasibleMoveDiscreteCommand) {
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%s", "Found event feasibleMoveDiscreteCommand");
				     		printf("%s\n", _s0);}
				     	{
				     		pthread_barrier_wait(&start_DiscreteGrippingArm->can_write);
				     		start_DiscreteGrippingArm->value = create_M_DiscreteGrippingArm_input_feasibleMoveDiscreteCommand();
				     		pthread_barrier_wait(&start_DiscreteGrippingArm->can_read);
				     	}
				     }
				//else if (strcmp(_event_, "openGripperCommand") == 0) {
			  else if (fmiModel->modelData.openGripperCommand) {
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%s", "Found event openGripperCommand");
				     		printf("%s\n", _s0);}
				     	{
				     		pthread_barrier_wait(&start_DiscreteGrippingArm->can_write);
				     		start_DiscreteGrippingArm->value = create_M_DiscreteGrippingArm_input_openGripperCommand();
				     		pthread_barrier_wait(&start_DiscreteGrippingArm->can_read);
				     	}
				     }
				//else if (strcmp(_event_, "robotStopped") == 0) {
				else if (fmiModel->modelData.robotStopped) {
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%s", "Found event robotStopped");
				     		printf("%s\n", _s0);}
				     	{
				     		pthread_barrier_wait(&start_DiscreteGrippingArm->can_write);
				     		start_DiscreteGrippingArm->value = create_M_DiscreteGrippingArm_input_robotStopped();
				     		pthread_barrier_wait(&start_DiscreteGrippingArm->can_read);
				     	}
				     }
				else if (fmiModel->modelData.moveCompleted) {
				//else if (strcmp(_event_, "moveCompleted") == 0) {
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%s", "Found event moveCompleted");
				     		printf("%s\n", _s0);}
				     	{
				     		pthread_barrier_wait(&start_DiscreteGrippingArm->can_write);
				     		start_DiscreteGrippingArm->value = create_M_DiscreteGrippingArm_input_moveCompleted();
				     		pthread_barrier_wait(&start_DiscreteGrippingArm->can_read);
				     	}
				     }
				//else if (strcmp(_event_, "gripperClosed") == 0) {
				else if (fmiModel->modelData.gripperClosed) {
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%s", "Found event gripperClosed");
				     		printf("%s\n", _s0);}
				     	{
				     		pthread_barrier_wait(&start_DiscreteGrippingArm->can_write);
				     		start_DiscreteGrippingArm->value = create_M_DiscreteGrippingArm_input_gripperClosed();
				     		pthread_barrier_wait(&start_DiscreteGrippingArm->can_read);
				     	}
				     }
				//else if (strcmp(_event_, "moveDiscreteCommand") == 0) {
				else if (fmiModel->modelData.moveDiscreteCommand) {
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%s", "Found event moveDiscreteCommand");
				     		printf("%s\n", _s0);}
				     	/*{
				     		char _s0[256];
				     		sprintf(_s0, "%s", "Enter value for event moveDiscreteCommand of type MovementArgs. Each attribute will be requested one at a time. ");
				     		printf("%s\n", _s0);}*/
				     	{
				     		/*MovementArgs _value_ = (MovementArgs) {
				     		                       	.target_X = 0
				     		                       	,
				     		                       	.target_Y = 0
				     		                       	,
				     		                       	.target_Z = 0
																			};*/
							 MovementArgs _value_ = (MovementArgs) {
				     		                       	.target_X = fmiModel->modelData.target_X
				     		                       	,
				     		                       	.target_Y = fmiModel->modelData.target_Y
				     		                       	,
				     		                       	.target_Z = fmiModel->modelData.target_Z
				     		                       };
				     		/*{
				     			{
				     				char _s0[256];
				     				sprintf(_s0, "%s", "Enter value for attribute target_X of type integer: ");
				     				printf("%s", _s0);
				     			}
				     			{
				     				char* _svalue_;
				     				char _temp_0[256];
				     				if (fgets(_temp_0, sizeof(_temp_0), stdin) == NULL) exit (0);
				     				_svalue_ = trim(_temp_0,NULL);
				     				int _target_X_value_ = 0;
				     				_target_X_value_ = atoi(_svalue_);
				     				(_value_).target_X = _target_X_value_;
				     			}
				     		}
				     		{
				     			{
				     				char _s0[256];
				     				sprintf(_s0, "%s", "Enter value for attribute target_Y of type integer: ");
				     				printf("%s", _s0);
				     			}
				     			{
				     				char* _svalue_;
				     				char _temp_0[256];
				     				if (fgets(_temp_0, sizeof(_temp_0), stdin) == NULL) exit (0);
				     				_svalue_ = trim(_temp_0,NULL);
				     				int _target_Y_value_ = 0;
				     				_target_Y_value_ = atoi(_svalue_);
				     				(_value_).target_Y = _target_Y_value_;
				     			}
				     		}
				     		{
				     			{
				     				char _s0[256];
				     				sprintf(_s0, "%s", "Enter value for attribute target_Z of type integer: ");
				     				printf("%s", _s0);
				     			}
				     			{
				     				char* _svalue_;
				     				char _temp_0[256];
				     				if (fgets(_temp_0, sizeof(_temp_0), stdin) == NULL) exit (0);
				     				_svalue_ = trim(_temp_0,NULL);
				     				int _target_Z_value_ = 0;
				     				_target_Z_value_ = atoi(_svalue_);
				     				(_value_).target_Z = _target_Z_value_;
				     			}
				     		}*/
				     		{
				     			pthread_barrier_wait(&start_DiscreteGrippingArm->can_write);
				     			start_DiscreteGrippingArm->value = create_M_DiscreteGrippingArm_input_moveDiscreteCommand(_value_);
				     			pthread_barrier_wait(&start_DiscreteGrippingArm->can_read);
				     		}
				     	}
				     }
				//else if (strcmp(_event_, "$end") == 0) {
				else if (fmiModel->terminateSimulation) {
				     	{
				     		pthread_barrier_wait(&start_DiscreteGrippingArm->can_write);
				     		start_DiscreteGrippingArm->value = create_M_DiscreteGrippingArm_input__terminate_();
				     		pthread_barrier_wait(&start_DiscreteGrippingArm->can_read);
				     	}
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%s", "Terminating system. One more cycle will run before this program ends.");
				     		printf("%s\n", _s0);}
				     	terminate__ = true;
				     	inputdone = true;
				     }
				else {
					{
						char _s0[256];
						//sprintf(_s0, "%s%s", "Unknown event: ", _event_);
						//printf("%s\n", _s0);}
						printf("Unknown event\n");}
				}
			}
		}
		{
			bool outputdone = false;
			while (!outputdone) {
				M_DiscreteGrippingArm_output_Enum _output_;
				{
					pthread_barrier_wait(&end_DiscreteGrippingArm->can_write);
					pthread_barrier_wait(&end_DiscreteGrippingArm->can_read);
					_output_ = end_DiscreteGrippingArm->value;
				}
				if (_output_.type == M_DiscreteGrippingArm_output_place) {
					float _aux1_ = _output_.data.place.v1;
					float _aux2_ = _output_.data.place.v2;
					float _aux3_ = _output_.data.place.v3;
					{
						char _s0[256];
						sprintf(_s0, "%s", "output place");
						printf("%s", _s0);
					}
					{
						char _s0[256];
						sprintf(_s0, "%s", "(");
						printf("%s", _s0);
					}
					{
						char _s0[256];
						sprintf(_s0, "%f", _aux1_);
						printf("%s", _s0);
					}
					{
						char _s0[256];
						sprintf(_s0, "%s", ",");
						printf("%s", _s0);
					}
					{
						char _s0[256];
						sprintf(_s0, "%f", _aux2_);
						printf("%s", _s0);
					}
					{
						char _s0[256];
						sprintf(_s0, "%s", ",");
						printf("%s", _s0);
					}
					{
						char _s0[256];
						sprintf(_s0, "%f", _aux3_);
						printf("%s", _s0);
					}
					{
						char _s0[256];
						sprintf(_s0, "%s", ")");
						printf("%s\n", _s0);}
				}
				else if (_output_.type == M_DiscreteGrippingArm_output_movejoint) {
				     	float _aux1_ = _output_.data.movejoint.v1;
				     	float _aux2_ = _output_.data.movejoint.v2;
				     	float _aux3_ = _output_.data.movejoint.v3;
				     	float _aux4_ = _output_.data.movejoint.v4;
				     	float _aux5_ = _output_.data.movejoint.v5;
				     	float _aux6_ = _output_.data.movejoint.v6;
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%s", "output movejoint");
				     		printf("%s", _s0);
				     	}
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%s", "(");
				     		printf("%s", _s0);
				     	}
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%f", _aux1_);
				     		printf("%s", _s0);
				     	}
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%s", ",");
				     		printf("%s", _s0);
				     	}
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%f", _aux2_);
				     		printf("%s", _s0);
				     	}
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%s", ",");
				     		printf("%s", _s0);
				     	}
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%f", _aux3_);
				     		printf("%s", _s0);
				     	}
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%s", ",");
				     		printf("%s", _s0);
				     	}
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%f", _aux4_);
				     		printf("%s", _s0);
				     	}
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%s", ",");
				     		printf("%s", _s0);
				     	}
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%f", _aux5_);
				     		printf("%s", _s0);
				     	}
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%s", ",");
				     		printf("%s", _s0);
				     	}
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%f", _aux6_);
				     		printf("%s", _s0);
				     	}
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%s", ")");
				     		printf("%s\n", _s0);}
				     }
				else if (_output_.type == M_DiscreteGrippingArm_output_stop) {
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%s", "output stop");
				     		printf("%s\n", _s0);}
				     }
				else if (_output_.type == M_DiscreteGrippingArm_output_movecartesian) {
				     	float _aux1_ = _output_.data.movecartesian.v1;
				     	float _aux2_ = _output_.data.movecartesian.v2;
				     	float _aux3_ = _output_.data.movecartesian.v3;
				     	float _aux4_ = _output_.data.movecartesian.v4;
				     	float _aux5_ = _output_.data.movecartesian.v5;
				     	float _aux6_ = _output_.data.movecartesian.v6;
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%s", "output movecartesian");
				     		printf("%s", _s0);
				     	}
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%s", "(");
				     		printf("%s", _s0);
				     	}
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%f", _aux1_);
				     		printf("%s", _s0);
				     	}
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%s", ",");
				     		printf("%s", _s0);
				     	}
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%f", _aux2_);
				     		printf("%s", _s0);
				     	}
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%s", ",");
				     		printf("%s", _s0);
				     	}
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%f", _aux3_);
				     		printf("%s", _s0);
				     	}
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%s", ",");
				     		printf("%s", _s0);
				     	}
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%f", _aux4_);
				     		printf("%s", _s0);
				     	}
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%s", ",");
				     		printf("%s", _s0);
				     	}
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%f", _aux5_);
				     		printf("%s", _s0);
				     	}
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%s", ",");
				     		printf("%s", _s0);
				     	}
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%f", _aux6_);
				     		printf("%s", _s0);
				     	}
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%s", ")");
				     		printf("%s\n", _s0);}
				     }
				else if (_output_.type == M_DiscreteGrippingArm_output_setvelocity) {
				     	float _aux1_ = _output_.data.setvelocity.v1;
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%s", "output setvelocity");
				     		printf("%s", _s0);
				     	}
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%s", "(");
				     		printf("%s", _s0);
				     	}
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%f", _aux1_);
				     		printf("%s", _s0);
				     	}
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%s", ")");
				     		printf("%s\n", _s0);}
				     }
				else if (_output_.type == M_DiscreteGrippingArm_output_movediscrete) {
				     	int _aux1_ = _output_.data.movediscrete.v1;
				     	int _aux2_ = _output_.data.movediscrete.v2;
				     	int _aux3_ = _output_.data.movediscrete.v3;
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%s", "output movediscrete");
				     		printf("%s", _s0);
				     	}
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%s", "(");
				     		printf("%s", _s0);
				     	}
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%d", _aux1_);
				     		printf("%s", _s0);
				     	}
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%s", ",");
				     		printf("%s", _s0);
				     	}
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%d", _aux2_);
				     		printf("%s", _s0);
				     	}
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%s", ",");
				     		printf("%s", _s0);
				     	}
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%d", _aux3_);
				     		printf("%s", _s0);
				     	}
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%s", ")");
				     		printf("%s\n", _s0);}
				     }
				else if (_output_.type == M_DiscreteGrippingArm_output_pick) {
				     	float _aux1_ = _output_.data.pick.v1;
				     	float _aux2_ = _output_.data.pick.v2;
				     	float _aux3_ = _output_.data.pick.v3;
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%s", "output pick");
				     		printf("%s", _s0);
				     	}
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%s", "(");
				     		printf("%s", _s0);
				     	}
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%f", _aux1_);
				     		printf("%s", _s0);
				     	}
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%s", ",");
				     		printf("%s", _s0);
				     	}
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%f", _aux2_);
				     		printf("%s", _s0);
				     	}
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%s", ",");
				     		printf("%s", _s0);
				     	}
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%f", _aux3_);
				     		printf("%s", _s0);
				     	}
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%s", ")");
				     		printf("%s\n", _s0);}
				     }
				else if (_output_.type == M_DiscreteGrippingArm_output__done_) {
				     	outputdone = true;
				     	{
				     		char _s0[256];
				     		sprintf(_s0, "%s", "---------------------");
				     		printf("%s\n", _s0);}
				     }
			}

		}
	}
}
}
typedef struct {
	M_DiscreteGrippingArm_input_Enum_Channel* start_DiscreteGrippingArm;
	C_cm_output_Enum_Channel* end_cm;
	M_DiscreteGrippingArm_output_Enum_Channel* end_DiscreteGrippingArm;
	C_cm_input_Enum_Channel* start_cm;
} mod_DiscreteGrippingArm_thread_Channels;

/* Declaration of function signatures */
	char* print_STATUS(STATUS_Enum* value);
	void mod_DiscreteGrippingArm_step(C_cm_input_Enum_Channel* start_cm
	                                  , C_cm_output_Enum_Channel* end_cm);
	void ctrl_cm_step(sm_input_Enum_Channel* start_sm
	                  , sm_output_Enum_Channel* end_sm);
	RESULT_Enum SimDiscreteGrippingArmMovement_J4(sm_state* state, sm_inputstate* inputstate, sm_memory* memorystate, sm_output_Enum_Channel* output);
	char* print_sm_state(sm_state* state);
	RESULT_Enum en_SimDiscreteGrippingArmMovement_ArmStop_1(sm_state* state, sm_inputstate* inputstate, sm_memory* memory, sm_output_Enum_Channel* output);
	RESULT_Enum en_SimDiscreteGrippingArmMovement_ArmMove_1(sm_state* state, sm_inputstate* inputstate, sm_memory* memory, sm_output_Enum_Channel* output);
	RESULT_Enum SimDiscreteGrippingArmMovement_J2(sm_state* state, sm_inputstate* inputstate, sm_memory* memorystate, sm_output_Enum_Channel* output);
	RESULT_Enum stm_sm_step(sm_state* state, sm_inputstate* inputstate, sm_memory* memorystate, sm_output_Enum_Channel* output);
	RESULT_Enum SimDiscreteGrippingArmMovement_J5(sm_state* state, sm_inputstate* inputstate, sm_memory* memorystate, sm_output_Enum_Channel* output);
	RESULT_Enum en_SimDiscreteGrippingArmMovement_GripperOpen_1(sm_state* state, sm_inputstate* inputstate, sm_memory* memory, sm_output_Enum_Channel* output);
	char* print_STATES_sm(STATES_sm_Enum* value);
	RESULT_Enum en_SimDiscreteGrippingArmMovement_GripperClose_1(sm_state* state, sm_inputstate* inputstate, sm_memory* memory, sm_output_Enum_Channel* output);
	RESULT_Enum SimDiscreteGrippingArmMovement_J3(sm_state* state, sm_inputstate* inputstate, sm_memory* memorystate, sm_output_Enum_Channel* output);

void *mod_DiscreteGrippingArm_thread(void *arg) {
	mod_DiscreteGrippingArm_thread_Channels* channels = (mod_DiscreteGrippingArm_thread_Channels*) arg;
	M_DiscreteGrippingArm_input_Enum_Channel* start_DiscreteGrippingArm = channels->start_DiscreteGrippingArm;
	C_cm_output_Enum_Channel* end_cm = channels->end_cm;
	M_DiscreteGrippingArm_output_Enum_Channel* end_DiscreteGrippingArm = channels->end_DiscreteGrippingArm;
	C_cm_input_Enum_Channel* start_cm = channels->start_cm;
{
	bool terminate__ = false;
	while (!terminate__) {
		{
			bool inputDone = false;
			while (!inputDone) {
				{
					char _s0[256];
					sprintf(_s0, "%s", "- Waiting for input on channel start_DiscreteGrippingArm");
					fprintf(log_file, "DEBUG: %s\n", _s0);
				}
				M_DiscreteGrippingArm_input_Enum _input_;
				{
					pthread_barrier_wait(&start_DiscreteGrippingArm->can_write);
					pthread_barrier_wait(&start_DiscreteGrippingArm->can_read);
					_input_ = start_DiscreteGrippingArm->value;
				}
				{
					char _s0[256];
					sprintf(_s0, "%s", "- Read input on channel start_DiscreteGrippingArm");
					fprintf(log_file, "DEBUG: %s\n", _s0);
				}
				if (_input_.type == M_DiscreteGrippingArm_input_gripperOpened) {
					{
						pthread_barrier_wait(&start_cm->can_write);
						start_cm->value = create_C_cm_input_gripperOpened();
						pthread_barrier_wait(&start_cm->can_read);
					}
				}
				else if (_input_.type == M_DiscreteGrippingArm_input_moveDiscreteCommand) {
				     	MovementArgs _aux1_ = _input_.data.moveDiscreteCommand.v1;
				     	{
				     		pthread_barrier_wait(&start_cm->can_write);
				     		start_cm->value = create_C_cm_input_moveDiscreteCommand(_aux1_);
				     		pthread_barrier_wait(&start_cm->can_read);
				     	}
				     }
				else if (_input_.type == M_DiscreteGrippingArm_input_moveCompleted) {
				     	{
				     		pthread_barrier_wait(&start_cm->can_write);
				     		start_cm->value = create_C_cm_input_moveCompleted();
				     		pthread_barrier_wait(&start_cm->can_read);
				     	}
				     }
				else if (_input_.type == M_DiscreteGrippingArm_input_openGripperCommand) {
				     	{
				     		pthread_barrier_wait(&start_cm->can_write);
				     		start_cm->value = create_C_cm_input_openGripperCommand();
				     		pthread_barrier_wait(&start_cm->can_read);
				     	}
				     }
				else if (_input_.type == M_DiscreteGrippingArm_input_feasibleMoveDiscreteCommand) {
				     	{
				     		pthread_barrier_wait(&start_cm->can_write);
				     		start_cm->value = create_C_cm_input_feasibleMoveDiscreteCommand();
				     		pthread_barrier_wait(&start_cm->can_read);
				     	}
				     }
				else if (_input_.type == M_DiscreteGrippingArm_input_robotStopped) {
				     	{
				     		pthread_barrier_wait(&start_cm->can_write);
				     		start_cm->value = create_C_cm_input_robotStopped();
				     		pthread_barrier_wait(&start_cm->can_read);
				     	}
				     }
				else if (_input_.type == M_DiscreteGrippingArm_input_collision) {
				     	{
				     		pthread_barrier_wait(&start_cm->can_write);
				     		start_cm->value = create_C_cm_input_collision();
				     		pthread_barrier_wait(&start_cm->can_read);
				     	}
				     }
				else if (_input_.type == M_DiscreteGrippingArm_input_gripperClosed) {
				     	{
				     		pthread_barrier_wait(&start_cm->can_write);
				     		start_cm->value = create_C_cm_input_gripperClosed();
				     		pthread_barrier_wait(&start_cm->can_read);
				     	}
				     }
				else if (_input_.type == M_DiscreteGrippingArm_input_closeGripperCommand) {
				     	{
				     		pthread_barrier_wait(&start_cm->can_write);
				     		start_cm->value = create_C_cm_input_closeGripperCommand();
				     		pthread_barrier_wait(&start_cm->can_read);
				     	}
				     }
				else if (_input_.type == M_DiscreteGrippingArm_input_nonfeasibleMoveDiscreteCommand) {
				     	{
				     		pthread_barrier_wait(&start_cm->can_write);
				     		start_cm->value = create_C_cm_input_nonfeasibleMoveDiscreteCommand();
				     		pthread_barrier_wait(&start_cm->can_read);
				     	}
				     }
				else if (_input_.type == M_DiscreteGrippingArm_input__done_) {
				     	{
				     		pthread_barrier_wait(&start_cm->can_write);
				     		start_cm->value = create_C_cm_input__done_();
				     		pthread_barrier_wait(&start_cm->can_read);
				     	}
				     	inputDone = true;
				     }
				else if (_input_.type == M_DiscreteGrippingArm_input__terminate_) {
				     	{
				     		pthread_barrier_wait(&start_cm->can_write);
				     		start_cm->value = create_C_cm_input__terminate_();
				     		pthread_barrier_wait(&start_cm->can_read);
				     	}
				     	terminate__ = true;
				     }
			}

		}
		{
			char _s0[256];
			sprintf(_s0, "%s", "Finished reading inputs of module DiscreteGrippingArm");
			fprintf(log_file, "DEBUG: %s\n", _s0);
		}
		mod_DiscreteGrippingArm_step(start_cm
		                             , end_cm);
		{
			bool outputDone = false;
			while (!outputDone) {
				C_cm_output_Enum _output_;
				{
					pthread_barrier_wait(&end_cm->can_write);
					pthread_barrier_wait(&end_cm->can_read);
					_output_ = end_cm->value;
				}
				if (_output_.type == C_cm_output_place) {
					float _aux1_ = _output_.data.place.v1;
					float _aux2_ = _output_.data.place.v2;
					float _aux3_ = _output_.data.place.v3;
					{
						pthread_barrier_wait(&end_DiscreteGrippingArm->can_write);
						end_DiscreteGrippingArm->value = create_M_DiscreteGrippingArm_output_place(_aux1_
						                                                                           ,_aux2_
						                                                                           ,_aux3_);
						pthread_barrier_wait(&end_DiscreteGrippingArm->can_read);
					}
				}
				else if (_output_.type == C_cm_output_stop) {
				     	{
				     		pthread_barrier_wait(&end_DiscreteGrippingArm->can_write);
				     		end_DiscreteGrippingArm->value = create_M_DiscreteGrippingArm_output_stop();
				     		pthread_barrier_wait(&end_DiscreteGrippingArm->can_read);
				     	}
				     }
				else if (_output_.type == C_cm_output_movediscrete) {
				     	int _aux1_ = _output_.data.movediscrete.v1;
				     	int _aux2_ = _output_.data.movediscrete.v2;
				     	int _aux3_ = _output_.data.movediscrete.v3;
				     	{
				     		pthread_barrier_wait(&end_DiscreteGrippingArm->can_write);
				     		end_DiscreteGrippingArm->value = create_M_DiscreteGrippingArm_output_movediscrete(_aux1_
				     		                                                                                  ,_aux2_
				     		                                                                                  ,_aux3_);
				     		pthread_barrier_wait(&end_DiscreteGrippingArm->can_read);
				     	}
				     }
				else if (_output_.type == C_cm_output_movejoint) {
				     	float _aux1_ = _output_.data.movejoint.v1;
				     	float _aux2_ = _output_.data.movejoint.v2;
				     	float _aux3_ = _output_.data.movejoint.v3;
				     	float _aux4_ = _output_.data.movejoint.v4;
				     	float _aux5_ = _output_.data.movejoint.v5;
				     	float _aux6_ = _output_.data.movejoint.v6;
				     	{
				     		pthread_barrier_wait(&end_DiscreteGrippingArm->can_write);
				     		end_DiscreteGrippingArm->value = create_M_DiscreteGrippingArm_output_movejoint(_aux1_
				     		                                                                               ,_aux2_
				     		                                                                               ,_aux3_
				     		                                                                               ,_aux4_
				     		                                                                               ,_aux5_
				     		                                                                               ,_aux6_);
				     		pthread_barrier_wait(&end_DiscreteGrippingArm->can_read);
				     	}
				     }
				else if (_output_.type == C_cm_output_movecartesian) {
				     	float _aux1_ = _output_.data.movecartesian.v1;
				     	float _aux2_ = _output_.data.movecartesian.v2;
				     	float _aux3_ = _output_.data.movecartesian.v3;
				     	float _aux4_ = _output_.data.movecartesian.v4;
				     	float _aux5_ = _output_.data.movecartesian.v5;
				     	float _aux6_ = _output_.data.movecartesian.v6;
				     	{
				     		pthread_barrier_wait(&end_DiscreteGrippingArm->can_write);
				     		end_DiscreteGrippingArm->value = create_M_DiscreteGrippingArm_output_movecartesian(_aux1_
				     		                                                                                   ,_aux2_
				     		                                                                                   ,_aux3_
				     		                                                                                   ,_aux4_
				     		                                                                                   ,_aux5_
				     		                                                                                   ,_aux6_);
				     		pthread_barrier_wait(&end_DiscreteGrippingArm->can_read);
				     	}
				     }
				else if (_output_.type == C_cm_output_pick) {
				     	float _aux1_ = _output_.data.pick.v1;
				     	float _aux2_ = _output_.data.pick.v2;
				     	float _aux3_ = _output_.data.pick.v3;
				     	{
				     		pthread_barrier_wait(&end_DiscreteGrippingArm->can_write);
				     		end_DiscreteGrippingArm->value = create_M_DiscreteGrippingArm_output_pick(_aux1_
				     		                                                                          ,_aux2_
				     		                                                                          ,_aux3_);
				     		pthread_barrier_wait(&end_DiscreteGrippingArm->can_read);
				     	}
				     }
				else if (_output_.type == C_cm_output_setvelocity) {
				     	float _aux1_ = _output_.data.setvelocity.v1;
				     	{
				     		pthread_barrier_wait(&end_DiscreteGrippingArm->can_write);
				     		end_DiscreteGrippingArm->value = create_M_DiscreteGrippingArm_output_setvelocity(_aux1_);
				     		pthread_barrier_wait(&end_DiscreteGrippingArm->can_read);
				     	}
				     }
				else if (_output_.type == C_cm_output__done_) {
				     	{
				     		pthread_barrier_wait(&end_DiscreteGrippingArm->can_write);
				     		end_DiscreteGrippingArm->value = create_M_DiscreteGrippingArm_output__done_();
				     		pthread_barrier_wait(&end_DiscreteGrippingArm->can_read);
				     	}
				     	outputDone = true;
				     }
			}

		}
	}
}
}
typedef struct {
	sm_input_Enum_Channel* start_sm;
	sm_output_Enum_Channel* end_sm;
} stm_sm_Channels;

/* Declaration of function signatures */
	char* print_STATUS(STATUS_Enum* value);
	void mod_DiscreteGrippingArm_step(C_cm_input_Enum_Channel* start_cm
	                                  , C_cm_output_Enum_Channel* end_cm);
	void ctrl_cm_step(sm_input_Enum_Channel* start_sm
	                  , sm_output_Enum_Channel* end_sm);
	RESULT_Enum SimDiscreteGrippingArmMovement_J4(sm_state* state, sm_inputstate* inputstate, sm_memory* memorystate, sm_output_Enum_Channel* output);
	char* print_sm_state(sm_state* state);
	RESULT_Enum en_SimDiscreteGrippingArmMovement_ArmStop_1(sm_state* state, sm_inputstate* inputstate, sm_memory* memory, sm_output_Enum_Channel* output);
	RESULT_Enum en_SimDiscreteGrippingArmMovement_ArmMove_1(sm_state* state, sm_inputstate* inputstate, sm_memory* memory, sm_output_Enum_Channel* output);
	RESULT_Enum SimDiscreteGrippingArmMovement_J2(sm_state* state, sm_inputstate* inputstate, sm_memory* memorystate, sm_output_Enum_Channel* output);
	RESULT_Enum stm_sm_step(sm_state* state, sm_inputstate* inputstate, sm_memory* memorystate, sm_output_Enum_Channel* output);
	RESULT_Enum SimDiscreteGrippingArmMovement_J5(sm_state* state, sm_inputstate* inputstate, sm_memory* memorystate, sm_output_Enum_Channel* output);
	RESULT_Enum en_SimDiscreteGrippingArmMovement_GripperOpen_1(sm_state* state, sm_inputstate* inputstate, sm_memory* memory, sm_output_Enum_Channel* output);
	char* print_STATES_sm(STATES_sm_Enum* value);
	RESULT_Enum en_SimDiscreteGrippingArmMovement_GripperClose_1(sm_state* state, sm_inputstate* inputstate, sm_memory* memory, sm_output_Enum_Channel* output);
	RESULT_Enum SimDiscreteGrippingArmMovement_J3(sm_state* state, sm_inputstate* inputstate, sm_memory* memorystate, sm_output_Enum_Channel* output);

void *stm_sm(void *arg) {
	stm_sm_Channels* channels = (stm_sm_Channels*) arg;
	sm_input_Enum_Channel* start_sm = channels->start_sm;
	sm_output_Enum_Channel* end_sm = channels->end_sm;
{
	// state machine variable declarations;
	sm_inputstate inputstate = (sm_inputstate) {
	                           	.gripperOpened = false,
	                           	.robotStopped = false,
	                           	.closeGripperCommand = false,
	                           	.collision = false,
	                           	.feasibleMoveDiscreteCommand = false,
	                           	.gripperClosed = false,
	                           	.nonfeasibleMoveDiscreteCommand = false,
	                           	.moveCompleted = false,
	                           	.openGripperCommand = false,
	                           	.moveDiscreteCommand = false,
	                           	.moveDiscreteCommand_value = (MovementArgs) {
	                           		.target_X = 0
	                           		,
	                           		.target_Y = 0
	                           		,
	                           		.target_Z = 0
	                           	},
	                           	._transition_ = create_TRANSITIONS_sm_NONE()
	                           };
	sm_state state = (sm_state) {
	                 	.done = false,
	                 	.state = create_STATES_sm_NONE(),
	                 	.target_state = create_STATES_sm_NONE(),
	                 	.status = create_STATUS_ENTER_STATE(),
	                 	.en_SimDiscreteGrippingArmMovement_ArmStop_1_done = false,
	                 	.en_SimDiscreteGrippingArmMovement_ArmStop_1_counter = 0
	                 	,
	                 	.en_SimDiscreteGrippingArmMovement_GripperOpen_1_done = false,
	                 	.en_SimDiscreteGrippingArmMovement_GripperOpen_1_counter = 0
	                 	,
	                 	.en_SimDiscreteGrippingArmMovement_GripperClose_1_done = false,
	                 	.en_SimDiscreteGrippingArmMovement_GripperClose_1_counter = 0
	                 	,
	                 	.en_SimDiscreteGrippingArmMovement_ArmMove_1_done = false,
	                 	.en_SimDiscreteGrippingArmMovement_ArmMove_1_counter = 0
	                 };
	sm_memory memorystate = (sm_memory) {
	                        	.MOTION_VEL = 0.0
	                        	,
	                        	.opening_diameter = 0.0
	                        	,
	                        	.PI = 0.0
	                        	,
	                        	.av = 0.0
	                        	,
	                        	.TARGET_Y = 0
	                        	,
	                        	.closing_speed = 0.0
	                        	,
	                        	.closing_force = 0.0
	                        	,
	                        	.closing_diameter = 0.0
	                        	,
	                        	.lv = 0.0
	                        	,
	                        	.opening_speed = 0.0
	                        	,
	                        	.margs = (MovementArgs) {
	                        		.target_X = 0
	                        		,
	                        		.target_Y = 0
	                        		,
	                        		.target_Z = 0
	                        	},
	                        	.opening_force = 0.0
	                        	,
	                        	.TARGET_X = 0
	                        	,
	                        	.TARGET_Z = 0
	                        };
	// state machine loop;
	while (!(state).done) {
		{
			{
				char _s0[256];
				sprintf(_s0, "%s", "- Waiting for input on channel start_sm");
				fprintf(log_file, "DEBUG: %s\n", _s0);
			}
			bool inputDone = false;
			while (!inputDone) {
				sm_input_Enum _input_;
				{
					pthread_barrier_wait(&start_sm->can_write);
					pthread_barrier_wait(&start_sm->can_read);
					_input_ = start_sm->value;
				}
				{
					char _s0[256];
					sprintf(_s0, "%s", "- Read input on channel start_sm");
					fprintf(log_file, "DEBUG: %s\n", _s0);
				}
				if (_input_.type == sm_input_gripperOpened) {
					(inputstate).gripperOpened = true;
				}
				else if (_input_.type == sm_input_robotStopped) {
				     	(inputstate).robotStopped = true;
				     }
				else if (_input_.type == sm_input_closeGripperCommand) {
				     	(inputstate).closeGripperCommand = true;
				     }
				else if (_input_.type == sm_input_collision) {
				     	(inputstate).collision = true;
				     }
				else if (_input_.type == sm_input_feasibleMoveDiscreteCommand) {
				     	(inputstate).feasibleMoveDiscreteCommand = true;
				     }
				else if (_input_.type == sm_input_gripperClosed) {
				     	(inputstate).gripperClosed = true;
				     }
				else if (_input_.type == sm_input_nonfeasibleMoveDiscreteCommand) {
				     	(inputstate).nonfeasibleMoveDiscreteCommand = true;
				     }
				else if (_input_.type == sm_input_moveCompleted) {
				     	(inputstate).moveCompleted = true;
				     }
				else if (_input_.type == sm_input_openGripperCommand) {
				     	(inputstate).openGripperCommand = true;
				     }
				else if (_input_.type == sm_input_moveDiscreteCommand) {
							//printf("MoveArm state\n"); //update santiago
				     	MovementArgs _aux_ = _input_.data.moveDiscreteCommand.v1;
				     	(inputstate).moveDiscreteCommand = true;
				     	(inputstate).moveDiscreteCommand_value = _aux_;
				     }
				else if (_input_.type == sm_input__done_) {
				     	inputDone = true;
				     }
				else if (_input_.type == sm_input__terminate_) {
				     	inputDone = true;
				     }
			}
		}
		RESULT_Enum ret = create_RESULT_CONT();
		while (	ret.type == create_RESULT_CONT().type
		        ) {
			char* temp_;
			temp_ = print_sm_state(&state);
			{
				char _s0[256];
				sprintf(_s0, "%s", temp_);
				fprintf(log_file, "DEBUG: %s\n", _s0);
			}
			ret = stm_sm_step(&state, &inputstate, &memorystate, end_sm);
		}
		{
			pthread_barrier_wait(&end_sm->can_write);
			end_sm->value = create_sm_output__done_();
			pthread_barrier_wait(&end_sm->can_read);
		}
		// update clocks;
		// reset input events;
		(inputstate).collision = false;
		(inputstate).gripperOpened = false;
		(inputstate).closeGripperCommand = false;
		(inputstate).robotStopped = false;
		(inputstate).moveCompleted = false;
		(inputstate).gripperClosed = false;
		(inputstate).feasibleMoveDiscreteCommand = false;
		(inputstate).openGripperCommand = false;
		(inputstate).moveDiscreteCommand = false;
		(inputstate).nonfeasibleMoveDiscreteCommand = false;
		{
			char _s0[256];
			sprintf(_s0, "%s", "		Sent output _done_ on channel end_sm");
			fprintf(log_file, "DEBUG: %s\n", _s0);
		}

	}
}
}
typedef struct {
	C_cm_input_Enum_Channel* start_cm;
	sm_output_Enum_Channel* end_sm;
	C_cm_output_Enum_Channel* end_cm;
	sm_input_Enum_Channel* start_sm;
} ctrl_cm_thread_Channels;

/* Declaration of function signatures */
	char* print_STATUS(STATUS_Enum* value);
	void mod_DiscreteGrippingArm_step(C_cm_input_Enum_Channel* start_cm
	                                  , C_cm_output_Enum_Channel* end_cm);
	void ctrl_cm_step(sm_input_Enum_Channel* start_sm
	                  , sm_output_Enum_Channel* end_sm);
	RESULT_Enum SimDiscreteGrippingArmMovement_J4(sm_state* state, sm_inputstate* inputstate, sm_memory* memorystate, sm_output_Enum_Channel* output);
	char* print_sm_state(sm_state* state);
	RESULT_Enum en_SimDiscreteGrippingArmMovement_ArmStop_1(sm_state* state, sm_inputstate* inputstate, sm_memory* memory, sm_output_Enum_Channel* output);
	RESULT_Enum en_SimDiscreteGrippingArmMovement_ArmMove_1(sm_state* state, sm_inputstate* inputstate, sm_memory* memory, sm_output_Enum_Channel* output);
	RESULT_Enum SimDiscreteGrippingArmMovement_J2(sm_state* state, sm_inputstate* inputstate, sm_memory* memorystate, sm_output_Enum_Channel* output);
	RESULT_Enum stm_sm_step(sm_state* state, sm_inputstate* inputstate, sm_memory* memorystate, sm_output_Enum_Channel* output);
	RESULT_Enum SimDiscreteGrippingArmMovement_J5(sm_state* state, sm_inputstate* inputstate, sm_memory* memorystate, sm_output_Enum_Channel* output);
	RESULT_Enum en_SimDiscreteGrippingArmMovement_GripperOpen_1(sm_state* state, sm_inputstate* inputstate, sm_memory* memory, sm_output_Enum_Channel* output);
	char* print_STATES_sm(STATES_sm_Enum* value);
	RESULT_Enum en_SimDiscreteGrippingArmMovement_GripperClose_1(sm_state* state, sm_inputstate* inputstate, sm_memory* memory, sm_output_Enum_Channel* output);
	RESULT_Enum SimDiscreteGrippingArmMovement_J3(sm_state* state, sm_inputstate* inputstate, sm_memory* memorystate, sm_output_Enum_Channel* output);

void *ctrl_cm_thread(void *arg) {
	ctrl_cm_thread_Channels* channels = (ctrl_cm_thread_Channels*) arg;
	C_cm_input_Enum_Channel* start_cm = channels->start_cm;
	sm_output_Enum_Channel* end_sm = channels->end_sm;
	C_cm_output_Enum_Channel* end_cm = channels->end_cm;
	sm_input_Enum_Channel* start_sm = channels->start_sm;
{
	bool terminate__ = false;
	while (!terminate__) {
		{
			bool inputDone = false;
			while (!inputDone) {
				{
					char _s0[256];
					sprintf(_s0, "%s", "- Waiting for input on channel start_cm");
					fprintf(log_file, "DEBUG: %s\n", _s0);
				}
				C_cm_input_Enum _input_;
				{
					pthread_barrier_wait(&start_cm->can_write);
					pthread_barrier_wait(&start_cm->can_read);
					_input_ = start_cm->value;
				}
				{
					char _s0[256];
					sprintf(_s0, "%s", "- Read input on channel start_cm");
					fprintf(log_file, "DEBUG: %s\n", _s0);
				}
				if (_input_.type == C_cm_input_moveDiscreteCommand) {
					MovementArgs _aux1_ = _input_.data.moveDiscreteCommand.v1;
					{
						pthread_barrier_wait(&start_sm->can_write);
						start_sm->value = create_sm_input_moveDiscreteCommand(_aux1_);
						pthread_barrier_wait(&start_sm->can_read);
					}
				}
				else if (_input_.type == C_cm_input_moveCompleted) {
				     	{
				     		pthread_barrier_wait(&start_sm->can_write);
				     		start_sm->value = create_sm_input_moveCompleted();
				     		pthread_barrier_wait(&start_sm->can_read);
				     	}
				     }
				else if (_input_.type == C_cm_input_feasibleMoveDiscreteCommand) {
				     	{
				     		pthread_barrier_wait(&start_sm->can_write);
				     		start_sm->value = create_sm_input_feasibleMoveDiscreteCommand();
				     		pthread_barrier_wait(&start_sm->can_read);
				     	}
				     }
				else if (_input_.type == C_cm_input_openGripperCommand) {
				     	{
				     		pthread_barrier_wait(&start_sm->can_write);
				     		start_sm->value = create_sm_input_openGripperCommand();
				     		pthread_barrier_wait(&start_sm->can_read);
				     	}
				     }
				else if (_input_.type == C_cm_input_nonfeasibleMoveDiscreteCommand) {
				     	{
				     		pthread_barrier_wait(&start_sm->can_write);
				     		start_sm->value = create_sm_input_nonfeasibleMoveDiscreteCommand();
				     		pthread_barrier_wait(&start_sm->can_read);
				     	}
				     }
				else if (_input_.type == C_cm_input_closeGripperCommand) {
				     	{
				     		pthread_barrier_wait(&start_sm->can_write);
				     		start_sm->value = create_sm_input_closeGripperCommand();
				     		pthread_barrier_wait(&start_sm->can_read);
				     	}
				     }
				else if (_input_.type == C_cm_input_gripperClosed) {
				     	{
				     		pthread_barrier_wait(&start_sm->can_write);
				     		start_sm->value = create_sm_input_gripperClosed();
				     		pthread_barrier_wait(&start_sm->can_read);
				     	}
				     }
				else if (_input_.type == C_cm_input_collision) {
				     	{
				     		pthread_barrier_wait(&start_sm->can_write);
				     		start_sm->value = create_sm_input_collision();
				     		pthread_barrier_wait(&start_sm->can_read);
				     	}
				     }
				else if (_input_.type == C_cm_input_robotStopped) {
				     	{
				     		pthread_barrier_wait(&start_sm->can_write);
				     		start_sm->value = create_sm_input_robotStopped();
				     		pthread_barrier_wait(&start_sm->can_read);
				     	}
				     }
				else if (_input_.type == C_cm_input_gripperOpened) {
				     	{
				     		pthread_barrier_wait(&start_sm->can_write);
				     		start_sm->value = create_sm_input_gripperOpened();
				     		pthread_barrier_wait(&start_sm->can_read);
				     	}
				     }
				else if (_input_.type == C_cm_input__done_) {
				     	{
				     		pthread_barrier_wait(&start_sm->can_write);
				     		start_sm->value = create_sm_input__done_();
				     		pthread_barrier_wait(&start_sm->can_read);
				     	}
				     	inputDone = true;
				     }
				else if (_input_.type == C_cm_input__terminate_) {
				     	{
				     		pthread_barrier_wait(&start_sm->can_write);
				     		start_sm->value = create_sm_input__terminate_();
				     		pthread_barrier_wait(&start_sm->can_read);
				     	}
				     	terminate__ = true;
				     }
			}

		}
		{
			char _s0[256];
			sprintf(_s0, "%s", "	Finished reading inputs of controller cm");
			fprintf(log_file, "DEBUG: %s\n", _s0);
		}
		ctrl_cm_step(start_sm
		             , end_sm);
		{
			bool outputDone = false;
			while (!outputDone) {
				sm_output_Enum _output_;
				{
					pthread_barrier_wait(&end_sm->can_write);
					pthread_barrier_wait(&end_sm->can_read);
					_output_ = end_sm->value;
				}
				if (_output_.type == sm_output_stop) {
					{
						pthread_barrier_wait(&end_cm->can_write);
						end_cm->value = create_C_cm_output_stop();
						pthread_barrier_wait(&end_cm->can_read);
					}
				}
				else if (_output_.type == sm_output_place) {
				     	float _aux1_ = _output_.data.place.v1;
				     	float _aux2_ = _output_.data.place.v2;
				     	float _aux3_ = _output_.data.place.v3;
				     	{
				     		pthread_barrier_wait(&end_cm->can_write);
				     		end_cm->value = create_C_cm_output_place(_aux1_
				     		                                         ,_aux2_
				     		                                         ,_aux3_);
				     		pthread_barrier_wait(&end_cm->can_read);
				     	}
				     }
				else if (_output_.type == sm_output_movejoint) {
				     	float _aux1_ = _output_.data.movejoint.v1;
				     	float _aux2_ = _output_.data.movejoint.v2;
				     	float _aux3_ = _output_.data.movejoint.v3;
				     	float _aux4_ = _output_.data.movejoint.v4;
				     	float _aux5_ = _output_.data.movejoint.v5;
				     	float _aux6_ = _output_.data.movejoint.v6;
				     	{
				     		pthread_barrier_wait(&end_cm->can_write);
				     		end_cm->value = create_C_cm_output_movejoint(_aux1_
				     		                                             ,_aux2_
				     		                                             ,_aux3_
				     		                                             ,_aux4_
				     		                                             ,_aux5_
				     		                                             ,_aux6_);
				     		pthread_barrier_wait(&end_cm->can_read);
				     	}
				     }
				else if (_output_.type == sm_output_movediscrete) {
				     	int _aux1_ = _output_.data.movediscrete.v1;
				     	int _aux2_ = _output_.data.movediscrete.v2;
				     	int _aux3_ = _output_.data.movediscrete.v3;
				     	{
				     		pthread_barrier_wait(&end_cm->can_write);
				     		end_cm->value = create_C_cm_output_movediscrete(_aux1_
				     		                                                ,_aux2_
				     		                                                ,_aux3_);
				     		pthread_barrier_wait(&end_cm->can_read);
				     	}
				     }
				else if (_output_.type == sm_output_pick) {
				     	float _aux1_ = _output_.data.pick.v1;
				     	float _aux2_ = _output_.data.pick.v2;
				     	float _aux3_ = _output_.data.pick.v3;
				     	{
				     		pthread_barrier_wait(&end_cm->can_write);
				     		end_cm->value = create_C_cm_output_pick(_aux1_
				     		                                        ,_aux2_
				     		                                        ,_aux3_);
				     		pthread_barrier_wait(&end_cm->can_read);
				     	}
				     }
				else if (_output_.type == sm_output_movecartesian) {
				     	float _aux1_ = _output_.data.movecartesian.v1;
				     	float _aux2_ = _output_.data.movecartesian.v2;
				     	float _aux3_ = _output_.data.movecartesian.v3;
				     	float _aux4_ = _output_.data.movecartesian.v4;
				     	float _aux5_ = _output_.data.movecartesian.v5;
				     	float _aux6_ = _output_.data.movecartesian.v6;
				     	{
				     		pthread_barrier_wait(&end_cm->can_write);
				     		end_cm->value = create_C_cm_output_movecartesian(_aux1_
				     		                                                 ,_aux2_
				     		                                                 ,_aux3_
				     		                                                 ,_aux4_
				     		                                                 ,_aux5_
				     		                                                 ,_aux6_);
				     		pthread_barrier_wait(&end_cm->can_read);
				     	}
				     }
				else if (_output_.type == sm_output_setvelocity) {
				     	float _aux1_ = _output_.data.setvelocity.v1;
				     	{
				     		pthread_barrier_wait(&end_cm->can_write);
				     		end_cm->value = create_C_cm_output_setvelocity(_aux1_);
				     		pthread_barrier_wait(&end_cm->can_read);
				     	}
				     }
				else if (_output_.type == sm_output__done_) {
				     	{
				     		pthread_barrier_wait(&end_cm->can_write);
				     		end_cm->value = create_C_cm_output__done_();
				     		pthread_barrier_wait(&end_cm->can_read);
				     	}
				     	outputDone = true;
				     }
			}

		}
	}
}
}
//update Santiago
/*void init(sm_memory* sm_memory, sm_inputstate* sm_inputstate, sm_state* sm_state ) {
	//main(1);

}*/

/*int main(int argc, char* argv[]) {
//void init(int argc, char* argv[]) {
	//let _ = WriteLogger::init(
	//	LevelFilter::Trace, Config::default(), File::create("test.log").unwrap());
	log_file = fopen("test.log", "w");

	//let _args: Vec<String> = std::env::args().collect();
    if (argc  <= 0) {
        fprintf(stderr, "error: Not enough arguments.");
        exit(1);
    }*/

	/*
		Changes Santiago
	*/
//void init(sm_memory* sm_memory, sm_inputstate* sm_inputstate, sm_state* sm_state ) {
//int main(int argc, char* argv[]) {
ModelInstance* tick(ModelInstance* comp){
	log_file = fopen("test.log", "w");

	/*
		End Changes
	*/

	// Module channel declarations;;
	M_DiscreteGrippingArm_input_Enum_Channel* start_DiscreteGrippingArm = (M_DiscreteGrippingArm_input_Enum_Channel*)malloc(sizeof(M_DiscreteGrippingArm_input_Enum_Channel));
	pthread_barrier_init(&start_DiscreteGrippingArm->can_read, NULL, 2);
	pthread_barrier_init(&start_DiscreteGrippingArm->can_write, NULL, 2);
	M_DiscreteGrippingArm_output_Enum_Channel* end_DiscreteGrippingArm = (M_DiscreteGrippingArm_output_Enum_Channel*)malloc(sizeof(M_DiscreteGrippingArm_output_Enum_Channel));
	pthread_barrier_init(&end_DiscreteGrippingArm->can_read, NULL, 2);
	pthread_barrier_init(&end_DiscreteGrippingArm->can_write, NULL, 2);
	C_cm_input_Enum_Channel* start_cm = (C_cm_input_Enum_Channel*)malloc(sizeof(C_cm_input_Enum_Channel));
	pthread_barrier_init(&start_cm->can_read, NULL, 2);
	pthread_barrier_init(&start_cm->can_write, NULL, 2);
	C_cm_output_Enum_Channel* end_cm = (C_cm_output_Enum_Channel*)malloc(sizeof(C_cm_output_Enum_Channel));
	pthread_barrier_init(&end_cm->can_read, NULL, 2);
	pthread_barrier_init(&end_cm->can_write, NULL, 2);
	sm_input_Enum_Channel* start_sm = (sm_input_Enum_Channel*)malloc(sizeof(sm_input_Enum_Channel));
	pthread_barrier_init(&start_sm->can_read, NULL, 2);
	pthread_barrier_init(&start_sm->can_write, NULL, 2);
	sm_output_Enum_Channel* end_sm = (sm_output_Enum_Channel*)malloc(sizeof(sm_output_Enum_Channel));
	pthread_barrier_init(&end_sm->can_read, NULL, 2);
	pthread_barrier_init(&end_sm->can_write, NULL, 2);
	// Instantiate threads;;
	int status;
	pthread_t control_id;
	control_Channels* control_channels = (control_Channels*)malloc(sizeof(control_Channels));

	control_channels->end_DiscreteGrippingArm = end_DiscreteGrippingArm;
	control_channels->start_DiscreteGrippingArm = start_DiscreteGrippingArm;

	status = pthread_create(&control_id, NULL, control, control_channels);
	if (status != 0)
			err_abort(status, "Create control thread");
	pthread_t mod_DiscreteGrippingArm_thread_id;
	mod_DiscreteGrippingArm_thread_Channels* mod_DiscreteGrippingArm_thread_channels = (mod_DiscreteGrippingArm_thread_Channels*)malloc(sizeof(mod_DiscreteGrippingArm_thread_Channels));

	mod_DiscreteGrippingArm_thread_channels->start_DiscreteGrippingArm = start_DiscreteGrippingArm;
	mod_DiscreteGrippingArm_thread_channels->end_cm = end_cm;
	mod_DiscreteGrippingArm_thread_channels->end_DiscreteGrippingArm = end_DiscreteGrippingArm;
	mod_DiscreteGrippingArm_thread_channels->start_cm = start_cm;

	status = pthread_create(&mod_DiscreteGrippingArm_thread_id, NULL, mod_DiscreteGrippingArm_thread, mod_DiscreteGrippingArm_thread_channels);
	if (status != 0)
			err_abort(status, "Create mod_DiscreteGrippingArm_thread thread");
	pthread_t stm_sm_id;
	stm_sm_Channels* stm_sm_channels = (stm_sm_Channels*)malloc(sizeof(stm_sm_Channels));

	stm_sm_channels->start_sm = start_sm;
	stm_sm_channels->end_sm = end_sm;

	status = pthread_create(&stm_sm_id, NULL, stm_sm, stm_sm_channels);
	if (status != 0)
			err_abort(status, "Create stm_sm thread");
	pthread_t ctrl_cm_thread_id;
	ctrl_cm_thread_Channels* ctrl_cm_thread_channels = (ctrl_cm_thread_Channels*)malloc(sizeof(ctrl_cm_thread_Channels));

	ctrl_cm_thread_channels->start_cm = start_cm;
	ctrl_cm_thread_channels->end_sm = end_sm;
	ctrl_cm_thread_channels->end_cm = end_cm;
	ctrl_cm_thread_channels->start_sm = start_sm;

	status = pthread_create(&ctrl_cm_thread_id, NULL, ctrl_cm_thread, ctrl_cm_thread_channels);
	if (status != 0)
			err_abort(status, "Create ctrl_cm_thread thread");

	status = pthread_join(control_id, NULL);
	if (status != 0)
			err_abort(status, "Join control thread");
	status = pthread_join(mod_DiscreteGrippingArm_thread_id, NULL);
	if (status != 0)
			err_abort(status, "Join mod_DiscreteGrippingArm_thread thread");
	status = pthread_join(stm_sm_id, NULL);
	if (status != 0)
			err_abort(status, "Join stm_sm thread");
	status = pthread_join(ctrl_cm_thread_id, NULL);
	if (status != 0)
			err_abort(status, "Join ctrl_cm_thread thread");

		return 0;;
}

	char* print_STATUS(STATUS_Enum* value) {
		if (value->type == STATUS_ENTER_STATE) {
			return "ENTER_STATE";
		}
		else if (value->type == STATUS_ENTER_CHILDREN) {
		     	return "ENTER_CHILDREN";
		     }
		else if (value->type == STATUS_EXECUTE_STATE) {
		     	return "EXECUTE_STATE";
		     }
		else if (value->type == STATUS_EXIT_CHILDREN) {
		     	return "EXIT_CHILDREN";
		     }
		else if (value->type == STATUS_EXIT_STATE) {
		     	return "EXIT_STATE";
		     }
		else if (value->type == STATUS_INACTIVE) {
		     	return "INACTIVE";
		     }
	}
	void mod_DiscreteGrippingArm_step(C_cm_input_Enum_Channel* start_cm
	                                  , C_cm_output_Enum_Channel* end_cm) {
		{
			char _s0[256];
			sprintf(_s0, "%s", "Started step of module DiscreteGrippingArm");
			fprintf(log_file, "DEBUG: %s\n", _s0);
		}
		{
			char _s0[256];
			sprintf(_s0, "%s", "Finished step of module DiscreteGrippingArm");
			fprintf(log_file, "DEBUG: %s\n", _s0);
		}
	}
	void ctrl_cm_step(sm_input_Enum_Channel* start_sm
	                  , sm_output_Enum_Channel* end_sm) {
		{
			char _s0[256];
			sprintf(_s0, "%s", "	Started step of controller cm");
			fprintf(log_file, "DEBUG: %s\n", _s0);
		}
	}
	RESULT_Enum SimDiscreteGrippingArmMovement_J4(sm_state* state, sm_inputstate* inputstate, sm_memory* memorystate, sm_output_Enum_Channel* output) {
		if ((inputstate)->gripperClosed) {
			(*state).state = create_STATES_sm_Idle();
			(*state).status = create_STATUS_ENTER_STATE();
			return create_RESULT_CONT();
		} else if (!(inputstate)->gripperClosed) {
			(*state).state = create_STATES_sm_GripperClosing();
			(*state).status = create_STATUS_ENTER_STATE();
			return create_RESULT_CONT();
		} else {
			return create_RESULT_CONT();
		}
	}
	char* print_sm_state(sm_state* state) {
		char* temp1_;
		temp1_ = print_STATES_sm(&(state)->state);
		char* temp2_;
		temp2_ = print_STATUS(&(state)->status);
		return concat(concat(concat(temp1_, " ("), temp2_), ")");
	}
	RESULT_Enum en_SimDiscreteGrippingArmMovement_ArmStop_1(sm_state* state, sm_inputstate* inputstate, sm_memory* memory, sm_output_Enum_Channel* output) {
		{
			char _s0[256];
			sprintf(_s0, "%s", "Running entry action 1 of state SimDiscreteGrippingArmMovement_ArmStop.");
			fprintf(log_file, "DEBUG: %s\n", _s0);
		}
		if (	(state)->en_SimDiscreteGrippingArmMovement_ArmStop_1_counter == 0 ) {
			{
				pthread_barrier_wait(&output->can_write);
				output->value = create_sm_output_stop();
				pthread_barrier_wait(&output->can_read);
			}
			(*state).en_SimDiscreteGrippingArmMovement_ArmStop_1_counter = 1;
			return create_RESULT_CONT();
		} else {
			(state)->en_SimDiscreteGrippingArmMovement_ArmStop_1_done = true;
			return create_RESULT_CONT();
		}
	}
	RESULT_Enum en_SimDiscreteGrippingArmMovement_ArmMove_1(sm_state* state, sm_inputstate* inputstate, sm_memory* memory, sm_output_Enum_Channel* output) {
		{
			char _s0[256];
			sprintf(_s0, "%s", "Running entry action 1 of state SimDiscreteGrippingArmMovement_ArmMove.");
			fprintf(log_file, "DEBUG: %s\n", _s0);
		}
		if (	(state)->en_SimDiscreteGrippingArmMovement_ArmMove_1_counter == 0 ) {
			{
				pthread_barrier_wait(&output->can_write);
				output->value = create_sm_output_movediscrete(((memory)->margs).target_X,((memory)->margs).target_Y,((memory)->margs).target_Z);
				pthread_barrier_wait(&output->can_read);
			}
			(*state).en_SimDiscreteGrippingArmMovement_ArmMove_1_counter = 1;
			return create_RESULT_CONT();
		} else {
			(state)->en_SimDiscreteGrippingArmMovement_ArmMove_1_done = true;
			return create_RESULT_CONT();
		}
	}
	RESULT_Enum SimDiscreteGrippingArmMovement_J2(sm_state* state, sm_inputstate* inputstate, sm_memory* memorystate, sm_output_Enum_Channel* output) {
		if (!((inputstate)->collision || (inputstate)->moveCompleted)) {
			(*state).state = create_STATES_sm_ArmMoving();
			(*state).status = create_STATUS_ENTER_STATE();
			return create_RESULT_CONT();
		} else if ((inputstate)->collision || (inputstate)->moveCompleted) {
			(*state).state = create_STATES_sm_ArmStop();
			(*state).status = create_STATUS_ENTER_STATE();
			return create_RESULT_CONT();
		} else {
			return create_RESULT_CONT();
		}
	}
	RESULT_Enum stm_sm_step(sm_state* state, sm_inputstate* inputstate, sm_memory* memorystate, sm_output_Enum_Channel* output) {
		{
			char _s0[256];
			sprintf(_s0, "%s", "		Running step of state machine SimDiscreteGrippingArmMovement");
			fprintf(log_file, "DEBUG: %s\n", _s0);
		}
		if ((*state).state.type == create_STATES_sm_NONE().type) {
			{
				char _s0[256];
				sprintf(_s0, "%s", "		Executing initial junction of SimDiscreteGrippingArmMovement");
				fprintf(log_file, "DEBUG: %s\n", _s0);
			}
			{
				(*state).state = create_STATES_sm_Idle();
			}
			return create_RESULT_CONT();
		}
		else if ((*state).state.type == create_STATES_sm_Idle().type) {
		     	if ((*state).status.type == create_STATUS_ENTER_STATE().type) {
		     		{
		     			char _s0[256];
		     			sprintf(_s0, "%s", "		Entering state Idle");
		     			fprintf(log_file, "DEBUG: %s\n", _s0);
		     		}
		     		{
		     			(*state).status = create_STATUS_ENTER_CHILDREN();
		     			return create_RESULT_CONT();
		     		}
		     	}
		     	else if ((*state).status.type == create_STATUS_ENTER_CHILDREN().type) {
		     	     	{
		     	     		char _s0[256];
		     	     		sprintf(_s0, "%s", "		Entering children of state Idle");
		     	     		fprintf(log_file, "DEBUG: %s\n", _s0);
		     	     	}
		     	     	(*state).status = create_STATUS_EXECUTE_STATE();
		     	     	{
		     	     		(*inputstate)._transition_ = create_TRANSITIONS_sm_NONE();
		     	     	}
		     	     	return create_RESULT_CONT();
		     	     }
		     	else if ((*state).status.type == create_STATUS_EXECUTE_STATE().type) {
		     	     	{
		     	     		char _s0[256];
		     	     		sprintf(_s0, "%s", "		Executing state Idle");
		     	     		fprintf(log_file, "DEBUG: %s\n", _s0);
		     	     	}
		     	     	if (	(*inputstate)._transition_.type == create_TRANSITIONS_sm_NONE().type
		     	     	     ) {
		     	     		if (!((inputstate)->moveDiscreteCommand || (inputstate)->openGripperCommand || (inputstate)->closeGripperCommand)) {
		     	     			(*inputstate)._transition_ = create_TRANSITIONS_sm_sm_t1_1();
		     	     			(*state).status = create_STATUS_EXIT_CHILDREN();
		     	     			return create_RESULT_WAIT();
		     	     		} else if ((inputstate)->openGripperCommand) {
		     	     			(*inputstate)._transition_ = create_TRANSITIONS_sm_sm_t5();
		     	     			(*state).status = create_STATUS_EXIT_CHILDREN();
		     	     			return create_RESULT_CONT();
		     	     		} else if ((inputstate)->moveDiscreteCommand) {
		     	     			(*memorystate).margs = (inputstate)->moveDiscreteCommand_value;
		     	     			(*inputstate)._transition_ = create_TRANSITIONS_sm_sm_t2();
		     	     			(*state).status = create_STATUS_EXIT_CHILDREN();
		     	     			return create_RESULT_CONT();
		     	     		} else if ((inputstate)->closeGripperCommand) {
		     	     			(*inputstate)._transition_ = create_TRANSITIONS_sm_sm_t4();
		     	     			(*state).status = create_STATUS_EXIT_CHILDREN();
		     	     			return create_RESULT_CONT();
		     	     		} else {
		     	     			return create_RESULT_CONT();
		     	     		}
		     	     	} else {
		     	     		return create_RESULT_CONT();
		     	     	}
		     	     }
		     	else if ((*state).status.type == create_STATUS_EXIT_CHILDREN().type) {
		     	     	{
		     	     		char _s0[256];
		     	     		sprintf(_s0, "%s", "		Exiting children of state Idle");
		     	     		fprintf(log_file, "DEBUG: %s\n", _s0);
		     	     	}
		     	     	(*state).status = create_STATUS_EXIT_STATE();
		     	     	return create_RESULT_CONT();
		     	     }
		     	else if ((*state).status.type == create_STATUS_EXIT_STATE().type) {
		     	     	{
		     	     		char _s0[256];
		     	     		sprintf(_s0, "%s", "		Exiting state Idle");
		     	     		fprintf(log_file, "DEBUG: %s\n", _s0);
		     	     	}
		     	     	{
		     	     		if (	(*inputstate)._transition_.type == create_TRANSITIONS_sm_sm_t1_1().type
		     	     		     ) {
		     	     			(*state).state = create_STATES_sm_Idle();
		     	     			(*state).status = create_STATUS_ENTER_STATE();
		     	     			return create_RESULT_CONT();
		     	     		} else if (	(*inputstate)._transition_.type == create_TRANSITIONS_sm_sm_t5().type
		     	     		            ) {
		     	     			(*state).state = create_STATES_sm_GripperOpen();
		     	     			(*state).status = create_STATUS_ENTER_STATE();
		     	     			return create_RESULT_CONT();
		     	     		} else if (	(*inputstate)._transition_.type == create_TRANSITIONS_sm_sm_t2().type
		     	     		            ) {
		     	     			(*state).state = create_STATES_sm_ArmMove();
		     	     			(*state).status = create_STATUS_ENTER_STATE();
		     	     			return create_RESULT_CONT();
		     	     		} else if (	(*inputstate)._transition_.type == create_TRANSITIONS_sm_sm_t4().type
		     	     		            ) {
		     	     			(*state).state = create_STATES_sm_GripperClose();
		     	     			(*state).status = create_STATUS_ENTER_STATE();
		     	     			return create_RESULT_CONT();
		     	     		} else {
		     	     			(*state).status = create_STATUS_INACTIVE();
		     	     			(*state).state = create_STATES_sm_NONE();
		     	     			return create_RESULT_CONT();
		     	     		}
		     	     	}
		     	     }
		     	else if ((*state).status.type == create_STATUS_INACTIVE().type) {
		     	     	{
		     	     		char _s0[256];
		     	     		sprintf(_s0, "%s", "		State Idle is inactive");
		     	     		fprintf(log_file, "DEBUG: %s\n", _s0);
		     	     	}
		     	     	return create_RESULT_CONT();
		     	     }
		     }
		else if ((*state).state.type == create_STATES_sm_ArmMove().type) {
		     	if ((*state).status.type == create_STATUS_ENTER_STATE().type) {
		     		{
		     			char _s0[256];
							printf("MoveArm state\n"); //update santiago
		     			sprintf(_s0, "%s", "		Entering state ArmMove");
		     			fprintf(log_file, "DEBUG: %s\n", _s0);
		     		}
		     		if (!(state)->en_SimDiscreteGrippingArmMovement_ArmMove_1_done) {
		     			RESULT_Enum _ret_;
		     			_ret_ = en_SimDiscreteGrippingArmMovement_ArmMove_1(state
		     			                                                    , inputstate
		     			                                                    , memorystate
		     			                                                    , output);
		     			return _ret_;
		     		} else {
		     			(*state).status = create_STATUS_ENTER_CHILDREN();
		     			(*state).en_SimDiscreteGrippingArmMovement_ArmMove_1_done = false;
		     			(*state).en_SimDiscreteGrippingArmMovement_ArmMove_1_counter = 0;
		     			return create_RESULT_CONT();
		     		}
		     	}
		     	else if ((*state).status.type == create_STATUS_ENTER_CHILDREN().type) {
		     	     	{
		     	     		char _s0[256];
		     	     		sprintf(_s0, "%s", "		Entering children of state ArmMove");
		     	     		fprintf(log_file, "DEBUG: %s\n", _s0);
		     	     	}
		     	     	(*state).status = create_STATUS_EXECUTE_STATE();
		     	     	{
		     	     		(*inputstate)._transition_ = create_TRANSITIONS_sm_NONE();
		     	     	}
		     	     	return create_RESULT_CONT();
		     	     }
		     	else if ((*state).status.type == create_STATUS_EXECUTE_STATE().type) {
		     	     	{
		     	     		char _s0[256];
		     	     		sprintf(_s0, "%s", "		Executing state ArmMove");
		     	     		fprintf(log_file, "DEBUG: %s\n", _s0);
		     	     	}
		     	     	if (	(*inputstate)._transition_.type == create_TRANSITIONS_sm_NONE().type
		     	     	     ) {
		     	     		if ((inputstate)->feasibleMoveDiscreteCommand) {
		     	     			(*inputstate)._transition_ = create_TRANSITIONS_sm_sm_t2_1();
		     	     			(*state).status = create_STATUS_EXIT_CHILDREN();
		     	     			return create_RESULT_CONT();
		     	     		} else if ((inputstate)->nonfeasibleMoveDiscreteCommand) {
		     	     			(*inputstate)._transition_ = create_TRANSITIONS_sm_sm_t2_nonfeasible();
		     	     			(*state).status = create_STATUS_EXIT_CHILDREN();
		     	     			return create_RESULT_CONT();
		     	     		} else {
		     	     			return create_RESULT_CONT();
		     	     		}
		     	     	} else {
		     	     		return create_RESULT_CONT();
		     	     	}
		     	     }
		     	else if ((*state).status.type == create_STATUS_EXIT_CHILDREN().type) {
		     	     	{
		     	     		char _s0[256];
		     	     		sprintf(_s0, "%s", "		Exiting children of state ArmMove");
		     	     		fprintf(log_file, "DEBUG: %s\n", _s0);
		     	     	}
		     	     	(*state).status = create_STATUS_EXIT_STATE();
		     	     	return create_RESULT_CONT();
		     	     }
		     	else if ((*state).status.type == create_STATUS_EXIT_STATE().type) {
		     	     	{
		     	     		char _s0[256];
		     	     		sprintf(_s0, "%s", "		Exiting state ArmMove");
		     	     		fprintf(log_file, "DEBUG: %s\n", _s0);
		     	     	}
		     	     	{
		     	     		if (	(*inputstate)._transition_.type == create_TRANSITIONS_sm_sm_t2_1().type
		     	     		     ) {
		     	     			(*state).state = create_STATES_sm_ArmMoving();
		     	     			(*state).status = create_STATUS_ENTER_STATE();
		     	     			return create_RESULT_CONT();
		     	     		} else if (	(*inputstate)._transition_.type == create_TRANSITIONS_sm_sm_t2_nonfeasible().type
		     	     		            ) {
		     	     			(*state).state = create_STATES_sm_Idle();
		     	     			(*state).status = create_STATUS_ENTER_STATE();
		     	     			return create_RESULT_CONT();
		     	     		} else {
		     	     			(*state).status = create_STATUS_INACTIVE();
		     	     			(*state).state = create_STATES_sm_NONE();
		     	     			return create_RESULT_CONT();
		     	     		}
		     	     	}
		     	     }
		     	else if ((*state).status.type == create_STATUS_INACTIVE().type) {
		     	     	{
		     	     		char _s0[256];
		     	     		sprintf(_s0, "%s", "		State ArmMove is inactive");
		     	     		fprintf(log_file, "DEBUG: %s\n", _s0);
		     	     	}
		     	     	return create_RESULT_CONT();
		     	     }
		     }
		else if ((*state).state.type == create_STATES_sm_ArmStop().type) {
		     	if ((*state).status.type == create_STATUS_ENTER_STATE().type) {
		     		{
		     			char _s0[256];
		     			sprintf(_s0, "%s", "		Entering state ArmStop");
		     			fprintf(log_file, "DEBUG: %s\n", _s0);
		     		}
		     		if (!(state)->en_SimDiscreteGrippingArmMovement_ArmStop_1_done) {
		     			RESULT_Enum _ret_;
		     			_ret_ = en_SimDiscreteGrippingArmMovement_ArmStop_1(state
		     			                                                    , inputstate
		     			                                                    , memorystate
		     			                                                    , output);
		     			return _ret_;
		     		} else {
		     			(*state).status = create_STATUS_ENTER_CHILDREN();
		     			(*state).en_SimDiscreteGrippingArmMovement_ArmStop_1_done = false;
		     			(*state).en_SimDiscreteGrippingArmMovement_ArmStop_1_counter = 0;
		     			return create_RESULT_CONT();
		     		}
		     	}
		     	else if ((*state).status.type == create_STATUS_ENTER_CHILDREN().type) {
		     	     	{
		     	     		char _s0[256];
		     	     		sprintf(_s0, "%s", "		Entering children of state ArmStop");
		     	     		fprintf(log_file, "DEBUG: %s\n", _s0);
		     	     	}
		     	     	(*state).status = create_STATUS_EXECUTE_STATE();
		     	     	{
		     	     		(*inputstate)._transition_ = create_TRANSITIONS_sm_NONE();
		     	     	}
		     	     	return create_RESULT_CONT();
		     	     }
		     	else if ((*state).status.type == create_STATUS_EXECUTE_STATE().type) {
		     	     	{
		     	     		char _s0[256];
		     	     		sprintf(_s0, "%s", "		Executing state ArmStop");
		     	     		fprintf(log_file, "DEBUG: %s\n", _s0);
		     	     	}
		     	     	if (	(*inputstate)._transition_.type == create_TRANSITIONS_sm_NONE().type
		     	     	     ) {
		     	     		if (true) {
		     	     			(*inputstate)._transition_ = create_TRANSITIONS_sm_sm_t3();
		     	     			(*state).status = create_STATUS_EXIT_CHILDREN();
		     	     			return create_RESULT_CONT();
		     	     		} else {
		     	     			return create_RESULT_CONT();
		     	     		}
		     	     	} else {
		     	     		return create_RESULT_CONT();
		     	     	}
		     	     }
		     	else if ((*state).status.type == create_STATUS_EXIT_CHILDREN().type) {
		     	     	{
		     	     		char _s0[256];
		     	     		sprintf(_s0, "%s", "		Exiting children of state ArmStop");
		     	     		fprintf(log_file, "DEBUG: %s\n", _s0);
		     	     	}
		     	     	(*state).status = create_STATUS_EXIT_STATE();
		     	     	return create_RESULT_CONT();
		     	     }
		     	else if ((*state).status.type == create_STATUS_EXIT_STATE().type) {
		     	     	{
		     	     		char _s0[256];
		     	     		sprintf(_s0, "%s", "		Exiting state ArmStop");
		     	     		fprintf(log_file, "DEBUG: %s\n", _s0);
		     	     	}
		     	     	{
		     	     		if (	(*inputstate)._transition_.type == create_TRANSITIONS_sm_sm_t3().type
		     	     		     ) {
		     	     			(*state).state = create_STATES_sm_ArmStopping();
		     	     			(*state).status = create_STATUS_ENTER_STATE();
		     	     			return create_RESULT_CONT();
		     	     		} else {
		     	     			(*state).status = create_STATUS_INACTIVE();
		     	     			(*state).state = create_STATES_sm_NONE();
		     	     			return create_RESULT_CONT();
		     	     		}
		     	     	}
		     	     }
		     	else if ((*state).status.type == create_STATUS_INACTIVE().type) {
		     	     	{
		     	     		char _s0[256];
		     	     		sprintf(_s0, "%s", "		State ArmStop is inactive");
		     	     		fprintf(log_file, "DEBUG: %s\n", _s0);
		     	     	}
		     	     	return create_RESULT_CONT();
		     	     }
		     }
		else if ((*state).state.type == create_STATES_sm_GripperClose().type) {
		     	if ((*state).status.type == create_STATUS_ENTER_STATE().type) {
		     		{
		     			char _s0[256];
		     			sprintf(_s0, "%s", "		Entering state GripperClose");
		     			fprintf(log_file, "DEBUG: %s\n", _s0);
		     		}
		     		if (!(state)->en_SimDiscreteGrippingArmMovement_GripperClose_1_done) {
		     			RESULT_Enum _ret_;
		     			_ret_ = en_SimDiscreteGrippingArmMovement_GripperClose_1(state
		     			                                                         , inputstate
		     			                                                         , memorystate
		     			                                                         , output);
		     			return _ret_;
		     		} else {
		     			(*state).status = create_STATUS_ENTER_CHILDREN();
		     			(*state).en_SimDiscreteGrippingArmMovement_GripperClose_1_done = false;
		     			(*state).en_SimDiscreteGrippingArmMovement_GripperClose_1_counter = 0;
		     			return create_RESULT_CONT();
		     		}
		     	}
		     	else if ((*state).status.type == create_STATUS_ENTER_CHILDREN().type) {
		     	     	{
		     	     		char _s0[256];
		     	     		sprintf(_s0, "%s", "		Entering children of state GripperClose");
		     	     		fprintf(log_file, "DEBUG: %s\n", _s0);
		     	     	}
		     	     	(*state).status = create_STATUS_EXECUTE_STATE();
		     	     	{
		     	     		(*inputstate)._transition_ = create_TRANSITIONS_sm_NONE();
		     	     	}
		     	     	return create_RESULT_CONT();
		     	     }
		     	else if ((*state).status.type == create_STATUS_EXECUTE_STATE().type) {
		     	     	{
		     	     		char _s0[256];
		     	     		sprintf(_s0, "%s", "		Executing state GripperClose");
		     	     		fprintf(log_file, "DEBUG: %s\n", _s0);
		     	     	}
		     	     	if (	(*inputstate)._transition_.type == create_TRANSITIONS_sm_NONE().type
		     	     	     ) {
		     	     		if (true) {
		     	     			(*inputstate)._transition_ = create_TRANSITIONS_sm_sm_t4_1();
		     	     			(*state).status = create_STATUS_EXIT_CHILDREN();
		     	     			return create_RESULT_CONT();
		     	     		} else {
		     	     			return create_RESULT_CONT();
		     	     		}
		     	     	} else {
		     	     		return create_RESULT_CONT();
		     	     	}
		     	     }
		     	else if ((*state).status.type == create_STATUS_EXIT_CHILDREN().type) {
		     	     	{
		     	     		char _s0[256];
		     	     		sprintf(_s0, "%s", "		Exiting children of state GripperClose");
		     	     		fprintf(log_file, "DEBUG: %s\n", _s0);
		     	     	}
		     	     	(*state).status = create_STATUS_EXIT_STATE();
		     	     	return create_RESULT_CONT();
		     	     }
		     	else if ((*state).status.type == create_STATUS_EXIT_STATE().type) {
		     	     	{
		     	     		char _s0[256];
		     	     		sprintf(_s0, "%s", "		Exiting state GripperClose");
		     	     		fprintf(log_file, "DEBUG: %s\n", _s0);
		     	     	}
		     	     	{
		     	     		if (	(*inputstate)._transition_.type == create_TRANSITIONS_sm_sm_t4_1().type
		     	     		     ) {
		     	     			(*state).state = create_STATES_sm_GripperClosing();
		     	     			(*state).status = create_STATUS_ENTER_STATE();
		     	     			return create_RESULT_CONT();
		     	     		} else {
		     	     			(*state).status = create_STATUS_INACTIVE();
		     	     			(*state).state = create_STATES_sm_NONE();
		     	     			return create_RESULT_CONT();
		     	     		}
		     	     	}
		     	     }
		     	else if ((*state).status.type == create_STATUS_INACTIVE().type) {
		     	     	{
		     	     		char _s0[256];
		     	     		sprintf(_s0, "%s", "		State GripperClose is inactive");
		     	     		fprintf(log_file, "DEBUG: %s\n", _s0);
		     	     	}
		     	     	return create_RESULT_CONT();
		     	     }
		     }
		else if ((*state).state.type == create_STATES_sm_GripperOpen().type) {
		     	if ((*state).status.type == create_STATUS_ENTER_STATE().type) {
		     		{
		     			char _s0[256];
		     			sprintf(_s0, "%s", "		Entering state GripperOpen");
		     			fprintf(log_file, "DEBUG: %s\n", _s0);
		     		}
		     		if (!(state)->en_SimDiscreteGrippingArmMovement_GripperOpen_1_done) {
		     			RESULT_Enum _ret_;
		     			_ret_ = en_SimDiscreteGrippingArmMovement_GripperOpen_1(state
		     			                                                        , inputstate
		     			                                                        , memorystate
		     			                                                        , output);
		     			return _ret_;
		     		} else {
		     			(*state).status = create_STATUS_ENTER_CHILDREN();
		     			(*state).en_SimDiscreteGrippingArmMovement_GripperOpen_1_done = false;
		     			(*state).en_SimDiscreteGrippingArmMovement_GripperOpen_1_counter = 0;
		     			return create_RESULT_CONT();
		     		}
		     	}
		     	else if ((*state).status.type == create_STATUS_ENTER_CHILDREN().type) {
		     	     	{
		     	     		char _s0[256];
		     	     		sprintf(_s0, "%s", "		Entering children of state GripperOpen");
		     	     		fprintf(log_file, "DEBUG: %s\n", _s0);
		     	     	}
		     	     	(*state).status = create_STATUS_EXECUTE_STATE();
		     	     	{
		     	     		(*inputstate)._transition_ = create_TRANSITIONS_sm_NONE();
		     	     	}
		     	     	return create_RESULT_CONT();
		     	     }
		     	else if ((*state).status.type == create_STATUS_EXECUTE_STATE().type) {
		     	     	{
		     	     		char _s0[256];
		     	     		sprintf(_s0, "%s", "		Executing state GripperOpen");
		     	     		fprintf(log_file, "DEBUG: %s\n", _s0);
		     	     	}
		     	     	if (	(*inputstate)._transition_.type == create_TRANSITIONS_sm_NONE().type
		     	     	     ) {
		     	     		if (true) {
		     	     			(*inputstate)._transition_ = create_TRANSITIONS_sm_sm_t5_1();
		     	     			(*state).status = create_STATUS_EXIT_CHILDREN();
		     	     			return create_RESULT_CONT();
		     	     		} else {
		     	     			return create_RESULT_CONT();
		     	     		}
		     	     	} else {
		     	     		return create_RESULT_CONT();
		     	     	}
		     	     }
		     	else if ((*state).status.type == create_STATUS_EXIT_CHILDREN().type) {
		     	     	{
		     	     		char _s0[256];
		     	     		sprintf(_s0, "%s", "		Exiting children of state GripperOpen");
		     	     		fprintf(log_file, "DEBUG: %s\n", _s0);
		     	     	}
		     	     	(*state).status = create_STATUS_EXIT_STATE();
		     	     	return create_RESULT_CONT();
		     	     }
		     	else if ((*state).status.type == create_STATUS_EXIT_STATE().type) {
		     	     	{
		     	     		char _s0[256];
		     	     		sprintf(_s0, "%s", "		Exiting state GripperOpen");
		     	     		fprintf(log_file, "DEBUG: %s\n", _s0);
		     	     	}
		     	     	{
		     	     		if (	(*inputstate)._transition_.type == create_TRANSITIONS_sm_sm_t5_1().type
		     	     		     ) {
		     	     			(*state).state = create_STATES_sm_GripperOpening();
		     	     			(*state).status = create_STATUS_ENTER_STATE();
		     	     			return create_RESULT_CONT();
		     	     		} else {
		     	     			(*state).status = create_STATUS_INACTIVE();
		     	     			(*state).state = create_STATES_sm_NONE();
		     	     			return create_RESULT_CONT();
		     	     		}
		     	     	}
		     	     }
		     	else if ((*state).status.type == create_STATUS_INACTIVE().type) {
		     	     	{
		     	     		char _s0[256];
		     	     		sprintf(_s0, "%s", "		State GripperOpen is inactive");
		     	     		fprintf(log_file, "DEBUG: %s\n", _s0);
		     	     	}
		     	     	return create_RESULT_CONT();
		     	     }
		     }
		else if ((*state).state.type == create_STATES_sm_ArmMoving().type) {
		     	if ((*state).status.type == create_STATUS_ENTER_STATE().type) {
		     		{
		     			char _s0[256];
		     			sprintf(_s0, "%s", "		Entering state ArmMoving");
		     			fprintf(log_file, "DEBUG: %s\n", _s0);
		     		}
		     		{
		     			(*state).status = create_STATUS_ENTER_CHILDREN();
		     			return create_RESULT_CONT();
		     		}
		     	}
		     	else if ((*state).status.type == create_STATUS_ENTER_CHILDREN().type) {
		     	     	{
		     	     		char _s0[256];
		     	     		sprintf(_s0, "%s", "		Entering children of state ArmMoving");
		     	     		fprintf(log_file, "DEBUG: %s\n", _s0);
		     	     	}
		     	     	(*state).status = create_STATUS_EXECUTE_STATE();
		     	     	{
		     	     		(*inputstate)._transition_ = create_TRANSITIONS_sm_NONE();
		     	     	}
		     	     	return create_RESULT_CONT();
		     	     }
		     	else if ((*state).status.type == create_STATUS_EXECUTE_STATE().type) {
		     	     	{
		     	     		char _s0[256];
		     	     		sprintf(_s0, "%s", "		Executing state ArmMoving");
		     	     		fprintf(log_file, "DEBUG: %s\n", _s0);
		     	     	}
		     	     	if (	(*inputstate)._transition_.type == create_TRANSITIONS_sm_NONE().type
		     	     	     ) {
		     	     		if (true) {
		     	     			(*inputstate)._transition_ = create_TRANSITIONS_sm_sm_t2_2();
		     	     			(*state).status = create_STATUS_EXIT_CHILDREN();
		     	     			return create_RESULT_WAIT();
		     	     		} else {
		     	     			return create_RESULT_CONT();
		     	     		}
		     	     	} else {
		     	     		return create_RESULT_CONT();
		     	     	}
		     	     }
		     	else if ((*state).status.type == create_STATUS_EXIT_CHILDREN().type) {
		     	     	{
		     	     		char _s0[256];
		     	     		sprintf(_s0, "%s", "		Exiting children of state ArmMoving");
		     	     		fprintf(log_file, "DEBUG: %s\n", _s0);
		     	     	}
		     	     	(*state).status = create_STATUS_EXIT_STATE();
		     	     	return create_RESULT_CONT();
		     	     }
		     	else if ((*state).status.type == create_STATUS_EXIT_STATE().type) {
		     	     	{
		     	     		char _s0[256];
		     	     		sprintf(_s0, "%s", "		Exiting state ArmMoving");
		     	     		fprintf(log_file, "DEBUG: %s\n", _s0);
		     	     	}
		     	     	{
		     	     		if (	(*inputstate)._transition_.type == create_TRANSITIONS_sm_sm_t2_2().type
		     	     		     ) {
		     	     			RESULT_Enum _ret_;
		     	     			_ret_ = SimDiscreteGrippingArmMovement_J2(state
		     	     			                                          , inputstate
		     	     			                                          , memorystate
		     	     			                                          , output);
		     	     			return _ret_;
		     	     		} else {
		     	     			(*state).status = create_STATUS_INACTIVE();
		     	     			(*state).state = create_STATES_sm_NONE();
		     	     			return create_RESULT_CONT();
		     	     		}
		     	     	}
		     	     }
		     	else if ((*state).status.type == create_STATUS_INACTIVE().type) {
		     	     	{
		     	     		char _s0[256];
		     	     		sprintf(_s0, "%s", "		State ArmMoving is inactive");
		     	     		fprintf(log_file, "DEBUG: %s\n", _s0);
		     	     	}
		     	     	return create_RESULT_CONT();
		     	     }
		     }
		else if ((*state).state.type == create_STATES_sm_ArmStopping().type) {
		     	if ((*state).status.type == create_STATUS_ENTER_STATE().type) {
		     		{
		     			char _s0[256];
		     			sprintf(_s0, "%s", "		Entering state ArmStopping");
		     			fprintf(log_file, "DEBUG: %s\n", _s0);
		     		}
		     		{
		     			(*state).status = create_STATUS_ENTER_CHILDREN();
		     			return create_RESULT_CONT();
		     		}
		     	}
		     	else if ((*state).status.type == create_STATUS_ENTER_CHILDREN().type) {
		     	     	{
		     	     		char _s0[256];
		     	     		sprintf(_s0, "%s", "		Entering children of state ArmStopping");
		     	     		fprintf(log_file, "DEBUG: %s\n", _s0);
		     	     	}
		     	     	(*state).status = create_STATUS_EXECUTE_STATE();
		     	     	{
		     	     		(*inputstate)._transition_ = create_TRANSITIONS_sm_NONE();
		     	     	}
		     	     	return create_RESULT_CONT();
		     	     }
		     	else if ((*state).status.type == create_STATUS_EXECUTE_STATE().type) {
		     	     	{
		     	     		char _s0[256];
		     	     		sprintf(_s0, "%s", "		Executing state ArmStopping");
		     	     		fprintf(log_file, "DEBUG: %s\n", _s0);
		     	     	}
		     	     	if (	(*inputstate)._transition_.type == create_TRANSITIONS_sm_NONE().type
		     	     	     ) {
		     	     		if (true) {
		     	     			(*inputstate)._transition_ = create_TRANSITIONS_sm_sm_t3_1();
		     	     			(*state).status = create_STATUS_EXIT_CHILDREN();
		     	     			return create_RESULT_WAIT();
		     	     		} else {
		     	     			return create_RESULT_CONT();
		     	     		}
		     	     	} else {
		     	     		return create_RESULT_CONT();
		     	     	}
		     	     }
		     	else if ((*state).status.type == create_STATUS_EXIT_CHILDREN().type) {
		     	     	{
		     	     		char _s0[256];
		     	     		sprintf(_s0, "%s", "		Exiting children of state ArmStopping");
		     	     		fprintf(log_file, "DEBUG: %s\n", _s0);
		     	     	}
		     	     	(*state).status = create_STATUS_EXIT_STATE();
		     	     	return create_RESULT_CONT();
		     	     }
		     	else if ((*state).status.type == create_STATUS_EXIT_STATE().type) {
		     	     	{
		     	     		char _s0[256];
		     	     		sprintf(_s0, "%s", "		Exiting state ArmStopping");
		     	     		fprintf(log_file, "DEBUG: %s\n", _s0);
		     	     	}
		     	     	{
		     	     		if (	(*inputstate)._transition_.type == create_TRANSITIONS_sm_sm_t3_1().type
		     	     		     ) {
		     	     			RESULT_Enum _ret_;
		     	     			_ret_ = SimDiscreteGrippingArmMovement_J3(state
		     	     			                                          , inputstate
		     	     			                                          , memorystate
		     	     			                                          , output);
		     	     			return _ret_;
		     	     		} else {
		     	     			(*state).status = create_STATUS_INACTIVE();
		     	     			(*state).state = create_STATES_sm_NONE();
		     	     			return create_RESULT_CONT();
		     	     		}
		     	     	}
		     	     }
		     	else if ((*state).status.type == create_STATUS_INACTIVE().type) {
		     	     	{
		     	     		char _s0[256];
		     	     		sprintf(_s0, "%s", "		State ArmStopping is inactive");
		     	     		fprintf(log_file, "DEBUG: %s\n", _s0);
		     	     	}
		     	     	return create_RESULT_CONT();
		     	     }
		     }
		else if ((*state).state.type == create_STATES_sm_GripperClosing().type) {
		     	if ((*state).status.type == create_STATUS_ENTER_STATE().type) {
		     		{
		     			char _s0[256];
		     			sprintf(_s0, "%s", "		Entering state GripperClosing");
		     			fprintf(log_file, "DEBUG: %s\n", _s0);
		     		}
		     		{
		     			(*state).status = create_STATUS_ENTER_CHILDREN();
		     			return create_RESULT_CONT();
		     		}
		     	}
		     	else if ((*state).status.type == create_STATUS_ENTER_CHILDREN().type) {
		     	     	{
		     	     		char _s0[256];
		     	     		sprintf(_s0, "%s", "		Entering children of state GripperClosing");
		     	     		fprintf(log_file, "DEBUG: %s\n", _s0);
		     	     	}
		     	     	(*state).status = create_STATUS_EXECUTE_STATE();
		     	     	{
		     	     		(*inputstate)._transition_ = create_TRANSITIONS_sm_NONE();
		     	     	}
		     	     	return create_RESULT_CONT();
		     	     }
		     	else if ((*state).status.type == create_STATUS_EXECUTE_STATE().type) {
		     	     	{
		     	     		char _s0[256];
		     	     		sprintf(_s0, "%s", "		Executing state GripperClosing");
		     	     		fprintf(log_file, "DEBUG: %s\n", _s0);
		     	     	}
		     	     	if (	(*inputstate)._transition_.type == create_TRANSITIONS_sm_NONE().type
		     	     	     ) {
		     	     		if (true) {
		     	     			(*inputstate)._transition_ = create_TRANSITIONS_sm_sm_t4_2();
		     	     			(*state).status = create_STATUS_EXIT_CHILDREN();
		     	     			return create_RESULT_WAIT();
		     	     		} else {
		     	     			return create_RESULT_CONT();
		     	     		}
		     	     	} else {
		     	     		return create_RESULT_CONT();
		     	     	}
		     	     }
		     	else if ((*state).status.type == create_STATUS_EXIT_CHILDREN().type) {
		     	     	{
		     	     		char _s0[256];
		     	     		sprintf(_s0, "%s", "		Exiting children of state GripperClosing");
		     	     		fprintf(log_file, "DEBUG: %s\n", _s0);
		     	     	}
		     	     	(*state).status = create_STATUS_EXIT_STATE();
		     	     	return create_RESULT_CONT();
		     	     }
		     	else if ((*state).status.type == create_STATUS_EXIT_STATE().type) {
		     	     	{
		     	     		char _s0[256];
		     	     		sprintf(_s0, "%s", "		Exiting state GripperClosing");
		     	     		fprintf(log_file, "DEBUG: %s\n", _s0);
		     	     	}
		     	     	{
		     	     		if (	(*inputstate)._transition_.type == create_TRANSITIONS_sm_sm_t4_2().type
		     	     		     ) {
		     	     			RESULT_Enum _ret_;
		     	     			_ret_ = SimDiscreteGrippingArmMovement_J4(state
		     	     			                                          , inputstate
		     	     			                                          , memorystate
		     	     			                                          , output);
		     	     			return _ret_;
		     	     		} else {
		     	     			(*state).status = create_STATUS_INACTIVE();
		     	     			(*state).state = create_STATES_sm_NONE();
		     	     			return create_RESULT_CONT();
		     	     		}
		     	     	}
		     	     }
		     	else if ((*state).status.type == create_STATUS_INACTIVE().type) {
		     	     	{
		     	     		char _s0[256];
		     	     		sprintf(_s0, "%s", "		State GripperClosing is inactive");
		     	     		fprintf(log_file, "DEBUG: %s\n", _s0);
		     	     	}
		     	     	return create_RESULT_CONT();
		     	     }
		     }
		else if ((*state).state.type == create_STATES_sm_GripperOpening().type) {
		     	if ((*state).status.type == create_STATUS_ENTER_STATE().type) {
		     		{
		     			char _s0[256];
		     			sprintf(_s0, "%s", "		Entering state GripperOpening");
		     			fprintf(log_file, "DEBUG: %s\n", _s0);
		     		}
		     		{
		     			(*state).status = create_STATUS_ENTER_CHILDREN();
		     			return create_RESULT_CONT();
		     		}
		     	}
		     	else if ((*state).status.type == create_STATUS_ENTER_CHILDREN().type) {
		     	     	{
		     	     		char _s0[256];
		     	     		sprintf(_s0, "%s", "		Entering children of state GripperOpening");
		     	     		fprintf(log_file, "DEBUG: %s\n", _s0);
		     	     	}
		     	     	(*state).status = create_STATUS_EXECUTE_STATE();
		     	     	{
		     	     		(*inputstate)._transition_ = create_TRANSITIONS_sm_NONE();
		     	     	}
		     	     	return create_RESULT_CONT();
		     	     }
		     	else if ((*state).status.type == create_STATUS_EXECUTE_STATE().type) {
		     	     	{
		     	     		char _s0[256];
		     	     		sprintf(_s0, "%s", "		Executing state GripperOpening");
		     	     		fprintf(log_file, "DEBUG: %s\n", _s0);
		     	     	}
		     	     	if (	(*inputstate)._transition_.type == create_TRANSITIONS_sm_NONE().type
		     	     	     ) {
		     	     		if (true) {
		     	     			(*inputstate)._transition_ = create_TRANSITIONS_sm_sm_t5_2();
		     	     			(*state).status = create_STATUS_EXIT_CHILDREN();
		     	     			return create_RESULT_WAIT();
		     	     		} else {
		     	     			return create_RESULT_CONT();
		     	     		}
		     	     	} else {
		     	     		return create_RESULT_CONT();
		     	     	}
		     	     }
		     	else if ((*state).status.type == create_STATUS_EXIT_CHILDREN().type) {
		     	     	{
		     	     		char _s0[256];
		     	     		sprintf(_s0, "%s", "		Exiting children of state GripperOpening");
		     	     		fprintf(log_file, "DEBUG: %s\n", _s0);
		     	     	}
		     	     	(*state).status = create_STATUS_EXIT_STATE();
		     	     	return create_RESULT_CONT();
		     	     }
		     	else if ((*state).status.type == create_STATUS_EXIT_STATE().type) {
		     	     	{
		     	     		char _s0[256];
		     	     		sprintf(_s0, "%s", "		Exiting state GripperOpening");
		     	     		fprintf(log_file, "DEBUG: %s\n", _s0);
		     	     	}
		     	     	{
		     	     		if (	(*inputstate)._transition_.type == create_TRANSITIONS_sm_sm_t5_2().type
		     	     		     ) {
		     	     			RESULT_Enum _ret_;
		     	     			_ret_ = SimDiscreteGrippingArmMovement_J5(state
		     	     			                                          , inputstate
		     	     			                                          , memorystate
		     	     			                                          , output);
		     	     			return _ret_;
		     	     		} else {
		     	     			(*state).status = create_STATUS_INACTIVE();
		     	     			(*state).state = create_STATES_sm_NONE();
		     	     			return create_RESULT_CONT();
		     	     		}
		     	     	}
		     	     }
		     	else if ((*state).status.type == create_STATUS_INACTIVE().type) {
		     	     	{
		     	     		char _s0[256];
		     	     		sprintf(_s0, "%s", "		State GripperOpening is inactive");
		     	     		fprintf(log_file, "DEBUG: %s\n", _s0);
		     	     	}
		     	     	return create_RESULT_CONT();
		     	     }
		     }
	}
	RESULT_Enum SimDiscreteGrippingArmMovement_J5(sm_state* state, sm_inputstate* inputstate, sm_memory* memorystate, sm_output_Enum_Channel* output) {
		if (!(inputstate)->gripperOpened) {
			(*state).state = create_STATES_sm_GripperOpening();
			(*state).status = create_STATUS_ENTER_STATE();
			return create_RESULT_CONT();
		} else if ((inputstate)->gripperOpened) {
			(*state).state = create_STATES_sm_Idle();
			(*state).status = create_STATUS_ENTER_STATE();
			return create_RESULT_CONT();
		} else {
			return create_RESULT_CONT();
		}
	}
	RESULT_Enum en_SimDiscreteGrippingArmMovement_GripperOpen_1(sm_state* state, sm_inputstate* inputstate, sm_memory* memory, sm_output_Enum_Channel* output) {
		{
			char _s0[256];
			sprintf(_s0, "%s", "Running entry action 1 of state SimDiscreteGrippingArmMovement_GripperOpen.");
			fprintf(log_file, "DEBUG: %s\n", _s0);
		}
		if (	(state)->en_SimDiscreteGrippingArmMovement_GripperOpen_1_counter == 0 ) {
			{
				pthread_barrier_wait(&output->can_write);
				output->value = create_sm_output_place((memory)->opening_diameter
				                                       ,(memory)->opening_speed
				                                       ,(memory)->opening_force);
				pthread_barrier_wait(&output->can_read);
			}
			(*state).en_SimDiscreteGrippingArmMovement_GripperOpen_1_counter = 1;
			return create_RESULT_CONT();
		} else {
			(state)->en_SimDiscreteGrippingArmMovement_GripperOpen_1_done = true;
			return create_RESULT_CONT();
		}
	}
	char* print_STATES_sm(STATES_sm_Enum* value) {
		if (value->type == STATES_sm_NONE) {
			return "NONE";
		}
		else if (value->type == STATES_sm_Idle) {
		     	return "Idle";
		     }
		else if (value->type == STATES_sm_ArmMove) {
		     	return "ArmMove";
		     }
		else if (value->type == STATES_sm_ArmStop) {
		     	return "ArmStop";
		     }
		else if (value->type == STATES_sm_GripperClose) {
		     	return "GripperClose";
		     }
		else if (value->type == STATES_sm_GripperOpen) {
		     	return "GripperOpen";
		     }
		else if (value->type == STATES_sm_ArmMoving) {
		     	return "ArmMoving";
		     }
		else if (value->type == STATES_sm_ArmStopping) {
		     	return "ArmStopping";
		     }
		else if (value->type == STATES_sm_GripperClosing) {
		     	return "GripperClosing";
		     }
		else if (value->type == STATES_sm_GripperOpening) {
		     	return "GripperOpening";
		     }
	}
	RESULT_Enum en_SimDiscreteGrippingArmMovement_GripperClose_1(sm_state* state, sm_inputstate* inputstate, sm_memory* memory, sm_output_Enum_Channel* output) {
		{
			char _s0[256];
			sprintf(_s0, "%s", "Running entry action 1 of state SimDiscreteGrippingArmMovement_GripperClose.");
			fprintf(log_file, "DEBUG: %s\n", _s0);
		}
		if (	(state)->en_SimDiscreteGrippingArmMovement_GripperClose_1_counter == 0 ) {
			{
				pthread_barrier_wait(&output->can_write);
				output->value = create_sm_output_pick((memory)->closing_diameter
				                                      ,(memory)->closing_speed
				                                      ,(memory)->closing_force);
				pthread_barrier_wait(&output->can_read);
			}
			(*state).en_SimDiscreteGrippingArmMovement_GripperClose_1_counter = 1;
			return create_RESULT_CONT();
		} else {
			(state)->en_SimDiscreteGrippingArmMovement_GripperClose_1_done = true;
			return create_RESULT_CONT();
		}
	}
	RESULT_Enum SimDiscreteGrippingArmMovement_J3(sm_state* state, sm_inputstate* inputstate, sm_memory* memorystate, sm_output_Enum_Channel* output) {
		if ((inputstate)->robotStopped) {
			(*state).state = create_STATES_sm_Idle();
			(*state).status = create_STATUS_ENTER_STATE();
			return create_RESULT_CONT();
		} else if (!(inputstate)->robotStopped) {
			(*state).state = create_STATES_sm_ArmStopping();
			(*state).status = create_STATUS_ENTER_STATE();
			return create_RESULT_CONT();
		} else {
			return create_RESULT_CONT();
		}
	}
