//
//  SubscriptionViewController.h
//  youku
//
//  Created by 卢喜羲 on 15/8/25.
//
//

#ifndef __youku__SubscriptionViewController__
#define __youku__SubscriptionViewController__

#include "RootWindow.h"

class SubscriptionViewController : public CAViewController {
    
public:
    SubscriptionViewController();
    
    virtual ~SubscriptionViewController();
    
    CREATE_FUNC(SubscriptionViewController);
    
protected:
    
    void viewDidLoad();
    
    void viewDidUnload();
    
    void viewDidAppear();
    
    void viewDidDisappear();
    
    void loadNavigationItem();
    
    void loadWeb();
    
private:
    CADipSize winSize;
    
    CAWebView *m_web;
};

#endif /* defined(__youku__SubscriptionViewController__) */
