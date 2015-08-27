//
//  HomeTavleViewCell.h
//  youku
//
//  Created by 卢喜羲 on 15/8/26.
//
//

#ifndef __youku__HomeTavleViewCell__
#define __youku__HomeTavleViewCell__

#include "RootWindow.h"
#include "RecommendView.h"
class HomeTavleViewCell : public CATableViewCell {
    
public:
    HomeTavleViewCell();
    
    virtual ~HomeTavleViewCell();
    
    static HomeTavleViewCell* create(const std::string& reuseIdentifier,const CADipRect& _rect);
    
    bool init(const std::string& reuseIdentifier,const CADipRect& _rect);
    
    void createLike();
    
    void setLikeTarget();
    
    void createRecommend(const int listSize);
    
    void setLike();
    
    void setRecommend(const CSJson::Value& listData);
    
private:
    void onLikeClick(CAControl *btn,CCPoint point);
    
private:
    CADipSize cellSize;
    
    CAButton *likebtn;
    
    RecommendView *reco;
    
    CAView *likeView;
    
};

#endif /* defined(__youku__HomeTavleViewCell__) */
