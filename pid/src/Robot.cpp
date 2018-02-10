#include <iostream>
#include <string>
#include "WPILib.h"
#include "ctre/Phoenix.h"
#include <Joystick.h>
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include "DriverStation.h"
#include <Encoder.h>
#include <unistd.h>

class Robot : public frc::IterativeRobot {
public:
	Joystick *joy;
	bool btn1;
	bool SP;
	WPI_TalonSRX *srx = new WPI_TalonSRX(0);
	void RobotInit() {
	}
	void AutonomousInit() override {}
	void AutonomousPeriodic() {}
	void TeleopInit() {
		const bool kInvert = true; /* pick this based on your preference on what positive motor output should spin to */
		const bool kSensorPhase = false; /* pick this so self-test stops reporting sensor-out-of-phase */

		srx->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 10);
		srx->SetStatusFramePeriod(StatusFrame::Status_1_General_, 5, 10); /* Talon will send new frame every 5ms */
		srx->SetSensorPhase(kSensorPhase);
		srx->SetInverted(kInvert);
	}
	void TeleopPeriodic() {
		bool btn1 = joy->GetRawButton(1); /* get buttons */
		/* on button unpress => press, change pos register */
		if (!btn1 && btn1) {
			srx->SetSelectedSensorPosition(-10, 0, 0);

		}

	}
	void TestPeriodic() {

	}
private:

	frc::LiveWindow& m_lw = *LiveWindow::GetInstance();
	frc::SendableChooser<std::string> m_chooser;
	const std::string kAutoNameDefault = "Default";
	const std::string kAutoNameCustom = "My Auto";
	std::string m_autoSelected;
};

START_ROBOT_CLASS(Robot)
