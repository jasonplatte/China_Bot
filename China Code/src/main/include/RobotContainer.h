/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "subsystems/Chassis.h"
#include <frc/XboxController.h>
#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>
#include <frc2/command/button/JoystickButton.h>
#include <frc/smartdashboard/SmartDashboard.h>


class RobotContainer {
 public:
  using WPI_TalonSRX = ctre::phoenix::motorcontrol::can::WPI_TalonSRX;

 // Speed Controller IDs (must be unique)
  static constexpr int kChassisFrontLeft{0};
  static constexpr int kChassisFrontRight{1};
  static constexpr int kChassisRearLeft{2};
  static constexpr int kChassisRearRight{3};

  RobotContainer();
    frc2::Command* GetAutonomousCommand();

 private:

  frc::XboxController driver{0};
  frc::XboxController coDriver{1};

  // Chassis Components
  Chassis::Components mChassisComponents{kChassisFrontLeft, kChassisFrontRight, kChassisRearLeft, kChassisRearRight};  
  Chassis mChassis{"Chassis", mChassisComponents};

  void ConfigureButtonBindings();


};