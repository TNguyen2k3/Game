// NetworkSceneManager.h
#ifndef __NETWORK_MANAGER_H__
#define __NETWORK_MANAGER_H__

#include "cocos2d.h"
#include "ui/cocosGUI.h"

#include "network/SocketIO.h"

using namespace cocos2d::network;
using namespace cocos2d::ui;
using namespace cocos2d;


class NetworkScene : public cocos2d::Layer, public SocketIO::SIODelegate
{
public:
    
    static cocos2d::Scene* createScene();
   
    virtual bool init();
    int you_are = -1;
    /*  0: O
        1: X
    */
    bool isStart = false;
    int a = 0;
    bool win = false;
    int who_win = 0;
    int getWinner() const;
    int** create_matrix(int **matrix, int a, int b);
    Vec2 roundV(Vec2 a);
    int** matrix = nullptr;
    bool check_Win_Con(int** matrix, int a, int b);
    bool check_full(int** matrix, int a, int b);
    void clean_screen(int a, int b);
    void prohibit(int a, int b);
    // onTouchBegan
    bool onTouchBegan(Touch* touch, Event* unused_event);
    void menuCloseCallback(cocos2d::Ref* pSender);
    // a selector callback
    // void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually

    // socket.io even\vent listener
    void onReceiveEvent(SIOClient* client, const std::string& data);
    // SIODelegate
    virtual void onConnect(SIOClient* client);
    virtual void onMessage(SIOClient* client, const std::string& data);
    virtual void onClose(SIOClient* client);
    virtual void onError(SIOClient* client, const std::string& data);
    
    CREATE_FUNC(NetworkScene);
    ~NetworkScene();
protected:
private:
    int index;
    SIOClient* _client = NULL;
    
    ListView* listView;
    bool _isConnected = false;
};
#endif // __NETWORK_MANAGER_H__