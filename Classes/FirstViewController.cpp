
#include "FirstViewController.h"
#include "CacheView.h"
#include "MemberViewController.h"
#include "HomeTavleViewCell.h"
#include "VideoPlayViewController.h"
#include "TableViewHeaderView.h"
#include "RecommendView.h"

#define MORESELECTED 100000
#define PAGELINKTAG 1000

FirstViewController::FirstViewController():m_pageViewIndex(0),m_tableView(NULL)
{

}

FirstViewController::~FirstViewController()
{

}

void FirstViewController::viewDidLoad()
{
    winSize = this->getView()->getBounds().size;
    this->getView()->setColor(CAColor_gray);
    
    this->parseJson();
    
    this->loadNavigationItem();
    
    this->initPageView();
    
    this->loadTableView();
}

void FirstViewController::parseJson() {
        std::string json_file = CCFileUtils::sharedFileUtils()->fullPathForFilename("r/data/HomeData.json");
        CCString *jsonData = CCString::createWithContentsOfFile(json_file.c_str());
    
        CSJson::Reader reader;
        if (reader.parse(jsonData->getCString(), value)) {
            //OK
        } else {
            //初始化失败。
        }
        CCLog("%s",jsonData->getCString());
}


void FirstViewController::viewDidUnload()
{
    
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

void FirstViewController::loadNavigationItem() {
    CAView *view = CAView::createWithFrame(CADipRect(0,0,winSize.width,130));
    view->setColor(CAColor_white);
    this->getView()->addSubview(view);
    
    CAImageView *logo = CAImageView::createWithFrame(CADipRect(30,60,76,50));
    logo->setImage(CAImage::create("r/icon_youku.png"));
    view->addSubview(logo);
    
    CAButton *search = CAButton::create(CAButtonTypeCustom);
    search->setImageForState(CAControlStateNormal,CAImage::create("r/btn_search.png"));
    search->setFrame(CADipRect(winSize.width / 2 - 70 * 1.6,55,80,70));
    search->setImageForState(CAControlStateHighlighted, CAImage::create("r/btn_search_selected.png"));
    search->addTarget(this, CAControl_selector(FirstViewController::onButtonSearch), CAControlEventTouchUpInSide);
    view->addSubview(search);
    
    CAButton *member = CAButton::create(CAButtonTypeCustom);
    member->setImageForState(CAControlStateNormal, CAImage::create("r/btn_vip.png"));
    member->setImageForState(CAControlStateHighlighted, CAImage::create("r/btn_vip_selected.png"));
    member->setFrame(CADipRect(winSize.width / 2 - 10 ,55,80,70));
    member->addTarget(this, CAControl_selector(FirstViewController::onButtonMenber), CAControlEventTouchUpInSide);
    view->addSubview(member);
    
    CAButton *record = CAButton::create(CAButtonTypeCustom);
    record->setImageForState(CAControlStateNormal, CAImage::create("r/myyouku_history.png"));
    record->setImageForState(CAControlStateHighlighted, CAImage::create("r/btn_history_selected.png"));
    record->setFrame(CADipRect(winSize.width / 2 + 92,55,80,70));
    record->addTarget(this, CAControl_selector(FirstViewController::onButtonRecord), CAControlEventTouchUpInSide);
    view->addSubview(record);
    
    CAButton *upload = CAButton::create(CAButtonTypeCustom);
    upload->setImageForState(CAControlStateNormal, CAImage::create("r/btn_upload.png"));
    upload->setImageForState(CAControlStateHighlighted, CAImage::create("r/btn_upload_selected.png"));
    upload->setFrame(CADipRect(winSize.width / 2 + 194,55,80,70));
    upload->addTarget(this, CAControl_selector(FirstViewController::onButtonUpload), CAControlEventTouchUpInSide);
    view->addSubview(upload);
    
    CAButton *more = CAButton::create(CAButtonTypeCustom);
    more->setImageForState(CAControlStateNormal, CAImage::create("r/btn_more.png"));
    more->setImageForState(CAControlStateHighlighted, CAImage::create("r/btn_more_selected.png"));
    more->setFrame(CADipRect(winSize.width / 2 + 296,55,80,70));
    more->addTarget(this, CAControl_selector(FirstViewController::onButtonMore), CAControlEventTouchUpInSide);
    view->addSubview(more);
    
    
}

void FirstViewController::initPageView() {
    m_header = CAView::createWithFrame(CADipRect(winSize.width / 2,winSize.height / 2,winSize.width,350),CAColor_clear);
    m_pageView = CAPageView::createWithFrame(CADipRect(0,0,winSize.width,350), CAPageViewDirectionHorizontal);
    m_pageView->setCurrPage(0, true);
    m_pageView->setPageViewDelegate(this);
    m_pageView->setSpacing(0);
    
    CADipSize headerSize = m_header->getBounds().size;
    
    CSJson::Value pageValue = value["header"];
    
    CAVector<CAView*> vec;
    for (int i = 0; i < pageValue.size(); i++) {
        std::string path = pageValue[i]["img"].asString();
        std::string js_title = pageValue[i]["title"].asString();
        int js_id = pageValue[i]["id"].asInt();
        
        CAImageView *image = CAImageView::createWithImage(CAImage::create(path));
        
        CALabel *title = CALabel::createWithFrame(CADipRect(20,winSize.height / 4.5,winSize.width,50));
        title->setText(js_title);
        title->setFontSize(_px(28));
        title->setColor(CAColor_white);
        image->addSubview(title);
        
        CAButton *btn = CAButton::create(CAButtonTypeCustom);
        btn->setFrame(CADipRect(0,0,headerSize.width,headerSize.height));
        btn->setBackGroundViewForState(CAControlStateAll, image);
        btn->setTag(js_id);
        btn->addTarget(this, CAControl_selector(FirstViewController::pageClick), CAControlEventTouchUpInSide);
        vec.pushBack(btn);
    }
    m_pageView->setViews(vec);
    m_header->addSubview(m_pageView);
    CAScheduler::schedule(schedule_selector(FirstViewController::changePageViewIndex), this, 3, false);
    
    for (int j = 0; j < vec.size(); j++) {
        CAView *pageLink = CAView::createWithFrame(CADipRect(20 + 118 * j,headerSize.height / 1.35,118,1),CAColor_gray);
        pageLink->setZOrder(100);
        if (j == 0) {
            pageLink->setFrame(CADipRect(20 + 118 * j,headerSize.height / 1.35 - 2,118,3));
            pageLink->setColor(CAColor_white);
        }
        pageLink->setTag(PAGELINKTAG+j);
        m_header->addSubview(pageLink);
    }
    
}

void FirstViewController::pageClick(CAControl *btn,CCPoint point) {
    int v_id = btn->getTag();
    CCLog("page 点中%d",v_id);
    RootWindow::create()->getNavigationController()->pushViewController(VideoPlayViewController::create(v_id), true);
}

void FirstViewController::loadTableView() {
    m_tableView = CATableView::createWithFrame(CADipRect(0,131,winSize.width,winSize.height-130.5));
    m_tableView->setAllowsSelection(false);
    m_tableView->setTableViewDataSource(this);
    m_tableView->setTableViewDelegate(this);
    m_tableView->setScrollViewDelegate(this);
    m_tableView->setTableHeaderHeight(350);
    m_tableView->setTableHeaderView(m_header);
    m_tableView->setSeparatorColor(ccc4(216,216,216, 255));
    m_tableView->setSeparatorViewHeight(15);
    
    CAPullToRefreshView *refreshDiscount1 = CAPullToRefreshView::create(CAPullToRefreshView::CAPullToRefreshTypeHeader);
    refreshDiscount1->setLabelColor(CAColor_black);
    refreshDiscount1->setPullToRefreshText(UTF8("下拉可以刷新"));
    refreshDiscount1->setLabelColor(CAColor_gray);
    refreshDiscount1->setRefreshingText(UTF8("正在刷新..."));
    m_tableView->setHeaderRefreshView(refreshDiscount1);
    
    this->getView()->addSubview(m_tableView);
}

//搜索
void FirstViewController::onButtonSearch(CAControl *btn, CCPoint point) {
    CCLog("搜索");
}
//会员中心
void FirstViewController::onButtonMenber(CAControl *btn, CCPoint point) {
    this->getNavigationController()->presentModalViewController(MemberViewController::create(), true);
}
//用户记录
void FirstViewController::onButtonRecord(CAControl *btn, CCPoint point) {
    
}
//上传
void FirstViewController::onButtonUpload(CAControl *btn, CCPoint point) {
    
}
//更多
void FirstViewController::onButtonMore(CAControl *btn, CCPoint point) {
    CacheView *more_selected = (CacheView*)this->getView()->getSubviewByTag(MORESELECTED);
    if (more_selected) {
        if (more_selected->isVisible()) {
            more_selected->setVisible(false);
        } else {
            more_selected->setVisible(true);
        }
        
    } else {
        more_selected = CacheView::create(CADipRect(0,130.5,winSize.width,winSize.height-130.5));
        more_selected->setTag(MORESELECTED);
        more_selected->addCacheTarget(this, CAControl_selector(FirstViewController::onButtonCache), CAControlEventTouchUpInSide);
        this->getView()->addSubview(more_selected);
    }
    
}

void FirstViewController::onButtonCache(CAControl *btn, CCPoint point) {
    CCLog("缓存触发");
}


void FirstViewController::tableViewDidSelectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row) {
    
}

void FirstViewController::tableViewDidDeselectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row) {
    
}

//Necessary
CATableViewCell* FirstViewController::tableCellAtIndex(CATableView* table, const CCSize& cellSize, unsigned int section, unsigned int row) {
    char identifier[20];
    sprintf(identifier, "home%d",section);
    
    CSJson::Value data = value["data"];
    CSJson::Value currList = data[section]["list"];
    int currListSize = currList.size();
    switch (section) {
        case 0:
        {
            HomeTavleViewCell *cell = (HomeTavleViewCell*)table->dequeueReusableCellWithIdentifier(identifier);
            if (cell == NULL) {
                cell = HomeTavleViewCell::create(identifier,CADipRect(0,0,cellSize.width,cellSize.height));
                cell->createLike();
            }
            cell->setLike();
            return cell;
        }
            
//        case 1:
//        {
//            CATableViewCell *cell = (CATableViewCell*)table->dequeueReusableCellWithIdentifier(identifier);
//            if (cell == NULL) {
//                cell = CATableViewCell::create(identifier);//,CADipRect(0,0,cellSize.width,cellSize.height)
//                
//                RecommendView *recommend = RecommendView::create(CADipRect(0,0,cellSize.width,cellSize.height));
//                recommend->setlistSize(currListSize);
//                recommend->setListData(currList);
//                recommend->initCollection();
//                recommend->setTag(1001);
//                cell->addSubview(recommend);
//            }
//            RecommendView *recommend = (RecommendView*)cell->getSubviewByTag(1001);
//            recommend->setReload(currList);
//            
//            return cell;
//        }
            
        default:
        {
            CATableViewCell *cell = (CATableViewCell*)table->dequeueReusableCellWithIdentifier(identifier);
            if (cell == NULL) {
                cell = CATableViewCell::create(identifier);//,CADipRect(0,0,cellSize.width,cellSize.height)
                
                RecommendView *recommend = RecommendView::create(CADipRect(0,0,cellSize.width,cellSize.height));
                recommend->setlistSize(currListSize);
                recommend->setListData(currList);
                recommend->initCollection();
                recommend->setTag(1001);
                cell->addSubview(recommend);
            }
            RecommendView *recommend = (RecommendView*)cell->getSubviewByTag(1001);
            recommend->setReload(currList);
            
            return cell;
        }
    }
}

//Necessary
unsigned int FirstViewController::tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row) {
    
    unsigned int pix;
    
    CSJson::Value data = value["data"];
    CSJson::Value currList = data[section]["list"];
    int currListSize = currList.size();
    
    int s = currListSize / 2;
    if (currListSize % 2 != 0) {
        s -= 1;
    }
    CCLog("ssss %d",s);
    switch (section) {
        case 0:
            pix = _px(100);
            break;
            
        case 1:
            pix = _px(311 * s);
            break;
            
        default:
            pix = _px(311 * s);
            break;
    }
    return pix;
}

//Necessary
unsigned int FirstViewController::numberOfRowsInSection(CATableView* table, unsigned int section) {
    return 1;
}

unsigned int FirstViewController::numberOfSections(CATableView* table) {
    CCLog("dta size %d",value["data"].size());
    return value["data"].size();
}

CAView* FirstViewController::tableViewSectionViewForHeaderInSection(CATableView* table, const CCSize& viewSize, unsigned int section) {
    TableViewHeaderView *view = NULL;
    
    CSJson::Value data = value["data"];
    CSJson::Value currHeader = data[section]["header"];
    
    switch (section) {
        case 0:
        case 1:
            break;
            
        default:
            view = TableViewHeaderView::createWithFrame(CADipRect(0,0,viewSize.width,viewSize.height));
            view->setModel(currHeader);
            break;
    }
    
    return view;
}

unsigned int FirstViewController::tableViewHeightForHeaderInSection(CATableView* table, unsigned int section) {
    unsigned int pix = 0;
    
    switch (section) {
        case 0:
        case 1:
            break;
            
//        case 2:
//            pix = _px(100);
//            break;
            
        default:
            pix = _px(100);
            break;
    }
    return pix;
}

CAView* FirstViewController::tableViewSectionViewForFooterInSection(CATableView* table, const CCSize& viewSize, unsigned int section) {
    
    return NULL;
}

unsigned int FirstViewController::tableViewHeightForFooterInSection(CATableView* table, unsigned int section) {
    unsigned int pix = 0;
    
    
    return pix;
}


void FirstViewController::tableViewWillDisplayCellAtIndex(CATableView* table, CATableViewCell* cell, unsigned int section, unsigned int row) {
    //CCLog("sdfeeeeee%d",row);
}

void FirstViewController::scrollViewHeaderBeginRefreshing(CAScrollView* view) {
    CAScheduler::schedule(schedule_selector(FirstViewController::onRefresing), this, 2, false);
}

void FirstViewController::scrollViewFooterBeginRefreshing(CAScrollView* view) {
    
}

void FirstViewController::onRefresing(float t) {
    m_tableView->reloadData();
}

void FirstViewController::pageViewDidBeginTurning(CAPageView* pageView) {
    CCLog("点点点1");
}

void FirstViewController::pageViewDidEndTurning(CAPageView* pageView) {
    if (pageView->getCurrPage() == m_pageViewIndex) {
        return;
    }
    
    int curr = pageView->getCurrPage();
    CADipSize headerSize = m_header->getBounds().size;
    
    CAView *link1 = (CAView*)m_header->getSubviewByTag(PAGELINKTAG+m_pageViewIndex);
    link1->setFrame(CADipRect(20 + 118 * m_pageViewIndex,headerSize.height / 1.35,118,1));
    link1->setColor(CAColor_gray);
    
    m_pageViewIndex = curr;
    
    CAView *link2 = (CAView*)m_header->getSubviewByTag(PAGELINKTAG+curr);
    link2->setFrame(CADipRect(20 + 118 * curr,headerSize.height / 1.35 - 2,118,3));
    link2->setColor(CAColor_white);
}

void FirstViewController::pageViewDidSelectedPageAtIndex(CAPageView* pageView, unsigned int index, const CCPoint& point) {
    CCLog("点点点2");
}

void FirstViewController::changePageViewIndex(float t) {
    int num = m_pageView->getPageCount();
    int curr = m_pageView->getCurrPage();
    if (curr < num - 1) {
        m_pageView->setCurrPage(curr+1, true);
    } else {
        m_pageView->setCurrPage(0, true);
    }
    
    curr = m_pageView->getCurrPage();
    
    if (curr == m_pageViewIndex) {
        return;
    }
    
    CADipSize headerSize = m_header->getBounds().size;
    
    CAView *link1 = (CAView*)m_header->getSubviewByTag(PAGELINKTAG+m_pageViewIndex);
    link1->setFrame(CADipRect(20 + 118 * m_pageViewIndex,headerSize.height / 1.35,118,1));
    link1->setColor(CAColor_gray);
    
    m_pageViewIndex = curr;
    
    CAView *link2 = (CAView*)m_header->getSubviewByTag(PAGELINKTAG+curr);
    link2->setFrame(CADipRect(20 + 118 * curr,headerSize.height / 1.35 - 2,118,3));
    link2->setColor(CAColor_white);

}












