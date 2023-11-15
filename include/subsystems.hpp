
// Intake


// Catapult
void setCatapult(int power);
void setCatapultMotors();
void shoot();
void cata_hold();
extern bool cata_shoot;
void auton_hold();
void DrivePTO();
void Puncher();
extern bool currentDrivePTO;
void setPTO(int L1, int L2, int R1, int R2);

// Grabber
void SetGrabber();

// Wings
void ActivateWings(bool dir);

void op_wings();

// Claw
void op_claw();

// Blocker
void op_blocker();