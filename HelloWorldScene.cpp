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
#include "FinishGameX.h"
#include "FinishGameO.h"
#include "FinishGameDraw.h"
USING_NS_CC;
int HelloWorld::getWinner() const{
    return who_win;
}
HelloWorld::~HelloWorld() {
    for (int i = 0; i < 51; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int **create_matrix(int** matrix, int a, int b) {

    matrix = new int* [a]; // axb
    /*
        0: chua danh
        1: X
        2: O
        3: cam danh
    */
    for (int i = 0; i < a; ++i) {
        matrix[i] = new int[b];
        for (int j = 0; j < b; ++j) {
            matrix[i][j] = 0;
        }
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < b; ++j) {
            matrix[i][j] = 3;
        }
    }
    for (int i = a - 10; i < a; i++) {
        for (int j = 0; j < b; ++j) {
            matrix[i][j] = 3;
        }
    }
    for (int i = 0; i < a; ++i) {
        for (int j = 0; j < 10; j++) {
            matrix[i][j] = 3;
        }
    }
    for (int i = 0; i < a; ++i) {
        for (int j = b - 10; j < b; j++)
        matrix[i][j] = 3;
    }
    // ko cho phep danh o bien man hinh
    return matrix;
}
bool HelloWorld::check_Win_Con(int** matrix, int a, int b) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    // Kiểm tra hàng ngang
    for (int i = 0; i < a; ++i) {
        for (int j = 0; j <= b - 5; ++j) {
            if (matrix[i][j] == 1 || matrix[i][j] == 2) {
                bool win = true;
                for (int k = 1; k < 5; ++k) {
                    if (matrix[i][j] != matrix[i][j + k]) {
                        win = false;
                        break;
                    }
                }
                if (win) {
                    
                    if (matrix[i][j] == 1) {
                        who_win = 1;
                        
                        
                    }
                    else {
                        who_win = 2;
                        
                        
                    }
                    return true;
                }
            }
        }
    }

    // Kiểm tra hàng dọc
    for (int i = 0; i <= a - 5; ++i) {
        for (int j = 0; j < b; ++j) {
            if (matrix[i][j] == 1 || matrix[i][j] == 2) {
                bool win = true;
                for (int k = 1; k < 5; ++k) {
                    if (matrix[i][j] != matrix[i + k][j]) {
                        win = false;
                        break;
                    }
                }
                if (win) {
                    
                    if (matrix[i][j] == 1) {
                        who_win = 1;
                        
                        
                    }
                    else {
                        who_win = 2;
                        
                        
                    }
                    return true;
                }
            }
        }
    }

    // Kiểm tra đường chéo chính
    for (int i = 0; i <= a - 5; ++i) {
        for (int j = 0; j <= b - 5; ++j) {
            if (matrix[i][j] == 1 || matrix[i][j] == 2) {
                bool win = true;
                for (int k = 1; k < 5; ++k) {
                    if (matrix[i][j] != matrix[i + k][j + k]) {
                        win = false;
                        break;
                    }
                }
                if (win) {
                    
                    if (matrix[i][j] == 1) {
                        who_win = 1;
                        
                        
                    }
                    else {
                        who_win = 2;
                        
                        
                    }
                    return true;
                }
            }
        }
    }

    // Kiểm tra đường chéo phụ
    for (int i = 0; i <= a - 5; ++i) {
        for (int j = 4; j < b; ++j) {
            if (matrix[i][j] == 1 || matrix[i][j] == 2) {
                bool win = true;
                for (int k = 1; k < 5; ++k) {
                    if (matrix[i][j] != matrix[i + k][j - k]) {
                        win = false;
                        break;
                    }
                }
                if (win) {
                    
                    if (matrix[i][j] == 1) {
                        who_win = 1;
                        
                        
                    }
                    else {
                        who_win = 2;
                        
                        
                    }
                    return true;
                }
            }
        }
    }

    return false;
}
void HelloWorld::clean_screen(int a, int b) {
    for (int i = 1; i < 50; i++) {
        for (int j = 1; j < 40; j++) {
            matrix[i][j] = 0;
        }
    }
}
void HelloWorld::prohibit(int a, int b) {
    for (int i = 1; i < 50; i++) {
        for (int j = 1; j < 40; j++) {
            if (matrix[i][j] == 0) matrix[i][j] = 3;
        }

    }
}
Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    if (scene == nullptr) CCLOG("Failed to create HelloWorld Scene");
    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
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
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

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

    auto label = Label::createWithTTF("Tic-tac-toe", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));
        
        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    // add "HelloWorld" splash screen"
    //auto sprite = Sprite::create("luoiovuong.png");
    //if (sprite == nullptr)
    //{
    //    problemLoading("'luoiovuong.png'");
    //}
    //else
    //{
        // position the sprite on the center of the screen
        // sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
        //sprite->setAnchorPoint(Vec2(0, 0)); // position of AnchorPoint matches the image
        //sprite->setPosition(Vec2(0.5 * visibleSize.width, 0.5 * visibleSize.height)); // position of AnchorPoint matches the screen
        //sprite->setScaleX(0.5); // the size of the image will be equal to 0.5 the old size
        //sprite->setScaleY(0.5);
        //sprite->setRotation(90); // xoay 1 goc 90 do theo chieu kim dong ho
        //sprite->setSkewY(30); // nghieng doi tuong 1 goc 30 do
        //auto ActionMove = MoveBy::create(3, Vec2(-1, -1)); // di chuyen tron 3 giay toi diem (300,100)
        // auto ActionMove = MoveBy::create(3, Vec2(300, 100)); // di chuyen tron 3 giay them 1 cach no (300,100)
        //sprite->runAction(ActionMove); // chi dinh doi tuong di chuyen 
        // tuong tu voi RotateTo va RotateBy
        //auto ActionRotate = RotateBy::create(3, 30);
        //auto ActionSequence = Sequence::create(ActionMove, ActionRotate, NULL); // thuc hien tuan tu cac hoat dong trong danh sach
        //auto ActionSpawn = Spawn::create(ActionMove, ActionRotate, NULL); // thuc hien dong thoi cac hoat dong trong danh sach
        //auto ActionRepeat = RepeatForever::create(ActionSpawn); // thuc hien lap lai hanh dong (repeat hoac repeatforever)
        //sprite->runAction(ActionRepeat);



        //sprite->runAction(ActionMove);
        // add the sprite as a child to this layer
        //this->addChild(sprite, 0); // dua ra man hinh
    //}
    CCLOG("Chieu rong man hinh: %d", visibleSize.width);
    matrix = create_matrix(matrix, 51, 41);

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    
    return true;
}

Vec2 roundV(Vec2 a) {
    float m = a.x;
    float n = a.y;
    while (m >= 20) m -= 20;
    if (m < 10) a.x -= m;
    else a.x += (20 - m);
    while (n >= 20) n -= 20;
    if (n < 10) a.y -= n;
    else a.y += (20 - n);
    return a;
}
bool HelloWorld::check_full(int** matrix, int a, int b) {
    for (int i = 10; i < a - 10; i++) {
        for (int j = 10; j < b - 10; j++) {
            if (matrix[i][j] == 0 || matrix[i][j] == 3) {
                return false;
            }
        }
    }
    return true;
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* unused_event) {
    
    if (check_full(matrix, 51, 41)) {
        auto scene = DrawScene::createScene(); // Thay GameScene bằng tên của Scene bạn muốn chuyển đến
        Director::getInstance()->replaceScene(scene);
        clean_screen(51, 41);
    }
    if (win) {
        clean_screen(51, 41);
        if (who_win == 1) {
            auto scene = FinishGameScene::createScene(); // Thay GameScene bằng tên của Scene bạn muốn chuyển đến
            Director::getInstance()->replaceScene(scene);
        }
        else {
            auto scene = FinishGameSceneO::createScene(); // Thay GameScene bằng tên của Scene bạn muốn chuyển đến
            Director::getInstance()->replaceScene(scene);
        }

    }
    Vec2 touchLocation = roundV(touch->getLocation());
    int m = touchLocation.x / 20;
    int n = touchLocation.y / 20;
    
    if (m < 0 || m > 50) return false;
    if (n < 0 || n > 50) return false;
    
    auto sprite1 = Sprite::create("res/X.png");
    auto sprite2 = Sprite::create("res/O.png");
    
    if (sprite1 == nullptr)
    {
        problemLoading("'X.png'");
        return false;
    }
    else if (sprite2 == nullptr)
    {
        problemLoading("'O.png'");
        return false;
    }
    else
    {   
        
        
        if (matrix[m][n] == 0) {
            sprite1->setScale(0.1);
            sprite2->setScale(0.1);

            // o danh truoc
            if (a % 2) {
                matrix[m][n] = 1;
                sprite1->setPosition(touchLocation);
                addChild(sprite1);
                CCLOG("X danh: %i%s%i", m * 20, " ", n * 20);
            }
            else {
                sprite2->setPosition(touchLocation);
                addChild(sprite2);
                CCLOG("Y danh: %i%s%i", m * 20, " ", n * 20);
                matrix[m][n] = 2;
            }
            a++;
            if (check_Win_Con(matrix, 51, 41)) {
                CCLOG("abc");
                prohibit(51, 41);
                win = true;
            }
            return true;
        }
        else {
            return false;
            
        }
        
    }
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
