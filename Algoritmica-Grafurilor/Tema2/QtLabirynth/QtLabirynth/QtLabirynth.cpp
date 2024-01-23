#include "QtLabirynth.h"
#include <fstream>

QtLabirynth::QtLabirynth(QWidget* parent)
	: QWidget(parent)
{
	graphWindow = new QWidget;
	solutionWindow = new QWidget;
	mainLayout = new QHBoxLayout();
	buttonLayout = new QVBoxLayout();
	labirynthLayout = new QGridLayout();
	solutionLayout = new QVBoxLayout;
	labirynthLayout->setSpacing(0);
	solutionLayout->setSpacing(0);

	exitButton = new QPushButton("Exit");
	generateButton = new QPushButton("Generate Labirynth");
	generateGraphButton = new QPushButton("Generate Graph");
	generateLabyrinthSolution = new QPushButton("Generate Solution");
	backButton = new QPushButton("Back");

	buttonLayout->addWidget(generateButton);
	QObject::connect(generateButton, &QPushButton::clicked, this, &QtLabirynth::pushGenerateButton);

	buttonLayout->addWidget(generateGraphButton);
	QObject::connect(generateGraphButton, &QPushButton::clicked, this, &QtLabirynth::pushGenerateGraphButton);

	buttonLayout->addWidget(generateLabyrinthSolution);
	QObject::connect(generateLabyrinthSolution, &QPushButton::clicked, this, &QtLabirynth::pushGenerateSolutionButton);


	buttonLayout->addWidget(exitButton);
	QObject::connect(exitButton, &QPushButton::clicked, this, &QtLabirynth::pushExitButton);

	mainLayout->addLayout(buttonLayout);
	mainLayout->addLayout(labirynthLayout);

	this->setLayout(mainLayout);
}

QtLabirynth::~QtLabirynth()
{
	delete graphWindow;
	delete solutionWindow;
	delete mainLayout;
	delete buttonLayout;
	delete labirynthLayout;
	delete solutionLayout;
	delete exitButton;
	delete generateButton;
	delete generateGraphButton;
	delete generateLabyrinthSolution;
	delete backButton;
}

void QtLabirynth::pushExitButton() {
	close();
}

void QtLabirynth::pushGenerateButton()
{
	std::ifstream inputFile("C:/Users/ELITEBOOK/Documents/Facultate/AG/QtLabirynth/QtLabirynth/labyrinth.txt");
	if (!inputFile) {
		std::cout << "Couldn't open file.";
		exit(1);
	}
	//Matrix save from file (WV)
	int rows = 0, cols = 0;
	inputFile >> rows >> cols;
	std::vector<std::vector<int>> matrix;
	for (int i = 0; i < rows; i++)
	{
		std::vector<int> row;
		for (int j = 0; j < cols; j++)
		{
			int value;
			inputFile >> value;
			row.push_back(value);
		}
		matrix.push_back(row);
	}
	inputFile.close();
	graph.setLabyrinthMatrix(matrix);
	//Adding the nodes into a Graph object (WV)
	std::vector<std::vector<int>> matrixCopy = matrix;
	//matrixCopy will be used to build the adjacencyMatrix
	int value = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (matrix[i][j] != 0)
			{
				value++;
				Node* newNode = new Node;
				newNode->setValue(value);
				newNode->setX(j);
				newNode->setY(i);
				if (matrix[i][j] == 2)
					newNode->setEnd(true);
				else if (matrix[i][j] == 3)
					graph.setStart(newNode);

				graph.addNode(*newNode);
				matrixCopy[i][j] = value;
				//Mark the positions in the labyrinth for wich a Node object was created
				//In the matrixCopy there will be a labyrinthMatrix with 0 for walls and
				//all the other values corresponding to existing node values
			}
		}
	}
	graph.setSolutionMatrix(matrixCopy);//will be used to draw the labyrinth solution
	//Building the Labyrinth Visual (WV)
	QColor colors[] = { Qt::black, Qt::white, Qt::red, Qt::blue };
	for (int i = 0; i < matrix.size(); ++i) {
		for (int j = 0; j < matrix[i].size(); ++j) {
			int value = matrix[i][j];
			QWidget* square = new QWidget();
			square->setFixedSize(50, 50);
			square->setStyleSheet(QString("background-color: %1").arg(colors[value].name()));
			labirynthLayout->addWidget(square, i, j);
		}
	}

	//Building the adjancencyMatrix (WV)
	std::vector<std::vector<int>> adjacencyMatrix(graph.getNodes().size(), std::vector<int>(graph.getNodes().size(), 0));

	for (int i = 0; i < matrixCopy.size(); i++)
	{
		for (int j = 0; j < matrixCopy[i].size(); j++)
		{
			int currentNode = matrixCopy[i][j];
			if (currentNode != 0)
			{
				std::vector<int> adjacentNodes;
				if (i > 0 && matrixCopy[i - 1][j] != 0) // Above
				{
					adjacentNodes.push_back(matrixCopy[i - 1][j]);
				}
				if (i < matrixCopy.size() - 1 && matrixCopy[i + 1][j] != 0) // Below
				{
					adjacentNodes.push_back(matrixCopy[i + 1][j]);
				}
				if (j > 0 && matrixCopy[i][j - 1] != 0) // Left
				{
					adjacentNodes.push_back(matrixCopy[i][j - 1]);
				}
				if (j < matrixCopy[i].size() - 1 && matrixCopy[i][j+1] != 0) // Right
				{
					adjacentNodes.push_back(matrixCopy[i][j+1]);
				}
				for (int k = 0; k < adjacentNodes.size(); k++)
				{
					int adjacentNode = adjacentNodes[k];
					adjacencyMatrix[currentNode - 1][adjacentNode - 1] = 1;
					adjacencyMatrix[adjacentNode - 1][currentNode - 1] = 1;
				}
			}
		}
	}
	graph.setMatrix(adjacencyMatrix);
	//For testing the adjacencyMatrix
	std::vector<std::vector<int>> test = graph.getMatrix();
	for (int i = 0; i < test[0].size(); i++)
	{
		qDebug() << test[i];
		qDebug() << "\n";
	}
	qDebug() << graph.getStartNode().getValue();
	update();
}

void QtLabirynth::pushGenerateGraphButton()
{
	this->hide();
	QObject::connect(backButton, &QPushButton::clicked, this, &QtLabirynth::pushBackButton);

	QVBoxLayout* graphLayout = new QVBoxLayout;
	QGraphicsScene* scene = new QGraphicsScene;
	std::vector<Node> nodes = graph.getNodes();

	for (int i = 0; i < nodes.size(); ++i) {
		int x = nodes[i].getX(); 
		int y = nodes[i].getY();
		QGraphicsEllipseItem* ellipse = scene->addEllipse(x * 50, y * 50, 20, 20);
		if(nodes[i].getValue()==graph.getStartNode().getValue())
			ellipse->setBrush(Qt::blue);
		if(nodes[i].getIsEnd())
			ellipse->setBrush(Qt::red);
		else ellipse->setBrush(Qt::white);
		QGraphicsTextItem* textItem = scene->addText(QString::number(nodes[i].getValue()));
		qreal textWidth = textItem->boundingRect().width();
		qreal textHeight = textItem->boundingRect().height();
		textItem->setPos(x * 50 + (20 - textWidth) / 2, y * 50 + (20 - textHeight) / 2);
	}
	std::vector<std::vector<int>> adjacencyMatrix = graph.getMatrix();
	
	for (int i = 0; i < adjacencyMatrix.size(); ++i) {
		for (int j = 0; j < adjacencyMatrix[i].size(); ++j) {
			if (adjacencyMatrix[i][j] == 1) {
				int x1 = nodes[i].getX(); 
				int y1 = nodes[i].getY(); 
				int x2 = nodes[j].getX();
				int y2 = nodes[j].getY();
				QGraphicsLineItem* line = scene->addLine(x1 * 50 + 10, y1 * 50 + 10, x2 * 50 + 10, y2 * 50 + 10); // Adjust line position
				line->setZValue(-1);
			}
		}
	}

	QGraphicsView* view = new QGraphicsView(scene);
	graphLayout->addWidget(view);
	graphLayout->addWidget(backButton);

	graphWindow->setLayout(graphLayout);
	graphWindow->show();
}

void QtLabirynth::pushBackButton()
{
	graphWindow->hide();
	this->show();
}

void QtLabirynth::pushGenerateSolutionButton()
{
	this->hide();
	
	if (graph.getNodes().empty()) {
		std::cout << "Graph wasn't generated yet.";
		exit(2);
	}
	else
	{
		graph.breadthFirst();
		std::vector<Node*> exitNodes;
		for (Node& node : graph.getNodes())
		{
			if (node.getIsEnd())
				exitNodes.push_back(&node);
		}
		for (int i = 0; i < exitNodes.size(); i++)
		{
			if (exitNodes[i] == nullptr)
			{
				std::cout << "Null pointer at index " << i << "." << std::endl;
				exit(3);
			}
			else
			{
				std::cout << "Processing exit node at index " << i << " with value " << exitNodes[i]->getValue() << "." << std::endl;
				graph.exitRoad(*exitNodes[i]);
			}
		}

		//deseneaza labirintul (again)
		
		std::vector<std::vector<int>> matrix = graph.getLabyrinthMatrix();
		QGridLayout* newLabyrinth = new QGridLayout;
		QColor colors[] = { Qt::black, Qt::white, Qt::red, Qt::blue };
		/*for (int i = 0; i < matrix.size(); ++i) {
			for (int j = 0; j < matrix[i].size(); ++j) {
				int value = matrix[i][j];
				QWidget* square = new QWidget();
				square->setFixedSize(50, 50);
				square->setStyleSheet(QString("background-color: %1").arg(colors[value].name()));
				newLabyrinth->addWidget(square, i, j);
			}
		}*/
		////Update roads
		std::vector<std::vector<int>> matrixSolution = graph.getSolutionMatrix();
		for (int i = 0; i < matrix.size(); ++i) {
			for (int j = 0; j < matrix[i].size(); ++j) {
				int value = matrix[i][j];
				QWidget* square = new QWidget();
				square->setFixedSize(50, 50);
				if (graph.getNode(matrixSolution[i][j])->getIsGoodRoad() == true && matrixSolution[i][j]!=graph.getStartNode().getValue()) {
					square->setStyleSheet("background-color: green");
				}
				else {
					square->setStyleSheet(QString("background-color: %1").arg(colors[value].name()));
				}
				newLabyrinth->addWidget(square, i, j);
			}
		}
		solutionLayout->addLayout(newLabyrinth);
		solutionWindow->setLayout(solutionLayout);
		solutionWindow->show();
	}
}
