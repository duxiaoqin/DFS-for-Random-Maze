/*
	Programmed by Xiaoqin Du, 383979583@qq.com
	School of Math and Computer Science, 
	Wuhan Textile University
*/

#include "stdafx.h"

#include "Search.h"

MyAI::SearchMaze::SearchMaze(MyObjects::Maze* pMaze)
{
	m_pMaze = pMaze;
	m_ppMaze = m_pMaze->GetMaze();
	m_posStart = m_pMaze->GetStartLoc();
	m_posGoal = m_pMaze->GetGoalLoc();
	m_posCurrent = m_posStart;
	m_pMazePathPoints = NULL;

	isFound = false;

	m_ppMazePoints = new CPoint*[m_pMaze->GetHeight()];
	for (int row = 0; row < m_pMaze->GetHeight(); row++)
		m_ppMazePoints[row] = new CPoint[m_pMaze->GetWidth()];

	for (int row = 0; row < m_pMaze->GetHeight(); row++)
		for (int col = 0; col < m_pMaze->GetWidth(); col++) {
			m_ppMazePoints[row][col].x = UNSEARCH_VALUE;
			m_ppMazePoints[row][col].y = UNSEARCH_VALUE;
		}
}

MyAI::SearchMaze::~SearchMaze()
{
	//ªÿ ’m_ppMazePointsø’º‰
	for (int row = 0; row < m_pMaze->GetHeight(); row++)
		delete[] m_ppMazePoints[row];
	delete[] m_ppMazePoints;
}

CPoint* MyAI::SearchMaze::GetPossibleMoves(CPoint pos)
{
	CPoint* possMoves = new CPoint[4];
	for (int i = 0; i < 4; i++) {
		possMoves[i].x = UNSEARCH_VALUE;
		possMoves[i].y = UNSEARCH_VALUE;
	}

	if (m_ppMaze[pos.y][pos.x-1] == m_pMaze->PASS_VALUE) {
		possMoves[0].x = pos.x - 1;
		possMoves[0].y = pos.y;
	}

	if (m_ppMaze[pos.y][pos.x+1] == m_pMaze->PASS_VALUE) {
		possMoves[1].x = pos.x + 1;
		possMoves[1].y = pos.y;
	}

	if (m_ppMaze[pos.y-1][pos.x] == m_pMaze->PASS_VALUE) {
		possMoves[2].x = pos.x;
		possMoves[2].y = pos.y - 1;
	}

	if (m_ppMaze[pos.y+1][pos.x] == m_pMaze->PASS_VALUE) {
		possMoves[3].x = pos.x;
		possMoves[3].y = pos.y + 1;
	}

	return possMoves;
}

void MyAI::SearchMaze::DepthFirstSearchEngine(CPoint curPos)
{
	if (isFound)
		return;

	CPoint* moves = GetPossibleMoves(curPos);
	short depth = m_ppMaze[curPos.y][curPos.x];

	for (int i = 0; i < 4; i++) {
		if (moves[i].x == UNSEARCH_VALUE ||
			moves[i].y == UNSEARCH_VALUE)
			continue;

		m_pMaze->SetValue(moves[i].y, moves[i].x, depth + 1);
		m_ppMazePoints[moves[i].y][moves[i].x] = curPos;
		if (moves[i].y == m_pMaze->GetGoalLoc().y &&
			moves[i].x == m_pMaze->GetGoalLoc().x) {
			isFound = true;
			return;
		}

		DepthFirstSearchEngine(moves[i]);
		if (isFound)
			return;
	}

	delete moves;
}

void MyAI::SearchMaze::DepthFirstSearch()
{
	DepthFirstSearchEngine(m_posCurrent);
}

CPoint* MyAI::SearchMaze::GetPathPoints(int* outCount)
{
	bool isPath;
	int count;

	CPoint goalPos;
	CPoint curPos;

	isPath = false;
	count = 1;
	goalPos = m_pMaze->GetGoalLoc();
	curPos = m_ppMazePoints[goalPos.y][goalPos.x];

	while (curPos.x != UNSEARCH_VALUE && curPos.y != UNSEARCH_VALUE) {
		count++;
		if (curPos.y == m_pMaze->GetStartLoc().y && curPos.x == m_pMaze->GetStartLoc().x) {
			isPath = true;
			break;
		}
		curPos = m_ppMazePoints[curPos.y][curPos.x];
	}

	if (isPath) {
		*outCount = count;
		m_pMazePathPoints = new CPoint[count];
		isPath = false;
		count = 1;
		goalPos = m_pMaze->GetGoalLoc();
		curPos = m_ppMazePoints[goalPos.y][goalPos.x];
		m_pMazePathPoints[count-1] = goalPos;

		while (curPos.x != UNSEARCH_VALUE && curPos.y != UNSEARCH_VALUE) {
			count++;
			m_pMazePathPoints[count-1] = curPos;
			if (curPos.y == m_pMaze->GetStartLoc().y && curPos.x == m_pMaze->GetStartLoc().x) {
				isPath = true;
				break;
			}
			curPos = m_ppMazePoints[curPos.y][curPos.x];
		}
	}
	else
		m_pMazePathPoints = NULL;

	return m_pMazePathPoints;
}