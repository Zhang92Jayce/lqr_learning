/**
 * @file
 * @brief defines the ControllerAgent class
 */

#pragma once

#include <memory>
#include <vector>

#include "control/common/dependency_injector.h"
#include "control/controller/controller.h"
#include "hlbc/proto/local_view.pb.h"

/**
 * @namespace autoagric::control
 * @brief autoagric::control
 */
namespace autoagric {
namespace control {

/**
 * @class ControllerAgent
 * @brief manage all controllers declared in control config file
 */
class ControllerAgent {
 public:
  /**
   * @brief initialize ControllerAgent
   * @param control_conf control configurations
   * @return Status initialization status
   */
  // common::Status Init(std::shared_ptr<DependencyInjector> injector,
  //                     const ControlConf *control_conf);

  common::Status Init(std::shared_ptr<DependencyInjector> injector,
                      const ControlConf *control_conf);

  /**
   * @brief compute control command based on current vehicle status
   *        and target trajectory
   * @param localization vehicle location
   * @param chassis vehicle status e.g., speed, acceleration
   * @param trajectory trajectory generated by planning
   * @param cmd control command
   * @return Status computation status
   */
  common::Status ComputeControlCommand(
      const localization::LocalizationEstimate *localization,
      const canbus::Chassis *chassis, const planning::ADCTrajectory *trajectory,
      control::ControlCommand *cmd);

  /**
   * @brief reset ControllerAgent
   * @return Status reset status
   */
  common::Status Reset();

 private:
  /**
   * @brief
   * Register new controllers. If you need to add a new type of controller,
   * You should first register your controller in this function.
   */
  // void RegisterControllers(const ControlConf *control_conf);

  common::Status InitializeConf(const ControlConf *control_conf);

  const ControlConf *control_conf_ = nullptr;

  std::unique_ptr<Controller> controller_ = nullptr;
  //   common::util::Factory<ControlConf::ControllerType, Controller>
  //       controller_factory_;
  //   std::vector<std::unique_ptr<Controller>> controller_list_;
  std::shared_ptr<DependencyInjector> injector_ = nullptr;
};
}  // namespace control
}  // namespace autoagric