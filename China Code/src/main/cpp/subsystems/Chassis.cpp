/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Chassis.h"

#include <frc/smartdashboard/SmartDashboard.h>


namespace{

    constexpr double kTicksPerRotation {2048};
    constexpr double kHundredMillisPerSecond {10};
    constexpr double kSecondsPerMin {60};

    constexpr double RPMToTicks(double rpm)
    {
        double ticks = (rpm * kTicksPerRotation) / kHundredMillisPerSecond / kSecondsPerMin;
        return ticks;
    }
    constexpr double kMaxVelocityError{3500-3000};
    constexpr double kP{(.10*1023)/kMaxVelocityError};
    constexpr double kI{0.0};
    constexpr double kD{0.0}; // 30 is too high
    constexpr double kF{(.70 * 1023)/ RPMToTicks(3000)};


void SetPID(Chassis::Components& components)
{
  components.frontLeft.Config_kP(0, kP, 10);
  components.frontLeft.Config_kI(0, kI, 10);
  components.frontLeft.Config_kD(0, kD, 10);
  components.frontLeft.Config_kF(0, kF, 10);

  components.frontRight.Config_kP(0, kP, 10);
  components.frontRight.Config_kI(0, kI, 10);
  components.frontRight.Config_kD(0, kD, 10);
  components.frontRight.Config_kF(0, kF, 10);
}


} //namespace


Chassis::Chassis(const wpi::Twine& name,
    Components& components)

:mComponents(components)
, mDrive{mComponents.frontLeft, mComponents.frontRight}
{
    SetName(name);
    // TODO: SetSensorPhase does not seem to be having an effect
    // The velocity is still going in reverse to the direction of travel.
    mComponents.frontLeft.SetSensorPhase(true);
    mComponents.backLeft.SetSensorPhase(true);
    mComponents.frontLeft.SetInverted(false);
    mComponents.backLeft.SetInverted(false);
    mComponents.frontRight.SetInverted(false);
    mComponents.backRight.SetInverted(false);

     mComponents.backLeft.Follow(mComponents.frontLeft); 
     mComponents.backRight.Follow(mComponents.frontRight); 
     SetPID(mComponents);
}

// This method will be called once per scheduler run
void Chassis::Periodic() 
{
    frc::SmartDashboard::PutNumber("left chassis velocity", GetLeftVelocity());
    frc::SmartDashboard::PutNumber("right chassis velocity", GetRightVelocity());
    frc::SmartDashboard::PutNumber("Right Chassis Pos", GetRightPos());
    frc::SmartDashboard::PutNumber("Left Chassis Pos", GetLeftPos());
}
void Chassis::TankDrive(double left, double right)
{
    mDrive.TankDrive(left, right);
}

double Chassis::GetLeftVelocity()
{
    return mComponents.frontLeft.GetSelectedSensorVelocity();
}

double Chassis::GetRightVelocity()
{
    return mComponents.frontRight.GetSelectedSensorVelocity();
}

double Chassis::GetRightPos()
{
    return mComponents.frontRight.GetSelectedSensorPosition();
}

double Chassis::GetLeftPos()
{
    return mComponents.frontLeft.GetSelectedSensorPosition();
}

void Chassis::ResetChassisPos()
{
    mComponents.frontLeft.SetSelectedSensorPosition(0);
    mComponents.frontRight.SetSelectedSensorPosition(0);
}