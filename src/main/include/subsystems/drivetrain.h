#pragma once

#include <frc2/command/SubsystemBase.h>

#include <AHRS.h>
#include <ctre/phoenix.h>
#include <frc/drive/MecanumDrive.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/motorcontrol/MotorControllerGroup.h>
#include <frc/filter/SlewRateLimiter.h>
#include <frc/kinematics/DifferentialDriveKinematics.h>
#include <frc/kinematics/DifferentialDriveOdometry.h>
#include <frc/kinematics/DifferentialDriveWheelSpeeds.h>
#include <frc/controller/RamseteController.h>
#include <frc/controller/SimpleMotorFeedforward.h>
#include <math.h>

#include "Constants.h"

using namespace controllerConstants;
using namespace drivetrainConstants;


class drivetrain : public frc2::SubsystemBase {
 public:
  drivetrain();

  /**
   * Gives us field persistent controls. Wrapped around the existing  
   * mecanum drive class; modifies the inputs before they are fed to 
   * driveCartesian.
   * @param xSpeed The x-speed of the robot (relative to the driver).
   * @param ySpeed The y-speed of the robot (relative to the driver).
   * @param zRotation The z-rotation of the robot (about its center).
   */
  void MecanumDriveJoystick(double xSpeed, double ySpeed, double zRotation);

  void MecanumDrive(double x, double y, double z);

  void TankDriveVolts(double left, double right);

  double GetEncoderDistance(bool left);

  double GetEncoderRate(bool left);

  void ZeroDriveEncoders();

  void SetBrakeMode(bool brake);

  void ZeroGyroYaw();

  void Center(double angleXOff);

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

  /**
   * Will be called periodically whenever the CommandScheduler runs during
   * simulation.
   */
  void SimulationPeriodic() override;

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.

  WPI_TalonFX m_motorFrontLeft{motorFrontLeft};
  WPI_TalonFX m_motorFrontRight{motorFrontRight};
  WPI_TalonFX m_motorRearLeft{motorRearLeft};
  WPI_TalonFX m_motorRearRight{motorRearRight};

  frc::MotorControllerGroup m_leftMotors{m_motorFrontLeft, m_motorFrontRight};
  frc::MotorControllerGroup m_rightMotors{m_motorFrontRight, m_motorRearRight};

  TalonFXConfiguration m_talonFXConfiguration{};

  frc::DifferentialDrive m_differentialDrive{m_leftMotors, m_rightMotors};

  frc::DifferentialDriveOdometry m_odometry{m_gyro.GetRotation2d()};

  //frc::MecanumDrive m_mecanumDrive{m_motorFrontLeft, m_motorRearLeft, m_motorFrontRight, m_motorRearRight};

  double m_adjXSpeed{0};
  double m_adjYSpeed{0};
  double m_adjYaw{0};

  //frc::SlewRateLimiter<double()> m_xRateLimiter{xRateLimit/1_s};
  //frc::SlewRateLimiter<double()> m_yRateLimiter{yRateLimit/1_s};
  //frc::SlewRateLimiter<double()> m_zRateLimiter{zRateLimit/1_s};

  AHRS m_gyro{frc::SPI::kMXP};
};
