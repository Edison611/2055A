
// Intake
void setIntake(int power);
void setIntakeMotors();

// Catapult
extern bool hold;
void setCatapult(double power);
void setCatapultMotors();
void toggleDown();
void kickerTask();
void pistonBoostTask();
void shoot();
void cata_hold();
extern bool cata_shoot;
void auton_hold();
void DrivePTO();
void Puncher();
extern bool currentDrivePTO;
void setPTO(int L1, int L2, int R1, int R2);

// Ram
void ram(int time, int dir);

// Grabber
void SetGrabber();

// Wings
void ActivateWings(bool dir);
void rightWing();
void setWings(bool right, bool left, int delay);

void op_wings();

// Claw
//void op_claw();

// Climb
void op_climb();
