//
//  ChannelListVideo.h
//  youku
//
//  Created by 卢喜羲 on 15/9/5.
//
//

#ifndef __youku__ChannelListVideo__
#define __youku__ChannelListVideo__

#include "RootWindow.h"

class ChannelListVideo
: public CAView
,public CACollectionViewDataSource
,public CACollectionViewDelegate
,public CAListViewDataSource
,public CAListViewDelegate
{
    
public:
    ChannelListVideo();
    
    virtual ~ChannelListVideo();
    
    static ChannelListVideo* createWithFrame(const CADipRect& _rect);
    
    void initListVideo(int channel_id);
    
    void initListView(CSJson::Value value);
    
    //----------------------------------------listView---------------------------------------
    virtual unsigned int numberOfIndex(CAListView *listView);
    
    virtual unsigned int listViewHeightForIndex(CAListView *listView, unsigned int index);
    
    virtual CAListViewCell* listViewCellAtIndex(CAListView *listView, const CCSize& cellSize, unsigned int index);
    
    
    
    
    //------------------------------------collectionView-------------------------------------
    virtual CACollectionViewCell* collectionCellAtIndex(CACollectionView *collectionView, const CCSize& cellSize, unsigned int section, unsigned int row, unsigned int item);
    
    //Necessary
    virtual unsigned int collectionViewHeightForRowAtIndexPath(CACollectionView* collectionView, unsigned int section, unsigned int row);
    
    //Necessary
    virtual unsigned int numberOfItemsInRowsInSection(CACollectionView *collectionView, unsigned int section, unsigned int row);
    
    //Necessary
    virtual unsigned int numberOfRowsInSection(CACollectionView *collectionView, unsigned int section);
    
    virtual void collectionViewDidSelectCellAtIndexPath(CACollectionView *collectionView, unsigned int section, unsigned int row, unsigned int item);
    
    virtual void collectionViewDidDeselectCellAtIndexPath(CACollectionView *collectionView, unsigned int section, unsigned int row, unsigned int item);
    
private:
    CADipSize viewSize;
    
    int m_channel_id;
    
    CSJson::Value m_value;
};

#endif /* defined(__youku__ChannelListVideo__) */
