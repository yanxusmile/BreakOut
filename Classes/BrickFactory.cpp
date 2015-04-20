//
//  BrickFactory.cpp
//  BreakOut
//
//  Created by Yanxu Zheng on 20/04/2015.
//
//

#include "BrickFactory.h"


BrickFactory::BrickFactory(Layer* gameLayer)
{
    this->gameLayer = gameLayer;
}


BrickBase* BrickFactory::createBrick(int brickTier)
{
    switch(brickTier)
    {
        case 1:
            return BrickT1::create();
            
    }
    return nullptr;
}
