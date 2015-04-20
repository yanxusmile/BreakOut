//
//  BrickBase.h
//  BreakOut
//
//  Created by Yanxu Zheng on 20/04/2015.
//
//

#ifndef __BreakOut__BrickBase__
#define __BreakOut__BrickBase__

#include <stdio.h>
USING_NS_CC;

class BrickBase : public Node
{
public:
    
    virtual bool init();
    
    Size getContentSize();
    Sprite* getSprite();
    PhysicsBody* getPhysicsBody();

    
    
protected:
    Sprite* brickSprite;
    PhysicsBody* brickBody;
    
    int hp;
    bool isDead;
    std::string  brickName;
    float density;
    float friction;
    float restitution;
    
    void update(float dt);
};
#endif /* defined(__BreakOut__BrickBase__) */
