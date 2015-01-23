#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    _map=TMXTiledMap::create("test.tmx");
    addChild(_map);
    
    TMXObjectGroup *tmxgroup=_map->getObjectGroup("Objects");
    CCASSERT(NULL!=tmxgroup, "'Objects' object group not found");
    auto tmxhero=tmxgroup->getObject("hero");
    int x=tmxhero["x"].asInt();
    herox=x;
    int y=tmxhero["y"].asInt();
//    _player=Sprite::create("taiga.png");
//    _player->setPosition(x, y+20);
//    addChild(_player);
    //添加人物
    hero=Hero::create();
    hero->InitHeroSprite("taiga.png");
    hero->setPosition(x, y+22);
    addChild(hero);
  
    //添加按钮图片
    auto leftbtn=Sprite::create("Thumb_dpad_left.png");
    leftbtn->setPosition(45,45);
    addChild(leftbtn);
    
    auto rightbtn=Sprite::create("Thumb_dpad_right.png");
    rightbtn->setPosition(180,45);
    addChild(rightbtn);
    
    auto jumpbtn=Sprite::create("Thumb_dpad_jump.png");
    jumpbtn->setPosition(visibleSize.width-150,45);
    addChild(jumpbtn);
  

    //添加点击事件
    auto listerner = EventListenerTouchAllAtOnce::create();
//    listerner->setSwallowTouches(true);
//    listerner->onTouchBegan=[](Touch* touch,Event* event){
//        
//        auto target = static_cast<Sprite*>(event->getCurrentTarget());
//        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
//        log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
//        auto move=MoveTo::create(2, locationInNode);
//        //定义回调,结束停止人物动画
////        auto func=[&](){};
////        auto callback=CallFunc::create(func);
////        Sequence *seq=Sequence::create(move, callback, nullptr);
//        hero->runAction(move);
//
//        return true;
//    };
    
    // 键盘测试
    auto listener2 = EventListenerKeyboard::create();
    listener2->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
    listener2->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, this);
    //****
    
    
//    listerner->onTouchEnded = [](Touch* touch, Event* event){
//        auto target = static_cast<Sprite*>(event->getCurrentTarget());
//        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
//        log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
//    };

    //使用 CC_CALLBACK_2
    listerner->onTouchesBegan=CC_CALLBACK_2(HelloWorld::onTouchesBegan,this);
    listerner->onTouchesEnded=CC_CALLBACK_2(HelloWorld::onTouchesEnded, this);
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listerner, this);
    return true;
}

void HelloWorld::onTouchesBegan(const std::vector<cocos2d::Touch*>& touch, cocos2d::Event *event){
    auto target = static_cast<Sprite*>(event->getCurrentTarget());
    Vector<Touch*>::const_iterator touchIter = touch.begin();
    Touch *pTouch = (Touch*)(*touchIter);
    Point locationInNode = target->convertToNodeSpace(pTouch->getLocation());
    log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
    hero->walkto(locationInNode);

   
//    auto pos=hero->getPosition();
//    
//    hero->IsRunning=true;
//    if (locationInNode.x>=500) {
//        hero->SetAnimation("taigelist.plist", "taigelist.png","taga",8,false);
//        pos.x+=2;
//            log("herox2=%f",pos.x);
//        hero->walkto(pos);
//    }else{
//        hero->SetAnimation("taigelist.plist", "taigelist.png","taga",8,true);
//        pos.x-=2;
//        
//        hero->walkto(pos);
//    }

    
}
void HelloWorld::onTouchesEnded(const std::vector<cocos2d::Touch*>& touch, cocos2d::Event *event){
    hero->StopAnimation();
}

// 键位响应函数原型
void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    log("Key with keycode %d pressed", keyCode);
}
void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    log("Key with keycode %d released", keyCode);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
