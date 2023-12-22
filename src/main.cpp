/*****************************************************************
 * Copyright (C) 2017- Robert Valler - All rights reserved.
 *
 * This file is part of the project: StarterApp
 *
 * This project can not be copied and/or distributed
 * without the express permission of the copyright holder
 *****************************************************************/

#include "infer_red_main.h"

#include "rclcpp/rclcpp.hpp"
#include "Logger.h"

#include <signal.h>
#include <atomic>
#include <thread>


namespace  {
    static std::atomic<bool> l_shutdowndown;
}

void my_handler(int)
{
    CLOG(LOGLEV_RUN, "POSIX Interrupt detected, stopping!");
    l_shutdowndown = true;
}

int main(int argc, char **argv)
{
    l_shutdowndown = false;
    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = my_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);
    sigaction(SIGTERM, &sigIntHandler, NULL);

    CInfraRedMain main;

    rclcpp::init(argc, argv);


    main.Start();

    while(!l_shutdowndown)
    {
        if(!main.Process())
            break;

        std::this_thread::sleep_for( std::chrono::milliseconds(200) );
    }

    rclcpp::shutdown();

    main.Stop();
}
