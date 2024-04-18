// NetworkSceneManager.cpp
#include "NetworkManager.h"
#include "json/document.h"
#include "json/rapidjson.h"
#include "network/SocketIO.h"
#include "ui/CocosGUI.h"
#include "FinishGameX.h"
#include "FinishGameO.h"
#include "FinishGameDraw.h"
#include "string.h"
USING_NS_CC;

int NetworkScene::getWinner() const {
    return who_win;
}

NetworkScene::~NetworkScene() {
    
    for (int i = 0; i < 51; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}
bool NetworkScene::check_full(int** matrix, int a, int b) {
    for(int i = 10; i < a - 10; i++) {
        for (int j = 10; j < b - 10; j++) {
            if (matrix[i][j] == 0 || matrix[i][j] == 3) {
                return false;
            }
        }
    }
    return true;
}
int** NetworkScene::create_matrix(int** matrix, int a, int b) {

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
bool NetworkScene::check_Win_Con(int** matrix, int a, int b) {
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
void NetworkScene::clean_screen(int a, int b) {
    for (int i = 1; i < 50; i++) {
        for (int j = 1; j < 40; j++) {
            matrix[i][j] = 0;
        }
    }
}
void NetworkScene::prohibit(int a, int b) {
    for (int i = 1; i < 50; i++) {
        for (int j = 1; j < 40; j++) {
            if (matrix[i][j] == 0) matrix[i][j] = 3;
        }

    }
}

Scene* NetworkScene::createScene()
{
    
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = NetworkScene::create();
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}


// on "init" you need to initialize your instance
bool NetworkScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(NetworkScene::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
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
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
        
    }

    // Tạo một DrawNode
    auto drawNode = DrawNode::create();
    this->addChild(drawNode);

    // Kích thước của mỗi ô vuông và số lượng ô vuông trên mỗi hàng và cột
    float squareSize = 20.0f;
    

    // Vẽ lưới ô vuông
    for (int i = 10; i < 41; ++i) {
        for (int j = 10; j < 31; ++j) {
            // Tính toạ độ của ô vuông
            float x = i * squareSize;
            float y = j * squareSize;

            // Vẽ hình chữ nhật (ô vuông) tại vị trí (x, y)
            drawNode->drawRect(Vec2(x, y), Vec2(x + squareSize, y + squareSize), Color4F::WHITE);
        }
    }

    matrix = create_matrix(matrix, 51, 41);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(NetworkScene::onTouchBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

    // textField = TextField::create("...", "fonts/arial.ttf", 30);
    // this->addChild(textField);
    // textField->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    // textField->addEventListener(CC_CALLBACK_2(NetworkScene::textFieldEvent, this));
    // connect to server
    // listView = ui::ListView::create();
    // listView->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 50));
    // listView->setDirection(ui::ListView::Direction::VERTICAL);
    // listView->setBounceEnabled(true);
    // listView->setContentSize(Size(200, 200));
    // this->addChild(listView);
    
    if (_client == NULL && a == 0) {
        _client = SocketIO::connect("http://192.168.56.1:8888", *this);
        _isConnected = true;
    }
    _client->on("you", CC_CALLBACK_2(NetworkScene::onReceiveEvent, this));
    _client->on("hello", CC_CALLBACK_2(NetworkScene::onReceiveEvent, this));
    _client->on("solo", CC_CALLBACK_2(NetworkScene::onReceiveEvent, this));
    _client->on("result", CC_CALLBACK_2(NetworkScene::onReceiveEvent, this));


    return true;
}

void NetworkScene::onConnect(SIOClient* client) {
    
    // SocketIO::connect success
}
void NetworkScene::onMessage(SIOClient* client, const std::string& data) {
    // SocketIO::send receive
}
void NetworkScene::onClose(SIOClient* client) {
    // SocketIO::disconnect success
    if (client) {
        client->disconnect();
 
    }
    
}
void NetworkScene::onError(SIOClient* client, const std::string& data) {
    // SocketIO::failed
    CCLOG("There is a problem with the connection");
}

void NetworkScene::onReceiveEvent(SIOClient* client, const std::string& data) {
    CCLOG("Event: %s", data.c_str());
    
    if (data == "\"Start\"") {
        
        isStart = true;
    }
    else if (data.substr(0, 12) == "\"init turn: ") {
        auto label1 = Label::createWithTTF("Turn: ", "fonts/Marker Felt.ttf", 50);
        label1->setPosition(Vec2(800, 740));
        this->addChild(label1);
        CCLOG("Ký tự số 13 là: %c", data[12]);
        if (data.substr(12, 1) == "0") {
            // initial turn = X
            auto sprite = Sprite::create("res/O Win.png");
            sprite->setPosition(920, 740);
            sprite->setScale(0.2, 0.2);
            this->addChild(sprite);
        }
        else {
            // initial turn = O
            auto sprite = Sprite::create("res/X Win.png");
            sprite->setPosition(920, 740);
            sprite->setScale(0.2, 0.2);
            this->addChild(sprite);
        }
    }
    else if (data == "\"end_game\"") {
        a = 0;
        
        _isConnected = false;
        isStart = false;
    }
    else if (data == "\"X win\"") {
        
        
        auto scene = FinishGameScene::createScene(); // Thay GameScene bằng tên của Scene bạn muốn chuyển đến
        Director::getInstance()->replaceScene(scene);
    }
    else if (data == "\"O win\"") {
        
        
        auto scene = FinishGameSceneO::createScene(); // Thay GameScene bằng tên của Scene bạn muốn chuyển đến
        Director::getInstance()->replaceScene(scene);
    }
    else if (data == "\"Draw\"") {
        
        
        auto scene = DrawScene::createScene(); // Thay GameScene bằng tên của Scene bạn muốn chuyển đến
        Director::getInstance()->replaceScene(scene);
    }
    else if (data == "\"You are X\"") {
        // if you are X
        CCLOG("I'm X");
        you_are = 1;
        auto label = Label::createWithTTF("You are", "fonts/Marker Felt.ttf", 50);
        label->setPosition(Vec2(100, 740));
        this->addChild(label);
        auto sprite = Sprite::create("res/X Win.png");
        sprite->setPosition(220, 740);
        sprite->setScale(0.2, 0.2);
        this->addChild(sprite);
    }
    else if (data == "\"You are O\"") {
        // if you are O
        CCLOG("I'm O");
        you_are = 0;
        auto label = Label::createWithTTF("You are", "fonts/Marker Felt.ttf", 50);
        label->setPosition(Vec2(100, 740));
        this->addChild(label);
        auto sprite = Sprite::create("res/O Win.png");
        sprite->setPosition(220, 740);
        sprite->setScale(0.2, 0.2);
        this->addChild(sprite);
    }
    else {
        
        std::string value;
        
        for (int i = 15; i < data.length() - 5; i++) {
            if (data[i] == '\0') break;
            value += data[i];
        }
        value = value.c_str();
        
        std::string numStr;
        if (value.length() > 2) numStr = value.substr(2); // Bỏ qua ký tự '1 ' hoặc là '0 '
        int x = 0, y = 0;
        int pos = numStr.find(' ');
        if (pos != std::string::npos) {
            x = std::stoi(numStr.substr(0, pos)); // Lấy số thứ nhất
            y = std::stoi(numStr.substr(pos + 1)); // Lấy số thứ hai
            

        }
        else {
            return;
        }
    
        
        
        if (x != 0 && y != 0) {
            
            
            auto sprite1 = Sprite::create("res/X.png");
            auto sprite2 = Sprite::create("res/O.png");

            if (sprite1 == nullptr)
            {
                problemLoading("'X.png'");
                return;
            }
            else if (sprite2 == nullptr)
            {
                problemLoading("'O.png'");

                return;
            }
            else
            {

                if (value.substr(0, 1) == "1") {
                    auto label = Label::createWithTTF("Turn: ", "fonts/Marker Felt.ttf", 50);
                    label->setPosition(Vec2(800, 740));
                    this->addChild(label);
                    auto sprite = Sprite::create("res/O Win.png");
                    sprite->setPosition(920, 740);
                    sprite->setScale(0.2, 0.2);
                    this->addChild(sprite);
                }
                else {
                    auto label = Label::createWithTTF("Turn: ", "fonts/Marker Felt.ttf", 50);
                    label->setPosition(Vec2(800, 740));
                    this->addChild(label);
                    auto sprite = Sprite::create("res/X Win.png");
                    sprite->setPosition(920, 740);
                    sprite->setScale(0.2, 0.2);
                    this->addChild(sprite);
                }


                sprite1->setScale(0.1);
                sprite2->setScale(0.1);
                // gui du lieu toa do danh len server

                // x danh truoc
                if (value.substr(0, 1) == "1") {

                    matrix[x][y] = 1;
                    sprite1->setPosition(Vec2(x * 20, y * 20));
                    this->addChild(sprite1);

                }
                else if (value.substr(0, 1) == "0") {

                    sprite2->setPosition(Vec2(x * 20, y * 20));
                    this->addChild(sprite2);

                    matrix[x][y] = 2;
                }



                return;
            }
        }
    }
    
    // phan tich chuoi json
    // auto layout = Layout::create();
    // layout->setContentSize(Size(100, 20));
    // auto button = Button::create();
    // button->setPosition(layout->getContentSize() / 2);
    // button->setTitleText(value);
    // button->setTitleFontSize(16);
    // button->setTitleColor(Color3B::YELLOW);
    // layout->addChild(button);
    // listView->addChild(layout);

    //hien du lieu


};


Vec2 NetworkScene::roundV(Vec2 a) {
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

bool NetworkScene::onTouchBegan(Touch* touch, Event* unused_event) {

    if (!_client || !_isConnected) return 0;
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


        if (matrix[m][n] == 0 && isStart) {
            sprite1->setScale(0.1);
            sprite2->setScale(0.1);
            // gui du lieu toa do danh len server
            
            // X danh truoc
            if (you_are == 0 || you_are == 1) {
                CCLOG("I'm %i", you_are);
                std::string mess = std::to_string(you_are) + " " + std::to_string(m) + " " + std::to_string(n);
                
                std::string sendText = "[{\"value\":\"" + mess + "\"}]";
                CCLOG(sendText.c_str());
                if (_client && _isConnected) _client->emit("solo", sendText);
            }
            
    
            return true;
        }
        else {
            CCLOG("Not begin yet");
            return false;

        }
    }
    return true;
}


void NetworkScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    onClose(_client);
    _isConnected = false;

    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}