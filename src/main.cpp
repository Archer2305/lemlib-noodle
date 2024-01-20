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
                              2                             // chase power is 2.
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

void autonomous() {
    // example movement: Move to x: 20 and y: 15, and face heading 90. Timeout set to 4000 ms
    //chassis.moveToPoint(0, 24, 100000);
    chassis.moveToPose(24, 24, 90, 4000);
    // example movement: Move to x: 0 and y: 0 and face heading 270, going backwards. Timeout set to 4000ms
    //chassis.turnTo(45, -45, 10000, true, 88);
    #if 0
    chassis.moveToPose(0, 0, 270, 4000, {.forwards = false});
    // cancel the movement after it has travelled 10 inches
    chassis.waitUntil(10);
    chassis.cancelMotion();
    // example movement: Turn to face the point x:45, y:-45. Timeout set to 1000
    // dont turn faster than 60 (out of a maximum of 127)
    chassis.turnTo(45, -45, 1000, true, 60);
    // example movement: Follow the path in path.txt. Lookahead at 15, Timeout set to 4000
    // following the path with the back of the robot (forwards = false)
    // see line 116 to see how to define a path
    chassis.follow(example_txt, 15, 4000, false);
    // wait until the chassis has travelled 10 inches. Otherwise the code directly after
    // the movement will run immediately
    // Unless its another movement, in which case it will wait
    chassis.waitUntil(10);
    pros::lcd::print(4, "Travelled 10 inches during pure pursuit!");
    // wait until the movement is done
    chassis.waitUntilDone();
    pros::lcd::print(4, "pure pursuit finished!");
    #endif
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
