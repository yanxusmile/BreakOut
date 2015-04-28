//
//  DataManager.cpp
//  BreakOut
//
//  Created by Yanxu Zheng on 27/04/2015.
//
//

#include "DataManager.h"

DataManager::DataManager()
{
    score = 0;
//    highestScore = 10;
}

DataManager* DataManager::instance;

DataManager* DataManager::getInstance()
{
    if (instance == NULL)
        instance = new DataManager();
    return instance;
}


void DataManager::clear()
{
    brickVector.clear();
}