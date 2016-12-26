#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QMainWindow>

#include "chart.h"
#include "chartview.h"
#include "thread.h"

#include "../src/timestamp.h"
#include "../src/pidmap.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow();
    ~MainWindow();

private slots:
    void Pcr(int state);
    void updatePcr();
    void deltaPcr(int state);
    void updateDeltaPcr();
    void jitterPcr(int state);
    void updateJitterPcr();

    void Pts(int state);
    void updatePts();
    void deltaPts(int state);
    void updatePtsDelta();

    void Dts(int state);
    void updateDts();
    void deltaDts(int state);
    void updateDtsDelta();

    void diffPcrPts(int state);
    void updateDiffPcrPts();
    void diffPcrDts(int state);
    void updateDiffPcrDts();
    void diffPtsDts(int state);
    void updateDiffPtsDts();

    void updateStatusBar(int);

    void openFile();
    void clearAllSeries();
    void erasePcrSeries(int);
    void erasePtsSeries(int);
    void eraseDtsSeries(int);
    void about();

private:
    std::ifstream* m_tsFile;

    QThreadPool *m_pthreadPool;

    ChartView *m_chartView;

    QComboBox *m_pcrComboBox;
    QComboBox *m_ptsComboBox;
    QComboBox *m_dtsComboBox;

    QGroupBox* m_pcrGroupBox;
    QGroupBox* m_ptsGroupBox;
    QGroupBox* m_dtsGroupBox;
    QGroupBox* m_diffGroupBox;

    QCheckBox* m_pcrBox;
    QCheckBox* m_deltaPcrBox;
    QCheckBox* m_jitterPcrBox;
    QCheckBox* m_ptsBox;
    QCheckBox* m_deltaPtsBox;
    QCheckBox* m_dtsBox;
    QCheckBox* m_deltaDtsBox;
    QCheckBox* m_diffPcrPtsBox;
    QCheckBox* m_diffPtsDtsBox;
    QCheckBox* m_diffPcrDtsBox;

    pcrWorker    *m_pcrWorker;
    ptsWorker    *m_ptsWorker;
    dtsWorker    *m_dtsWorker;
    pcrDeltaWorker  *m_deltaPcrWorker;
    pcrJitterWorker *m_jitterPcrWorker;
    ptsDeltaWorker  *m_ptsDeltaWorker;
    dtsDeltaWorker  *m_dtsDeltaWorker;
    diffPcrPtsWorker *m_diffPcrPtsWorker;
    diffPcrDtsWorker *m_diffPcrDtsWorker;
    diffPtsDtsWorker *m_diffPtsDtsWorker;

    void createLayout(QWidget *widget);
    void createMenu();
};

#endif // MAINWINDOW_H
