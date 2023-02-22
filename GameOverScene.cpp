//
//  GameOverScene.cpp
//  ColorGame-mobile
//
//  Created by SarthakR on 21/02/23.
//

#include "GameOverScene.hpp"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include <ui/CocosGUI.h>
#include<iostream>
USING_NS_CC;

int score;
Scene* GameOver::createScene(int s)
{
    score=s;
    return GameOver::create();
}


bool GameOver::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    auto label = Label::createWithTTF("GAME OVER", "fonts/arial.ttf", 36);
    label->setPosition(Vec2(visibleSize.width/2+origin.x,visibleSize.height*7/8));
    this->addChild(label);
    
    __String *tempScore = __String::createWithFormat("Score : %i",score);
    auto scoreLabel = Label::createWithTTF(tempScore->getCString(), "fonts/arial.ttf", 36);
    scoreLabel->setPosition(Vec2(visibleSize.width/2+origin.x,visibleSize.height*6/8));
    this->addChild(scoreLabel);
    
    auto menu = Menu::create();
    auto restart = MenuItemFont::create("Restart",[](Ref *pSender){
        auto scene = HelloWorld::createScene();
        Director::getInstance()->replaceScene(scene);
    });
    restart->setPosition(Vec2(visibleSize.width/2+origin.x,visibleSize.height*4/8));
    menu->addChild(restart);
    auto quit = MenuItemFont::create("Quit",[](Ref *pSender){
        Director::getInstance()->end();
    });
    quit->setPosition(Vec2(visibleSize.width/2+origin.x,visibleSize.height*3/8));
    menu->addChild(quit);
    menu->alignItemsVertically();
    this->addChild(menu);
    

    return true;
}

