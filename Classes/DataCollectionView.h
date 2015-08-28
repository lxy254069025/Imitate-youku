//
//  DataCollectionView.h
//  youku
//
//  Created by 卢喜羲 on 15/8/28.
//
//

#ifndef __youku__DataCollectionView__
#define __youku__DataCollectionView__

#include "RootWindow.h"

class DataCollectionView : public CAView, CACollectionViewDelegate,CACollectionViewDataSource,CAPageViewDelegate,CAScrollViewDelegate {
    
public:
    DataCollectionView();
    
    virtual ~DataCollectionView();
    
    static DataCollectionView* createWithFrame(const CADipRect& _ret);
    
    virtual bool init(const CADipRect& _ret);
    
    void setValue(CSJson::Value value);
    
    void initCollection();
    
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
    
    virtual CAView* collectionViewSectionViewForFooterInSection(CACollectionView *collectionView, const CCSize& viewSize, unsigned int section);
    
    virtual unsigned int collectionViewHeightForFooterInSection(CACollectionView *collectionView, unsigned int section);
    
    virtual void collectionViewDidSelectCellAtIndexPath(CACollectionView *collectionView, unsigned int section, unsigned int row, unsigned int item);
    
    virtual void collectionViewDidDeselectCellAtIndexPath(CACollectionView *collectionView, unsigned int section, unsigned int row, unsigned int item);
    
    virtual void scrollViewHeaderBeginRefreshing(CAScrollView* view);
    
    virtual void scrollViewFooterBeginRefreshing(CAScrollView* view);
    
    virtual void pageViewDidBeginTurning(CAPageView* pageView);
    
    virtual void pageViewDidEndTurning(CAPageView* pageView);
    
    virtual void pageViewDidSelectedPageAtIndex(CAPageView* pageView, unsigned int index, const CCPoint& point);
    
private:
    
    void loadPageView();
    
    void changePageViewIndex(float t);
    
    void pageClick(CAControl *btn,CCPoint point);
    
    void onRefresing(float t);
    
private:
    CADipSize winSize;
    
    CSJson::Value m_value;
    
    CACollectionView* m_collection;
    
    CAPageView* m_pageView;
    
    int m_pageViewIndex;
    
    CAView *m_header;
    
};

#endif /* defined(__youku__DataCollectionView__) */
