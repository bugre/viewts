#ifndef THREAD_H
#define THREAD_H

#include <QDebug>
#include <QRunnable>
#include <QtCharts/QLineSeries>

#include "chart.h"
#include "../src/timestamp.h"

QT_CHARTS_USE_NAMESPACE

class timeStampWorker : public QObject, public QRunnable
{
    Q_OBJECT

    // used to compute competion rate
    unsigned int m_nbProgress;
    unsigned int m_progress;
    unsigned int m_fileSize;

    // update the competion rate
    void updateProgress();

    // number of packet read by library before run() returns
    const unsigned int m_WindowPacket = 5000;

protected:
    // retrieve the time stamps
    timestamp* m_timestamp;

    // chart for drawing
    Chart* m_chart;

    // series of data to draw
    QLineSeries* m_Series;

public:
    timeStampWorker(std::ifstream *tsFile, Chart *chart);
    ~timeStampWorker();

    // true if the thread is running
    bool m_isRunning;

    // manipulate the series
    void showSeries();
    void hideSeries();

    // write the serie of points in file - TODO
    void serializeSerie();

    // run function from QRunnable
    void run();

    // function used in thread - factorize the code
    bool (timestamp::*m_func)(unsigned int& index, double& val);

signals:
     void finished();
     void updated(int);
};


////////////////////
// PCR worker
class pcrWorker : public timeStampWorker
{
public:
    pcrWorker(std::ifstream *tsFile, unsigned int pid, Chart *chart);
};

class pcrDeltaWorker : public timeStampWorker
{
public:
    pcrDeltaWorker(std::ifstream *tsFile, unsigned int pid, Chart *chart);
};

class pcrJitterWorker : public timeStampWorker
{
public:
    pcrJitterWorker(std::ifstream *tsFile, unsigned int pid, Chart *chart);
};


////////////////////
// PTS worker
class ptsWorker : public timeStampWorker
{
public:
    ptsWorker(std::ifstream *tsFile, unsigned int pid, Chart *chart);
};

class ptsDeltaWorker : public timeStampWorker
{
public:
    ptsDeltaWorker(std::ifstream *tsFile, unsigned int pid, Chart *chart);
};


////////////////////
// DTS worker
class dtsWorker : public timeStampWorker
{
public:
    dtsWorker(std::ifstream *tsFile, unsigned int pid, Chart *chart);
};

// DTS delta worker
class dtsDeltaWorker : public timeStampWorker
{
public:
    dtsDeltaWorker(std::ifstream *tsFile, unsigned int pid, Chart *chart);
};

////////////////
// Diff worker
class diffPcrPtsWorker : public timeStampWorker
{
public:
    diffPcrPtsWorker(std::ifstream *tsFile, unsigned int pidPcr, unsigned int pidPts, Chart *chart);
};

class diffPcrDtsWorker : public timeStampWorker
{
public:
    diffPcrDtsWorker(std::ifstream *tsFile, unsigned int pidPcr, unsigned int pidPts, Chart *chart);
};

class diffPtsDtsWorker : public timeStampWorker
{
public:
    diffPtsDtsWorker(std::ifstream *tsFile, unsigned int pidPts, unsigned int pidDts, Chart *chart);
};

#endif // THREAD_H
