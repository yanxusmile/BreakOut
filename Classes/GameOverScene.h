//
//  GameOverScene.h
//  BreakOut
//
//  Created by Yanxu Zheng on 23/04/2015.
//
//

#ifndef __BreakOut__GameOverScene__
#define __BreakOut__GameOverScene__

#include <stdio.h>
USING_NS_CC;

class GameOverScene : public Layer
{
public:
    static Scene* createScene(unsigned int tempScore);
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameOverScene);
    
private:
//    void GoToMainMenuScene( cocos2d::Ref *sender );
    void GoToGameScene( cocos2d::Ref *sender );

};
#endif /* defined(__BreakOut__GameOverScene__) */
