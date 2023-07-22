
// Intake
void setIntake(int intaker_power);
void setIntakeMotors();

// Catapult
void setCatapult(int power);
void setCatapultMotors();
void shoot();
void cata_hold();
extern bool cata_shoot;
void auton_hold();
void SetCataRatchet();

// Grabber
void SetGrabber();

// Wings
void ActivateWings(bool dir);

void op_wings();