//
//  Brick.h
//  BreakOut
//
//  Created by Yanxu Zheng on 15/04/2015.
//
//

#ifndef __BreakOut__Brick__
#define __BreakOut__Brick__

#include <stdio.h>
USING_NS_CC;

class Brick : public Node
{
public:
    Brick();
    ~Brick();
    
    void initBrickSprite(std::string name);
    
    bool isDead;
    
    Sprite* getSprite();
    PhysicsBody* getPhysicsBody();
    Size getContentSize();
    
    CREATE_FUNC(Brick);

private:
    Sprite* brickSprite;
    PhysicsBody* brickBody;
    std::string  brickName;
//    int hp;
};

#endif /* defined(__BreakOut__Brick__) */
