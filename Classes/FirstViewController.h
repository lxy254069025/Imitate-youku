
#ifndef __HelloCpp__ViewController__
#define __HelloCpp__ViewController__

#include "RootWindow.h"

class FirstViewController: public CAViewController,CATableViewDataSource,CATableViewDelegate,CAScrollViewDelegate,CAPageViewDelegate,CACollectionViewDataSource,CACollectionViewDelegate
{
    
public:

	FirstViewController();
    
	virtual ~FirstViewController();
    
    virtual void tableViewDidSelectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);
    
    virtual void tableViewDidDeselectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);
    
    //Necessary
    virtual CATableViewCell* tableCellAtIndex(CATableView* table, const CCSize& cellSize, unsigned int section, unsigned int row);
    
    //Necessary
    virtual unsigned int tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);
    
    //Necessary
    virtual unsigned int numberOfRowsInSection(CATableView* table, unsigned int section);
    
    virtual unsigned int numberOfSections(CATableView* table);
    
    virtual CAView* tableViewSectionViewForHeaderInSection(CATableView* table, const CCSize& viewSize, unsigned int section);
    
    virtual unsigned int tableViewHeightForHeaderInSection(CATableView* table, unsigned int section);
    
    virtual CAView* tableViewSectionViewForFooterInSection(CATableView* table, const CCSize& viewSize, unsigned int section);
    
    virtual unsigned int tableViewHeightForFooterInSection(CATableView* table, unsigned int section);
    
    virtual void tableViewWillDisplayCellAtIndex(CATableView* table, CATableViewCell* cell, unsigned int section, unsigned int row);
    
    virtual void scrollViewHeaderBeginRefreshing(CAScrollView* view);
    
    virtual void scrollViewFooterBeginRefreshing(CAScrollView* view);
    
    virtual void pageViewDidBeginTurning(CAPageView* pageView);
    
    virtual void pageViewDidEndTurning(CAPageView* pageView);
    
    virtual void pageViewDidSelectedPageAtIndex(CAPageView* pageView, unsigned int index, const CCPoint& point);
    
    
protected:
    
    void viewDidLoad();
    
    void viewDidUnload();
    
protected:
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
    
    void changePageViewIndex(float t);
    
    void pageClick(CAControl *btn,CCPoint point);
    
    void onRefresing(float t);
    
private:
    
    void loadNavigationItem();
    
    void loadTableView();
    
    void initPageView();
    
    void parseJson();
    
private:
    CADipSize winSize;
    
    CATableView* m_tableView;
    
    CAPageView* m_pageView;
    
    int m_pageViewIndex;
    
    CAView *m_header;
    
    CSJson::Value value;
    
};


#endif /* defined(__HelloCpp__ViewController__) */
