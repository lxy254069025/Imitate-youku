//
//  MineViewController.h
//  youku
//
//  Created by 卢喜羲 on 15/8/25.
//
//

#ifndef __youku__MineViewController__
#define __youku__MineViewController__

#include "RootWindow.h"

class MineTableViewCell : public CATableViewCell {
    
public:
    MineTableViewCell();
    
    virtual ~MineTableViewCell();
    
    static MineTableViewCell* create(const std::string& reuseIdentifier,const CADipRect& _rect = CADipRectZero);
    
    void initTableViewCell();
    
    virtual void highlightedTableViewCell();
    
    virtual void selectedTableViewCell();
    
};

class MineViewController : public CAViewController,CAMediaDelegate,CATableViewDataSource,CATableViewDelegate {
    
public:
    MineViewController();
    
    virtual ~MineViewController();
    
    CREATE_FUNC(MineViewController);
    
    virtual void getSelectedImage(CAImage *image);
    
    //Necessary
    virtual CATableViewCell* tableCellAtIndex(CATableView* table, const CCSize& cellSize, unsigned int section, unsigned int row);
    
    //Necessary
    virtual unsigned int tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);
    
    //Necessary
    virtual unsigned int numberOfRowsInSection(CATableView* table, unsigned int section);
    
    virtual unsigned int numberOfSections(CATableView* table);
    
    virtual CAView* tableViewSectionViewForHeaderInSection(CATableView* table, const CCSize& viewSize, unsigned int section);
    
    virtual unsigned int tableViewHeightForHeaderInSection(CATableView* table, unsigned int section);
    
    virtual void tableViewDidSelectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);
    
    virtual void tableViewDidDeselectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);
protected:
    void viewDidLoad();
    
    void viewDidUnload();
    
private:
    
    void loadHeader();
    
    void loadTableView();
    
private:
    CAView* m_header;
    
    CATableView* m_tableView;
    
    CADipSize winSize;
    
    CAView* m_backView;
};

#endif /* defined(__youku__MineViewController__) */
