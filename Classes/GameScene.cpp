//
//  GameScene.cpp
//  BreakOut
//
//  Created by Yanxu Zheng on 10/04/2015.
//
//

#include "GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    auto scene = Scene::createWithPhysics();
    
    //for debug show the physics body of object
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    scene->getPhysicsWorld()->setGravity( Vect( 0, -10 ) );

    
    auto layer = GameScene::create();
    layer->SetPhysicsWorld( scene->getPhysicsWorld() );
    
    scene->addChild(layer);
    
    return scene;
}

bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    isGameover = false;
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    setUI();
    
    //set physic edge of the screen
    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
    edgeBody->getShape(0)->setRestitution(1.0f);
    edgeBody->getShape(0)->setFriction(0.0f);
    edgeBody->getShape(0)->setDensity(1.0f);
    
    auto edgeNode = Node::create();
    edgeNode->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    edgeNode->setPhysicsBody(edgeBody);
    edgeNode->setTag(0);
    this->addChild(edgeNode);

    //set paddle
    paddle = Sprite::create("paddle.png");
    paddle->setPosition(Point(visibleSize.width / 2, paddle->getContentSize().height / 2));
    
    auto paddleBody = PhysicsBody::createEdgeBox(paddle->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
    paddleBody->getShape(0)->setRestitution(1.0f);
    paddleBody->getShape(0)->setFriction(0.0f);
    paddleBody->getShape(0)->setDensity(10.0f);
    paddleBody->setGravityEnable(false);
    paddleBody->setDynamic(false);
    
    paddle->setPhysicsBody(paddleBody);
    paddle->setTag(2);
    this->addChild(paddle);

    //set ball
    ball = Sprite::create("CloseNormal.png");
    ball->setPosition(Point(visibleSize.width / 2, paddle->getContentSize().height+ball->getContentSize().height/2));
    
    auto ballBody = PhysicsBody::createCircle(ball->getContentSize().width / 2.);
    ballBody->getShape(0)->setRestitution(1.0f);
    ballBody->getShape(0)->setFriction(0.0f);
    ballBody->getShape(0)->setDensity(1.0f);
    ballBody->setContactTestBitmask(1);
    ballBody->setGravityEnable(false);
    ball->setPhysicsBody(ballBody);
    ball->setTag(1);
    this->addChild(ball);
    
    
    Vect force = Vect(1000000.0f, 1000000.0f);
    ballBody->applyImpulse(force);
    
    
    //set blocks
    setBlock();
    
    //set touch listerner
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority( touchListener, this );

    //set contact listener
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    this->scheduleUpdate();
    
    return true;
}

bool GameScene::onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *event )
{
    Point touchLocation = this->convertToWorldSpace(this->convertTouchToNodeSpace(touch));
    paddle->setPositionX(touchLocation.x);
    
    return true;
}


void GameScene::onTouchMoved(Touch* touch, Event* event)
{
    Point touchLocation = this->convertToWorldSpace(this->convertTouchToNodeSpace(touch));
    paddle->setPositionX(touchLocation.x);
}

bool GameScene::onContactBegin( cocos2d::PhysicsContact &contact )
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    
    if (nodeA && nodeB)
    {
        if (nodeA->getTag() == 3)
        {
            nodeA->removeFromParentAndCleanup(true);
        }
        else if (nodeB->getTag() == 3)
        {
            nodeB->removeFromParentAndCleanup(true);
        }
    }
        return true;
}


void GameScene::setBlock()
{
    for (int i = 0; i < 3; i++) {
        
        static int padding = 100;
        
        auto block = Sprite::create("block.png");
        
        auto blockBody = PhysicsBody::createBox(block->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
        blockBody->getShape(0)->setDensity(10.0f);
        blockBody->getShape(0)->setFriction(0.0f);
        blockBody->getShape(0)->setRestitution(1.f);
        blockBody->setContactTestBitmask(1);
        blockBody->setDynamic(false);
        
        int xOffset = padding + block->getContentSize().width / 2 + ((block->getContentSize().width + padding)*i);
        block->setPosition(xOffset, 450);
        block->setPhysicsBody(blockBody);
        block->setTag(3);
        this->addChild(block);
    }
}

void GameScene::setUI(){
    pauseButton = MenuItemImage::create("PauseButton.png", "PauseButton.png", CC_CALLBACK_0(GameScene::PauseGame, this));
    pauseButton->setPosition(Point(visibleSize.width - pauseButton->getContentSize().width, visibleSize.height - pauseButton->getContentSize().height/2));
    
    playButton = MenuItemImage::create("rePlayButton1.png", "rePlayButton2.png", CC_CALLBACK_0(GameScene::StartGame, this));
    playButton->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
    playButton->setVisible(false);
    
    menu = Menu::create(pauseButton, playButton, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 2);
    
    TTFConfig ttfconfig("fonts/Marker Felt.ttf",40);
    gameover = Label::createWithTTF(ttfconfig, " Game Over !",TextHAlignment::CENTER);
    gameover->setPosition(Point(visibleSize.width/2,visibleSize.height/2+gameover->getContentSize().height));
    gameover->setVisible(false);
    gameover->setColor(Color3B::WHITE);
    this->addChild(gameover, 2);
    
}

void GameScene::PauseGame()
{
    Director::getInstance()->pause();
    ball->setVisible(false);
    playButton->setVisible(true);
    pauseButton->setVisible(false);
    ball->pause();
//    ActionManager::pauseTarget(ball);
}

void GameScene::GameOver()
{
    PauseGame();
    playButton->setPosition(Point(visibleSize.width/2,visibleSize.height/2-gameover->getContentSize().height));
    gameover->setVisible(true);
    isGameover = true;
}

void GameScene::StartGame()
{
    if(!isGameover)
    {
        Director::getInstance()->resume();
        playButton->setVisible(false);
        pauseButton->setVisible(true);
        ball->setVisible(true);
    }
    else
    {
//        this->unscheduleAllSelectors();
        Director::getInstance()->resume();
        this->removeAllChildren();
        this->init();
//        auto scene = GameScene::createScene();
//        Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
        
    }
}

void GameScene::update(float dt)
{
    if (ball->getPositionY() <= ball->getContentSize().height/2)
    {
        GameOver();
    }
}
