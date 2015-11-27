/*
 * TreePlotImpl.h
 *
 *  Created on: Nov 27, 2015
 *      Author: spatel78745
 */

#ifndef TREEPLOTIMPL_H_
#define TREEPLOTIMPL_H_
#include <string>

using namespace std;

class TreePlotImpl
{
public:
    /*
     * Need this because declaring the private copy constructor deletes the synthesized default
     * constructor, and subclass constructors implicitly call the default constructor.
     */
    TreePlotImpl() {}

    virtual void drawNode(int row, int col, const string& key) const = 0;

    virtual void drawLeftLeg(int row, int col) const = 0;

    virtual void drawRightLeg(int row, int col) const = 0;

    virtual int rows() const = 0;

    virtual int cols() const = 0;

    /*
     * Interesting: why can't this be pure virtual?
     * virtual ~TreePlotImple() = 0
     */
    virtual ~TreePlotImpl() {};

private:
    /*
     * Forbid copying. N.B. you only need to make it private here. You also need a default
     * constructor because declaring this one constructor implicitly deletes the synthesized
     * default constructor.
     */
    TreePlotImpl(const TreePlotImpl &);
    TreePlotImpl& operator=(const TreePlotImpl &);
};

#endif /* TREEPLOTIMPL_H_ */
