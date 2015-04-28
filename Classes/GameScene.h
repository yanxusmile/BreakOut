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
#include "DataManager.h"

USING_NS_CC;

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
        
    CREATE_FUNC(GameScene);
    
    Sprite* ball;
    PhysicsBody* ballBody;
    
    Sprite* paddle;
    
    void PauseGame();
    void GameOver();
    void ResumeGame();
    
//    bool isGameover;
//    bool isWin;
    
    void tick(float dt);
    
    void ShootBall();
    
    DataManager* dataManager;
    
private:
    PhysicsWorld* sceneWorld;
    
    void SetPhysicsWorld(PhysicsWorld* world){ sceneWorld = world; };
    
    bool onContactBegin( cocos2d::PhysicsContact &contact );

    bool onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *event );
    void onTouchMoved(Touch* touch, Event* event);
    
    void setBlock();
    
    Size visibleSize;
    Vec2 origin;
    
    //UI
    MenuItemImage *pauseButton;
    MenuItemImage *playButton;
    Menu* menu;
    Label* gameover;
    Label* gamewin;
    void setUI();
    
//    unsigned int score;
    Label *scoreLabel;
    
    void update(float dt);
};

#endif /* defined(__BreakOut__GameScene__) */
