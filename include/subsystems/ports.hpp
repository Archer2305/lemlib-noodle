#ifndef __PORTS_H__
#define __PORTS_H__

//----------drive----------
#define RIGHT_FRONT     -4
#define RIGHT_MIDDLE    -2
#define RIGHT_BACK      1

#define LEFT_FRONT      7
#define LEFT_MIDDLE     8
#define LEFT_BACK       -10
//-------------------------

//----------intake---------
#define INTAKE_PORT     19
//-------------------------

//----------lift----------
#define LIFT_PORT       5
//------------------------

//---------sensors----------
#define IMU_PORT        15
//--------------------------

//---------pneumatics----------
#define WINGS_ADI       'A'
#define RACHET_ADI      'B'
//-----------------------------

//-------------------------buttons-------------------------------
#define BUTTON_INTAKE           pros::E_CONTROLLER_DIGITAL_R1
#define BUTTON_OUTTAKE          pros::E_CONTROLLER_DIGITAL_R2

#define WINGS_ACTUATE_O         pros::E_CONTROLLER_DIGITAL_B
#define WINGS_ACTUATE_I         pros::E_CONTROLLER_DIGITAL_DOWN

//#define RACHET_ACT              
//#define RACHET_DEACT
//---------------------------------------------------------------

#endif
