//
//  MineViewController.h
//  youku
//
//  Created by 卢喜羲 on 15/8/25.
//
//

#ifndef __youku__MineViewController__
#define __youku__MineViewController__

#include "RootWindow.h"

class MineViewController : public CAViewController,CAMediaDelegate {
    
public:
    MineViewController();
    
    virtual ~MineViewController();
    
    CREATE_FUNC(MineViewController);
    
    virtual void getSelectedImage(CAImage *image);
protected:
    void viewDidLoad();
    
    void viewDidUnload();
};

#endif /* defined(__youku__MineViewController__) */
