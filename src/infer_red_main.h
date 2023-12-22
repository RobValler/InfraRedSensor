/*****************************************************************
 * Copyright (C) 2017-   Robert Valler - All rights reserved.
 *
 * This file is part of the project: Auto
 *
 * This project can not be copied and/or distributed
 * without the express permission of the copyright holder
 *****************************************************************/

#pragma once

#include "rclcpp/rclcpp.hpp"

#include "std_msgs/msg/string.hpp"

#include <thread>
#include <atomic>
#include <thread>
#include <string>

class CInfraRedMain
{
public:
    CInfraRedMain();                                            // Constructor
    CInfraRedMain(const CInfraRedMain&) = delete;               // Copy constructor
    CInfraRedMain(CInfraRedMain&&) = delete;                    // Move constructor
    CInfraRedMain& operator=(const CInfraRedMain&) = delete;    // Copy assignment operator
    CInfraRedMain& operator=(CInfraRedMain&&) = delete;         // Move assignment operator
    ~CInfraRedMain();                                           // Destructor

    bool Start();
    bool Process();
    bool Stop();

private:
    void FuncThread();
    void SubscriptionCallBack(const std_msgs::msg::String& msg);

    std::thread t_blocker;
    std::atomic<bool> m_isShutdownRequest{false};
    std::string m_DataIn;

    rclcpp::Node::SharedPtr m_node;
    typename rclcpp::Subscription<std_msgs::msg::String>::SharedPtr m_sub;

};
