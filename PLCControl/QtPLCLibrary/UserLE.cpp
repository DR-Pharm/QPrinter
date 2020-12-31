#include "UserLE.h"

UserLE::UserLE(QWidget *parent)
	: QLineEdit(parent)
{
}

UserLE::~UserLE()
{
}

void UserLE::mousePressEvent(QMouseEvent*)
{
	this->selectAll();
	emit POPUPKEYBOARD();
}
void UserLE::focusInEvent(QFocusEvent *event)
{
	emit CHANGERUNSPEED();
}