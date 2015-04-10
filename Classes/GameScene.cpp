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
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
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
    
    //set ball
    ball = Sprite::create("CloseNormal.png");
    ball->setPosition(100, 100);
    
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
    
    //set paddle
    paddle = Sprite::create("paddle.png");
    paddle->cocos2d::Node::setPosition(Point(visibleSize.width / 2, paddle->getContentSize().height / 2));

    auto paddleBody = PhysicsBody::createEdgeBox(paddle->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
    paddleBody->getShape(0)->setRestitution(1.0f);
    paddleBody->getShape(0)->setFriction(0.0f);
    paddleBody->getShape(0)->setDensity(10.0f);
    paddleBody->setGravityEnable(false);
    paddleBody->setDynamic(false);
    
    paddle->setPhysicsBody(paddleBody);
    paddle->setTag(2);
    this->addChild(paddle);
    
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
    auto spriteA = contact.getShapeA()->getBody()->getNode();
    auto spriteB = contact.getShapeB()->getBody()->getNode();
    int tagA = spriteA->getTag();
    int tagB = spriteB->getTag();
    
    if (tagA == 3)
    {
        spriteA->removeFromParentAndCleanup(true);
    }
    
    if (tagB == 3)
    {
        spriteB->removeFromParentAndCleanup(true);
    }
    return true;
}


void GameScene::setBlock()
{
    for (int i = 0; i < 10; i++) {
        
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

