/*
	Programmed by Xiaoqin Du, 383979583@qq.com
	School of Math and Computer Science, 
	Wuhan Textile University
*/

#pragma once

#include "Maze.h"

namespace MyAI {
	class SearchMaze {
	public:
		SearchMaze(MyObjects::Maze* pMaze);
		~SearchMaze();
		CPoint* GetPossibleMoves(CPoint pos);
		void DepthFirstSearch();
		CPoint* GetPathPoints(int* outCount);

	public:
		static const int UNSEARCH_VALUE = -1;

	private:
		void DepthFirstSearchEngine(CPoint curPos);

	private:
		MyObjects::Maze* m_pMaze;
		short** m_ppMaze;

		CPoint m_posStart;
		CPoint m_posGoal;
		CPoint m_posCurrent;

		CPoint** m_ppMazePoints;

		CPoint* m_pMazePathPoints;

		bool isFound;
	};
}