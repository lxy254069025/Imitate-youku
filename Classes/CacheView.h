//
//  CacheView.h
//  youku
//
//  Created by 卢喜羲 on 15/8/25.
//
//

#ifndef __youku__CacheView__
#define __youku__CacheView__

#include "RootWindow.h"

class CacheView : public CAView {
public:
    CacheView();
    
    virtual ~CacheView();
    
    static CacheView* create(CADipRect _ret);
    
    bool init(CADipRect _ret);
    
    void addCacheTarget(CAObject *target, SEL_CAControl selector, CAControlEvents event);
    
    virtual bool ccTouchBegan(CATouch *pTouch, CAEvent *pEvent);
    
    virtual void ccTouchMoved(CATouch *pTouch, CAEvent *pEvent);
    virtual void ccTouchEnded(CATouch *pTouch, CAEvent *pEvent);
    
private:
    CAButton *cache1;
    CAButton *cache2;
};

#endif /* defined(__youku__CacheView__) */
