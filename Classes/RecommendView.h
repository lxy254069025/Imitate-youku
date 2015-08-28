//
//  RecommendView.h
//  youku
//
//  Created by 卢喜羲 on 15/8/26.
//
//

#ifndef __youku__RecommendView__
#define __youku__RecommendView__

#include "RootWindow.h"

class RecommendView : public CAView,CACollectionViewDataSource,CACollectionViewDelegate,CAScrollViewDelegate {
    
public:
    RecommendView();
    
    virtual ~RecommendView();
    
    static RecommendView* create(const CADipRect& _ret);
    
    virtual bool init(const CADipRect& _ret);
    
    //Necessary
    virtual CACollectionViewCell* collectionCellAtIndex(CACollectionView *collectionView, const CCSize& cellSize, unsigned int section, unsigned int row, unsigned int item);
    
    //Necessary
    virtual unsigned int collectionViewHeightForRowAtIndexPath(CACollectionView* collectionView, unsigned int section, unsigned int row);
    
    //Necessary
    virtual unsigned int numberOfItemsInRowsInSection(CACollectionView *collectionView, unsigned int section, unsigned int row);
    
    //Necessary
    virtual unsigned int numberOfRowsInSection(CACollectionView *collectionView, unsigned int section);
    
    virtual void collectionViewDidSelectCellAtIndexPath(CACollectionView *collectionView, unsigned int section, unsigned int row, unsigned int item);
    
    virtual void collectionViewDidDeselectCellAtIndexPath(CACollectionView *collectionView, unsigned int section, unsigned int row, unsigned int item);
    
    void setReload(const CSJson::Value& listData);
    
    void setListData(const CSJson::Value& listData);
    
    void setlistSize(const int listSize);
    
    void initCollection();
    
private:
    
    
private:
    CADipSize winSize;
    
    std::string reuseIdentifier;
    
    int m_listSize;
    
    CACollectionView* m_collection;
    
    CSJson::Value m_listData;
    
};

#endif /* defined(__youku__RecommendView__) */
