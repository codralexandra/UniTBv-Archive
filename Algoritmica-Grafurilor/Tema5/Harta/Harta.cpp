#include "Harta.h"
#include <limits>
#include <numeric>

Harta::Harta(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	readXMLFileAndFillGraph("C:/Users/ELITEBOOK/Documents/Facultate/AG/Teme/Tema5/Harta_Luxemburg.xml");
}

Harta::~Harta()
{
	//graph.clear();
}

void Harta::paintEvent(QPaintEvent* event)
{
	QMainWindow::paintEvent(event);

	QPainter painter(this);

	QPainterPath allArcsPath;

	for (const auto& pair : graph.getAdjacencyList())
	{
		Node* fromNode = pair.first;
		const auto& neighbors = pair.second;

		for (const auto& neighbor : neighbors)
		{
			Node* toNode = neighbor.first;

			QPointF fromPos(fromNode->getPos().x(), fromNode->getPos().y());
			QPointF toPos(toNode->getPos().x(), toNode->getPos().y());

			allArcsPath.moveTo(fromPos);
			allArcsPath.lineTo(toPos);
		}
	}

	painter.setPen(QPen(Qt::black, 2, Qt::SolidLine));
	painter.drawPath(allArcsPath);
	if (m_selectedNodeForArc && m_selectedNodeForArcSecond) //draw the selected nodes
	{
		painter.setPen(Qt::red);
		painter.setBrush(Qt::red);
		painter.setRenderHint(QPainter::Antialiasing);

		QPoint pos1 = m_selectedNodeForArc->getPos();
		painter.drawEllipse(pos1, 5, 5);

		QPoint pos2 = m_selectedNodeForArcSecond->getPos();
		painter.drawEllipse(pos2, 5, 5);
	}
	if (!result.first.empty())
	{
		painter.setPen(QPen(Qt::red, 2, Qt::SolidLine));

		const std::vector<Node*>& pathNodes = result.first;

		for (size_t i = 0; i < pathNodes.size() - 1; ++i)
		{
			Node* fromNode = pathNodes[i];
			Node* toNode = pathNodes[i + 1];

			QPointF fromPos(fromNode->getPos().x(), fromNode->getPos().y());
			QPointF toPos(toNode->getPos().x(), toNode->getPos().y());

			painter.drawLine(fromPos, toPos);
		}
	}
}

void Harta::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::RightButton)
	{
		QPoint position = event->pos();
		Node* clickedNode = graph.getNodeAtPosition(position);

		if (clickedNode)
		{
			if (!m_selectedNodeForArc)
			{
				m_selectedNodeForArc = clickedNode;
				ui.ID1->setText(QString::number(m_selectedNodeForArc->getID()));
			}
			else if (!m_selectedNodeForArcSecond)
			{
				m_selectedNodeForArcSecond = clickedNode;
				ui.ID2->setText(QString::number(m_selectedNodeForArcSecond->getID()));
				qDebug() << "IDS:" << m_selectedNodeForArc->getID() << " " << m_selectedNodeForArcSecond->getID() << "\n";
				// apply dijkstra algorithm to find the shortest way from the two nodes selected
				result = graph.dijkstra(m_selectedNodeForArc, m_selectedNodeForArcSecond);
				ui.cost->setText(QString::number(result.second));
			}
			else
			{
				ui.ID1->clear();
				ui.ID2->clear();
				result.first.clear();
				result.second = 0;
				m_selectedNodeForArc = clickedNode;
				m_selectedNodeForArcSecond = nullptr;
				ui.ID1->setText(QString::number(m_selectedNodeForArc->getID()));
			}
		}
	}
	update();
}


void Harta::readXMLFileAndFillGraph(const QString& filePath)
{
	QFile file(filePath);

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qDebug() << "Failed to open file.";
		return;
	}

	QXmlStreamReader xmlReader(&file);
	Node* currentNode = nullptr;

	findMinMaxCoordinates(filePath);
	double mainWindowWidth = width();
	double mainWindowHeight = height();
	double latScale = mainWindowHeight / (MAX_LATITUDE - MIN_LATITUDE);
	double longScale = mainWindowWidth / (MAX_LONGITUDE - MIN_LONGITUDE);

	while (!xmlReader.atEnd() && !xmlReader.hasError())
	{
		QXmlStreamReader::TokenType token = xmlReader.readNext();

		if (token == QXmlStreamReader::StartElement)
		{
			if (xmlReader.name().toString() == "node")
			{
				currentNode = new Node();
				currentNode->setId(xmlReader.attributes().value("id").toUInt());

				double latitude = xmlReader.attributes().value("latitude").toDouble();
				double longitude = xmlReader.attributes().value("longitude").toDouble();
				QPoint originalPosition;
				originalPosition.setX(longitude);
				originalPosition.setY(latitude);
				currentNode->setMapPos(originalPosition);

				double scaledLatitude = (MAX_LATITUDE - latitude) * latScale;
				double scaledLongitude = (longitude - MIN_LONGITUDE) * longScale;

				currentNode->setPos(scaledLongitude, scaledLatitude);

				graph.addNode(currentNode);
			}
			else if (xmlReader.name().toString() == "arc")
			{
				uint32_t from = xmlReader.attributes().value("from").toUInt();
				uint32_t to = xmlReader.attributes().value("to").toUInt();
				double length = xmlReader.attributes().value("length").toDouble();

				Node* fromNode = graph.getNodeById(from);
				Node* toNode = graph.getNodeById(to);

				if (fromNode && toNode)
				{
					graph.addEdge(fromNode, toNode, length);
				}
			}
		}
	}

	if (xmlReader.hasError())
	{
		qDebug() << "Error while parsing XML:" << xmlReader.errorString();
	}

	file.close();
}

void Harta::findMinMaxCoordinates(const QString& filePath)
{
	QFile file(filePath);

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qDebug() << "Failed to open file.";
		return;
	}

	QXmlStreamReader xmlReader(&file);

	MIN_LATITUDE = std::numeric_limits<double>::max();
	MAX_LATITUDE = std::numeric_limits<double>::min();
	MIN_LONGITUDE = std::numeric_limits<double>::max();
	MAX_LONGITUDE = std::numeric_limits<double>::min();

	while (!xmlReader.atEnd() && !xmlReader.hasError())
	{
		QXmlStreamReader::TokenType token = xmlReader.readNext();

		if (token == QXmlStreamReader::StartElement)
		{
			if (xmlReader.name().toString() == "node")
			{
				double latitude = xmlReader.attributes().value("latitude").toDouble();
				double longitude = xmlReader.attributes().value("longitude").toDouble();

				MIN_LATITUDE = qMin(MIN_LATITUDE, latitude);
				MAX_LATITUDE = qMax(MAX_LATITUDE, latitude);
				MIN_LONGITUDE = qMin(MIN_LONGITUDE, longitude);
				MAX_LONGITUDE = qMax(MAX_LONGITUDE, longitude);
			}
		}
	}

	if (xmlReader.hasError())
	{
		qDebug() << "Error while parsing XML:" << xmlReader.errorString();
	}

	file.close();
}

void Harta::resizeEvent(QResizeEvent* event)
{
	QMainWindow::resizeEvent(event);

	double mainWindowWidth = width();
	double mainWindowHeight = height();

	double latScale = mainWindowHeight / (MAX_LATITUDE - MIN_LATITUDE);
	double longScale = mainWindowWidth / (MAX_LONGITUDE - MIN_LONGITUDE);

	for (auto& pair : graph.getAdjacencyList())
	{
		Node* node = pair.first;
		QPointF originalPos = node->getMapPos();

		double scaledLatitude = (MAX_LATITUDE - originalPos.y()) * latScale;
		double scaledLongitude = (originalPos.x() - MIN_LONGITUDE) * longScale;

		node->setPos(scaledLongitude, scaledLatitude);
	}

	update();
}
