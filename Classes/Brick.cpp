//
//  Brick.cpp
//  BreakOut
//
//  Created by Yanxu Zheng on 15/04/2015.
//
//

#include "Brick.h"

Brick::Brick()
{
//    brickName = NULL;
//    hp = NULL;
    isDead = false;
}

Brick::~Brick()
{
    
}

Sprite* Brick::getSprite()
{
    return brickSprite;
}

PhysicsBody* Brick::getPhysicsBody()
{
    return brickBody;
}

Size Brick::getContentSize()
{
    return brickSprite->getContentSize();
}

void Brick::initBrickSprite(std::string name)
{
    brickName=name;
    brickSprite=Sprite::create(name);
    
    brickBody = PhysicsBody::createBox(brickSprite->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
    brickBody->getShape(0)->setDensity(10.0f);
    brickBody->getShape(0)->setFriction(0.0f);
    brickBody->getShape(0)->setRestitution(1.f);
    brickBody->setContactTestBitmask(1);
    brickBody->setDynamic(false);
    
    brickSprite->setPhysicsBody(brickBody);
    brickSprite->setTag(3);
    
    this->addChild(brickSprite);
}
