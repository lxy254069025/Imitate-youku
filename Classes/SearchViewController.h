//
//  SearchViewController.h
//  youku
//
//  Created by 卢喜羲 on 15/9/2.
//
//

#ifndef __youku__SearchViewController__
#define __youku__SearchViewController__

#include "RootWindow.h"

class SearchViewController : public CAViewController {
    
public:
    SearchViewController();
    
    virtual ~SearchViewController();
    
    CREATE_FUNC(SearchViewController);
    
    void viewDidLoad();
    
    void viewDidUnload();
    
    void onBtn(CAControl *btn,CCPoint point);
};

#endif /* defined(__youku__SearchViewController__) */
