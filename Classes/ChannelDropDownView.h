//
//  ChannelDropDownView.h
//  youku
//
//  Created by 卢喜羲 on 15/9/1.
//
//

#ifndef __youku__ChannelDropDownView__
#define __youku__ChannelDropDownView__

#include "RootWindow.h"

class ChannelDropDownView : public CAView {
    
public:
    ChannelDropDownView();
    
    virtual ~ChannelDropDownView();
    
    static ChannelDropDownView* createWithFrame(const CADipRect& _rect);
    
    bool init(const CADipRect& _rect);
    
    void setDefaultChannel(int default_id); // 0是全部
    
private:
    void parseJson();
    
    void loadCollectionView();
    
private:
    
    CADipSize winSize;
    
    CSJson::Value m_value;
};

#endif /* defined(__youku__ChannelDropDownView__) */
