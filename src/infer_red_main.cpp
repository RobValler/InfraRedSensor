/*****************************************************************
 * Copyright (C) 2017-   Robert Valler - All rights reserved.
 *
 * This file is part of the project: Auto
 *
 * This project can not be copied and/or distributed
 * without the express permission of the copyright holder
 *****************************************************************/

#include "infer_red_main.h"


#include "Logger.h"

#include <functional>

CInfraRedMain::CInfraRedMain()
{

}

CInfraRedMain::~CInfraRedMain()
{
    m_isShutdownRequest = true;
    t_blocker.join();
}

bool CInfraRedMain::Start()
{
    //device to open:  /dev/bus/usb/001/007





    // ros subscriber
    using std::placeholders::_1;
    m_node = rclcpp::Node::make_shared("infra_red");
    m_sub = m_node->create_subscription<std_msgs::msg::String>("cmd/ir_str", 10,
        std::bind(&CInfraRedMain::SubscriptionCallBack, this, _1));


    t_blocker = std::thread(&CInfraRedMain::FuncThread, this);

    return true;
}

bool CInfraRedMain::Process()
{

    return true;
}

bool CInfraRedMain::Stop()
{

    return true;
}

void CInfraRedMain::FuncThread()
{
    rclcpp::Rate loop_rate(10);
    while(!m_isShutdownRequest)
    {
        if(rclcpp::ok()) {
            rclcpp::spin_some(m_node);
            loop_rate.sleep();
        }
    }
}

void CInfraRedMain::SubscriptionCallBack(const std_msgs::msg::String& msg)
{
    // Get data
    m_DataIn = msg.data;
    CLOG(LOGLEV_RUN, "data = ", m_DataIn);


    // push the data to the Infra red channel



}
