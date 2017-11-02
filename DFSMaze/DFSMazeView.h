/*
	Programmed by Xiaoqin Du, 383979583@qq.com
	School of Math and Computer Science, 
	Wuhan Textile University
*/

// DFSMazeView.h : interface of the CDFSMazeView class
//

#pragma once

#include "Maze.h"
#include "Search.h"
#include "Draw.h"

class CDFSMazeView : public CView
{
protected: // create from serialization only
	CDFSMazeView();
	DECLARE_DYNCREATE(CDFSMazeView)

// Attributes
public:
	CDFSMazeDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CDFSMazeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

private:
	MyObjects::Maze* m_pMaze;
	MyAI::SearchMaze* m_pSearch;
	CPoint* m_pPathPoints;
	int m_nCount;
	MyGDI::Draw* m_pDraw;

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DFSMazeView.cpp
inline CDFSMazeDoc* CDFSMazeView::GetDocument() const
   { return reinterpret_cast<CDFSMazeDoc*>(m_pDocument); }
#endif

