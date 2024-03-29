#ifndef __PORTS_H__
#define __PORTS_H__

//----------drive----------
#define RIGHT_FRONT     -14
#define RIGHT_MIDDLE    -4
#define RIGHT_BACK       8

#define LEFT_FRONT      20
#define LEFT_MIDDLE      7
#define LEFT_BACK       -6
//-------------------------

//----------intake---------
#define INTAKE1_PORT     12
#define INTAKE2_PORT     13
//-------------------------

//--------slapper---------
#define SLAPPER_PORT    15
//------------------------

//----------lift----------
#define LIFT_PORT       3
//------------------------

//---------sensors----------
#define IMU_PORT        1
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

#define RACHET_ACT             pros::E_CONTROLLER_DIGITAL_Y
#define RACHET_DEACT           pros::E_CONTROLLER_DIGITAL_RIGHT

#define BUTTON_SLAPPER          pros::E_CONTROLLER_DIGITAL_A
//#define RACHET_ACT              
//#define RACHET_DEACT
//---------------------------------------------------------------

#endif
