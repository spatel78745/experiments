/*
 * TreePlotImplGserv.h
 *
 *  Created on: Nov 27, 2015
 *      Author: spatel78745
 */

#ifndef GSERV_H_
#define GSERV_H_

#include <string>
#include "TcpSocket.h"
#include "TreePlot.h"

using namespace std;

class Gserv : public TreePlot
{
public:
    Gserv(const char *host, int port);

    virtual void drawNode(int row, int col, const string& key) const override;

    virtual void drawLeftLeg(int row1, int col1, int row2, int col2) const override;

    virtual void drawRightLeg(int row1, int col1, int row2, int col2) const override;

    virtual int rows() const override;

    virtual int cols() const override;

    virtual ~Gserv() override;

private:
    void sendCommand(string cmd) const;

private:
    TcpSocket *mTcpSocket;
    const char *mHost;
    const int mPort;
};

#endif /* GSERV_H_ */
