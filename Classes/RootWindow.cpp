

#include "RootWindow.h"
#include "FirstViewController.h"
#include "ClassifyViewController.h"
#include "SubscriptionViewController.h"
#include "MineViewController.h"
#include "IndexViewController.h"

static RootWindow* _window = NULL;
RootWindow* RootWindow::create()
{
    if (_window == NULL) {
        _window = new RootWindow();
        _window->init();
        _window->autorelease();
    }
    
    return _window;
}

RootWindow::RootWindow():m_pNavigationController(NULL),m_pTabBarController(NULL)
{
//    std::string json_file = CCFileUtils::sharedFileUtils()->fullPathForFilename("r/data/data.json");
//    jsonData = CCString::createWithContentsOfFile(json_file.c_str());
//    
//    CSJson::Reader reader;
//    if (reader.parse(jsonData->getCString(), data_json)) {
//        //OK
//    } else {
//        //初始化失败。
//    }
    //CCLog("%s",jsonData->getCString());
}

RootWindow::~RootWindow()
{

}

bool RootWindow::init()
{
    if (!CAWindow::init())
    {
        return false;
    }
    
    CAVector<CAViewController*> vec;
    
    IndexViewController* _viewController = new IndexViewController();
    _viewController->init();
    _viewController->autorelease();
    _viewController->setTabBarItem(CATabBarItem::create(UTF8("首页"), CAImage::create("r/navbar_icon_home_normal.png"),CAImage::create("r/navbar_icon_home_selected.png")));
    vec.pushBack(_viewController);
    
    ClassifyViewController *classify = ClassifyViewController::create();
    classify->setTabBarItem(CATabBarItem::create(UTF8("频道"), CAImage::create("r/navbar_icon_channel_normal.png"),CAImage::create("r/navbar_icon_channel_selected.png")));
    vec.pushBack(classify);
    
    SubscriptionViewController *subscription = SubscriptionViewController::create();
    subscription->setTabBarItem(CATabBarItem::create(UTF8("订阅"), CAImage::create("r/navbar_icon_subscribe_normal.png"),CAImage::create("r/navbar_icon_subscribe_selected.png")));
    vec.pushBack(subscription);
    
    MineViewController *mine = MineViewController::create();
    mine->setTabBarItem(CATabBarItem::create(UTF8("我的"), CAImage::create("r/navbar_icon_user_normal.png"),CAImage::create("r/navbar_icon_user_selected.png")));
    vec.pushBack(mine);
    
    CATabBarController *tabBar = new CATabBarController();
    tabBar->initWithViewControllers(vec);
    tabBar->autorelease();
    tabBar->setTabBarBackGroundImage(CAImage::create("r/d_banner.png"));
    tabBar->setTabBarTitleColorForNormal(CAColor_gray);
    tabBar->setTabBarSelectedBackGroundColor(CAColor_clear);
    tabBar->setScrollEnabled(false);
    
    CANavigationController *nav = new CANavigationController();
    nav->initWithRootViewController(tabBar);
    nav->autorelease();
    nav->setNavigationBarHidden(true, false);
    
    this->setRootViewController(nav);
    
    m_pTabBarController = tabBar;
    m_pNavigationController = nav;
    return true;
}
