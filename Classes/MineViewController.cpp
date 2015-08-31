//
//  MineViewController.cpp
//  youku
//
//  Created by 卢喜羲 on 15/8/25.
//
//

#include "MineViewController.h"


MineTableViewCell::MineTableViewCell() {
    
}

MineTableViewCell::~MineTableViewCell() {
    
}

MineTableViewCell* MineTableViewCell::create(const std::string& reuseIdentifier,const CADipRect& _rect) {
    MineTableViewCell *tableViewCell = new MineTableViewCell();
    if (tableViewCell && tableViewCell->initWithReuseIdentifier(reuseIdentifier)) {
        tableViewCell->setFrame(_rect);
        tableViewCell->autorelease();
        return tableViewCell;
    }
    delete tableViewCell;
    tableViewCell = NULL;
    return NULL;
}

void MineTableViewCell::initTableViewCell() {
    CADipSize viewSize = this->getBounds().size;
    
    CALabel *title = CALabel::createWithCenter(CADipRect(viewSize.width / 2 + 100,viewSize.height / 2,viewSize.width,40));
    title->setTag(99);
    //title->setText(UTF8("会员中心"));
    title->setFontSize(_px(30));
    title->setTextAlignment(CATextAlignmentLeft);
    title->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    //title->setColor(CAColor_gray);
    this->addSubview(title);
    
    CAScale9ImageView *leftImg = CAScale9ImageView::createWithCenter(CADipRect(50,viewSize.height / 2,50,50));
    leftImg->setTag(100);
    //leftImg->setImage(CAImage::create("r/btn_vip.png"));
    
    this->addSubview(leftImg);
    
    CAScale9ImageView *rightImg = CAScale9ImageView::createWithCenter(CADipRect(viewSize.width - 50,viewSize.height / 2,50,50));
    rightImg->setImage(CAImage::create("source_material/cell_btn_right.png"));
    rightImg->setTag(101);
    
    this->addSubview(rightImg);
}


void MineTableViewCell::highlightedTableViewCell() {
    this->setBackgroundView(CAView::createWithColor(ccc4(0, 0, 0, 64)));
}

void MineTableViewCell::selectedTableViewCell() {
    this->setBackgroundView(CAView::createWithColor(ccc4(0, 0, 0, 64)));
}



MineViewController::MineViewController():m_header(NULL),m_tableView(NULL) {
    
}

MineViewController::~MineViewController() {
    
}

void MineViewController::viewDidLoad() {
    //CADevice::openCamera(this);
    this->getView()->setDisplayRange(true);
    //this->getView()->setColor(ccc4(47, 179, 255, 255));
    
    winSize = this->getView()->getBounds().size;
    
    m_backView = CAView::createWithFrame(CADipRect(0,0,winSize.width,winSize.height));
    
    CAView *shang = CAView::createWithFrame(CADipRect(0,0,winSize.width,winSize.height / 2),ccc4(47, 179, 255, 255));
    m_backView->addSubview(shang);
    
    CAView *xia = CAView::createWithFrame(CADipRect(0,winSize.height / 2,winSize.width,winSize.height / 2),ccc4(216,216,216, 255));
    m_backView->addSubview(xia);
    
    this->getView()->addSubview(m_backView);
    
    this->loadHeader();
    
    this->loadTableView();
}


void MineViewController::viewDidUnload() {
    
}

void MineViewController::loadHeader() {
    m_header = CAView::createWithFrame(CADipRect(0,0,winSize.width,230));
    m_header->setColor(ccc4(47, 179, 255, 255));
    
    CADipSize headerSize = m_header->getBounds().size;
    CAImageView *headerImg = CAImageView::createWithCenter(CADipRect(30 + 140 / 2.f,headerSize.height / 2,140,140));
    headerImg->setImage(CAImage::create("r/header.png"));
    m_header->addSubview(headerImg);
    
    CALabel *nickname = CALabel::createWithCenter(CADipRect(headerSize.width - (headerSize.width - 170) / 2 + 20 , headerSize.height / 2 - 25,headerSize.width - 170,50));
    nickname->setText("更快更短更小");
    nickname->setTextAlignment(CATextAlignmentLeft);
    nickname->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    nickname->setColor(CAColor_white);
    nickname->setFontSize(_px(38));
    m_header->addSubview(nickname);
    
    CAImageView *imageMember = CAImageView::createWithFrame(CADipRect(30 + 140 - 52 / 2.0f - 3,headerSize.height / 2 + 18,52,52));
    imageMember->setImage(CAImage::create("r/more_member_icon.png"));
    m_header->addSubview(imageMember);
    
}

void MineViewController::loadTableView() {
    m_tableView = CATableView::createWithFrame(CADipRect(0,40,winSize.width,winSize.height - 40));
    m_tableView->setTableHeaderHeight(_px(230));
    m_tableView->setTableHeaderView(m_header);
    m_tableView->setTableViewDataSource(this);
    m_tableView->setTableViewDelegate(this);
    m_tableView->setAllowsSelection(true);
    m_tableView->setBackGroundColor(CAColor_clear);
    m_backView->addSubview(m_tableView);
    m_tableView->setSeparatorColor(ccc4(240,240,240,255));
    m_tableView->setScrollEnabled(true);
    m_tableView->setHorizontalScrollEnabled(false);
    m_tableView->setAllowsSelection(false);
}

void MineViewController::getSelectedImage(CAImage *image) {
    CAImageView *imgView = CAImageView::createWithFrame(this->getView()->getBounds());
    imgView->setImage(image);
    this->getView()->addSubview(imgView);
}

//Necessary
CATableViewCell* MineViewController::tableCellAtIndex(CATableView* table, const CCSize& cellSize, unsigned int section, unsigned int row) {
    MineTableViewCell *cell = (MineTableViewCell*)table->dequeueReusableCellWithIdentifier("mine");
    if (cell == NULL) {
        cell = MineTableViewCell::create("mine",CADipRect(0,0,cellSize.width,cellSize.height));
        cell->initTableViewCell();
    }
    
    CALabel *title = (CALabel*)cell->getSubviewByTag(99);
    CAScale9ImageView *leftImg = (CAScale9ImageView*)cell->getSubviewByTag(100);
    switch (section) {
        case 0:
            title->setText("会员中心");
            leftImg->setImage(CAImage::create("r/btn_vip.png"));
            break;
            
        case 1:
            if (row == 0) {
                title->setText("历史记录");
                leftImg->setImage(CAImage::create("r/myyouku_history.png"));
            };
            
            if (row == 1) {
                title->setText("离线缓存");
                leftImg->setImage(CAImage::create("r/btn_downloading.png"));
            };
            
            if (row == 2) {
                title->setText("视频上传");
                leftImg->setImage(CAImage::create("r/btn_upload.png"));
            };
            break;
        
        case 2:
            if (row == 0) {
                title->setText("订阅中心");
                leftImg->setImage(CAImage::create("r/navbar_icon_subscribe_normal.png"));
            };
            
            if (row == 1) {
                title->setText("我的收藏");
                leftImg->setImage(CAImage::create("r/appcenter_list_item_rate_star_grey.png"));
            };
            break;
            
        case 3:
            if (row == 0) {
                title->setText("联通流量包");
                leftImg->setImage(CAImage::create("r/btn_vip.png"));
            };
            
            if (row == 1) {
                title->setText("问题反馈");
                leftImg->setImage(CAImage::create("r/btn_vip.png"));
            };
            
            if (row == 2) {
                title->setText("设置");
                leftImg->setImage(CAImage::create("r/btn_setting.png"));
            };
            
            break;
        default:
            break;
    }
    return cell;
}

//Necessary
unsigned int MineViewController::tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row) {
    return _px(110);
}

//Necessary
unsigned int MineViewController::numberOfRowsInSection(CATableView* table, unsigned int section) {
    if (section == 0) {
        return 1;
    } else if(section == 1 || section == 3) {
        return 3;
    } else if(section == 2) {
        return 2;
    }
}

unsigned int MineViewController::numberOfSections(CATableView* table) {
    return 4;
}

CAView* MineViewController::tableViewSectionViewForHeaderInSection(CATableView* table, const CCSize& viewSize, unsigned int section) {
    return CAView::createWithColor(ccc4(240,240,240,255));
}

unsigned int MineViewController::tableViewHeightForHeaderInSection(CATableView* table, unsigned int section) {
    if (section == 0) {
        return 0;
    }
    return _px(15);
}

void MineViewController::tableViewDidSelectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row) {
    
}

void MineViewController::tableViewDidDeselectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row) {
    
}




