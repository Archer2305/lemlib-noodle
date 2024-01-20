#include "main.h"
#include "subsystems/intake.hpp"

pros::Motor intakeMotor(INTAKE_PORT, pros::E_MOTOR_GEARSET_06, false);

void update_intake() {
    int input_1 = controller.get_digital(BUTTON_INTAKE);
    int input_2 = controller.get_digital(BUTTON_OUTTAKE);

    if (input_1) {
        intakeMotor.move_velocity(600);
    } else if (input_2){
        intakeMotor.move_velocity(-600);
    } else {
        intakeMotor.move_velocity(0);
    } 
}
