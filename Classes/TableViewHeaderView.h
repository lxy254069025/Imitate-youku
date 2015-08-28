//
//  TableViewHeaderView.h
//  youku
//
//  Created by 卢喜羲 on 15/8/26.
//
//

#ifndef __youku__TableViewHeaderView__
#define __youku__TableViewHeaderView__

#include "RootWindow.h"

class TableViewHeaderView : public CAView {
    
public:
    TableViewHeaderView();
    
    virtual ~TableViewHeaderView();
    
    static TableViewHeaderView* createWithFrame(const CADipRect& _ret);
    
    virtual bool init(const CADipRect& _ret);
    
    void setModel(const CSJson::Value chan);
    
    void onClick(CAControl *btn , CCPoint point);
private:
    CADipSize winSize;
    
    CAView *m_btnView;
    
    CAButton *m_btn;
    
    CALabel *m_title;
    
    CAImageView *m_right;
    
    CAView *m_rightView;
    
    CAButton *m_rightBtn1;
    
    CAButton *m_rightBtn2;
    
    CAButton *m_rightBtn3;
    
    CAView *m_navigation;
};

#endif /* defined(__youku__TableViewHeaderView__) */
