#pragma once
#define INSPECTION_360

#define MODEL_BASLER		0
#define MODEL_DAHENG		1


//”ÎPLCÕ®–≈
#define PLCCONNECT
	


#define BASLER
#define BASLERUSB
//#define DAHENG


//#define CARINOUTCHECK



#pragma region QT
#include <QSettings>
#include <QTcpSocket>
#include <QtNetwork>
#include <QThread>
#include <QMessageBox>
#include <QMessageBox>
#include <QDir>
#include <QLibrary>
#include <QVector>
#include <QGraphicsScene>
#include <QCloseEvent>
#include <QTimerEvent>
#include <QtMultimedia/QSound>
#include <QFileDialog>
#include <QTableWidget>
#include <QHeaderView>
#include <QTableWidgetItem>
#pragma endregion

#ifdef PLCCONNECT
#include "comm.h"
#endif // PLCCONNECT

#include <io.h>  
#include <direct.h>  
#include <vector>
#include <fstream>
#include <iostream> 
#include <math.h>
#pragma region log
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
namespace spd = spdlog;
#pragma endregion

