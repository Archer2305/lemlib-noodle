#include "main.h"
#include "lemlib/api.hpp"

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
                                            0,      // derivative gain (kD)
                                            3,      // anti windup
                                            1,      // small error range, in inches
                                            100,    // small error range timeout, in milliseconds
                                            4,      // large error range, in inches
                                            500,    // large error range timeout, in milliseconds
                                            20      // maximum acceleration (slew)
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



/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    pros::lcd::initialize(); // initialize brain screen
    chassis.calibrate(); // calibrate sensors

    pros::Task screenTask([&]() {
        lemlib::Pose pose(0, 0, 0);
        while (true) {
            pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
            lemlib::telemetrySink()->info("Chassis pose: {}", chassis.getPose());
            pros::delay(50);
        }
    });

    //Motor inits
    liftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

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
    pros::delay(120);
    liftMotor.move_voltage(0);
}


void elims() {
    flipout();
    chassis.moveToPoint(0, 16, 1000);
    chassis.moveToPose(-8, 38, -93, 1000);
    chassis.waitUntilDone();

    intakeMotor.move_velocity(-600);
    pros::delay(640);
    intakeMotor.move_velocity(0);

    chassis.moveToPoint(12, 38, 2000, {.forwards=false});
    wings.set_state(1);
    chassis.waitUntilDone();
}
void autonomous() {
    elims();
}

void opcontrol() {
    while (true) {
        update_intake();
        wings.driver_update();
        //rachet_p.drive_update();

        // get joystick positions
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
        // move the chassis with curvature drive
        chassis.curvature(abs(leftY) > 16 ? leftY : 0, abs(rightX) > 16 ? rightX : 0);
        // delay to save resources
        pros::delay(10);
    }
}
