#ifndef SCENE_H
#define SCENE_H

#define MAX_TOP_LEFT_CORNER -984,-446
#define WIDTH_MUX 1
#define MUXs_SIZE 6
#define REGISTERS_COLOR QColor(50,50,50)
#define INITAIL_COLOR QColor(70,70,70)
#define FLUSH_COLOR QColor(70,70,70)

#define fetch 0
#define decode 1
#define ex 2
#define memory 3
#define wb 4

#define PC_POS 0
#define STALL 1
#define FLUSH 2
#include <QCoreApplication>
#include <QObject>
#include <QWidget>
#include <QPen>
#include <QBrush>
#include <QFont>
#include <QPainter>
#include <QPaintEvent>
#include <QRect>
#include <QRectF>
#include <QLabel>
#include <QPointF>
#include <QPainterPath>
#include <bits/stdc++.h>
#include <iostream>
#include <QImage>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSceneEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsTextItem>
#include "path.h"
#include "stage.h"
#include "instructionfetch.h"
#include "instructiondecode.h"
#include "execution.h"
#include "memorystage.h"
#include "writebackstage.h"
#include <stack>
#include <QStack>
#include <fstream>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QHBoxLayout>
#include <QTimer>
#include <QProgressBar>

using namespace std;
class state {
public:
    QColor color;
    QString text_instruction;
    vector<string> MUXs;
    state(QColor clr = Qt::white ){ this->color = clr;}
};

class myScene : public QGraphicsScene
{
    Q_OBJECT
private:
    QString Pipeline_Path;
    QGraphicsTextItem* cursor; // printing coordinates
    QTimer* timer;
    bool play;

    vector<QColor> colors;
    int index_color;  // fetch color
    uint index; // state index


    vector<string> code;
    vector<string> clocks_verilog;
    vector<string> regfile_clocks;
    vector<string> datamemory_clocks;
    vector<string> pipeline_regs_clocks;
    uint max_clocks;
    ifstream verilog_file, regfile_file,dataMem_file,pipeline_regs_file ;
    string   verilogPath , regfilePath,dataMemPath,pipeline_regsPath;

    vector< vector<state> > states;

    InstructionFetch* IF;
    InstructionDecode* ID;
    Execution* EX;
    MemoryStage* MEM;
    WriteBackStage* WB;

    QGraphicsRectItem* IF_ID;
    QGraphicsRectItem* ID_EX;
    QGraphicsRectItem* EX_MEM;
    QGraphicsRectItem* MEM_WB;
    // Text Drawing *** Not Imortant ***
    QGraphicsTextItem* IFID_txt;
    QGraphicsTextItem* IDEX_txt;
    QGraphicsTextItem* EXMEM_txt;
    QGraphicsTextItem* MEMWB_txt;
    QGraphicsTextItem** MUX_txt;

    int PC;
    int flush;
    int stall;

    QImage image;
    QIcon icon;

    QProgressBar* progressBar;

public:
    explicit myScene(QWidget *parent = nullptr);
    void updateStagesColors(int);
    void updateProgressBar();

private:
    void RegistersUnit();
    void initColors();
    void initText();
    void initStates();
    void initButtons();
    void ReadClocks();
    void ReadRegFile();
    void ReadDataMem();
    void Readpipeline_regs();
    vector<string> split_string(string s,string splitter);
    QString parasePC_Text(string pc);
protected:
//    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void keyPressEvent(QKeyEvent *event) override;
//    void drawBackground(QPainter *painter, const QRectF &rect) override;

signals:
    void updateDataMem(string); // it updates data memory and data_mem table
    void updateRegFile(string);
    void updatepipeline_regs(string);
    void updateRegistersGUI();

public slots:
    void addNewItem(QGraphicsItem*);
    void UpdatePipeline(int direction);
    void INIT_Scene(vector<string>);
    void rightButton();
    void leftButton();
    void playButton();
    void continuous_play();

};

#endif // SCENE_H
