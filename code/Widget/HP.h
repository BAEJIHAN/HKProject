
#pragma once

#include "Widget/WidgetWindow.h"
#include "Widget/Image.h"
#include "Widget/Text.h"
class CHP :
	public CWidgetWindow
{
	friend class CViewport;

protected:
	CHP();
	CHP(const CHP& window);
	virtual ~CHP();

private:

	CSharedPtr<CImage>	m_HP;
	CSharedPtr<CImage> Piece[5];
	//CSharedPtr<CImage> Piece;
	CSharedPtr<CText> Text;

	float time;
	int flag;

	bool PieceDie[5];
	
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CHP* Clone();

	void SetDie(int index);
	void SetText(const TCHAR* t);
	void SetTextOpacity(float f);
public:

};

