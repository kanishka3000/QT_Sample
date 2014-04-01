#ifndef _DEFS_
#define _DEFS_
#include <QString>
class Instrument
{
public:
	QMap<QString,QVariant> map_Fields;

	
};

namespace Defs
{
	enum Windows
	{
		MainWindow = 20,
		OrderEntry,
		PreferenceWnd,
		Blotter,
		Amend

	};

}

class NewOrder
{
public:
	QString s_Symbol;
	double d_Price;
	double d_Size;
	int i_Side;
	int i_OrderID;
	QString s_OrderTye;
	QString s_TIF;
	QString s_ExpiryDate;
};

class ExecutionReport
{
public:
	QString s_Symbol;
	double d_Price;
	double d_Size;
	int i_Side;
	int i_ExecutionType;
	int i_OrderID;

	QString s_OrderTye;
	QString s_TIF;
	QString s_ExpiryDate;
};


class ExecReportFilter
{
public:
	QString s_Symbol;
	double d_Price;
	double d_Size;
	int i_ExecutionType;
public:
	ExecReportFilter()
	{
		d_Price = 0;
		d_Size = 0;
		i_ExecutionType = 0;
	}

};

class IndexObject
{
public:
	QString s_IndexName;
	double d_IndexValue;
	double d_DiffFrmPrev;
	int i_InternalIndex;

public :
	IndexObject()
	{
		d_IndexValue = 0.0;
		s_IndexName = "Test";
		d_DiffFrmPrev = 0.0;
		i_InternalIndex = 0;
	}
};

#endif
