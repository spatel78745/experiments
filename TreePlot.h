/*
 * TreePlot.h
 *
 *  Created on: Nov 24, 2015
 *      Author: spatel78745
 */

#ifndef TREEPLOT_H_
#define TREEPLOT_H_

#include "TcpSocket.h"

class TreePlot
{
public:
    /*
     * Constructs a TreePlot
     * - height: The height of the tree
     */
    TreePlot(int height, const char *hostname = "localhost", int port = 50006) :
        mNumRows(height), mNumCols((2^(height + 1) - 1) * 50), mSocket(nullptr) {}

    virtual ~TreePlot() { delete mSocket; }

    bool drawNode(int row, int col, const string& key) const
    {
        fprintf(stderr, "drawNode(%d, %d, %s)\n", row, col, key.c_str());
        return true;
    }

    bool drawLeftLeg(int row, int col)
    {
        fprintf(stderr, "drawLeftLeg(%d, %d)\n", row, col);
        return true;
    }

    bool drawRightLeg(int row, int col)
    {
        fprintf(stderr, "drawRightLeg(%d, %d)\n", row, col);
        return true;
    }

    int rows() { return mNumRows; }

    int cols() { return mNumCols; }

private:
    int mNumRows;
    int mNumCols;
    TcpSocket* mSocket;
};



#endif /* TREEPLOT_H_ */
