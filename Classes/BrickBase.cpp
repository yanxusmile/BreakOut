//
//  BrickBase.cpp
//  BreakOut
//
//  Created by Yanxu Zheng on 20/04/2015.
//
//

#include "BrickBase.h"


bool BrickBase::init()
{
    brickSprite=Sprite::create(brickName);
    
    brickBody = PhysicsBody::createBox(brickSprite->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
    brickBody->getShape(0)->setDensity(density);
    brickBody->getShape(0)->setFriction(friction);
    brickBody->getShape(0)->setRestitution(restitution);
    brickBody->setContactTestBitmask(1);
    brickBody->setDynamic(false);
    
    brickSprite->setPhysicsBody(brickBody);
    brickSprite->setTag(3);
    
    this->addChild(brickSprite);
    
    this->scheduleUpdate();


    
    return true;
}

void BrickBase::update(float dt)
{
    if (hp <= 0)
    {
        this->removeFromParentAndCleanup(true);
    }
        
}

Size BrickBase::getContentSize()
{
    return brickSprite->getContentSize();
}

Sprite* BrickBase::getSprite()
{
    return brickSprite;
}

PhysicsBody* BrickBase::getPhysicsBody()
{
    return brickBody;
}
