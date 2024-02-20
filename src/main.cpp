#include "main.h"
#include "lemlib/api.hpp"
#include "subsystems/slapper.hpp"

// drive motors
pros::Motor leftFront(LEFT_FRONT, pros::E_MOTOR_GEARSET_06);
pros::Motor leftMiddle(LEFT_MIDDLE, pros::E_MOTOR_GEARSET_06);
pros::Motor leftBack(LEFT_BACK, pros::E_MOTOR_GEARSET_06);
pros::Motor rightFront(RIGHT_FRONT, pros::E_MOTOR_GEARSET_06);
pros::Motor rightMiddle(RIGHT_MIDDLE, pros::E_MOTOR_GEARSET_06);
pros::Motor rightBack(RIGHT_BACK, pros::E_MOTOR_GEARSET_06);

// motor groups
pros::MotorGroup leftMotors({leftFront, leftMiddle, leftBack});
pros::MotorGroup rightMotors({rightFront, rightMiddle, rightBack});

// Inertial Sensor on port 2
pros::Imu imu(IMU_PORT);

// drivetrain settings
lemlib::Drivetrain drivetrain(&leftMotors,                  // left motor group
                              &rightMotors,                 // right motor group
                              11,                           // 11 inch track width
                              lemlib::Omniwheel::NEW_325,   // using new 3.25" omnis
                              450,                          // drivetrain rpm is 450
                              4                             // chase power is 2.
);

// lateral motion controller
lemlib::ControllerSettings linearController(6,      // proportional gain (kP)
                                            0,      // integral gain (kI)
                                            1,      // derivative gain (kD)
                                            3,      // anti windup
                                            1,      // small error range, in inches
                                            100,    // small error range timeout, in milliseconds
                                            4,      // large error range, in inches
                                            500,    // large error range timeout, in milliseconds
                                            0      // maximum acceleration (slew)
);

// angular motion controller
lemlib::ControllerSettings angularController(2,     // proportional gain (kP)
                                             0,     // integral gain (kI)
                                             11,    // derivative gain (kD)
                                             3,     // anti windup
                                             1,     // small error range, in degrees
                                             100,   // small error range timeout, in milliseconds
                                             3,     // large error range, in degrees
                                             500,   // large error range timeout, in milliseconds
                                             0      // maximum acceleration (slew)
);

lemlib::OdomSensors sensors(nullptr, nullptr, nullptr, nullptr, &imu);
lemlib::Chassis chassis(drivetrain, linearController, angularController, sensors);
//-----------------------------end-globals----------------------------


void updateDriveNoodle(double L, double R){
    chassis.tank(L,R);
}
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

// Please move this into drive.hpp, i cant figure out how to make it so im pasting it here


void matchLoading(){

    chassis.moveToPose(36,-10,-90,1000, {.forwards=false});
    chassis.moveToPoint(50,-10,500, {.forwards=false});
    chassis.waitUntilDone();
    chassis.moveToPose(15, -10, 23, 3000, {.forwards=false});
    chassis.waitUntilDone();
    //leftMotors.move_velocity(-5);
    wings.set_state(1);
    slapperMotor.move_velocity(55);
    pros::delay(30 *1000);
    slapperMotor.move_velocity(0);
    leftMotors.move_velocity(0);
}

void skillsRun(){
matchLoading();
chassis.moveToPose(25,45,0,1000);
intake.move_velocity(200);
chassis.waitUntilDone();
chassis.turnTo(114, 45, 90, 1000);
intake.move_velocity(-200);
}
void initialize() {
    pros::lcd::initialize(); // initialize brain screen
    chassis.calibrate(); // calibrate sensors

    pros::Task screenTask([&]() {
        lemlib::Pose pose(0, 0, 0);
        while (true) {
            pros::lcd::print(0, "LF: %lf", leftMotors.get_actual_velocities()[0]); // x
            pros::lcd::print(1, "LM: %lf", rightMotors.get_actual_velocities()[0]); // y
            //pros::lcd::print(2, "LB: %lf", leftBack.get_power()); // heading

            //pros::lcd::print(3, "RF: %f", rightFront.get_power()); // x
            //pros::lcd::print(4, "RM: %f", rightMiddle.get_power()); // y
            //pros::lcd::print(5, "RB: %f", rightBack.get_power()); // heading

            pros::delay(50);
        }
    });

    //Motor inits
    liftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}
#if 0 
void elims() {
    flipout();
    chassis.moveToPoint(0, 16, 1000);
    chassis.moveToPose(-12, 44, -97, 1000);
    chassis.waitUntilDone();
    intakeMotor.move_velocity(-600);
    pros::delay(640);
    intakeMotor.move_velocity(0);

    chassis.turnTo(-12, 0, 1000);
    chassis.waitUntilDone();
    chassis.moveToPose(16, 42, 1000, false);
    wings.set_state(1);
    chassis.turnTo(25, 42, 1000, false);
    chassis.waitUntilDone();
    chassis.tank(-127, -127);
    pros::delay(400);
    chassis.tank(0, 0);
}
#endif
/**
 * Runs while the robot is disabled
 */
void disabled() {
//       liftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}


/**
 * runs after initialize if the robot is connected to field control
 */
void competition_initialize() {}

// get a path used for pure pursuit
// this needs to be put outside a function
ASSET(example_txt); // '.' replaced with "_" to make c++ happy

void flipout() {
    liftMotor.move_voltage(12000);
    pros::delay(320);
    liftMotor.move_voltage(0);
}

void awp() {
    flipout();
    chassis.moveToPoint(0, 16, 1000);
    chassis.moveToPose(-8, 38, -93, 1000);
    chassis.waitUntilDone();
    intake.move_velocity(-600);
    pros::delay(640);
    intake.move_velocity(0);

    chassis.moveToPose(-28, 2, 42, 1600, {.forwards=false});
    chassis.turnTo(-20, -6, 1000, false);
    chassis.waitUntilDone();
    chassis.tank(-80, -80);
    pros::delay(64);
    chassis.tank(0, 0);
    wings.set_state(1);
    chassis.turnTo(21, -8, 1000, false);
    pros::delay(500);
    wings.set_state(0);
    chassis.turnTo(16, -10, 1000);

    chassis.turnTo(13, -9, 1600);
    chassis.waitUntilDone();
    chassis.tank(80, 80);
    pros::delay(610);
    chassis.tank(0, 0);

    chassis.turnTo(chassis.getPose().x + 12, chassis.getPose().y, 1600);
    chassis.waitUntilDone();
    chassis.tank(80, 80);
    pros::delay(180);
    chassis.tank(0, 0);

    intake.move_velocity(-600);
    pros::delay(1600);
    intake.move_velocity(0);
}

void six_ball() {
    flipout();

    intake.move_velocity(600);
    chassis.moveToPoint(0, 4, 1000, {.maxSpeed = 16});
    pros::delay(420);
    intake.move_velocity(0);

    chassis.moveToPoint(0, -30, 2000, {.forwards = false, .maxSpeed=88});
    chassis.moveToPose(42, -59, -84, 500, {.forwards = false, .maxSpeed=127}, true); //|
    pros::delay(170);
    //chassis.waitUntil(8);                                                             //|
    wings.set_state(1);
    //chassis.waitUntil(16);
    pros::delay(640);
    wings.set_state(0);
    chassis.waitUntilDone();

    chassis.moveToPoint(37, -55, 2000, {.forwards=false});
    chassis.tank(64, 64);
    pros::delay(100);
    chassis.tank(0, 0);
    chassis.moveToPose(32, -55, 95, 1000, {.maxSpeed = 64});
    chassis.waitUntilDone();
    intake.move_velocity(-600);
    pros::delay(250);
    chassis.tank(88, 88);
    pros::delay(380);
    chassis.tank(-80, -80);
    pros::delay(400);
    chassis.tank(0, 0);
    intake.move_velocity(0);

    chassis.moveToPoint(51, 0, 1000, {.maxSpeed=95});
    intake.move_velocity(600);
    chassis.waitUntilDone();
    pros::delay(800);
    intake.move_velocity(0);
    chassis.moveToPoint(57, -38, 1000);
    pros::delay(160);
    intake.move_velocity(-600);
    chassis.waitUntilDone();
    chassis.tank(-80, -80);
    pros::delay(100);
    chassis.tank(0, 0);
    intake.move_velocity(0);
//backup
    chassis.tank(-64, -64);
    pros::delay(280);
    chassis.tank(0, 0);
}

void autonomous() {
    skillsRun();
}

void opcontrol() {
    matchLoading();
    while (true) {
        update_intake();
        update_slapper();
        update_lift();
        wings.driver_update();
        rachet_p.driver_update();

        // get joystick positions
        int input_brake = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
        if (input_brake > 100) {
            leftMotors.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
            rightMotors.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
            liftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        } else if (input_brake < -100) {
            leftMotors.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
            rightMotors.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
            liftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
        }
            
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
        // move the chassis with curvature drive
        chassis.curvature(abs(leftY) > 16 ? leftY : 0, abs(rightX) > 16 ? rightX : 0);
        // delay to save resources
        pros::delay(10);
    }
}
