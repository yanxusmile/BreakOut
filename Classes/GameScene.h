//
//  GameScene.h
//  BreakOut
//
//  Created by Yanxu Zheng on 10/04/2015.
//
//

#ifndef __BreakOut__GameScene__
#define __BreakOut__GameScene__

#include <stdio.h>
USING_NS_CC;

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
        
    CREATE_FUNC(GameScene);
    
    Sprite* ball;
    Sprite* paddle;
//    Sprite* edgeBody;
    
private:
    PhysicsWorld* sceneWorld;
    
    void SetPhysicsWorld(PhysicsWorld* world){ sceneWorld = world; };
    
    bool onContactBegin( cocos2d::PhysicsContact &contact );

    bool onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *event );
    void onTouchMoved(Touch* touch, Event* event);
    
    void setBlock();
};

#endif /* defined(__BreakOut__GameScene__) */
