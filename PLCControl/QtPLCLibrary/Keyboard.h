#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QWidget>
class QStackedWidget;
class QLabel;
class QLineEdit;
class QPushButton;
class QComboBox;

// ��ť�ı߳�,�����ܳ���=14*BTN_SIZE,�����ܿ��=3*BTN_SIZE
#define BTN_SIZE    40

class keyBoard : public QWidget
{
    Q_OBJECT
public:
    explicit keyBoard(QWidget *parent = 0);
    ~keyBoard();

protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);

private slots:
    void focusChanged(QWidget *, QWidget *nowWidget);
    void slotBtnClicked();         // ��������

private:
    int deskWidth;                  //������
    int deskHeight;                 //����߶�
    int frmWidth;                   //������
    int frmHeight;                  //����߶�

    QPoint mousePoint;              //����϶��Զ��������ʱ������
    bool mousePressed;              //����Ƿ���
    void InitWindow();              //��ʼ���ޱ߿���
    void InitForm();                //��ʼ����������

    QLineEdit *currentLineEdit;     //��ǰ������ı���
    QString currentType;            //��ǰ���뷨����
    void changeType(QString type);  //�ı����뷨����
    void changeLetter(bool isUpper);//�ı���ĸ��Сд
    void changeStyle(int style);    //�л���ʽ����
    void setStyle(QString topColor,QString bottomColor,QString borderColor,QString textColor);

    int currentStyle;

    QStackedWidget *keyWindow;      // ���̴���,���Է�ҳ��ʾ
    QWidget *letterWindow;          // ��ĸ����
    QWidget *signWindow;            // ��ĸ����
    QLabel *infoLabel;              // ��ʾ������Ϣ

	QPushButton *closeBtn;
	QPushButton *okBtn;
    QPushButton *delBtn;
    QPushButton *typeBtn;
    QPushButton *styleBtn;

	QLabel *lb0;
	QPushButton *btn0;
    QPushButton *btn1;
    QPushButton *btn2;
    QPushButton *btn3;
    QPushButton *btn4;
    QPushButton *btn5;
    QPushButton *btn6;
    QPushButton *btn7;
    QPushButton *btn8;
    QPushButton *btn9;

    QPushButton *btnA;
    QPushButton *btnB;
    QPushButton *btnC;
    QPushButton *btnD;
    QPushButton *btnE;
    QPushButton *btnF;
    QPushButton *btnG;
    QPushButton *btnH;
    QPushButton *btnI;
    QPushButton *btnJ;
    QPushButton *btnK;
    QPushButton *btnL;
    QPushButton *btnM;
    QPushButton *btnN;
    QPushButton *btnO;
    QPushButton *btnP;
    QPushButton *btnQ;
    QPushButton *btnR;
    QPushButton *btnS;
    QPushButton *btnT;
    QPushButton *btnU;
    QPushButton *btnV;
    QPushButton *btnW;
    QPushButton *btnX;
    QPushButton *btnY;
    QPushButton *btnZ;

    QPushButton *btnSign0;
    QPushButton *btnSign1;
    QPushButton *btnSign2;
    QPushButton *btnSign3;
    QPushButton *btnSign4;
    QPushButton *btnSign5;
    QPushButton *btnSign6;
    QPushButton *btnSign7;
    QPushButton *btnSign8;
    QPushButton *btnSign9;
    QPushButton *btnSign10;
    QPushButton *btnSign11;
    QPushButton *btnSign12;
};

#endif // KEYBOARD_H


