//
//  IndexViewController.h
//  youku
//
//  Created by 卢喜羲 on 15/8/28.
//
//

#ifndef __youku__IndexViewController__
#define __youku__IndexViewController__

#include "RootWindow.h"

class IndexViewController : public CAViewController,CACollectionViewDataSource,CACollectionViewDelegate,CAPageViewDelegate {
    
public:
    IndexViewController();
    
    virtual ~IndexViewController();
    
    //搜索
    void onButtonSearch(CAControl *btn, CCPoint point);
    //会员中心
    void onButtonMenber(CAControl *btn, CCPoint point);
    //用户记录
    void onButtonRecord(CAControl *btn, CCPoint point);
    //上传
    void onButtonUpload(CAControl *btn, CCPoint point);
    //更多
    void onButtonMore(CAControl *btn, CCPoint point);
    
    void onButtonCache(CAControl *btn, CCPoint point);
    
    void onRefresing(float t);
    
protected:
    void viewDidLoad();
    
    void viewDidUnload();
    
    
private:
    void parseJson();
    
    void loadNavigationItem();
    
    void loadPageView();
    
    void loadCollectionView();
    
private:
    CADipSize winSize;
    
    CSJson::Value value;
};

#endif /* defined(__youku__IndexViewController__) */
