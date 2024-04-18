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

#include "SplashScene.h"
#include "ui/CocosGUI.h"
#include "HelloWorldScene.h"
#include "NetworkManager.h"
//#include "OnlineConnectScene.h"
USING_NS_CC;
Scene* scene = nullptr;
Scene* SplashScene::createScene()
{
    auto scene = Scene::create();
    auto layer = SplashScene::create();
    scene->addChild(layer);
    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in SplashSceneScene.cpp\n");
}

// on "init" you need to initialize your instance
bool SplashScene::init()
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
                                           CC_CALLBACK_1(SplashScene::menuCloseCallback, this));

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

    
    // create and initialize a label

    auto label = Label::createWithTTF("Tic-tac-toe", "fonts/Marker Felt.ttf", 24);
    label->setColor(Color3B::RED);
    auto label1 = Label::createWithTTF("Play clone", "fonts/Marker Felt.ttf", 24);
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
        label1->setPosition(Vec2(visibleSize.width / 2 - 100,
            100 + visibleSize.height / 2));
        // add the label as a child to this layer
        this->addChild(label, 1);
        this->addChild(label1, 1);
    }

    // add "SplashScene" splash screen"
    auto blackScreen = LayerColor::create(Color4B(255, 255, 255, 255));
    this->addChild(blackScreen);

    //Button play clone
    auto button = ui::Button::create("PlayButton_Normal.png");

    button->setPosition(Vec2(0.5 * visibleSize.width, 0.5 * visibleSize.height + 100));
    button->setScale(0.1);
    button->addTouchEventListener(CC_CALLBACK_2(SplashScene::goToHelloWorldScene, this));

    if (button == nullptr)
    {
        problemLoading("'PlayButton_Normal.png'");
    }
    else
    {
        
        
        
           
        if (button->getParent() == nullptr) {
            this->addChild(button, 1);
        }
        else {
            CCLOG("Button already has a parent");
        }
        
        
        //this->addChild(sprite, 0); // dua ra man hinh
    }

    // button play online
    auto label2 = Label::createWithTTF("Play online", "fonts/Marker Felt.ttf", 24);
    label2->setColor(Color3B::BLACK);
    label2->setPosition(Vec2(visibleSize.width / 2 - 100,
        visibleSize.height / 2));
    this->addChild(label2, 1);
    auto button1 = ui::Button::create("play_online.png");

    button1->setPosition(Vec2(0.5 * visibleSize.width, 0.5 * visibleSize.height));
    button1->setScale(0.1);
    button1->addTouchEventListener(CC_CALLBACK_2(SplashScene::goToNetworkScene, this));
    
    if (button1 == nullptr)
    {
        problemLoading("'play_online.png'");
    }
    else
    {

        
        this->addChild(button1, 1);
        
        
    }

    // button play with AI
    auto playWithAIButton = MenuItemImage::create(
        "PlayWithAIButton.png",
        "PlayWithAIButton.png",
        CC_CALLBACK_1(SplashScene::playWithAIButtonCallback, this));

    if (playWithAIButton)
    {
        float x = origin.x + visibleSize.width / 2;
        float y = origin.y + visibleSize.height / 2 + 100;
        playWithAIButton->setPosition(Vec2(x, y));

        auto menu = Menu::create(playWithAIButton, nullptr);
        menu->setPosition(Vec2::ZERO);
        this->addChild(menu, 1);
    }

    
    return true;
}
void SplashScene::goToNetworkScene(Ref* sender, ui::Widget::TouchEventType type) {
    if (type == ui::Widget::TouchEventType::BEGAN) {
        auto scene = NetworkScene::createScene(); // Thay GameScene bằng tên của Scene bạn muốn chuyển đến
        Director::getInstance()->replaceScene(scene);
        

    }
}
void SplashScene::goToHelloWorldScene(Ref* sender, ui::Widget::TouchEventType type) {
    if (type == ui::Widget::TouchEventType::BEGAN) {
        auto scene = HelloWorld::createScene(); // Thay GameScene bằng tên của Scene bạn muốn chuyển đến
        Director::getInstance()->replaceScene(scene);
    }
}

void SplashScene::playWithAIButtonCallback(Ref* pSender)
{
    //Director::getInstance()->replaceScene(AIPlayerScene::createScene());
    // Add logic here to initialize AI player mode
}

void SplashScene::playOnlineButtonCallback(Ref* pSender)
{
    // Director::getInstance()->replaceScene(OnlineConnectScene::createScene());
    // Add logic here to initialize online game mode
}

void SplashScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
