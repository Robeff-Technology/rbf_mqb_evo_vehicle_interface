#pragma once

#include <rclcpp/rclcpp.hpp>

#include <stdexcept>
#include <string>
#include <vector>

/**
 * @brief Utility class for loading, declaring, and printing ROS2 parameters.
 *
 */
class ParamLoader
{
public:
  /**
   * @brief Construct a new ParamLoader.
   *
   * @param node Pointer to the rclcpp::Node that owns the parameters.
   * @throws std::runtime_error If node is null.
   */
  explicit ParamLoader(rclcpp::Node * node) : node_(node)
  {
    if (!node_) {
      throw std::runtime_error("ParamLoader: node pointer is null.");
    }
  }

  /**
   * @brief Load a parameter. If undeclared, automatically declares it.
   *
   * @tparam T Parameter type
   * @param name Parameter name
   * @return T The retrieved value
   *
   * @throws std::runtime_error If parameter cannot be retrieved
   */
  template <typename T>
  T get(const std::string & name)
  {
    declare_if_needed<T>(name);

    T value{};
    if (!node_->get_parameter(name, value)) {
      throw std::runtime_error("ParamLoader: Failed to get parameter '" + name + "'");
    }

    loaded_params_.push_back({name, node_->get_parameter(name)});
    return value;
  }

  /**
   * @brief Load a parameter with fallback default value.
   *
   * If the parameter is undeclared, declares it with @p default_val.
   *
   * @tparam T Parameter type
   * @param name Parameter name
   * @param default_val Default value if parameter is missing
   * @return T The retrieved or default value
   */
  template <typename T>
  T get_or(const std::string & name, const T & default_val)
  {
    declare_if_needed<T>(name, default_val);

    T value{};
    if (!node_->get_parameter(name, value)) {
      value = default_val;
    }

    loaded_params_.push_back({name, node_->get_parameter(name)});
    return value;
  }

  /**
   * @brief Print all loaded parameters using RCLCPP_INFO.
   */
  void print_loaded_parameters() const
  {
    RCLCPP_INFO(node_->get_logger(), "=== Loaded Parameters ===");

    for (const auto & p : loaded_params_) {
      const auto & param = p.second;

      switch (param.get_type()) {
        case rclcpp::ParameterType::PARAMETER_BOOL:
          RCLCPP_INFO(
            node_->get_logger(), "%s: %s", p.first.c_str(), param.as_bool() ? "true" : "false");
          break;

        case rclcpp::ParameterType::PARAMETER_INTEGER:
          RCLCPP_INFO(node_->get_logger(), "%s: %ld", p.first.c_str(), param.as_int());
          break;

        case rclcpp::ParameterType::PARAMETER_DOUBLE:
          RCLCPP_INFO(node_->get_logger(), "%s: %.4f", p.first.c_str(), param.as_double());
          break;

        case rclcpp::ParameterType::PARAMETER_STRING:
          RCLCPP_INFO(node_->get_logger(), "%s: %s", p.first.c_str(), param.as_string().c_str());
          break;

        case rclcpp::ParameterType::PARAMETER_STRING_ARRAY: {
          auto arr = param.as_string_array();
          std::string s = "[";
          for (size_t i = 0; i < arr.size(); i++) {
            s += arr[i];
            if (i + 1 < arr.size()) s += ", ";
          }
          s += "]";
          RCLCPP_INFO(node_->get_logger(), "%s: %s", p.first.c_str(), s.c_str());
          break;
        }

        default:
          RCLCPP_INFO(node_->get_logger(), "%s: (unsupported type)", p.first.c_str());
          break;
      }
    }

    RCLCPP_INFO(node_->get_logger(), "===========================");
  }

private:
  /**
   * @brief Declare a parameter if it has not been previously declared.
   *
   * @tparam T Parameter type
   * @param name Parameter name
   */
  template <typename T>
  void declare_if_needed(const std::string & name)
  {
    if (!node_->has_parameter(name)) {
      node_->declare_parameter<T>(name);
    }
  }

  /**
   * @brief Declare a parameter with default value if not declared.
   *
   * @tparam T Parameter type
   * @param name Parameter name
   * @param def Default value
   */
  template <typename T>
  void declare_if_needed(const std::string & name, const T & def)
  {
    if (!node_->has_parameter(name)) {
      node_->declare_parameter<T>(name, def);
    }
  }

  /// @brief Internal structure to keep track of loaded parameters
  std::vector<std::pair<std::string, rclcpp::Parameter>> loaded_params_;

  /// @brief Pointer to ROS2 node
  rclcpp::Node * node_;
};