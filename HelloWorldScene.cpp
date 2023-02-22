/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "GameOverScene.hpp"
#include "SimpleAudioEngine.h"
#include <ui/CocosGUI.h>
#include<iostream>
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}


bool HelloWorld::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    Color4B colorArr[4] = {
        Color4B(120, 0, 0, 255), //RED
        Color4B(0, 120, 0, 255), //GREEN
        Color4B(0, 0, 120, 255), //BLUE
        Color4B(120, 120, 120, 255) //GREY
    };
    
    Vec2 positions[4]{
        Vec2(origin.x,visibleSize.height/2), //TOP-LEFT
        Vec2(visibleSize.width/2+origin.x,visibleSize.height/2), //TOP-RIGHT
        Vec2(origin.x,origin.y), //BOTTOM-LEFT
        Vec2(visibleSize.width/2+origin.x,origin.y) //BOTTOM-RIGHT
    };
    
    auto layerSize = Size(visibleSize.width/2,visibleSize.height/2);
                                         
    auto layerRed = LayerColor::create(colorArr[0]);
    layerRed->setContentSize(layerSize);
    layerRed->setPosition(positions[0]);
    this->addChild(layerRed);
    
    auto layerGreen = LayerColor::create(colorArr[1]);
    layerGreen->setContentSize(layerSize);
    layerGreen->setPosition(positions[1]);
    this->addChild(layerGreen);

    auto layerBlue = LayerColor::create(colorArr[2]);
    layerBlue->setPosition(positions[2]);
    layerBlue->setContentSize(layerSize);
    this->addChild(layerBlue);

    layerGrey = LayerColor::create(colorArr[3]);
    layerGrey->setPosition(positions[3]);
    layerGrey->setContentSize(layerSize);
    this->addChild(layerGrey);
    
    listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan,this);
    listener->setEnabled(false);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    label = Label::createWithTTF("Score : 0", "fonts/arial.ttf", 24);
    label->setPosition(Vec2(visibleSize.width/2+origin.x,visibleSize.height*7/8));
    this->addChild(label);
    
    std::vector<int> n = {0,1,2,3};
    
    auto menu = Menu::create();
    auto start = MenuItemFont::create("Start",[=](Ref *pSender){
        menu->removeFromParent();
        listener->setEnabled(true);
        score=0;
        this->schedule([=](float delta) mutable {
            listener->setEnabled(true);
            if(!flag){
                this->unschedule("game");
                auto scene = GameOver::createScene(score);
                Director::getInstance()->replaceScene(scene);
                
            }
            flag = false;
            int last = n.at(3);
            n.pop_back();
            n.insert(n.begin(), last);
            std::random_shuffle(n.begin()+1, n.end());
            std::random_shuffle(n.begin(), n.end()-1);
            layerRed->setPosition(positions[n.at(0)]);
            layerGreen->setPosition(positions[n.at(1)]);
            layerBlue->setPosition(positions[n.at(2)]);
            layerGrey->setPosition(positions[n.at(3)]);
        }, 1, "game");
        
    });
    
    menu->addChild(start);
    this->addChild(menu);
    

    return true;
}

bool HelloWorld::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event){
    Vec2 touchLocation = touch->getLocation();
    Rect touchArea = layerGrey->getBoundingBox();
    listener->setEnabled(false);
    if(touchArea.containsPoint(touchLocation)){
        score++;
        __String *tempScore = __String::createWithFormat("Score : %i",score);
        label->setString(tempScore->getCString());
        flag=true;
        std::cout<<score;
    }else{
        flag=false;
        auto scene = GameOver::createScene(score);
        Director::getInstance()->replaceScene(scene);
    }
    return false;
}
