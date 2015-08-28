

#ifndef __HelloCpp__RootWindow__
#define __HelloCpp__RootWindow__

#include "HomeData.h"


class RootWindow: public CAWindow
{
    
public:

	static RootWindow* create();
    
	RootWindow();
    
	virtual ~RootWindow();
    
    virtual bool init();
    
    CC_SYNTHESIZE_READONLY(CANavigationController*, m_pNavigationController, NavigationController);
    
    CC_SYNTHESIZE_READONLY(CATabBarController*, m_pTabBarController, TabBarController);
    
private:
    CCString* jsonData;
};


#endif /* defined(__HelloCpp__ViewController__) */
