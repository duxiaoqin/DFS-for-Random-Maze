/*
	Programmed by Xiaoqin Du, 383979583@qq.com
	School of Math and Computer Science, 
	Wuhan Textile University
*/

// DFSMazeView.cpp : implementation of the CDFSMazeView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "DFSMaze.h"
#endif

#include "DFSMazeDoc.h"
#include "DFSMazeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDFSMazeView

IMPLEMENT_DYNCREATE(CDFSMazeView, CView)

BEGIN_MESSAGE_MAP(CDFSMazeView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CDFSMazeView construction/destruction

CDFSMazeView::CDFSMazeView()
{
	// TODO: add construction code here
	m_pMaze = new MyObjects::Maze(30, 20);
	m_pSearch = new MyAI::SearchMaze(m_pMaze);
	m_pSearch->DepthFirstSearch();
	m_pPathPoints = m_pSearch->GetPathPoints(&m_nCount);
	m_pDraw = new MyGDI::Draw(m_pMaze);
}

CDFSMazeView::~CDFSMazeView()
{
	delete[] m_pPathPoints;
	delete m_pDraw;
	delete m_pSearch;
	delete m_pMaze;
}

BOOL CDFSMazeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CDFSMazeView drawing

void CDFSMazeView::OnDraw(CDC* pDC)
{
	CDFSMazeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	m_pDraw->DrawMaze(pDC, m_pPathPoints, m_nCount);
}


// CDFSMazeView printing

BOOL CDFSMazeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDFSMazeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDFSMazeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CDFSMazeView diagnostics

#ifdef _DEBUG
void CDFSMazeView::AssertValid() const
{
	CView::AssertValid();
}

void CDFSMazeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDFSMazeDoc* CDFSMazeView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDFSMazeDoc)));
	return (CDFSMazeDoc*)m_pDocument;
}
#endif //_DEBUG


// CDFSMazeView message handlers
