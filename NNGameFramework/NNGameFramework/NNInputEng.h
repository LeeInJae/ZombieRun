#pragma once
#include "NNObject.h"
#include <fstream>
#include <string>
#include "NNSound.h"
#include "PRE_DEFINE.h"

class NNLabel;

class NNInputEng :	public NNObject
{
public:
	NNInputEng(void);
	~NNInputEng(void);

	//NNCREATE_FUNC( NNInputEng );

	
	float GetSpeed() { return m_Speed; }
	void SetSpeed( float speed ) { m_Speed = speed; m_Velocity = m_Speed / 60.f; }
	void SetCheckAnswer( bool check) { m_CheckAnswer = check; }
	bool GetCheckAnswer() { return m_CheckAnswer; }
	bool GetSpecialCehcek() { return m_SpecialCheck; }
	unsigned int GetCombo() { return m_Combo; }
	void SetEnd( bool end );
	bool GetEnd() { return m_End; }
	unsigned int  GetMaxCombo() { return m_MaxCombo; }
	unsigned int  GetMaxTotCombo() { return m_TotCombo; }
private:
	void Init() {};
	void Number_Init();
	void Label_Init();
	void File_Init();
	void File_Close();
	void Update( float dTime );

	NNLabel*			m_pContentString;
	NNLabel*			m_pContentString2;

	//임시변수
	char				m_InputStrings[ IN_MAX_LENGTH ][ IN_MAX_LENGTH ];
	int					m_DataCount;
	int					m_Index;

	size_t				m_convertedChars;
	size_t				m_convertedChars2;
	
	char				m_InputString[ IN_MAX_LENGTH ];
	char				m_Playerstring[ IN_MAX_LENGTH ];

	std::ifstream		m_fin;
	float				m_SumTime;
	float				m_Speed;
	float				m_Velocity;
	float				m_PivotTime;

	wchar_t*			m_Wcstring;
	wchar_t*			m_Wcstring2;
	
	bool				m_Check;
	bool				m_End;
	int					m_Len;
	unsigned int		m_MaxCombo;
	unsigned int		m_TotCombo;
	int					m_Input_position;
	std::string			m_Player_Input_String;
	bool				m_CheckAnswer;
	unsigned int		m_Combo;
	bool				m_AnswerCheck;
	bool				m_SpecialCheck;
	NNSound*			m_AnswerSound;
	NNSound*			m_WrongSound;
	NNSound*			m_MissileSound;
};