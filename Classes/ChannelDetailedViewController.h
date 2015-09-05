//
//  ChannelDetailedViewController.h
//  youku
//
//  Created by 卢喜羲 on 15/9/1.
//
//

#ifndef __youku__ChannelDetailedViewController__
#define __youku__ChannelDetailedViewController__

#include "RootWindow.h"
#include "ChannelDropDownView.h"

class ChannelDetailedViewController : public CAViewController {
public:
    ChannelDetailedViewController();
    
    virtual ~ChannelDetailedViewController();
    
    static ChannelDetailedViewController* create(const int channel_id = 0,const int channel_s_id = 0);
    
    bool init(const int channel_id = 0,const int channel_s_id = 0);
    
    void viewDidLoad();
    
    void viewDidUnload();
    
    void onFanHui(CAControl *btn, CCPoint point);
    
    void onDropDwon(CAControl *btn,CCPoint point);
    
    void setDorDwonAttr(std::string title,int channel_id);
    
    std::string reustChannelTitle();
    
    void loadTitleList();
    
private:
    void loadNavigationIemt();
    
    void parseJson();
    
private:
    int m_channel_id;
    int m_channel_s_id;
    
    CADipSize winSize;
    
    CSJson::Value m_channel_value;
    
    CAView* m_dropDownView;
    
    CAButton* m_dropDownBtn;
    
    ChannelDropDownView* m_cDropDownView;
    
    int m_channelSize;
};

#endif /* defined(__youku__ChannelDetailedViewController__) */
