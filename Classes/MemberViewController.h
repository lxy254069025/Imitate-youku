//
//  MemberViewController.h
//  youku
//
//  Created by 卢喜羲 on 15/8/25.
//
//

#ifndef __youku__MemberViewController__
#define __youku__MemberViewController__

#include "RootWindow.h"

class MemberViewController: public CAViewController {
    
public:
    MemberViewController();
    
    virtual ~MemberViewController();
    
    CREATE_FUNC(MemberViewController);
    
protected:
    void viewDidLoad();
    
    void viewDidUnload();
    
private:
    void loadNavigationItem();
    
    void onBtnFanhui(CAControl *btn,CCPoint point);
    
private:
    CADipSize winSize;
};

#endif /* defined(__youku__MemberViewController__) */
