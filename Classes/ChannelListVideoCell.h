//
//  ChannelListVideoCell.h
//  youku
//
//  Created by 卢喜羲 on 15/9/6.
//
//

#ifndef __youku__ChannelListVideoCell__
#define __youku__ChannelListVideoCell__

#include "RootWindow.h"

class ChannelListVideoCell : public CAListViewCell {
public:
    ChannelListVideoCell();
    
    virtual ~ChannelListVideoCell();
    
    static ChannelListVideoCell* create(const std::string& ident,const CADipRect& _rect);
    
    void initCell();
    
    void setModel(CSJson::Value value);
    
    virtual void normalListViewCell();
    
    virtual void highlightedListViewCell();
    
    virtual void selectedListViewCell();
    
    virtual void disabledListViewCell();
    
private:
    CALabel* m_lable;
    
    CAView* m_line;
};

#endif /* defined(__youku__ChannelListVideoCell__) */
