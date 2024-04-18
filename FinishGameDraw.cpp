﻿/****************************************************************************
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

#include "FinishGameDraw.h"
#include "ui/CocosGUI.h"
#include "SplashScene.h"
USING_NS_CC;
Scene* DrawScene::createScene()
{
    auto scene = Scene::create();
    auto layer = DrawScene::create();
    scene->addChild(layer);
    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in DrawSceneScene.cpp\n");
}

// on "init" you need to initialize your instance
bool DrawScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(DrawScene::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("The game is finished, no one is the winner", "fonts/Marker Felt.ttf", 24);
    auto label1 = Label::createWithTTF("Play Again!", "fonts/Marker Felt.ttf", 24);
    label1->setColor(Color3B::BLACK);
    
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));
        label1->setPosition(Vec2(visibleSize.width / 2,
            150 + visibleSize.height / 2));

        label->setColor(Color3B::RED);
        // add the label as a child to this layer
        this->addChild(label, 1);
        this->addChild(label1, 1);
    }

    // add "DrawScene" splash screen"
    auto blackScreen = LayerColor::create(Color4B(255, 255, 255, 255));
    this->addChild(blackScreen);
   
    auto button = ui::Button::create("res/Retry button.png");
    button->setColor(Color3B::BLACK);
    button->setPosition(Vec2(0.5 * visibleSize.width, 0.5 * visibleSize.height));
    button->setScale(0.3);
    button->addTouchEventListener(CC_CALLBACK_2(DrawScene::goToSplashScene, this));

    if (button == nullptr)
    {
        problemLoading("'res/Retry button.png'");
    }
    else
    {




        
        this->addChild(button, 1);
        
        
    }
    return 1;

}

void DrawScene::goToSplashScene(Ref * sender, ui::Widget::TouchEventType type) {
    if (type == ui::Widget::TouchEventType::BEGAN) {
        auto scene = SplashScene::createScene(); // Thay GameScene bằng tên của Scene bạn muốn chuyển đến
        Director::getInstance()->replaceScene(scene);
    }
}


void DrawScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
