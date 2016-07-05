#include "customplot.h"

CustomPlot::CustomPlot()
{
	setMinimumSize(1000, 400);
	replot();
}
CustomPlot::CustomPlot(std::shared_ptr<RatingInsulation> rate)
{
	m_Rate = rate;
}
void CustomPlot::setCustomPlot()
{
	Test m_Test(m_Rate->returnsTest());
	std::multimap<double, double> glinka(m_Test.returnsm_MMGlinkaVoltageTime());
	QVector<double> x;
	QVector<double> y;
	QVector<double> minX;
	QVector<double> minY;

	QVector<double> maxX;
	QVector<double> maxY;

	for (auto i:glinka)
	{
		y.push_back(i.first);
		x.push_back(i.second);

	}

	for (int i=0; i<=m_Test.returnsPairMaxVoltageTime().first; ++i)
	{
		minX.push_back(m_Test.returnsPairMinVoltageTime().second);
		minY.push_back(i);
	}

	for (int i=0; i<=m_Test.returnsPairMaxVoltageTime().first; ++i)
	{
		maxX.push_back(m_Test.returnsPairMaxVoltageTime().second);
		maxY.push_back(i);
	}

	addGraph();
	graph(0)->setName(tr("Napięcie odbudowy [V]"));
	//graph(0)->setLabel(tr("Czas [s]"));
	graph(0)->setData(x, y);
	addGraph();
	graph(1)->setData(minX, minY);
	addGraph();
	graph(2)->setData(maxX, maxY);

	//m_CustomPlot->graph(0)->setName(tr("Napięcie odbudowy [V]"));
	//m_CustomPlot->xAxis->setLabel(tr("Czas [s]"));
	//m_CustomPlot->yAxis->setLabel(tr("Napięcie odbudowy [V]"));
	xAxis->setRange(0, *(std::max_element(x.begin(), x.end())));
	yAxis->setRange(0, *(std::max_element(y.begin(), y.end())));
	//m_CustomPlot->setMinimumSize(1000, 500);
	legend->setVisible(true);
	legend->setBrush(QBrush(QColor(255,255,255,230)));
	axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignLeft);
	//m_CustomPlot->setInteraction(QCP::iRangeDrag, true);
	//m_CustomPlot->setInteraction(QCP::iSelectPlottables, true);
	setInteractions(QCP::iRangeDrag | QCP::iSelectPlottables| QCP::iRangeZoom | QCP::iMultiSelect| QCP::iSelectAxes| QCP::iSelectLegend | QCP::iSelectItems | QCP::iSelectOther);
	replot();
}