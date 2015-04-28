//
//  BrickT1.cpp
//  BreakOut
//
//  Created by Yanxu Zheng on 20/04/2015.
//
//

#include "BrickT1.h"

BrickT1::BrickT1()
{
    brickName = "brickT1.png";
    density = 10.0f;
    friction = 0.0f;
    restitution = 1.0f;
    hp = 2;
    score = 1;
    
}


BrickT1* BrickT1::create()
{
    BrickT1 *pRet = new BrickT1();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    } 
}