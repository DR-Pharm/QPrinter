#include "keyBoard.h"
#include "qdesktopwidget.h"
#include <QApplication>
#include <QStackedWidget>
#include <QMouseEvent>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QDebug>

keyBoard::keyBoard(QWidget *parent) :
	QWidget(parent)
{
	this->InitWindow();
	//    this->InitProperty();
	this->InitForm();

	QDesktopWidget* w = QApplication::desktop();
	deskWidth = w->screenGeometry().width();
	deskHeight = w->screenGeometry().height();
	frmWidth = this->width();
	frmHeight = this->height();

	// 自动填充在底部
	//this->setGeometry(0,deskHeight-frmWidth,deskWidth,frmWidth);
	// 居中显示
	//QPoint movePoint(deskWidth / 2 - frmWidth / 2, deskHeight / 2 - frmHeight / 2);
	//this->move(movePoint);
}

keyBoard::~keyBoard()
{
}

void keyBoard::mouseMoveEvent(QMouseEvent *e)
{
	if (mousePressed && (e->buttons() && Qt::LeftButton))
	{
		this->move(e->globalPos() - mousePoint);
		this->repaint();
		e->accept();
	}
}

void keyBoard::mousePressEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton)
	{
		mousePressed = true;
		mousePoint = e->globalPos() - this->pos();
		e->accept();
	}
}

void keyBoard::mouseReleaseEvent(QMouseEvent *)
{
	mousePressed = false;
}

void keyBoard::focusChanged(QWidget *, QWidget *nowWidget)
{
#if 1
	if (nowWidget != 0 && !this->isAncestorOf(nowWidget))
	{
		if (nowWidget->inherits("QLineEdit"))
		{
			currentLineEdit = (QLineEdit *)nowWidget;

			QPoint movePoint;

			// 鼠标点击位置坐标
			if (QCursor::pos().y() > deskHeight / 2)
			{
				// 靠上居中显示
				movePoint = QPoint(deskWidth / 2 - frmWidth / 2, 0);
			}
			else
			{
				// 靠下居中显示
				movePoint = QPoint(deskWidth / 2 - frmWidth / 2, deskHeight - frmHeight);
			}

			//this->move(movePoint);
			this->repaint();
			this->setVisible(true);
		}
		else
		{
			currentLineEdit = 0;
			//qDebug() << "BBB";
			this->setVisible(false);
			// 需要将输入法切换到最初的原始状态--小写
			currentType = "min";
			changeType(currentType);
			currentStyle = 0;
			changeStyle(currentStyle);
			keyWindow->setCurrentIndex(0);
		}
	}
#endif
}
void keyBoard::slotBtnClicked()
{
	QPushButton *btn = (QPushButton *)sender();
	QString objectName = btn->objectName();

	if (objectName == "typeBtn")
	{
		if (currentType == "min")
		{
			currentType = "max";
		}
		else if (currentType == "max")
		{
			currentType = "sign";
		}
		else
		{
			currentType = "min";
		}
		changeType(currentType);
	}
	else if (objectName == "delBtn")
	{
		if (currentLineEdit != 0)
		{
			currentLineEdit->backspace();
		}
	}
	else if (objectName == "styleBtn")
	{
		currentStyle++;
		if (currentStyle > 2)
		{
			currentStyle = 0;
		}
		changeStyle(currentStyle);
	}
	else if (objectName == "closeBtn")
	{
#ifdef Q_OS_WIN     //如果是windows系统
		this->move(-500, -500);
#else
		this->setVisible(false);
#endif
		currentType = "min";
		changeType(currentType);
		currentStyle = 0;
		changeStyle(currentStyle);
		keyWindow->setCurrentIndex(0);
		//close();
	}
	else if (objectName == "okBtn")
	{
		if (currentLineEdit != 0)
		{
			currentLineEdit->clearFocus();
		}
	}
	else
	{
		QString value = btn->text();
		// 如果是&按钮，因为对应&被过滤,所以真实的text为去除前面一个&字符
		if (value == "&&")
		{
			value = value.right(1);
		}
		// 当前不是中文模式,则单击按钮对应text为传递参数
		if (currentType != "chinese")
		{
			if (currentLineEdit != 0)
			{
				currentLineEdit->insert(value);
			}
		}
	}
}

void keyBoard::InitWindow()
{
	this->setProperty("Form", true);
	this->setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
	this->setFixedSize(14 * BTN_SIZE, 3 * BTN_SIZE);
	this->setFocusPolicy(Qt::NoFocus);
	//    this->setAttribute(Qt::WA_X11DoNotAcceptFocus, true);
	//    this->setAttribute(Qt::WA_ShowWithoutActivating,true);

	keyWindow = new QStackedWidget(this);
	keyWindow->setFixedSize(13 * BTN_SIZE, 2 * BTN_SIZE);
	letterWindow = new QWidget;
	signWindow = new QWidget;

	// 填加功能按钮

	lb0 = new QLabel(this);
	lb0->setAlignment(Qt::AlignCenter);
	lb0->setObjectName("lb0");
	//lb0->setProperty("function", true);
	lb0->setStyleSheet("font: bold; background: rgb(255, 200, 200);");
	lb0->setText(QString::fromLocal8Bit("MOV"));
	lb0->setFixedSize(BTN_SIZE, BTN_SIZE);

	closeBtn = new QPushButton(this);
	closeBtn->setObjectName("closeBtn");
	closeBtn->setProperty("function", true);
	closeBtn->setText(tr("X"));
	closeBtn->setFixedSize(BTN_SIZE, BTN_SIZE);

	okBtn = new QPushButton(this);
	okBtn->setObjectName("okBtn");
	okBtn->setProperty("function", true);
	okBtn->setText(tr("OK"));
	okBtn->setFixedSize(BTN_SIZE, BTN_SIZE);

	// 删除一个字符
	delBtn = new QPushButton(this);
	delBtn->setObjectName("delBtn");
	delBtn->setProperty("function", true);
	delBtn->setText(tr("D"));
	delBtn->setFixedSize(BTN_SIZE, BTN_SIZE);

	// 改变输法类型:大写,小写,字符
	typeBtn = new QPushButton(this);
	typeBtn->setObjectName("typeBtn");
	typeBtn->setProperty("function", true);
	typeBtn->setText(tr("小"));
	typeBtn->setFixedSize(BTN_SIZE, BTN_SIZE);

	// 换肤
	styleBtn = new QPushButton(this);
	styleBtn->setObjectName("styleBtn");
	styleBtn->setProperty("function", true);
	styleBtn->setText(tr("style"));
	styleBtn->setFixedSize(BTN_SIZE, BTN_SIZE);

	// 填加数字键盘
	btn1 = new QPushButton(this);
	btn1->setText(tr("1"));
	btn1->setProperty("num", true);
	btn1->setFixedSize(BTN_SIZE, BTN_SIZE);

	btn2 = new QPushButton(this);
	btn2->setText(tr("2"));
	btn2->setProperty("num", true);
	btn2->setFixedSize(BTN_SIZE, BTN_SIZE);

	btn3 = new QPushButton(this);
	btn3->setText(tr("3"));
	btn3->setProperty("num", true);
	btn3->setFixedSize(BTN_SIZE, BTN_SIZE);

	btn4 = new QPushButton(this);
	btn4->setFixedSize(BTN_SIZE, BTN_SIZE);
	btn4->setProperty("num", true);
	btn4->setText(tr("4"));

	btn5 = new QPushButton(this);
	btn5->setFixedSize(BTN_SIZE, BTN_SIZE);
	btn5->setProperty("num", true);
	btn5->setText(tr("5"));

	btn6 = new QPushButton(this);
	btn6->setFixedSize(BTN_SIZE, BTN_SIZE);
	btn6->setProperty("num", true);
	btn6->setText(tr("6"));

	btn7 = new QPushButton(this);
	btn7->setFixedSize(BTN_SIZE, BTN_SIZE);
	btn7->setProperty("num", true);
	btn7->setText(tr("7"));

	btn8 = new QPushButton(this);
	btn8->setFixedSize(BTN_SIZE, BTN_SIZE);
	btn8->setProperty("num", true);
	btn8->setText(tr("8"));

	btn9 = new QPushButton(this);
	btn9->setFixedSize(BTN_SIZE, BTN_SIZE);
	btn9->setProperty("num", true);
	btn9->setText(tr("9"));

	btn0 = new QPushButton(this);
	btn0->setFixedSize(BTN_SIZE, BTN_SIZE);
	btn0->setProperty("num", true);
	btn0->setText(tr("0"));

	// 填加字母键盘
	btnA = new QPushButton(letterWindow);
	btnA->setText(tr("a"));
	btnA->setProperty("letter", true);
	btnA->setFixedSize(BTN_SIZE, BTN_SIZE);

	btnB = new QPushButton(letterWindow);
	btnB->setText(tr("b"));
	btnB->setProperty("letter", true);
	btnB->setFixedSize(BTN_SIZE, BTN_SIZE);

	btnC = new QPushButton(letterWindow);
	btnC->setText(tr("c"));
	btnC->setProperty("letter", true);
	btnC->setFixedSize(BTN_SIZE, BTN_SIZE);

	btnD = new QPushButton(letterWindow);
	btnD->setText(tr("d"));
	btnD->setProperty("letter", true);
	btnD->setFixedSize(BTN_SIZE, BTN_SIZE);

	btnE = new QPushButton(letterWindow);
	btnE->setText(tr("e"));
	btnE->setProperty("letter", true);
	btnE->setFixedSize(BTN_SIZE, BTN_SIZE);

	btnF = new QPushButton(letterWindow);
	btnF->setText(tr("f"));
	btnF->setProperty("letter", true);
	btnF->setFixedSize(BTN_SIZE, BTN_SIZE);

	btnG = new QPushButton(letterWindow);
	btnG->setText(tr("g"));
	btnG->setProperty("letter", true);
	btnG->setFixedSize(BTN_SIZE, BTN_SIZE);

	btnH = new QPushButton(letterWindow);
	btnH->setText(tr("h"));
	btnH->setProperty("letter", true);
	btnH->setFixedSize(BTN_SIZE, BTN_SIZE);

	btnI = new QPushButton(letterWindow);
	btnI->setText(tr("i"));
	btnI->setProperty("letter", true);
	btnI->setFixedSize(BTN_SIZE, BTN_SIZE);

	btnJ = new QPushButton(letterWindow);
	btnJ->setText(tr("j"));
	btnJ->setProperty("letter", true);
	btnJ->setFixedSize(BTN_SIZE, BTN_SIZE);

	btnK = new QPushButton(letterWindow);
	btnK->setText(tr("k"));
	btnK->setProperty("letter", true);
	btnK->setFixedSize(BTN_SIZE, BTN_SIZE);

	btnL = new QPushButton(letterWindow);
	btnL->setText(tr("l"));
	btnL->setProperty("letter", true);
	btnL->setFixedSize(BTN_SIZE, BTN_SIZE);

	btnM = new QPushButton(letterWindow);
	btnM->setText(tr("m"));
	btnM->setProperty("letter", true);
	btnM->setFixedSize(BTN_SIZE, BTN_SIZE);

	btnN = new QPushButton(letterWindow);
	btnN->setText(tr("n"));
	btnN->setProperty("letter", true);
	btnN->setFixedSize(BTN_SIZE, BTN_SIZE);

	btnO = new QPushButton(letterWindow);
	btnO->setText(tr("o"));
	btnO->setProperty("letter", true);
	btnO->setFixedSize(BTN_SIZE, BTN_SIZE);

	btnP = new QPushButton(letterWindow);
	btnP->setText(tr("p"));
	btnP->setProperty("letter", true);
	btnP->setFixedSize(BTN_SIZE, BTN_SIZE);

	btnQ = new QPushButton(letterWindow);
	btnQ->setText(tr("q"));
	btnQ->setProperty("letter", true);
	btnQ->setFixedSize(BTN_SIZE, BTN_SIZE);

	btnR = new QPushButton(letterWindow);
	btnR->setText(tr("r"));
	btnR->setProperty("letter", true);
	btnR->setFixedSize(BTN_SIZE, BTN_SIZE);

	btnS = new QPushButton(letterWindow);
	btnS->setText(tr("s"));
	btnS->setProperty("letter", true);
	btnS->setFixedSize(BTN_SIZE, BTN_SIZE);

	btnT = new QPushButton(letterWindow);
	btnT->setText(tr("t"));
	btnT->setProperty("letter", true);
	btnT->setFixedSize(BTN_SIZE, BTN_SIZE);

	btnU = new QPushButton(letterWindow);
	btnU->setText(tr("u"));
	btnU->setProperty("letter", true);
	btnU->setFixedSize(BTN_SIZE, BTN_SIZE);

	btnV = new QPushButton(letterWindow);
	btnV->setText(tr("v"));
	btnV->setProperty("letter", true);
	btnV->setFixedSize(BTN_SIZE, BTN_SIZE);

	btnW = new QPushButton(letterWindow);
	btnW->setText(tr("w"));
	btnW->setProperty("letter", true);
	btnW->setFixedSize(BTN_SIZE, BTN_SIZE);

	btnX = new QPushButton(letterWindow);
	btnX->setText(tr("x"));
	btnX->setProperty("letter", true);
	btnX->setFixedSize(BTN_SIZE, BTN_SIZE);

	btnY = new QPushButton(letterWindow);
	btnY->setFixedSize(BTN_SIZE, BTN_SIZE);
	btnY->setProperty("letter", true);
	btnY->setText(tr("y"));

	btnZ = new QPushButton(letterWindow);
	btnZ->setFixedSize(BTN_SIZE, BTN_SIZE);
	btnZ->setProperty("letter", true);
	btnZ->setText(tr("z"));

	QGridLayout *letterLayout = new QGridLayout;
	letterLayout->addWidget(btnA, 0, 0, 1, 1);
	letterLayout->addWidget(btnB, 0, 1, 1, 1);
	letterLayout->addWidget(btnC, 0, 2, 1, 1);
	letterLayout->addWidget(btnD, 0, 3, 1, 1);
	letterLayout->addWidget(btnE, 0, 4, 1, 1);
	letterLayout->addWidget(btnF, 0, 5, 1, 1);
	letterLayout->addWidget(btnG, 0, 6, 1, 1);
	letterLayout->addWidget(btnH, 0, 7, 1, 1);
	letterLayout->addWidget(btnI, 0, 8, 1, 1);
	letterLayout->addWidget(btnJ, 0, 9, 1, 1);
	letterLayout->addWidget(btnK, 0, 10, 1, 1);
	letterLayout->addWidget(btnL, 0, 11, 1, 1);
	letterLayout->addWidget(btnM, 0, 12, 1, 1);
	letterLayout->addWidget(btnN, 1, 0, 1, 1);
	letterLayout->addWidget(btnO, 1, 1, 1, 1);
	letterLayout->addWidget(btnP, 1, 2, 1, 1);
	letterLayout->addWidget(btnQ, 1, 3, 1, 1);
	letterLayout->addWidget(btnR, 1, 4, 1, 1);
	letterLayout->addWidget(btnS, 1, 5, 1, 1);
	letterLayout->addWidget(btnT, 1, 6, 1, 1);
	letterLayout->addWidget(btnU, 1, 7, 1, 1);
	letterLayout->addWidget(btnV, 1, 8, 1, 1);
	letterLayout->addWidget(btnW, 1, 9, 1, 1);
	letterLayout->addWidget(btnX, 1, 10, 1, 1);
	letterLayout->addWidget(btnY, 1, 11, 1, 1);
	letterLayout->addWidget(btnZ, 1, 12, 1, 1);

	// 设置行和列间距
	letterLayout->setSpacing(0);

	// 设置和外框间距
	letterLayout->setContentsMargins(0, 0, 0, 0);
	letterWindow->setLayout(letterLayout);

	// 填加符号键盘
	btnSign0 = new QPushButton(signWindow);
	btnSign0->setFixedSize(BTN_SIZE, BTN_SIZE);
	btnSign0->setProperty("sign", true);
	btnSign0->setText(tr("!"));

	btnSign1 = new QPushButton(signWindow);
	btnSign1->setFixedSize(BTN_SIZE, BTN_SIZE);
	btnSign1->setProperty("sign", true);
	btnSign1->setText(tr("@"));

	btnSign2 = new QPushButton(signWindow);
	btnSign2->setFixedSize(BTN_SIZE, BTN_SIZE);
	btnSign2->setProperty("sign", true);
	btnSign2->setText(tr("#"));

	btnSign3 = new QPushButton(signWindow);
	btnSign3->setFixedSize(BTN_SIZE, BTN_SIZE);
	btnSign3->setProperty("sign", true);
	btnSign3->setText(tr("$"));

	btnSign4 = new QPushButton(signWindow);
	btnSign4->setFixedSize(BTN_SIZE, BTN_SIZE);
	btnSign4->setProperty("sign", true);
	btnSign4->setText(tr("%"));

	btnSign5 = new QPushButton(signWindow);
	btnSign5->setFixedSize(BTN_SIZE, BTN_SIZE);
	btnSign5->setProperty("sign", true);
	btnSign5->setText(tr("^"));

	btnSign6 = new QPushButton(signWindow);
	btnSign6->setFixedSize(BTN_SIZE, BTN_SIZE);
	btnSign6->setProperty("sign", true);
	btnSign6->setText(tr("&&"));

	btnSign7 = new QPushButton(signWindow);
	btnSign7->setFixedSize(BTN_SIZE, BTN_SIZE);
	btnSign7->setProperty("sign", true);
	btnSign7->setText(tr("*"));

	btnSign8 = new QPushButton(signWindow);
	btnSign8->setFixedSize(BTN_SIZE, BTN_SIZE);
	btnSign8->setProperty("sign", true);
	btnSign8->setText(tr("("));

	btnSign9 = new QPushButton(signWindow);
	btnSign9->setFixedSize(BTN_SIZE, BTN_SIZE);
	btnSign9->setProperty("sign", true);
	btnSign9->setText(tr(")"));

	btnSign10 = new QPushButton(signWindow);
	btnSign10->setFixedSize(BTN_SIZE, BTN_SIZE);
	btnSign10->setProperty("sign", true);
	btnSign10->setText(tr(","));

	btnSign11 = new QPushButton(signWindow);
	btnSign11->setFixedSize(BTN_SIZE, BTN_SIZE);
	btnSign11->setProperty("sign", true);
	btnSign11->setText(tr("."));

	btnSign12 = new QPushButton(signWindow);
	btnSign12->setFixedSize(BTN_SIZE, BTN_SIZE);
	btnSign12->setProperty("sign", true);
	btnSign12->setText(tr("?"));

	infoLabel = new QLabel(signWindow);
	infoLabel->setProperty("sign", true);

	QGridLayout *signLayout = new QGridLayout;
	signLayout->addWidget(btnSign0, 0, 0, 1, 1);
	signLayout->addWidget(btnSign1, 0, 1, 1, 1);
	signLayout->addWidget(btnSign2, 0, 2, 1, 1);
	signLayout->addWidget(btnSign3, 0, 3, 1, 1);
	signLayout->addWidget(btnSign4, 0, 4, 1, 1);
	signLayout->addWidget(btnSign5, 0, 5, 1, 1);
	signLayout->addWidget(btnSign6, 0, 6, 1, 1);
	signLayout->addWidget(btnSign7, 0, 7, 1, 1);
	signLayout->addWidget(btnSign8, 0, 8, 1, 1);
	signLayout->addWidget(btnSign9, 0, 9, 1, 1);
	signLayout->addWidget(btnSign10, 0, 10, 1, 1);
	signLayout->addWidget(btnSign11, 0, 11, 1, 1);
	signLayout->addWidget(btnSign12, 0, 12, 1, 1);
	signLayout->addWidget(infoLabel, 1, 0, 1, 13, Qt::AlignCenter);

	// 设置行和列间距
	signLayout->setSpacing(0);

	// 设置和外框间距
	signLayout->setContentsMargins(0, 0, 0, 0);
	signWindow->setLayout(signLayout);

	keyWindow->addWidget(letterWindow);
	keyWindow->addWidget(signWindow);
	keyWindow->setCurrentIndex(0);

	// 全局步局
	QGridLayout *layout = new QGridLayout;

	layout->addWidget(lb0, 0, 0, 1, 1);
	layout->addWidget(btn0, 0, 1, 1, 1);
	layout->addWidget(btn1, 0, 2, 1, 1);
	layout->addWidget(btn2, 0, 3, 1, 1);
	layout->addWidget(btn3, 0, 4, 1, 1);
	layout->addWidget(btn4, 0, 5, 1, 1);
	layout->addWidget(btn5, 0, 6, 1, 1);
	layout->addWidget(btn6, 0, 7, 1, 1);
	layout->addWidget(btn7, 0, 8, 1, 1);
	layout->addWidget(btn8, 0, 9, 1, 1);
	layout->addWidget(btn9, 0, 10, 1, 1);
	layout->addWidget(delBtn, 0, 11, 1, 1);
	layout->addWidget(closeBtn, 0, 13, 1, 1);
	layout->addWidget(okBtn, 0, 12, 1, 1);
	layout->addWidget(typeBtn, 1, 13, 1, 1);
	layout->addWidget(styleBtn, 2, 13, 1, 1);
	layout->addWidget(keyWindow, 1, 0, 2, 13);
	layout->setSpacing(0);
	layout->setContentsMargins(0, 0, 0, 0);
	this->setLayout(layout);
}

void keyBoard::InitForm()
{
	currentStyle = 0;
	currentLineEdit = 0;
	mousePressed = false;
	currentType = "min";
	changeType("min");
	currentStyle = 0;
	changeStyle(currentStyle);

	QList<QPushButton *> btn = this->findChildren<QPushButton *>();
	foreach(QPushButton * b, btn) {
		connect(b, SIGNAL(clicked()), this, SLOT(slotBtnClicked()));
	}

	// 绑定全局改变焦点信号槽
	connect(qApp, SIGNAL(focusChanged(QWidget *, QWidget *)),
		this, SLOT(focusChanged(QWidget *, QWidget *)));
	// 绑定按键事件过滤器
//    qApp->installEventFilter(this);
}

void keyBoard::changeType(QString type)
{
	if (type == "min")
	{
		typeBtn->setText(QString::fromLocal8Bit ("↓"));
		changeLetter(false);
		keyWindow->setCurrentIndex(0);
	}
	else if (type == "max")
	{
		typeBtn->setText(QString::fromLocal8Bit("↑"));
		changeLetter(true);
	}
	else
	{
		typeBtn->setText(QString::fromLocal8Bit("SY"));
		keyWindow->setCurrentIndex(1);
	}
}

void keyBoard::changeLetter(bool isUpper)
{
	QList<QPushButton *> btn = this->findChildren<QPushButton *>();
	foreach(QPushButton * b, btn)
	{
		if (b->property("letter").toBool())
		{
			if (isUpper)
			{
				b->setText(b->text().toUpper());
			}
			else
			{
				b->setText(b->text().toLower());
			}
		}
	}
}

void keyBoard::changeStyle(int style)
{
	switch (style)
	{
	case 0:
	{
		// 灰色
		setStyle("#E4E4E4", "#A2A2A2", "#DCDCDC", "#000000");
		styleBtn->setText(QString::fromLocal8Bit("ST"));
		break;
	}
	case 1:
	{
		// 蓝色
		setStyle("#DEF0FE", "#C0DEF6", "#C0DCF2", "#386487");
		styleBtn->setText(QString::fromLocal8Bit("ST"));
		break;
	}
	case 2:
	{
		// 黑色
		setStyle("#4D4D4D", "#292929", "#C2CCD8", "#F0F0F0");
		styleBtn->setText(QString::fromLocal8Bit("ST"));
		break;
	}
	}
}


void keyBoard::setStyle(QString topColor, QString bottomColor, QString borderColor, QString textColor)
{
	QStringList qss;

	// 设置键盘背景色,从上到下渐变效果
	qss.append(QString("QWidget{background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 %1,stop:1 %2);}")
		.arg(topColor).arg(bottomColor));

	// 设置字按钮字体
	qss.append(QString("QLabel,QPushButton{font:%1px;color:%2;}").arg(BTN_SIZE / 2).arg(textColor));

	// 按钮边框
	qss.append(QString("QPushButton{border:1px solid %1;}").arg(borderColor));

	// 去掉按钮焦点虚线框和圆角
	qss.append("QPushButton{outline:0px;border-radius:5px;}");

	// 按钮有按下的效果
	qss.append(QString("QPushButton:pressed{padding-left:5px;padding-top:5px;}"));

	// 删除按钮设为蓝色背景,白色字体
	qss.append("QPushButton#delBtn{font:bold;background:blue;color:white;}");

	// 关闭按钮设为红色背景,白色字体
	qss.append("QLable#lb0{font:bold;background:white;color:white;}");

	qss.append("QPushButton#closeBtn{font:bold;background:red;color:white;}");

	qss.append("QPushButton#okBtn{font:bold;background:green;color:white;}");


	this->setStyleSheet(qss.join(""));
}
