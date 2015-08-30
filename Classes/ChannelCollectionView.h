//
//  ChannelCollectionView.h
//  youku
//
//  Created by 卢喜羲 on 15/8/31.
//
//

#ifndef __youku__ChannelCollectionView__
#define __youku__ChannelCollectionView__

#include "RootWindow.h"

class ChannelCollectionView :
public CAView
,public CACollectionViewDataSource
,public CACollectionViewDelegate
{
    
public:
    ChannelCollectionView();
    virtual ~ChannelCollectionView();
    
    static ChannelCollectionView* createWithFrame(const CADipRect& _ret);
    
    virtual bool init(const CADipRect& _ret);
    
    //Necessary
    virtual CACollectionViewCell* collectionCellAtIndex(CACollectionView *collectionView, const CCSize& cellSize, unsigned int section, unsigned int row, unsigned int item);
    
    //Necessary
    virtual unsigned int collectionViewHeightForRowAtIndexPath(CACollectionView* collectionView, unsigned int section, unsigned int row);
    
    //Necessary
    virtual unsigned int numberOfItemsInRowsInSection(CACollectionView *collectionView, unsigned int section, unsigned int row);
    
    //Necessary
    virtual unsigned int numberOfRowsInSection(CACollectionView *collectionView, unsigned int section);
    
    virtual unsigned int numberOfSections(CACollectionView *collectionView);
    
    virtual CAView* collectionViewSectionViewForHeaderInSection(CACollectionView *collectionView, const CCSize& viewSize, unsigned int section);
    
    virtual unsigned int collectionViewHeightForHeaderInSection(CACollectionView *collectionView, unsigned int section);
    
    virtual void collectionViewDidSelectCellAtIndexPath(CACollectionView *collectionView, unsigned int section, unsigned int row, unsigned int item);
    
    virtual void collectionViewDidDeselectCellAtIndexPath(CACollectionView *collectionView, unsigned int section, unsigned int row, unsigned int item);
    
private:
    
    void parseJson();
    
    void loadCollectionView();
    
private:
    CADipSize winSize;
    
    CACollectionView* m_collection;
    
    CSJson::Value m_value;
    
};

#endif /* defined(__youku__ChannelCollectionView__) */
