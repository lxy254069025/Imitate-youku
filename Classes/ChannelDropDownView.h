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

class ChannelDropDownViewCell : public CACollectionViewCell {
public:
    ChannelDropDownViewCell();
    virtual ~ChannelDropDownViewCell();
    
    static ChannelDropDownViewCell* create(const std::string& identifier, const CADipRect& _rect = CADipRectZero);
    
    bool init(const std::string& identifier, const CADipRect& _rect = CADipRectZero);
    
    virtual void highlightedCollectionViewCell();
    
    virtual void selectedCollectionViewCell();
    
    virtual void normalCollectionViewCell();
//
    virtual void disabledTableViewCell();
    
    void setModel(CSJson::Value value,int default_id);
    
private:
    CALabel* m_title;
    
    CADipSize m_winSize;
};










class ChannelDropDownView : public CAView,CACollectionViewDataSource,CACollectionViewDelegate {
    
public:
    ChannelDropDownView();
    
    virtual ~ChannelDropDownView();
    
    static ChannelDropDownView* createWithFrame(const CADipRect& _rect);
    
    bool init(const CADipRect& _rect);
    
    void setDefaultChannel(int default_id); // 0是全部
    
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
    
    void setDataSize(int __size) {
        this->m__size = __size;
    }
    
    void initCollectionView() {
        this->loadCollectionView();
    }
    
    void setValue(const CSJson::Value& value) {
        this->m_value = value;
    }
    
    void setCallBack(CAObject *target, Channel_Control selector);
    
private:
    void parseJson();
    
    void loadCollectionView();
    
private:
    
    CADipSize winSize;
    
    CSJson::Value m_value;
    
    int m__size;
    
    int m_DefaultId;
    
    CAObject *m_target;
    
    Channel_Control m_selector;
};

#endif /* defined(__youku__ChannelDropDownView__) */
