//
//  FirstCollectionHeaderView.h
//  youku
//
//  Created by 卢喜羲 on 15/8/29.
//
//

#ifndef __youku__FirstCollectionHeaderView__
#define __youku__FirstCollectionHeaderView__

#include "RootWindow.h"

class FirstCollectionHeaderView : public CAView {
    
public:
    FirstCollectionHeaderView();
    
    virtual ~FirstCollectionHeaderView();
    
    static FirstCollectionHeaderView* createWithFrame(const CADipRect& _ret);
    
    bool init(const CADipRect& _ret);
    
private:
    CADipSize winSize;
    
private:
    void onTopHeaderClick(CAControl *btn,CCPoint point);
};

#endif /* defined(__youku__FirstCollectionHeaderView__) */
